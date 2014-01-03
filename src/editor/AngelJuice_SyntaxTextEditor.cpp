/*
  ==============================================================================

   This file is part of the eJUCE library
   which is based on Raw Material Software ltd. JUCE

   eJUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   eJUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eJUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

   @author	Asnaghi Lucio

  ==============================================================================
*/

#include "AngelJuice_SyntaxTextEditor.h"


//==============================================================================
class SyntaxTextEditorInsertAction  : public UndoableAction
{
    SyntaxTextEditor& owner;
    const String text;
    const int insertIndex, oldCaretPos, newCaretPos;
    const Colour colour;

    SyntaxTextEditorInsertAction (const SyntaxTextEditorInsertAction&);
    const SyntaxTextEditorInsertAction& operator= (const SyntaxTextEditorInsertAction&);

public:
    SyntaxTextEditorInsertAction (SyntaxTextEditor& owner_,
                            const String& text_,
                            const int insertIndex_,
                            const Colour& colour_,
                            const int oldCaretPos_,
                            const int newCaretPos_)
        : owner (owner_),
          text (text_),
          insertIndex (insertIndex_),
          oldCaretPos (oldCaretPos_),
          newCaretPos (newCaretPos_),
          colour (colour_)
    {
    }

    ~SyntaxTextEditorInsertAction()
    {
    }

    bool perform()
    {
        owner.insert (text, insertIndex, colour, 0, newCaretPos);
        return true;
    }

    bool undo()
    {
        owner.remove (insertIndex, insertIndex + text.length(), 0, oldCaretPos);
        return true;
    }

    int getSizeInUnits()
    {
        return text.length() + 16;
    }
};

//==============================================================================
class SyntaxTextEditorRemoveAction  : public UndoableAction
{
    SyntaxTextEditor& owner;
    const int startIndex, endIndex, oldCaretPos, newCaretPos;
    const String text;

    SyntaxTextEditorRemoveAction (const SyntaxTextEditorRemoveAction&);
    const SyntaxTextEditorRemoveAction& operator= (const SyntaxTextEditorRemoveAction&);

public:
    SyntaxTextEditorRemoveAction (SyntaxTextEditor& owner_,
							const String& text_,
                            const int startIndex_,
                            const int endIndex_,
                            const int oldCaretPos_,
                            const int newCaretPos_)
        : owner (owner_),
          startIndex (startIndex_),
          endIndex (endIndex_),
          oldCaretPos (oldCaretPos_),
          newCaretPos (newCaretPos_),
          text (text_)
    {
    }

    ~SyntaxTextEditorRemoveAction()
    {
    }

    bool perform()
    {
        owner.remove (startIndex, endIndex, 0, newCaretPos);
        return true;
    }

    bool undo()
    {
		owner.insert (text, startIndex, owner.textColour, 0, oldCaretPos);
        return true;
    }

    int getSizeInUnits()
    {
        return text.length() + 16;
    }
};

//==============================================================================
class SyntaxTextHolderComponent  : public Component,
							       public Timer
{
    SyntaxTextEditor* const owner;

    SyntaxTextHolderComponent (const SyntaxTextHolderComponent&);
    const SyntaxTextHolderComponent& operator= (const SyntaxTextHolderComponent&);

public:
    SyntaxTextHolderComponent (SyntaxTextEditor* const owner_)
        : owner (owner_)
    {
        setWantsKeyboardFocus (false);
        setInterceptsMouseClicks (false, true);
    }

    ~SyntaxTextHolderComponent()
    {
    }

    void paint (Graphics& g)
    {
        owner->drawContent (g);
    }

    void timerCallback()
    {
        owner->timerCallbackInt();
    }

    const MouseCursor getMouseCursor()
    {
        return owner->getMouseCursor();
    }
};

//==============================================================================
class SyntaxTextEditorViewport  : public Viewport
{
    SyntaxTextEditor* const owner;

    SyntaxTextEditorViewport (const SyntaxTextEditorViewport&);
    const SyntaxTextEditorViewport& operator= (const SyntaxTextEditorViewport&);

public:
    SyntaxTextEditorViewport (SyntaxTextEditor* const owner_)
        : owner (owner_)
    {
    }

    ~SyntaxTextEditorViewport()
    {
    }

    void visibleAreaChanged (int, int, int, int)
    {
        owner->updateTextHolderSize();
    }
};

//==============================================================================
const int flashSpeedIntervalMs = 500;

const int textChangeMessageId        = 0x10003001;
const int returnKeyMessageId         = 0x10003002;
const int escapeKeyMessageId         = 0x10003003;
const int focusLossMessageId         = 0x10003004;
const int changeBreakPointMessageId  = 0x10003005;


//==============================================================================
SyntaxTextEditor::SyntaxTextEditor (const String& name)
    : Component (name),
      borderSize (1, 1, 1, 3),
      readOnly (false),
      caretVisible (true),
      popupMenuEnabled (true),
      selectAllTextWhenFocused (false),
      menuVisible (false),
      wasFocused (false),
      caretFlashState (true),
      keepCursorOnScreen (true),
	  breakPointsEnabled (false),
	  debugMode (false),
      cursorX (0),
      cursorY (0),
      cursorHeight (0),
      selectionStart (0),
      selectionEnd (0),
      leftIndent (46),
      topIndent (4),
      lastTransactionTime (0),
      totalNumChars (0),
      caretPosition (0),
	  linePosition (-1),
	  lastInsertChar (0),
      currentFont (14.0f),
      backgroundColour (Colours::white),
      textColour (Colours::black),
      highlightColour (Colour (0x401111ee)),
      caretColour (Colours::black),
      shadowColour (0x38000000),
      document (T(""), currentFont),
      dragType (notDragging),
      listeners (2)
{
    setOpaque (true);

    addAndMakeVisible (viewport = new SyntaxTextEditorViewport (this));
    viewport->setViewedComponent (textHolder = new SyntaxTextHolderComponent (this));
    viewport->setWantsKeyboardFocus (false);
    viewport->setScrollBarsShown (true, true);

    setMouseCursor (MouseCursor::IBeamCursor);
    setWantsKeyboardFocus (true);
    Component::beginDragAutoRepeat (100);

	// ------------------------
	// suggestBox = new SuggestFunctionListBox (this);

	functions.add (T("drawComponent"));
	functions.add (T("selectComponent"));
	functions.add (T("exitComponent"));
	functions.add (T("add"));
}

SyntaxTextEditor::~SyntaxTextEditor()
{
    clearInternal (0);
    delete viewport;
	//	delete suggestBox;
}



//==============================================================================
/*
int SyntaxTextEditor::getNumRows()
{
	return functions.size ();
}

void SyntaxTextEditor::paintListBoxItem (int rowNumber,
                                         Graphics& g,
                                         int width, int height,
                                         bool rowIsSelected)
{
	if (rowNumber > functions.size())
		return;

	if (rowIsSelected)
		g.fillAll(Colours::azure.brighter(1.5f));

	g.setColour(Colours::black);
	g.setFont(currentFont);
	g.drawText(functions[rowNumber],
			0+5, 5, width-5, height-5,
			Justification::centredLeft, true);
}

void SyntaxTextEditor::selectedRowsChanged (int row)
{
	if (row < 0 || row >= functions.size())
		return;

	suggestBox->repaint();
}

void SyntaxTextEditor::listBoxItemClicked (int numRow, const MouseEvent& e)
{
	suggestBox->close();
}

void SyntaxTextEditor::deleteKeyPressed (int numRow)
{
	suggestBox->close();
}

void SyntaxTextEditor::returnKeyPressed (int numRow)
{
	suggestBox->close();
}
*/


//==============================================================================
void SyntaxTextEditor::newTransaction()
{
    lastTransactionTime = Time::getApproximateMillisecondCounter();
    undoManager.beginNewTransaction();
}

void SyntaxTextEditor::doUndoRedo (const bool isRedo)
{
    if (! isReadOnly())
    {
        if ((isRedo) ? undoManager.redo()
                     : undoManager.undo())
        {
            scrollToMakeSureCursorIsVisible();
            repaint();
            textChanged();
        }
    }
}

//==============================================================================
void SyntaxTextEditor::setReadOnly (const bool shouldBeReadOnly)
{
    readOnly = shouldBeReadOnly;

    setWantsKeyboardFocus (! shouldBeReadOnly);
    enablementChanged();
}

bool SyntaxTextEditor::isReadOnly() const
{
    return readOnly || ! isEnabled();
}

void SyntaxTextEditor::setPopupMenuEnabled (bool b)
{
    popupMenuEnabled = b;
}

void SyntaxTextEditor::setSelectAllWhenFocused (bool b)
{
    selectAllTextWhenFocused = b;
}

//==============================================================================
const Font SyntaxTextEditor::getFont() const
{
    return currentFont;
}

void SyntaxTextEditor::setFont (const Font& newFont)
{
    currentFont = newFont;

	document.setFont (newFont);

    updateTextHolderSize();
    scrollToMakeSureCursorIsVisible();
    repaint();
}

void SyntaxTextEditor::setColours (const Colour& newForeground,
                             const Colour& newBackground,
                             const Colour& newHighlight,
                             const Colour& newOutlineColour,
                             const Colour& dropShadowColour)
{
    textColour = newForeground;
    backgroundColour = newBackground;
    highlightColour = newHighlight;
    outlineColour = newOutlineColour;
    shadowColour = dropShadowColour;

    setOpaque (newBackground.isOpaque());
    repaint();
}

void SyntaxTextEditor::setCaretColour (const Colour& colour)
{
    caretColour = colour;
    repaintCaret();
}

void SyntaxTextEditor::setCaretVisible (bool shouldCaretBeVisible)
{
    caretVisible = shouldCaretBeVisible;

    if (shouldCaretBeVisible)
        textHolder->startTimer (flashSpeedIntervalMs);

    setMouseCursor (shouldCaretBeVisible ? MouseCursor::IBeamCursor
                                         : MouseCursor::NormalCursor);
}

void SyntaxTextEditor::setScrollBarThickness (const int newThicknessPixels)
{
    viewport->setScrollBarThickness (newThicknessPixels);
}

void SyntaxTextEditor::setScrollBarButtonVisibility (const bool buttonsVisible)
{
    viewport->setScrollBarButtonVisibility (buttonsVisible);
}

//==============================================================================
void SyntaxTextEditor::clear()
{
    clearInternal (0);
    undoManager.clearUndoHistory();
}

void SyntaxTextEditor::setText (const String& newText,
                                const bool sendTextChangeMessage)
{
    const int newLength = newText.length();

    if (newLength != getTotalNumChars() || getText() != newText)
    {
        const int oldCursorPos = caretPosition;
        // const bool cursorWasAtEnd = oldCursorPos >= getTotalNumChars();

        clearInternal (0);
        insert (newText, 0, textColour, 0, caretPosition);

        moveCursorTo (oldCursorPos, false);

        if (sendTextChangeMessage)
            textChanged();

        repaint();
    }

    updateTextHolderSize();
    scrollToMakeSureCursorIsVisible();
    undoManager.clearUndoHistory();
}

//==============================================================================
void SyntaxTextEditor::textChanged()
{
    updateTextHolderSize();
    postCommandMessage (textChangeMessageId);
}

void SyntaxTextEditor::returnPressed()
{
    postCommandMessage (returnKeyMessageId);
}

void SyntaxTextEditor::escapePressed()
{
    postCommandMessage (escapeKeyMessageId);
}

void SyntaxTextEditor::addListener (SyntaxTextEditorListener* const newListener)
{
    listeners.addIfNotAlreadyThere (newListener);
}

void SyntaxTextEditor::removeListener (SyntaxTextEditorListener* const listenerToRemove)
{
    listeners.removeValue (listenerToRemove);
}

//==============================================================================
void SyntaxTextEditor::timerCallbackInt()
{
    const bool newState = (! caretFlashState) && ! isCurrentlyBlockedByAnotherModalComponent();

    if (caretFlashState != newState)
    {
        caretFlashState = newState;

        if (caretFlashState)
            wasFocused = true;

        if (caretVisible
             && hasKeyboardFocus (false)
             && ! isReadOnly())
        {
            repaintCaret();
        }
    }

    const unsigned int now = Time::getApproximateMillisecondCounter();

    if (now > lastTransactionTime + 250)
        newTransaction();
}

void SyntaxTextEditor::repaintCaret()
{
    if (! caretColour.isTransparent())
        textHolder->repaint (leftIndent + roundFloatToInt (cursorX) - 1,
                             topIndent + roundFloatToInt (cursorY) - 1,
                             4,
                             roundFloatToInt (cursorHeight) + 2);
}

void SyntaxTextEditor::repaintText (int textStartIndex, int textEndIndex)
{
    if (textStartIndex > textEndIndex && textEndIndex > 0)
        swapVariables (textStartIndex, textEndIndex);

    float x, y, lh;
    getCharPosition (textStartIndex, x, y, lh);
    const int y1 = (int) y;

    int y2;

    if (textEndIndex >= 0)
    {
        getCharPosition (textEndIndex, x, y, lh);
        y2 = (int) (y + lh * 2.0f);
    }
    else
    {
        y2 = textHolder->getHeight();
    }

    textHolder->repaint (0, y1, textHolder->getWidth(), y2 - y1);
}

//==============================================================================
void SyntaxTextEditor::moveCaret (int newCaretPos)
{
    if (newCaretPos < 0)
        newCaretPos = 0;
    else if (newCaretPos > getTotalNumChars())
        newCaretPos = getTotalNumChars();

    if (newCaretPos != getCaretPosition())
    {
        repaintCaret();
        caretFlashState = true;
        caretPosition = newCaretPos;
        textHolder->startTimer (flashSpeedIntervalMs);
        scrollToMakeSureCursorIsVisible();
        repaintCaret();
    }
}

void SyntaxTextEditor::setCaretPosition (const int newIndex)
{
    moveCursorTo (newIndex, false);
}

int SyntaxTextEditor::getCaretPosition() const
{
    return caretPosition;
}

int SyntaxTextEditor::getCaretLineNumber() const
{
	// @TODO - improve this

	String text = document.getAllText();

	int lineCount = 1;
	int index = caretPosition;
	int start = 0, end = text.indexOf (start, T("\n"));

	while (end >= 0 && (index < start || index > end))
	{
		start = end + 1;
		end = text.indexOf (start, T("\n"));
		lineCount++;
	}

	return lineCount;
}

//==============================================================================
void SyntaxTextEditor::updateTextHolderSize()
{
    float maxWidth = 0.0f;

	SyntaxDocumentIterator i (&document);

    while (i.next())
        maxWidth = jmax (maxWidth, i.atomRight);

    const int w = leftIndent + roundFloatToInt (maxWidth);
    const int h = topIndent + roundFloatToInt (jmax (i.lineY + i.lineHeight,
                                                     currentFont.getHeight()));

    textHolder->setSize (w + 1, h + 1);
}

int SyntaxTextEditor::getTextWidth() const
{
    return textHolder->getWidth();
}

int SyntaxTextEditor::getTextHeight() const
{
    return textHolder->getHeight();
}

void SyntaxTextEditor::setIndents (const int newLeftIndent,
                             const int newTopIndent)
{
    leftIndent = newLeftIndent;
    topIndent = newTopIndent;
}

void SyntaxTextEditor::setBorder (const BorderSize& border)
{
    borderSize = border;
    resized();
}

const BorderSize SyntaxTextEditor::getBorder() const throw()
{
    return borderSize;
}

void SyntaxTextEditor::setScrollToShowCursor (const bool shouldScrollToShowCursor) throw()
{
    keepCursorOnScreen = shouldScrollToShowCursor;
}

void SyntaxTextEditor::scrollToMakeSureCursorIsVisible()
{
    if (keepCursorOnScreen)
    {
        cursorHeight = currentFont.getHeight(); // (in case the text is empty and the call below doesn't set this value)

        getCharPosition (caretPosition,
                         cursorX, cursorY,
                         cursorHeight);

        int x = viewport->getViewPositionX();
        int y = viewport->getViewPositionY();

        const int relativeCursorX = roundFloatToInt (cursorX) - x;
        const int relativeCursorY = roundFloatToInt (cursorY) - y;

        if (relativeCursorX < jmax (1, proportionOfWidth (0.05f)))
        {
            x += relativeCursorX - proportionOfWidth (0.2f);
        }
        else if (relativeCursorX > jmax (0, viewport->getMaximumVisibleWidth() - 10))
        {
            x += relativeCursorX + proportionOfWidth (0.2f) - viewport->getMaximumVisibleWidth();
        }

        x = jlimit (0, jmax (0, textHolder->getWidth() + 8 - viewport->getMaximumVisibleWidth()), x);

        const int curH = roundFloatToInt (cursorHeight);
        if (relativeCursorY < 0)
        {
            y = jmax (0, relativeCursorY + y);
        }
        else if (relativeCursorY > jmax (0, viewport->getMaximumVisibleHeight() - topIndent - curH))
        {
            y += relativeCursorY + 2 + curH + topIndent - viewport->getMaximumVisibleHeight();
        }

        viewport->setViewPosition (x, y);
    }
}

void SyntaxTextEditor::moveCursorTo (const int newPosition,
                                     const bool isSelecting)
{
    if (isSelecting)
    {
        moveCaret (newPosition);
        repaintText (selectionStart, selectionEnd);

        if (dragType == notDragging)
        {
            if (abs (getCaretPosition() - selectionStart) < abs (getCaretPosition() - selectionEnd))
                dragType = draggingSelectionStart;
            else
                dragType = draggingSelectionEnd;
        }

        if (dragType == draggingSelectionStart)
        {
            selectionStart = getCaretPosition();

            if (selectionEnd < selectionStart)
            {
                swapVariables (selectionStart, selectionEnd);
                dragType = draggingSelectionEnd;
            }
        }
        else
        {
            selectionEnd = getCaretPosition();

            if (selectionEnd < selectionStart)
            {
                swapVariables (selectionStart, selectionEnd);
                dragType = draggingSelectionStart;
            }
        }

        repaintText (selectionStart, selectionEnd);
    }
    else
    {
        dragType = notDragging;

        if (selectionEnd > selectionStart)
            repaintText (selectionStart, selectionEnd);

        moveCaret (newPosition);
        selectionStart = getCaretPosition();
        selectionEnd = getCaretPosition();
    }
}

int SyntaxTextEditor::getTextIndexAt (const int x,
                                      const int y)
{
    return indexAtPosition ((float) (x + viewport->getViewPositionX() - leftIndent),
                            (float) (y + viewport->getViewPositionY() - topIndent));
}

int SyntaxTextEditor::getTextLineAt (const int x,
                                     const int y)
{
	int index = indexAtPosition ((float) (x + viewport->getViewPositionX() - leftIndent),
                                 (float) (y + viewport->getViewPositionY() - topIndent));

    String text = document.getAllText();

	int lineCount = 1;
	int start = 0, end = text.indexOf (start, T("\n"));

	while (end >= 0 && (index < start || index > end))
	{
		start = end + 1;
		end = text.indexOf (start, T("\n"));
		lineCount++;
	}

	return lineCount;
}

void SyntaxTextEditor::getTextPositionOfLine (const int lineNumber,
											  int& startIndex,
											  int& numberOfCharactersInTheLine)
{
    String text = document.getAllText();

	int start = 0;
	int end = text.indexOf (start, T("\n"));
	int lineCount = 1;

	while (end >= 0 && lineCount < lineNumber)
	{
		start = end + 1;
		end = text.indexOf (start, T("\n"));
		lineCount++;
	}

	end = text.indexOf (start, T("\n"));
	if (end < 0)
		end = text.length() - start;
	end -= start;

	if (end <= 0)
		end = 1;

	startIndex = start;
	numberOfCharactersInTheLine = end;
}

void SyntaxTextEditor::insertTextAtCursor (String newText)
{
    const int newCaretPos = selectionStart + newText.length();
    const int insertIndex = selectionStart;

    remove (selectionStart, selectionEnd,
            &undoManager,
            newCaretPos);

    if (newText.isNotEmpty())
        insert (newText,
                insertIndex,
                textColour,
                &undoManager,
                newCaretPos);

    textChanged();
}

void SyntaxTextEditor::setHighlightedRegion (int startPos, int numChars)
{
    moveCursorTo (startPos, false);
    moveCursorTo (startPos + numChars, true);
}

//==============================================================================
void SyntaxTextEditor::copy()
{
    const String selection (getTextSubstring (selectionStart, selectionEnd));

    if (selection.isNotEmpty())
        SystemClipboard::copyTextToClipboard (selection);
}

void SyntaxTextEditor::paste()
{
    if (! isReadOnly())
    {
        const String clip (SystemClipboard::getTextFromClipboard());

        if (clip.isNotEmpty())
            insertTextAtCursor (clip);
    }
}

void SyntaxTextEditor::cut()
{
    if (! isReadOnly())
    {
        moveCaret (selectionEnd);
        insertTextAtCursor (String::empty);
    }
}

//==============================================================================
void SyntaxTextEditor::drawContent (Graphics& g)
{
	g.setFont (currentFont);

	drawLineNumbers (g);

	g.setOrigin (leftIndent, topIndent);
    const Rectangle clip (g.getClipBounds());

    if (selectionStart < selectionEnd)
    {
        g.setColour (hasKeyboardFocus (true) ? highlightColour.withMultipliedAlpha (0.8f)
                                             : highlightColour.withMultipliedAlpha (0.5f));

		SyntaxDocumentIterator i (&document);
        while (i.next() && i.lineY < clip.getBottom())
        {
            if (i.lineY + i.lineHeight >= clip.getY()
                 && selectionEnd >= i.indexInText
                 && selectionStart <= i.indexInText + i.atom->numChars)
            {
                i.drawSelection (g, selectionStart, selectionEnd);
            }
        }
    }

	g.setColour (textColour);
	SyntaxDocumentIterator i (&document);
    while (i.next() && i.lineY < clip.getBottom())
    {
        if (i.lineY + i.lineHeight >= clip.getY())
            i.draw (g);
    }

    if (caretFlashState
         && hasKeyboardFocus (false)
         && caretVisible
         && ! isReadOnly())
    {
        g.setColour (caretColour);
        g.fillRect (cursorX, cursorY, 2.0f, cursorHeight);
    }
}

void SyntaxTextEditor::drawLineNumbers (Graphics& g)
{
    const Rectangle clip (g.getClipBounds());

	g.setColour (Colour::greyLevel(0.8f));
	g.fillRect (0, 0, leftIndent-2, textHolder->getHeight());

	g.setColour (Colours::black);

	int lineNumber = 1;
	float oldLineY = -1.0f;
	int topOffset = topIndent - 1;

	SyntaxDocumentIterator i (&document);
	while (i.next() && i.lineY < clip.getBottom())
	{
		if (oldLineY != i.lineY)
		{
			if (i.lineY + i.lineHeight >= clip.getY())
			{
				// draw line number
                g.setColour (Colours::black);
				g.drawSingleLineText (String(lineNumber), 4, topOffset + (int)(i.lineY + i.lineHeight));

				// draw breakpoints
				if (breakPointsEnabled && breakPoints.contains (lineNumber))
				{
				    g.setColour (Colours::red.withAlpha (0.5f));
					g.fillEllipse (leftIndent - 12, topIndent + (int)(i.lineY), 8, i.lineHeight - 1);
				}
			}

			// current line execution indicator
			if (linePosition == lineNumber)
			{
				int startX = leftIndent / 2;
				int endX = leftIndent - 2;
                int startY = (int) i.lineY + topIndent + (int) currentFont.getHeight() / 2;
                int halfHeight = (int) i.lineHeight / 2;

				g.setColour (Colours::yellow.withAlpha (0.5f));
				g.drawArrow (startX, startY, endX, startY, halfHeight, i.lineHeight, halfHeight);
			}

			++lineNumber;
			oldLineY = i.lineY;
		}
	}

	// line number not shown on last line if no chars on it
	if (i.atom && i.atom->numChars && i.atom->isNewLine())
	{
		// draw last line text
        g.setColour (Colours::black);
		g.drawSingleLineText (String(lineNumber), 4, topOffset + (int)(i.lineY + i.lineHeight));

		// draw last line breakpoint
		if (breakPointsEnabled && breakPoints.contains (lineNumber))
		{
		    g.setColour (Colours::red.withAlpha (0.5f));
			g.fillEllipse (leftIndent - 12, topIndent + (int)(i.lineY), 8, i.lineHeight - 1);
		}

		// @TODO do last line execution indicator
	}
};

void SyntaxTextEditor::paint (Graphics& g)
{
    g.fillAll (backgroundColour);
}

void SyntaxTextEditor::paintOverChildren (Graphics& g)
{
    if (isEnabled())
    {
		int width = getWidth();
		int height = getHeight();

        if (hasKeyboardFocus (true) && ! isReadOnly())
        {
            const int border = 1;

            g.setColour (Colour (0xffccccff));
            g.drawRect (0, 0, width, height, border);

            g.setOpacity (1.0f);
            const Colour shadowColour (getShadowColour().withMultipliedAlpha (0.75f));
            g.drawBevel (0, 0, width, height + 2, border + 2, shadowColour, shadowColour);
        }
        else
        {
            g.setColour (getOutlineColour());
            g.drawRect (0, 0, width, height);

            g.setOpacity (1.0f);
            const Colour shadowColour (getShadowColour());
            g.drawBevel (0, 0, width, height + 2, 3, shadowColour, shadowColour);
        }
    }
}

//==============================================================================
void SyntaxTextEditor::mouseDown (const MouseEvent& e)
{
    newTransaction();

    if (wasFocused || ! selectAllTextWhenFocused)
    {
        if (! (popupMenuEnabled && e.mods.isPopupMenu()))
        {
			if (!debugMode)
	            moveCursorTo (getTextIndexAt (e.x, e.y),
	                          e.mods.isShiftDown());

			if (e.x < leftIndent)
			{
				toggleBreakPointAt (e.x, e.y);
			}
        }
        else
        {
			if (debugMode)
				return;

            const bool writable = ! isReadOnly();

            PopupMenu m;
            m.addItem (1, TRANS("cut"), writable);
            m.addItem (2, TRANS("copy"), selectionStart < selectionEnd);
            m.addItem (3, TRANS("paste"), writable);
            m.addItem (4, TRANS("delete"), writable);
            m.addSeparator();
            m.addItem (5, TRANS("select all"));
            m.addSeparator();
            m.addItem (6, TRANS("undo"), undoManager.canUndo());
            m.addItem (7, TRANS("redo"), undoManager.canRedo());

			if (areBreakPointsEnabled())
			{
				m.addSeparator();
	            m.addItem (8, TRANS("clear breakpoints"), breakPoints.size()>0);
			}

            menuVisible = true;

            switch (m.show())
            {
            case 1:
                copy();
                cut();
                break;

            case 2:
                copy();
                break;

            case 3:
                paste();
                break;

            case 4:
                cut();
                break;

            case 5:
                moveCursorTo (getTotalNumChars(), false);
                moveCursorTo (0, true);
                break;

            case 6:
                doUndoRedo (false);
                break;

            case 7:
                doUndoRedo (true);
                break;

			case 8:
				clearBreakPoints ();
				break;
            }

            menuVisible = false;
        }
    }
}

void SyntaxTextEditor::mouseDrag (const MouseEvent& e)
{
	if (debugMode)
		return;

    if (wasFocused || ! selectAllTextWhenFocused)
    {
        if (! (popupMenuEnabled && e.mods.isPopupMenu()))
        {
           moveCursorTo (getTextIndexAt (e.x, e.y), true);
        }
    }
}

void SyntaxTextEditor::mouseMove (const MouseEvent& e)
{
    if (! (popupMenuEnabled && e.mods.isPopupMenu()))
    {
		if (e.x <= leftIndent && getMouseCursor () != MouseCursor::PointingHandCursor)
		{
			setMouseCursor (MouseCursor::PointingHandCursor);
		}
		else if (e.x > leftIndent && getMouseCursor () != MouseCursor::IBeamCursor)
		{
			setMouseCursor (MouseCursor::IBeamCursor);
		}
    }
}

void SyntaxTextEditor::mouseUp (const MouseEvent& e)
{
	if (debugMode)
		return;

	newTransaction();
    textHolder->startTimer (flashSpeedIntervalMs);

    if (wasFocused || ! selectAllTextWhenFocused)
    {
        if (! (popupMenuEnabled && e.mods.isPopupMenu()))
        {
            moveCaret (getTextIndexAt (e.x, e.y));
        }
    }

    wasFocused = true;
}

void SyntaxTextEditor::mouseDoubleClick (const MouseEvent& e)
{
    int tokenEnd = getTextIndexAt (e.x, e.y);
    int tokenStart = tokenEnd;

    if (e.getNumberOfClicks() > 3)
    {
        tokenStart = 0;
        tokenEnd = getTotalNumChars();
    }
    else
    {
        const String t (getText());
        const int totalLength = getTotalNumChars();

        while (tokenEnd < totalLength)
        {
            if (CharacterFunctions::isLetterOrDigit (t [tokenEnd]))
                ++tokenEnd;
            else
                break;
        }

        tokenStart = tokenEnd;

        while (tokenStart > 0)
        {
            if (CharacterFunctions::isLetterOrDigit (t [tokenStart - 1]))
                --tokenStart;
            else
                break;
        }

        if (e.getNumberOfClicks() > 2)
        {
            while (tokenEnd < totalLength)
            {
                if (t [tokenEnd] != T('\r') && t [tokenEnd] != T('\n'))
                    ++tokenEnd;
                else
                    break;
            }

            while (tokenStart > 0)
            {
                if (t [tokenStart - 1] != T('\r') && t [tokenStart - 1] != T('\n'))
                    --tokenStart;
                else
                    break;
            }
        }
    }

    moveCursorTo (tokenEnd, false);
    moveCursorTo (tokenStart, true);
}

void SyntaxTextEditor::mouseWheelMove (const MouseEvent& e, float ix, float iy)
{
    if (! viewport->useMouseWheelMoveIfNeeded (e, ix, iy))
        Component::mouseWheelMove (e, ix, iy);
}

//==============================================================================
bool SyntaxTextEditor::keyPressed (const KeyPress& key)
{
    const bool moveInWholeWordSteps = key.getModifiers().isCtrlDown() || key.getModifiers().isAltDown();

    if (key.isKeyCode (KeyPress::leftKey)
         || key.isKeyCode (KeyPress::upKey))
    {
        newTransaction();

        if (key.isKeyCode (KeyPress::upKey))
        {
            moveCursorTo (indexAtPosition (cursorX, cursorY - 1),
                          key.getModifiers().isShiftDown());
        }
        else if (moveInWholeWordSteps)
        {
            moveCursorTo (findWordBreakBefore (getCaretPosition()),
                          key.getModifiers().isShiftDown());
        }
        else
        {
            moveCursorTo (getCaretPosition() - 1, key.getModifiers().isShiftDown());
        }
    }
    else if (key.isKeyCode (KeyPress::rightKey)
              || key.isKeyCode (KeyPress::downKey))
    {
        newTransaction();

        if (key.isKeyCode (KeyPress::downKey))
        {
            moveCursorTo (indexAtPosition (cursorX, cursorY + cursorHeight + 1),
                          key.getModifiers().isShiftDown());
        }
        else if (moveInWholeWordSteps)
        {
            moveCursorTo (findWordBreakAfter (getCaretPosition()),
                          key.getModifiers().isShiftDown());
        }
        else
        {
            moveCursorTo (getCaretPosition() + 1, key.getModifiers().isShiftDown());
        }
    }
    else if (key.isKeyCode (KeyPress::pageDownKey))
    {
        newTransaction();

        moveCursorTo (indexAtPosition (cursorX, cursorY + cursorHeight + viewport->getViewHeight()),
                      key.getModifiers().isShiftDown());
    }
    else if (key.isKeyCode (KeyPress::pageUpKey))
    {
        newTransaction();

        moveCursorTo (indexAtPosition (cursorX, cursorY - viewport->getViewHeight()),
                      key.getModifiers().isShiftDown());
    }
    else if (key.isKeyCode (KeyPress::homeKey))
    {
        newTransaction();

        if (! moveInWholeWordSteps)
            moveCursorTo (indexAtPosition (0.0f, cursorY),
                          key.getModifiers().isShiftDown());
        else
            moveCursorTo (0, key.getModifiers().isShiftDown());
    }
    else if (key.isKeyCode (KeyPress::endKey))
    {
        newTransaction();

        if (! moveInWholeWordSteps)
            moveCursorTo (indexAtPosition ((float) textHolder->getWidth(), cursorY),
                          key.getModifiers().isShiftDown());
        else
            moveCursorTo (getTotalNumChars(), key.getModifiers().isShiftDown());
    }
    else if (key.isKeyCode (KeyPress::backspaceKey))
    {
        if (moveInWholeWordSteps)
        {
            moveCursorTo (findWordBreakBefore (getCaretPosition()), true);
        }
        else
        {
            if (selectionStart == selectionEnd && selectionStart > 0)
                --selectionStart;
        }

        cut();
    }
    else if (key.isKeyCode (KeyPress::deleteKey))
    {
        if (key.getModifiers().isShiftDown())
            copy();

        if (selectionStart == selectionEnd
             && selectionEnd < getTotalNumChars())
        {
            ++selectionEnd;
        }

        cut();
    }
    else if (key.getModifiers().isCommandDown())
    {
        newTransaction();
        const int keyChar = CharacterFunctions::toLowerCase ((tchar) key.getKeyCode());

        if (keyChar == T('c'))
        {
            copy();
        }
        else if (keyChar == T('x'))
        {
            copy();
            cut();
        }
        else if (keyChar == T('v'))
        {
            paste();
        }
/* @XXX - keep this off since it will be triggered from main application
        else if (keyChar == T('z'))
        {
            doUndoRedo (false);
        }
        else if (keyChar == T('y'))
        {
            doUndoRedo (true);
        }
*/
        else if (keyChar == T('a'))
        {
            moveCursorTo (getTotalNumChars(), false);
            moveCursorTo (0, true);
        }
        else
        {
            return Component::keyPressed (key);
        }
    }
    else if (key.isKeyCode (KeyPress::returnKey))
    {
        if (! isReadOnly())
        {
			// updates breakpoints
			int currentLine = getCaretLineNumber ();
			for (int i = 0; i < breakPoints.size(); i++)
			{
				int currentBreak = breakPoints.getUnchecked(i);
				if (currentBreak >= currentLine)
				{
					breakPoints.set (i, currentBreak + 1);
				}
			}

            newTransaction();
            insertTextAtCursor (T("\n"));
        }
    }
	else if (key.isKeyCode (KeyPress::tabKey))
    {
       if (! isReadOnly())
       {
            newTransaction();
			insertTextAtCursor (T("\t"));
       }
	   else
		    return Component::keyPressed (key);
	}
    else if (key.isKeyCode (KeyPress::escapeKey))
    {
        newTransaction();
        moveCursorTo (getCaretPosition(), false);
        escapePressed();
    }
    else if ((key.getKeyCode() < 0xff)
              && ! (isReadOnly()
                     || key.isKeyCode (KeyPress::tabKey)
#ifdef JUCE_MAC
                     ))
#else
                     || key.getModifiers().isAltDown()))
#endif
    {
        if (! isReadOnly())
            insertTextAtCursor (String::charToString ((tchar) key.getKeyCode()));

        lastTransactionTime = Time::getApproximateMillisecondCounter();
    }
/*
	else if (key.isKeyCode (KeyPress::F1Key))
	{
		float x, y, lineHeight;
		getCharPosition (getCaretPosition(), x, y, lineHeight);

		suggestBox->setTopLeftPosition(
								getScreenX() + (int)x + leftIndent,
								getScreenY() + (int)y + (int)currentFont.getHeight() + 4);

		suggestBox->setSize (150,200);

		suggestBox->open();
	}
*/
    else
    {
        return Component::keyPressed (key);
    }
    
    return true;
}

bool SyntaxTextEditor::keyStateChanged()
{
    // (overridden to avoid forwarding key events to the parent)
    return false;
}

void SyntaxTextEditor::actionListenerCallback (const String& message)
{
/*    // (code fold popup selector) !

	insertTextAtCursor (codeFoldCombo->getText());

	codeFoldCombo->clear ();
	codeFoldCombo->setVisible (false);
*/
}

//==============================================================================
void SyntaxTextEditor::focusGained (FocusChangeType)
{
    newTransaction();

    caretFlashState = true;

    if (selectAllTextWhenFocused)
    {
        moveCursorTo (0, false);
        moveCursorTo (getTotalNumChars(), true);
    }

    repaint();

    if (caretVisible)
        textHolder->startTimer (flashSpeedIntervalMs);
}

void SyntaxTextEditor::focusLost (FocusChangeType)
{
    newTransaction();

    wasFocused = false;
    textHolder->stopTimer();
    caretFlashState = false;

    postCommandMessage (focusLossMessageId);
    repaint();
}

//==============================================================================
void SyntaxTextEditor::resized()
{
    viewport->setBoundsInset (borderSize);
    viewport->setSingleStepSizes (16, roundFloatToInt (currentFont.getHeight()));

    updateTextHolderSize();

    cursorHeight = currentFont.getHeight(); // (in case the text is empty and the call below doesn't set this value)

    getCharPosition (caretPosition,
                     cursorX, cursorY,
                     cursorHeight);
}

//==============================================================================
void SyntaxTextEditor::handleCommandMessage (int commandId)
{
    for (int i = listeners.size(); --i >= 0;)
    {
        SyntaxTextEditorListener* const tl = (SyntaxTextEditorListener*) listeners[i];

        if (tl != 0)
        {
            if (commandId == textChangeMessageId)
            {
                tl->textEditorTextChanged (*this);
            }
            else if (commandId == returnKeyMessageId)
            {
                tl->textEditorReturnKeyPressed (*this);
            }
            else if (commandId == escapeKeyMessageId)
            {
                tl->textEditorEscapeKeyPressed (*this);
            }
            else if (commandId == focusLossMessageId)
            {
                tl->textEditorFocusLost (*this);
            }
			else if (commandId == changeBreakPointMessageId)
			{
	            tl->textEditorChangeBreakPoints (*this);
		    }

            if (i > 0 && ! isValidComponent())
                break;
        }
    }
}

void SyntaxTextEditor::enablementChanged()
{
    setMouseCursor (MouseCursor (isReadOnly() ? MouseCursor::NormalCursor
                                              : MouseCursor::IBeamCursor));
    repaint();
}

//==============================================================================
void SyntaxTextEditor::clearInternal (UndoManager* const um)
{
    remove (0, getTotalNumChars(), um, caretPosition);
}

void SyntaxTextEditor::insert (const String& text,
                         const int insertIndex,
                         const Colour& colour,
                         UndoManager* const um,
                         const int caretPositionToMoveTo)
{
    if (text.isNotEmpty())
    {
        if (um != 0)
        {
            um->perform (new SyntaxTextEditorInsertAction (*this,
                                                     text,
                                                     insertIndex,
                                                     colour,
                                                     caretPosition,
                                                     caretPositionToMoveTo));
        }
        else
        {
			document.insert (text, insertIndex);

			totalNumChars = -1;

			moveCursorTo (caretPositionToMoveTo, false);
            repaintText (0, -1);
        }
    }
}

void SyntaxTextEditor::remove (int startIndex,
                         int endIndex,
                         UndoManager* const um,
                         const int caretPositionToMoveTo)
{
//	int sectionIndex = 0;

    if (endIndex > startIndex)
    {
//        int index = 0;

        if (um != 0)
        {
            um->perform (new SyntaxTextEditorRemoveAction (*this,
													 document.getTextSubstring (startIndex, endIndex),
                                                     startIndex,
                                                     endIndex,
                                                     caretPosition,
                                                     caretPositionToMoveTo));
        }
        else
        {
			int currentLine = getCaretLineNumber();
			int newLinesRemoved = document.remove (startIndex, endIndex);

			// updates breakpoints
			for (int i = 0; i < breakPoints.size(); i++)
			{
				int currentBreak = breakPoints.getUnchecked(i);
				if (currentBreak >= currentLine)
				{
					breakPoints.set (i, currentBreak - newLinesRemoved);
				}
			}

			totalNumChars = -1;

            moveCursorTo (caretPositionToMoveTo, false);
            repaintText (0, -1);
        }
    }
}

//==============================================================================
const String SyntaxTextEditor::getText() const
{
	return document.getAllText();
}

const String SyntaxTextEditor::getTextSubstring (const int startCharacter, const int endCharacter) const
{
	return document.getTextSubstring (startCharacter, endCharacter);
}

int SyntaxTextEditor::getTotalNumChars()
{
    if (totalNumChars < 0)
    {
		totalNumChars = document.getTotalLength();
    }

    return totalNumChars;
}

bool SyntaxTextEditor::isEmpty() const
{
    if (totalNumChars != 0)
    {
		if (document.getTotalLength() > 0)
			return false;
    }

    return true;
}

void SyntaxTextEditor::getCharPosition (const int index, float& cx, float& cy, float& lineHeight)
{
	SyntaxDocumentIterator i (&document);

    while (i.next())
    {
        cy = i.lineY;

        if (i.indexInText + i.atom->numChars > index)
        {
            cx = i.indexToX (index);
            lineHeight = i.lineHeight;
            return;
        }
    }

    cx = i.atomX;
    cy = i.lineY;

    lineHeight = currentFont.getHeight();
}

int SyntaxTextEditor::indexAtPosition (const float x, const float y)
{
	SyntaxDocumentIterator i (&document);

    while (i.next())
    {
        if (i.lineY + i.lineHeight > y)
        {
            if (i.lineY > y)
                return jmax (0, i.indexInText - 1);

            if (i.atomX >= x)
                return i.indexInText;

            if (x < i.atomRight)
                return i.xToIndex (x);
        }
    }

    return getTotalNumChars();
}

//==============================================================================
static int getCharacterCategory (const tchar character) throw()
{
    return CharacterFunctions::isLetterOrDigit (character) ?
				2 : (CharacterFunctions::isWhitespace (character) ? 0 : 1);
}

int SyntaxTextEditor::findWordBreakAfter (int position) const
{
    const String t (getTextSubstring (position, position + 512));
    const int totalLength = t.length();
    int i = 0;

    while (i < totalLength)
    {
        if (CharacterFunctions::isWhitespace (t [i]))
            ++position;
        else
            break;

        ++i;
    }

    const int type = getCharacterCategory (t [i]);

    while (i < totalLength)
    {
        if (type == getCharacterCategory (t [i]))
            ++position;
        else
            break;

        ++i;
    }

    return position;
}

int SyntaxTextEditor::findWordBreakBefore (int position) const
{
    if (position > 0)
    {
        const int maximumToDo = jmin (512, position);
        const int startOfBuffer = position - maximumToDo;
        const String t (getTextSubstring (startOfBuffer, position));

        while (position > startOfBuffer)
        {
            if (CharacterFunctions::isWhitespace (t [position - 1 - startOfBuffer]))
                --position;
            else
                break;
        }

        const int type = getCharacterCategory (t [position - 1 - startOfBuffer]);

        while (position > startOfBuffer)
        {
            if (type == getCharacterCategory (t [position - 1 - startOfBuffer]))
                --position;
            else
                break;
        }
    }

    return jmax (position, 0);
}

//==============================================================================
bool SyntaxTextEditor::areBreakPointsEnabled () const
{
	return breakPointsEnabled;
}

void SyntaxTextEditor::setBreakPointsEnabled (const bool enable)
{
	breakPointsEnabled = enable;
}

bool SyntaxTextEditor::isBreakPointToggledAtCurrentLine ()
{
	return breakPoints.contains (getCaretLineNumber ());
}

void SyntaxTextEditor::toggleBreakPointAt (const int x, const int y)
{
	toggleBreakPointAtLine (getTextLineAt (x, y));
}

void SyntaxTextEditor::toggleBreakPointAtLine (const int lineNumber)
{
	if (breakPoints.contains (lineNumber))
	{
		breakPoints.removeValue (lineNumber);
	}
	else
	{
		IntegerElementComparator<int> comparator;
		breakPoints.addSorted (comparator, lineNumber);
	}

	// @TODO - use textholder visible height
	repaint (0,0,leftIndent, textHolder->getHeight());

	postCommandMessage (changeBreakPointMessageId);
}

Array<int>& SyntaxTextEditor::getBreakPointsArray ()
{
	return breakPoints;
}

int SyntaxTextEditor::getNumBreakPoints () const
{
	return breakPoints.size ();
}

void SyntaxTextEditor::clearBreakPoints ()
{
	breakPoints.clear ();

	repaint (0,0,leftIndent, textHolder->getHeight());
}

void SyntaxTextEditor::setSyntaxLexer (SyntaxLexer* lexer)
{
	document.setLexer (lexer);
    repaintText (0, -1);
}

SyntaxLexer* SyntaxTextEditor::getSyntaxLexer ()
{
	return document.getLexer();
}

//==============================================================================
void SyntaxTextEditor::setCurrentExecutedLine (const int lineNumber)
{
	linePosition = lineNumber;

	repaint (0,0,leftIndent,getHeight());
}

void SyntaxTextEditor::setDebugMode (const bool shouldDoDebug)
{
	debugMode = shouldDoDebug;
}


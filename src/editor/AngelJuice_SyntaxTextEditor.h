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

#ifndef __ANGELJUICE_SYNTAXTEXTEDITOR_HEADER__
#define __ANGELJUICE_SYNTAXTEXTEDITOR_HEADER__

#include "AngelJuice_SyntaxLexer.h"
#include "AngelJuice_SyntaxDocument.h"


class SyntaxTextEditor;
class SyntaxTextHolderComponent;



//==============================================================================
/*
class SuggestFunctionListBox : public SimpleListBox
{
public:

	SuggestFunctionListBox (SimpleListBoxModel* model) :
		SimpleListBox (T("suggest"), model)
	{
//		setOpaque (true);
	}

	void focusLost (Component::FocusChangeType cause)
	{
		close();
	}

	void open ()
	{
		addToDesktop (ComponentPeer::windowHasDropShadow);

		setVisible (true);
		toFront (true);
		grabKeyboardFocus ();
	}

	void close ()
	{
		if (isOnDesktop ())
			removeFromDesktop ();
		setVisible (false);
	}
};

*/


//==============================================================================
/**
    Receives callbacks from a SyntaxTextEditor component when it changes.

    @see SyntaxTextEditor::addListener
*/
class JUCE_API  SyntaxTextEditorListener
{
public:
    /** Destructor. */
    virtual ~SyntaxTextEditorListener()  {}

    /** Called when the user changes the text in some way. */
    virtual void textEditorTextChanged (SyntaxTextEditor& editor) = 0;

    /** Called when the user presses the return key. */
    virtual void textEditorReturnKeyPressed (SyntaxTextEditor& editor) = 0;

    /** Called when the user presses the escape key. */
    virtual void textEditorEscapeKeyPressed (SyntaxTextEditor& editor) = 0;

    /** Called when the text editor loses focus. */
    virtual void textEditorFocusLost (SyntaxTextEditor& editor) = 0;

    /** Called when the text editor changes breakpoints. */
    virtual void textEditorChangeBreakPoints (SyntaxTextEditor& editor) = 0;
	// @TODO - callback on this
};


//==============================================================================
/**
    A component containing text that can be edited.

    A SyntaxTextEditor can either be in single- or multi-line mode, and supports mixed
    fonts and colours.

    @see SyntaxTextEditorListener, Label
*/
class SyntaxTextEditor  : public Component,
                          public SettableTooltipClient,
						  public ActionListener
{
public:
    //==============================================================================
    /** Creates a new, empty text editor.

        @param componentName        the name to pass to the component for it to use as its name
        @param passwordCharacter    if this is not zero, this character will be used as a replacement
                                    for all characters that are drawn on screen - e.g. to create
                                    a password-style textbox, you could set this to T('*')
    */
    SyntaxTextEditor (const String& componentName = String::empty);

    /** Destructor. */
    virtual ~SyntaxTextEditor();


    //==============================================================================
    /** Changes the editor to read-only mode.

        By default, the text editor is not read-only. If you're making it read-only, you
        might also want to call setCaretVisible (false) to get rid of the caret.

        The text can still be highlighted and copied when in read-only mode.

        @see isReadOnly, setCaretVisible
    */
    void setReadOnly (const bool shouldBeReadOnly);

    /** Returns true if the editor is in read-only mode.
    */
    bool isReadOnly() const;

    /** Makes the caret visible or invisible.

        By default the caret is visible.

        @see setCaretColour, setCaretPosition
    */
    void setCaretVisible (bool shouldBeVisible);

    /** Changes the colour of the caret.

        By default it will be black, so you might need to change it if you're working with
        wacky colours.

        @see setCaretVisible, setCaretPosition
    */
    void setCaretColour (const Colour& colour);

    /** Allows a right-click menu to appear for the editor.

        (This defaults to being enabled).

        If enabled, right-clicking (or command-clicking on the Mac) will pop up a menu
        of options such as cut/copy/paste, undo/redo, etc.
    */
    void setPopupMenuEnabled (const bool menuEnabled);

    /** Sets the colours for the editor.

        @param currentTextColour    the colour that will be used when text is added to the editor. Note
                                    that because the editor can contain multiple colours, calling this
                                    method won't change the colour of existing text - to do that, call
                                    applyFontToAllText() after calling this method.
        @param backgroundColour     the colour to use for the text component's background - this can be
                                    transparent if necessary
        @param highlightColour      the colour with which to highlight sections of the text - this can
                                    be transparent if you don't want to show any highlighting.
        @param outlineColour        if this is non-transparent, it will be used to draw a box around
                                    the edge of the component
        @param dropShadowColour     If this is non-transparent, it'll be used to draw an inner shadow
                                    around the edge of the editor
    */
    void setColours (const Colour& currentTextColour,
                     const Colour& backgroundColour = Colours::white,
                     const Colour& highlightColour = Colour (0x401111ee),
                     const Colour& outlineColour = Colours::transparentBlack,
                     const Colour& dropShadowColour = Colours::black.withAlpha (0.22f));

    /** Returns the text colour, as set by setColours(). */
    const Colour& getTextColour() const throw()                     { return textColour; }

    /** Returns the background colour, as set by setColours(). */
    const Colour& getBackgroundColour() const throw()               { return backgroundColour; }

    /** Returns the highlight colour, as set by setColours(). */
    const Colour& getHighlightColour() const throw()                { return highlightColour; }

    /** Returns the outline colour, as set by setColours(). */
    const Colour& getOutlineColour() const throw()                  { return outlineColour; }

    /** Returns the shadow colour, as set by setColours(). */
    const Colour& getShadowColour() const throw()                   { return shadowColour; }

    //==============================================================================
    /** Sets the font to use for newly added text.

        This will change the font that will be used next time any text is added or entered
        into the editor. It won't change the font of any existing text - to do that, use
        applyFontToAllText() instead.

        @see applyFontToAllText
    */
    void setFont (const Font& newFont);

    /** Returns the font that's currently being used for new text.

        @see setFont
    */
    const Font getFont() const;

    //==============================================================================
    /** If set to true, focusing on the editor will highlight all its text.

        (Set to false by default).

        This is useful for boxes where you expect the user to re-enter all the
        text when they focus on the component, rather than editing what's already there.
    */
    void setSelectAllWhenFocused (bool b);

    //==============================================================================
    /** Changes the size of the scrollbars that are used.

        Handy if you need smaller scrollbars for a small text box.
    */
    void setScrollBarThickness (const int newThicknessPixels);

    /** Shows or hides the buttons on any scrollbars that are used.

        @see ScrollBar::setButtonVisibility
    */
    void setScrollBarButtonVisibility (const bool buttonsVisible);

    //==============================================================================
    /** Registers a listener to be told when things happen to the text.

        @see removeListener
    */
    void addListener (SyntaxTextEditorListener* const newListener);

    /** Deregisters a listener.

        @see addListener
    */
    void removeListener (SyntaxTextEditorListener* const listenerToRemove);

    //==============================================================================
    /** Returns the entire contents of the editor. */
    const String getText() const;

    /** Returns a section of the contents of the editor. */
    const String getTextSubstring (const int startCharacter, const int endCharacter) const;

    /** Returns true if there are no characters in the editor.

        This is more efficient than calling getText().isEmpty().
    */
    bool isEmpty() const;

    /** Sets the entire content of the editor.

        This will clear the editor and insert the given text (using the current colour
        and font).

        @param newText                  the text to add
        @param sendTextChangeMessage    if true, this will cause a change message to
                                        be sent to all the listeners.
        @see insertText
    */
    void setText (const String& newText,
                  const bool sendTextChangeMessage = true);

    /** Inserts some text at the current cursor position.

        If a section of the text is highlighted, it will be replaced by
        this string, otherwise it will be inserted.

        To delete a section of text, you can use setHighlightedRegion() to
        highlight it, and call insertTextAtCursor (String::empty).

        @see setCaretPosition, getCaretPosition, setHighlightedRegion
    */
    void insertTextAtCursor (String textToInsert);

    /** Deletes all the text from the editor. */
    void clear();

    /** Deletes the currently selected region, and puts it on the clipboard.

        @see copy, paste, SystemClipboard
    */
    void cut();

    /** Copies any currently selected region to the clipboard.

        @see cut, paste, SystemClipboard
    */
    void copy();

    /** Pastes the contents of the clipboard into the editor at the cursor position.

        @see cut, copy, SystemClipboard
    */
    void paste();

    /** Undo or Redo last action

        @see newTransaction
    */
	void doUndoRedo (const bool isRedo);

    //==============================================================================
    /** Moves the caret to be in front of a given character.

        @see getCaretPosition
    */
    void setCaretPosition (const int newIndex);

    /** Returns the current index of the caret.

        @see setCaretPosition
    */
    int getCaretPosition() const;

    /** Returns the current line of the caret.

        @see getCaretPosition
    */
	int getCaretLineNumber() const;

    /** Selects a section of the text.
    */
    void setHighlightedRegion (int startIndex,
                               int numberOfCharactersToHighlight);

    /** Finds the index of the character at a given position.

        The co-ordinates are relative to the component's top-left.
    */
    int getTextIndexAt (const int x, const int y);

    /** Finds the line number at a given position.

        The co-ordinates are relative to the component's top-left.
		The line number starts from 1 (and not 0 as you could imagine).
    */
	int getTextLineAt (const int x, const int y);

    /** Finds the start and end index position of a specified line

		The line number starts from 1 (and not 0 as you could imagine).
    */
	void getTextPositionOfLine (const int lineNumber,
                                int& startIndex,
                                int& numberOfCharactersInTheLine);

    /** Returns the total width of the text, as it is currently laid-out.

        This may be larger than the size of the SyntaxTextEditor, and can change when
        the SyntaxTextEditor is resized or the text changes.
    */
    int getTextWidth() const;

    /** Returns the maximum height of the text, as it is currently laid-out.

        This may be larger than the size of the SyntaxTextEditor, and can change when
        the SyntaxTextEditor is resized or the text changes.
    */
    int getTextHeight() const;

    /** Changes the size of the gap at the top and left-edge of the editor.

        By default there's a gap of 4 pixels.
    */
    void setIndents (const int newLeftIndent, const int newTopIndent);

    /** Changes the size of border left around the edge of the component.

        @see getBorder
    */
    void setBorder (const BorderSize& border);

    /** Returns the size of border around the edge of the component.

        @see setBorder
    */
    const BorderSize getBorder() const throw();

    /** Used to disable the auto-scrolling which keeps the cursor visible.

        If true (the default), the editor will scroll when the cursor moves offscreen. If
        set to false, it won't.
    */
    void setScrollToShowCursor (const bool shouldScrollToShowCursor) throw();

    //==============================================================================
	/** Get if the breakpoint set is enabled

        @see areBreakPointsEnabled
    */
	void setSyntaxLexer (SyntaxLexer* lexer);

	SyntaxLexer* getSyntaxLexer ();

	//==============================================================================
	/** Get if the breakpoint set is enabled

        @see areBreakPointsEnabled
    */
	bool areBreakPointsEnabled () const;

	/** Used to enable or disable breakpoints

        @see areBreakPointsEnabled
    */
	void setBreakPointsEnabled (const bool breakPointsEnabled);
	
	/** ???
	*/
	bool isBreakPointToggledAtCurrentLine ();

	/** Set a breakpoint on the line at a given position.

        If the breakpoint is already there it will be removed,
		otherwise it will be added
    */
	void toggleBreakPointAt (const int x, const int y);

    /** Set a breakpoint on a specified line

        If the breakpoint is already there it will be removed,
		otherwise it will be added
    */
	void toggleBreakPointAtLine (const int lineNumber);

    /** Returns the array of the current set breakpoints

        @see areBreakPointsEnabled
    */
	Array<int>& getBreakPointsArray ();

    /** Returns the number of the current set breakpoints

        @see areBreakPointsEnabled
    */
	int getNumBreakPoints () const;

    /** Clean all the breakpoints that have been set

        @see toggleBreakPointAtLine, toggleBreakPointAt
    */
	void clearBreakPoints ();

	//==============================================================================
	/** Set the current highlighted line
    */
	void setCurrentExecutedLine (const int lineNumber);

	/** Set if we run in debug mode
    */
	void setDebugMode (const bool shouldDoDebug);


    //==============================================================================
    /** Used by an internal ComboBox to keep track of code folding
    */
	void actionListenerCallback (const String& message);


    //==============================================================================
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void paintOverChildren (Graphics& g);
    /** @internal */
    void mouseDown (const MouseEvent& e);
    /** @internal */
    void mouseUp (const MouseEvent& e);
    /** @internal */
    void mouseDrag (const MouseEvent& e);
    /** @internal */
    void mouseDoubleClick (const MouseEvent& e);
    /** @internal */
    void mouseWheelMove (const MouseEvent& e, float ix, float iy);
    /** @internal */
    void mouseMove (const MouseEvent& e);
    /** @internal */
    bool keyPressed (const KeyPress& key);
    /** @internal */
    bool keyStateChanged();
    /** @internal */
    void focusGained (FocusChangeType cause);
    /** @internal */
    void focusLost (FocusChangeType cause);
    /** @internal */
    void resized();
    /** @internal */
    void enablementChanged();

	//==============================================================================
    /** @internal */
	int getNumRows();
    /** @internal */
	void paintListBoxItem (int rowNumber,
                           Graphics& g,
                           int width, int height,
                           bool rowIsSelected);
    /** @internal */
	void selectedRowsChanged (int row);
    /** @internal */
	void listBoxItemClicked (int row, const MouseEvent& e);
    /** @internal */
	void deleteKeyPressed (int row);
    /** @internal */
	void returnKeyPressed (int row);


    juce_UseDebuggingNewOperator

protected:
    void scrollToMakeSureCursorIsVisible();
    void moveCaret (int newCaretPos);
    void moveCursorTo (const int newPosition, const bool isSelecting);
    void textChanged();
    void handleCommandMessage (int commandId);

    virtual void returnPressed();
    virtual void escapePressed();

private:
    Viewport* viewport;
    SyntaxTextHolderComponent* textHolder;
	BorderSize borderSize;

    bool readOnly                   : 1;
    bool caretVisible               : 1;
    bool popupMenuEnabled           : 1;
    bool selectAllTextWhenFocused   : 1;
    bool menuVisible                : 1;
    bool wasFocused                 : 1;
    bool caretFlashState            : 1;
    bool keepCursorOnScreen         : 1;
	bool breakPointsEnabled         : 1;
	bool debugMode                  : 1;

    UndoManager undoManager;
    float cursorX, cursorY, cursorHeight;
    int selectionStart, selectionEnd;
    int leftIndent, topIndent;
    unsigned int lastTransactionTime;
    int totalNumChars, caretPosition, linePosition;
	tchar lastInsertChar;

    Font currentFont;
	Colour backgroundColour,
			textColour,
			highlightColour,
			caretColour,
			outlineColour,
			shadowColour;

//	SuggestFunctionListBox* suggestBox;
	StringArray functions;
	SyntaxDocument document;
	Array<int> breakPoints;

	enum
    {
        notDragging,
        draggingSelectionStart,
        draggingSelectionEnd
    } dragType;

    VoidArray listeners;

    friend class SyntaxTextEditorInsertAction;
    friend class SyntaxTextEditorRemoveAction;

	void updateSyntaxSections ();
	void updateSyntaxSections (const int startIndex, const int numAtoms);
	void processText (String& allText);

    void clearInternal (UndoManager* const um);

    void insert (const String& text,
                 const int insertIndex,
                 const Colour& colour,
                 UndoManager* const um,
                 const int caretPositionToMoveTo);

    void remove (int startIndex,
                 int endIndex,
                 UndoManager* const um,
                 const int caretPositionToMoveTo);

    int getTotalNumChars();

    void getCharPosition (const int index,
                          float& x, float& y,
                          float& lineHeight);

    int indexAtPosition (const float x,
                         const float y);

    int findWordBreakAfter (int position) const;
    int findWordBreakBefore (int position) const;

    void newTransaction();

    friend class SyntaxTextHolderComponent;
    friend class SyntaxTextEditorViewport;

	void drawContent (Graphics& g);
	void drawLineNumbers (Graphics& g);

    void updateTextHolderSize();
    void timerCallbackInt();
    void repaintCaret();
    void repaintText (int textStartIndex, int textEndIndex);

    SyntaxTextEditor (const SyntaxTextEditor&);
    const SyntaxTextEditor& operator= (const SyntaxTextEditor&);
};



#endif   // __EJUCE_SYNTAXTEXTEDITOR__

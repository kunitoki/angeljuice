/*
  ==============================================================================

   This file is part of AngelJuice

   which is based on kRAkEn/gORe eJUCE library
   which uses
               Raw Material Software ltd. JUCE library
               AngelCode AngelScript scripting library

   AngelJuice can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   AngelJuice is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eJUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

   @coder	Asnaghi Lucio a.k.a. kRAkEn/gORe

  ==============================================================================
*/

#include "AngelJuice_AngelicLookAndFeel.h"


//==============================================================================
static const Colour createBaseColour (const Colour& buttonColour,
                                      const bool hasKeyboardFocus,
                                      const bool isMouseOverButton,
                                      const bool isButtonDown)
{
    float sat = hasKeyboardFocus ? 1.3f : 0.9f;

    Colour baseColour (buttonColour.withMultipliedSaturation (sat));

    if (isButtonDown)
        return baseColour.contrasting (0.2f);
    else if (isMouseOverButton)
        return baseColour.contrasting (0.1f);

    return baseColour;
}


//==============================================================================
AngelicLookAndFeel::AngelicLookAndFeel()
{
    /*
    setColour (ComboBox::buttonColourId,            Colour (0xffccccff));
    setColour (ComboBox::outlineColourId,           Colours::grey.withAlpha (0.7f));
    setColour (ComboBox::backgroundColourId,        Colour (0x991111aa));
    setColour (ComboBox::textColourId,              findColour (ComboBox::backgroundColourId));

    setColour (ListBox::outlineColourId,            findColour (ComboBox::outlineColourId));

//    setColour (ScrollBar::backgroundColourId,       Colours::transparentBlack);
//    setColour (ScrollBar::thumbColourId,            Colours::white);

    setColour (Slider::thumbColourId,               findColour (TextButton::buttonColourId));
    setColour (Slider::trackColourId,               Colour (0x7fffffff));
    setColour (Slider::textBoxOutlineColourId,      findColour (ComboBox::outlineColourId));

    setColour (ProgressBar::backgroundColourId,     Colours::white);
    setColour (ProgressBar::foregroundColourId,     Colour (0xffaaaaee));

    setColour (PopupMenu::backgroundColourId,             Colours::white);
    setColour (PopupMenu::highlightedTextColourId,        findColour (PopupMenu::backgroundColourId));
    setColour (PopupMenu::highlightedBackgroundColourId,  findColour (ComboBox::backgroundColourId));

    setColour (TextEditor::focusedOutlineColourId,  findColour (TextButton::buttonColourId));
    */
    
    commonShadow.setShadowProperties (1.8f, 0.5f, 0, 0);
}

AngelicLookAndFeel::~AngelicLookAndFeel()
{
}


//==============================================================================
DropShadower* AngelicLookAndFeel::createDropShadowerForComponent (Component*)
{
    return new DropShadower (0.4f, 0, 2, 6);
}

//==============================================================================
const Font AngelicLookAndFeel::getPopupMenuFont()
{
    return Font (14.0f);
}

//==============================================================================
void AngelicLookAndFeel::drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& textEditor)
{
    if (textEditor.isEnabled())
    {
        if (textEditor.hasKeyboardFocus (true) && ! textEditor.isReadOnly())
        {
            const int border = 1;

            g.setColour (textEditor.findColour (TextEditor::focusedOutlineColourId));
            g.drawRect (0, 0, width, height, border);

            g.setOpacity (1.0f);
            const Colour shadowColour (textEditor.findColour (TextEditor::shadowColourId).withMultipliedAlpha (0.75f));
            g.drawBevel (0, 0, width, height + 2, border + 2, shadowColour, shadowColour);
        }
        else
        {
            g.setColour (textEditor.findColour (TextEditor::outlineColourId));
            g.drawRect (0, 0, width, height);

            g.setOpacity (1.0f);
            const Colour shadowColour (textEditor.findColour (TextEditor::shadowColourId));
            g.drawBevel (0, 0, width, height + 2, 3, shadowColour, shadowColour);
        }
    }
}

//==============================================================================
void AngelicLookAndFeel::getComboBoxFonts (Font& itemFont,
                                           Font& popupListFont,
                                           ComboBox& box)
{
    itemFont = Font (jmin (15.0f, box.getHeight() * 0.85f));
    popupListFont = Font (15.0f);
}

//==============================================================================
void AngelicLookAndFeel::drawScrollbarButton (Graphics& g,
                                       ScrollBar& scrollbar,
                                       int width, int height,
                                       int buttonDirection,
                                       bool isScrollbarVertical,
                                       bool isMouseOverButton,
                                       bool isButtonDown)
{
    if (isScrollbarVertical)
        width -= 2;
    else
        height -= 2;

    Path p;

    if (buttonDirection == 0)
        p.addTriangle (width * 0.5f, height * 0.2f,
                       width * 0.1f, height * 0.7f,
                       width * 0.9f, height * 0.7f);
    else if (buttonDirection == 1)
        p.addTriangle (width * 0.8f, height * 0.5f,
                       width * 0.3f, height * 0.1f,
                       width * 0.3f, height * 0.9f);
    else if (buttonDirection == 2)
        p.addTriangle (width * 0.5f, height * 0.8f,
                       width * 0.1f, height * 0.3f,
                       width * 0.9f, height * 0.3f);
    else if (buttonDirection == 3)
        p.addTriangle (width * 0.2f, height * 0.5f,
                       width * 0.7f, height * 0.1f,
                       width * 0.7f, height * 0.9f);

    if (isButtonDown)
        g.setColour (scrollbar.findColour (ScrollBar::thumbColourId).contrasting (0.2f));
    else
        g.setColour (scrollbar.findColour (ScrollBar::thumbColourId));

    g.fillPath (p);

    g.setColour (Colours::black.withAlpha (0.5f));
    g.strokePath (p, PathStrokeType (0.5f));
}

void AngelicLookAndFeel::drawScrollbar (Graphics& g,
                                 ScrollBar& scrollbar,
                                 int x, int y,
                                 int width, int height,
                                 bool isScrollbarVertical,
                                 int thumbStartPosition,
                                 int thumbSize,
                                 bool isMouseOver,
                                 bool isMouseDown)
{
    g.fillAll (scrollbar.findColour (ScrollBar::backgroundColourId));

    g.setColour (scrollbar.findColour (ScrollBar::thumbColourId).withAlpha ((isMouseOver || isMouseDown) ? 0.4f : 0.15f));

    if (thumbSize > 0.0f)
    {
        Rectangle thumb;

        if (isScrollbarVertical)
        {
            width -= 2;
            g.fillRect (x + roundFloatToInt (width * 0.35f), y,
                        roundFloatToInt (width * 0.3f), height);

            thumb.setBounds (x + 1, thumbStartPosition,
                             width - 2, thumbSize);
        }
        else
        {
            height -= 2;
            g.fillRect (x, y + roundFloatToInt (height * 0.35f),
                        width, roundFloatToInt (height * 0.3f));

            thumb.setBounds (thumbStartPosition, y + 1,
                             thumbSize, height - 2);
        }

        g.setColour (scrollbar.findColour (ScrollBar::thumbColourId).withAlpha ((isMouseOver || isMouseDown) ? 0.95f : 0.7f));
        g.fillRect (thumb);

        g.setColour (Colours::black.withAlpha ((isMouseOver || isMouseDown) ? 0.4f : 0.25f));
        g.drawRect (thumb.getX(), thumb.getY(), thumb.getWidth(), thumb.getHeight());

        if (thumbSize > 16)
        {
            for (int i = 3; --i >= 0;)
            {
                const float linePos = thumbStartPosition + thumbSize / 2 + (i - 1) * 4.0f;
                g.setColour (Colours::black.withAlpha (0.15f));

                if (isScrollbarVertical)
                {
                    g.drawLine (x + width * 0.2f, linePos, width * 0.8f, linePos);
                    g.setColour (Colours::white.withAlpha (0.15f));
                    g.drawLine (width * 0.2f, linePos - 1, width * 0.8f, linePos - 1);
                }
                else
                {
                    g.drawLine (linePos, height * 0.2f, linePos, height * 0.8f);
                    g.setColour (Colours::white.withAlpha (0.15f));
                    g.drawLine (linePos - 1, height * 0.2f, linePos - 1, height * 0.8f);
                }
            }
        }
    }
}

ImageEffectFilter* AngelicLookAndFeel::getScrollbarEffect()
{
    return &commonShadow;
}

int AngelicLookAndFeel::getMinimumScrollbarThumbSize (ScrollBar& scrollbar)
{
    return jmin (scrollbar.getWidth(), scrollbar.getHeight()) * 2;
}

int AngelicLookAndFeel::getDefaultScrollbarWidth()
{
    return 14;
}

int AngelicLookAndFeel::getScrollbarButtonSize (ScrollBar& scrollbar)
{
    return 2 + ((scrollbar.isVertical()) ? scrollbar.getWidth()
                                         : scrollbar.getHeight());
}

//==============================================================================
void AngelicLookAndFeel::drawCornerResizer (Graphics& g,
                                          int w, int h,
                                          bool isMouseOver,
                                          bool isMouseDragging)
{
    const float lineThickness = jmin (w, h) * 0.05f;

	g.setColour (Colours::darkgrey);
	g.drawLine ( w - h, h, w, h - w, lineThickness);
}

//==============================================================================
void AngelicLookAndFeel::drawTableHeaderColumn (Graphics& g, const String& columnName, int columnId,
                                            int width, int height,
                                         bool isMouseOver, bool isMouseDown,
                                         int columnFlags)
{
    if (isMouseDown)
        g.fillAll (Colour (0x8899aadd));
    else if (isMouseOver)
        g.fillAll (Colour (0x5599aadd));

    int rightOfText = width - 4;

    if ((columnFlags & (TableHeaderComponent::sortedForwards | TableHeaderComponent::sortedBackwards)) != 0)
    {
        const float top = height * ((columnFlags & TableHeaderComponent::sortedForwards) != 0 ? 0.35f : (1.0f - 0.35f));
        const float bottom = height - top;

        const float w = height * 0.5f;
        const float x = rightOfText - (w * 1.25f);
        rightOfText = (int) x;

        Path sortArrow;
        sortArrow.addTriangle (x, bottom, x + w * 0.5f, top, x + w, bottom);

        g.setColour (Colours::black.withAlpha (0.6f));
        g.fillPath (sortArrow);
    }

    g.setColour (Colours::black);
    g.setFont (height * 0.6f, Font::plain);
    const int textX = 4;
	g.drawFittedText (columnName, textX, 0, rightOfText - textX, height, Justification::centredLeft, 1);
}

//==============================================================================
int AngelicLookAndFeel::getTabButtonOverlap (int tabDepth)
{
    return 1 + tabDepth / 4;
}

void AngelicLookAndFeel::createTabButtonShape (Path& p,
                                               int width, int height,
                                               int tabIndex,
                                               const String& text,
                                               Button& button,
                                               TabbedButtonBar::Orientation orientation,
                                               const bool isMouseOver,
                                               const bool isMouseDown,
                                               const bool isFrontTab)
{
    const float w = (float) width;
    const float h = (float) height;

    float length = w;
    float depth = h;

    if (orientation == TabbedButtonBar::TabsAtLeft
         || orientation == TabbedButtonBar::TabsAtRight)
    {
        swapVariables (length, depth);
    }

    const float indent = (float) getTabButtonOverlap ((int) depth);
    const float overhang = 4.0f;

    if (orientation == TabbedButtonBar::TabsAtLeft)
    {
        p.startNewSubPath (w, 0.0f);
        p.lineTo (0.0f, indent);
        p.lineTo (0.0f, h - indent);
        p.lineTo (w, h);
        p.lineTo (w + overhang, h + overhang);
        p.lineTo (w + overhang, -overhang);
    }
    else if (orientation == TabbedButtonBar::TabsAtRight)
    {
        p.startNewSubPath (0.0f, 0.0f);
        p.lineTo (w, indent);
        p.lineTo (w, h - indent);
        p.lineTo (0.0f, h);
        p.lineTo (-overhang, h + overhang);
        p.lineTo (-overhang, -overhang);
    }
    else if (orientation == TabbedButtonBar::TabsAtBottom)
    {
        p.startNewSubPath (0.0f, 0.0f);
        p.lineTo (indent, h);
        p.lineTo (w - indent, h);
        p.lineTo (w, 0.0f);
        p.lineTo (w + overhang, -overhang);
        p.lineTo (-overhang, -overhang);
    }
    else
    {
        p.startNewSubPath (0.0f, h);
        p.lineTo (indent, 0.0f);
        p.lineTo (w - indent, 0.0f);
        p.lineTo (w, h);
        p.lineTo (w + overhang, h + overhang);
        p.lineTo (-overhang, h + overhang);
    }

    p.closeSubPath();

    p = p.createPathWithRoundedCorners (3.0f);
}


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

#ifndef __ANGELJUICE_ANGELICLOOKANDFEEL_HEADER__
#define __ANGELJUICE_ANGELICLOOKANDFEEL_HEADER__

#include "juce.h"


//==============================================================================
/**
    A new, angelic looking look-and-feel.

    To make this the default look for your app, just set it as the default in
    your initialisation code.

    e.g. @code
    void initialise (const String& commandLine)
    {
        static AngelicLookAndFeel shinyLook;
        LookAndFeel::setDefaultLookAndFeel (&shinyLook);
    }
    @endcode
*/
class AngelicLookAndFeel  : public LookAndFeel
{
public:
    //==============================================================================
    /** Creates a AngelicLookAndFeel look and feel object. */
    AngelicLookAndFeel();

    /** Destructor. */
    virtual ~AngelicLookAndFeel();

/*

	//==============================================================================
    void drawDocumentWindowTitleBar (DocumentWindow& window,
                                     Graphics& g, int w, int h,
                                     int titleSpaceX, int titleSpaceW,
                                     const Image* icon,
                                     bool drawTitleTextOnLeft);

	Button* createDocumentWindowButton (int buttonType);

	void positionDocumentWindowButtons (DocumentWindow& window,
                                        int titleBarX, int titleBarY,
                                        int titleBarW, int titleBarH,
                                        Button* minimiseButton,
                                        Button* maximiseButton,
                                        Button* closeButton,
                                        bool positionTitleBarButtonsOnLeft);
*/
    //==============================================================================
    virtual DropShadower* createDropShadowerForComponent (Component* component);


	//==============================================================================
	const Font getPopupMenuFont();

    //==============================================================================
    void drawTextEditorOutline (Graphics& g,
                                int width, int height,
                                TextEditor& textEditor);

    //==============================================================================
    void getComboBoxFonts (Font& itemFont, Font& popupListFont, ComboBox& box);

    //==============================================================================
    void drawScrollbarButton (Graphics& g,
                              ScrollBar& scrollbar,
                              int width, int height,
                              int buttonDirection,
                              bool isScrollbarVertical,
                              bool isMouseOverButton,
                              bool isButtonDown);

    void drawScrollbar (Graphics& g,
                        ScrollBar& scrollbar,
                        int x, int y,
                        int width, int height,
                        bool isScrollbarVertical,
                        int thumbStartPosition,
                        int thumbSize,
                        bool isMouseOver,
                        bool isMouseDown);

    ImageEffectFilter* getScrollbarEffect();

	int getMinimumScrollbarThumbSize (ScrollBar& scrollbar);
	int getDefaultScrollbarWidth();
	int getScrollbarButtonSize (ScrollBar& scrollbar);

    //==============================================================================
    void drawCornerResizer (Graphics& g,
                            int w, int h,
                            bool isMouseOver,
                            bool isMouseDragging);

    //==============================================================================
	void drawTableHeaderColumn (Graphics& g, const String& columnName, int columnId,
                                int width, int height,
                                bool isMouseOver, bool isMouseDown,
                                int columnFlags);

    //==============================================================================
    int getTabButtonOverlap (int tabDepth);

    void createTabButtonShape (Path& p,
                               int width, int height,
                               int tabIndex,
                               const String& text,
                               Button& button,
                               TabbedButtonBar::Orientation orientation,
                               const bool isMouseOver,
                               const bool isMouseDown,
                               const bool isFrontTab);

    //==============================================================================
    juce_UseDebuggingNewOperator

private:

    DropShadowEffect commonShadow;
};


#endif   // __EJUCE_MINIMALLOOKANDFEEL__

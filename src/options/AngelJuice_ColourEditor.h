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

#ifndef __ANGELJUICE_COLOUREDITORCOMPONENT_HEADER__
#define __ANGELJUICE_COLOUREDITORCOMPONENT_HEADER__


#include "../AngelJuice.h"
#include "../AngelJuice_config.h"
#include "../editor/AngelJuice_SyntaxLexerAS.h"


//==============================================================================
/**
    A component that shows a colour swatch with hex ARGB value, and which pops up
    a colour selector when you click it.
*/
class ColourEditor    : public Component,
                        public ChangeListener
{
public:
	ColourEditor (const String& name_, const int style_) :
	  Component (name_),
	  style (style_)
    {
		// @TODO - is good to have getInstance everywhere and not use static ?
		colour = GlobalConfig::getInstance ()->textColours [style];
    }

    ~ColourEditor()
    {
    }

    void paint (Graphics& g)
    {
        g.fillAll (Colours::grey);

        g.fillCheckerBoard (2, 2, getWidth() - 4, getHeight() - 4,
                            10, 10,
                            Colour (0xffdddddd).overlaidWith (colour),
                            Colour (0xffffffff).overlaidWith (colour));

        g.setColour (Colours::white.overlaidWith (colour).contrasting());
        g.setFont (getHeight() * 0.6f, Font::bold);
		g.drawFittedText (getName(),
                          2, 1, getWidth() - 4, getHeight() - 1,
                          Justification::centred, 1);
    }

    void refresh()
    {
        const Colour col (getColour());

        if (col != colour)
        {
            colour = col;
            repaint();
        }
    }

    void mouseDown (const MouseEvent& e)
    {
        ColourSelector colourSelector;
        colourSelector.setName (T("Colour"));
        colourSelector.setCurrentColour (getColour());
        colourSelector.addChangeListener (this);

        PopupMenu m;
        m.addCustomItem (0, &colourSelector, 280, 300, true);
        m.showAt (this);
    }

    void changeListenerCallback (void* source)
    {
        const ColourSelector* const cs = (const ColourSelector*) source;

        if (cs->getCurrentColour() != getColour())
            setColour (cs->getCurrentColour());
    }

	void setColour (const Colour& newColour)
	{
		colour = newColour;

		// @TODO - actually this not triggers a change in the editors
		GlobalConfig::getInstance ()->textColours [style] = newColour;

		SyntaxLexerAngelScript::setStyleGroupColour (style, newColour);

		CommandManager::getInstance()->invokeDirectly (CommandIDs::appColoursUpdate, true);

		repaint();
	}

	const Colour getColour() const
	{
		return colour;
	}


    juce_UseDebuggingNewOperator

private:
    Colour colour;
	int style;
};


#endif   // __JUCER_COLOUREDITORCOMPONENT_JUCEHEADER__

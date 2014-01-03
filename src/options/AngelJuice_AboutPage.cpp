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

#include "../AngelJuice.h"
#include "../AngelJuice_config.h"
#include "../AngelJuice_command.h"
#include "../resources/AngelJuice_Resource.h"
#include "AngelJuice_AboutPage.h"


//==============================================================================
AboutPage::AboutPage() :
	link (0),
	logo (0)
{
	logo = ImageCache::getFromMemory (Resource::logo, Resource::logo_size);

	text1.appendText ("This is a tool made by coders for coders, and this was possible thanks to "
					  "Julian Storer (www.rawmaterialsoftware.com), Andreas Jonsson (www.angelcode.com), "
					  "Niall Moody (www.niallmoody.com), Anthony Casteel (www.omnisu.com). ", Font (13.0f));
	text1.appendText ("Hope you'll use and like AngelJuice scripting engine "
					  "(even if i'm not sure neither the former nor the latter...) ", Font (13.0f, Font::bold));

	text2.appendText (T("AngelJuice v") + JUCEApplication::getInstance()->getApplicationVersion() +
						T(" by kRAkEn/gOre"), Font (24.0f, Font::bold));

	addAndMakeVisible (link = new HyperlinkButton (T("www.anticore.org/juce/angeljuice"),
												   URL (T("http://www.anticore.org/juce/angeljuice"))));
	link->setFont (Font (10.0f, Font::bold | Font::underlined), true);
	// link->setTextColour (Colours::orangered);
}

AboutPage::~AboutPage()
{
	deleteAllChildren();
	ImageCache::release (logo);
}

void AboutPage::paint (Graphics& g)
{
	g.fillAll (Colour (0xffebebeb));

	text2.drawWithin (g, 0, 4, getWidth(), 40, Justification::centredTop);

	g.drawImageWithin (logo, 0, 44, getWidth(), getHeight() - 174, RectanglePlacement::centred, false);

	text1.drawWithin (g, 0, getHeight() - 110, getWidth(), 90, Justification::centredTop);
}

void AboutPage::resized()
{
	text1.layout (getWidth() - 24, Justification::topLeft, false);
	text2.layout (getWidth() - 24, Justification::horizontallyJustified, true);

	link->setSize (100, 22);
	link->changeWidthToFitText();
	link->setTopLeftPosition ((getWidth() - link->getWidth()) / 2, getHeight() - link->getHeight() - 10);
}


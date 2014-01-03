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
#include "AngelJuice_FontsPage.h"


FontsPage::FontsPage()
{
	Font::findFonts (fonts);

	// listbox of font names
	addAndMakeVisible (listBox = new ListBox (T("fonts"), this));
	listBox->setRowHeight (26);

	// colour selector editor
	addAndMakeVisible (colour[0] = new ColourEditor("default", 0));
	addAndMakeVisible (colour[1] = new ColourEditor("comments", 1));
	addAndMakeVisible (colour[2] = new ColourEditor("numbers", 2));
	addAndMakeVisible (colour[3] = new ColourEditor("words", 3));
	addAndMakeVisible (colour[4] = new ColourEditor("classes", 4));
	addAndMakeVisible (colour[5] = new ColourEditor("strings", 5));
	addAndMakeVisible (colour[6] = new ColourEditor("preprocessor", 6));
	addAndMakeVisible (colour[7] = new ColourEditor("identifiers", 7));

	// bold toggle
	addAndMakeVisible (boldButton = new ToggleButton (T("bold")));
	boldButton->addButtonListener (this);

	// italic toggle
	addAndMakeVisible (italicButton = new ToggleButton (T("italic")));
	italicButton->addButtonListener (this);

	// font height slider
	addAndMakeVisible (sizeSlider = new Slider (T("size")));
	sizeSlider->setRange (5.0, 30.0, 0.1);
	sizeSlider->setValue (14.0);
	// sizeSlider->setChangeNotificationOnlyOnRelease (true);
	sizeSlider->setMouseCursor (MouseCursor(MouseCursor::LeftRightResizeCursor));
	sizeSlider->setSkewFactor (0.5f);
	sizeSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 15);
	sizeSlider->setTextValueSuffix (T(" px"));
	sizeSlider->addListener (this);


	listBox->selectRow (0);
	// listBox->setOutlineColour (Colours::black.withAlpha (0.5f), 1);


	// set up the layout and resizer bars..
	verticalLayout.setItemLayout (0, -0.2, -0.8, -0.65);  // width of the font list must be between 20% and 80%, preferably 50%
	verticalLayout.setItemLayout (1, 3, 3, 3);           // the vertical divider drag-bar thing is always 8 pixels wide
	verticalLayout.setItemLayout (2, 150, -1.0, -0.35);   // the components on the right must be
														 // at least 150 pixels wide, preferably 50% of the total width
	verticalDividerBar = new StretchableLayoutResizerBar (&verticalLayout, 1, true);
	addAndMakeVisible (verticalDividerBar);

	horizontalLayout.setItemLayout (0, 20, 20, 20);        // default
	horizontalLayout.setItemLayout (1, 20, 20, 20);        // comments
	horizontalLayout.setItemLayout (2, 20, 20, 20);        // number
	horizontalLayout.setItemLayout (3, 20, 20, 20);        // word
	horizontalLayout.setItemLayout (4, 20, 20, 20);        // classes
	horizontalLayout.setItemLayout (5, 20, 20, 20);        // string / chars
	horizontalLayout.setItemLayout (6, 20, 20, 20);        // operator
	horizontalLayout.setItemLayout (7, 20, 20, 20);        // identifier
		horizontalLayout.setItemLayout (8, 3, 3, 3);       // the horizontal divider drag-bar thing is always 8 pixels high
		horizontalLayout.setItemLayout (9, 2, 5, 5);       // a gap between the controls
	horizontalLayout.setItemLayout (10, 15, 20, 20);       // the italic button would like to be 20 pixels high
		horizontalLayout.setItemLayout (11, 2, 5, 5);      // a gap between the controls
	horizontalLayout.setItemLayout (12, 15, 20, 20);       // the bold button would like to be 20 pixels high
		horizontalLayout.setItemLayout (13, 2, 5, 5);      // a gap between the controls
	horizontalLayout.setItemLayout (14, 15, 20, 20);       // the italic button would like to be 20 pixels high
		horizontalLayout.setItemLayout (15, 5, -1.0, 5);   // add a gap at the bottom that will fill up any

	horizontalDividerBar = new StretchableLayoutResizerBar (&horizontalLayout, 1, false);
	addAndMakeVisible (horizontalDividerBar);
}

FontsPage::~FontsPage()
{
	deleteAllChildren();
}

void FontsPage::resized()
{
	// lay out the list box and vertical divider..
	Component* vcomps[] = { listBox, verticalDividerBar, 0 };

	verticalLayout.layOutComponents (vcomps, 3,
									 3, 3, getWidth() - 6, getHeight() - 6,
									 false,     // lay out side-by-side
									 true);     // resize the components' heights as well as widths

	// now lay out the text box and the controls below it..
	Component* hcomps[] = {
							colour[0],colour[1],colour[2],colour[3],colour[4],colour[5],colour[6],colour[7],
							horizontalDividerBar, 0,
							boldButton, 0,
							italicButton, 0,
							sizeSlider };

	horizontalLayout.layOutComponents (hcomps, 15,
									   3 + verticalLayout.getItemCurrentPosition (2), // for their widths, refer to the vertical layout state
									   3,
									   verticalLayout.getItemCurrentAbsoluteSize (2),
									   getHeight() - 6,
									   true,    // lay out above each other
									   true);   // resize the components' widths as well as heights
}

// implements the SimpleListBoxModel method
int FontsPage::getNumRows()
{
	return 1 + fonts.size();
}

// implements the SimpleListBoxModel method
void FontsPage::paintListBoxItem (int rowNumber,
									Graphics& g,
									int width, int height,
									bool rowIsSelected)
{
	if (rowIsSelected)
		g.fillAll (Colours::lightblue);

	Font font (*(GlobalConfig::getInstance()->editorFont));
	font.setHeight (10.0f);

	if (rowNumber == 0)
	{
		// Font font (*(GlobalConfig::getInstance()->editorFont));
		// font.setHeight (10.0f);

		g.setFont (font);
		g.drawText ("default font",
					4, 0, width - 4, height,
					Justification::centredLeft, true);
	}
	else
	{
		if (fonts [rowNumber - 1] != 0)
		{
			Font fontName (*fonts [rowNumber - 1]);
			// font.setHeight (height * 0.7f);

			g.setFont (font);
			g.drawText (fontName.getTypefaceName(),
						4, 0, width - 4, height,
						Justification::centredLeft, true);
		}
	}
}

void FontsPage::updateFont()
{
	int selectedRow = listBox->getSelectedRow();

	Font* f = GlobalConfig::getInstance()->editorFont;
	if (selectedRow != 0)
	{
		f = fonts [selectedRow - 1];
	}

	if (f != 0)
	{
		Font font (*f);

		font.setHeight ((float) sizeSlider->getValue());
		font.setBold (boldButton->getToggleState());
		font.setItalic (italicButton->getToggleState());

		// update font on all text editors
		GlobalConfig::getInstance()->currentFont = font;
		CommandManager::getInstance()->invokeDirectly (CommandIDs::appFontUpdate, true);
	}
}

void FontsPage::selectedRowsChanged (int lastRowselected)
{
	if (lastRowselected == 0)
	{
		boldButton->setToggleState (false,false);
		boldButton->setEnabled (false);

		italicButton->setToggleState (false,false);
		italicButton->setEnabled (false);
		
		sizeSlider->setValue (10.0f);
		sizeSlider->setEnabled (false);
	}
	else
	{
		boldButton->setEnabled (true);
		italicButton->setEnabled (true);
		sizeSlider->setEnabled (true);
	}

	updateFont();
}

void FontsPage::buttonClicked (Button* button)
{
	// (this is called when a toggle button is pressed)
	updateFont();
}

void FontsPage::sliderValueChanged (Slider*)
{
	// (this is called when the size slider is moved)
	updateFont();
}


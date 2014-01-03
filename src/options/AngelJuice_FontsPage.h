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

#ifndef __ANGELJUICE_FONTSPAGE_HEADER__
#define __ANGELJUICE_FONTSPAGE_HEADER__


#include "../AngelJuice.h"
#include "../AngelJuice_config.h"

#include "AngelJuice_ColourEditor.h"


//==============================================================================
class FontsPage : public Component,
                  public ListBoxModel,
                  public ButtonListener,
                  public SliderListener
{
public:

    FontsPage();
    ~FontsPage();

    void resized();

    // implements the SimpleListBoxModel method
    int getNumRows();
    void paintListBoxItem (int rowNumber,
                           Graphics& g,
                           int width, int height,
                           bool rowIsSelected);
    void selectedRowsChanged (int lastRowselected);

    void buttonClicked (Button* button);
    void sliderValueChanged (Slider*);

    void updateFont();

protected:
	
    OwnedArray<Font> fonts;
    ListBox* listBox;
    TextEditor* textBox;
    ToggleButton* boldButton;
    ToggleButton* italicButton;
    Slider* sizeSlider;
	ColourEditor* colour[8];

    StretchableLayoutManager verticalLayout;
    StretchableLayoutManager horizontalLayout;

    StretchableLayoutResizerBar* verticalDividerBar;
    StretchableLayoutResizerBar* horizontalDividerBar;
};


#endif // __ANGELJUICE_FONTSPAGE_HEADER__

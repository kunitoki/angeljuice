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

#ifndef __ANGELJUICE_TOOLBAR_HEADER__
#define __ANGELJUICE_TOOLBAR_HEADER__


#include "../AngelJuice_config.h"


//==============================================================================
class ToolbarFactory   : public ToolbarItemFactory
{
public:

	//==============================================================================
	ToolbarFactory ();
	~ToolbarFactory ();

	//==============================================================================
	void getAllToolbarItemIds (Array <int>& ids);
	void getDefaultItemSet (Array <int>& ids);

	ToolbarItemComponent* createItem (const int itemId);

private:

	//==============================================================================
    ToolbarButton* createButtonFromImage (const int itemId,
                                          const String& text,
                                          const char* imageData,
                                          const int imageDataSize,
                                          const int commandID = 0,
                                          const bool toggle = false);

	// Demonstrates how to put a custom component into a toolbar - this one contains
	// a ComboBox.
	/*
	class CustomToolbarComboBox : public ToolbarItemComponent
	{
	public:
		CustomToolbarComboBox (const int toolbarItemId)
			: ToolbarItemComponent (toolbarItemId, T("Custom Toolbar Item"), false)
		{
			addAndMakeVisible (comboBox = new ComboBox (T("demo toolbar combo box")));

			for (int i = 1; i < 20; ++i)
			comboBox->addItem (T("Toolbar ComboBox item ") + String (i), i);

			comboBox->setSelectedId (1);
			comboBox->setEditableText (true);
		}

		~CustomToolbarComboBox()
		{
			delete comboBox;
		}

		bool getToolbarItemSizes (int toolbarDepth,
									bool isToolbarVertical,
									int& preferredSize, int& minSize, int& maxSize)
		{
			if (isToolbarVertical)
				return false;

			preferredSize = 250;
			minSize = 80;
			maxSize = 300;
			return true;
		}

		void paintButtonArea (Graphics&, int, int, bool, bool)
		{
		}

		void contentAreaChanged (const Rectangle& contentArea)
		{
			comboBox->setSize (contentArea.getWidth() - 2,
								jmin (contentArea.getHeight() - 2, 22));

			comboBox->setCentrePosition (contentArea.getCentreX(), contentArea.getCentreY());
		}

	private:
		ComboBox* comboBox;
	};
	*/
};


#endif // __ANGELJUICE_TOOLBAR_HEADER__

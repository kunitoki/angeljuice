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

#include "../AngelJuice.h"
#include "../AngelJuice_config.h"
#include "AngelJuice_ErrorOutput.h"


//==============================================================================
ErrorOutputComponent::ErrorOutputComponent (AngelJuiceComponent* holder_)
    : holder (holder_),
    font (*(GlobalConfig::getInstance()->editorFont))
{
    // Create our table component and add it to this component..
    addAndMakeVisible (table = new TableListBox (T("error table"), this));

    // give it a border
	table->setHeaderHeight (18);
	table->setRowHeight (16);
	table->setOutlineThickness (0);
	table->setColour (ListBox::outlineColourId, Colours::grey);
	table->setColour (ListBox::backgroundColourId, Colours::black);

    // Add some columns to the table header, based on the column list in our database..
	table->getHeader()->addColumn (T("Type"), 1, 70, 50, 100, TableHeaderComponent::defaultFlags);
	table->getHeader()->addColumn (T("File"), 2, 180, 100, 400, TableHeaderComponent::defaultFlags);
	table->getHeader()->addColumn (T("Line"), 3, 50, 50, 50, TableHeaderComponent::defaultFlags);
	table->getHeader()->addColumn (T("Message"), 4, 280, 50, -1, TableHeaderComponent::defaultFlags);

    // we could now change some initial settings..
//    table->getHeader()->setSortColumnId (0, true); // sort forwards by the ID column
//    table->getHeader()->setColumnVisible (7, false); // hide the "length" column until the user shows it
}

ErrorOutputComponent::~ErrorOutputComponent()
{
	clearErrors ();

	deleteAllChildren();
}

//==============================================================================
void ErrorOutputComponent::appendErrorLine (const String& errorType,
											const String& errorString,
											const String& fileName,
											const int lineNumber)
{
	dataList.add (new ErrorInformation (errorType,errorString,fileName,lineNumber));

	table->autoSizeAllColumns ();
	table->updateContent ();
}

void ErrorOutputComponent::clearErrors ()
{
	for (int i = 0; i < dataList.size (); i++)
	{
		delete (ErrorInformation*) dataList.getUnchecked (i);
	}
	dataList.clear ();

	table->updateContent();
}

//==============================================================================
// This is overloaded from TableListBoxModel, and must return the total number of rows in our table
int ErrorOutputComponent::getNumRows()
{
    return dataList.size ();
}

void ErrorOutputComponent::paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
		g.fillAll (Colours::darkgreen);
}

// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
// components.
void ErrorOutputComponent::paintCell (Graphics& g,
                                     int rowNumber,
                                     int columnId,
                                     int width, int height,
                                     bool rowIsSelected)
{
    g.setColour (Colours::lightgreen);
    g.setFont (font);

	ErrorInformation* info = (ErrorInformation*) dataList [rowNumber];
	if (info != 0)
	{
        const String text (info->getAttributeForColumnId (columnId));
        g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
	}

    g.setColour (Colours::white.withAlpha (0.2f));
    g.fillRect (width - 1, 0, 1, height);
}

// This is overloaded from TableListBoxModel, and tells us that the user has clicked a table header
// to change the sort order.
void ErrorOutputComponent::sortOrderChanged (int newSortColumnId, const bool isForwards)
{
    if (newSortColumnId != 0)
    {
        DemoDataSorter sorter (newSortColumnId, isForwards);
        dataList.sort (sorter);

        table->updateContent();
    }
}

// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* ErrorOutputComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected,
                                                          Component* existingComponentToUpdate)
{
/*
    if (columnId == 5) // If it's the ratings column, we'll return our custom component..
    {
        RatingColumnCustomComponent* ratingsBox = (RatingColumnCustomComponent*) existingComponentToUpdate;

        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (ratingsBox == 0)
            ratingsBox = new RatingColumnCustomComponent (*this);

        ratingsBox->setRowAndColumn (rowNumber, columnId);

        return ratingsBox;
    }
    else
    {
        // for any other column, just return 0, as we'll be painting these columns directly.
*/
        jassert (existingComponentToUpdate == 0);
        return 0;
/*
	}
*/
}

// This is overloaded from TableListBoxModel, and should choose the best width for the specified
// column.
int ErrorOutputComponent::getColumnAutoSizeWidth (int columnId)
{
//    if (columnId == 5)
//        return 100; // (this is the ratings column, containing a custom component)

    int widest = 32;

	for (int i = 0; i < dataList.size (); i++)
	{
		ErrorInformation* info = (ErrorInformation*) dataList.getUnchecked (i);

		const String text (info->getAttributeForColumnId (columnId));

		widest = jmax (widest, font.getStringWidth (text));
	}

    return widest + 8;
}

void ErrorOutputComponent::cellClicked (int rowNumber, int columnId, const MouseEvent& e)
{
	ErrorInformation* info = (ErrorInformation*) dataList [rowNumber];
	if (info != 0)
	{
		String bubbleText (info->getAttributeForColumnId (2));
		bubbleText << " at line " << info->getAttributeForColumnId (3) << "\n";
		bubbleText << info->getAttributeForColumnId (1) << ": ";
		bubbleText << info->getAttributeForColumnId (4);

		BubbleMessageComponent* bmc = new BubbleMessageComponent();

        if (Desktop::canUseSemiTransparentWindows())
        {
            bmc->setAlwaysOnTop (true);
            bmc->addToDesktop (0);
            bmc->showAt (e.getMouseDownScreenX(), e.getMouseDownScreenY(), bubbleText, 2000, true, true);
        }
        else
        {
            holder->addChildComponent (bmc);
            bmc->showAt (this, bubbleText, 2000, true, true);
        }

	}
}

void ErrorOutputComponent::cellDoubleClicked (int rowNumber, int columnId, const MouseEvent&)
{
	ErrorInformation* info = (ErrorInformation*) dataList [rowNumber];
	if (info != 0)
	{
        const String fileName (info->getAttributeForColumnId (2));
        const int lineNumber = info->getAttributeForColumnId (3).getIntValue();

		int docIndex = holder->getCurrentOpenDocumentIndex ();
		int lastDocIndex = holder->getLastCompiledDocumentIndex ();

		if (docIndex != lastDocIndex)
			docIndex = lastDocIndex;

		if (fileName != ANGELJUICE_UNTITLED)
			docIndex = holder->getDocumentIndexFromFileName (fileName);

		if (docIndex >= 0)
		{
			holder->setCurrentOpenDocumentIndex (docIndex);
			holder->setDocumentHighlightLine (docIndex, lineNumber);
		}
	}
}

//==============================================================================
void ErrorOutputComponent::resized()
{
    // position our table with a gap around its edge
    table->setBoundsInset (BorderSize(0));
}


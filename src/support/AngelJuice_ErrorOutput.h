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

#ifndef __ANGELJUICE_ERROROUTPUT_HEADER__
#define __ANGELJUICE_ERROROUTPUT_HEADER__


class AngelJuiceComponent;


//==============================================================================
class ErrorOutputComponent : public Component,
                             public TableListBoxModel
{
public:

	//==============================================================================
	class ErrorInformation
	{
	public:
		ErrorInformation (const String& msgType_,
						  const String& msgText_,
						  const String& fileName_,
						  const int lineNumber_)
		{
			columns [0] = msgType_;
			columns [1] = fileName_;
			columns [2] = String(lineNumber_);
			columns [3] = msgText_;
		}

		const String& getAttributeForColumnId (const int columnId)
		{
			return columns [columnId - 1];
		}

		String columns [4];
	};


	//==============================================================================
    ErrorOutputComponent (AngelJuiceComponent* holder);
    ~ErrorOutputComponent();

    //==============================================================================
	void appendErrorLine (const String& errorType,
                          const String& errorString,
						  const String& fileName,
						  const int line);
	void clearErrors ();

    //==============================================================================
    // This is overloaded from TableListBoxModel, and must return the total number of rows in our table
    int getNumRows();

    // This is overloaded from TableListBoxModel, and should fill in the background of the whole row
    void paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected);

    // This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
    // components.
    void paintCell (Graphics& g,
                    int rowNumber,
                    int columnId,
                    int width, int height,
                    bool rowIsSelected);

    // This is overloaded from TableListBoxModel, and tells us that the user has clicked a table header
    // to change the sort order.
    void sortOrderChanged (int newSortColumnId, const bool isForwards);

    // This is overloaded from TableListBoxModel, and must update any custom components that we're using
    Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected,
                                        Component* existingComponentToUpdate);

    // This is overloaded from TableListBoxModel, and should choose the best width for the specified
    // column.
    int getColumnAutoSizeWidth (int columnId);

    // This is overloaded from TableListBoxModel, and should act when a cell is clicked
    void cellClicked (int rowNumber, int columnId, const MouseEvent& e);

    // This is overloaded from TableListBoxModel, and should act when a cell is double clicked
	void cellDoubleClicked (int rowNumber, int columnId, const MouseEvent&);

    //==============================================================================
    /** @internal */
    void resized();

private:

	AngelJuiceComponent* holder;

	TableListBox* table;    // the table component itself
    Font font;

	VoidArray dataList;   // A pointer to the sub-node of demoData that contains the list of data rows
    int numRows;            // The number of rows of data we've got


    //==============================================================================
    // A comparator used to sort our data when the user clicks a column header
    class DemoDataSorter
    {
    public:
        DemoDataSorter (const int columnToSort_, bool forwards)
            : columnToSort (columnToSort_),
              direction (forwards ? 1 : -1)
        {
        }

        int compareElements (void* first_,
                             void* second_)
        {
			ErrorInformation* first = (ErrorInformation*) first_;
			ErrorInformation* second = (ErrorInformation*) second_;

            int result = first->getAttributeForColumnId (columnToSort)
                           .compareLexicographically (second->getAttributeForColumnId (columnToSort));

            if (result == 0)
                result = first->getAttributeForColumnId (1)
                           .compareLexicographically (second->getAttributeForColumnId (1));

            return direction * result;
        }

    private:
        const int columnToSort;
        const int direction;
    };

};


#endif // __ANGELJUICE_ERROROUTPUT_HEADER__

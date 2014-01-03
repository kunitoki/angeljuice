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

#ifndef __ANGELJUICE_TABBEDEDITOR_HEADER__
#define __ANGELJUICE_TABBEDEDITOR_HEADER__


#include "../AngelJuice_config.h"
#include "AngelJuice_OpenDocument.h"


//==============================================================================
class AngelJuiceComponent;


//==============================================================================
class TabbedEditorComponent  : public TabbedComponent
{
public:

    TabbedEditorComponent (AngelJuiceComponent* holder);
    ~TabbedEditorComponent ();

	void addPanelComponentTab (const File& file = File::nonexistent);
	void popupMenuClickOnTab (const int tabIndex, const String& tabName);

	OpenDocumentComponent* getDocumentByIndex (const int tabIndex);

	void closeDocumentByIndex (const int tabIndex);

	bool isFileAlreadyOpened (const File& fileToCheck, int& fileIndex);
	void updatePanelComponentFilePath (const int tabIndex, const File& file);

	void setDebugMode (const bool isDebugging);
	void setFont (const Font& font);
	void updateColors ();

protected:
	AngelJuiceComponent* holder;
	bool isInDebugMode;
};


#endif // __ANGELJUICE_TABBEDEDITOR_HEADER__

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

#include "AngelJuice_TabbedEditor.h"
#include "AngelJuice_OpenDocument.h"


//==============================================================================
TabbedEditorComponent::TabbedEditorComponent(AngelJuiceComponent* holder_) :
	TabbedComponent (TabbedButtonBar::TabsAtTop),
	holder (holder_),
	isInDebugMode (false)
{
	setTabBarDepth (26);
	setWantsKeyboardFocus (true);
}

TabbedEditorComponent::~TabbedEditorComponent()
{
}

//------------------------------------------------------------------------------
void TabbedEditorComponent::addPanelComponentTab (const File& file)
{
	String fileName;
	if (file == File::nonexistent)
		fileName = ANGELJUICE_UNTITLED;
	else
	{
		fileName = file.getFileName ();
	}

	OpenDocumentComponent* newDocument = new OpenDocumentComponent (holder, this);

	addTab (fileName,
            ANGELJUICE_COLOR,
			newDocument,
			true);

	newDocument->setDocumentFilePath (file);
}

void TabbedEditorComponent::popupMenuClickOnTab (const int tabIndex, const String& tabName)
{
    OpenDocumentComponent* currentDocument = getDocumentByIndex (tabIndex);

	PopupMenu menu;
	menu.addItem (1, "Close document", !isInDebugMode);
	menu.addItem (2, "Reload document", false && !isInDebugMode);
    menu.addSeparator ();
    menu.addItem (3, "Syntax hightlighting", true && !isInDebugMode, currentDocument->isSyntaxLexerActive());

	switch (menu.show())
	{
		case 1:
			closeDocumentByIndex (tabIndex);
			break;
		case 2:
            // @TODO: call reloadDocument
			break;
        case 3:
            currentDocument->setSyntaxLexerActive (!currentDocument->isSyntaxLexerActive());
            break;
        case 0:
		default:
			break;
	}
}

//------------------------------------------------------------------------------
OpenDocumentComponent* TabbedEditorComponent::getDocumentByIndex (const int tabIndex)
{
	return (OpenDocumentComponent*) getTabContentComponent (tabIndex);
}

void TabbedEditorComponent::closeDocumentByIndex (const int tabIndex)
{
	OpenDocumentComponent* document = getDocumentByIndex (tabIndex);

	if (document && document->closeDocument ())
		removeTab (tabIndex);
}

//------------------------------------------------------------------------------
void TabbedEditorComponent::updatePanelComponentFilePath (const int tabIndex, const File& file)
{
	if (tabIndex >= 0 && tabIndex < getNumTabs())
	{
		String fileName;
		if (file == File::nonexistent)
			fileName = ANGELJUICE_UNTITLED;
		else
		{
			fileName = file.getFileName ();
		}

		if (getDocumentByIndex (tabIndex)->hasBeenModified())
			setTabName (tabIndex, fileName + T(" *"));
		else
			setTabName (tabIndex, fileName);

		getDocumentByIndex (tabIndex)->setDocumentFilePath (file);
	}
}

//------------------------------------------------------------------------------
bool TabbedEditorComponent::isFileAlreadyOpened (const File& fileToCheck, int& fileIndex)
{
	bool alreadyOpen = false;

	for (int i = 0; i < getNumTabs(); i++)
	{
		File file = getDocumentByIndex(i)->getDocumentFilePath();
		if (file != File::nonexistent &&
			file == fileToCheck)
		{
			setCurrentTabIndex (i);

			// @TODO check if is modified

			fileIndex = i;
			alreadyOpen = true;
			break;
		}
	}

	return alreadyOpen;
}

//------------------------------------------------------------------------------
void TabbedEditorComponent::setDebugMode (const bool isDebugging)
{
    isInDebugMode = isDebugging;

	if (isDebugging)
	{
		setEnabled (false);

		for (int i=0; i < getNumTabs(); i++)
		{
			getDocumentByIndex (i)->setDebugMode (isDebugging);
		}
	}
	else
	{
		setEnabled (true);

		for (int i=0; i < getNumTabs(); i++)
		{
			getDocumentByIndex (i)->setDebugMode (isDebugging);
		}

		OpenDocumentComponent* document =
			(OpenDocumentComponent*) getCurrentContentComponent ();
		document->grabKeyboardFocus ();
	}
}

void TabbedEditorComponent::setFont (const Font& font)
{
	for (int i=0; i < getNumTabs(); i++)
	{
		OpenDocumentComponent* document = getDocumentByIndex (i);
		SyntaxTextEditor* textBox = document->getTextEditor ();

		textBox->setFont (font);
	}
}

void TabbedEditorComponent::updateColors ()
{
	OpenDocumentComponent* document =
		(OpenDocumentComponent*) getCurrentContentComponent ();
	document->repaint ();
}


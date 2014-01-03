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

#include "../AngelJuice_config.h"
#include "../AngelJuice_command.h"
#include "../editor/AngelJuice_SyntaxLexerAS.h"
#include "../scripting/AngelJuice_ScriptableEngine.h"
#include "AngelJuice_OpenDocument.h"
#include "AngelJuice_TabbedEditor.h"


//==============================================================================
OpenDocumentComponent::OpenDocumentComponent (AngelJuiceComponent* holder_,
											  TabbedEditorComponent* parent_) :
	holder (holder_),
	parent (parent_),
	isModified (false),
	firstLoad (false)
{
	filePath = File::nonexistent;

	setOpaque(true);

	textBox = new SyntaxTextEditor();
	textBox->setColours (Colours::black, Colours::white);
	textBox->setWantsKeyboardFocus (true);
	textBox->setFont (GlobalConfig::getInstance()->currentFont);
    // @XXX: not do this here, just wait !
    //	textBox->setSyntaxLexer (new SyntaxLexerAngelScript);

	textBox->setBreakPointsEnabled (true);
	textBox->setText (T(""),false);
	textBox->setCaretPosition (0);

	textBox->addListener (this);

	addAndMakeVisible (textBox);
}

OpenDocumentComponent::~OpenDocumentComponent ()
{
	deleteAllChildren ();
}

//------------------------------------------------------------------------------
void OpenDocumentComponent::resized ()
{
	textBox->setBounds (0,0,getWidth(),getHeight());
}

//------------------------------------------------------------------------------
void OpenDocumentComponent::textEditorReturnKeyPressed (SyntaxTextEditor& editor){}
void OpenDocumentComponent::textEditorEscapeKeyPressed (SyntaxTextEditor& editor){}
void OpenDocumentComponent::textEditorFocusLost (SyntaxTextEditor& editor){}
void OpenDocumentComponent::textEditorTextChanged (SyntaxTextEditor& editor)
{
	if (!firstLoad)
		setModified (true);
	else
		firstLoad = false;
}

void OpenDocumentComponent::textEditorChangeBreakPoints (SyntaxTextEditor& editor)
{
	ScriptableEngine::getInstance()->setBreakPoints (editor.getBreakPointsArray());
}


//------------------------------------------------------------------------------
bool OpenDocumentComponent::closeDocument ()
{
	if (isModified)
	{
		// ask user what to do
		int returnValue = AlertWindow::showYesNoCancelBox(
											AlertWindow::QuestionIcon,
											T("Script has been modified"),
											T("Would you like to save it ?"));

		switch (returnValue)
		{
		case 1: // yes
			CommandManager::getInstance()->invokeDirectly (CommandIDs::fileSave, false);
			break;
		case 2: // no
			break;
		case 0: // cancel
			return false;
		}
	}

	return true;
}

//------------------------------------------------------------------------------
SyntaxTextEditor* OpenDocumentComponent::getTextEditor ()
{
	return textBox;
}

String OpenDocumentComponent::getDocumentContent ()
{
	return textBox->getText ();
}

File& OpenDocumentComponent::getDocumentFilePath ()
{
	return filePath;
}

//------------------------------------------------------------------------------
void OpenDocumentComponent::setDocumentContent (const String& text)
{
	textBox->setText (text);
	textBox->grabKeyboardFocus ();
}

void OpenDocumentComponent::setDocumentFilePath (const File& newFileToSet)
{
	filePath = newFileToSet;
	fileAccessTime = filePath.getLastModificationTime ();

	if (newFileToSet.hasFileExtension (GlobalConfig::getInstance()->preferredExtension) ||
		newFileToSet == File::nonexistent)
		textBox->setSyntaxLexer (new SyntaxLexerAngelScript);
	else
		textBox->setSyntaxLexer (0);
}

void OpenDocumentComponent::checkDocumentModifications ()
{
	if (filePath.getLastModificationTime () != fileAccessTime)
	{
		String message;
		message << "Someone has modified " << filePath.getFileName() << " in background. Reload ?";
		bool reload = AlertWindow::showOkCancelBox (AlertWindow::WarningIcon,T("Warning"),message);

		if (reload)
		{
			textBox->setText (filePath.loadFileAsString ());
			setModified (false);
			setDocumentFilePath (filePath);
		}
	}
}

//------------------------------------------------------------------------------
bool OpenDocumentComponent::hasBeenModified ()
{
	return isModified;
}

void OpenDocumentComponent::setModified (const bool newState)
{
	if (isModified != newState)
	{
		isModified = newState;

		StringArray tabNames = parent->getTabNames();
		for (int i = 0; i < parent->getNumTabs(); ++i)
		{
			if (this == parent->getTabContentComponent(i))
			{
				if (isModified)
				{
					parent->setTabName (i, tabNames[i] + T(" *"));
				}
				else
				{
					parent->setTabName (i, tabNames[i].replace (T(" *"),T("")));
				}

				// parent->>setTabBackgroundColour (i, isModified ? ANGELJUICE_COLORDARK : ANGELJUICE_COLOR);
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
void OpenDocumentComponent::setFirstLoad (const bool isFirstLoad)
{
	firstLoad = isFirstLoad;
}

//------------------------------------------------------------------------------
void OpenDocumentComponent::setDebugMode (const bool isDebugging)
{
	if (isDebugging)
	{
		textBox->setCurrentExecutedLine (-1);
		textBox->setColours (
						Colours::black,
						Colours::palegreen.brighter(2.0f),
						Colours::yellow );

		textBox->setDebugMode (true);
//		textBox->setInterceptsMouseClicks (false,false);
	}
	else
	{
		textBox->setCurrentExecutedLine (-1);
		textBox->setColours (
						Colours::black,
						Colours::white,
						Colour (0x401111ee) );

		textBox->setDebugMode (false);
//		textBox->setInterceptsMouseClicks (true,false);
		textBox->setHighlightedRegion (textBox->getCaretPosition(),0);
	}
}

//------------------------------------------------------------------------------
void OpenDocumentComponent::highlightLine (const int lineNumber)
{
	int start, end;

	textBox->getTextPositionOfLine (lineNumber, start, end);
	textBox->setHighlightedRegion (start, end);
}

void OpenDocumentComponent::setCurrentExecutedLine (const int lineNumber)
{
	textBox->setCurrentExecutedLine (lineNumber);
}

//------------------------------------------------------------------------------
bool OpenDocumentComponent::isSyntaxLexerActive ()
{
    return textBox->getSyntaxLexer () != 0;
}

void OpenDocumentComponent::setSyntaxLexerActive (const bool isActive)
{
    if (isActive)
        textBox->setSyntaxLexer (new SyntaxLexerAngelScript);
    else
        textBox->setSyntaxLexer (0);
}

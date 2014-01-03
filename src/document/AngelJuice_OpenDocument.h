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

#ifndef __ANGELJUICE_OPENDOCUMENT_HEADER__
#define __ANGELJUICE_OPENDOCUMENT_HEADER__

#include "../AngelJuice_config.h"
#include "../editor/AngelJuice_SyntaxTextEditor.h"


//==============================================================================
class AngelJuiceComponent;		// main gui
class TabbedEditorComponent;	// parent


//==============================================================================
// @TODO - make it inherit FileBasedDocument
class OpenDocumentComponent :	public Component,
								public SyntaxTextEditorListener
{
public:
    OpenDocumentComponent (AngelJuiceComponent* holder,
                           TabbedEditorComponent* parent);
    ~OpenDocumentComponent ();

	void resized ();

	void textEditorTextChanged (SyntaxTextEditor& editor);
	void textEditorReturnKeyPressed (SyntaxTextEditor& editor);
	void textEditorEscapeKeyPressed (SyntaxTextEditor& editor);
	void textEditorFocusLost (SyntaxTextEditor& editor);
	void textEditorChangeBreakPoints (SyntaxTextEditor& editor);

	SyntaxTextEditor* getTextEditor ();
	String getDocumentContent ();
	File& getDocumentFilePath ();

//    void reloadDocument ();
	bool closeDocument ();

	void setDocumentContent (const String& text);
	void setDocumentFilePath (const File& file);
	void checkDocumentModifications ();

	bool hasBeenModified ();
	void setFirstLoad (const bool isFirstLoad);
	void setModified (const bool newState);
	void setDebugMode (const bool isDebugging);

	void setCurrentExecutedLine (const int lineNumber);
	void highlightLine (const int lineNumber);

    bool isSyntaxLexerActive ();
    void setSyntaxLexerActive (const bool isActive);

protected:

	AngelJuiceComponent* holder;
	TabbedEditorComponent* parent;

	SyntaxTextEditor* textBox;
	File filePath;
	Time fileAccessTime;
	bool isModified;
	bool firstLoad;
};


#endif // __ANGELJUICE_OPENDOCUMENT_HEADER__

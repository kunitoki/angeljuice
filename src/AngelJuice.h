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

#ifndef __ANGELJUICE_HEADER__
#define __ANGELJUICE_HEADER__

#include "AngelJuice_config.h"
#include "AngelJuice_command.h"
#include "AngelJuice_window.h"

//==============================================================================
#include "resources/AngelJuice_Resource.h"

#include "scripting/AngelJuice_ScriptablePlugin.h"
#include "scripting/AngelJuice_ScriptableEngine.h"

#include "document/AngelJuice_TabbedEditor.h"
#include "document/AngelJuice_ProjectTree.h"
#include "document/AngelJuice_OpenDocument.h"

#include "support/AngelJuice_Toolbar.h"
#include "support/AngelJuice_TabbedSupport.h"
#include "support/AngelJuice_StatusBar.h"

#include "options/AngelJuice_OptionWindow.h"



//==============================================================================
class AngelJuiceComponent :	public Component,
							public ApplicationCommandTarget,
							public MenuBarModel,
							public ScriptableEngineModel
{
public:

	AngelJuiceComponent (AngelJuiceWindow* mainWindow);
    ~AngelJuiceComponent ();

	//==============================================================================
	AngelJuiceWindow* getMainWindow ();
	ApplicationCommandManager* getApplicationCommandManager ();

	//==============================================================================
	void loadScriptFromFile (const File& file);
	void addScriptFromString (const String& text);
    void updateCurrentScriptFromString (const String& text);

    //==============================================================================
	bool loadProjectFile (const File& fileToLoad);
	bool saveProjectFile (const File& fileToSave, const bool isBundle);

    //==============================================================================
	int getLastCompiledDocumentIndex ();
	int getDocumentIndexFromFileName (const String& fileName);
	int getCurrentOpenDocumentIndex ();
	OpenDocumentComponent* getCurrentOpenDocument ();
	void setCurrentOpenDocumentIndex (const int docIndex);

    //==============================================================================
	void setDocumentHighlightLine (const int docIndex, const int lineNumber);

    //==============================================================================
    const StringArray getMenuBarNames ();
	const PopupMenu getMenuForIndex (int menuIndex,
                                     const String& menuName);
	void menuItemSelected (int menuItemID,
                           int topLevelMenuIndex);

    //==============================================================================
    ApplicationCommandTarget* getNextCommandTarget();
    void getAllCommands (Array <CommandID>& commands);
    void getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result);
    bool perform (const InvocationInfo& info);

    //==============================================================================
	void registerNewObjects (ScriptableEngine* engine);
	void debugLineCallback (ScriptableEngine* engine, asIScriptContext* context);
	void reportErrors (const String& errorType,
                       const String& errorString,
					   const String& fileName,
					   const int line);
	void reportOutput (const String& text, const int appendMode);

    //==============================================================================
    /** @internal */
	void filesDropped (const StringArray& filenames, int mouseX, int mouseY);
	/** @internal */
	void resized ();

    //==============================================================================
    juce_UseDebuggingNewOperator

protected:

	Toolbar* toolBar;
	ToolbarFactory toolFactory;

	ProjectTreeView* projectPanel;
	TabbedEditorComponent* tabbedPanel;
	TabbedSupportComponent* supportPanel;
	StatusBarComponent* statusBar;

	StretchableLayoutManager verticalLayout;
	StretchableLayoutResizerBar* verticalDividerBar;

	StretchableLayoutManager horizontalLayout;
	StretchableLayoutResizerBar* horizontalDividerBar;

	AngelJuiceWindow* mainWindow;
	OptionWindow* optionWindow;

    int lastCompiledDocument;
};


#endif // __ANGELJUICE_HEADER__

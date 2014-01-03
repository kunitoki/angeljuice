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

#include "AngelJuice.h"


//==============================================================================
AngelJuiceComponent::AngelJuiceComponent (AngelJuiceWindow* mainWindow_)
	: Component (T("AngelJuiceComponent")),
	mainWindow (mainWindow_),
	lastCompiledDocument (-1)
{
    GlobalConfig* config = GlobalConfig::getInstance();

	setWantsKeyboardFocus (true);

	// tool bar
	addAndMakeVisible (toolBar = new Toolbar());
	toolBar->setVertical (false);
	toolBar->setColour (Toolbar::backgroundColourId, ANGELJUICE_COLOR.brighter(0.4f));

	if (config->toolbarSet != String::empty)
        toolBar->restoreFromString (toolFactory, config->toolbarSet);
    else
        toolBar->addDefaultItems (toolFactory);

    // project tree
	addAndMakeVisible (projectPanel = new ProjectTreeView(this));

	// tabbel panel
	addAndMakeVisible (tabbedPanel = new TabbedEditorComponent(this));

	// support output
	addAndMakeVisible (supportPanel = new TabbedSupportComponent(this));

	// status bar
	addAndMakeVisible (statusBar = new StatusBarComponent(this));

	//- keep out in the application initialization instead
	optionWindow = new OptionWindow (this);

	// vertical layout
/* @TODO - until project component is finished
	verticalLayout.setItemLayout (0, -0.100, -0.900, -0.200);
	verticalLayout.setItemLayout (1, 3, 3, 3);
	verticalLayout.setItemLayout (2, -0.100, -0.900, -0.800);
*/
	verticalLayout.setItemLayout (0, -1.000, -1.000, -1.000);

	verticalDividerBar = new StretchableLayoutResizerBar (&verticalLayout, 1, true);
    addAndMakeVisible (verticalDividerBar);

	// horizontal layout
	horizontalLayout.setItemLayout (0, -0.100, -0.900, -0.800);
	horizontalLayout.setItemLayout (1, 3, 3, 3);
	horizontalLayout.setItemLayout (2, -0.100, -0.900, -0.200);

	horizontalDividerBar = new StretchableLayoutResizerBar (&horizontalLayout, 1, false);
    addAndMakeVisible (horizontalDividerBar);

	// @TODO - keep out in the application initialization instead
	// construct the engine
	ScriptableEngine* engine = ScriptableEngine::getInstance ();
	engine->setEngineModel (this);
	engine->addResolveFilePath (
		File::getCurrentWorkingDirectory().getFullPathName());
	engine->addResolveFilePath (
		File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getFullPathName());

	String version = "__VERSION__ ";
	version << "\"" << ANGELJUICE_VERSION << "\"";
	Preprocessor::define ((const char*) version);

	// register new types
	registerNewObjects (engine);
	// @TODO - keep out in the application initialization instead

	// set the default script
	addScriptFromString (T(""));

	// @TODO - keep out from the component
/*
	RecentlyOpenedFilesList* list = &(GlobalConfig::getInstance()->lastOpenedFiles);
	for (int i=0; i < list->getNumFiles(); i++)
		loadSourceCode (list->getFile (i));
*/
}

AngelJuiceComponent::~AngelJuiceComponent()
{
    GlobalConfig* config = GlobalConfig::getInstance();
    config->toolbarSet = toolBar->toString();

	deleteAndZero (optionWindow);

	deleteAllChildren();

	ScriptableEngine::deleteInstance ();
}

//==============================================================================
void AngelJuiceComponent::resized ()
{
	int toolBarHeight = 26;
	int statusBarHeight = 0;

	// layout toolbar bar independently
	toolBar->setBounds (0, 0, getWidth(), toolBarHeight);

	// lay out the list box and vertical divider..
    Component* hcomps[] = { 0, horizontalDividerBar, supportPanel };
    horizontalLayout.layOutComponents (hcomps, 3,
                                       3, toolBarHeight,
									   getWidth() - 6, getHeight() - toolBarHeight - statusBarHeight,
                                       true,
                                       true);

	// lay out the list box and vertical divider..
    Component* vcomps[] = { /*projectPanel, verticalDividerBar,*/ tabbedPanel };
    verticalLayout.layOutComponents (vcomps, 1, // 3,
                                     3, toolBarHeight,
									 getWidth() - 6, horizontalLayout.getItemCurrentAbsoluteSize (0),
                                     false,
                                     true);

	// @TODO - layout status bar independently
	// statusBar->setBounds (0, getHeight() - statusBarHeight, getWidth(), statusBarHeight);
}

//==============================================================================
void AngelJuiceComponent::filesDropped (const StringArray& filenames, int mouseX, int mouseY)
{
	for( int i=0; i<filenames.size(); i++ )
	{
		File droppedFile(filenames[i]);

		if (droppedFile.isDirectory())
		{
			OwnedArray<File> childFiles;
			droppedFile.findChildFiles (childFiles, File::findFiles, true);

			for (int i = 0; i < childFiles.size(); ++i)
			{
				const File foundFile (*(childFiles[i]));

				loadScriptFromFile (foundFile);
			}
		}
		else if (droppedFile.existsAsFile() )
		{
			loadScriptFromFile (droppedFile);
		}
	}
}

//==============================================================================
// returns the currently selected OpenDocumentComponent
AngelJuiceWindow* AngelJuiceComponent::getMainWindow ()
{
	return mainWindow;
}

ApplicationCommandManager* AngelJuiceComponent::getApplicationCommandManager ()
{
	return CommandManager::getInstance();
}

//==============================================================================
// returns the currently selected OpenDocumentComponent
OpenDocumentComponent* AngelJuiceComponent::getCurrentOpenDocument ()
{
	return (OpenDocumentComponent*) tabbedPanel->getCurrentContentComponent();
}

// returns the index of the currently selected OpenDocumentComponent
int AngelJuiceComponent::getCurrentOpenDocumentIndex ()
{
	return tabbedPanel->getCurrentTabIndex();
}

int AngelJuiceComponent::getDocumentIndexFromFileName (const String& fileName)
{
	for (int i = 0; i < tabbedPanel->getNumTabs(); i++)
	{
		OpenDocumentComponent* indexedDoc =
			(OpenDocumentComponent*) tabbedPanel->getTabContentComponent (i);

		if (indexedDoc &&
			indexedDoc->getDocumentFilePath().getFileName() == fileName)
		{
			return i;
		}
	}

	return -1;
}

int AngelJuiceComponent::getLastCompiledDocumentIndex ()
{
	return lastCompiledDocument;
}

void AngelJuiceComponent::setCurrentOpenDocumentIndex (const int docIndex)
{
	tabbedPanel->setCurrentTabIndex (docIndex);
}

void AngelJuiceComponent::setDocumentHighlightLine (const int docIndex, const int lineNumber)
{
	OpenDocumentComponent* indexedDoc =
		(OpenDocumentComponent*) tabbedPanel->getTabContentComponent (docIndex);

	if (indexedDoc)
		indexedDoc->highlightLine (lineNumber);
}

//==============================================================================
// load source code from a file into a new OpenDocumentComponent
void AngelJuiceComponent::loadScriptFromFile (const File& file)
{
	// selected if is already open
	int fileAtIndex = 0;
	if (file != File::nonexistent &&
		tabbedPanel->isFileAlreadyOpened (file, fileAtIndex))
	{
		tabbedPanel->setCurrentTabIndex (fileAtIndex);
		return;
	}

	// add it if is not opened
	tabbedPanel->addPanelComponentTab (file);

	// select it
	tabbedPanel->setCurrentTabIndex (tabbedPanel->getNumTabs() - 1);

	// then try to open the file in it
	OpenDocumentComponent* doc = getCurrentOpenDocument();
	if (doc != 0)
	{
		FileInputStream *io = file.createInputStream();
		if (io)
		{
			doc->setDocumentContent (io->readEntireStreamAsString());
			doc->setFirstLoad (true);
			doc->setModified (false);
			delete io;
		}
	}
}

// add source code from a string to a new OpenDocumentComponent
void AngelJuiceComponent::addScriptFromString (const String& text)
{
	tabbedPanel->addPanelComponentTab ();

	int newTabIndex = tabbedPanel->getNumTabs() - 1;

	tabbedPanel->setCurrentTabIndex (newTabIndex);

	OpenDocumentComponent* doc = getCurrentOpenDocument();
	if (doc != 0)
	{
		doc->setDocumentContent (text);
		doc->setModified (false);
	}
}

// update source code directly into the currently selected OpenDocumentComponent
void AngelJuiceComponent::updateCurrentScriptFromString (const String& text)
{
	OpenDocumentComponent* doc = getCurrentOpenDocument();
	if (doc != 0)
	{
		doc->setDocumentContent (text);
		doc->setModified (true);
	}
}

//==============================================================================
bool AngelJuiceComponent::loadProjectFile (const File& fileToLoad)
{
	XmlDocument parser (fileToLoad);
	XmlElement* e = parser.getDocumentElement();

	if (e != 0)
	{
		// @TODO - delay after check if project file is a valid file
		tabbedPanel->clearTabs ();

/*
		if( e->hasTagName (T("AngelJuiceProject")) )
		{
			XmlElement* config = e->getChildByName(T("config"));

			if (config)
			{
				XmlElement* name = config->getChildByName (T("name"));
				XmlElement* settings = config->getChildByName (T("settings"));
			}
		}
*/
		e = e->getChildByName (T("file"));
        while (e != 0)
        {
            if (e->hasTagName (T("file")))
            {
                // found a file, so use some of its attributes..
				String path = e->getStringAttribute (T("path"));
				String text = e->getAllSubText ();
				// int index = e->getIntAttribute (T("index"));

				if (path == String::empty)
				{
					addScriptFromString (text);
				}
				else
				{
					loadScriptFromFile (fileToLoad.getParentDirectory().getChildFile (path));
				}
            }
            e = e->getNextElement();
        }

		return true;
	}
	else
		supportPanel->appendOutputText ("file isn't a valid project \n");

	return false;
}

bool AngelJuiceComponent::saveProjectFile (const File& fileToSave, const bool isBundle)
{
    // create an outer XML element..
    XmlElement xmlMain (T("AngelJuiceProject"));

    // add some attributes to it..
//	xmlMain.setAttribute (T("projectName"), className->getText());
//	xmlMain.setAttribute (T("outputName"), outputName->getText());

	// configuration
	XmlElement* xmlConfig = new XmlElement (T("config"));

		XmlElement* xmlName = new XmlElement (T("name"));
		xmlName->addTextElement (T("undefined"));
		xmlConfig->addChildElement (xmlName);

	xmlMain.addChildElement (xmlConfig);

	// file list
	for (int i = 0; i < tabbedPanel->getNumTabs(); ++i)
    {
		XmlElement* xmlFile = new XmlElement (T("file"));
		xmlFile->setAttribute (T("index"), i);

		File currentFile = tabbedPanel->getDocumentByIndex (i)->getDocumentFilePath ();

		if (! isBundle && currentFile != File::nonexistent)
		{
			String relativePath = currentFile.getRelativePathFrom (fileToSave.getParentDirectory());
			xmlFile->setAttribute (T("name"), currentFile.getFileName ());
			xmlFile->setAttribute (T("path"), relativePath);
		}
		else
		{
			String scriptCode = tabbedPanel->getDocumentByIndex (i)->getTextEditor()->getText();
			xmlFile->setAttribute (T("name"), i);
			xmlFile->addTextElement (scriptCode);
		}

		xmlMain.addChildElement (xmlFile);
	}

	// you could also add as many child elements as you need to here..
	fileToSave.deleteFile();

	if (!xmlMain.writeToFile (fileToSave, String::empty))
	{
		supportPanel->appendOutputText ("cannot save project file \n");
		return false;
	}
	else
		return true;
}

//==============================================================================
// the window main menu
const StringArray AngelJuiceComponent::getMenuBarNames ()
{
    const tchar* const names[] = { T("File"), T("Edit"), T("Project"), T("Compiler"), T("View"), T("?"), 0 };

    return StringArray ((const tchar**) names);
}

// where the menu is constructed
const PopupMenu AngelJuiceComponent::getMenuForIndex (
                                 int menuIndex,
                                 const String& menuName)
{
    CommandManager* commandManager = CommandManager::getInstance();
	GlobalConfig* config = GlobalConfig::getInstance();

    PopupMenu menu;

    if (menuIndex == 0)
    {
		PopupMenu recentSubMenu;
		config->recentFiles.createPopupMenuItems (recentSubMenu,
													0x3000, // @XXX - not good to kepp tracking of baseindex
													false,
													true);

		menu.addCommandItem (commandManager, CommandIDs::fileNew);
		menu.addCommandItem (commandManager, CommandIDs::fileLoad);
		menu.addCommandItem (commandManager, CommandIDs::fileRevert);
		menu.addCommandItem (commandManager, CommandIDs::fileClone);
		menu.addSubMenu (T("Recent Files"), recentSubMenu);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::fileSave);
		menu.addCommandItem (commandManager, CommandIDs::fileSaveAs);
		menu.addCommandItem (commandManager, CommandIDs::fileSaveAll);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::fileClose);
		menu.addCommandItem (commandManager, CommandIDs::fileCloseAll);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::appClose);
    }
    else if (menuIndex == 1)
    {
		menu.addCommandItem (commandManager, CommandIDs::editUndo);
		menu.addCommandItem (commandManager, CommandIDs::editRedo);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::editCut);
		menu.addCommandItem (commandManager, CommandIDs::editCopy);
		menu.addCommandItem (commandManager, CommandIDs::editPaste);
    }
    else if (menuIndex == 2)
    {
		menu.addCommandItem (commandManager, CommandIDs::projectLoad);
		menu.addCommandItem (commandManager, CommandIDs::projectSave);
		menu.addCommandItem (commandManager, CommandIDs::projectBundle);
		menu.addCommandItem (commandManager, CommandIDs::projectClose);
	}
    else if (menuIndex == 3)
    {
		menu.addCommandItem (commandManager, CommandIDs::scriptCompile);
		menu.addCommandItem (commandManager, CommandIDs::scriptRun);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::scriptStepNext);
		menu.addCommandItem (commandManager, CommandIDs::scriptContinue);
		menu.addCommandItem (commandManager, CommandIDs::scriptAbort);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::scriptDebug);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::scriptLoadByteCode);
		menu.addCommandItem (commandManager, CommandIDs::scriptSaveByteCode);
    }
	else if (menuIndex == 4)
    {
		menu.addCommandItem (commandManager, CommandIDs::breakPointToggle);
		menu.addCommandItem (commandManager, CommandIDs::breakPointClear);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::appFullScreen);
	}
    else if (menuIndex == 5)
    {
		menu.addCommandItem (commandManager, CommandIDs::appOptions);
		menu.addSeparator();
		menu.addItem (-1,T("Help"),false); // @TODO
		menu.addCommandItem (commandManager, CommandIDs::appUpdateCheck);
		menu.addSeparator();
		menu.addCommandItem (commandManager, CommandIDs::appAboutBox);
    }

    return menu;
}

void AngelJuiceComponent::menuItemSelected (int menuItemID,
											int topLevelMenuIndex)
{
	GlobalConfig* config = GlobalConfig::getInstance();

	// handle recent files selection
	int fileID = menuItemID - 0x3000; // @XXX - not good to kepp tracking of baseindex
	if (fileID >= 0 && fileID < config->recentFiles.getNumFiles())
	{
		File fileToLoad = config->recentFiles.getFile (fileID);

		loadScriptFromFile (fileToLoad);

		supportPanel->clearOutputText ();
		supportPanel->appendOutputText ("file " + fileToLoad.getFullPathName() + " loaded\n");
	}
}

//==============================================================================
// The following methods implement the ApplicationCommandTarget interface, allowing
// this window to publish a set of actions it can perform, and which can be mapped
// onto menus, keypresses, etc.
ApplicationCommandTarget* AngelJuiceComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

// this returns the set of all commands that this target can perform..
void AngelJuiceComponent::getAllCommands (Array <CommandID>& commands)
{
    const CommandID ids[] = {
								CommandIDs::fileNew,
								CommandIDs::fileLoad,
								CommandIDs::fileSave,
								CommandIDs::fileSaveAs,
								CommandIDs::fileSaveAll,
								CommandIDs::fileClose,
								CommandIDs::fileCloseAll,
								CommandIDs::fileRevert,
								CommandIDs::fileClone,
								CommandIDs::projectLoad,
								CommandIDs::projectSave,
								CommandIDs::projectBundle,
								CommandIDs::projectClose,
								CommandIDs::editUndo,
								CommandIDs::editRedo,
								CommandIDs::editCut,
								CommandIDs::editCopy,
								CommandIDs::editPaste,
								CommandIDs::scriptCompile,
								CommandIDs::scriptDebug,
								CommandIDs::scriptRun,
								CommandIDs::scriptAbort,
								CommandIDs::scriptContinue,
								CommandIDs::scriptStepNext,
//								CommandIDs::scriptStepInto,
//								CommandIDs::scriptStepOut,
								CommandIDs::scriptLoadByteCode,
								CommandIDs::scriptSaveByteCode,
								CommandIDs::breakPointToggle,
								CommandIDs::breakPointClear,
//								CommandIDs::pluginInstall,
								CommandIDs::appOptions,
								CommandIDs::appToolbar,
								CommandIDs::appFontUpdate,
								CommandIDs::appColoursUpdate,
								CommandIDs::appFullScreen,
								CommandIDs::appUpdateCheck,
								CommandIDs::appAboutBox,
								CommandIDs::appClose
    };

    commands.addArray (ids, sizeof (ids) / sizeof (ids [0]));
}

// This method is used when something needs to find out the details about one of the commands
// that this object can perform..
void AngelJuiceComponent::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
    const int none = 0;
    const int cmd = ModifierKeys::commandModifier;
    const int shift = ModifierKeys::shiftModifier;

	ScriptableEngine* engine = ScriptableEngine::getInstance();
	OpenDocumentComponent* openDocument = getCurrentOpenDocument();

    switch (commandID)
    {
    case CommandIDs::fileNew:
		result.setInfo (T("New script"), T("Create a new empty script"), CommandCategories::file, 0);
		result.addDefaultKeypress (T('n'), cmd);
		result.setActive (!engine->isRunningScript());
        break;
    case CommandIDs::fileLoad:
        result.setInfo (T("Load script..."), T("Load a script from file"), CommandCategories::file, 0);
		result.addDefaultKeypress (T('d'), cmd);
		result.setActive (!engine->isRunningScript());
        break;
	case CommandIDs::fileSave:
        result.setInfo (T("Save script"), T("Save the script to file"), CommandCategories::file, 0);
		result.addDefaultKeypress (T('s'), cmd);
		result.setActive (openDocument != 0 &&
							!engine->isRunningScript() &&
							openDocument->hasBeenModified() /*&&
							openDocument->getDocumentFilePath() != File::nonexistent*/);
        break;
	case CommandIDs::fileSaveAs:
        result.setInfo (T("Save script as..."), T("Save the script to a new file"), CommandCategories::file, 0);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
        break;
	case CommandIDs::fileSaveAll:
        result.setInfo (T("Save all scripts"), T("Save all the scripts to a file"), CommandCategories::file, 0);
		result.addDefaultKeypress (T('f'), cmd);
		result.setActive (false);
        break;
	case CommandIDs::fileClose:
        result.setInfo (T("Close script"), T("Close the current script"), CommandCategories::file, 0);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
        break;
	case CommandIDs::fileCloseAll:
        result.setInfo (T("Close all scripts"), T("Close all the opened scripts"), CommandCategories::file, 0);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
        break;
	case CommandIDs::fileRevert:
        result.setInfo (T("Revert script"), T("Revert script from disk"), CommandCategories::file, 0);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
		result.addDefaultKeypress (T('r'), cmd);
		break;
	case CommandIDs::fileClone:
        result.setInfo (T("Clone script"), T("Clone current script"), CommandCategories::file, 0);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
		break;

	case CommandIDs::projectLoad:
		result.setInfo (T("Load Project"), T("Load a project from file"), CommandCategories::project, 0);
		result.setActive (!engine->isRunningScript());
		break;
	case CommandIDs::projectSave:
        result.setInfo (T("Save Project"), T("Save the current project to a file"), CommandCategories::project, 0);
		result.setActive (!engine->isRunningScript());
		break;
	case CommandIDs::projectBundle:
        result.setInfo (T("Bundle Project"), T("Bundle the current project to a file"), CommandCategories::project, 0);
		result.setActive (!engine->isRunningScript());
		break;

	case CommandIDs::projectClose:
        result.setInfo (T("Close Project"), T("Close the current project"), CommandCategories::project, 0);
		result.setActive (false);
		break;

	case CommandIDs::editUndo:
        result.setInfo (T("Undo"), T("Undo last action"), CommandCategories::edit, 0);
		result.addDefaultKeypress (T('z'), cmd);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
		break;
	case CommandIDs::editRedo:
        result.setInfo (T("Redo"), T("Redo last action"), CommandCategories::edit, 0);
		result.addDefaultKeypress (T('z'), cmd | shift);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
		break;
	case CommandIDs::editCut:
        result.setInfo (T("Cut"), T("Cut current selection"), CommandCategories::edit, 0);
		result.addDefaultKeypress (T('x'), cmd);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
        break;
	case CommandIDs::editCopy:
        result.setInfo (T("Copy"), T("Copy current selection"), CommandCategories::edit, 0);
		result.addDefaultKeypress (T('c'), cmd);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
        break;
	case CommandIDs::editPaste:
        result.setInfo (T("Paste"), T("Paste current clipboard content"), CommandCategories::edit, 0);
		result.addDefaultKeypress (T('v'), cmd);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
        break;

    case CommandIDs::scriptDebug:
        result.setInfo (T("Debug mode"), T("Set if the engine is to be run in debug"), CommandCategories::compiler, 0);
		result.addDefaultKeypress (KeyPress::F3Key, none);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
		result.setTicked (engine->isDebuggingScript());
        break;
	case CommandIDs::scriptCompile:
        result.setInfo (T("Compile"), T("Compile the current script"), CommandCategories::compiler, 0);
		result.addDefaultKeypress (KeyPress::F4Key, none);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
        break;
    case CommandIDs::scriptRun:
        result.setInfo (T("Run"), T("Run the current script"), CommandCategories::compiler, 0);
		result.addDefaultKeypress (KeyPress::F5Key, none);
		result.setActive (openDocument != 0 && !engine->isRunningScript());
        break;
    case CommandIDs::scriptStepNext:
        result.setInfo (T("Step next"), T("Step to the next line"), CommandCategories::compiler, 0);
		result.addDefaultKeypress (KeyPress::F10Key, none);
		result.setActive (engine->isDebuggingScript()
		                  && engine->isRunningScript()
		                  && !engine->isContinueDebugging());
        break;
    case CommandIDs::scriptAbort:
        result.setInfo (T("Abort debug"), T("Abort the current script execution"), CommandCategories::compiler, 0);
		result.addDefaultKeypress (KeyPress::F9Key, none);
		result.addDefaultKeypress (KeyPress::escapeKey, none);
		result.setActive (engine->isRunningScript());
        break;
    case CommandIDs::scriptContinue:
        result.setInfo (T("Continue debug"), T("Continue till the next breakpoint"), CommandCategories::compiler, 0);
		result.addDefaultKeypress (KeyPress::F11Key, none);
		result.setActive (engine->isDebuggingScript() && engine->isRunningScript());
        break;

	case CommandIDs::scriptLoadByteCode:
        result.setInfo (T("Load bytecode"), T("Load bytecode from file"), CommandCategories::compiler, 0);
		break;
	case CommandIDs::scriptSaveByteCode:
        result.setInfo (T("Save bytecode"), T("Save bytecode to file"), CommandCategories::compiler, 0);
		break;

	case CommandIDs::breakPointToggle:
        result.setInfo (T("Toggle breakpoint"), T("Add or remove a breakpoint in the current line"), CommandCategories::compiler, 0);
		result.addDefaultKeypress (T('b'), cmd);
		result.setActive (openDocument != 0);
		result.setTicked (openDocument != 0 &&
							openDocument->getTextEditor()->isBreakPointToggledAtCurrentLine ());
        break;
    case CommandIDs::breakPointClear:
        result.setInfo (T("Clear breakpoints"), T("Remove all breakpoints for the current file"), CommandCategories::compiler, 0);
		result.addDefaultKeypress (T('b'), cmd | shift);
		result.setActive (openDocument != 0 &&
                          openDocument->getTextEditor()->getNumBreakPoints());
        break;

	case CommandIDs::appFullScreen:
        result.setInfo (T("Full screen"), T("Set the application to be full screen"), CommandCategories::view, 0);
		result.addDefaultKeypress (KeyPress::returnKey, cmd);
		result.setTicked (mainWindow->isFullScreen());
        break;
	case CommandIDs::appOptions:
        result.setInfo (T("Options..."), T("Show preferences window"), CommandCategories::help, 0);
		result.addDefaultKeypress (T('o'), cmd);
		result.setActive (!engine->isRunningScript());
		break;
	case CommandIDs::appToolbar:
        result.setInfo (T("Setup Toolbar..."), T("Show toolbar setup window"), CommandCategories::help, 0);
//		result.addDefaultKeypress (T('o'), cmd);
		result.setActive (true);
		break;
	case CommandIDs::appFontUpdate:
		result.setInfo (T("Update font"), T("Update font in editor"), CommandCategories::help, ApplicationCommandInfo::hiddenFromKeyEditor);
		result.setActive (true);
		break;
	case CommandIDs::appColoursUpdate:
		result.setInfo (T("Update colors"), T("Update colors in editor"), CommandCategories::help, ApplicationCommandInfo::hiddenFromKeyEditor);
		result.setActive (true);
		break;
	case CommandIDs::appUpdateCheck:
        result.setInfo (T("Check for updates..."), T("Check if updates are available online"), CommandCategories::help, 0);
		result.addDefaultKeypress (T('u'), cmd);
		result.setActive (!engine->isRunningScript());
		break;
    case CommandIDs::appAboutBox:
        result.setInfo (T("About"), T("About AngelJuice"), CommandCategories::help, 0);
		result.addDefaultKeypress (T('w'), cmd);
		result.setActive (!engine->isRunningScript());
		break;
	case CommandIDs::appClose:
        result.setInfo (T("Quit"), T("Quit application"), CommandCategories::file, 0);
		result.addDefaultKeypress (T('q'), cmd);
		break;

	default:
        break;
    }
}

// this is the ApplicationCommandTarget method that is used to actually perform one of our commands..
bool AngelJuiceComponent::perform (const InvocationInfo& info)
{
	ScriptableEngine* engine = ScriptableEngine::getInstance();
	GlobalConfig* config = GlobalConfig::getInstance();
	OpenDocumentComponent* currentDocument = getCurrentOpenDocument();

    switch (info.commandID)
    {
	//---------------------------------------------------------------------------------------------
	case CommandIDs::fileNew:
		{
			tabbedPanel->addPanelComponentTab ();
			tabbedPanel->setCurrentTabIndex (tabbedPanel->getNumTabs()-1);
			break;
		}

	//---------------------------------------------------------------------------------------------
	case CommandIDs::fileLoad:
		{
			String scriptWildcard = T("*.*;*.") + GlobalConfig::getInstance()->preferredExtension;

			FileChooser myChooser (T("Load a script file..."),
									File::getCurrentWorkingDirectory(),
									scriptWildcard);

			if (myChooser.browseForFileToOpen())
			{
				supportPanel->clearOutputText ();

				File fileToLoad = myChooser.getResult();
				if (fileToLoad.existsAsFile())
				{
					// update recently files
					config->recentFiles.addFile (fileToLoad);
					config->recentFiles.removeNonExistentFiles ();

					// load it from the file
					loadScriptFromFile (fileToLoad);

					supportPanel->appendOutputText ("file " + fileToLoad.getFullPathName() + " loaded\n");
				}
				else
					supportPanel->appendOutputText ("cannot load file " + fileToLoad.getFullPathName() + "\n");
			}
			break;
		}

    case CommandIDs::fileSave:
		{
			if (currentDocument != 0)
			{
				File fileToSave = currentDocument->getDocumentFilePath();
				if (fileToSave.existsAsFile())
				{
					supportPanel->clearOutputText ();

					if (!fileToSave.replaceWithText (currentDocument->getDocumentContent()))
						supportPanel->appendOutputText ("cannot save file " + fileToSave.getFullPathName() + "\n");
					else
					{
						supportPanel->appendOutputText ("file " + fileToSave.getFullPathName() + " saved\n");

						// update document path
						currentDocument->setDocumentFilePath (fileToSave);

						// tag document
						currentDocument->setModified (false);
					}
				}
				else
				{
					invokeDirectly (CommandIDs::fileSaveAs,false);
				}
			}
			break;
		}

    case CommandIDs::fileSaveAs:
		{
			String scriptExtension = GlobalConfig::getInstance()->preferredExtension;
			String scriptWildcard = T("*.*;*.") + scriptExtension;

			FileChooser myChooser (T("Save a script file..."),
									File::getCurrentWorkingDirectory(),
									 scriptWildcard);

			if (myChooser.browseForFileToSave(true))
			{
				File fileToSave = myChooser.getResult().withFileExtension (scriptExtension);

				if (currentDocument != 0)
				{
					supportPanel->clearOutputText ();

					if (!fileToSave.replaceWithText (currentDocument->getDocumentContent()))
						supportPanel->appendOutputText ("cannot save file " + fileToSave.getFullPathName() + "\n");
					else
					{
						// update recently file list
						config->recentFiles.addFile (fileToSave);
						config->recentFiles.removeNonExistentFiles ();

						// must call this to update also tabbed button name
						tabbedPanel->updatePanelComponentFilePath (
										getCurrentOpenDocumentIndex(),
										fileToSave );

						// tag document
						currentDocument->setModified (false);

						supportPanel->appendOutputText ("file " + fileToSave.getFullPathName() + " saved\n");
					}
				}
			}
			break;
		}

    case CommandIDs::fileSaveAll:
		{
			String scriptExtension = GlobalConfig::getInstance()->preferredExtension;
			String scriptWildcard = T("*.*;*.") + scriptExtension;

			supportPanel->clearOutputText ();

			for (int i=0; i<tabbedPanel->getNumTabs(); i++)
			{
				// @TODO - check if file needs save

				OpenDocumentComponent* doc = tabbedPanel->getDocumentByIndex (i);
				if (doc != 0)
				{
					File fileToSave = doc->getDocumentFilePath();
					if (fileToSave != File::nonexistent)
					{
						if (!fileToSave.replaceWithText (doc->getDocumentContent()))
							supportPanel->appendOutputText ("cannot save file " + fileToSave.getFullPathName() + "\n");
						else
						{
							supportPanel->appendOutputText ("file " + fileToSave.getFullPathName() + " saved\n");
							doc->setModified (false);
						}
					}
					else
					{
						FileChooser myChooser (T("Save a script file..."),
												File::getCurrentWorkingDirectory(),
												scriptWildcard);

						if (myChooser.browseForFileToSave(true))
						{
							File fileToSave = myChooser.getResult().withFileExtension(scriptExtension);

							if (!fileToSave.replaceWithText (doc->getDocumentContent()))
								supportPanel->appendOutputText ("cannot save file " + fileToSave.getFullPathName() + "\n");
							else
							{
								// must call this to update also tabbed button name
								tabbedPanel->updatePanelComponentFilePath (
												getCurrentOpenDocumentIndex(),
												fileToSave );

								doc->setModified (false);

								supportPanel->appendOutputText ("file " + fileToSave.getFullPathName() + " saved\n");
							}
						}
					}
				}
			}

			break;
		}

	case CommandIDs::fileClose:
		{
			tabbedPanel->closeDocumentByIndex (getCurrentOpenDocumentIndex());
			break;
		}

    case CommandIDs::fileCloseAll:
		{
			while (tabbedPanel->getNumTabs()>0)
			{
				tabbedPanel->closeDocumentByIndex (getCurrentOpenDocumentIndex());
			}
			break;
		}

	case CommandIDs::fileRevert:
		{
			supportPanel->clearOutputText ();

			if (currentDocument)
			{
				File fileToLoad = currentDocument->getDocumentFilePath();

				FileInputStream *io = fileToLoad.createInputStream();
				if (io)
				{
					currentDocument->setDocumentContent (io->readEntireStreamAsString());
					currentDocument->setModified (false);
					delete io;

					supportPanel->appendOutputText ("file " + fileToLoad.getFullPathName() + " reloaded\n");
					break;
				}
			}

			supportPanel->appendOutputText ("cannot revert file\n");

			break;
		}

	case CommandIDs::fileClone:
		{
			if (currentDocument)
			{
				addScriptFromString (currentDocument->getTextEditor()->getText());

				supportPanel->appendOutputText ("script cloned\n");
			}

			break;
		}

	//---------------------------------------------------------------------------------------------
	case CommandIDs::projectLoad:
		{
			FileChooser myChooser (T("Load a project file..."),
									File::getCurrentWorkingDirectory(),
									"*.xml");

			if (myChooser.browseForFileToOpen())
			{
				File fileToLoad = myChooser.getResult();
				if (fileToLoad.existsAsFile())
				{
					invokeDirectly (CommandIDs::fileCloseAll, false);

					loadProjectFile (fileToLoad);
				}
			}

			break;
		}

	case CommandIDs::projectSave:
		{
			FileChooser myChooser (T("Save a project file..."),
									File::getCurrentWorkingDirectory(),
									"*.xml");

			if (myChooser.browseForFileToSave(true))
			{
				File fileToSave = myChooser.getResult().withFileExtension ("xml");

				saveProjectFile (fileToSave, false);
			}

			break;
		}

	case CommandIDs::projectBundle:
		{
			FileChooser myChooser (T("Bundle a project file..."),
                                    File::getCurrentWorkingDirectory(),
									"*.xml");

			if (myChooser.browseForFileToSave(true))
			{
				File fileToSave = myChooser.getResult().withFileExtension ("xml");

				saveProjectFile (fileToSave, true);
			}
			break;
		}

	case CommandIDs::projectClose:
		{
			break;
		}

	//---------------------------------------------------------------------------------------------
	case CommandIDs::editUndo:
		{
			if (currentDocument)
				currentDocument->getTextEditor()->doUndoRedo (false);
			break;
		}
	case CommandIDs::editRedo:
		{
			if (currentDocument)
				currentDocument->getTextEditor()->doUndoRedo (true);
			break;
		}

	case CommandIDs::editCut:
		{
			if (currentDocument)
				currentDocument->getTextEditor()->cut();
			break;
		}

	case CommandIDs::editCopy:
		{
			if (currentDocument)
				currentDocument->getTextEditor()->copy();
	        break;
		}

	case CommandIDs::editPaste:
		{
			if (currentDocument)
				currentDocument->getTextEditor()->paste();
	        break;
		}

	//---------------------------------------------------------------------------------------------
    case CommandIDs::scriptCompile:
		{
			if (currentDocument != 0)
			{
				supportPanel->clearErrors ();
				supportPanel->clearOutputText ();

				if (currentDocument->hasBeenModified())
				{
					if (currentDocument->getDocumentFilePath() != File::nonexistent)
						invokeDirectly (CommandIDs::fileSave, false);
//					else
//						invokeDirectly (CommandIDs::fileSaveAs,false);
				}

				// compile the section script
				File currentFilePath = currentDocument->getDocumentFilePath();

				String sectionName = (currentFilePath == File::nonexistent) ?
										T("untitled") : currentFilePath.getFileName();

				// add current script path to resolve path
				engine->addResolveFilePath (currentFilePath.getParentDirectory());

				// compile script
				bool compiled = engine->compileScript (currentDocument->getDocumentContent(), sectionName);

				// remove current script path to resolve path
				engine->removeResolveFilePath (currentFilePath.getParentDirectory());

				// remember this index as last compiled document
				lastCompiledDocument = getCurrentOpenDocumentIndex ();

				if (compiled)
					supportPanel->appendOutputText (T("compile success!\n"));
				else
				{
					supportPanel->appendOutputText (T("compile failed!\n"));
					supportPanel->setCurrentTabIndex (1);
				}
			}
			break;
		}

    case CommandIDs::scriptRun:
		{
			supportPanel->clearErrors ();
			supportPanel->clearOutputText ();
			supportPanel->clearCallstackText ();

			// @TODO check if file needs compile
			invokeDirectly (CommandIDs::scriptCompile,false);

			if (engine->hasFailedCompiling() ||
				engine->hasFailedPreprocessing())
				break;

			// update panels before running debug
			if (engine->isDebuggingScript ())
			{
				tabbedPanel->setDebugMode (true);

				supportPanel->appendOutputText (T("running main in DEBUG MODE...\n"));
			}
			else
				supportPanel->appendOutputText (T("running main...\n"));

			bool runWithNoErrors = engine->executeFunction (T("main"));

			// update panels after running debug
			if (engine->isDebuggingScript ())
			{
				tabbedPanel->setDebugMode (false);

				supportPanel->clearCallstackText ();
				supportPanel->clearVariablesText ();
			}

			if (runWithNoErrors)
				supportPanel->appendOutputText (T("completed\n"));
			else if (engine->isAbortingScript ())
				supportPanel->appendOutputText (T("aborted\n"));
			else
			{
				supportPanel->appendOutputText (T("completed with errors\n"));
				supportPanel->setCurrentTabIndex (1);
			}

			// update components linked to commands
//			CommandManager::getInstance()->commandStatusChanged ();

			break;
		}

    case CommandIDs::scriptAbort:
		{
			if (engine->isRunningScript())
			{
				engine->abortExecution ();

				if (mainWindow->isCurrentlyModal())
					mainWindow->exitModalState(0);

    			// update components linked to commands
//	    		CommandManager::getInstance()->commandStatusChanged ();
			}
	        break;
		}

    case CommandIDs::scriptContinue:
		{
			if (engine->isRunningScript())
			{
				engine->continueExecution ();

				if (mainWindow->isCurrentlyModal())
					mainWindow->exitModalState(0);

    			// update components linked to commands
//	    		CommandManager::getInstance()->commandStatusChanged ();
			}
			break;
		}

    case CommandIDs::scriptDebug:
		{
//			supportPanel->clearErrors ();
//			supportPanel->clearOutputText ();

			engine->debugMode = !engine->debugMode;
			if (engine->isDebuggingScript())
			{
				supportPanel->appendOutputText (T("set debug mode ON"));
			}
			else
			{
				supportPanel->appendOutputText (T("set debug mode OFF"));
			}
			break;
		}

    case CommandIDs::scriptStepNext:
		{
			// we are tunning in debug mode, and current component is modal
			if (engine->isDebuggingScript() && mainWindow->isCurrentlyModal())
				mainWindow->exitModalState(0);
	        break;
		}

	//---------------------------------------------------------------------------------------------
	case CommandIDs::scriptLoadByteCode:
		{
			FileChooser myChooser (T("Load byte code..."),
			                        File::getCurrentWorkingDirectory(),
									T("*.ajb"));
			if (myChooser.browseForFileToOpen())
			{
				File fileToLoad = myChooser.getResult();
				if (fileToLoad.existsAsFile())
				{
					engine->loadByteCode (fileToLoad);
					engine->executeFunction (T("main"));
				}
			}
			break;
		}

	case CommandIDs::scriptSaveByteCode:
		{
			FileChooser myChooser (T("Save byte code..."),
									File::getCurrentWorkingDirectory(),
									T("*.ajb"));

			if (myChooser.browseForFileToSave(true))
			{
				File fileToSave = myChooser.getResult().withFileExtension (T(".ajb"));

				if (fileToSave.existsAsFile())
					fileToSave.deleteFile();

				engine->saveByteCode (fileToSave);
			}
			break;
		}

	//---------------------------------------------------------------------------------------------
    case CommandIDs::breakPointToggle:
		{
			SyntaxTextEditor* textBox = (currentDocument) ? currentDocument->getTextEditor() : 0;
			if (textBox)
			{
				textBox->toggleBreakPointAtLine (textBox->getCaretLineNumber());
				textBox->grabKeyboardFocus ();
			}
	        break;
		}

	case CommandIDs::breakPointClear:
		{
			SyntaxTextEditor* textBox = (currentDocument) ? currentDocument->getTextEditor() : 0;
			if (textBox)
			{
				textBox->clearBreakPoints ();
				textBox->grabKeyboardFocus ();
			}
			break;
		}

	//---------------------------------------------------------------------------------------------
	case CommandIDs::appFontUpdate:
		{
			tabbedPanel->setFont (config->currentFont);
			break;
		}

	case CommandIDs::appColoursUpdate:
		{
			tabbedPanel->updateColors ();
			break;
		}

	//---------------------------------------------------------------------------------------------
	case CommandIDs::appFullScreen:
		{
			mainWindow->setFullScreen (!mainWindow->isFullScreen());
			mainWindow->toFront (true);
			break;
		}

	case CommandIDs::appOptions:
		{
			optionWindow->show ();
			break;
		}

	case CommandIDs::appToolbar:
		{
			toolBar->showCustomisationDialog (toolFactory,
                                              (Toolbar::allowIconsOnlyChoice | Toolbar::showResetToDefaultsButton));
			break;
		}

	case CommandIDs::appUpdateCheck:
		{
			config->checkForUpdates (ANGELJUICE_UPDATECHECK);
			break;
		}

    case CommandIDs::appAboutBox:
		{
			optionWindow->showAbout ();
			break;
		}

	case CommandIDs::appClose:
		{
			mainWindow->closeButtonPressed ();
			break;
		}

    default:
        return false;
    }

    return true;
}

//==============================================================================
void AngelJuiceComponent::registerNewObjects (ScriptableEngine* engine)
{
}

void AngelJuiceComponent::reportOutput (const String& text, const int appendMode)
{
	if (appendMode)
		supportPanel->appendOutputText (text);
	else
		supportPanel->replaceOutputText (text);
}

void AngelJuiceComponent::reportErrors (const String& errorType,
                                        const String& errorString,
										const String& fileName,
										const int line)
{
	supportPanel->appendErrorLine (errorType, errorString, fileName, line);
}

void AngelJuiceComponent::debugLineCallback (ScriptableEngine* engine, asIScriptContext* context)
{
	int lineNumber = engine->resolveOriginalLine (context->GetCurrentLineNumber ());
	String functionName = engine->resolveFunctionDeclaration (context->GetCurrentFunction ());
	String fileName = engine->resolveOriginalFile (context->GetCurrentLineNumber ());

	// check if the original file is open
	OpenDocumentComponent* document = getCurrentOpenDocument();

	bool debugFileStepOK = false;

	File currentDocumentFile = document->getDocumentFilePath();
	if (currentDocumentFile != File::nonexistent &&
		currentDocumentFile.getFileName() != String(fileName))
	{
		bool fileAlreadyOpen = false;

		for (int i = 0; i < tabbedPanel->getNumTabs(); i++)
		{
			OpenDocumentComponent* indexedDoc =
				(OpenDocumentComponent*) tabbedPanel->getTabContentComponent (i);

			if (indexedDoc && indexedDoc->getDocumentFilePath().getFileName() == String(fileName))
			{
				tabbedPanel->setCurrentTabIndex (i);
				document = indexedDoc;
				fileAlreadyOpen = true;
				debugFileStepOK = true;
				break;
			}
		}

		if (!fileAlreadyOpen)
		{
			// try to load file
			File fullPath = engine->findResolveFilePaths (fileName);
			if (fullPath != File::nonexistent && fullPath.existsAsFile())
			{
				loadScriptFromFile (fullPath);

				document = getCurrentOpenDocument();
				document->setDebugMode (true);

				debugFileStepOK = true;
			}
			else
			{
				supportPanel->appendOutputText ( "cannot locate \'" + fileName + "\'" );
			}
		}
	}
	else
		debugFileStepOK = true;

	// resolve if is to jump to next breakpoint
	if (engine->breakPoints.contains (lineNumber))
		engine->continueSilently = false;

	// we are doing line per line stop
	if (!engine->continueSilently)
	{
		// add callstack to callstack output
		int callstackSize = context->GetCallstackSize();

		String currentCallStack;
		currentCallStack << "[" << callstackSize << "] " <<
				functionName <<
				" : line " <<
				lineNumber << "\n";

		for (int i = callstackSize - 1; i >= 0; --i)
		{
			currentCallStack << "[" << i << "] " <<
				engine->resolveFunctionDeclaration (context->GetCallstackFunction (i)) <<
				" : line " <<
				engine->resolveOriginalLine (context->GetCallstackLineNumber (i)) << "\n";
		}
		supportPanel->replaceCallstackText (currentCallStack);

		// add variables to the variables output
		currentCallStack = T("");
		int varNumber = context->GetVarCount ();
		if (varNumber > 0)
		{
			for (int i = 0; i < varNumber; i++)
			{
				void* varPointer = context->GetVarPointer (i);

				currentCallStack <<
					"[0x" << String().toHexString((int)varPointer) << "] : " <<
					context->GetVarDeclaration (i) << " = " <<
					engine->serializeVariable (context, i) << "\n";
			}
		}
		else
			currentCallStack << "No variables on stack" << "\n";
		supportPanel->replaceVariablesText (currentCallStack);

		// highlight line & wait for key events
		if (debugFileStepOK)
		{
			document->highlightLine (lineNumber);
			document->setCurrentExecutedLine (lineNumber);
			document->grabKeyboardFocus ();
		}

		if (!mainWindow->isCurrentlyModal())
			mainWindow->runModalLoop ();
	}
}



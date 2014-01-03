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
#include "../resources/AngelJuice_Resource.h"
#include "AngelJuice_Toolbar.h"


//==============================================================================
ToolbarFactory::ToolbarFactory ()
{
}

ToolbarFactory::~ToolbarFactory()
{
}

//==============================================================================
// Each type of item a toolbar can contain must be given a unique ID. These
// are the ones we'll use in this demo.
void ToolbarFactory::getAllToolbarItemIds (Array <int>& ids)
{
    ids.add (CommandIDs::fileNew);
    ids.add (CommandIDs::fileLoad);
    ids.add (CommandIDs::fileSave);
    ids.add (CommandIDs::fileSaveAs);
    ids.add (CommandIDs::fileSaveAll);
    ids.add (CommandIDs::fileClose);
//    ids.add (CommandIDs::fileCloseAll);
//    ids.add (CommandIDs::fileClone);
    ids.add (CommandIDs::fileRevert);
    ids.add (CommandIDs::editUndo);
    ids.add (CommandIDs::editRedo);
    ids.add (CommandIDs::editCopy);
    ids.add (CommandIDs::editCut);
    ids.add (CommandIDs::editPaste);
//    ids.add (CommandIDs::scriptCompile);
    ids.add (CommandIDs::scriptDebug);
    ids.add (CommandIDs::scriptRun);
    ids.add (CommandIDs::scriptContinue);
    ids.add (CommandIDs::scriptStepNext);
//    ids.add (CommandIDs::scriptStepInto);
//    ids.add (CommandIDs::scriptStepOut);
    ids.add (CommandIDs::scriptAbort);
    ids.add (CommandIDs::appOptions);
    ids.add (CommandIDs::appToolbar);
    ids.add (CommandIDs::appUpdateCheck);
    ids.add (CommandIDs::appClose);
    // ids.add (customComboBox);

    // If you're going to use separators, then they must also be added explicitly
    // to the list.
    ids.add (separatorBarId);
    ids.add (spacerId);
    ids.add (flexibleSpacerId);
}

void ToolbarFactory::getDefaultItemSet (Array <int>& ids)
{
    ids.add (CommandIDs::fileNew);
    ids.add (CommandIDs::fileLoad);
    ids.add (CommandIDs::fileSave);
    ids.add (CommandIDs::fileSaveAs);
    ids.add (CommandIDs::fileSaveAll);
    ids.add (CommandIDs::fileClose);
//    ids.add (CommandIDs::fileCloseAll);
//		ids.add (CommandIDs::fileClone);
    ids.add (CommandIDs::fileRevert);
    ids.add (separatorBarId);
    ids.add (CommandIDs::editUndo);
    ids.add (CommandIDs::editRedo);
    ids.add (CommandIDs::editCopy);
    ids.add (CommandIDs::editCut);
    ids.add (CommandIDs::editPaste);
    ids.add (separatorBarId);
//		ids.add (CommandIDs::scriptCompile);
    ids.add (CommandIDs::scriptDebug);
    ids.add (CommandIDs::scriptRun);
    ids.add (CommandIDs::scriptStepNext);
    ids.add (CommandIDs::scriptContinue);
//		ids.add (CommandIDs::scriptStepInto);
//      ids.add (CommandIDs::scriptStepOut);
    ids.add (CommandIDs::scriptAbort);
    ids.add (separatorBarId);
    ids.add (flexibleSpacerId);
    ids.add (CommandIDs::appOptions);
    ids.add (CommandIDs::appToolbar);
    ids.add (CommandIDs::appUpdateCheck);
    ids.add (spacerId);
    ids.add (CommandIDs::appClose);
}

ToolbarItemComponent* ToolbarFactory::createItem (const int itemId)
{
    switch (itemId)
    {
    case CommandIDs::fileNew:
        return createButtonFromImage (itemId, T("new"), Resource::filenew, Resource::filenew_size, CommandIDs::fileNew);
    case CommandIDs::fileLoad:
        return createButtonFromImage (itemId, T("open"), Resource::fileopen, Resource::fileopen_size, CommandIDs::fileLoad);
    case CommandIDs::fileSave:
        return createButtonFromImage (itemId, T("save"), Resource::filesave, Resource::filesave_size, CommandIDs::fileSave);
    case CommandIDs::fileSaveAs:
        return createButtonFromImage (itemId, T("saveas"), Resource::filesaveas, Resource::filesaveas_size, CommandIDs::fileSaveAs);
    case CommandIDs::fileSaveAll:
        return createButtonFromImage (itemId, T("saveall"), Resource::filesaveall, Resource::filesaveall_size, CommandIDs::fileSaveAll);
    case CommandIDs::fileRevert:
        return createButtonFromImage (itemId, T("revert"), Resource::filerevert, Resource::filerevert_size, CommandIDs::fileRevert);
    case CommandIDs::fileClose:
        return createButtonFromImage (itemId, T("close"), Resource::fileclose, Resource::fileclose_size, CommandIDs::fileClose);

    case CommandIDs::editUndo:
        return createButtonFromImage (itemId, T("undo"), Resource::undo, Resource::undo_size, 0);
    case CommandIDs::editRedo:
        return createButtonFromImage (itemId, T("redo"), Resource::redo, Resource::redo_size, 0);
    case CommandIDs::editCut:
        return createButtonFromImage (itemId, T("cut"), Resource::editcut, Resource::editcut_size, CommandIDs::editCut);
    case CommandIDs::editCopy:
        return createButtonFromImage (itemId, T("copy"), Resource::editcopy, Resource::editcopy_size, CommandIDs::editCopy);
    case CommandIDs::editPaste:
        return createButtonFromImage (itemId, T("paste"), Resource::editpaste, Resource::editpaste_size, CommandIDs::editPaste);

    case CommandIDs::scriptDebug:
        return createButtonFromImage (itemId, T("debug"), Resource::debug, Resource::debug_size, CommandIDs::scriptDebug, true);
    case CommandIDs::scriptRun:
        return createButtonFromImage (itemId, T("run"), Resource::compilerrun, Resource::compilerrun_size, CommandIDs::scriptRun);
    case CommandIDs::scriptStepNext:
        return createButtonFromImage (itemId, T("step"), Resource::compilerstep, Resource::compilerstep_size, CommandIDs::scriptStepNext);
    case CommandIDs::scriptContinue:
        return createButtonFromImage (itemId, T("continue"), Resource::compilercontinue, Resource::compilercontinue_size, CommandIDs::scriptContinue);
    case CommandIDs::scriptAbort:
        return createButtonFromImage (itemId, T("abort"), Resource::compilerabort, Resource::compilerabort_size, CommandIDs::scriptAbort);

    case CommandIDs::appOptions:
        return createButtonFromImage (itemId, T("options"), Resource::options, Resource::options_size, CommandIDs::appOptions);
    case CommandIDs::appToolbar:
        return createButtonFromImage (itemId, T("toolbar"), Resource::fonts, Resource::fonts_size, CommandIDs::appToolbar);
    case CommandIDs::appUpdateCheck:
        return createButtonFromImage (itemId, T("update"), Resource::update, Resource::update_size, CommandIDs::appUpdateCheck);
//		case CommandIDs::appHelp:
//            return createButtonFromImage (itemId, T("help"), Resource::help, Resource::help_size, 0);
    case CommandIDs::appClose:
        return createButtonFromImage (itemId, T("quit"), Resource::quit, Resource::quit_size, CommandIDs::appClose);

//            case juceLogoButton:
//                return new ToolbarButton (itemId, T("juce!"), Drawable::createFromImageData (BinaryData::juce_png, BinaryData::juce_pngSize), 0);

//		case customComboBox:
//			return new CustomToolbarComboBox (itemId);

    default:
        break;
    }

    return 0;
}

ToolbarButton* ToolbarFactory::createButtonFromImage (const int itemId,
                                                      const String& text,
                                                      const char* imageData,
                                                      const int imageDataSize,
                                                      const int commandID,
                                                      const bool toggle)
{
    DrawableImage *icon = 0, *iconToggled = 0;

    Image* imageToSet = ImageCache::getFromMemory (imageData, imageDataSize);

    icon = new DrawableImage();
    icon->setImage (imageToSet, true);

    if (toggle)
    {
        iconToggled = new DrawableImage();
        iconToggled->setImage (imageToSet, true);
        iconToggled->setOverlayColour (Colours::red.withAlpha (0.35f));
        
        ImageCache::incReferenceCount (imageToSet);
    }

    ToolbarButton* button = new ToolbarButton (itemId, text, icon, iconToggled);

    if (commandID >= 0)
        button->setCommandToTrigger (CommandManager::getInstance(), commandID, true);
    else
        button->setEnabled (false);

    return button;
}


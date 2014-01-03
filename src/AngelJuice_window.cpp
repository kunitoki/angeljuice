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

#include "AngelJuice_config.h"
#include "AngelJuice_window.h"
#include "AngelJuice_command.h"
#include "AngelJuice.h"


//==============================================================================
AngelJuiceWindow::AngelJuiceWindow (const String& commandLine) :
	DocumentWindow (ANGELJUICE_NAME, ANGELJUICE_COLOR, DocumentWindow::allButtons, true)
{
	// get the already created manager
	CommandManager* commandManager = CommandManager::getInstance();

	// creates the main component
	AngelJuiceComponent* contentComp = new AngelJuiceComponent(this);

	// set the current content component for the window
	setContentComponent (contentComp);

	// register targets after being created
	commandManager->registerAllCommandsForTarget (contentComp);
	commandManager->setFirstCommandTarget (contentComp);

	// @XXX - reload key mappings
	XmlElement* const keys = GlobalConfig::getInstance()->configFile->getXmlValue (T("key_mappings"));
    if (keys != 0) {
        commandManager->getKeyMappings()->restoreFromXml (*keys);
        delete keys;
    }
	addKeyListener (commandManager->getKeyMappings());

	// setup specific window configuration
	setResizable (true,true);
    setResizeLimits (320, 200, 4096, 4096);
	setUsingNativeTitleBar (false);
	setTitleBarTextCentred (false);
	setTitleBarHeight (24);

	// this tells the DocumentWindow to automatically create and manage a MenuBarComponent
	// which uses our contentComp as its MenuBarModel
	setMenuBar (contentComp, 19);

    // @TODO - parse command line
}

AngelJuiceWindow::~AngelJuiceWindow ()
{
	// @XXX - save key mappings
	XmlElement* keys = CommandManager::getInstance()->getKeyMappings()->createXml (true);
	if (keys != 0) {
		GlobalConfig::getInstance()->configFile->setValue (T("key_mappings"), keys);
		delete keys;
	}
}

int AngelJuiceWindow::getDesktopWindowStyleFlags() const
{
    int flags = ComponentPeer::windowAppearsOnTaskbar;

    flags |= ComponentPeer::windowHasDropShadow;

    return flags;
}

void AngelJuiceWindow::mouseDoubleClick(const MouseEvent& e)
{
	setFullScreen (!isFullScreen());
}

void AngelJuiceWindow::closeButtonPressed ()
{
	if (isCurrentlyModal())
		CommandManager::getInstance()->invokeDirectly (CommandIDs::scriptAbort, false);

    JUCEApplication::getInstance()->systemRequestedQuit();
}


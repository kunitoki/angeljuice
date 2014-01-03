/*
  ==============================================================================

   This file is part of AngelJuice

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

  ==============================================================================
*/

#include "MainWindow.h"
#include "MainComponent.h"


//==============================================================================
MainWindow::MainWindow()
    : DocumentWindow ("angeljuice",
                      Colours::azure,
                      DocumentWindow::allButtons,
                      true)
{
    setUsingNativeTitleBar (true);

    MainComponent* contentComp = new MainComponent(this);
    //commandManager.registerAllCommandsForTarget (contentComp);
    //commandManager.registerAllCommandsForTarget (JUCEApplication::getInstance());

    // this lets the command manager use keypresses that arrive in our window to send
    // out commands
    //addKeyListener (commandManager.getKeyMappings());

    // sets the main content component for the window to be this tabbed
    // panel. This will be deleted when the window is deleted.
    setContentOwned (contentComp, false);

    // this tells the DocumentWindow to automatically create and manage a MenuBarComponent
    // which uses our contentComp as its MenuBarModel
    //setMenuBar (contentComp);

    // tells our menu bar model that it should watch this command manager for
    // changes, and send change messages accordingly.
    //contentComp->setApplicationCommandManagerToWatch (&commandManager);

    setWantsKeyboardFocus (false);
    
    setResizable (true, false); // resizability is a property of ResizableWindow
    centreWithSize (700, 600);

    setResizeLimits (400, 300, 8192, 8192);
}

MainWindow::~MainWindow()
{
    // because we've set the content comp to be used as our menu bar model, we
    // have to switch this off before deleting the content comp..
    setMenuBar (nullptr);

   #if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
    MenuBarModel::setMacMainMenu (nullptr);
   #endif

    // clearing the content component will delete the current one, and
    // that will in turn delete all its child components. You don't always
    // have to do this explicitly, because the base class's destructor will
    // also delete the content component, but in this case we need to
    // make sure our content comp has gone away before deleting our command
    // manager.
    clearContentComponent();
}

void MainWindow::closeButtonPressed()
{
    // The correct thing to do when you want the app to quit is to call the
    // JUCEApplication::systemRequestedQuit() method.

    // That means that requests to quit that come from your own UI, or from other
    // OS-specific sources (e.g. the dock menu on the mac) all get handled in the
    // same way.

    JUCEApplication::getInstance()->systemRequestedQuit();
}

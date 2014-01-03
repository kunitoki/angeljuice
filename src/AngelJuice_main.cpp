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
class AngelJuiceApplication : public JUCEApplication
{
public:

	//==============================================================================
    AngelJuiceApplication() :
		mainWindow (0)
    {}

    ~AngelJuiceApplication()
	{}

	//==============================================================================
	void initialise (const String& commandLine)
    {
		// create the default config
		GlobalConfig* config = GlobalConfig::getInstance();

		// create the command manager
		/*CommandManager* commandManager =*/ CommandManager::getInstance();

        // create the main window...
		mainWindow = new AngelJuiceWindow (commandLine);
		mainWindow->addToDesktop (ComponentPeer::windowHasDropShadow |
                                  ComponentPeer::windowAppearsOnTaskbar);
		mainWindow->centreWithSize (800, 720);
        mainWindow->setVisible (true);
		mainWindow->toFront (true);

		// improve image cache performance
        ImageCache::setCacheTimeout (30 * 1000);

		// check for updates silently
//		if (config->automaticUpdates)
//			config->checkForUpdatesSilently (ANGELJUICE_UPDATECHECK);
		// update executable if any updates found
		config->installUpdateIfFound ();
	}

    void shutdown()
    {
		deleteAndZero (mainWindow);

		// delete the command manager
		CommandManager::deleteInstance();

		// must be last thing we do cause we free the look and feel
		GlobalConfig::deleteInstance();
	}

	//==============================================================================
    void systemRequestedQuit()
    {
		quit (false);
    }

	void unhandledException (const std::exception* e,
                             const String& sourceFilename,
                             const int lineNumber)
	{
#ifndef JUCE_DEBUG
		AlertWindow::showMessageBox (AlertWindow::WarningIcon,
									 T("Unhandled Exception"),
									 T("Something bad happened to the application.") );

		quit (false);
#endif
	}

	//==============================================================================
    const String getApplicationName()
	{
		return ANGELJUICE_NAME;
	}

    const String getApplicationVersion()
	{
		return ANGELJUICE_VERSION;
	}

	//==============================================================================
    bool moreThanOneInstanceAllowed()
	{
/*
#ifndef JUCE_LINUX
*/
        return false;
/*
#else
        return true;
#endif
*/
	}

	void anotherInstanceStarted (const String& commandLine)
	{
	}

private:

	AngelJuiceWindow* mainWindow;
};


//==============================================================================
START_JUCE_APPLICATION (AngelJuiceApplication)

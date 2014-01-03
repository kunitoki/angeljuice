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

#include "../JuceLibraryCode/JuceHeader.h"

#include "Engine/ScriptableEngine.h"
#include "Interface/MainWindow.h"


//==============================================================================
class angeljuiceApplication  : public JUCEApplication,
                               public ScriptableEngineModel
{
public:
    //==============================================================================
    angeljuiceApplication() {}

    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed()       { return true; }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        // Add your application's initialisation code here..

        // engine test
        engine.setEngineModel(this);
        engine.enableDebug(true);

        File script = File::getCurrentWorkingDirectory()
                           .getChildFile("unit_test.c");
        
        if (engine.compileScript(script.loadFileAsString(), script.getFullPathName()))
        {
            engine.executeFunction("main");
        }

        // show the window
        //theMainWindow.setVisible (true);
                
        // early quit
        systemRequestedQuit();
    }

    void shutdown()
    {
        // Add your application's shutdown code here..
    }

    //==============================================================================
	void reportErrors (const String& errorType,
                       const String& errorString,
			           const String& fileName,
					   const int lineNumber)
    {
        printf("%s: %s in file %s(%d)\n",
               (const char*)errorType.toUTF8(),
               (const char*)errorString.toUTF8(),
               (const char*)fileName.toUTF8(),
               lineNumber);
    }
    
    void reportOutput (const String& message, const int appendMode)
    {
        printf("%s", (const char*)message.toUTF8());
    }
    
    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

private:
    //MainWindow theMainWindow;
    ScriptableEngine engine;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (angeljuiceApplication)

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

#ifndef __ANGELJUICE_CONFIG_HEADER__
#define __ANGELJUICE_CONFIG_HEADER__

#include "juce.h"
#include "utils/AngelJuice_CommandLineTokenizer.h"
#include "utils/AngelJuice_InternetUpdateChecker.h"
#include "utils/AngelJuice_AngelicLookAndFeel.h"

//==============================================================================
#define ANGELJUICE_NAME				T("aNGELjUICE v0.6.5")
#define ANGELJUICE_VERSION			T("0.6.5")
#define ANGELJUICE_MAJOR			0
#define ANGELJUICE_MINOR			6
#define ANGELJUICE_REVISION			5
#define ANGELJUICE_JUCE_MAX         1
#define ANGELJUICE_JUCE_MIN         44
#define ANGELJUICE_COLOR            Colours::orange.brighter(1.65f)
#define ANGELJUICE_UNTITLED         T("untitled")
#define ANGELJUICE_WELCOME          T("Welcome To AngelJuice !\n")

#ifdef JUCE_WIN32
  #define ANGELJUICE_DIRECTORY      T("angeljuice")
  #define ANGELJUICE_UPDATECHECK    T("http://www.anticore.org/juce/angeljuice/update/check_win.php")
#elif defined JUCE_LINUX
  #define ANGELJUICE_DIRECTORY      T(".angeljuice")
  #define ANGELJUICE_UPDATECHECK    T("http://www.anticore.org/juce/angeljuice/update/check_linux.php")
#elif defined JUCE_MAC
  #define ANGELJUICE_DIRECTORY      T(".angeljuice")
  #define ANGELJUICE_UPDATECHECK    T("http://www.anticore.org/juce/angeljuice/update/check_mac.php")
#endif

#if JUCE_VERSION != ((ANGELJUICE_JUCE_MAX << 16) + (ANGELJUICE_JUCE_MIN << 8))
  #error Your JUCE version isn't compatible with this version of AngelJuice !
#endif


//==============================================================================
class GlobalConfig : public InternetUpdateChecker
{
public:

	GlobalConfig ();
	~GlobalConfig ();

	// config properties
	RecentlyOpenedFilesList recentFiles;
	String preferredExtension;
	String toolbarSet;
//	File lastProjectOpened;
	Font currentFont;
	Colour textColours [8];
	Colour appColour;
	bool automaticUpdates;
	bool saveAtExit;

	// config helpers & resources
	PropertiesFile* configFile;
	AngelicLookAndFeel angelicLookAndFeel;
	Font* editorFont; // must delete this

	// implements InternetUpdateChecker
	// @TODO - make this part of the application
	void onUpdateError (const int errorReported);

	// ensure that all config is written to the file
	void flush ();

	// singleton
	juce_DeclareSingleton (GlobalConfig, true)
};



#endif // __ANGELJUICE_CONFIG_HEADER__

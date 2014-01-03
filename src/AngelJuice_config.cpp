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
#include "AngelJuice_command.h"
#include "resources/AngelJuice_Resource.h"


//==============================================================================
GlobalConfig::GlobalConfig () :
	InternetUpdateChecker (ANGELJUICE_MAJOR,ANGELJUICE_MINOR,ANGELJUICE_REVISION),
	currentFont (0),
	configFile (0),
	editorFont (0)
{
	// sets the default look and feel
	LookAndFeel::setDefaultLookAndFeel (&angelicLookAndFeel);

	// setup default font
	MemoryInputStream fontStream (Resource::proggytiny,Resource::proggytiny_size, false);
	Typeface* typeFace = new Typeface (fontStream);
	editorFont = new Font (*typeFace);
	editorFont->setHeight (10.0f);
	delete typeFace;

	// create the default configuration file...
	configFile = PropertiesFile::createDefaultAppPropertiesFile (
														T("angeljuice"),
														T("conf"),
														ANGELJUICE_DIRECTORY,
                                                        false,
                                                        -1,
                                                        PropertiesFile::ignoreCaseOfKeyNames
                                                        | PropertiesFile::storeAsXML);

	// check for automatic updates
	automaticUpdates = configFile->getBoolValue (T("automatic_updates"), false);

	// save options at exit
	saveAtExit = true;

	// setup recent file list
	recentFiles.setMaxNumberOfItems (10);
	recentFiles.restoreFromString (configFile->getValue (T("recent_files")));

    // toolbar item set
    toolbarSet = configFile->getValue (T("toolbar_Set"), String::empty);

	// setup last opened files list
//	lastOpenedFiles.setMaxNumberOfItems (256);
//	lastOpenedFiles.restoreFromString (configFile->getValue (T("last_opened_files")));

	// open last used font
	String typeFaceName = configFile->getValue (T("current_font_name"),T("default_font"));
	if (typeFaceName != T("default_font"))
	{
		currentFont = Font (typeFaceName, (float)configFile->getDoubleValue (T("current_font_height"),10.0), Font::plain);
		// @TODO - take style into account
	}
	else
		currentFont = *editorFont;

	// reload preferredExtension
	preferredExtension = configFile->getValue (T("preferred_extension"), T("ajs"));

	// set last colours from config file
	textColours [0] = Colour::fromString (configFile->getValue (T("color_0"), T("ff000000"))); // LEX_DEFAULT
	textColours [1] = Colour::fromString (configFile->getValue (T("color_1"), T("ff009900"))); // LEX_COMMENT
	textColours [2] = Colour::fromString (configFile->getValue (T("color_2"), T("ff9200cc"))); // LEX_NUMBER
	textColours [3] = Colour::fromString (configFile->getValue (T("color_3"), T("ff0000ff"))); // LEX_WORD
	textColours [4] = Colour::fromString (configFile->getValue (T("color_4"), T("ff990000"))); // LEX_WORD2
	textColours [5] = Colour::fromString (configFile->getValue (T("color_5"), T("ffff0000"))); // LEX_STRING
	textColours [6] = Colour::fromString (configFile->getValue (T("color_6"), T("ffdd9200"))); // LEX_PREPROCESSOR
	textColours [7] = Colour::fromString (configFile->getValue (T("color_7"), T("ff000000"))); // LEX_OPERATOR

	// @TODO set last app string
	// appColour = stringToColour (configFile->getValue (T("preferred_colour"), T("ajs"));
}

GlobalConfig::~GlobalConfig ()
{
	if (saveAtExit)
		flush();

	if (editorFont)
		delete editorFont;

	if (configFile)
		delete configFile;
}

void GlobalConfig::flush ()
{
	// write configuration on files
	configFile->setValue (T("automatic_updates"), automaticUpdates);
	configFile->setValue (T("recent_files"), recentFiles.toString());
//	configFile->setValue (T("last_opened_files"), lastOpenedFiles.toString()); // @TODO - find a way to update this from component
	configFile->setValue (T("current_font_name"), (currentFont == *editorFont) ? T("default_font") : currentFont.getTypefaceName());
	configFile->setValue (T("current_font_height"), currentFont.getHeight());
	configFile->getValue (T("preferred_extension"), preferredExtension);
    configFile->setValue (T("color_0"), textColours [0].toString ());
    configFile->setValue (T("color_1"), textColours [1].toString ());
    configFile->setValue (T("color_2"), textColours [2].toString ());
    configFile->setValue (T("color_3"), textColours [3].toString ());
    configFile->setValue (T("color_4"), textColours [4].toString ());
    configFile->setValue (T("color_5"), textColours [5].toString ());
    configFile->setValue (T("color_6"), textColours [6].toString ());
    configFile->setValue (T("color_7"), textColours [7].toString ());

	// flush it
	configFile->save ();
}

void GlobalConfig::onUpdateError (const int errorReported)
{
	switch (errorReported)
	{
	case InternetUpdateChecker::UnableToConnect:
		AlertWindow::showMessageBox(AlertWindow::QuestionIcon,
					                        T("Error"),
											T("Internet connection must be active for updating AngelJuice!"));
		break;
	case InternetUpdateChecker::UpdateAlreadyInstalled:
		AlertWindow::showMessageBox(AlertWindow::InfoIcon,
					                        T("Warning"),
											T("You have already the latest version!"));
		break;
	case InternetUpdateChecker::UpdateNotValid:
		AlertWindow::showMessageBox(AlertWindow::QuestionIcon,
					                        T("Error"),
											T("Cannot fetch a valid AngelJuice update!"));
		break;
	}
}

//==============================================================================
juce_ImplementSingleton (GlobalConfig)


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

#include "AngelJuice_InternetUpdateChecker.h"

#define UPDATE_TEMP_FILE_NAME "__update__"

//==============================================================================
InternetUpdateChecker::InternetUpdateChecker (const int major_, const int minor_, const int revision_) :
	majorVersion (major_),
	minorVersion (minor_),
	revision (revision_)
{
	updateNames.add (UPDATE_TEMP_FILE_NAME);
	updateNames.add (T("_update"));
	updateNames.add (T("__"));
}

InternetUpdateChecker::~InternetUpdateChecker ()
{
}

//==============================================================================
void InternetUpdateChecker::onUpdateError (const int errorReported)
{
}

bool InternetUpdateChecker::askUserForUpdate (const int major_, const int minor_, const int revision_)
{
	String message = T("Would you like to download and install version ");
	message << major_ << "." << minor_ << "." << revision_ << " ?";

	return AlertWindow::showOkCancelBox (AlertWindow::InfoIcon,T("Update Found"),message);
}

//==============================================================================
void InternetUpdateChecker::installUpdateIfFound ()
{
	String fileName = File::getSpecialLocation (File::currentExecutableFile).getFileName ();
	bool updateFound = false;

	for (int i = 0; i < updateNames.size(); i++)
	{
		String updateString = updateNames[i];

		if (fileName.indexOf (updateString) >= 0)
		{
			String fileNameWithoutUpdate = fileName.replace (updateString,String::empty,true);
			String currentDir = File::getCurrentWorkingDirectory ().getFullPathName();

			File updateFile (currentDir + "\\" + fileNameWithoutUpdate);

			File::getSpecialLocation (File::currentExecutableFile).copyFileTo (updateFile);

			updateFile.startAsProcess ();

			updateFound = true;

			JUCEApplication::getInstance()->systemRequestedQuit();

			break;
		}
	}

	if (! updateFound)
	{
		File currentDir = File::getCurrentWorkingDirectory();
		File currentFile = File::getSpecialLocation (File::currentExecutableFile);

		File outputFile (
					currentDir.getFullPathName()+"\\"+
					currentFile.getFileNameWithoutExtension()+UPDATE_TEMP_FILE_NAME+".exe" );

		if (outputFile.existsAsFile ())
			while(!outputFile.deleteFile ());
	}

}

//==============================================================================
bool InternetUpdateChecker::checkForUpdates (const String& checkUrl)
{
	String versionString;
	versionString << majorVersion << "." << minorVersion << "." << revision;

	URL updateURL (checkUrl);
	updateURL = updateURL.withParameter (T("action"),T("check"));
	updateURL = updateURL.withParameter (T("version"),versionString);

	InputStream* checkStream = updateURL.createInputStream (false); // post
	if (checkStream == 0)
	{
		onUpdateError (InternetUpdateChecker::UnableToConnect);
	}
	else
	{
		int majorUpdate = checkStream->readNextLine ().getIntValue();
		int minorUpdate = checkStream->readNextLine ().getIntValue();
		int revisionUpdate = checkStream->readNextLine ().getIntValue();
		int updateSizeInBytes = checkStream->readNextLine ().getIntValue();

		delete checkStream;

		// the user needs an update ?
		if (checkIfUpdateApplies (majorUpdate, minorUpdate, revisionUpdate))
		{
			return doRealUpdatingProcess (checkUrl,
										  majorUpdate,
										  minorUpdate,
										  revisionUpdate,
										  updateSizeInBytes);
		}
		else
		{
			onUpdateError (InternetUpdateChecker::UpdateAlreadyInstalled);
		}
	}
	
    return false;
}


bool InternetUpdateChecker::checkForUpdatesSilently (const String& checkUrl)
{
	String versionString;
	versionString << majorVersion << "." << minorVersion << "." << revision;

	URL updateURL (checkUrl);
	updateURL = updateURL.withParameter (T("action"),T("check"));
	updateURL = updateURL.withParameter (T("version"),versionString);

	InputStream* io = updateURL.createInputStream (false); // post
	if (io != 0)
	{
		int majorUpdate = io->readNextLine ().getIntValue();
		int minorUpdate = io->readNextLine ().getIntValue();
		int revisionUpdate = io->readNextLine ().getIntValue();
		int updateSizeInBytes = io->readNextLine ().getIntValue();

		delete io;

		if (checkIfUpdateApplies (majorUpdate, minorUpdate, revisionUpdate))
		{
			return doRealUpdatingProcess (checkUrl,
										  majorUpdate,
										  minorUpdate,
										  revisionUpdate,
										  updateSizeInBytes);
		}
	}
	
	return false;
}

//==============================================================================
bool InternetUpdateChecker::doRealUpdatingProcess (const String& checkUrl,
												   const int majorUpdate,
												   const int minorUpdate,
												   const int revisionUpdate,
												   const int updateSizeInBytes)
{
	// the user wants an update ?
	bool wantsUpdate = askUserForUpdate (majorUpdate, minorUpdate, revisionUpdate);
	if (wantsUpdate)
	{
		URL fileURL (checkUrl);
		fileURL = fileURL.withParameter (T("action"),T("update"));

		InputStream* fileStream = fileURL.createInputStream (true); // post
		if (fileStream == 0)
		{
			onUpdateError (InternetUpdateChecker::UnableToConnect);
			return false;
		}
		else
		{
			MemoryOutputStream memStream;
			memStream.writeFromInputStream (*fileStream,-1);
			memStream.flush();

			delete fileStream;

			// check if fetch size and downaloded one is the same
			if (updateSizeInBytes != memStream.getDataSize())
			{
				onUpdateError (InternetUpdateChecker::UpdateNotValid);
				return false;
			}

			// copy the new update file
			File currentDir = File::getCurrentWorkingDirectory();
			File currentFile = File::getSpecialLocation (File::currentExecutableFile);
			File outputFile (
					currentDir.getFullPathName()+"\\"+
					currentFile.getFileNameWithoutExtension()+UPDATE_TEMP_FILE_NAME+".exe");

			MemoryInputStream inStream (memStream.getData(),memStream.getDataSize(),false);

			// write it to a file
			FileOutputStream* outputStream = new FileOutputStream (outputFile);
			outputStream->writeFromInputStream (inStream, -1);
			delete outputStream;

			// start it as process
			outputFile.startAsProcess ();
		}

		JUCEApplication::getInstance()->systemRequestedQuit();
		return true;
	}

	return false;
}

bool InternetUpdateChecker::checkIfUpdateApplies (const int majorUpdate,
                                                  const int minorUpdate,
                                                  const int revisionUpdate)
{
    if (majorUpdate > majorVersion)
        return true;
    else if (majorUpdate == majorVersion)
    {
        if (minorUpdate > minorVersion)
            return true;
        else if (minorUpdate == minorVersion)
        {
            if (revisionUpdate > revision)
                return true;
        }
    }
    return false;
}



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

#ifndef __ANGELJUICE_INTERNETUPDATECHECKER_HEADER__
#define __ANGELJUICE_INTERNETUPDATECHECKER_HEADER__

#include "juce.h"


//==============================================================================
/**

*/
class InternetUpdateChecker
{
public:

    //==============================================================================
    enum
	{
		UnableToConnect = 0,
		UpdateNotValid,
		UpdateAlreadyInstalled
	};

	//==============================================================================
    /** Creates an internet update check manager */
	InternetUpdateChecker (const int major, const int minor, const int revision);

	/** Destructor */
	virtual ~InternetUpdateChecker ();

	//==============================================================================
	/** This callback let you do anything that should be reported to the user
	    when an error occurred

		@param errorReported	the type of error encountered
	*/
	virtual void onUpdateError (const int errorReported);

	/** This callback let you execute code for asking a user if he wants to update
		or not. It should return true if the user wants to update, false otherwise.

		@param major			the update major version
		@param minor			the update minor version
		@param revision			the update revision

		@return	true to let the engine do the update, false nothing will be done
	*/
	virtual bool askUserForUpdate (const int major, const int minor, const int revision);

	//==============================================================================
	/** This has to be called one time in your application startup,
	    mainly in the initialise function, and is responsible of handling background
		executable update after a internet fetch of a new update.
	*/
	void installUpdateIfFound ();

	/** Call this when u need to check for online updates, and ask user what to do.
	    The string that u pass must be a valid url.

		@param checkUrl			url of the script that will provide either check or
								file fetching possibility (usually a php file)

		@return	true if updates has occurred
	*/
	bool checkForUpdates (const String& checkUrl);

	/** Call this when u need to know if updates are available

		@param checkUrl			url of the script that will provide either check or
								file fetching possibility (usually a php file)

		@return	true if updates are available
	*/
	bool checkForUpdatesSilently (const String& checkUrl);

protected:

	/** @internal */
	bool doRealUpdatingProcess (const String& checkUrl,
							    const int majorUpdate,
							    const int minorUpdate,
							    const int revisionUpdate,
							    const int updateSizeInBytes);
	/** @internal */
    bool checkIfUpdateApplies (const int major,
                               const int minor,
                               const int revision);

	int majorVersion;
	int minorVersion;
	int revision;

	StringArray updateNames;
};


#endif // __ANGELJUICE_INTERNETUPDATECHECKER_HEADER__

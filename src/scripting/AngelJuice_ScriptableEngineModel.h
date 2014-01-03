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

#ifndef __ANGELJUICE_SCRIPTABLEENGINEMODEL_HEADER__
#define __ANGELJUICE_SCRIPTABLEENGINEMODEL_HEADER__

#include "../libraries/angelscript/angelscript.h"

#include "juce.h"

class ScriptableEngine;


//==============================================================================
/** Manages the engine model

    @see angelscript
*/
class ScriptableEngineModel
{
public:

	//==============================================================================
    /** Public destructor. */
    virtual ~ScriptableEngineModel()         {}

	//==============================================================================
	/** Use this to do some jobs before script sections compilation */
	virtual void preCompileCallback (ScriptableEngine* engine) {}

	/** Used in debugging mode to do some jobs every line of the script */
	virtual void debugLineCallback (ScriptableEngine* engine,
                                    asIScriptContext* context) {}

    //==============================================================================
    /** Use this to set your specific report when the compiler
	    gets messed up. Here you could write to a Log file or
		use the AlertWindow to report errors to user.
    */
	virtual void reportErrors (const String& errorType,
                               const String& errorString,
							   const String& fileName,
							   const int lineNumber) = 0;

    //==============================================================================
    /** Use this to output lines from plugins in a IDE output section.
		This is useful when u want the user defined plugins to be able to
		interact with the ide directly, outputting strings in the text
		editor debugger.
    */
	virtual void reportOutput (const String& message, const int appendMode) {}

protected:

	//==============================================================================
    /** Protected constructor. */
    ScriptableEngineModel() throw()          {}
};

#endif // __ANGELJUICE_SCRIPTABLEENGINEMODEL_HEADER__

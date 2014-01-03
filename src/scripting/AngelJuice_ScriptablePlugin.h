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

#ifndef __ANGELJUICE_SCRIPTABLEPLUGIN_HEADER__
#define __ANGELJUICE_SCRIPTABLEPLUGIN_HEADER__

#include "../libraries/angelscript/angelscript.h"
#include "../utils/AngelJuice_DynamicLibraryLoader.h"

#include "juce.h"


//==============================================================================
/** This is the function pointer for sending output to ide
*/
typedef void (*asDebuggerOutput) (const char*, const int);

/** This is the dll interface for the libraries
*/
typedef int (*PluginRegister) (asIScriptEngine*, asDebuggerOutput);
typedef int (*PluginCompile) (asIScriptEngine*);
typedef char* (*PluginVariableInfo) (asIScriptEngine*, const int, void*);


//==============================================================================
/** Manages a script to access functionality of juce

    @see angelscript
*/
class ScriptableExtensionModel
{
public:

    /** Destructor. */
	virtual ~ScriptableExtensionModel() {}

	/** Return true if the plugin is the one that the engine request */
	virtual bool identifyPlugin (const char* pluginName) = 0;

	/** Subclass this for registering objects and functions */
	virtual int registerCallback (asIScriptEngine* engine, asDebuggerOutput func) = 0;

	/** Register objects and functions with the engine */
	virtual int compileCallback (asIScriptEngine* engine) = 0;

	/** Subclass this for serialize a variable to a string */
	virtual char* variableCallback (asIScriptEngine* engine,
                                    const int typeID,
								    void* varPointer) = 0;

};


//==============================================================================
/** Manages a script to access functionality of juce

    @see angelscript
*/
class ScriptablePlugin : public ScriptableExtensionModel,
                         public DynamicLibraryLoader
{
public:

    //==============================================================================
	ScriptablePlugin (const File& fileToLoad);

	bool identifyPlugin (const char* pluginName);

	int registerCallback (asIScriptEngine* engine,
                          asDebuggerOutput func);

	int compileCallback (asIScriptEngine* engine);

	char* variableCallback (asIScriptEngine* engine,
                            const int typeID,
						    void* varPointer);

protected:

	File pluginFile;
};


//==============================================================================
/** Manages a script to access functionality of juce

    @see angelscript
*/
class ScriptableExtension : public ScriptableExtensionModel
{
public:

    //==============================================================================
	ScriptableExtension (const String& extToLoad);

	bool identifyPlugin (const char* pluginName);

	int registerCallback (asIScriptEngine* engine,
                          asDebuggerOutput func);

	int compileCallback (asIScriptEngine* engine);

	char* variableCallback (asIScriptEngine* engine,
                            const int typeID,
                            void* varPointer);

protected:

	String extensionName;
};


#endif // __ANGELJUICE_SCRIPTABLEPLUGIN_HEADER__

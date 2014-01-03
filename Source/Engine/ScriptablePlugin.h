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

#ifndef __ANGELJUICE_SCRIPTABLEPLUGIN_H_INCLUDED__
#define __ANGELJUICE_SCRIPTABLEPLUGIN_H_INCLUDED__

#include "../../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/** This is the dll/so interface for the libraries
*/
typedef int (*PluginRegister) (asIScriptEngine*);
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
	virtual int registerCallback (asIScriptEngine* engine) = 0;

	/** Register objects and functions with the engine */
	virtual int compileCallback (asIScriptEngine* engine) = 0;

	/** Subclass this for serialize a variable to a string */
	virtual char* variableCallback (asIScriptEngine* engine,
                                    const int typeID,
								    void* varPointer) = 0;

};


//==============================================================================
/** Class that all the scriptable classes will inherit

    @see angelscript
*/
class ScriptableExtensionObjectCreator
{
public:

    /** Destructor. */
	virtual ~ScriptableExtensionObjectCreator() {}

	/** Register the types */
	virtual void registerTypes(asIScriptEngine* engine) const = 0;
	
	/* Register the functions/method */
	virtual void registerFunctions(asIScriptEngine* engine) const = 0;
	
	/* This is called when stuff is recompiled */
	int compileCallback(asIScriptEngine* engine) {}
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

	int registerCallback (asIScriptEngine* engine);

	int compileCallback (asIScriptEngine* engine);

	char* variableCallback (asIScriptEngine* engine,
                            const int typeID,
                            void* varPointer);

protected:

	String extensionName;

	OwnedArray<ScriptableExtensionObjectCreator> creators;
};


//==============================================================================
/** Manages a script to access functionality of external plugins

    @see angelscript
*/
class ScriptablePlugin : public ScriptableExtensionModel
{
public:

    //==============================================================================
	ScriptablePlugin (const File& fileToLoad);

	bool identifyPlugin (const char* pluginName);

	int registerCallback (asIScriptEngine* engine);

	int compileCallback (asIScriptEngine* engine);

	char* variableCallback (asIScriptEngine* engine,
                            const int typeID,
						    void* varPointer);

protected:

	File pluginFile;
	DynamicLibrary pluginLibrary;
};


#endif // __ANGELJUICE_SCRIPTABLEPLUGIN_H_INCLUDED__

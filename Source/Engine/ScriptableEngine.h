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

#ifndef __ANGELJUICE_SCRIPTABLEENGINE_H_INCLUDED__
#define __ANGELJUICE_SCRIPTABLEENGINE_H_INCLUDED__

#include "../../JuceLibraryCode/JuceHeader.h"

#include "ScriptablePreprocessor.h"

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
    virtual ~ScriptableEngineModel() {}

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
    ScriptableEngineModel() throw() {}
};


//==============================================================================
/** Manages a script to access functionality of juce

    @see angelscript
*/
class ScriptableEngine : public Preprocessor::PragmaModel
{
public:

    //==============================================================================
    enum
    {
        SCRIPT_ENGINE_PTR = 0,
        DEBUG_OUTPUT_CALLBACK,
    };

    //==============================================================================
    /** Creates a script engine. */
    ScriptableEngine();

    /** Destructor. */
    virtual ~ScriptableEngine();

    //==============================================================================
	bool isAbortingScript() { return abortScript; }
	bool isRunningScript() { return runningScript; }
	bool isContinueDebugging() { return continueSilently; }
	bool hasFailedPreprocessing() { return preprocessFailed; }
	bool hasFailedCompiling() { return compileFailed; }

	
    //==============================================================================
    /** Enables or disables debug mode
    */
	void enableDebug(bool enable);
	bool isDebugEnabled() { return debugMode; }
	
    //==============================================================================
	/** Registers a global property to be used in the script

		This function is actually used in the main application to publish app managed
		objects and variables to the script sections.

		@param declaration				this is the declaration of the variable,
										usually something like "Object obj"
		@param object					this is a void pointer to the object the
										application is publishing
	*/
	void registerGlobalProperty(const String& declaration, void* object);

    //==============================================================================
	/** Add a script section to the engine

        You can add any number of script sections you need, but u have to
		name them with different identifier. This also compile
		the script that u added

		@param strScript				this is the script code as string
		@param strSection				this is the name of the section you are compiling
										since more session are allowed, you have to make different
										names for different sections
    */
	bool compileScript(const String& strScript,
                       const String& strSection = "main");

    //==============================================================================
    /** This check for a function defined in the script
		and execute it in the context we have created

		Actually this support only one context at time

		@param strFunction				this is the declaration of the function you
										would like to execute
    */
	bool executeFunction(const String& strFunction);

    //==============================================================================
    /** This abort the current running context

		Actually this is only useful in debug mode
    */
	void abortExecution();

    /** This let continue execution if in debug mode

		Actually this is only useful in debug mode
    */
	void continueExecution();

    //==============================================================================
	void loadByteCode(const File& file);
	void saveByteCode(const File& file);

    //==============================================================================
	void setBreakPoints(const Array<int>& breakPointsToSet)
	{
		breakPoints = breakPointsToSet;
	}

	//==============================================================================
	/** This lets you add directory to the resolve path when looking for
		files to include or a plugin library to load
	*/
	void addResolveFilePath(const File& directoryToLookInto);

	/** This lets you remove a previously added directory to the resolve path
	*/
	void removeResolveFilePath(const File& directoryToLookInto);

	/** This lets you try to locate a file in the resolve paths, useful for
		trying to locate add directory to the resolve path when looking for
		files to include or a plugin library to load
	*/
	File findResolveFilePaths(const String& fileName);

	/** It will return the original line number

	    Passing it a line number, especially when using #include preprocessor
		directives, it will resolve the original line number
	*/
	int resolveOriginalLine(const int lineNumber);

	/** It will return the original file name the line is into

	    Passing it a line number, especially when using #include preprocessor
		directives, it will resolve the original file name
	*/
	String resolveOriginalFile(const int lineNumber);

	//==============================================================================
	/** Registers the basic core types to be used in the script

		You have to call this function to actually register basic support for
		all the bindings class and functions. In alternative, you can avoid calling
		this, and instead register your own objects.
	*/
	bool registerInternalExtension(const String& extensionName);

	/** Registers a plugin passing a full path name of the desired library

		You have to call this function to actually register a user plugin library
	*/
	bool registerPluginLibrary(const String& pluginName);

    //==============================================================================
	void setEngineModel(ScriptableEngineModel* modelToNotify)	{ engineModel = modelToNotify; }
	ScriptableEngineModel* getEngineModel() const	            { return engineModel; }

    //==============================================================================
	/**@internal*/
	asIScriptEngine* getEngine() const		{ return engine; }
	/**@internal*/
	void createEngine();
	/**@internal*/
	void releaseEngine();
	/**@internal*/
	asIScriptContext* createContext();
	/**@internal*/
    int enableDebugInContext(asIScriptContext* context, bool enable);
	/**@internal*/
	String serializeVariable(asIScriptContext* context, int i);
	/**@internal*/
	void handlePragma(const Preprocessor::PragmaInstance&);
	/**@internal*/
	int getTimeout() const;

protected:
    friend class ScriptableCompilerStream;
    friend class ScriptablePreprocessorStream;
    friend class ScriptableByteCodeOutStream;
    friend class ScriptablePreprocessorFileSource;

   	static int numInstances;

	int timeOut;

	bool debugMode;

	bool warningsOn;
	bool preprocessFailed;
	bool compileFailed;

	bool runningScript;
	bool abortScript;
	bool continueSilently; // @TODO - change this to step to next breakpoint

	Array<int> breakPoints;
	StringArray resolvePaths;
	Array<void*> plugins;

	Preprocessor preprocessor;
	Preprocessor::LineNumberTranslator lineTranslator;
	void* outStreamPreprocessor;
	void* outStream;

	ScriptableEngineModel* engineModel;

	asIScriptEngine *engine;
	asIScriptModule *module;
	
//	asCJITCompiler* jit;

//	ScriptableContextManager contextManager;
};

/*

struct ScriptableContextInfo
{
	uint32 sleepUntil;
	asIScriptContext *ctx;
};

class ScriptableContextManager
{
public:

	void executeScripts()
	{
		// Check if the system time is higher than the time set for the contexts
		unsigned int time = Time::getMillisecondCounter();
		for( uint32 n = 0; n < contexts.size(); n++ )
		{
			if( contexts[n].ctx && contexts[n].sleepUntil < time )
			{
				int r = contexts[n].ctx->Execute();
				if( r != asEXECUTION_SUSPENDED )
				{
					// The context has terminated execution (for one reason or other)
					contexts[n].ctx->Release();
					contexts[n].ctx = 0;
				}
			}
		}
	}

	void abortAll()
	{
		// Abort all contexts and release them. The script engine will make
		// sure that all resources held by the scripts are properly released.
		for( uint32 n = 0; n < contexts.size(); n++ )
		{
			if( contexts[n].ctx )
			{
				contexts[n].ctx->Abort();
				contexts[n].ctx->Release();
				contexts[n].ctx = 0;
			}
		}
	}

	void addContext(asIScriptContext* ctx)
	{
		// Add the context to the list for execution
		ScriptableContextInfo info = {0, ctx};
		contexts.push_back(info);
	}

	void setSleeping(asIScriptContext *ctx, uint32 milliSeconds)
	{
		// Find the context and update the timeStamp
		// for when the context is to be continued
		for( uint32 n = 0; n < contexts.size(); n++ )
		{
			if( contexts[n].ctx == ctx )
			{
				contexts[n].sleepUntil = Time::getMillisecondCounter() + milliSeconds;
			}
		}
	}


	std::vector<ScriptableContextInfo> contexts;
};

*/

#endif // __ANGELJUICE_SCRIPTABLEENGINE_H_INCLUDED__

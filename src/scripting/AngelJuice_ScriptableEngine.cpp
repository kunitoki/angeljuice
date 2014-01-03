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

#include "../libraries/angelscript/angelscript.h"

#include "bindings/AngelJuice_AngelScriptCore.h"
#include "bindings/AngelJuice_AngelScriptString.h"
#include "bindings/AngelJuice_AngelScriptFile.h"
#include "bindings/AngelJuice_AngelScriptOpenGL.h"
#include "bindings/AngelJuice_AngelScriptImaging.h"
#include "bindings/AngelJuice_AngelScriptComponent.h"
#include "AngelJuice_ScriptableEngine.h"
#include "AngelJuice_ScriptablePlugin.h"
#include "AngelJuice_ScriptablePreprocessor.h"


//==============================================================================
juce_ImplementSingleton (ScriptableEngine);


//==============================================================================
class ScriptableCompilerStream
{
public:

	ScriptableCompilerStream (ScriptableEngine* compiler_) :
	  compiler (compiler_)
	{}

	void Write (asSMessageInfo* msg)
	{
		const char *msgType = "Info";
		if( msg->type == 0 ) msgType = "Error";
		if( msg->type == 1 ) msgType = "Warning";
		// if( msg->type == 2 ) msgType = "Info";

		String file = compiler->lineTranslator.ResolveOriginalFile (msg->row).c_str();
		int line = (int) compiler->lineTranslator.ResolveOriginalLine (msg->row);

		switch (msg->type)
		{
		case 0: // Error
			compiler->engineModel->reportErrors (msgType, msg->message, file, line);
			break;
		case 1: // Warning
			if (compiler->warningsOn)
				compiler->engineModel->reportErrors (msgType, msg->message, file, line);
			break;
		case 2: // Info
			break;
		}
	}

private:
	ScriptableEngine* compiler;
};

//==============================================================================
class ScriptablePreprocessorStream : public Preprocessor::OutStream
{
public:

	ScriptablePreprocessorStream (ScriptableEngine* compiler_) :
	  compiler (compiler_)
	{}

	void Write (const char* text,unsigned int size) {}

    void ReportErrors(const char* msgType,
                      const char* msgText,
                      const char* fileName,
                      unsigned int line)
    {
        compiler->engineModel->reportErrors (msgType, msgText, fileName, line);
        compiler->preprocessFailed = true;
    }

private:
	ScriptableEngine* compiler;
};

//==============================================================================
class ScriptableByteCodeInStream : public asIBinaryStream
{
public:

	ScriptableByteCodeInStream (ScriptableEngine* compiler_,
							    const File& byteCodeFile_) :
	  compiler (compiler_),
      byteCodeFile (byteCodeFile_)
	{
		in = byteCodeFile.createInputStream();
	}

	~ScriptableByteCodeInStream () {
		delete in;
	}

	void Write (const void *ptr, asUINT size) {}
	void Read (void *ptr, asUINT size) {
		in->read (ptr, size);
	}

private:
	ScriptableEngine* compiler;
	FileInputStream* in;
	File byteCodeFile;
};

class ScriptableByteCodeOutStream : public asIBinaryStream
{
public:

	ScriptableByteCodeOutStream (ScriptableEngine* compiler_,
							     const File& byteCodeFile_) :
	  compiler (compiler_),
      byteCodeFile (byteCodeFile_)
	{
		out = byteCodeFile.createOutputStream();
	}

	~ScriptableByteCodeOutStream () {
		delete out;
	}

	void Read (void *ptr, asUINT size) {}
	void Write (const void *ptr, asUINT size) {
		out->write (ptr, size);
	}

private:
	ScriptableEngine* compiler;
	FileOutputStream* out;
	File byteCodeFile;
};

//==============================================================================
class ScriptablePreprocessor : public Preprocessor::FileSource
{
public:

	ScriptablePreprocessor (ScriptableEngine* compiler_) :
	  compiler (compiler_)
	{}

	bool LoadFile (const std::string& filename, std::vector<char>& data)
	{
		bool loadOK = false;

		int pathToResolve = compiler->resolvePaths.size();
		for (int i=0; i<pathToResolve; i++)
		{
			String filePath = compiler->resolvePaths [i];
			filePath << T("\\") << (const char*) &filename[0];

			File fileToInclude (filePath);
			if (fileToInclude.existsAsFile())
			{
				String content = fileToInclude.loadFileAsString();
				const char* strPtr = (const char*) content;

				data.resize (content.length());

				for (int i=0; i<content.length(); i++)
					data [i] = *strPtr++;

				loadOK = true;
				break;
			}
		}

		return loadOK;
	}

private:
	ScriptableEngine* compiler;
};


//==============================================================================
/*
String PrintVariables (asIScriptContext *ctx, int stackLevel)
{
	String error;
	int numVars = ctx->GetVarCount(stackLevel);
	asIScriptEngine *engine = ctx->GetEngine();
	for( int n = 0; n < numVars; n++ )
	{
		int typeId = ctx->GetVarTypeId(n, stackLevel);
		if( typeId == engine->GetTypeIdByDecl(0, "int") )
		{
			error << ctx->GetVarDeclaration(n, 0, stackLevel)
					<< " " << *(int*)ctx->GetVarPointer(n, stackLevel) << "\n";
		}
		else if( typeId == engine->GetTypeIdByDecl(0, "String") )
		{
			error << ctx->GetVarDeclaration(n, 0, stackLevel)
					<< " " << (const char*) ((*(asString**)ctx->GetVarPointer(n, stackLevel))->buffer);
		}
	}
	return error;
}

void ScriptableExceptionCallback (asIScriptContext *context, void *param)
{
	ScriptableEngine* script = (ScriptableEngine*) param;
	asIScriptEngine *engine = context->GetEngine();

	int funcID = context->GetExceptionFunction();

	String error = "Exception: ";
	error
		<< context->GetExceptionString() << "\n"
		<< engine->GetFunctionDeclaration(funcID) << "\n";

	error += PrintVariables (context, -1);
	error += "\n";

	for( int n = 0; n < context->GetCallstackSize(); n++ )
	{
		funcID = context->GetCallstackFunction (n);

		error += engine->GetFunctionDeclaration(funcID);
		error += "\n";
		error += PrintVariables (context, n);
		error += "\n";
	}

	if (script->engineModel)
		script->engineModel->reportErrors ("runtime", error);
}
*/

//==============================================================================
void ScriptableDebuggerOutput (const char* message, const int appendMode)
{
	ScriptableEngine* script = ScriptableEngine::getInstance();
	if (script && script->engineModel)
	{
		script->engineModel->reportOutput (message, appendMode);
	}
}

//==============================================================================
void ScriptableLineCallback (asIScriptContext* context, ScriptableEngine* script)
{
	// If the time out is reached we suspend the script
	if( script->timeOut < Time::currentTimeMillis() )
		context->Suspend();
}

void ScriptableLineCallbackDebug (asIScriptContext* context, ScriptableEngine* script)
{
	if (script->engineModel)
		script->engineModel->debugLineCallback (script, context);

	context->Suspend();
}


//==============================================================================
ScriptableEngine::ScriptableEngine() :
		timeOut (0),
		debugMode (false),
		warningsOn (true),
		preprocessFailed (false),
		compileFailed (false),
		runningScript (false),
		abortScript (false),
		continueSilently (false),
		outStreamPreprocessor (0),
        outStream (0),
		engineModel (0),
		engine (0)
{
	// creates the engine
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	if( engine == 0 )
	{
		return;
	}

	// creates the common preprocessor message handler
	outStreamPreprocessor = new ScriptablePreprocessorStream (this);

	// set the common compiler message handler
	outStream = new ScriptableCompilerStream (this);
//	engine->SetCommonMessageStream ((ScriptableCompilerStream*) outStream);
	engine->SetMessageCallback (asMETHOD(ScriptableCompilerStream,Write), outStream, asCALL_THISCALL);

    // allow unsafe references
    // engine->SetEngineProperty (asEP_ALLOW_UNSAFE_REFERENCES, 1);

	// register pragmas
	Preprocessor::registerPragma ("engine", this);
	Preprocessor::registerPragma ("warnings", this);
	Preprocessor::registerPragma ("plugin", this);
	Preprocessor::registerPragma ("extension", this);

	// add some predefined resolvePaths
//	resolvePaths.add ( File::getCurrentWorkingDirectory().getFullPathName() );
//	resolvePaths.add ( File::getCurrentApplicationFile().getParentDirectory().getFullPathName() );
}

ScriptableEngine::~ScriptableEngine()
{
	for (int i=0; i<plugins.size(); i++)
	{
		ScriptablePlugin* plug =
			(ScriptablePlugin*) plugins.getUnchecked (i);
		delete plug;
	}
	plugins.clear ();

	if (engine)
		engine->Release();

	if (outStreamPreprocessor)
		delete (ScriptablePreprocessorStream*) outStreamPreprocessor;

	if (outStream)
		delete (ScriptableCompilerStream*) outStream;
}

//==============================================================================
void ScriptableEngine::resetEngine ()
{
	// release the engine
	if (engine)
		engine->Release ();

	// clear plugins
	for (int i=0; i<plugins.size(); i++)
	{
		ScriptablePlugin* plug =
			(ScriptablePlugin*) plugins.getUnchecked (i);
		delete plug;
	}
	plugins.clear ();

	// recreates the engine
	engine = asCreateScriptEngine (ANGELSCRIPT_VERSION);
	if( engine == 0 )
		return;

	engine->SetMessageCallback (asMETHOD(ScriptableCompilerStream,Write), outStream, asCALL_THISCALL);

	debugMode = false;
	runningScript = false;
	abortScript = false;
	continueSilently = false;
	preprocessFailed = false;
	compileFailed = false;
}


//==============================================================================
void ScriptableEngine::setDefaultContextStackSize (const int initialSize, const int maxSize)
{
	engine->SetDefaultContextStackSize (initialSize, maxSize);
}

//==============================================================================
void ScriptableEngine::registerGlobalProperty(const String& declaration, void* object)
{
	engine->RegisterGlobalProperty ((const char*)declaration,object);
}

//==============================================================================
bool ScriptableEngine::compileScript (const String& strScript, const String& strSection)
{
	if (!engine || !engineModel)
		return false;

	compileFailed = false;
	preprocessFailed = false;

	// do garbage collect
	engine->GarbageCollect (true);

	// remove carriage returns if any...
	String preScript = strScript.replaceCharacter('\r','\n');
	preScript += T(' '); // hack if the script is empty

	// do preprocessing
	Preprocessor::VectorOutStream outVector;
	ScriptablePreprocessor preprocessorObject (this);
	Preprocessor::preprocess (	(const char*) strSection,
								(const char*) preScript,
								preprocessorObject,
								outVector,
								*((ScriptablePreprocessorStream*)outStreamPreprocessor),
								&lineTranslator);
	if (preprocessFailed)
		return false;

	// call the pre compiler callback
	engineModel->preCompileCallback (this);

	// call the plugin pre compiler callback
	for (int i=0; i<plugins.size(); i++)
	{
		ScriptableExtensionModel* plug =
			(ScriptableExtensionModel*) plugins.getUnchecked (i);
		plug->compileCallback (engine);
	}

	// add a script section
	int r = engine->AddScriptSection(0, (const char*) strSection, outVector.data(), outVector.size(), 0);
	if( r < 0 )
	{
		compileFailed = true;
		return false;
	}

	// build the script
	r = engine->Build(0);
	if( r < 0 )
	{
		compileFailed = true;
		return false;
	}

	return true;
}

//==============================================================================
asIScriptContext* ScriptableEngine::createContext()
{
	asIScriptContext* context = engine->CreateContext();

	if( context != 0 )
	{
		int r;
		if (debugMode)
			r = context->SetLineCallback (asFUNCTION(ScriptableLineCallbackDebug), this, asCALL_CDECL);
		else
			r = context->SetLineCallback (asFUNCTION(ScriptableLineCallback), this, asCALL_CDECL);
		if( r < 0 )
		{
			context->Release();
			context = 0;
		}

		// context->SetExceptionCallback(asFUNCTION(ScriptableExceptionCallback), this, asCALL_CDECL);
	}

	return context;
}

//==============================================================================
bool ScriptableEngine::executeFunction (const String& strFunction)
{
	if (!engine || !engineModel || compileFailed)
		return false;

	// get the function to execute
	int functionID = engine->GetFunctionIDByName(0, (const char*)strFunction);
	if( functionID < 0 )
	{
		engineModel->reportErrors (T("runtime"), String("Cannot find function ") + strFunction, T(""), -1);
		return false;
	}

	// creates the context
	asIScriptContext* context = createContext();
	if( context == 0 )
	{
		engineModel->reportErrors (T("runtime"), T("Cannot create context for execution"), T(""), -1);
		return false;
	}

	// prepare the function
	int r = context->Prepare (functionID);
	if( r < 0 )
	{
		engineModel->reportErrors (T("runtime"), T("Cannot prepare function ececution"), T(""), -1);
		return false;
	}

	bool returnValue = false;
	bool exitLoop = false;

	runningScript = true;
	abortScript = false;
	continueSilently = true;

	while (!abortScript)
	{
//	    try
	    {
    		timeOut = Time::getMillisecondCounter() + 100; // 100
    		r = context->Execute();
	    }
//	    catch(...)
//	    {
//	        r = asEXECUTION_EXCEPTION;
//      }

		switch(r)
		{
		case asEXECUTION_FINISHED:
			{
			returnValue = true;
			exitLoop = true;
			break;
			}
		case asEXECUTION_SUSPENDED:
			{
			MessageManager::getInstance()->dispatchPendingMessages ();
			break;
			}
		case asEXECUTION_ABORTED:
			{
			engineModel->reportErrors (T("Exception"),
									   T("The script has timed out."),
									   resolveOriginalFile (context->GetExceptionLineNumber()),
									   resolveOriginalLine (context->GetExceptionLineNumber()) );
			exitLoop = true;
			break;
			}
		case asEXECUTION_EXCEPTION:
			{
			int funcID = context->GetExceptionFunction();

			engineModel->reportErrors (T("Exception"),
										resolveFunctionDeclaration (funcID) + " : " +context->GetExceptionString(),
										resolveOriginalFile (context->GetExceptionLineNumber()),
										resolveOriginalLine (context->GetExceptionLineNumber()) );

			exitLoop = true;
			break;
			}
		default:
			exitLoop = true;
			break;
		}

		if (exitLoop)
			break;
	}

/*
//	Retrieve the return value from the context
	float returnValue = context->GetReturnFloat();
	cout << "The script function returned: " << returnValue << endl;
	returnValue = true;
*/

	context->Release();

	runningScript = false;

	return returnValue;
}

bool ScriptableEngine::executeString (const String& strScript)
{
	if (!engine)
		return false;

	int r = engine->ExecuteString (0, (const char*)strScript);
	if( r < 0 )
	{
		return false;
	}
	return true;
}

//==============================================================================
void ScriptableEngine::abortExecution ()
{
	// @XXX - hack for the component bindings
	asComponentManager::getInstance()->releaseComponents();

	abortScript = true;
}

void ScriptableEngine::continueExecution ()
{
	continueSilently = true;
}

//==============================================================================
void ScriptableEngine::loadByteCode (const File& file)
{
	ScriptableByteCodeInStream in (this, file);

	engine->LoadByteCode (0, &in);
}

void ScriptableEngine::saveByteCode (const File& file)
{
	if (compileFailed)
		return;

	ScriptableByteCodeOutStream out (this, file);

	engine->SaveByteCode (0, &out);
}


//==============================================================================
int ScriptableEngine::resolveOriginalLine (const int lineNumber)
{
	return lineTranslator.ResolveOriginalLine (lineNumber);
}

String ScriptableEngine::resolveOriginalFile (const int lineNumber)
{
	return String ((const char*) lineTranslator.ResolveOriginalFile (lineNumber).c_str());
}

String ScriptableEngine::resolveFunctionDeclaration (const int functionID)
{
	return String (engine->GetFunctionDeclaration (functionID));
}

String ScriptableEngine::serializeVariable (asIScriptContext* context, const int variableNumber)
{
	void* varPointer = context->GetVarPointer (variableNumber);
	int typeID = context->GetVarTypeId (variableNumber);
	String typeDecl = engine->GetTypeDeclaration (typeID);

	if (typeDecl == T("bool"))
	{
		return String ((int)*(bool*)(varPointer));
	}
	else if (typeDecl == T("int8") ||
		typeDecl == T("int16") ||
		typeDecl == T("int32") ||
		typeDecl == T("int"))
	{
		return String (*(int*)(varPointer));
	}
	else if (typeDecl == T("uint8") ||
		typeDecl == T("uint16") ||
		typeDecl == T("uint32") ||
		typeDecl == T("uint"))
	{
		return String ((int)*(unsigned int*)(varPointer));
	}
	else if (typeDecl == T("float"))
	{
		return String (*(float*)(varPointer));
	}
	else if (typeDecl == T("double"))
	{
		return String (*(double*)(varPointer));
	}
	else
	{
		char* buffer = 0;
		for (int i=0; i<plugins.size(); i++)
		{
			ScriptableExtensionModel* plug =
				(ScriptableExtensionModel*) plugins.getUnchecked (i);

			buffer = plug->variableCallback (engine, typeID, varPointer);

			if (buffer != 0)
			{
				String varValue = buffer;
				free (buffer);
				return varValue;
			}
		}
	}

	return T("???");
}

//==============================================================================
void ScriptableEngine::addResolveFilePath (const File& directoryToLookInto)
{
	jassert (!directoryToLookInto.existsAsFile())

//	if (directoryToLookInto.existsAsFile())
//		resolvePaths.add (directoryToLookInto.getParentDirectory().getFullPathName());
//	else
		resolvePaths.add (directoryToLookInto.getFullPathName());
}

void ScriptableEngine::removeResolveFilePath (const File& directoryToLookInto)
{
	jassert (!directoryToLookInto.existsAsFile())

//	if (directoryToLookInto.existsAsFile())
//		resolvePaths.removeString (directoryToLookInto.getParentDirectory().getFullPathName());
//	else
		resolvePaths.removeString (directoryToLookInto.getFullPathName());
}

File ScriptableEngine::findResolveFilePaths (const String& fileName)
{
	File fileFound = File::nonexistent;

	int pathToResolve = resolvePaths.size();
	for (int i=0; i<pathToResolve; i++)
	{
		String filePath = resolvePaths [i];
		filePath << T("\\") << fileName;

		File fileToLoad (filePath);
		if (fileToLoad.existsAsFile())
		{
			fileFound = fileToLoad;
			break;
		}
	}

	return fileFound;
}

//==============================================================================
bool ScriptableEngine::registerInternalExtension (const String& extensionName)
{
	// check if is already there
	for (int i=0; i<plugins.size(); i++)
	{
		ScriptableExtensionModel* plug =
			(ScriptableExtensionModel*) plugins.getUnchecked (i);

		if (plug->identifyPlugin ((const char*) extensionName))
			return true; // already registered
	}

	try
	{
		// otherwise add it
		ScriptableExtension* plugin = new ScriptableExtension (extensionName);

		int returnValue = plugin->registerCallback (engine, &ScriptableDebuggerOutput);

		if (returnValue >= 0)
			plugins.add (plugin);
	}
	catch (...)
	{
		String errorLoadingPlugin = T("Error when registering \"");
		errorLoadingPlugin << extensionName << T("\" library !");

		if (engineModel)
			engineModel->reportErrors (T("compiler"), errorLoadingPlugin, T(""), -1);

		return false; // error occurred
	}

	return true;
}

//==============================================================================
bool ScriptableEngine::registerPluginLibrary (const String& pluginName)
{
	// check if is already there
	for (int i=0; i<plugins.size(); i++)
	{
		ScriptableExtensionModel* plug =
			(ScriptableExtensionModel*) plugins.getUnchecked (i);

		if (plug->identifyPlugin ((const char*) pluginName))
			return true; // already registered
	}

	try
	{
		// otherwise add it
		ScriptablePlugin* plugin = new ScriptablePlugin (pluginName);

		int returnValue = plugin->registerCallback (engine, &ScriptableDebuggerOutput);

		if (returnValue >= 0)
			plugins.add (plugin);
	}
	catch (...)
	{
		String errorLoadingPlugin = T("Error when registering \"");
		errorLoadingPlugin << pluginName << T("\" library !");

		if (engineModel)
			engineModel->reportErrors (T("compiler"), errorLoadingPlugin, T(""), -1);

		return false; // error occurred
	}

	return true;
}

//==============================================================================
void ScriptableEngine::handlePragma (const PragmaInstance& pragma)
{
	if (pragma.name == "engine")
	{
		if (pragma.text == "reset")
			resetEngine ();
	}
	else if (pragma.name == "warnings")
	{
		if (pragma.text == "on")
			warningsOn = true;
		else if (pragma.text == "off")
			warningsOn = false;
	}
	else if (pragma.name == "extension")
	{
		registerInternalExtension (T("core"));
	}
	else if (pragma.name == "plugin")
	{
		bool loadOK = false;

		int pathToResolve = resolvePaths.size();
		for (int i = 0; i < pathToResolve; i++)
		{
			String filePath = resolvePaths [i];
			filePath << T("\\") << (const char*) &(pragma.text[0]);

			File pluginFile (filePath);
			if (pluginFile.existsAsFile())
			{
				loadOK = registerPluginLibrary (pluginFile.getFullPathName());
				break;
			}
		}
	}

}

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

//#include "bindings/AngelScriptCore.h"
#include "Bindings/AngelScriptString.h"
//#include "bindings/AngelScriptFile.h"
//#include "bindings/AngelScriptOpenGL.h"
//#include "bindings/AngelScriptImaging.h"
//#include "bindings/AngelScriptComponent.h"

#include "ScriptableEngine.h"
#include "ScriptablePlugin.h"
#include "ScriptablePreprocessor.h"


//==============================================================================

class ScriptableCompilerStream
{
public:

	ScriptableCompilerStream (ScriptableEngine* engine_) :
	  engine(engine_)
	{}

	void Write (asSMessageInfo* msg)
	{
		const char *msgType = "Info";
		if( msg->type == 0 ) msgType = "Error";
		if( msg->type == 1 ) msgType = "Warning";
		if( msg->type == 2 ) msgType = "Info";

		const String file = engine->resolveOriginalFile(msg->row);
		const int line = engine->resolveOriginalLine(msg->row);

		switch (msg->type)
		{
		case 0: // Error
		    if (engine->getEngineModel())
			    engine->getEngineModel()->reportErrors(msgType, msg->message, file, line);
			break;
		case 1: // Warning
			if (engine->getEngineModel() && engine->warningsOn) // TODO - protected
				engine->getEngineModel()->reportErrors(msgType, msg->message, file, line);
			break;
		case 2: // Info
		    // TODO
		    //if (engine->getEngineModel())
			//    engine->getEngineModel()->reportErrors(msgType, msg->message, file, line);
			break;
		}
	}

private:
	ScriptableEngine* engine;
};


//==============================================================================

class ScriptableByteCodeInStream : public asIBinaryStream
{
public:

	ScriptableByteCodeInStream (ScriptableEngine* engine_,
							    const File& byteCodeFile_) :
	  engine(engine_),
      byteCodeFile(byteCodeFile_)
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
	ScriptableEngine* engine;
	FileInputStream* in;
	File byteCodeFile;
};

class ScriptableByteCodeOutStream : public asIBinaryStream
{
public:

	ScriptableByteCodeOutStream (ScriptableEngine* engine_,
							     const File& byteCodeFile_) :
	  engine(engine_),
      byteCodeFile(byteCodeFile_)
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
	ScriptableEngine* engine;
	FileOutputStream* out;
	File byteCodeFile;
};


//==============================================================================

class ScriptablePreprocessorStream : public Preprocessor::OutStream
{
public:

	ScriptablePreprocessorStream (ScriptableEngine* engine_) :
	  engine(engine_)
	{}

	void Write (const char* text,unsigned int size) {}

    void ReportErrors(const char* msgType,
                      const char* msgText,
                      const char* fileName,
                      unsigned int line)
    {
        if (engine->getEngineModel())
            engine->getEngineModel()->reportErrors(msgType, msgText, fileName, line);

        engine->preprocessFailed = true; // TODO - protected
    }

private:
	ScriptableEngine* engine;
};


class ScriptablePreprocessorFileSource : public Preprocessor::FileSource
{
public:

	ScriptablePreprocessorFileSource (ScriptableEngine* engine_) :
	  engine(engine_)
	{}

	bool LoadFile (const std::string& filename, std::vector<char>& data)
	{
		bool loadOK = false;

		int pathToResolve = engine->resolvePaths.size(); // TODO - protected
		for (int i = 0; i < pathToResolve; ++i)
		{
			String filePath = engine->resolvePaths[i]; // TODO - protected
			filePath << "\\" << (const char*)&filename[0];

			File fileToInclude(filePath);
			if (fileToInclude.existsAsFile())
			{
				String content = fileToInclude.loadFileAsString();
				const char* strPtr = (const char*)content.toUTF8();

				data.resize(content.length());

				for (int k = 0; k < content.length(); ++k)
					data[k] = *strPtr++;

				loadOK = true;
				break;
			}
		}

		return loadOK;
	}

private:
	ScriptableEngine* engine;
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
void ScriptableLineCallback (asIScriptContext* context, ScriptableEngine* engine)
{
	// If the time out is reached we suspend the script
	if (engine->getTimeout() < Time::currentTimeMillis())
		context->Suspend();
}

void ScriptableLineCallbackDebug (asIScriptContext* context, ScriptableEngine* engine)
{
	if (engine->getEngineModel())
		engine->getEngineModel()->debugLineCallback(engine, context);

	context->Suspend();
}


//==============================================================================

//------------------------------------------------------------------------------

int ScriptableEngine::numInstances = 0;


//------------------------------------------------------------------------------

ScriptableEngine::ScriptableEngine()
  : timeOut (0),
	debugMode (false),
	warningsOn (true),
	preprocessFailed (false),
	compileFailed (false),
	runningScript (false),
	abortScript (false),
	continueSilently (false),
	outStreamPreprocessor (nullptr),
    outStream (nullptr),
	engineModel (nullptr),
	engine (nullptr),
	module (nullptr)
	//, jit (nullptr)
{
    // prepare for multithread environment
    if (numInstances++ == 0)
    {
        asPrepareMultithread();
    }
    
	// register pragmas
	preprocessor.registerPragma("engine", this);
	preprocessor.registerPragma("debug", this);
	preprocessor.registerPragma("warnings", this);
	preprocessor.registerPragma("plugin", this);
	preprocessor.registerPragma("extension", this);

	// add some predefined resolvePaths
    // resolvePaths.add(File::getCurrentWorkingDirectory().getFullPathName());
    // resolvePaths.add(File::getCurrentApplicationFile().getParentDirectory().getFullPathName());

    // create the engine
    createEngine();
}


//------------------------------------------------------------------------------

ScriptableEngine::~ScriptableEngine()
{
    // release the engine
    releaseEngine();

    // release multithread environment
    if (--numInstances == 0)
    {
        asUnprepareMultithread();
    }
}


//------------------------------------------------------------------------------

void ScriptableEngine::createEngine()
{
    // release the engine
    releaseEngine();

	// recreates the engine
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	if (engine == nullptr)
    {
		return;
    }
    
 	// saves a pointer to us
	engine->SetUserData(this, SCRIPT_ENGINE_PTR);

	// creates the common preprocessor message handler
	outStreamPreprocessor = new ScriptablePreprocessorStream(this);

	// set the common compiler message handler
	outStream = new ScriptableCompilerStream(this);
    engine->SetMessageCallback(asMETHOD(ScriptableCompilerStream, Write), outStream, asCALL_THISCALL);

    // set default engine properties
    engine->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES, true);

    // create the jit compiler
    //jit = new asCJITCompiler(0);
    //engine->SetEngineProperty(asEP_INCLUDE_JIT_INSTRUCTIONS, 1);
    //engine->SetJITCompiler(jit);

	// recreate the module
	module = engine->GetModule("module", asGM_ALWAYS_CREATE);
    
	// reset variables
	debugMode = false;
	runningScript = false;
	abortScript = false;
	continueSilently = false;
	preprocessFailed = false;
	compileFailed = false;
}


//------------------------------------------------------------------------------

void ScriptableEngine::releaseEngine()
{
	for (int i = 0; i < plugins.size(); ++i)
	{
		ScriptablePlugin* plug =
			(ScriptablePlugin*)plugins.getUnchecked(i);
		delete plug;
	}
	plugins.clear ();

	if (engine)
    {
		engine->Release();

		engine = nullptr;
		module = nullptr;
    }

  	//if (jit)
    //    deleteAndZero(jit);

	if (outStreamPreprocessor) {
		delete (ScriptablePreprocessorStream*)outStreamPreprocessor;
		outStreamPreprocessor = nullptr;
    }

	if (outStream) {
		delete (ScriptableCompilerStream*)outStream;
		outStream = nullptr;
	}
}


//------------------------------------------------------------------------------

void ScriptableEngine::enableDebug(bool enable)
{
    if (debugMode != enable)
    {
        debugMode = enable;

        asIScriptContext* context = asGetActiveContext();
        if (runningScript && context)
        {
            int r = enableDebugInContext(context, debugMode);
		    //if (r < 0)
		    //{
		    //	context->Release();
		    //	context = nullptr;
		    //}
        }
    }
}


//------------------------------------------------------------------------------

asIScriptContext* ScriptableEngine::createContext()
{
    jassert(engine != nullptr);
    
	asIScriptContext* context = engine->CreateContext();
	if (context != nullptr)
	{
		int r = enableDebugInContext(context, debugMode);
		if (r < 0)
		{
			context->Release();
			context = nullptr;
		}

		// context->SetExceptionCallback(asFUNCTION(ScriptableExceptionCallback), this, asCALL_CDECL);
	}

	return context;
}


//------------------------------------------------------------------------------

int ScriptableEngine::enableDebugInContext(asIScriptContext* context, bool enable)
{
    jassert(context != nullptr);
    
    if (enable)
    {
		return context->SetLineCallback(asFUNCTION(ScriptableLineCallbackDebug), this, asCALL_CDECL);
    }
    else
    {
		return context->SetLineCallback(asFUNCTION(ScriptableLineCallback), this, asCALL_CDECL);
    }
}


//------------------------------------------------------------------------------

void ScriptableEngine::registerGlobalProperty(const String& declaration, void* object)
{
    jassert(engine != nullptr);
    
	engine->RegisterGlobalProperty((const char*)declaration.toUTF8(), object);
}


//------------------------------------------------------------------------------

bool ScriptableEngine::compileScript(const String& strScript, const String& strSection)
{
    jassert(engine != nullptr);
    jassert(module != nullptr);

	compileFailed = false;
	preprocessFailed = false;

	// do garbage collect
	engine->GarbageCollect(true);

	// remove carriage returns if any...
	String preScript = strScript + " ";
	// TODO - check if we need replaceCharacter('\r','\n') anymore ?

	// do preprocessing
	Preprocessor::VectorOutStream outVector;
	ScriptablePreprocessorFileSource preprocessorFileSource(this);
	preprocessor.preprocess(strSection,
                            preScript,
                            preprocessorFileSource,
							outVector,
							*((ScriptablePreprocessorStream*)outStreamPreprocessor),
							&lineTranslator);
	if (preprocessFailed)
		return false;

	// call the pre compiler callback
	if (engineModel)
	    engineModel->preCompileCallback (this);

	// call the plugin pre compiler callback
	for (int i = 0; i < plugins.size(); i++)
	{
		ScriptableExtensionModel* plug =
			(ScriptableExtensionModel*)plugins.getUnchecked(i);
		plug->compileCallback(engine);
	}

	// add a script section
	int r = module->AddScriptSection((const char*)strSection.toUTF8(), outVector.data(), outVector.size(), 0);
	if (r < 0)
	{
		compileFailed = true;
		return false;
	}

	// build the script
	r = module->Build();
	if (r < 0)
	{
		compileFailed = true;
		return false;
	}

	// finalize jit compiler
	//jit->finalizePages();
	
	return true;
}


//------------------------------------------------------------------------------

bool ScriptableEngine::executeFunction(const String& strFunction)
{
    jassert(engine != nullptr);
    jassert(module != nullptr);

    if (compileFailed)
		return false;

	// get the function to execute
	asIScriptFunction* function = module->GetFunctionByName((const char*)strFunction.toUTF8());
	if (function == nullptr)
	{
	    if (engineModel)
		    engineModel->reportErrors ("runtime", String("Cannot find function ") + strFunction, "", -1);
		return false;
	}

	// creates the context
	asIScriptContext* context = createContext();
	if (context == nullptr)
	{
	    if (engineModel)
		    engineModel->reportErrors ("runtime", "Cannot create context for execution", "", -1);
		return false;
	}

	// prepare the function
	int r = context->Prepare(function);
	if (r < 0)
	{
	    if (engineModel)
		    engineModel->reportErrors ("runtime", "Cannot prepare function ececution", "", -1);
		return false;
	}

	bool returnValue = false;
	bool exitLoop = false;
	int timeoutDelta = 500; // milliseconds of continued execution

	runningScript = true;
	abortScript = false;
	continueSilently = true;

	while(! abortScript)
	{
//	    try
//	    {

   		timeOut = Time::getMillisecondCounter() + timeoutDelta;
   		r = context->Execute();

//	    }
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
			    MessageManager::getInstance()->runDispatchLoopUntil(1);
			    break;
			}
		case asEXECUTION_ABORTED:
			{
    	        if (engineModel)
			        engineModel->reportErrors("Exception",
									          "The script has timed out.",
									          resolveOriginalFile(context->GetExceptionLineNumber()),
									          resolveOriginalLine(context->GetExceptionLineNumber()));
			    exitLoop = true;
			    break;
			}
		case asEXECUTION_EXCEPTION:
			{
			    asIScriptFunction* func = context->GetExceptionFunction();
			    if (func)
			    {
			        if (engineModel)
			            engineModel->reportErrors("Exception",
										          String(func->GetDeclaration()) + " : " + String(context->GetExceptionString()),
										          resolveOriginalFile(context->GetExceptionLineNumber()),
										          resolveOriginalLine(context->GetExceptionLineNumber()));
			    }

			    exitLoop = true;
			    break;
			}
		default:
		    {
			    exitLoop = true;
			    break;
		    }
		}

		if (exitLoop)
			break;
	}

/*
    // Retrieve the return value from the context
	float returnValue = context->GetReturnFloat();
	cout << "The script function returned: " << returnValue << endl;
	returnValue = true;
*/

	context->Release();
	context = nullptr;

	runningScript = false;

	return returnValue;
}


//------------------------------------------------------------------------------

void ScriptableEngine::abortExecution()
{
    jassert(runningScript == true);
    jassert(abortScript == false);
    
	// @XXX - hack for the component bindings
	/*
	asComponentManager::getInstance()->releaseComponents();
	*/
    
	abortScript = true;
}


//------------------------------------------------------------------------------

void ScriptableEngine::continueExecution()
{
    jassert(runningScript == true);

    continueSilently = true;
}


//------------------------------------------------------------------------------

void ScriptableEngine::loadByteCode(const File& file)
{
    jassert(module != nullptr);
    
	ScriptableByteCodeInStream in(this, file);

	module->LoadByteCode(&in);
}


//------------------------------------------------------------------------------

void ScriptableEngine::saveByteCode(const File& file)
{
    jassert(module != nullptr);

    if (compileFailed)
		return;

	ScriptableByteCodeOutStream out(this, file);

	module->SaveByteCode(&out);
}


//------------------------------------------------------------------------------

int ScriptableEngine::resolveOriginalLine(int lineNumber)
{
	return lineTranslator.ResolveOriginalLine(lineNumber);
}


//------------------------------------------------------------------------------

String ScriptableEngine::resolveOriginalFile(int lineNumber)
{
	return String((const char*)lineTranslator.ResolveOriginalFile(lineNumber).c_str());
}


//------------------------------------------------------------------------------

String ScriptableEngine::serializeVariable(asIScriptContext* context, int variableNumber)
{
    jassert(engine != nullptr);
    jassert(context != nullptr);
    
	void* varPointer = context->GetAddressOfVar(variableNumber);
	int typeID = context->GetVarTypeId(variableNumber);
	String typeDecl = engine->GetTypeDeclaration(typeID);

	if (typeDecl == "bool")
	{
		return String((int)*(bool*)(varPointer));
	}
	else if (typeDecl == "int8" ||
		typeDecl == "int16" ||
		typeDecl == "int32" ||
		typeDecl == "int")
	{
		return String(*(int*)(varPointer));
	}
	else if (typeDecl == "uint8" ||
		typeDecl == "uint16" ||
		typeDecl == "uint32" ||
		typeDecl == "uint")
	{
		return String((int)*(unsigned int*)(varPointer));
	}
	else if (typeDecl == "float")
	{
		return String(*(float*)(varPointer));
	}
	else if (typeDecl == "double")
	{
		return String(*(double*)(varPointer));
	}
	else
	{
		char* buffer = 0;
		for (int i = 0; i < plugins.size(); ++i)
		{
			ScriptableExtensionModel* plug =
				(ScriptableExtensionModel*)plugins.getUnchecked(i);

			buffer = plug->variableCallback(engine, typeID, varPointer);

			if (buffer != 0)
			{
				String varValue = buffer;
				free(buffer);
				return varValue;
			}
		}
	}

	return "???";
}


//------------------------------------------------------------------------------

void ScriptableEngine::addResolveFilePath(const File& directoryToLookInto)
{
	jassert(! directoryToLookInto.existsAsFile())

//	if (directoryToLookInto.existsAsFile())
//		resolvePaths.add(directoryToLookInto.getParentDirectory().getFullPathName());
//	else
		resolvePaths.add(directoryToLookInto.getFullPathName());
}


//------------------------------------------------------------------------------

void ScriptableEngine::removeResolveFilePath(const File& directoryToLookInto)
{
	jassert (! directoryToLookInto.existsAsFile())

//	if (directoryToLookInto.existsAsFile())
//		resolvePaths.removeString(directoryToLookInto.getParentDirectory().getFullPathName());
//	else
		resolvePaths.removeString(directoryToLookInto.getFullPathName());
}


//------------------------------------------------------------------------------

File ScriptableEngine::findResolveFilePaths(const String& fileName)
{
	File fileFound = File::nonexistent;

	int pathToResolve = resolvePaths.size();
	for (int i = 0; i < pathToResolve; i++)
	{
		File fileToLoad = File(resolvePaths[i]).getChildFile(fileName);
		if (fileToLoad.existsAsFile())
		{
			fileFound = fileToLoad;
			break;
		}
	}

	return fileFound;
}


//------------------------------------------------------------------------------

bool ScriptableEngine::registerInternalExtension(const String& extensionName)
{
	// check if is already there
	for (int i = 0; i < plugins.size(); i++)
	{
		ScriptableExtensionModel* plug =
			(ScriptableExtensionModel*)plugins.getUnchecked(i);

		if (plug->identifyPlugin((const char*)extensionName.toUTF8()))
			return true; // already registered
	}

	try
	{
		// otherwise add it
		ScriptableExtension* plugin = new ScriptableExtension(extensionName);

		int returnValue = plugin->registerCallback(engine);

		if (returnValue >= 0)
			plugins.add(plugin);
	}
	catch (...)
	{
		String errorLoadingPlugin = "Error when registering \"";
		errorLoadingPlugin << extensionName << "\" library !";

		if (engineModel)
			engineModel->reportErrors("compiler", errorLoadingPlugin, "", -1);

		return false; // error occurred
	}

	return true;
}


//------------------------------------------------------------------------------

bool ScriptableEngine::registerPluginLibrary(const String& pluginName)
{
	// check if is already there
	for (int i = 0; i < plugins.size(); i++)
	{
		ScriptableExtensionModel* plug =
			(ScriptableExtensionModel*)plugins.getUnchecked(i);

		if (plug->identifyPlugin((const char*)pluginName.toUTF8()))
			return true; // already registered
	}

	try
	{
		// otherwise add it
		ScriptablePlugin* plugin = new ScriptablePlugin(pluginName);

		int returnValue = plugin->registerCallback(engine);

		if (returnValue >= 0)
			plugins.add(plugin);
	}
	catch (...)
	{
		String errorLoadingPlugin = "Error when registering \"";
		errorLoadingPlugin << pluginName << "\" library !";

		if (engineModel)
			engineModel->reportErrors("compiler", errorLoadingPlugin, "", -1);

		return false; // error occurred
	}

	return true;
}


//------------------------------------------------------------------------------

void ScriptableEngine::handlePragma(const Preprocessor::PragmaInstance& pragma)
{
	if (pragma.name == "engine")
	{
		if (pragma.text == "reset")
			createEngine();
	}
	else if (pragma.name == "warnings")
	{
		if (pragma.text == "on")
	    {
			warningsOn = true;
	    }
		else if (pragma.text == "off")
	    {
			warningsOn = false;
	    }
	    else
	    {
	        // TODO - invalid value
	    }
	}
	else if (pragma.name == "debug")
	{
		if (pragma.text == "on")
	    {
			enableDebug(true);
	    }
		else if (pragma.text == "off")
	    {
			enableDebug(false);
	    }
		else
		{
	        // TODO - invalid value
		}
	}
	else if (pragma.name == "extension")
	{
		registerInternalExtension("core");
	}
	else if (pragma.name == "plugin")
	{
		bool loadOK = false;

		int pathToResolve = resolvePaths.size();
		for (int i = 0; i < pathToResolve; i++)
		{
			File pluginFile = File(resolvePaths[i]).getChildFile(pragma.text.c_str());
			if (pluginFile.existsAsFile())
			{
				loadOK = registerPluginLibrary(pluginFile.getFullPathName());
				break;
			}
		}
	}
}


//==============================================================================
int ScriptableEngine::getTimeout() const
{
    return timeOut;
}

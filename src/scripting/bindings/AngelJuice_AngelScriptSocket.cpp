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

#include "../../libraries/angelscript/angelscript.h"

#include "../AngelJuice_ScriptableEngine.h"
#include "AngelJuice_AngelScriptCore.h"
#include "AngelJuice_AngelScriptString.h"
#include "AngelJuice_AngelScriptSocket.h"


//==============================================================================
asURL::asURL() {
	refCount = 1;
}
asURL::asURL(const URL &u) {
	refCount = 1;
	url = u;
}
asURL::asURL(const String &s) {
	refCount = 1;
	url = URL(s);
}
asURL::asURL(const asURL &u) {
	refCount = 1;
	url = u.url;
}
asURL::asURL(const asString &s) {
	refCount = 1;
	url = URL(s.buffer);
}
asURL::~asURL() {
	jassert( refCount == 0 );
}

void asURL::addRef() {
	refCount++;
}
void asURL::release() {
	if( --refCount == 0 )
		delete this;
}

asURL &asURL::operator=(const asURL &other) {
	url = other.url;
	return *this;
}

asString* asURL::toString (const bool includeGetParameters) {
	return new asString(url.toString(includeGetParameters));
}
asURL* asURL::withParameter (const asString& parameterName, const asString& parameterValue) {
	return new asURL(url.withParameter(parameterName.buffer,parameterValue.buffer));
}
asString* asURL::readEntireTextStream (const bool usePostCommand) {
	return new asString(url.readEntireTextStream(usePostCommand));
}

asInputStream* asURL::createInputStream (const bool usePostCommand) const {
	return new asInputStream (url.createInputStream (usePostCommand));
}

asInputStream* asURL::createPostInputStream (const String& postText) const {
	return new asInputStream (url.createPostInputStream (postText));
}

//    const StringPairArray& getParameters() const;
//    bool readEntireBinaryStream (MemoryBlock& destData,
//                                 const bool usePostCommand = false) const;
//    XmlElement* readEntireXmlStream (const bool usePostCommand = false) const;

static void ConstructURL(asURL *thisPointer) {
	new(thisPointer) asURL();
}
static void ConstructURLByString(const asString& text, asURL *thisPointer) {
    new(thisPointer) asURL(text);
}
static void ConstructURLByURL(const asURL& other, asURL *thisPointer) {
    new(thisPointer) asURL(other.url);
}

void asURL:: registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("URL", sizeof(asURL), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("URL", asBEHAVE_CONSTRUCT,  "void f()",                       asFUNCTION(ConstructURL), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("URL", asBEHAVE_CONSTRUCT,  "void f(const String& in)",       asFUNCTION(ConstructURLByString), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("URL", asBEHAVE_CONSTRUCT,  "void f(const URL& in)",          asFUNCTION(ConstructURLByURL), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("URL", asBEHAVE_ADDREF,     "void f()",                       asMETHOD(asURL,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("URL", asBEHAVE_RELEASE,    "void f()",                       asMETHOD(asURL,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("URL", asBEHAVE_ASSIGNMENT, "URL &f(const URL &in)",          asMETHOD(asURL,operator=), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("URL", "bool isWellFormed()",                                    asMETHOD(URL, isWellFormed), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("URL", "bool launchInDefaultBrowser()",                          asMETHOD(URL, launchInDefaultBrowser), asCALL_THISCALL); jassert(r>=0);
//	r = engine->RegisterObjectMethod("URL", "bool isProbablyAWebsiteURL(const String& in)",           asMETHOD(URL, isProbablyAWebsiteURL), asCALL_THISCALL); jassert(r>=0);
//	r = engine->RegisterObjectMethod("URL", "bool isProbablyAnEmailAddress(const String& in)",        asMETHOD(URL, isProbablyAnEmailAddress), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("URL", "URL@ withParameter(const String& in, const String& in)", asMETHOD(asURL, withParameter), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("URL", "String@ readEntireTextStream(bool)",                     asMETHOD(asURL, readEntireTextStream), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("URL", "String@ toString(bool)",                                 asMETHOD(asURL, toString), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("URL", "InputStream& createInputStream(const bool)",             asMETHOD(asURL, createInputStream), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("URL", "InputStream& createPostInputStream(const String&)",      asMETHOD(asURL, createPostInputStream), asCALL_THISCALL); jassert(r>=0);
}





//==============================================================================
/*
asInterprocessConnection::asInterprocessConnection(const bool callbacksOnMessageThread,
					                              const uint32 magicMessageHeaderNumber) :
	InterprocessConnection (callbacksOnMessageThread, magicMessageHeaderNumber),
	methodOwner(0)
{
	eventContext = ScriptableEngine::getInstance()->createContext();
}

asInterprocessConnection::~asInterprocessConnection()
{
	eventContext->Release();
	eventContext = 0;
}

void asInterprocessConnection::addRef() {}
void asInterprocessConnection::release() {}

enum asInterprocessConnectionMethods
{
	CONNECTION_MADE = 0,
	CONNECTION_LOST,
	MESSAGE_RECEIVED,
	NUM_CALLBACKS
};

void asInterprocessConnection::setClassAndObject(const String& className_,const String& objectName_)
{
	className = className_;
	objectName = objectName_;

	asIScriptEngine* scriptEngine = ScriptableEngine::getInstance()->getEngine();

	int classID = scriptEngine->GetTypeIdByDecl (0, (const char*)className_);
	int methodOwnerID = scriptEngine->GetGlobalVarIDByName (0, (const char*)objectName_);
	methodOwner = scriptEngine->GetGlobalVarPointer (methodOwnerID);

	methodId.ensureStorageAllocated (NUM_CALLBACKS);

	methodId.insert(CONNECTION_MADE,	scriptEngine->GetMethodIDByDecl(classID,"void connectionMade()"));
	methodId.insert(CONNECTION_LOST,	scriptEngine->GetMethodIDByDecl(classID,"void connectionLost()"));
	methodId.insert(MESSAGE_RECEIVED,	scriptEngine->GetMethodIDByDecl(classID,"void messageReceived(const MemoryBlock& in)"));
}

void asInterprocessConnection::connectionMade()
{
	if (eventContext && methodId[CONNECTION_MADE] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[CONNECTION_MADE]);
		eventContext->SetObject(methodOwner);
		doExecuteContext();
	}
}
void asInterprocessConnection::connectionLost()
{
	if (eventContext && methodId[CONNECTION_LOST] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[CONNECTION_LOST]);
		eventContext->SetObject(methodOwner);
		doExecuteContext();
	}
}
void asInterprocessConnection::messageReceived (const MemoryBlock& message)
{
	if (eventContext && methodId[MESSAGE_RECEIVED] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MESSAGE_RECEIVED]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&message);
		doExecuteContext();
	}
}

void asInterprocessConnection::doExecuteContext ()
{
	// @XXX call execute on the script engine !

	ScriptableEngine* engine = ScriptableEngine::getInstance();

	engine->runningScript = true;
	engine->abortScript = false;
	engine->continueSilently = false;

	bool exitLoop = false;
	bool returnValue = false;
	int r;

	while (!engine->abortScript && !exitLoop)
	{
		engine->timeOut = Time::getMillisecondCounter() + 100; // 100
		r = eventContext->Execute();

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
			break;
			}
		case asEXECUTION_ABORTED:
			{
			if (engine->engineModel)
				engine->engineModel->reportErrors (T("runtime"),T("The script has timed out."));
			exitLoop = true;
			break;
			}
		case asEXECUTION_EXCEPTION:
			{
			int funcID = eventContext->GetExceptionFunction();
			String errorString = T("\nThe script ended with an exception.\n");
			errorString << T("file: ") << engine->resolveOriginalFile (eventContext->GetExceptionLineNumber()) << T("\n");
			errorString << T("line: ") << engine->resolveOriginalLine (eventContext->GetExceptionLineNumber()) << T("\n");
//			errorString << T("module: ") << engine->GetModuleNameFromIndex(asMODULEIDX(functionID)) << T("\n");
//			errorString << T("section: ") << engine->GetFunctionSection(funcID) << T("\n");
			errorString << T("function: ") << engine->resolveFunctionDeclaration (funcID) << T("\n");
			errorString << T("error: ") << eventContext->GetExceptionString() << T("\n");
			if (engine->engineModel)
				engine->engineModel->reportErrors (T("runtime"), errorString);
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

	engine->runningScript = false;
}


//==============================================================================
void InterprocessConnection_Constructor(asInterprocessConnection *obj) {
	new(obj) asInterprocessConnection();
}
void InterprocessConnection_ConstructorByValue(const bool callbacksOnMessageThread,
												asInterprocessConnection *obj) {
	new(obj) asInterprocessConnection(callbacksOnMessageThread);
}
void InterprocessConnection_ConstructorByValues(const bool callbacksOnMessageThread,
												const uint32 magicMessageHeaderNumber,
												asInterprocessConnection *obj) {
	new(obj) asInterprocessConnection(callbacksOnMessageThread, magicMessageHeaderNumber);
}
void InterprocessConnection_Destructor(asInterprocessConnection *obj) {
//	obj->~asInterprocessConnection();
}
static void *AllocInterprocessConnection(int) {
	return new char[sizeof(asInterprocessConnection)];
}
static void FreeInterprocessConnection(void *p) {
//	jassert( p );
//	delete p;
}


void asInterprocessConnection::registerObjectType(asIScriptEngine *engine)
{
    int r;
	r = engine->RegisterObjectType("InterprocessConnection", sizeof(asInterprocessConnection), asOBJ_CLASS_CD); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("InterprocessConnection", asBEHAVE_CONSTRUCT, "void f()",                        asFUNCTION(InterprocessConnection_Constructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("InterprocessConnection", asBEHAVE_CONSTRUCT, "void f(const bool)",              asFUNCTION(InterprocessConnection_ConstructorByValue), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("InterprocessConnection", asBEHAVE_CONSTRUCT, "void f(const bool, const int)",   asFUNCTION(InterprocessConnection_ConstructorByValues), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("InterprocessConnection", asBEHAVE_DESTRUCT, "void f()",                         asFUNCTION(InterprocessConnection_Destructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("InterprocessConnection", asBEHAVE_ADDREF,     "void f()",                       asMETHOD(asInterprocessConnection,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("InterprocessConnection", asBEHAVE_RELEASE,    "void f()",                       asMETHOD(asInterprocessConnection,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("InterprocessConnection", asBEHAVE_ALLOC,      "InterprocessConnection &f(uint)",   asFUNCTION(AllocInterprocessConnection), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("InterprocessConnection", asBEHAVE_FREE,       "void f(InterprocessConnection &in)",asFUNCTION(FreeInterprocessConnection), asCALL_CDECL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("InterprocessConnection", "void setClassAndObject(const String& in,const String& in)", asMETHOD(asInterprocessConnection,setClassAndObject), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("InterprocessConnection", "bool connectToSocket(const String&, const int, const int)",	asMETHOD(InterprocessConnection, connectToSocket), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("InterprocessConnection", "bool connectToPipe(const String&)",	                        asMETHOD(InterprocessConnection, connectToPipe), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("InterprocessConnection", "bool createPipe(const String&)",	                        asMETHOD(InterprocessConnection, createPipe), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("InterprocessConnection", "void disconnect()",	                                        asMETHOD(InterprocessConnection, disconnect), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("InterprocessConnection", "bool isConnected()",				                        asMETHOD(InterprocessConnection, isConnected), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("InterprocessConnection", "bool sendMessage(const MemoryBlock&)",	                    asMETHOD(InterprocessConnection, sendMessage), asCALL_THISCALL); jassert(r>=0);
}


*/


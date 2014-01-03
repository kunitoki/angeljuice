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
#include "AngelJuice_AngelScriptCommon.h"
#include "AngelJuice_AngelScriptCore.h"
#include "AngelJuice_AngelScriptString.h"
#include "../AngelJuice_ScriptableEngine.h"


//==============================================================================
void asMath::registerObjectType(asIScriptEngine *engine)
{
	int r;

	// global variables
	r = engine->RegisterGlobalProperty("float float_Pi", (void*)&float_Pi);
	r = engine->RegisterGlobalProperty("double double_Pi", (void*)&double_Pi);

	// math functions
	r = engine->RegisterGlobalFunction("float sin(float)",						asFUNCTION(sinf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float cos(float)",						asFUNCTION(cosf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float sqrt(float)",						asFUNCTION(sqrtf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float asin(float)",						asFUNCTION(asinf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float acos(float)",						asFUNCTION(acosf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float tan(float)",						asFUNCTION(tanf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float atan(float)",						asFUNCTION(atanf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float log(float)",						asFUNCTION(logf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float log10(float)",					asFUNCTION(log10f), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float pow(float,float)",				asFUNCTION(powf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int min(int,int)",						asFUNCTIONPR(jmin,(int,int),int), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int max(int,int)",						asFUNCTIONPR(jmax,(int,int),int), asCALL_CDECL); jassert(r >= 0);
// @TODO - compile on linux
//	r = engine->RegisterGlobalFunction("int limit(int,int,int)",				asFUNCTION(jlimit<int>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float min(float,float)",				asFUNCTIONPR(jmin,(float,float),float), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float max(float,float)",				asFUNCTIONPR(jmax,(float,float),float), asCALL_CDECL); jassert(r >= 0);
// @TODO - compile on linux
//	r = engine->RegisterGlobalFunction("float limit(float,float,float)",		asFUNCTION(jlimit<float>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double min(double,double)",				asFUNCTIONPR(jmin,(double,double),double), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double max(double,double)",				asFUNCTIONPR(jmax,(double,double),double), asCALL_CDECL); jassert(r >= 0);
// @TODO - compile on linux
//	r = engine->RegisterGlobalFunction("double limit(double,double,double)",	asFUNCTION(jlimit<double>), asCALL_CDECL); jassert(r >= 0);
// @TODO - compile on linux
//	r = engine->RegisterGlobalFunction("double _hypot(double,double)",			asFUNCTION(_hypot), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("double _j0(double)",					asFUNCTION(_j0), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("double _j1(double)",					asFUNCTION(_j1), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("double _jn(int,double)",				asFUNCTION(_jn), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("double _y0(double)",					asFUNCTION(_y0), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("double _y1(double)",					asFUNCTION(_y1), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("double _yn(int,double)",				asFUNCTION(_yn), asCALL_CDECL); jassert(r >= 0);

#ifdef AS_ALLOW_UNSAFE_REFERENCES
//	r = engine->RegisterGlobalFunction("void swap(bool&, bool&)",				asFUNCTION(swapVariables<bool>), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("void swap(int&, int&)",					asFUNCTION(swapVariables<int>), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("void swap(float&, float&)",				asFUNCTION(swapVariables<float>), asCALL_CDECL); jassert(r >= 0);
//	r = engine->RegisterGlobalFunction("void swap(double&, double&)",			asFUNCTION(swapVariables<double>), asCALL_CDECL); jassert(r >= 0);
#endif
}


//==============================================================================
// @XXX this for some reasons do not compiles on MACOSX
void Random_Constructor(Random *obj) {
	new(obj) Random(Time::currentTimeMillis());
}
void Random_Destructor(Random *obj) {
	obj->~Random();
}

void asRandom::registerObjectType(asIScriptEngine *engine)
{
    int r;
	r = engine->RegisterObjectType("Random", sizeof(Random), asOBJ_CLASS_CD); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Random", asBEHAVE_CONSTRUCT, "void f()",   asFUNCTION(Random_Constructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Random", asBEHAVE_DESTRUCT, "void f()",    asFUNCTION(Random_Destructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "int nextInt(int)",                  asMETHODPR(Random, nextInt, (int), int), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "int nextInt()",                     asMETHODPR(Random, nextInt, (void), int), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "float nextFloat()",                 asMETHOD(Random, nextFloat), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "void setSeed(int)",                 asMETHOD(Random, setSeed), asCALL_THISCALL); jassert(r>=0);
}

//==============================================================================
asString* asSystemStats::getJUCEVersion()	        { return new asString(SystemStats::getJUCEVersion()); }
asString* asSystemStats::getOperatingSystemName()	{ return new asString(SystemStats::getOperatingSystemName()); }
asString* asSystemStats::getCpuVendor()		        { return new asString(SystemStats::getCpuVendor()); }

void asSystemStats::registerObjectType(asIScriptEngine *engine)
{
    int r;
	r = engine->RegisterObjectType("SystemStats_", 0, asOBJ_PRIMITIVE); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("SystemStats_", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(dummy_Constructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("SystemStats_", asBEHAVE_DESTRUCT, "void f()",  asFUNCTION(dummy_Destructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String@ getJUCEVersion()",        asMETHOD(asSystemStats,getJUCEVersion), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String@ getOperatingSystemName()",asMETHOD(asSystemStats,getOperatingSystemName), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String@ getCpuVendor()",          asMETHOD(asSystemStats,getCpuVendor), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "int getCpuSpeedInMegaherz()",     asFUNCTION(SystemStats::getCpuSpeedInMegaherz), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool hasMMX()",                   asFUNCTION(SystemStats::hasMMX), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool hasSSE()",                   asFUNCTION(SystemStats::hasSSE), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool hasSSE2()",                  asFUNCTION(SystemStats::hasSSE2), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool has3DNow()",                 asFUNCTION(SystemStats::has3DNow), asCALL_CDECL_OBJLAST); jassert(r>=0);
//	r = engine->RegisterObjectMethod("SystemStats_", "int getNumPhysicalCpus()",        asFUNCTION(SystemStats::getNumPhysicalCpus), asCALL_CDECL_OBJLAST); jassert(r>=0);
//	r = engine->RegisterObjectMethod("SystemStats_", "int getNumLogicalCpus()",         asFUNCTION(SystemStats::getNumLogicalCpus), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "int getMemorySizeInMegabytes()",  asFUNCTION(SystemStats::getMemorySizeInMegabytes), asCALL_CDECL_OBJLAST); jassert(r>=0);
//	r = engine->RegisterObjectMethod("SystemStats_", "int getClockCycleCounter()",      asFUNCTION(SystemStats::getClockCycleCounter), asCALL_CDECL_OBJLAST); jassert(r>=0);

	engine->RegisterGlobalProperty("SystemStats_ SystemStats",(void*)&dummy32bit);
}


//==============================================================================
static void warningAlert(const asString &text) {
	AlertWindow::showMessageBox(AlertWindow::InfoIcon,T("Alert"),text.buffer);
}
static void errorAlert(const asString &text) {
	AlertWindow::showMessageBox(AlertWindow::WarningIcon,T("Error"),text.buffer);
}
static int askAlert(const asString &text) {
	return (int)AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon,T("Question"),text.buffer);
}
static void executeScript (const String& script) {
	ScriptableEngine::getInstance ()->executeString (script);
}
static void throwException(asString *str) {
	asIScriptContext *context = asGetActiveContext();
	context->SetException((const char *)str->buffer);
}
static void abortApplication () {
   	ScriptableEngine::getInstance ()->abortExecution ();
}
static void quitApplication () {
	JUCEApplication::getInstance()->systemRequestedQuit();
}
static uint8* getReference (uint8* p)  {
   return p;
}

void asCore::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterGlobalFunction("void execute(const String &in)",    asFUNCTION(executeScript), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void throw(const String &in)",      asFUNCTION(throwException), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("uint8& getRef(uint8& in)",          asFUNCTION(getReference), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void alert(const String &in)",      asFUNCTIONPR(warningAlert, (const asString&), void), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void error(const String &in)",      asFUNCTIONPR(errorAlert, (const asString&), void), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("int ask(const String &in)",         asFUNCTIONPR(askAlert, (const asString&), int), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void quit()",                       asFUNCTION(quitApplication), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void abort()",                      asFUNCTION(abortApplication), asCALL_CDECL); jassert( r >= 0 );
}


//==============================================================================
asInputStream::asInputStream(InputStream* s) : stream(s) {
	refCount = 1;
}
asInputStream::~asInputStream() {
	jassert( refCount == 0 );
	if (stream)
		delete stream;
}

void asInputStream::addRef() {
	refCount++;
}
void asInputStream::release() {
	if( --refCount == 0 )
		delete this;
}

asInputStream &asInputStream::operator=(asInputStream &other) {
	stream = other.stream;
	other.stream = 0;
	return *this;
}

int asInputStream::getPosition() { return (int) stream->getPosition(); }
bool asInputStream::setPosition (int pos) { return stream->setPosition(pos); }
void asInputStream::skipNextBytes (int numBytesToSkip) { stream->skipNextBytes(numBytesToSkip); }
int asInputStream::getTotalLength() { return (int) stream->getTotalLength(); }
bool asInputStream::isExhausted() { return stream->isExhausted(); }
bool asInputStream::readBool() { return stream->readBool(); }
char asInputStream::readByte() { return stream->readByte(); }
short asInputStream::readShort() { return stream->readShort(); }
short asInputStream::readShortBigEndian() { return stream->readShortBigEndian(); }
int asInputStream::readInt() { return stream->readInt(); }
int asInputStream::readIntBigEndian() { return stream->readIntBigEndian(); }
int64 asInputStream::readInt64() { return stream->readInt64(); }
int64 asInputStream::readInt64BigEndian() { return stream->readInt64BigEndian(); }
float asInputStream::readFloat() { return stream->readFloat(); }
double asInputStream::readDouble() { return stream->readDouble(); }
int asInputStream::readCompressedInt() { return stream->readCompressedInt(); }
asString* asInputStream::readNextLine() { return new asString(stream->readNextLine()); }
asString* asInputStream::readString() { return new asString(stream->readString()); }
asString* asInputStream::readEntireStreamAsString() { return new asString(stream->readEntireStreamAsString()); }
// int asInputStream::readIntoMemoryBlock (MemoryBlock& destBlock,int maxNumBytesToRead) {}

void asInputStream::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("InputStream", sizeof(asInputStream), asOBJ_CLASS_A); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("InputStream", asBEHAVE_ADDREF,     "void f()",                    asMETHOD(asInputStream,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("InputStream", asBEHAVE_RELEASE,    "void f()",                    asMETHOD(asInputStream,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("InputStream", asBEHAVE_ASSIGNMENT, "InputStream &f(const InputStream &in)",     asMETHOD(asInputStream, operator =), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("InputStream", "int getPosition()",                                   asMETHOD(asInputStream,getPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "bool setPosition(int)",                               asMETHOD(asInputStream,setPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "void skipNextBytes(int)",                             asMETHOD(asInputStream,skipNextBytes), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int getTotalLength()",                                asMETHOD(asInputStream,getTotalLength), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "bool isExhausted()",                                  asMETHOD(asInputStream,isExhausted), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "bool readBool()",                                     asMETHOD(asInputStream,readBool), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int8 readByte()",                                     asMETHOD(asInputStream,readByte), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int16 readShort()",                                   asMETHOD(asInputStream,readShort), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int16 readShortBigEndian()",                          asMETHOD(asInputStream,readShortBigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int readInt()",                                       asMETHOD(asInputStream,readInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int readIntBigEndian()",                              asMETHOD(asInputStream,readIntBigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int64 readInt64()",                                   asMETHOD(asInputStream,readInt64), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int64 readInt64BigEndian()",                          asMETHOD(asInputStream,readInt64BigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "float readFloat()",                                   asMETHOD(asInputStream,readFloat), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "double readDouble()",                                 asMETHOD(asInputStream,readDouble), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int readCompressedInt()",                             asMETHOD(asInputStream,readCompressedInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "String@ readNextLine()",                              asMETHOD(asInputStream,readNextLine), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "String@ readString()",                                asMETHOD(asInputStream,readString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "String@ readEntireStreamAsString()",                  asMETHOD(asInputStream,readEntireStreamAsString), asCALL_THISCALL); jassert( r >= 0 );
}


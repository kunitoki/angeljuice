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

#include "AngelJuice_AngelScriptString.h"
#include "AngelJuice_AngelScriptFile.h"


//==============================================================================
asString::asString() {
	refCount = 1;
}
asString::asString(const char s) {
	refCount = 1;
	buffer << s;
}
asString::asString(const char *s) {
	refCount = 1;
	buffer = s;
}
asString::asString(const tchar s) {
	refCount = 1;
	buffer << s;
}
asString::asString(const tchar *s) {
	refCount = 1;
	buffer = s;
}
asString::asString(const String &s) {
	refCount = 1;
	buffer = s;
}
asString::asString(const asString &s) {
	refCount = 1;
	buffer = s.buffer;
}
asString::~asString() {
	jassert( refCount == 0 );
}


//==============================================================================
void asString::addRef() {
	refCount++;
}
void asString::release() {
	if( --refCount == 0 )
		delete this;
}

//==============================================================================
bool asString::equalsIgnoreCase(const asString &str) {
	return buffer.equalsIgnoreCase(str.buffer);
}
int asString::compare (const asString& other) {
	return buffer.compare(other.buffer);
}
int asString::compareIgnoreCase (const asString& other) {
	return buffer.compareIgnoreCase(other.buffer);
}
int asString::compareLexicographically (const asString& other) {
	return buffer.compareLexicographically(other.buffer);
}
bool asString::startsWith (const asString& text) {
	return buffer.startsWith(text.buffer);
}
bool asString::startsWithIgnoreCase (const asString& text) {
	return buffer.startsWithIgnoreCase(text.buffer);
}
bool asString::endsWith (const asString& text) {
	return buffer.endsWith(text.buffer);
}
bool asString::endsWithIgnoreCase (const asString& text) {
	return buffer.endsWithIgnoreCase(text.buffer);
}
bool asString::contains (const asString& text) {
	return buffer.contains(text.buffer);
}
bool asString::containsIgnoreCase (const asString& text) {
	return buffer.containsIgnoreCase(text.buffer);
}
bool asString::containsWholeWord (const asString& wordToLookFor) {
	return buffer.containsWholeWord(wordToLookFor.buffer);
}
bool asString::containsWholeWordIgnoreCase (const asString& wordToLookFor) {
	return buffer.containsWholeWordIgnoreCase(wordToLookFor.buffer);
}
bool asString::containsAnyOf (const asString& charactersItMightContain) {
	return buffer.containsAnyOf(charactersItMightContain.buffer);
}
bool asString::containsOnly (const asString& charactersItMightContain) {
	return buffer.containsOnly(charactersItMightContain.buffer);
}
bool asString::matchesWildcard (const asString& wildcard, const bool ignoreCase) {
	return buffer.matchesWildcard(wildcard.buffer,ignoreCase);
}
int asString::indexOf (const asString& other) {
	return buffer.indexOf (other.buffer);
}
int asString::indexOf (const int startIndex, const asString& textToLookFor) {
	return buffer.indexOf (startIndex, textToLookFor.buffer);
}
int asString::indexOfIgnoreCase (const asString& textToLookFor) {
	return buffer.indexOfIgnoreCase (textToLookFor.buffer);
}
int asString::indexOfIgnoreCase (const int startIndex, const asString& textToLookFor) {
	return buffer.indexOfIgnoreCase (startIndex, textToLookFor.buffer);
}
int asString::lastIndexOf (const asString& textToLookFor) {
	return buffer.lastIndexOf (textToLookFor.buffer);
}
int asString::lastIndexOfIgnoreCase (const asString& textToLookFor) {
	return buffer.lastIndexOfIgnoreCase (textToLookFor.buffer);
}
asString* asString::substring (int startIndex, int endIndex) {
	return new asString(buffer.substring(startIndex,endIndex));
}
asString* asString::substring (const int startIndex) {
	return new asString(buffer.substring(startIndex));
}
asString* asString::dropLastCharacters (const int numberToDrop) {
	return new asString(buffer.dropLastCharacters(numberToDrop));
}
asString* asString::fromFirstOccurrenceOf (const asString& substringToStartFrom,
                                        const bool includeSubStringInResult,
                                        const bool ignoreCase) {
	return new asString(buffer.fromFirstOccurrenceOf(substringToStartFrom.buffer,includeSubStringInResult,ignoreCase));
}
asString* asString::fromLastOccurrenceOf (const asString& substringToFind,
                                       const bool includeSubStringInResult,
                                       const bool ignoreCase) {
	return new asString(buffer.fromLastOccurrenceOf(substringToFind.buffer,includeSubStringInResult,ignoreCase));
}
asString* asString::upToFirstOccurrenceOf (const asString& substringToEndWith,
                                        const bool includeSubStringInResult,
                                        const bool ignoreCase) {
	return new asString(buffer.upToFirstOccurrenceOf(substringToEndWith.buffer,includeSubStringInResult,ignoreCase));
}
asString* asString::upToLastOccurrenceOf (const asString& substringToFind,
                                       const bool includeSubStringInResult,
                                       const bool ignoreCase) {
	return new asString(buffer.upToLastOccurrenceOf(substringToFind.buffer,includeSubStringInResult,ignoreCase));
}
asString* asString::trim(){
	return new asString(buffer.trim());
}
asString* asString::trimStart(){
	return new asString(buffer.trimStart());
}
asString* asString::trimEnd(){
	return new asString(buffer.trimEnd());
}
asString* asString::toUpperCase(){
	return new asString(buffer.toUpperCase());
}
asString* asString::toLowerCase(){
	return new asString(buffer.toLowerCase());
}
asString* asString::replaceSection (int startIndex, int numCharactersToReplace, const asString& stringToInsert){
	return new asString(buffer.replaceSection(startIndex,numCharactersToReplace,stringToInsert.buffer));
}
asString* asString::replace (const asString& stringToReplace,const asString& stringToInsertInstead,const bool ignoreCase){
	return new asString(buffer.replace(stringToReplace.buffer,stringToInsertInstead.buffer,ignoreCase));
}
asString* asString::replaceCharacter (const asString& characterToReplace, const asString& characterToInsertInstead){
	return new asString(buffer.replaceCharacter(characterToReplace.buffer[0],characterToInsertInstead.buffer[0]));
}
asString* asString::replaceCharacters (const asString& charactersToReplace, const asString& charactersToInsertInstead){
	return new asString(buffer.replaceCharacters(charactersToReplace.buffer,charactersToInsertInstead.buffer));
}
asString* asString::retainCharacters (const asString& charactersToRetain){
	return new asString(buffer.retainCharacters(charactersToRetain.buffer));
}
asString* asString::removeCharacters (const asString& charactersToRemove){
	return new asString(buffer.removeCharacters(charactersToRemove.buffer));
}
asString* asString::initialSectionContainingOnly (const asString& charactersToRetain){
	return new asString(buffer.initialSectionContainingOnly(charactersToRetain.buffer));
}
asString* asString::initialSectionNotContaining (const asString& charactersNotToRetain){
	return new asString(buffer.initialSectionNotContaining(charactersNotToRetain.buffer));
}
asString* asString::unquoted(){
	return new asString(buffer.unquoted());
}
asString* asString::quoted (const asString& quoteCharacter){
	return new asString(buffer.quoted(quoteCharacter.buffer[0]));
}


//==============================================================================
bool operator==(const asString &a, const asString &b) { return a.buffer == b.buffer; }
bool operator!=(const asString &a, const asString &b) { return a.buffer != b.buffer; }
bool operator<=(const asString &a, const asString &b) { return a.buffer <= b.buffer; }
bool operator>=(const asString &a, const asString &b) {	return a.buffer >= b.buffer; }
bool operator<(const asString &a, const asString &b) { return a.buffer < b.buffer; }
bool operator>(const asString &a, const asString &b) { return a.buffer > b.buffer; }
bool operator==(const asString &a, const float b) { return a.buffer.getFloatValue() == b; }
bool operator!=(const asString &a, const float b) { return a.buffer.getFloatValue() != b; }
bool operator<=(const asString &a, const float b) { return a.buffer.getFloatValue() <= b; }
bool operator>=(const asString &a, const float b) { return a.buffer.getFloatValue() >= b; }
bool operator<(const asString &a, const float b) { return a.buffer.getFloatValue() < b; }
bool operator>(const asString &a, const float b) { return a.buffer.getFloatValue() > b; }
bool operator==(const asString &a, const int b) { return a.buffer.getIntValue() == b; }
bool operator!=(const asString &a, const int b) { return a.buffer.getIntValue() != b; }
bool operator<=(const asString &a, const int b) { return a.buffer.getIntValue() <= b; }
bool operator>=(const asString &a, const int b) { return a.buffer.getIntValue() >= b; }
bool operator<(const asString &a, const int b) { return a.buffer.getIntValue() < b; }
bool operator>(const asString &a, const int b) { return a.buffer.getIntValue() > b; }


//==============================================================================
asString &asString::operator=(const asString &other) {
	buffer = other.buffer;
	return *this;
}

asString &asString::operator+=(const asString &other) {
	buffer += other.buffer;
	return *this;
}

asString *operator+(const asString &a, const asString &b) {
	return new asString(a.buffer + b.buffer);
}

//==============================================================================
asString* StringShiftLeftBool(asString* dest, bool b) {
	dest->buffer << ((b==true)?1:0);
	return dest;
}

asString* StringShiftLeftInt(asString* dest, int i) {
	dest->buffer << i;
	return dest;
}

asString* StringShiftLeftUInt(asString* dest, unsigned int ui) {
	dest->buffer << (int)ui;
	return dest;
}

asString* StringShiftLeftFloat(asString* dest, float f) {
	dest->buffer << f;
	return dest;
}

asString* StringShiftLeftDouble(asString* dest, double d) {
	dest->buffer << d;
	return dest;
}

asString* StringShiftLeftString(asString* dest, asString& other) {
	dest->buffer << other.buffer;
	return dest;
}



//==============================================================================
static asString &AssignBoolToString(bool b, asString &dest)
{
	String stream;
	stream << ((b==true)?1:0);
	dest.buffer = stream;
	return dest;
}

static asString &AssignUIntToString(unsigned int i, asString &dest)
{
	String stream;
	stream.printf(T("%u"), i);
	dest.buffer = stream;
	return dest;
}

static asString &AssignIntToString(int i, asString &dest)
{
	String stream;
	stream << i;
	dest.buffer = stream;
	return dest;
}

static asString &AssignFloatToString(float f, asString &dest)
{
	String stream;
	stream << f;
	dest.buffer = stream;
	return dest;
}

static asString &AssignDoubleToString(double f, asString &dest)
{
	String stream;
	stream << f;
	dest.buffer = stream;
	return dest;
}


//==============================================================================
static asString &AddAssignBoolToString(bool b, asString &dest)
{
	String stream;
	stream << ((b==true)?1:0);
	dest.buffer += stream;
	return dest;
}

static asString &AddAssignUIntToString(unsigned int i, asString &dest)
{
	String stream;
	stream.printf(T("%u"), i);
	dest.buffer += stream;
	return dest;
}

static asString &AddAssignIntToString(int i, asString &dest)
{
	String stream;
	stream << i;
	dest.buffer += stream;
	return dest;
}

static asString &AddAssignFloatToString(float f, asString &dest)
{
	String stream;
	stream << f;
	dest.buffer += stream;
	return dest;
}

static asString &AddAssignDoubleToString(double f, asString &dest)
{
	String stream;
	stream << f;
	dest.buffer += stream;
	return dest;
}

//==============================================================================
static asString *AddStringBool(const asString &str,bool b)
{
	String stream;
	stream << (const char*)str.buffer << ((b==true)?1:0);
	return new asString(stream);
}

static asString *AddStringUInt(const asString &str, unsigned int i)
{
	String stream;
	stream.printf(T("%u"), i );
	return new asString(str.buffer + stream);
}

static asString *AddStringInt(const asString &str, int i)
{
	String stream;
	stream << (const char*)str.buffer << i;
	return new asString(stream);
}

static asString *AddStringFloat(const asString &str, float f)
{
	String stream;
	stream << (const char*)str.buffer << f;
	return new asString(stream);
}

static asString *AddStringDouble(const asString &str, double f)
{
	String stream;
	stream << (const char*)str.buffer << f;
	return new asString(stream);
}

//==============================================================================
static asString *AddBoolString(bool b, const asString &str)
{
	String stream;
	stream << ((b==true)?1:0) << (const char*)str.buffer;
	return new asString(stream);
}

static asString *AddUIntString(unsigned int i, const asString &str)
{
	String stream;
	stream.printf(T("%u"), i );
	return new asString(stream + str.buffer);
}

static asString *AddIntString(int i, const asString &str)
{
	String stream;
	stream << i << (const char*)str.buffer;
	return new asString(stream);
}

static asString *AddFloatString(float f, const asString &str)
{
	String stream;
	stream << f << (const char*)str.buffer;
	return new asString(stream);
}

static asString *AddDoubleString(double f, const asString &str)
{
	String stream;
	stream << f << (const char*)str.buffer;
	return new asString(stream);
}


//==============================================================================
// static char* StringCharAt(unsigned int i, asString &str)
static asString* StringCharAt(unsigned int i, asString &str)
{
	if( i >= (unsigned int) str.buffer.length() )
	{
		// Set a script exception
		asIScriptContext *ctx = asGetActiveContext();
		ctx->SetException("Out of range");

		// Return a null pointer
		return 0;
	}

//	return &str.buffer [i];
	return new asString(str.buffer.substring(i,i+1));
}


//==============================================================================
// This function allocates memory for the string object
static void *StringAlloc(int) {
	return new char[sizeof(asString)];
}

// This function deallocates the memory for the string object
static void StringFree(void *p) {
	jassert( p );
	delete[] (char*) p;
}

// This is the string factory that creates new strings for the script
static asString *StringFactory(asUINT length, const char *s) {
	return new asString(s);
}

// This is a wrapper for the default asString constructor, since
// it is not possible to take the address of the constructor directly
static void ConstructString(asString *thisPointer) {
	new(thisPointer) asString();
}
static void ConstructStringByBool(bool b, asString *thisPointer) {
	String text;
	text << ((b==true)?1:0);
	new(thisPointer) asString(text);
}
static void ConstructStringByUInt(unsigned int i, asString *thisPointer) {
	String text;
	text.printf(T("%u"),i);
	new(thisPointer) asString(text);
}
static void ConstructStringByInt(int i, asString *thisPointer) {
	String text;
	text << i;
	new(thisPointer) asString(text);
}
static void ConstructStringByFloat(float f, asString *thisPointer) {
	String text;
	text << f;
	new(thisPointer) asString(text);
}
static void ConstructStringByDouble(double d, asString *thisPointer) {
	String text;
	text << d;
	new(thisPointer) asString(text);
}
static void ConstructStringByString(const asString& text, asString *thisPointer) {
    new(thisPointer) asString(text);
}


//==============================================================================
// This is where we register the string type
void asString:: registerObjectType(asIScriptEngine *engine)
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("String", sizeof(asString), asOBJ_CLASS_CDA); jassert( r >= 0 );

	// Register the object operator overloads
	// Note: We don't have to register the destructor, since the object uses reference counting
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f()",                    asFUNCTION(ConstructString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(const String& in)",    asFUNCTION(ConstructStringByString), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(bool)",                asFUNCTION(ConstructStringByBool), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(uint)",                asFUNCTION(ConstructStringByUInt), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(int)",                 asFUNCTION(ConstructStringByInt), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(float)",               asFUNCTION(ConstructStringByFloat), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(double)",              asFUNCTION(ConstructStringByDouble), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ADDREF,     "void f()",                    asMETHOD(asString,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_RELEASE,    "void f()",                    asMETHOD(asString,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ASSIGNMENT, "String &f(const String &in)", asMETHODPR(asString, operator =, (const asString&), asString&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ADD_ASSIGN, "String &f(const String &in)", asMETHODPR(asString, operator+=, (const asString&), asString&), asCALL_THISCALL); jassert( r >= 0 );

	// Register the memory allocator routines. This will make all memory allocations for the string
	// object be made in one place, which is important if for example the script library is used from a dll
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ALLOC,		"String &f(uint)",			asFUNCTION(StringAlloc), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_FREE,		"void f(String &in)",		asFUNCTION(StringFree), asCALL_CDECL); jassert( r >= 0 );

	// Register the factory to return a handle to a new string
	// Note: We must register the string factory after the basic behaviours,
	// otherwise the library will not allow the use of object handles for this type
	r = engine->RegisterStringFactory("String@", asFUNCTION(StringFactory), asCALL_CDECL); jassert( r >= 0 );

	// Register the global operator overloads
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(const String &in, const String &in)", asFUNCTIONPR(operator +, (const asString &, const asString &), asString*), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,       "bool f(const String &in, const String &in)",    asFUNCTIONPR(operator==, (const asString &, const asString &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,    "bool f(const String &in, const String &in)",    asFUNCTIONPR(operator!=, (const asString &, const asString &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_LEQUAL,      "bool f(const String &in, const String &in)",    asFUNCTIONPR(operator<=, (const asString &, const asString &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_GEQUAL,      "bool f(const String &in, const String &in)",    asFUNCTIONPR(operator>=, (const asString &, const asString &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_LESSTHAN,    "bool f(const String &in, const String &in)",    asFUNCTIONPR(operator <, (const asString &, const asString &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_GREATERTHAN, "bool f(const String &in, const String &in)",    asFUNCTIONPR(operator >, (const asString &, const asString &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,       "bool f(const String &in, const float)",         asFUNCTIONPR(operator==, (const asString &, const float), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,    "bool f(const String &in, const float)",         asFUNCTIONPR(operator!=, (const asString &, const float), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_LEQUAL,      "bool f(const String &in, const float)",         asFUNCTIONPR(operator<=, (const asString &, const float), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_GEQUAL,      "bool f(const String &in, const float)",         asFUNCTIONPR(operator>=, (const asString &, const float), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_LESSTHAN,    "bool f(const String &in, const float)",         asFUNCTIONPR(operator <, (const asString &, const float), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_GREATERTHAN, "bool f(const String &in, const float)",         asFUNCTIONPR(operator >, (const asString &, const float), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,       "bool f(const String &in, const int)",           asFUNCTIONPR(operator==, (const asString &, const int), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,    "bool f(const String &in, const int)",           asFUNCTIONPR(operator!=, (const asString &, const int), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_LEQUAL,      "bool f(const String &in, const int)",           asFUNCTIONPR(operator<=, (const asString &, const int), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_GEQUAL,      "bool f(const String &in, const int)",           asFUNCTIONPR(operator>=, (const asString &, const int), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_LESSTHAN,    "bool f(const String &in, const int)",           asFUNCTIONPR(operator <, (const asString &, const int), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_GREATERTHAN, "bool f(const String &in, const int)",           asFUNCTIONPR(operator >, (const asString &, const int), bool), asCALL_CDECL); jassert( r >= 0 );

	// Register the index operator
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_INDEX, "String@ f(uint)", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
//	r = engine->RegisterObjectBehaviour("String", asBEHAVE_INDEX, "uint8 &f(uint)", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
//	r = engine->RegisterObjectBehaviour("String", asBEHAVE_INDEX, "const uint8 &f(uint) const", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); jassert( r >= 0 );

	// Register the object methods
	r = engine->RegisterObjectMethod("String", "int length() const",										asMETHOD(String,length), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int hashCode() const",										asMETHOD(String,hashCode), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool isEmpty() const",										asMETHOD(String,isEmpty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool isNotEmpty() const",									asMETHOD(String,isNotEmpty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool equalsIgnoreCase(const String& in) const",				asMETHOD(asString, equalsIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int compare(const String& in) const",						asMETHOD(asString, compare), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int compareIgnoreCase(const String& in) const",				asMETHOD(asString, compareIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int compareLexicographically(const String& in) const",		asMETHOD(asString, compareLexicographically), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool startsWith(const String& in) const",					asMETHOD(asString, startsWith), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool startsWithIgnoreCase(const String& in) const",			asMETHOD(asString, startsWithIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool endsWith(const String& in) const",						asMETHOD(asString, endsWith), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool endsWithIgnoreCase(const String& in) const",			asMETHOD(asString, endsWithIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool contains(const String& in) const",						asMETHOD(asString, contains), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsIgnoreCase(const String& in) const",			asMETHOD(asString, containsIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsWholeWord(const String& in) const",			asMETHOD(asString, containsWholeWord), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsWholeWordIgnoreCase(const String& in) const",	asMETHOD(asString, containsWholeWordIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsAnyOf(const String& in) const",				asMETHOD(asString, containsAnyOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsOnly(const String& in) const",					asMETHOD(asString, containsOnly), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool matchesWildcard(const String& in, const bool) const",	asMETHOD(asString, matchesWildcard), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOf(const String& in) const",						asMETHODPR(asString, indexOf, (const asString&), int), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOf(const int, const String& in) const",			asMETHODPR(asString, indexOf, (const int, const asString&), int), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfIgnoreCase(const String& in) const",				asMETHODPR(asString, indexOfIgnoreCase, (const asString&), int), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfIgnoreCase(const int, const String& in) const",	asMETHODPR(asString, indexOfIgnoreCase, (const int, const asString&), int), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int lastIndexOf(const String& in) const",					asMETHOD(asString, lastIndexOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int lastIndexOfIgnoreCase(const String& in) const",			asMETHOD(asString, lastIndexOfIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ substring(int)",						            asMETHODPR(asString, substring, (int), asString*), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ substring(int,int)",						        asMETHODPR(asString, substring, (int,int), asString*), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ dropLastCharacters(int)",						    asMETHOD(asString, dropLastCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ fromFirstOccurrenceOf(const String& in,bool,bool)",	asMETHOD(asString, fromFirstOccurrenceOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ fromLastOccurrenceOf(const String& in,bool,bool)",	asMETHOD(asString, fromLastOccurrenceOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ upToFirstOccurrenceOf(const String& in,bool,bool)",	asMETHOD(asString, upToFirstOccurrenceOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ upToLastOccurrenceOf(const String& in,bool,bool)",	asMETHOD(asString, upToLastOccurrenceOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ trim()",	                                        asMETHOD(asString, trim), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ trimStart()",	                                    asMETHOD(asString, trimStart), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ trimEnd()",	                                        asMETHOD(asString, trimEnd), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ toUpperCase()",	                                    asMETHOD(asString, toUpperCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ toLowerCase()",	                                    asMETHOD(asString, toLowerCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ replaceSection(int,int,const String& in)",          asMETHOD(asString, replaceSection), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ replace(const String& in,const String& in,bool)",   asMETHOD(asString, replace), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ replaceCharacter(const String& in,const String& in)",asMETHOD(asString, replaceCharacter), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ replaceCharacters(const String& in,const String& in)",asMETHOD(asString, replaceCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ retainCharacters(const String& in)",                asMETHOD(asString, retainCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ removeCharacters(const String& in)",                asMETHOD(asString, removeCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ initialSectionContainingOnly(const String& in)",    asMETHOD(asString, initialSectionContainingOnly), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ initialSectionNotContaining(const String& in)",     asMETHOD(asString, initialSectionNotContaining), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool isQuotedString() const",		                        asMETHOD(String,isQuotedString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ unquoted()",	                                    asMETHOD(asString, unquoted), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String@ quoted(const String& in)",	                        asMETHOD(asString, quoted), asCALL_THISCALL); jassert( r >= 0 );

	// Register global operators
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ASSIGNMENT, "String &f(double)",                 asFUNCTION(AssignDoubleToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ADD_ASSIGN, "String &f(double)",                 asFUNCTION(AddAssignDoubleToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(const String &in, double)",        asFUNCTION(AddStringDouble), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(double, const String &in)",        asFUNCTION(AddDoubleString), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ASSIGNMENT, "String &f(float)",                  asFUNCTION(AssignFloatToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ADD_ASSIGN, "String &f(float)",                  asFUNCTION(AddAssignFloatToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(const String &in, float)",         asFUNCTION(AddStringFloat), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(float, const String &in)",         asFUNCTION(AddFloatString), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ASSIGNMENT, "String &f(int)",                    asFUNCTION(AssignIntToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ADD_ASSIGN, "String &f(int)",                    asFUNCTION(AddAssignIntToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(const String &in, int)",           asFUNCTION(AddStringInt), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(int, const String &in)",           asFUNCTION(AddIntString), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ASSIGNMENT, "String &f(uint)",                   asFUNCTION(AssignUIntToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ADD_ASSIGN, "String &f(uint)",                   asFUNCTION(AddAssignUIntToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(const String &in, uint)",          asFUNCTION(AddStringUInt), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(uint, const String &in)",          asFUNCTION(AddUIntString), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ASSIGNMENT, "String &f(bool)",                   asFUNCTION(AssignBoolToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_ADD_ASSIGN, "String &f(bool)",                   asFUNCTION(AddAssignBoolToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(const String &in, bool)",          asFUNCTION(AddStringBool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "String@ f(bool, const String &in)",          asFUNCTION(AddBoolString), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_BIT_SLL,     "String& f(const String &in, String &in)",    asFUNCTION(StringShiftLeftString), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_BIT_SLL,     "String& f(const String &in, double)",        asFUNCTION(StringShiftLeftDouble), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_BIT_SLL,     "String& f(const String &in, float)",         asFUNCTION(StringShiftLeftFloat), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_BIT_SLL,     "String& f(const String &in, int)",           asFUNCTION(StringShiftLeftInt), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_BIT_SLL,     "String& f(const String &in, uint)",          asFUNCTION(StringShiftLeftUInt), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_BIT_SLL,     "String& f(const String &in, bool)",          asFUNCTION(StringShiftLeftBool), asCALL_CDECL); jassert( r >= 0 );
}


//==============================================================================
asRegularExpression::asRegularExpression() :
	regex()
{}
asRegularExpression::asRegularExpression(const asString& pattern) :
	regex(pattern.buffer)
{}

asString* asRegularExpression::getMatch( int num, int* start, int* end ) {
	String found = regex.getMatch (num, *start, *end);
	return new asString(found);
}

static void ConstructRegex(asRegularExpression *thisPointer) {
    new(thisPointer) asRegularExpression();
}
static void ConstructRegexByString(const asString& text, asRegularExpression *thisPointer) {
    new(thisPointer) asRegularExpression(text);
}
static void DestructRegex(asRegularExpression *thisPointer) {
    thisPointer->~asRegularExpression();
}

// This is where we register the string type
void asRegularExpression::registerObjectType(asIScriptEngine *engine)
{
    int r;
    r = engine->RegisterObjectType("RegExp", sizeof(asRegularExpression), asOBJ_CLASS_CD); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("RegExp", asBEHAVE_CONSTRUCT,  "void f()",                    asFUNCTION(ConstructRegex), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("RegExp", asBEHAVE_CONSTRUCT,  "void f(const String& in)",    asFUNCTION(ConstructRegexByString), asCALL_CDECL_OBJLAST);
    r = engine->RegisterObjectBehaviour("RegExp", asBEHAVE_DESTRUCT,   "void f()",                    asFUNCTION(DestructRegex), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("RegExp", "int match(const String& in)",                         asMETHODPR(RegularExpression,match,(const String&),int), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("RegExp", "int match(const String& in,const String& in)",        asMETHODPR(RegularExpression,match,(const String&,const String&),int), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("RegExp", "String@ getMatch(int, int& out, int& out)",           asMETHOD(asRegularExpression,getMatch), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asXmlElement::asXmlElement(XmlElement* other) :
	element(*other), refCount(1)
{}
asXmlElement::asXmlElement(const XmlElement& other) :
	element(other), refCount(1)
{}
asXmlElement::asXmlElement(const String& tagName) :
	element(tagName), refCount(1)
{}
asXmlElement::asXmlElement(const asString& tagName) :
	element(tagName.buffer), refCount(1)
{}
asXmlElement::asXmlElement(const asXmlElement& other) :
	element(other.element), refCount(1)
{}
asXmlElement::~asXmlElement() {
	jassert(refCount==0);
}

void asXmlElement::addRef() {
	refCount++;
}
void asXmlElement::release() {
	if( --refCount == 0 )
		delete this;
}

asXmlElement &asXmlElement::operator=(const asXmlElement &other) {
	element = other.element;
	return *this;
}

bool asXmlElement::isEquivalentTo (asXmlElement* other, const bool ignoreOrderOfAttributes) {
	return element.isEquivalentTo(&(other->element),ignoreOrderOfAttributes);
}
asString* asXmlElement::createDocument (const asString& dtdToUse,const bool allOnOneLine,const bool includeXmlHeader,const asString& encodingType){
	return new asString( element.createDocument(dtdToUse.buffer,allOnOneLine,includeXmlHeader,encodingType.buffer));
}
bool asXmlElement::writeToFile (const asFile& destinationFile,const asString& dtdToUse,const asString& encodingType){
	 return element.writeToFile(destinationFile.file,dtdToUse.buffer,encodingType.buffer);
}
asString* asXmlElement::getTagName(){
	return new asString(element.getTagName());
}
bool asXmlElement::hasTagName (const asString& possibleTagName){
	return element.hasTagName(possibleTagName.buffer);
}
int asXmlElement::getNumAttributes(){
	return element.getNumAttributes();
}
asString* asXmlElement::getAttributeName (const int attributeIndex){
	return new asString(element.getAttributeName(attributeIndex));
}
asString* asXmlElement::getAttributeValue (const int attributeIndex){
	return new asString(element.getAttributeValue(attributeIndex));
}
bool asXmlElement::hasAttribute (const asString& attributeName){
	return element.hasAttribute(attributeName.buffer);
}
asString* asXmlElement::getStringAttribute (const asString& attributeName,const asString& defaultReturnValue){
	return new asString(element.getStringAttribute(attributeName.buffer,defaultReturnValue.buffer));
}
bool asXmlElement::compareAttribute (const asString& attributeName,const asString& stringToCompareAgainst,const bool ignoreCase){
	return element.compareAttribute(attributeName.buffer,stringToCompareAgainst.buffer,ignoreCase);
}
int asXmlElement::getIntAttribute (const asString& attributeName,const int defaultReturnValue){
	return element.getIntAttribute(attributeName.buffer,defaultReturnValue);
}
double asXmlElement::getDoubleAttribute (const asString& attributeName, const double defaultReturnValue){
	return element.getDoubleAttribute(attributeName.buffer,defaultReturnValue);
}
bool asXmlElement::getBoolAttribute (const asString& attributeName, const bool defaultReturnValue){
	return element.getBoolAttribute(attributeName.buffer,defaultReturnValue);
}
void asXmlElement::setAttribute (const asString& attributeName,const asString& newValue){
	element.setAttribute(attributeName.buffer,newValue.buffer);
}
void asXmlElement::setAttribute (const asString& attributeName,const int newValue){
	element.setAttribute(attributeName.buffer,newValue);
}
void asXmlElement::setAttribute (const asString& attributeName,const double newValue){
	element.setAttribute(attributeName.buffer,newValue);
}
void asXmlElement::removeAttribute (const asString& attributeName){
	element.removeAttribute(attributeName.buffer);
}
void asXmlElement::removeAllAttributes(){
	element.removeAllAttributes();
}
asXmlElement* asXmlElement::getFirstChildElement(){
	return new asXmlElement(element.getFirstChildElement());
}
asXmlElement* asXmlElement::getNextElement(){
	return new asXmlElement(element.getNextElement());
}
int asXmlElement::getNumChildElements(){
	return element.getNumChildElements();
}
asXmlElement* asXmlElement::getChildElement (const int index){
	return new asXmlElement(element.getChildElement(index));
}
asXmlElement* asXmlElement::getChildByName (const asString& tagNameToLookFor){
	return new asXmlElement(element.getChildByName(tagNameToLookFor.buffer));
}
void asXmlElement::addChildElement (asXmlElement* newChildElement){
	element.addChildElement(&(newChildElement->element));
}
void asXmlElement::insertChildElement (asXmlElement* newChildNode,int indexToInsertAt){
	element.insertChildElement(&(newChildNode->element),indexToInsertAt);
}
bool asXmlElement::replaceChildElement (asXmlElement* currentChildElement, asXmlElement* newChildNode){
	return element.replaceChildElement(&(currentChildElement->element),&(newChildNode->element));
}
void asXmlElement::removeChildElement (asXmlElement* childToRemove, const bool shouldDeleteTheChild){
	element.removeChildElement(&(childToRemove->element),shouldDeleteTheChild);
}
void asXmlElement::deleteAllChildElements(){
	element.deleteAllChildElements();
}
void asXmlElement::deleteAllChildElementsWithTagName (const asString& tagName){
	element.deleteAllChildElementsWithTagName(tagName.buffer);
}
//    void asXmlElement::sortChildElements (ElementComparator<XmlElement*>& comparatorToUse);
bool asXmlElement::isTextElement(){
	return element.isTextElement();
}
asString* asXmlElement::getText(){
	return new asString(element.getText());
}
asString* asXmlElement::getAllSubText(){
	return new asString(element.getAllSubText());
}
void asXmlElement::addTextElement (const asString& text){
	element.addTextElement(text.buffer);
}
void asXmlElement::deleteAllTextElements(){
	element.deleteAllTextElements();
}


static void ConstructXmlElementByString(const asString& tagName, asXmlElement *thisPointer) {
    new(thisPointer) asXmlElement(tagName);
}
static void ConstructXmlElementByXmlElement(const asXmlElement& other, asXmlElement *thisPointer) {
    new(thisPointer) asXmlElement(other);
}

// This is where we register the string type
void asXmlElement::registerObjectType(asIScriptEngine *engine)
{
    int r;
    r = engine->RegisterObjectType("XmlElement", sizeof(asXmlElement), asOBJ_CLASS_CDA); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("XmlElement", asBEHAVE_CONSTRUCT,  "void f(const XmlElement& in)",                asFUNCTION(ConstructXmlElementByXmlElement), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("XmlElement", asBEHAVE_CONSTRUCT,  "void f(const String& in)",                    asFUNCTION(ConstructXmlElementByString), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("XmlElement", asBEHAVE_ADDREF,     "void f()",                                    asMETHOD(asXmlElement,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("XmlElement", asBEHAVE_RELEASE,    "void f()",                                    asMETHOD(asXmlElement,release), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectBehaviour("XmlElement", asBEHAVE_ASSIGNMENT, "XmlElement &f(const XmlElement &in)",         asMETHODPR(asXmlElement, operator =, (const asXmlElement&), asXmlElement&), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("XmlElement", "bool isEquivalentTo(XmlElement@+, bool)",                             asMETHOD(asXmlElement,isEquivalentTo), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "String@ createDocument(const String& in,bool,bool,const String& in)", asMETHOD(asXmlElement,createDocument), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "bool writeToFile(const File& in,const String& in,const String& in)",  asMETHOD(asXmlElement,writeToFile), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "String@ getTagName()",                                                asMETHOD(asXmlElement,getTagName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "bool hasTagName(const String& in)",                                   asMETHOD(asXmlElement,hasTagName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "int getNumAttributes()",                                              asMETHOD(asXmlElement,getNumAttributes), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "String@ getAttributeName(int)",                                       asMETHOD(asXmlElement,getAttributeName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "String@ getAttributeValue(int)",                                      asMETHOD(asXmlElement,getAttributeValue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "bool hasAttribute(const String& in)",                                 asMETHOD(asXmlElement,hasAttribute), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "String@ getStringAttribute(const String& in,const String& in)",       asMETHOD(asXmlElement,getStringAttribute), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "bool compareAttribute(const String& in,const String& in,bool)",       asMETHOD(asXmlElement,compareAttribute), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "int getIntAttribute(const String& in,int)",                           asMETHOD(asXmlElement,getIntAttribute), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "double getDoubleAttribute(const String& in,double)",                  asMETHOD(asXmlElement,getDoubleAttribute), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "bool getBoolAttribute(const String& in,bool)",                        asMETHOD(asXmlElement,getBoolAttribute), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void setAttribute(const String& in,const String& in)",                asMETHODPR(asXmlElement,setAttribute,(const asString&,const asString&),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void setAttribute(const String& in,int)",                             asMETHODPR(asXmlElement,setAttribute,(const asString&,int),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void setAttribute(const String& in,double)",                          asMETHODPR(asXmlElement,setAttribute,(const asString&,double),void), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("XmlElement", "void setAttribute(const String& in,bool)",                            asMETHODPR(asXmlElement,setAttribute,(const asString&,bool),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void removeAttribute(const String& in)",                              asMETHOD(asXmlElement,removeAttribute), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void removeAllAttributes()",                                          asMETHOD(asXmlElement,removeAllAttributes), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "XmlElement@ getFirstChildElement()",                                  asMETHOD(asXmlElement,getFirstChildElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "XmlElement@ getNextElement()",                                        asMETHOD(asXmlElement,getNextElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "int getNumChildElements()",                                           asMETHOD(asXmlElement,getNumChildElements), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "XmlElement@ getChildElement(int)",                                    asMETHOD(asXmlElement,getChildElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "XmlElement@ getChildByName(const String& in)",                        asMETHOD(asXmlElement,getChildByName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void addChildElement(XmlElement@+)",                                  asMETHOD(asXmlElement,addChildElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void insertChildElement(XmlElement@+,int)",                           asMETHOD(asXmlElement,insertChildElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void replaceChildElement(XmlElement@+,XmlElement@+)",                 asMETHOD(asXmlElement,replaceChildElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void removeChildElement(XmlElement@+,bool)",                          asMETHOD(asXmlElement,removeChildElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void deleteAllChildElements()",                                       asMETHOD(asXmlElement,deleteAllChildElements), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void deleteAllChildElementsWithTagName(const String& in)",            asMETHOD(asXmlElement,deleteAllChildElementsWithTagName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "bool isTextElement()",                                                asMETHOD(asXmlElement,isTextElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "String@ getText()",                                                   asMETHOD(asXmlElement,getText), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "String@ getAllSubText()",                                             asMETHOD(asXmlElement,getAllSubText), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void addTextElement(const String& in)",                               asMETHOD(asXmlElement,addTextElement), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlElement", "void deleteAllTextElements()",                                        asMETHOD(asXmlElement,deleteAllTextElements), asCALL_THISCALL); jassert( r >= 0 );
}




//==============================================================================
asXmlDocument::asXmlDocument(const asString& doc) :
	document(doc.buffer), refCount(1)
{}
asXmlDocument::asXmlDocument(const asFile& file) :
	document(file.file), refCount(1)
{}
asXmlDocument::~asXmlDocument() {
	jassert(refCount==0);
}

void asXmlDocument::addRef() {
	refCount++;
}
void asXmlDocument::release() {
	if( --refCount == 0 )
		delete this;
}

asXmlElement* asXmlDocument::getDocumentElement () {
	XmlElement* elementToCopy = document.getDocumentElement();
	asXmlElement* elementToReturn = new asXmlElement(elementToCopy);
	delete elementToCopy;
	return elementToReturn;
}
asXmlElement* asXmlDocument::getDocumentElement (const bool onlyReadOuterDocumentElement) {
	XmlElement* elementToCopy = document.getDocumentElement(onlyReadOuterDocumentElement);
	asXmlElement* elementToReturn = new asXmlElement(elementToCopy);
	delete elementToCopy;
	return elementToReturn;
}
asString* asXmlDocument::getLastParseError() {
	return new asString(document.getLastParseError());
}


static void ConstructXmlDocumentByString(const asString& text, asXmlDocument *thisPointer) {
    new(thisPointer) asXmlDocument(text);
}
static void ConstructXmlDocumentByFile(const asFile& file, asXmlDocument *thisPointer) {
    new(thisPointer) asXmlDocument(file);
}

// This is where we register the string type
void asXmlDocument::registerObjectType(asIScriptEngine *engine)
{
    int r;
    r = engine->RegisterObjectType("XmlDocument", sizeof(asXmlDocument), asOBJ_CLASS_CD); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("XmlDocument", asBEHAVE_CONSTRUCT,  "void f(const File& in)",      asFUNCTION(ConstructXmlDocumentByFile), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("XmlDocument", asBEHAVE_CONSTRUCT,  "void f(const String& in)",    asFUNCTION(ConstructXmlDocumentByString), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("XmlDocument", asBEHAVE_ADDREF,     "void f()",                    asMETHOD(asXmlDocument,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("XmlDocument", asBEHAVE_RELEASE,    "void f()",                    asMETHOD(asXmlDocument,release), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("XmlDocument", "XmlElement@ getDocumentElement()",                    asMETHODPR(asXmlDocument,getDocumentElement,(),asXmlElement*), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("XmlDocument", "XmlElement@ getDocumentElement(const bool)",          asMETHODPR(asXmlDocument,getDocumentElement,(const bool),asXmlElement*), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("XmlDocument", "String@ getLastParseError()",                         asMETHOD(asXmlDocument,getLastParseError), asCALL_THISCALL); jassert( r >= 0 );
}


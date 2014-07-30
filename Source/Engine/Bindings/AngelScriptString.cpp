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

#include "AngelScriptString.h"
//#include "AngelJuice_AngelScriptFile.h"

namespace Bindings {


//==============================================================================
/*

// This function allocates memory for the string object
static void *StringAlloc(int) {
	return new char[sizeof(asString)];
}

// This function deallocates the memory for the string object
static void StringFree(void *p) {
	jassert( p );
	delete[] (char*) p;
}
*/


//==============================================================================

//------------------------------------------------------------------------------

String StringFactory(asUINT length, const char* s)
{
    return String::fromUTF8(s, length);
}


//------------------------------------------------------------------------------

void ConstructString(String* thisPointer)
{
	new(thisPointer) String();
}

void DestructString(String* thisPointer)
{
	thisPointer->~String();
}

void ConstructStringByString(const String &other, String* thisPointer)
{
	new(thisPointer) String(other);
}

void ConstructStringByBool(bool b, String* thisPointer)
{
	new(thisPointer) String((b == true) ? 1 : 0);
}

void ConstructStringByUInt16(uint16 i, String* thisPointer)
{
	String text;
	text.formatted("%u", i);
	new(thisPointer) String(text);
}

void ConstructStringByInt16(int16 i, String* thisPointer)
{
	new(thisPointer) String(i);
}

void ConstructStringByUInt32(uint32 i, String* thisPointer)
{
	String text;
	text.formatted("%u", i);
	new(thisPointer) String(text);
}

void ConstructStringByInt32(int32 i, String* thisPointer)
{
	new(thisPointer) String(i);
}

void ConstructStringByUInt64(uint64 i, String* thisPointer)
{
	String text;
	text.formatted("%u", i);
	new(thisPointer) String(text);
}

void ConstructStringByInt64(int64 i, String* thisPointer)
{
	new(thisPointer) String(i);
}

void ConstructStringByFloat(float f, String* thisPointer)
{
	new(thisPointer) String(f);
}

void ConstructStringByFloatWithDecimalPlaces(float f, int decimal, String* thisPointer)
{
	new(thisPointer) String(f, decimal);
}

void ConstructStringByDouble(double d, String* thisPointer)
{
	new(thisPointer) String(d);
}

void ConstructStringByDoubleWithDecimalPlaces(double d, int decimal, String* thisPointer)
{
	new(thisPointer) String(d, decimal);
}


//------------------------------------------------------------------------------

String AddStringToString(const String& a, String& b)
{
	return b + a;
}


//------------------------------------------------------------------------------

// For some reason gcc 4.7 has difficulties resolving the 
// asFUNCTIONPR(operator==, (const string &, const string &) 
// makro, so this wrapper was introduced as work around.
bool StringEquals(const String& lhs, const String& rhs)
{
    return lhs == rhs;
}

int StringCmp(const String& a, const String& b)
{
	int cmp = 0;
	if (a < b) cmp = -1;
	else if (a > b) cmp = 1;
	return cmp;
}

int StringIndexOfChar(wchar_t search, const String& str)
{
    return str.indexOfChar(search);
}

int StringIndexOfCharWithStart(int startIndex, wchar_t search, const String& str)
{
    return str.indexOfChar(startIndex, search);
}

int StringIndexOf(const String& search, const String& str)
{
    return str.indexOf(search);
}

int StringIndexOfWithStart(int startIndex, const String& search, const String& str)
{
    return str.indexOf(startIndex, search);
}

int StringIndexOfIgnoreCase(const String& search, const String& str)
{
    return str.indexOfIgnoreCase(search);
}

int StringIndexOfIgnoreCaseWithStart(int startIndex, const String& search, const String& str)
{
    return str.indexOfIgnoreCase(startIndex, search);
}


//------------------------------------------------------------------------------

String StringCharAt(int i, String& str)
{
	if (i >= 0 && i < str.length())
	{
	    return str.substring(i, i + 1);
	}
	
	// Set a script exception
	asIScriptContext *ctx = asGetActiveContext();

	ctx->SetException("String index out of range");

	// Return an empty string (was a null pointer)
    return "";
}


//------------------------------------------------------------------------------

String& StringShiftLeftBool(bool b, String& dest)
{
	dest << (b ? 1 : 0);
	return dest;
}

String& StringShiftLeftInt8(int8 i, String& dest)
{
	dest << i;
	return dest;
}

String& StringShiftLeftUInt8(uint8 ui, String& dest)
{
	dest << (int8)ui;
	return dest;
}

String& StringShiftLeftInt16(int16 i, String& dest)
{
	dest << i;
	return dest;
}

String& StringShiftLeftUInt16(uint16 ui, String& dest)
{
	dest << (int16)ui;
	return dest;
}

String& StringShiftLeftInt32(int32 i, String& dest)
{
	dest << i;
	return dest;
}

String& StringShiftLeftUInt32(uint32 ui, String& dest)
{
	dest << (int32)ui;
	return dest;
}

String& StringShiftLeftInt64(int64 i, String& dest)
{
	dest << i;
	return dest;
}

String& StringShiftLeftUInt64(uint64 ui, String& dest)
{
	dest << (int64)ui;
	return dest;
}

String& StringShiftLeftFloat(float f, String& dest)
{
	dest << f;
	return dest;
}

String& StringShiftLeftDouble(double d, String& dest)
{
	dest << d;
	return dest;
}

String& StringShiftLeftString(const String& other, String& dest)
{
	dest << other;
	return dest;
}


//------------------------------------------------------------------------------

String StringQuoted(const String& quote, const String& str)
{
    if (quote.isNotEmpty())
        return str.quoted(quote[0]);
    else
        return str.quoted();
}

String StringQuotedNoArgs(const String& str)
{
    return str.quoted();
}


String StringReplace(const String& needle, const String& repl, const String& str)
{
    return str.replace(needle, repl);
}

String StringSubstringStartEnd(int start, int end, const String& str)
{
    return str.substring(start, end);
}

String StringSubstringStart(int start, const String& str)
{
    return str.substring(start);
}


//------------------------------------------------------------------------------

void ScriptableString::registerTypes(asIScriptEngine* engine) const
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); jassert( r >= 0 );
}

void ScriptableString::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	// Register the factory to return a new string (by value)
    r = engine->RegisterStringFactory("String", asFUNCTION(StringFactory), asCALL_CDECL); jassert( r >= 0 );

   	// Register the memory allocator routines. This will make all memory allocations for the string
	// object be made in one place, which is important if for example the script library is used from a dll
	//r = engine->RegisterObjectBehaviour("String", asBEHAVE_ALLOC,		"String &f(uint)",			asFUNCTION(StringAlloc), asCALL_CDECL); jassert( r >= 0 );
	//r = engine->RegisterObjectBehaviour("String", asBEHAVE_FREE,		"void f(String &in)",		asFUNCTION(StringFree), asCALL_CDECL); jassert( r >= 0 );
    
	// Register the constructors / destructors
    r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f()",                    asFUNCTION(ConstructString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(const String& in)",    asFUNCTION(ConstructStringByString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(bool)",                asFUNCTION(ConstructStringByBool), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(uint16)",              asFUNCTION(ConstructStringByUInt16), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(int16)",               asFUNCTION(ConstructStringByInt16), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(uint32)",              asFUNCTION(ConstructStringByUInt32), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(int32)",               asFUNCTION(ConstructStringByInt32), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(uint64)",              asFUNCTION(ConstructStringByUInt64), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(int64)",               asFUNCTION(ConstructStringByInt64), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(float)",               asFUNCTION(ConstructStringByFloat), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(double)",              asFUNCTION(ConstructStringByDouble), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(float, int)",          asFUNCTION(ConstructStringByFloatWithDecimalPlaces), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT,  "void f(double, int)",         asFUNCTION(ConstructStringByDoubleWithDecimalPlaces), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT,   "void f()",                    asFUNCTION(DestructString),  asCALL_CDECL_OBJLAST); jassert( r >= 0 );

	// Register the global operator overloads
	r = engine->RegisterObjectMethod("String", "bool opEquals(const String &in) const",               asFUNCTIONPR(StringEquals, (const String&, const String&), bool), asCALL_CDECL_OBJFIRST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int opCmp(const String &in) const",                   asFUNCTION(StringCmp), asCALL_CDECL_OBJFIRST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opAssign(const String &in)",                  asMETHODPR(String, operator=, (const String&), String&), asCALL_THISCALL); jassert( r >= 0 );
  	r = engine->RegisterObjectMethod("String", "String opAdd(const String &in) const",                asFUNCTION(AddStringToString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String &opAddAssign(const String &in)",               asMETHODPR(String, operator+=, (const String&), String&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String &opAddAssign(int8)",                           asMETHODPR(String, operator+=, (char), String&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String &opAddAssign(int)",                            asMETHODPR(String, operator+=, (int), String&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String opIndex(int) const",                           asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(bool)",                                 asFUNCTION(StringShiftLeftBool), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(int8)",                                 asFUNCTION(StringShiftLeftInt8), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(uint8)",                                asFUNCTION(StringShiftLeftUInt8), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(int16)",                                asFUNCTION(StringShiftLeftInt16), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(uint16)",                               asFUNCTION(StringShiftLeftUInt16), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(int32)",                                asFUNCTION(StringShiftLeftInt32), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(uint32)",                               asFUNCTION(StringShiftLeftUInt32), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(int64)",                                asFUNCTION(StringShiftLeftInt64), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(uint64)",                               asFUNCTION(StringShiftLeftUInt64), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(float)",                                asFUNCTION(StringShiftLeftFloat), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(double)",                               asFUNCTION(StringShiftLeftDouble), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String& opShl(const String&)",                        asFUNCTION(StringShiftLeftString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	
    // Register the cast behaviour
	// int ConvStringToInt(const std::string &s)
    // {
    //     return atoi(s.c_str());
    // }
    // r = engine->RegisterObjectBehaviour("String", asBEHAVE_VALUE_CAST, "int f() const", asFUNCTION(ConvStringToInt), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    
	// Register the object methods
	r = engine->RegisterObjectMethod("String", "int hashCode() const",                                              asMETHOD(String, hashCode), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int64 hashCode64() const",                                          asMETHOD(String, hashCode64), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int length() const",                                                asMETHOD(String, length), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "void append(const String& in, uint)",                               asMETHOD(String, append), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool isEmpty() const",                                              asMETHOD(String, isEmpty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool isNotEmpty() const",                                           asMETHOD(String, isNotEmpty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool equalsIgnoreCase(const String& in) const",				        asMETHODPR(String, equalsIgnoreCase, (const String&) const, bool), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int compare(const String& in) const",						        asMETHODPR(String, compare, (const String&) const, int), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int compareIgnoreCase(const String& in) const",				        asMETHOD(String, compareIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int compareNatural(const String& in) const",		                asMETHOD(String, compareNatural), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool startsWith(const String& in) const",					        asMETHOD(String, startsWith), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool startsWithChar(int) const",				                    asMETHOD(String, startsWithChar), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool startsWithIgnoreCase(const String& in) const",			        asMETHOD(String, startsWithIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool endsWith(const String& in) const",						        asMETHOD(String, endsWith), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("String", "bool endsWithChar(int) const",				                        asMETHOD(String, endsWithChar), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool endsWithIgnoreCase(const String& in) const",			        asMETHOD(String, endsWithIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool contains(const String& in) const",						        asMETHOD(String, contains), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("String", "bool containsChar(int) const",				                        asMETHOD(String, containsChar), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsIgnoreCase(const String& in) const",			        asMETHOD(String, containsIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsWholeWord(const String& in) const",			        asMETHOD(String, containsWholeWord), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsWholeWordIgnoreCase(const String& in) const",	        asMETHOD(String, containsWholeWordIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfWholeWord(const String& in) const",			            asMETHOD(String, indexOfWholeWord), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfWholeWordIgnoreCase(const String& in) const",            asMETHOD(String, indexOfWholeWordIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsAnyOf(const String& in) const",				        asMETHOD(String, containsAnyOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsOnly(const String& in) const",					        asMETHOD(String, containsOnly), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool containsNonWhitespaceChars() const",					        asMETHOD(String, containsNonWhitespaceChars), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool matchesWildcard(const String& in, const bool) const",	        asMETHOD(String, matchesWildcard), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfChar(int) const",						                asFUNCTION(StringIndexOfChar), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfChar(int, int) const",						            asFUNCTION(StringIndexOfCharWithStart), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
      // TODO - wrapper //r = engine->RegisterObjectMethod("String", "int indexOfAnyOf(const String& in) const",	              asMETHODPR(String, indexOfAnyOf, (StringRef, int, bool) const, int), asCALL_THISCALL); jassert( r >= 0 );
	  // TODO - wrapper //r = engine->RegisterObjectMethod("String", "int indexOfAnyOf(const String& in, int) const",	          asMETHODPR(String, indexOfAnyOf, (StringRef, int, bool) const, int), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfAnyOf(const String& in, int, bool) const",	            asMETHOD(String, indexOfAnyOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOf(const String& in) const",						        asFUNCTION(StringIndexOf), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOf(int, const String& in) const",			                asFUNCTION(StringIndexOfWithStart), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfIgnoreCase(const String& in) const",						asFUNCTION(StringIndexOfIgnoreCase), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int indexOfIgnoreCase(int, const String& in) const",			    asFUNCTION(StringIndexOfIgnoreCaseWithStart), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int lastIndexOfChar(int) const",					                asMETHOD(String, lastIndexOfChar), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int lastIndexOf(const String& in) const",					        asMETHOD(String, lastIndexOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int lastIndexOfIgnoreCase(const String& in) const",			        asMETHOD(String, lastIndexOfIgnoreCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int lastIndexOfAnyOf(const String& in, bool) const",	            asMETHOD(String, lastIndexOfAnyOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String trim() const",                                               asMETHOD(String, trim), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String trimStart() const",                                          asMETHOD(String, trimStart), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String trimEnd() const",                                            asMETHOD(String, trimEnd), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String trimCharactersAtStart(const String& in) const",              asMETHOD(String, trimCharactersAtStart), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String trimCharactersAtEnd(const String& in) const",                asMETHOD(String, trimCharactersAtEnd), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String paddedLeft(int, int) const",                                 asMETHOD(String, paddedLeft), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String paddedRight(int, int) const",                                asMETHOD(String, paddedRight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String toUpperCase() const",                                        asMETHOD(String, toUpperCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String toLowerCase() const",                                        asMETHOD(String, toLowerCase), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String replaceSection(int,int,const String& in) const",             asMETHOD(String, replaceSection), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String replace(const String& in,const String& in,bool) const",      asMETHOD(String, replace), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String replace(const String& in,const String& in) const",           asFUNCTION(StringReplace), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String replaceCharacter(int, int) const",                           asMETHOD(String, replaceCharacter), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String replaceCharacters(const String& in,const String& in) const", asMETHOD(String, replaceCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String retainCharacters(const String& in) const",                   asMETHOD(String, retainCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String removeCharacters(const String& in) const",                   asMETHOD(String, removeCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String initialSectionContainingOnly(const String& in) const",       asMETHOD(String, initialSectionContainingOnly), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String initialSectionNotContaining(const String& in) const",        asMETHOD(String, initialSectionNotContaining), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "bool isQuotedString() const",		                                asMETHOD(String, isQuotedString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String unquoted() const",	                                        asMETHOD(String, unquoted), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String quoted() const",	                                            asFUNCTION(StringQuotedNoArgs), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String quoted(const String& in) const",	                            asFUNCTION(StringQuoted), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int getLastCharacter() const",	                                    asMETHOD(String, getLastCharacter), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String substring(int) const",                                       asFUNCTION(StringSubstringStart), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String substring(int, int) const",                                  asFUNCTION(StringSubstringStartEnd), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String dropLastCharacters(int) const",						        asMETHOD(String, dropLastCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String getLastCharacters(int) const",						        asMETHOD(String, getLastCharacters), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String fromFirstOccurrenceOf(const String& in,bool,bool) const",    asMETHOD(String, fromFirstOccurrenceOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String fromLastOccurrenceOf(const String& in,bool,bool) const",	    asMETHOD(String, fromLastOccurrenceOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String upToFirstOccurrenceOf(const String& in,bool,bool) const",    asMETHOD(String, upToFirstOccurrenceOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "String upToLastOccurrenceOf(const String& in,bool,bool) const",	    asMETHOD(String, upToLastOccurrenceOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int getIntValue() const",	                                        asMETHOD(String, getIntValue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int64 getLargeIntValue() const",	                                asMETHOD(String, getLargeIntValue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int getTrailingIntValue() const",	                                asMETHOD(String, getTrailingIntValue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "float getFloatValue() const",	                                    asMETHOD(String, getFloatValue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "double getDoubleValue() const",	                                    asMETHOD(String, getDoubleValue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int getHexValue32() const",	                                        asMETHOD(String, getHexValue32), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "int64 getHexValue64() const",	                                    asMETHOD(String, getHexValue64), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "void preallocateBytes(uint)",	                                    asMETHOD(String, preallocateBytes), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("String", "void swapWith(String& inout)",	                                    asMETHOD(String, swapWith), asCALL_THISCALL); jassert( r >= 0 );

	// static methods/properties
	r = engine->SetDefaultNamespace("String"); jassert( r >= 0 );
	r = engine->RegisterGlobalProperty("const String empty", (void*)&String::empty); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("String charToString(int)",                                                  asFUNCTION(String::charToString), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("String toHexString(int16)",                                                 asFUNCTIONPR(String::toHexString, (short), String), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("String toHexString(int32)",                                                 asFUNCTIONPR(String::toHexString, (int), String), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("String toHexString(int64)",                                                 asFUNCTIONPR(String::toHexString, (int64), String), asCALL_CDECL); jassert(r>=0);
	r = engine->SetDefaultNamespace(""); jassert(r >= 0);
}


//==============================================================================

//------------------------------------------------------------------------------

void ConstructStringArray(StringArray* thisPointer)
{
	new(thisPointer) StringArray();
}

void DestructStringArray(StringArray* thisPointer)
{
	thisPointer->~StringArray();
}

void ConstructStringArrayByStringArray(const StringArray &other, StringArray* thisPointer)
{
	new(thisPointer) StringArray(other);
}

void ConstructStringArrayByString(const String &other, StringArray* thisPointer)
{
	new(thisPointer) StringArray(other);
}


//------------------------------------------------------------------------------

bool StringArrayEquals(const StringArray& lhs, const StringArray& rhs)
{
    return lhs == rhs;
}


//------------------------------------------------------------------------------

String StringArrayAt(int i, StringArray& strArray)
{
	if (i >= 0 && i < strArray.size())
	{
	    return strArray[i];
	}
	
	// Set a script exception
	asIScriptContext *ctx = asGetActiveContext();
	ctx->SetException("StringArray index out of range");

    return "";
}


//------------------------------------------------------------------------------

bool StringArrayContains1(const String& in, const StringArray& array)
{
    return array.contains(in);
}

bool StringArrayContains2(const String& in, bool a, const StringArray& array)
{
    return array.contains(in, a);
}


//------------------------------------------------------------------------------

int StringArrayIndexOf1(const String& in, const StringArray& array)
{
    return array.indexOf(in);
}

int StringArrayIndexOf2(const String& in, bool a, const StringArray& array)
{
    return array.indexOf(in, a);
}

int StringArrayIndexOf3(const String& in, bool a, int b, const StringArray& array)
{
    return array.indexOf(in, a, b);
}


//------------------------------------------------------------------------------

void ScriptableStringArray::registerTypes(asIScriptEngine* engine) const
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("StringArray", sizeof(String), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); jassert( r >= 0 );
}

void ScriptableStringArray::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	// Register the constructors / destructors
    r = engine->RegisterObjectBehaviour("StringArray", asBEHAVE_CONSTRUCT,  "void f()",                      asFUNCTION(ConstructStringArray), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("StringArray", asBEHAVE_DESTRUCT,   "void f()",                      asFUNCTION(DestructStringArray),  asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("StringArray", asBEHAVE_CONSTRUCT,  "void f(const String& in)",      asFUNCTION(ConstructStringArrayByString), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("StringArray", asBEHAVE_CONSTRUCT,  "void f(const StringArray& in)", asFUNCTION(ConstructStringArrayByStringArray), asCALL_CDECL_OBJLAST); jassert( r >= 0 );

	// operators
	r = engine->RegisterObjectMethod("StringArray", "String opIndex(int) const",                             asFUNCTION(StringArrayAt), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "bool opEquals(const StringArray &in) const",            asFUNCTION(StringArrayEquals), asCALL_CDECL_OBJFIRST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "String& opAssign(const String &in)",                    asMETHODPR(StringArray, operator=, (const StringArray&), StringArray&), asCALL_THISCALL); jassert( r >= 0 );
	
	// Methods
	r = engine->RegisterObjectMethod("StringArray", "void swapWith(StringArray& inout)",	                 asMETHOD(StringArray, swapWith), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "int size() const",	                                     asMETHOD(StringArray, size), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "String& getReference(int) const",	                     asMETHOD(StringArray, getReference), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "bool contains(const String& in) const",	             asFUNCTION(StringArrayContains1), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "bool contains(const String& in, bool) const",           asFUNCTION(StringArrayContains2), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "int indexOf(const String& in) const",	                 asFUNCTION(StringArrayIndexOf1), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "int indexOf(const String& in, bool) const",	         asFUNCTION(StringArrayIndexOf2), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "int indexOf(const String& in, bool, int) const",	     asFUNCTION(StringArrayIndexOf3), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void add(const String& in)",	                         asMETHOD(StringArray, add), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void insert(int, const String& in)",	                 asMETHOD(StringArray, insert), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void addIfNotAlreadyThere(const String& in)",	     asMETHOD(StringArray, addIfNotAlreadyThere), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void addIfNotAlreadyThere(const String& in, bool)",   asMETHOD(StringArray, addIfNotAlreadyThere), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void set(int, const String& in)",	                     asMETHOD(StringArray, set), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void addArray(const StringArray& in)",	             asMETHOD(StringArray, addArray), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void addArray(const StringArray& in, int)",	         asMETHOD(StringArray, addArray), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void addArray(const StringArray& in, int, int)",	     asMETHOD(StringArray, addArray), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "int addTokens(const String& in, bool)",	             asMETHODPR(StringArray, addTokens, (StringRef, bool), int), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "int addTokens(const String& in, const String& in, const String& in)", asMETHODPR(StringArray, addTokens, (StringRef, StringRef, StringRef), int), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "int addLines(const String& in)",	                     asMETHOD(StringArray, addLines), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void clear()",   	                                     asMETHOD(StringArray, clear), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void clearQuick()",   	                                 asMETHOD(StringArray, clearQuick), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void remove(int)",   	                                 asMETHOD(StringArray, remove), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void removeString(const String& in)",                   asMETHOD(StringArray, removeString), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void removeString(const String& in, bool)",             asMETHOD(StringArray, removeString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void removeRange(int, int)",   	                     asMETHOD(StringArray, removeRange), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void removeDuplicates(bool)",   	                     asMETHOD(StringArray, removeDuplicates), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void removeEmptyStrings()",   	                     asMETHOD(StringArray, removeEmptyStrings), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "void removeEmptyStrings(bool)",   	                 asMETHOD(StringArray, removeEmptyStrings), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void move(int, int)",   	                             asMETHOD(StringArray, move), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void trim()",   	                                     asMETHOD(StringArray, trim), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "String joinIntoString(const String& in) const",	         asMETHOD(StringArray, joinIntoString), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "String joinIntoString(const String& in, int) const",	     asMETHOD(StringArray, joinIntoString), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectMethod("StringArray", "String joinIntoString(const String& in, int, int) const", asMETHOD(StringArray, joinIntoString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void sort(bool)",   	                                 asMETHOD(StringArray, sort), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void ensureStorageAllocated(int)",   	                 asMETHOD(StringArray, ensureStorageAllocated), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("StringArray", "void minimiseStorageOverheads()",   	                 asMETHOD(StringArray, minimiseStorageOverheads), asCALL_THISCALL); jassert( r >= 0 );

	/*
    StringArray & 	operator= (const StringArray &)
    bool 	operator== (const StringArray &) const noexcept
    bool 	operator!= (const StringArray &) const noexcept
    String * 	begin () const noexcept
    String * 	end () const noexcept
    void 	appendNumbersToDuplicates (bool ignoreCaseWhenComparing, bool appendNumberToFirstInstance, CharPointer_UTF8 preNumberString=CharPointer_UTF8(nullptr), CharPointer_UTF8 postNumberString=CharPointer_UTF8(nullptr))
    String 	joinIntoString (StringRef separatorString, int startIndex=0, int numberOfElements=-1) const
 	*/

	// static methods/properties
	r = engine->SetDefaultNamespace("StringArray"); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("StringArray fromTokens(const String& in, bool)",                     asFUNCTIONPR(StringArray::fromTokens, (StringRef, bool), StringArray), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("StringArray fromTokens(const String& in, const String& in, const String& in)", asFUNCTIONPR(StringArray::fromTokens, (StringRef, StringRef, StringRef), StringArray), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("StringArray fromLines(const String& in)",                            asFUNCTION(StringArray::fromLines), asCALL_CDECL); jassert(r>=0);
	r = engine->SetDefaultNamespace(""); jassert(r >= 0);
}


} // end namespace

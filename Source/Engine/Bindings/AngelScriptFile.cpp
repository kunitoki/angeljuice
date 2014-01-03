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

//#include "AngelJuice_AngelScriptCommon.h"
//#include "AngelScriptCore.h"
//#include "AngelScriptString.h"
#include "AngelScriptFile.h"

#include "../ScriptableEngine.h"

namespace Bindings {


//==============================================================================

//------------------------------------------------------------------------------

void FileConstructor(File* thisPointer)
{
	new(thisPointer) File();
}

void FileConstructorByString(const String& path, File* thisPointer)
{
	new(thisPointer) File(path);
}

void FileConstructorByFile(const File& other, File* thisPointer)
{
	new(thisPointer) File(other);
}

void FileDestructor(File* thisPointer)
{
	thisPointer->~File();
}


//------------------------------------------------------------------------------

void ScriptableFile::registerTypes(asIScriptEngine* engine) const
{
	int r;

	r = engine->RegisterObjectType("File", sizeof(File), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); jassert(r>=0);
}


void ScriptableFile::registerFunctions(asIScriptEngine* engine) const
{
    int r;

    // constructors / destructors
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_CONSTRUCT, "void f()",                     asFUNCTION(FileConstructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_CONSTRUCT, "void f(const String& in)",     asFUNCTION(FileConstructorByString), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_CONSTRUCT, "void f(const File& in)",       asFUNCTION(FileConstructorByFile), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_DESTRUCT,  "void f()",                     asFUNCTION(FileDestructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	
	// operators
	r = engine->RegisterObjectMethod("File", "File& opAssign(const String& in)",                    asMETHODPR(File, operator=, (const String&), File&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "File& opAssign(const File& in)",                      asMETHODPR(File, operator=, (const File&), File&), asCALL_THISCALL); jassert( r >= 0 );
    
	/* 
    bool 	operator== (const File &) const
    bool 	operator!= (const File &) const
    bool 	operator< (const File &) const
    bool 	operator> (const File &) const
    */

    // methods
	r = engine->RegisterObjectMethod("File", "bool exists() const",                                 asMETHOD(File, exists), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool existsAsFile() const",                           asMETHOD(File, existsAsFile), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool isDirectory() const",                            asMETHOD(File, isDirectory), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "int64 getSize() const",                               asMETHOD(File, getSize), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "const String& getFullPathName() const",               asMETHOD(File, getFullPathName), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "String getFileName() const",                          asMETHOD(File, getFileName), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "String getRelativePathFrom(const File& in) const",    asMETHOD(File, getRelativePathFrom), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "String getFileExtension() const",                     asMETHOD(File, getFileExtension), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "bool hasFileExtension(const String& in) const",       asMETHOD(File, hasFileExtension), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "File withFileExtension(const String& in) const",      asMETHOD(File, withFileExtension), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "String getFileNameWithoutExtension() const",          asMETHOD(File, getFileNameWithoutExtension), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "int hashCode() const",                                asMETHOD(File, hashCode), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "int64 hashCode64() const",                            asMETHOD(File, hashCode64), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "File getChildFile(const String& in) const",           asMETHOD(File, getChildFile), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "File getSiblingFile(const String& in) const",         asMETHOD(File, getSiblingFile), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "File getParentDirectory() const",                     asMETHOD(File, getParentDirectory), asCALL_THISCALL); jassert(r>=0);
    r = engine->RegisterObjectMethod("File", "bool isAChildOf(const File& in) const",               asMETHOD(File, isAChildOf), asCALL_THISCALL); jassert(r>=0);
    //r = engine->RegisterObjectMethod("File", "File getNonexistentChildFile(const String& in, const String& in) const", asMETHOD(File, getNonexistentChildFile), asCALL_THISCALL); jassert(r>=0);
    //r = engine->RegisterObjectMethod("File", "File getNonexistentChildFile(const String& in, const String& in, bool) const", asMETHOD(File, getNonexistentChildFile), asCALL_THISCALL); jassert(r>=0);
    //r = engine->RegisterObjectMethod("File", "File getNonexistentSibling() const",                asMETHOD(File, getNonexistentSibling), asCALL_THISCALL); jassert(r>=0);
    //r = engine->RegisterObjectMethod("File", "File getNonexistentSibling(bool) const",            asMETHOD(File, getNonexistentSibling), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool hasWriteAccess() const",                         asMETHOD(File, hasWriteAccess), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool setReadOnly(bool) const",                      asMETHOD(File, setReadOnly), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool setReadOnly(bool, bool) const",                asMETHOD(File, setReadOnly), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool isHidden() const",                               asMETHOD(File, isHidden), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "File getLinkedTarget() const",                        asMETHOD(File, getLinkedTarget), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "Time getLastModificationTime() const",                asMETHOD(File, getLastModificationTime), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "Time getLastAccessTime() const",                      asMETHOD(File, getLastAccessTime), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "Time getCreationTime() const",                        asMETHOD(File, getCreationTime), asCALL_THISCALL); jassert(r>=0);
 	r = engine->RegisterObjectMethod("File", "bool setLastModificationTime(Time) const",            asMETHOD(File, setLastModificationTime), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool setLastAccessTime(Time) const",                  asMETHOD(File, setLastAccessTime), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool setCreationTime(Time) const",                    asMETHOD(File, setCreationTime), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "String getVersion() const",                           asMETHOD(File, getVersion), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool deleteFile() const",                             asMETHOD(File, deleteFile), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool deleteRecursively() const",                      asMETHOD(File, deleteRecursively), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool moveToTrash() const",                            asMETHOD(File, moveToTrash), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool moveFileTo(const File& in) const",               asMETHOD(File, moveFileTo), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool copyFileTo(const File& in) const",               asMETHOD(File, copyFileTo), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool copyDirectoryTo(const File& in) const",          asMETHOD(File, copyDirectoryTo), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "int getNumberOfChildFiles(int) const",                   asMETHOD(File, getNumberOfChildFiles), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "int getNumberOfChildFiles(int, const String& in) const", asMETHOD(File, getNumberOfChildFiles), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool containsSubDirectories() const",                 asMETHOD(File, containsSubDirectories), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "String loadFileAsString() const",                     asMETHOD(File, loadFileAsString), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "void readLines(StringArray& inout) const",            asMETHOD(File, readLines), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool appendText(const String &in) const",             asMETHOD(File, appendText), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool appendText(const String &in, bool) const",       asMETHOD(File, appendText), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool appendText(const String &in, bool, bool) const", asMETHOD(File, appendText), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool replaceWithText(const String &in) const",             asMETHOD(File, replaceWithText), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool replaceWithText(const String &in, bool) const",       asMETHOD(File, replaceWithText), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool replaceWithText(const String &in, bool, bool) const", asMETHOD(File, replaceWithText), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool hasIdenticalContentTo(const File& in) const",    asMETHOD(File, hasIdenticalContentTo), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "String getVolumeLabel() const",                       asMETHOD(File, getVolumeLabel), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "int getVolumeSerialNumber() const",                   asMETHOD(File, getVolumeSerialNumber), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "int64 getBytesFreeOnVolume() const",                  asMETHOD(File, getBytesFreeOnVolume), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "int64 getVolumeTotalSize() const",                    asMETHOD(File, getVolumeTotalSize), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool isOnCDRomDrive() const",                         asMETHOD(File, isOnCDRomDrive), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool isOnHardDisk() const",                           asMETHOD(File, isOnHardDisk), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool isOnRemovableDrive() const",                     asMETHOD(File, isOnRemovableDrive), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool startAsProcess() const",                         asMETHOD(File, startAsProcess), asCALL_THISCALL); jassert(r>=0);
	//r = engine->RegisterObjectMethod("File", "bool startAsProcess(const String& in) const",         asMETHOD(File, startAsProcess), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool revealToUser() const",                           asMETHOD(File, revealToUser), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool setAsCurrentWorkingDirectory() const",           asMETHOD(File, setAsCurrentWorkingDirectory), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool loadFileAsData(MemoryBlock& inout) const",       asMETHOD(File, loadFileAsData), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool appendData(const void_ptr, uint) const",         asMETHOD(File, appendData), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("File", "bool replaceWithData(const void_ptr, uint) const",    asMETHOD(File, replaceWithData), asCALL_THISCALL); jassert(r>=0);
	/* 
    Result 	create () const
    Result 	createDirectory () const
    int 	findChildFiles (Array< File > &results, int whatToLookFor, bool searchRecursively, const String &wildCardPattern="*") const
    FileInputStream * 	createInputStream () const
    FileOutputStream * 	createOutputStream (size_t bufferSize=0x8000) const
    */

	// static methods
	r = engine->SetDefaultNamespace("File"); jassert( r >= 0 );
	
	r = engine->RegisterEnum ("TypesOfFileToFind"); jassert(r>=0);
	r = engine->RegisterEnumValue ("TypesOfFileToFind", "findDirectories", File::findDirectories); jassert(r>=0);
	r = engine->RegisterEnumValue ("TypesOfFileToFind", "findFiles", File::findFiles); jassert(r>=0);
	r = engine->RegisterEnumValue ("TypesOfFileToFind", "findFilesAndDirectories", File::findFilesAndDirectories); jassert(r>=0);
	r = engine->RegisterEnumValue ("TypesOfFileToFind", "ignoreHiddenFiles", File::ignoreHiddenFiles); jassert(r>=0);

	r = engine->RegisterEnum ("SpecialLocationType"); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "userHomeDirectory", File::userHomeDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "userDocumentsDirectory", File::userDocumentsDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "userDesktopDirectory", File::userDesktopDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "userMusicDirectory", File::userMusicDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "userMoviesDirectory", File::userMoviesDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "userPicturesDirectory", File::userPicturesDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "userApplicationDataDirectory", File::userApplicationDataDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "commonApplicationDataDirectory", File::commonApplicationDataDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "commonDocumentsDirectory", File::commonDocumentsDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "tempDirectory", File::tempDirectory); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "currentExecutableFile", File::currentExecutableFile); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "currentApplicationFile", File::currentApplicationFile); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "invokedExecutableFile", File::invokedExecutableFile); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "hostApplicationPath", File::hostApplicationPath); jassert(r>=0);
	r = engine->RegisterEnumValue ("SpecialLocationType", "globalApplicationsDirectory", File::globalApplicationsDirectory); jassert(r>=0);
	
	r = engine->RegisterGlobalFunction("String descriptionOfSizeInBytes(int64)",                    asFUNCTION(File::descriptionOfSizeInBytes), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("File getSpecialLocation(const File::SpecialLocationType)",  asFUNCTION(File::getSpecialLocation), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("File createTempFile(const String& in)",                     asFUNCTION(File::createTempFile), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("File getCurrentWorkingDirectory()",                         asFUNCTION(File::getCurrentWorkingDirectory), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("File createLegalFileName(const String& in)",                asFUNCTION(File::createLegalFileName), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("File createLegalPathName(const String& in)",                asFUNCTION(File::createLegalPathName), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("bool areFileNamesCaseSensitive()",                          asFUNCTION(File::areFileNamesCaseSensitive), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("bool isAbsolutePath(const String& in)",                     asFUNCTION(File::isAbsolutePath), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("File createFileWithoutCheckingPath(const String& in)",      asFUNCTION(File::createFileWithoutCheckingPath), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("String addTrailingSeparator(const String& in)",             asFUNCTION(File::addTrailingSeparator), asCALL_CDECL); jassert(r>=0);
	
	r = engine->SetDefaultNamespace(""); jassert(r >= 0);
    
    /*    
    static void 	findFileSystemRoots (Array< File > &results)
    */
}



//==============================================================================

//------------------------------------------------------------------------------

void InputStreamDestructor(InputStream* thisPointer)
{
	thisPointer->~InputStream();
}


//------------------------------------------------------------------------------

void ScriptableInputStream::registerTypes(asIScriptEngine* engine) const
{
    /*
	int r;

	r = engine->RegisterObjectType("InputStream", sizeof(InputStream), asOBJ_APP_CLASS_D); jassert(r>=0);
	*/
}


void ScriptableInputStream::registerFunctions(asIScriptEngine* engine) const
{
    /*
    int r;

    // constructors / destructors
	r = engine->RegisterObjectBehaviour("InputStream", asBEHAVE_DESTRUCT,  "void f()",                     asFUNCTION(InputStreamDestructor), asCALL_CDECL_OBJLAST); jassert(r>=0);

	//r = engine->RegisterObjectBehaviour("InputStream", asBEHAVE_ASSIGNMENT, "InputStream &f(const InputStream &in)",     asMETHOD(asInputStream, operator =), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("InputStream", "int getPosition()",                                   asMETHOD(InputStream, getPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "bool setPosition(int)",                               asMETHOD(InputStream, setPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "void skipNextBytes(int)",                             asMETHOD(InputStream, skipNextBytes), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int getTotalLength()",                                asMETHOD(InputStream, getTotalLength), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "bool isExhausted()",                                  asMETHOD(InputStream, isExhausted), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "bool readBool()",                                     asMETHOD(InputStream, readBool), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int8 readByte()",                                     asMETHOD(InputStream, readByte), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int16 readShort()",                                   asMETHOD(InputStream, readShort), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int16 readShortBigEndian()",                          asMETHOD(InputStream, readShortBigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int readInt()",                                       asMETHOD(InputStream, readInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int readIntBigEndian()",                              asMETHOD(InputStream, readIntBigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int64 readInt64()",                                   asMETHOD(InputStream, readInt64), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int64 readInt64BigEndian()",                          asMETHOD(InputStream, readInt64BigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "float readFloat()",                                   asMETHOD(InputStream, readFloat), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "double readDouble()",                                 asMETHOD(InputStream, readDouble), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "int readCompressedInt()",                             asMETHOD(InputStream, readCompressedInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "String readNextLine()",                               asMETHOD(InputStream, readNextLine), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "String readString()",                                 asMETHOD(InputStream, readString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("InputStream", "String readEntireStreamAsString()",                   asMETHOD(InputStream, readEntireStreamAsString), asCALL_THISCALL); jassert( r >= 0 );
    */
}


#if 0

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

#endif


} // end namespace

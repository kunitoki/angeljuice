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
asFileInputStream::asFileInputStream(const asFile &f) : stream(f.file) {
	refCount = 1;
}
asFileInputStream::asFileInputStream(FileInputStream* s) : stream(*s) {
	refCount = 1;
}
asFileInputStream::~asFileInputStream() {
	jassert( refCount == 0 );
}

void asFileInputStream::addRef() {
	refCount++;
}
void asFileInputStream::release() {
	if( --refCount == 0 )
		delete this;
}

asFile* asFileInputStream::getFile() {
	return new asFile(stream.getFile());
}
int asFileInputStream::getPosition() {
	return (int)stream.getPosition();
}
bool asFileInputStream::setPosition (int pos) {
	return stream.setPosition(pos);
}
void asFileInputStream::skipNextBytes (int numBytesToSkip) {
	stream.skipNextBytes(numBytesToSkip);
}
asString* asFileInputStream::readNextLine() {
	return new asString(stream.readNextLine());
}
asString* asFileInputStream::readString() {
	return new asString(stream.readString());
}
asString* asFileInputStream::readEntireStreamAsString() {
	return new asString(stream.readEntireStreamAsString());
}
// int asFileInputStream::readIntoMemoryBlock (MemoryBlock& destBlock,int maxNumBytesToRead) {}


static void ConstructFileInputStream(const asFile& file, asFileInputStream *thisPointer) {
    new(thisPointer) asFileInputStream(file);
}


//==============================================================================
asFileOutputStream::asFileOutputStream(const asFile &f) : stream(f.file) {
	refCount = 1;
}
asFileOutputStream::asFileOutputStream(FileOutputStream* s) : stream(*s) {
	refCount = 1;
}
asFileOutputStream::~asFileOutputStream() {
	jassert( refCount == 0 );
}

void asFileOutputStream::addRef() {
	refCount++;
}
void asFileOutputStream::release() {
	if( --refCount == 0 )
		delete this;
}

asFile* asFileOutputStream::getFile() {
	return new asFile(stream.getFile());
}
int asFileOutputStream::getPosition() {
	return (int)stream.getPosition();
}
bool asFileOutputStream::setPosition (int pos) {
	return stream.setPosition(pos);
}
int asFileOutputStream::writeFromInputStream(asFileInputStream& in, int numBytesToWrite) {
	return stream.writeFromInputStream(in.stream,numBytesToWrite);
}


static void ConstructFileOutputStream(const asFile& file, asFileOutputStream *thisPointer) {
    new(thisPointer) asFileOutputStream(file);
}


//==============================================================================
asDirectoryIterator::asDirectoryIterator(const asFile& file, bool recurse, const asString& wildcard) :
	iterator(file.file,recurse,wildcard.buffer) {
	refCount = 1;
}
asDirectoryIterator::~asDirectoryIterator() {
	jassert( refCount == 0 );
}

void asDirectoryIterator::addRef() {
	refCount++;
}
void asDirectoryIterator::release() {
	if( --refCount == 0 )
		delete this;
}

asFile* asDirectoryIterator::getFile() {
	return new asFile(iterator.getFile());
}

static void ConstructDirectoryIterator(const asFile& text, bool recurse, const asString& wild, asDirectoryIterator *thisPointer) {
    new(thisPointer) asDirectoryIterator(text,recurse,wild);
}


//==============================================================================
asFileChooser::asFileChooser(const String& title, const File& file, const String& wild, const bool native) :
	chooser(title,file,wild,native) {
}
asFileChooser::asFileChooser(const asString& title, const asFile& file, const asString& wild, const bool native) :
	chooser(title.buffer,file.file,wild.buffer,native) {
}
asFileChooser::~asFileChooser() {
}

bool asFileChooser::browseForFileToOpen () { return chooser.browseForFileToOpen(); }
bool asFileChooser::browseForFileToSave(bool warn) { return chooser.browseForFileToSave(warn); }
bool asFileChooser::browseForDirectory() { return chooser.browseForDirectory(); }
asFile* asFileChooser::getResult() {
	return new asFile(chooser.getResult());
}

void ConstructFileChooser1(const asString& title, asFileChooser *thisPointer) {
	new(thisPointer) asFileChooser(title.buffer,File::nonexistent,String::empty,true);
}
void ConstructFileChooser2(const asString& title, const asFile& file, asFileChooser *thisPointer) {
    new(thisPointer) asFileChooser(title.buffer,file.file,String::empty,true);
}
void ConstructFileChooser3(const asString& title, const asFile& file, const asString& wild, asFileChooser *thisPointer) {
    new(thisPointer) asFileChooser(title.buffer,file.file,wild.buffer,true);
}
void ConstructFileChooser4(const asString& title, const asFile& file, const asString& wild, const bool native, asFileChooser *thisPointer) {
    new(thisPointer) asFileChooser(title.buffer,file.file,wild.buffer,native);
}
static void DestructFileChooser(asFileChooser *thisPointer) {
    thisPointer->~asFileChooser();
}


//==============================================================================
asFile::asFile() {
	refCount = 1;
}
asFile::asFile(const File &f) {
	refCount = 1;
	file = f;
}
asFile::asFile(const String &s) {
	refCount = 1;
	file = s;
}
asFile::asFile(const asFile &f) {
	refCount = 1;
	file = f.file;
}
asFile::asFile(const asString &s) {
	refCount = 1;
	file = s.buffer;
}
asFile::~asFile() {
	jassert( refCount == 0 );
}

void asFile::addRef() {
	refCount++;
}
void asFile::release() {
	if( --refCount == 0 )
		delete this;
}

bool operator==(const asFile &a, const asFile &b) {
	return a.file == b.file;
}
bool operator!=(const asFile &a, const asFile &b) {
	return a.file != b.file;
}
asFile &asFile::operator=(const asFile &other) {
	file = other.file;
	return *this;
}

asFile &asFile::operator=(const asString &other) {
	file = other.buffer;
	return *this;
}

asString* asFile::getFullPathName(){
	return new asString(file.getFullPathName());
}
asString* asFile::getFileName(){
	return new asString(file.getFileName());
}
asFile* asFile::getChildFile (const asString& relativePath){
	return new asFile(file.getChildFile(relativePath.buffer));
}
asFile* asFile::getSiblingFile (const asString& siblingFileName){
	return new asFile(file.getSiblingFile(siblingFileName.buffer));
}
asFile* asFile::getParentDirectory(){
	return new asFile(file.getParentDirectory());
}
asString* asFile::getRelativePathFrom (const asFile& directoryToBeRelativeTo){
	return new asString(file.getRelativePathFrom(directoryToBeRelativeTo.file));
}
asString* asFile::getFileExtension(){
	return new asString(file.getFileExtension());
}
asFile* asFile::withFileExtension (const asString& newExtension){
	return new asFile(file.withFileExtension(newExtension.buffer));
}
asString* asFile::getFileNameWithoutExtension(){
	return new asString(file.getFileNameWithoutExtension());
}
asFile* asFile::getNonexistentChildFile (const asString& prefix, const asString& suffix, bool putNumbersInBrackets){
	return new asFile(file.getNonexistentChildFile(prefix.buffer,suffix.buffer,putNumbersInBrackets));
}
asFile* asFile::getNonexistentSibling (const bool putNumbersInBrackets){
	return new asFile(file.getNonexistentSibling(putNumbersInBrackets));
}
asString* asFile::getVolumeLabel(){
	return new asString(file.getVolumeLabel());
}
//    const Time getLastModificationTime();
//    const Time getLastAccessTime();
//    const Time getCreationTime();
//    bool setLastModificationTime (const Time& newTime);
//    bool setLastAccessTime (const Time& newTime);
//    bool setCreationTime (const Time& newTime);

/*    int findChildFiles (OwnedArray<File>& results,
                    const bool searchForDirectories,
                    const bool searchRecursively,
                    const String& wildCardPattern = T("*")); */

// CHECK ERRORS !
asFileInputStream* asFile::createInputStream() {
	return new asFileInputStream(file.createInputStream());
}
asFileOutputStream* asFile::createOutputStream (const int bufferSize) {
	return new asFileOutputStream(file.createOutputStream(bufferSize));
}
//    bool loadFileAsData (MemoryBlock& result);
asString* asFile::loadFileAsString(){
	return new asString(file.loadFileAsString());
}

//    static void findFileSystemRoots (OwnedArray<File>& results) throw();
//    static const String descriptionOfSizeInBytes (const int64 bytes);
//    static const File createTempFile (const String& fileNameEnding) throw();
//    static const File getSystemTemporaryDirectory() throw();
//    static const File getCurrentApplicationFile();
//    static const File getCurrentWorkingDirectory() throw();
//    static const String createLegalFileName (const String& fileNameToFix) throw();
//    static const String createLegalPathName (const String& pathNameToFix) throw();

static void ConstructFile(asFile *thisPointer) {
	new(thisPointer) asFile();
}
static void ConstructFileByString(const asString& text, asFile *thisPointer) {
    new(thisPointer) asFile(text);
}

void asFile:: registerObjectType(asIScriptEngine *engine)
{
	int r;

	//--------------------------------------------------------------------------------------------------------------
	r = engine->RegisterObjectType("File", sizeof(asFile), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_CONSTRUCT,  "void f()",                    asFUNCTION(ConstructFile), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_CONSTRUCT,  "void f(const String& in)",    asFUNCTION(ConstructFileByString), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_ADDREF,     "void f()",                    asMETHOD(asFile,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_RELEASE,    "void f()",                    asMETHOD(asFile,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_ASSIGNMENT, "File &f(const File &in)",     asMETHODPR(asFile, operator =, (const asFile&), asFile&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("File", asBEHAVE_ASSIGNMENT, "File &f(const String &in)",   asMETHODPR(asFile, operator =, (const asString&), asFile&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,       "bool f(const File &in, const File &in)",    asFUNCTIONPR(operator==, (const asFile &, const asFile &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,    "bool f(const File &in, const File &in)",    asFUNCTIONPR(operator!=, (const asFile &, const asFile &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,       "bool f(const File &in, const String &in)",  asFUNCTIONPR(operator==, (const asFile &, const asString &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,    "bool f(const File &in, const String &in)",  asFUNCTIONPR(operator!=, (const asFile &, const asString &), bool), asCALL_CDECL); jassert( r >= 0 );

	//--------------------------------------------------------------------------------------------------------------
	r = engine->RegisterObjectType("FileInputStream", sizeof(asFileInputStream), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileInputStream", asBEHAVE_CONSTRUCT,  "void f(const File &in)",      asFUNCTION(ConstructFileInputStream), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileInputStream", asBEHAVE_ADDREF,     "void f()",                    asMETHOD(asFileInputStream,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileInputStream", asBEHAVE_RELEASE,    "void f()",                    asMETHOD(asFileInputStream,release), asCALL_THISCALL); jassert( r >= 0 );

	//--------------------------------------------------------------------------------------------------------------
	r = engine->RegisterObjectType("FileOutputStream", sizeof(asFileOutputStream), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileOutputStream", asBEHAVE_CONSTRUCT,  "void f(const File &in)",     asFUNCTION(ConstructFileOutputStream), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileOutputStream", asBEHAVE_ADDREF,     "void f()",                   asMETHOD(asFileOutputStream,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileOutputStream", asBEHAVE_RELEASE,    "void f()",                   asMETHOD(asFileOutputStream,release), asCALL_THISCALL); jassert( r >= 0 );


	//--------------------------------------------------------------------------------------------------------------
	r = engine->RegisterObjectMethod("File", "bool exists()",                                     asMETHOD(File,exists), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool existsAsFile()",                               asMETHOD(File,existsAsFile), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool isDirectory()",                                asMETHOD(File,isDirectory), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "int getSize()",                                     asMETHOD(File,getSize), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "String@ getFullPathName()",                         asMETHOD(asFile,getFullPathName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "String@ getFileName()",                             asMETHOD(asFile,getFileName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "String@ getFileExtension()",                        asMETHOD(asFile,getFileExtension), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "String@ getFileNameWithoutExtension()",             asMETHOD(asFile,getFileNameWithoutExtension), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "int hashCode()",                                    asMETHOD(File,hashCode), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "File@ getChildFile(const String& in)",              asMETHOD(asFile,getChildFile), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "File@ getSiblingFile(const String& in)",            asMETHOD(asFile,getSiblingFile), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "File@ getParentDirectory()",                        asMETHOD(asFile,getParentDirectory), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "String@ getRelativePathFrom(const File& in)",       asMETHOD(asFile,getRelativePathFrom), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool isAChildOf(const File& in)",                   asMETHOD(File,isAChildOf), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool hasFileExtension(const String& in)",           asMETHOD(File,hasFileExtension), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "File@ withFileExtension(const String& in)",         asMETHOD(asFile,withFileExtension), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "File@ getNonexistentChildFile(const String& in,const String& in,const bool)", asMETHOD(asFile,getNonexistentChildFile), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "File@ getNonexistentSibling(const bool)",           asMETHOD(asFile,getNonexistentSibling), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool hasWriteAccess()",                             asMETHOD(File,hasWriteAccess), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool setReadOnly(const bool,const bool)",           asMETHOD(File,setReadOnly), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool create()",                                     asMETHOD(File,create), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool createDirectory()",                            asMETHOD(File,createDirectory), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool deleteFile()",                                 asMETHOD(File,deleteFile), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool deleteRecursively()",                          asMETHOD(File,deleteRecursively), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool setAsCurrentWorkingDirectory()",               asMETHOD(File,setAsCurrentWorkingDirectory), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool moveFileTo(const File& in)",                   asMETHOD(File,moveFileTo), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool copyFileTo(const File& in)",                   asMETHOD(File,copyFileTo), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool copyDirectoryTo(const File& in)",              asMETHOD(File,copyDirectoryTo), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "int getNumberOfChildFiles(const bool, const String& in)",  asMETHOD(File,getNumberOfChildFiles), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool appendText(const String& in)",                 asMETHOD(File,appendText), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("File", "bool replaceWithText(const String& in)",            asMETHOD(File,replaceWithText), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "String@ loadFileAsString()",                        asMETHOD(asFile,loadFileAsString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "String@ getVolumeLabel()",                          asMETHOD(asFile,getVolumeLabel), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "int getVolumeSerialNumber()",                       asMETHOD(File,getVolumeSerialNumber), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "int getBytesFreeOnVolume()",                        asMETHOD(File,getBytesFreeOnVolume), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool isOnCDRomDrive()",                             asMETHOD(File,isOnCDRomDrive), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool isOnHardDisk()",                               asMETHOD(File,isOnHardDisk), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("File", "bool isOnRemovableDrive()",                         asMETHOD(File,isOnRemovableDrive), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "bool startAsProcess(const String& in)",             asMETHOD(File,startAsProcess), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "FileInputStream@ createInputStream()",              asMETHOD(asFile,createInputStream), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("File", "FileOutputStream@ createOutputStream(int)",         asMETHOD(asFile,createOutputStream), asCALL_THISCALL); jassert( r >= 0 );

/*    int findChildFiles (OwnedArray<File>& results,
                        const bool searchForDirectories,
                        const bool searchRecursively,
                        const String& wildCardPattern = T("*")); */

//    const Time getLastModificationTime();
//    const Time getLastAccessTime();
//    const Time getCreationTime();
//    bool setLastModificationTime (const Time& newTime);
//    bool setLastAccessTime (const Time& newTime);
//    bool setCreationTime (const Time& newTime);

//    static void findFileSystemRoots (OwnedArray<File>& results) throw();
//    static const File createTempFile (const String& fileNameEnding) throw();
//    static const File getSystemTemporaryDirectory() throw();
//    static const File getCurrentApplicationFile();
//    static const File getCurrentWorkingDirectory() throw();
//    static const String createLegalFileName (const String& fileNameToFix) throw();
//    static const String createLegalPathName (const String& pathNameToFix) throw();

	//--------------------------------------------------------------------------------------------------------------
	r = engine->RegisterObjectMethod("FileInputStream", "File@ getFile()",                                     asMETHOD(asFileInputStream,getFile), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "int getPosition()",                                   asMETHOD(asFileInputStream,getPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "bool setPosition(int)",                               asMETHOD(asFileInputStream,setPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "void skipNextBytes(int)",                             asMETHOD(asFileInputStream,skipNextBytes), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "int getTotalLength()",                                asMETHOD(FileInputStream,getTotalLength), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "bool isExhausted()",                                  asMETHOD(FileInputStream,isExhausted), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "bool readBool()",                                     asMETHOD(FileInputStream,readBool), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "int8 readByte()",                                     asMETHOD(FileInputStream,readByte), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "int16 readShort()",                                   asMETHOD(FileInputStream,readShort), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "int16 readShortBigEndian()",                          asMETHOD(FileInputStream,readShortBigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "int readInt()",                                       asMETHOD(FileInputStream,readInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "int readIntBigEndian()",                              asMETHOD(FileInputStream,readIntBigEndian), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("FileInputStream", "int64 readInt64()",                                   asMETHOD(FileInputStream,readInt64), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("FileInputStream", "int64 readInt64BigEndian()",                          asMETHOD(FileInputStream,readInt64BigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "float readFloat()",                                   asMETHOD(FileInputStream,readFloat), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "double readDouble()",                                 asMETHOD(FileInputStream,readDouble), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "int readCompressedInt()",                             asMETHOD(FileInputStream,readCompressedInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "String@ readNextLine()",                              asMETHOD(asFileInputStream,readNextLine), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "String@ readString()",                                asMETHOD(asFileInputStream,readString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileInputStream", "String@ readEntireStreamAsString()",                  asMETHOD(asFileInputStream,readEntireStreamAsString), asCALL_THISCALL); jassert( r >= 0 );


	//--------------------------------------------------------------------------------------------------------------
	r = engine->RegisterObjectMethod("FileOutputStream", "File@ getFile()",                                    asMETHOD(asFileOutputStream,getFile), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "int getPosition()",                                  asMETHOD(asFileOutputStream,getPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "bool setPosition(int)",                              asMETHOD(asFileOutputStream,setPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeBool(bool)",                               asMETHOD(FileOutputStream,writeBool), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeByte(int8)",                               asMETHOD(FileOutputStream,writeByte), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeShort(int16)",                             asMETHOD(FileOutputStream,writeShort), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeShortBigEndian(int16)",                    asMETHOD(FileOutputStream,writeShortBigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeInt(int)",                                 asMETHOD(FileOutputStream,writeInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeIntBigEndian(int)",                        asMETHOD(FileOutputStream,writeIntBigEndian), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("FileOutputStream", "void writeInt64(int64)",                             asMETHOD(FileOutputStream,writeInt64), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("FileOutputStream", "void writeInt64BigEndian(int64)",                    asMETHOD(FileOutputStream,writeInt64BigEndian), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeFloat(float)",                             asMETHOD(FileOutputStream,writeFloat), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeDouble(double)",                           asMETHOD(FileOutputStream,writeDouble), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeCompressedInt(int)",                       asMETHOD(FileOutputStream,writeCompressedInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeString(const String& in)",                 asMETHOD(FileOutputStream,writeString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "void writeText(const String& in,bool,bool)",         asMETHOD(FileOutputStream,writeText), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileOutputStream", "int writeFromInputStream(FileInputStream& in,int)",  asMETHOD(asFileOutputStream,writeFromInputStream), asCALL_THISCALL); jassert( r >= 0 );


	//--------------------------------------------------------------------------------------------------------------
	r = engine->RegisterObjectType("DirectoryIterator", sizeof(asDirectoryIterator), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("DirectoryIterator", asBEHAVE_CONSTRUCT,  "void f(const File &in,bool,const String&in)", asFUNCTION(ConstructDirectoryIterator), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("DirectoryIterator", asBEHAVE_ADDREF,     "void f()",                   asMETHOD(asDirectoryIterator,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("DirectoryIterator", asBEHAVE_RELEASE,    "void f()",                   asMETHOD(asDirectoryIterator,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("DirectoryIterator", "bool next()",										asMETHOD(DirectoryIterator,next), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("DirectoryIterator", "float getEstimatedProgress()",						asMETHOD(DirectoryIterator,getEstimatedProgress), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("DirectoryIterator", "File@ getFile()",						            asMETHOD(asDirectoryIterator,getFile), asCALL_THISCALL); jassert( r >= 0 );


	//--------------------------------------------------------------------------------------------------------------
	r = engine->RegisterObjectType("FileChooser", sizeof(asFileChooser), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileChooser", asBEHAVE_CONSTRUCT,  "void f(const String& in)",                                      asFUNCTION(ConstructFileChooser1), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileChooser", asBEHAVE_CONSTRUCT,  "void f(const String& in,const File& in)",                       asFUNCTION(ConstructFileChooser2), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileChooser", asBEHAVE_CONSTRUCT,  "void f(const String& in,const File& in,const String& in)",      asFUNCTION(ConstructFileChooser3), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileChooser", asBEHAVE_CONSTRUCT,  "void f(const String& in,const File& in,const String& in,bool)", asFUNCTION(ConstructFileChooser4), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("FileChooser", asBEHAVE_DESTRUCT,   "void f()",                                                      asFUNCTION(DestructFileChooser), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileChooser", "bool browseForFileToOpen()",                 asMETHOD(asFileChooser,browseForFileToOpen), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileChooser", "bool browseForFileToSave(bool)",             asMETHOD(asFileChooser,browseForFileToSave), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileChooser", "bool browseForDirectory()",                  asMETHOD(asFileChooser,browseForDirectory), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("FileChooser", "File@ getResult()",                          asMETHOD(asFileChooser,getResult), asCALL_THISCALL); jassert( r >= 0 );
}


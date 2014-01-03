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

#ifndef __ANGELJUICE_ANGELSCRIPTFILE_HEADER__
#define __ANGELJUICE_ANGELSCRIPTFILE_HEADER__

#include "juce.h"

class asString;
class asFile;


//==============================================================================
/** Manages the file input streams in angel scripts

    @see AngelScriptEngine, FileInputStream
*/
class asFileInputStream
{
public:

	asFileInputStream (const asFile& fileToRead);
	asFileInputStream (FileInputStream* s);

	void addRef();
	void release();

    asFile* getFile();
    int getPosition();
    bool setPosition (int pos);
    void skipNextBytes (int numBytesToSkip);
    asString* readNextLine();
	asString* readString();
	asString* readEntireStreamAsString();
//    int readIntoMemoryBlock (MemoryBlock& destBlock,int maxNumBytesToRead);

	FileInputStream stream;

protected:
	~asFileInputStream();
	int refCount;
};


//==============================================================================
/** Manages the file output streams in angel scripts

    @see AngelScriptEngine, FileOutputStream
*/
class asFileOutputStream
{
public:

	asFileOutputStream (const asFile& fileToWriteTo);
	asFileOutputStream (FileOutputStream* s);

	void addRef();
	void release();

    asFile* getFile();
    int getPosition();
    bool setPosition (int pos);

	int writeFromInputStream(asFileInputStream& in, int numBytesToWrite);

	FileOutputStream stream;

protected:
	~asFileOutputStream();
	int refCount;
};


//==============================================================================
/** Manages the file output streams in angel scripts

    @see AngelScriptEngine, DirectoryIterator
*/
class asDirectoryIterator
{
public:

	asDirectoryIterator (const asFile& file, bool recurse, const asString& wildcard);

	void addRef();
	void release();

    asFile* getFile();

	DirectoryIterator iterator;

protected:
	~asDirectoryIterator();
	int refCount;
};

//==============================================================================
/** Manages the files in angel scripts

    @see AngelScriptEngine, File
*/
class asFile
{
public:

	asFile();
	asFile(const File& other);
	asFile(const asFile& other);
	asFile(const String& s);
	asFile(const asString& s);

	void addRef();
	void release();

	asFile& operator=(const asFile &other);
	asFile& operator=(const asString &other);

    asString* getFullPathName();
	asString* getFileName();
    asFile* getChildFile (const asString& relativePath);
    asFile* getSiblingFile (const asString& siblingFileName);
    asFile* getParentDirectory();
    asString* getRelativePathFrom (const asFile& directoryToBeRelativeTo);
    asString* getFileExtension();
    asFile* withFileExtension (const asString& newExtension);
    asString* getFileNameWithoutExtension();
    asFile* getNonexistentChildFile (const asString& prefix,const asString& suffix, bool putNumbersInBrackets);
    asFile* getNonexistentSibling (const bool putNumbersInBrackets);
    asFileInputStream* createInputStream();
    asFileOutputStream* createOutputStream (const int bufferSize);
//    bool loadFileAsData (MemoryBlock& result);
    asString* loadFileAsString();
    asString* getVolumeLabel();

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
//    static const String descriptionOfSizeInBytes (const int64 bytes);
//    static const File createTempFile (const String& fileNameEnding) throw();
//    static const File getSystemTemporaryDirectory() throw();
//    static const File getCurrentApplicationFile();
//    static const File getCurrentWorkingDirectory() throw();
//    static const String createLegalFileName (const String& fileNameToFix) throw();
//    static const String createLegalPathName (const String& pathNameToFix) throw();

	static void registerObjectType(asIScriptEngine *engine);

	File file;

protected:
	~asFile();
	int refCount;
};


//==============================================================================
/** Manages the file chooser in angel scripts

    @see AngelScriptEngine, angelscript
*/
class asFileChooser
{
public:

	asFileChooser(const String& title,const File& startDir,const String& wild,const bool useNativeBox);
	asFileChooser(const asString& title,const asFile& startDir,const asString& wild,const bool useNativeBox);
	~asFileChooser();

	bool browseForFileToOpen ();
    bool browseForFileToSave(bool warn);
    bool browseForDirectory();

	asFile* getResult();

	FileChooser chooser;
};


#endif	// __ANGELJUICE_ANGELSCRIPTFILE_HEADER__

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

#ifndef __ANGELJUICE_ANGELSCRIPTCORE_H_INCLUDED__
#define __ANGELJUICE_ANGELSCRIPTCORE_H_INCLUDED__

#include "../../../JuceLibraryCode/JuceHeader.h"

#include "../ScriptablePlugin.h"

namespace Bindings {


//==============================================================================
/** Manages Alerts and Error reporting in angel scripts

    @see AngelScriptEngine, AlertWindow
*/
class ScriptableCore : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages standard <math.h> functions in angel scripts

    @see AngelScriptEngine, <math.h>
*/
class ScriptableMath : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages ByteOrder functions in angel scripts

    @see AngelScriptEngine, ByteOrder
*/
class ScriptableByteOrder : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages BigInteger class in angel scripts

    @see AngelScriptEngine, BigInteger
*/
class ScriptableBigInteger : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages Random number generation in angel scripts

    @see AngelScriptEngine, Random
*/
class ScriptableRandom : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages the SystemStats in angel scripts

    @see AngelScriptEngine, SystemStats
*/
class ScriptableSystemStats : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages the Time in angel scripts

    @see AngelScriptEngine, Time
*/
class ScriptableTime : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages the RelativeTime in angel scripts

    @see AngelScriptEngine, RelativeTime
*/
class ScriptableRelativeTime : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages the MemoryBlock in angel scripts

    @see AngelScriptEngine, MemoryBlock
*/
class ScriptableMemoryBlock : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages the Array<T> in angel scripts

    @see AngelScriptEngine, Array
*/
class ScriptableArrayTemplate : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};



#if 0
//==============================================================================
/** Manages MD5 in angel scripts

    @see AngelScriptEngine, MD5
*/
class asMD5
{
public:

	asMD5 ();
	asMD5 (const MD5& other);
	asMD5 (const String& text);
	asMD5 (const File& file);
	asMD5 (const asMD5& other);
	asMD5 (const asString& text);
//	asMD5 (const asFile& file);
//	asMD5 (InputStream& input, int numBytesToRead = -1);

	void addRef();
	void release();

	asMD5& operator= (const asMD5& other);

	asString* toHexString();
//	MemoryBlock getRawChecksumData();

	static void registerObjectType(asIScriptEngine *engine);

	MD5 md5;

protected:
	~asMD5();
	int refCount;
};

//    bool operator== (const asMD5& other) const;
//    bool operator!= (const asMD5& other) const;


//==============================================================================
/** Manages Time in angel scripts

    @see AngelScriptEngine, Time
*/
class asTime
{
public:

	asTime ();
	asTime (const Time& other);
	asTime (const asTime& other);
	asTime (int millisecondsSinceEpoch); // int64
	asTime (const int year,
          const int month,
          const int day,
          const int hours,
          const int minutes,
          const int seconds = 0,
          const int milliseconds = 0);

	void addRef();
	void release();

	asTime& operator= (const asTime& other);

	static void registerObjectType(asIScriptEngine *engine);

	Time time;

protected:
	~asTime();
	int refCount;
};


//==============================================================================
/** Manages the input streams in angel scripts

    @see AngelScriptEngine, InputStream
*/
class asInputStream
{
public:

	asInputStream (InputStream* s);

	void addRef();
	void release();

	asInputStream& operator=(asInputStream &other);

    int getPosition();
    bool setPosition (int pos);
    void skipNextBytes (int numBytesToSkip);
	int getTotalLength();
	bool isExhausted();
	bool readBool();
	char readByte();
	short readShort();
	short readShortBigEndian();
	int readInt();
	int readIntBigEndian();
	int64 readInt64();
	int64 readInt64BigEndian();
	float readFloat();
	double readDouble();
	int readCompressedInt();
    asString* readNextLine();
	asString* readString();
	asString* readEntireStreamAsString();
//    int readIntoMemoryBlock (MemoryBlock& destBlock,int maxNumBytesToRead);

	static void registerObjectType(asIScriptEngine *engine);

	InputStream* stream;

protected:
	~asInputStream();
	int refCount;
};

#endif

} // end namespace


#endif	// __ANGELJUICE_ANGELSCRIPTCORE_H_INCLUDED__

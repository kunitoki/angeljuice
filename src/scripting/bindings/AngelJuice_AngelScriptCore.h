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

#ifndef __ANGELJUICE_ANGELSCRIPTCORE_HEADER__
#define __ANGELJUICE_ANGELSCRIPTCORE_HEADER__

#include "juce.h"

class asString;


//==============================================================================
/** Manages standard math.h functions in angel scripts

    @see AngelScriptEngine, Random
*/
class asMath
{
public:
	static void registerObjectType(asIScriptEngine *engine);
};


//==============================================================================
/** Manages Random number generation in angel scripts

    @see AngelScriptEngine, Random
*/
class asRandom
{
public:
	static void registerObjectType(asIScriptEngine *engine);
};


//==============================================================================
/** Manages the SystemStats in angel scripts

    @see AngelScriptEngine, SystemStats
*/
class asSystemStats
{
public:

	asString* getJUCEVersion();
	asString* getOperatingSystemName();
	asString* getCpuVendor();

	static void registerObjectType(asIScriptEngine *engine);
};


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
/** Manages Alerts and Error reporting in angel scripts

    @see AngelScriptEngine, AlertWindow
*/
class asCore
{
public:
	static void registerObjectType(asIScriptEngine *engine);
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


#endif	// __ANGELJUICE_ANGELSCRIPTCORE_HEADER__

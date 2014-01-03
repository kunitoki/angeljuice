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

#ifndef __ANGELJUICE_ANGELSCRIPTSOCKET_HEADER__
#define __ANGELJUICE_ANGELSCRIPTSOCKET_HEADER__

#include "juce.h"

class asString;


//==============================================================================
/** Manages the URLs in angel scripts

    @see AngelScriptEngine, URL
*/
class asURL
{
public:

    asURL ();
    asURL (const String& url);
    asURL (const asString& url);
    asURL (const URL& other);
    asURL (const asURL& other);

	void addRef();
	void release();

    asURL& operator= (const asURL& other);

	asString* toString (const bool includeGetParameters);
    asURL* withParameter (const asString& parameterName, const asString& parameterValue);

//    const StringPairArray& getParameters() const;
    asInputStream* createInputStream (const bool usePostCommand) const;
    asInputStream* createPostInputStream (const String& postText) const;
//    bool readEntireBinaryStream (MemoryBlock& destData,
//                                 const bool usePostCommand = false) const;
//    XmlElement* readEntireXmlStream (const bool usePostCommand = false) const;
    asString* readEntireTextStream (const bool usePostCommand);

	static void registerObjectType(asIScriptEngine *engine);

	URL url;

protected:
	~asURL();
	int refCount;
};



//==============================================================================
/** Manages the URLs in angel scripts

    @see AngelScriptEngine, URL
*/
/*
class asInterprocessConnection : public InterprocessConnection
{
public:

    asInterprocessConnection (const bool callbacksOnMessageThread = true,
                              const uint32 magicMessageHeaderNumber = 0xf2b49e2c);
	~asInterprocessConnection();

	void addRef();
	void release();

	//==============================================================================
	bool connectToSocket (const String& hostName,
                          const int portNumber,
                          const int timeOutMillisecs);
    bool connectToPipe (const String& pipeName);
    bool createPipe (const String& pipeName);
    void disconnect();
    bool isConnected() const;

	bool sendMessage (const MemoryBlock& message);

	void connectionMade();
    void connectionLost();
    void messageReceived (const MemoryBlock& message);

	//==============================================================================
	void setClassAndObject (const String& className,const String& objectName);
	void doExecuteContext ();

	//==============================================================================
	static void registerObjectType(asIScriptEngine *engine);

protected:
	String className;
	String objectName;
	void* methodOwner;
	Array<int> methodId;
	asIScriptContext* eventContext;
};
*/


#endif	// __ANGELJUICE_ANGELSCRIPTSOCKET_HEADER__

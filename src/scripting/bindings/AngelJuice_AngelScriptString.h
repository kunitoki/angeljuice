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

#ifndef __ANGELJUICE_ANGELSCRIPTSTRING_HEADER__
#define __ANGELJUICE_ANGELSCRIPTSTRING_HEADER__

#include "juce.h"
#include "../../utils/AngelJuice_RegularExpression.h"

class asFile;


//==============================================================================
/** Manages Strings in angel scripts

    @see AngelScriptengine, String
*/
class asString
{
public:

    asString ();
    asString (const asString &other);
    asString (const char s);
    asString (const char* s);
    asString (const tchar s);
    asString (const tchar* s);
    asString (const String &s);

    void addRef ();
    void release ();

    asString& operator= (const asString &other);
    asString& operator+= (const asString &other);

    bool equalsIgnoreCase (const asString& other);
    int compare (const asString& other);
    int compareIgnoreCase (const asString& other);
    int compareLexicographically (const asString& other);
    bool startsWith (const asString& text);
    bool startsWithIgnoreCase (const asString& text);
    bool endsWith (const asString& text);
    bool endsWithIgnoreCase (const asString& text);
    bool contains (const asString& text);
    bool containsIgnoreCase (const asString& text);
    bool containsWholeWord (const asString& wordToLookFor);
    bool containsWholeWordIgnoreCase (const asString& wordToLookFor);
    bool containsAnyOf (const asString& charactersItMightContain);
    bool containsOnly (const asString& charactersItMightContain);
    bool matchesWildcard (const asString& wildcard, const bool ignoreCase);
    int indexOf (const asString& other);
    int indexOf (const int startIndex, const asString& textToLookFor);
    int indexOfIgnoreCase (const asString& textToLookFor);
    int indexOfIgnoreCase (const int startIndex, const asString& textToLookFor);
    int lastIndexOf (const asString& textToLookFor);
    int lastIndexOfIgnoreCase (const asString& textToLookFor);
    asString* substring (int startIndex, int endIndex);
    asString* substring (const int startIndex);
    asString* dropLastCharacters (const int numberToDrop);
    asString* fromFirstOccurrenceOf (const asString& substringToStartFrom,
                                     const bool includeSubStringInResult,
                                     const bool ignoreCase);
    asString* fromLastOccurrenceOf (const asString& substringToFind,
                                    const bool includeSubStringInResult,
                                    const bool ignoreCase);
    asString* upToFirstOccurrenceOf (const asString& substringToEndWith,
                                     const bool includeSubStringInResult,
                                     const bool ignoreCase);
    asString* upToLastOccurrenceOf (const asString& substringToFind,
                                    const bool includeSubStringInResult,
                                    const bool ignoreCase);
    asString* trim();
    asString* trimStart();
    asString* trimEnd();
    asString* toUpperCase();
    asString* toLowerCase();
    asString* replaceSection (int startIndex,
                                 int numCharactersToReplace,
                                 const asString& stringToInsert);
    asString* replace (const asString& stringToReplace,
                          const asString& stringToInsertInstead,
                          const bool ignoreCase = false);
    asString* replaceCharacter (const asString& characterToReplace,
                                   const asString& characterToInsertInstead);
    asString* replaceCharacters (const asString& charactersToReplace,
                                    const asString& charactersToInsertInstead);
    asString* retainCharacters (const asString& charactersToRetain);
    asString* removeCharacters (const asString& charactersToRemove);
    asString* initialSectionContainingOnly (const asString& charactersToRetain);
    asString* initialSectionNotContaining (const asString& charactersNotToRetain);
    asString* unquoted();
    asString* quoted (const asString& quoteCharacter = T('"'));


	String buffer;


	static void registerObjectType (asIScriptEngine *engine);

protected:
	~asString();
	int refCount;
};


//==============================================================================
/** Manages regular expressions in angel scripts

    @see AngelScriptengine, RegularExpression
*/

class asRegularExpression
{
public:
    asRegularExpression();
    asRegularExpression(const asString& pattern);

    asString* getMatch (int num, int* start, int* end);

    static void registerObjectType (asIScriptEngine *engine);

    RegularExpression regex;
};


//==============================================================================
/** Manages xml elements in angel scripts

    @see AngelScriptengine, XmlElement
*/
class asXmlElement
{
public:
    asXmlElement(XmlElement* other);
    asXmlElement(const XmlElement& other);
    asXmlElement(const String& tagName);
    asXmlElement(const asString& tagName);
    asXmlElement(const asXmlElement& other);

    void addRef();
    void release();
    asXmlElement& operator=(const asXmlElement &other);

    bool isEquivalentTo (asXmlElement* other, const bool ignoreOrderOfAttributes);
    asString* createDocument (const asString& dtdToUse, const bool allOnOneLine, const bool includeXmlHeader, const asString& encodingType);
    bool writeToFile (const asFile& destinationFile, const asString& dtdToUse, const asString& encodingType);
    asString* getTagName();
    bool hasTagName (const asString& possibleTagName);
    int getNumAttributes();
    asString* getAttributeName (const int attributeIndex);
    asString* getAttributeValue (const int attributeIndex);
    bool hasAttribute (const asString& attributeName);
    asString* getStringAttribute (const asString& attributeName,const asString& defaultReturnValue);
    bool compareAttribute (const asString& attributeName, const asString& stringToCompareAgainst,const bool ignoreCase);
    int getIntAttribute (const asString& attributeName,const int defaultReturnValue = 0);
    double getDoubleAttribute (const asString& attributeName,const double defaultReturnValue = 0.0);
    bool getBoolAttribute (const asString& attributeName,const bool defaultReturnValue = false);
    void setAttribute (const asString& attributeName,const asString& newValue);
    void setAttribute (const asString& attributeName,const int newValue);
    void setAttribute (const asString& attributeName,const double newValue);
    void removeAttribute (const asString& attributeName);
    void removeAllAttributes();
    asXmlElement* getFirstChildElement();
    asXmlElement* getNextElement();
    int getNumChildElements();
    asXmlElement* getChildElement (const int index);
    asXmlElement* getChildByName (const asString& tagNameToLookFor);
    void addChildElement (asXmlElement* newChildElement);
    void insertChildElement (asXmlElement* newChildNode,int indexToInsertAt);
    bool replaceChildElement (asXmlElement* currentChildElement, asXmlElement* newChildNode);
    void removeChildElement (asXmlElement* childToRemove, const bool shouldDeleteTheChild);
    void deleteAllChildElements();
    void deleteAllChildElementsWithTagName (const asString& tagName);
//    void sortChildElements (ElementComparator<XmlElement*>& comparatorToUse);
    bool isTextElement();
    asString* getText();
    asString* getAllSubText();
    void addTextElement (const asString& text);
    void deleteAllTextElements();

    static void registerObjectType (asIScriptEngine *engine);

    XmlElement element;

protected:
    ~asXmlElement();
    int refCount;
};


//==============================================================================
/** Manages xml documents in angel scripts

    @see AngelScriptengine, XmlDocument
*/
class asXmlDocument
{
public:
    asXmlDocument(const asString& s);
    asXmlDocument(const asFile& f);

    void addRef();
    void release();

    asXmlElement* getDocumentElement ();
    asXmlElement* getDocumentElement (const bool onlyReadOuterDocumentElement);
    asString* getLastParseError();

    static void registerObjectType (asIScriptEngine *engine);

    XmlDocument document;

protected:
    ~asXmlDocument();
    int refCount;
};


#endif	// __ANGELJUICE_ANGELSCRIPTSTRING_HEADER__

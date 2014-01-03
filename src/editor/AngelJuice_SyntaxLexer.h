/*
  ==============================================================================

   This file is part of the eJUCE library
   which is based on Raw Material Software ltd. JUCE

   eJUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   eJUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eJUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
   Boston, MA 02111-1307 USA

   @author	Asnaghi Lucio

  ==============================================================================
*/

#ifndef __ANGELJUICE_SYNTAXLEXER_HEADER__
#define __ANGELJUICE_SYNTAXLEXER_HEADER__

#include "../AngelJuice_config.h"
#include <ctype.h>


class SyntaxDocument;


//==============================================================================
/** Typedefs with the default states of the lexer. We are specifying here for
	the use with the default CPP lexer, but you could specify your own in your
	specific lexer as they are used mainly to define styles and to cut up
	the sections in the parsed text.
*/
enum
{
	LEX_DEFAULT = 0,
	LEX_STARTCOMMENT,
	LEX_ENDCOMMENT,
	LEX_COMMENT,
	LEX_COMMENTLINE,
	LEX_NUMBER,
	LEX_WORD,
	LEX_WORD2,
	LEX_WORD3,
	LEX_WORD4,
	LEX_STRING,
	LEX_CHARACTER,
	LEX_PREPROCESSOR,
	LEX_OPERATOR,
	LEX_IDENTIFIER,
	LEX_STRINGEOL,

	LEX_NUMSTYLES
};


//==============================================================================
/** Utility class that holds a current style
*/
struct SyntaxStyle
{
	Colour textColour;
};


//==============================================================================
/** Utility class to parse a string following a source code syntax style

*/
class SyntaxLexer
{
public:

	tchar ch;
	tchar chNext;

	int startPosition;
	int currentIndex;
	int maxLength;

	int currentState;
	int tokenIndex;

	String* allText;
	SyntaxDocument* document;

	StringArray wordList;

    //==============================================================================
    /** Functions to get the current selected token utility to create a tokenized string

        If you pass an empty string, nothing will be done, every values are returned
		as empty strings
    */
	SyntaxLexer ();

	/** Destructor */
	virtual ~SyntaxLexer ();

    //==============================================================================
    /** Functions to get the current selected token utility to create a tokenized string

        If you pass an empty string, nothing will be done, every values are returned
		as empty strings
    */
	virtual void parseText (String& string, const int tokenIndex) = 0;

    /** Functions to get the current selected token utility to create a tokenized string

        If you pass an empty string, nothing will be done, every values are returned
		as empty strings
    */
	virtual void testKeyWord (const String& word) = 0;

    //==============================================================================
    /** 
    */
	virtual Colour getStyleColour (const int styleNumber) const = 0;


    //==============================================================================
    /** 
    */
	void setDocument (SyntaxDocument* documentToLink);

protected:

    //==============================================================================
    /** Functions to get the current selected token utility to create a tokenized string

        If you pass an empty string, nothing will be done, every values are returned
		as empty strings
    */
	forcedinline void setText (String& string)
	{
		allText = &string;
		maxLength = string.length();
		currentIndex = 0;
		startPosition = 0;
		currentState = 0;

		ch = charAt (currentIndex);
		chNext = charAt (currentIndex+1);
	}

    //==============================================================================
    /** Gets the current selected token
    */
	forcedinline String tokenOnly ()
	{
		return (*allText).substring (startPosition, currentIndex);	
	}

	/** Gets the current selected token and advance to next section
    */
	forcedinline String tokenAdvance ()
	{
		int oldPos = startPosition;
		startPosition = currentIndex;
		return (*allText).substring (oldPos, currentIndex);
	}

    //==============================================================================
    /** Advance to next char
    */
	forcedinline void next ()
	{
		currentIndex++;
		ch = charAt (currentIndex);
		chNext = charAt (currentIndex+1);	
	}

    /** Returns true if the lexer have more char to process
    */
	forcedinline bool more ()
	{
		return currentIndex < maxLength;
	}

    /** Complete the syntax analysis of the last section
    */
	forcedinline void complete ()
	{
		internalStateChange (-1);
	}

    /** change the state internally
    */
	forcedinline void stateOnly (const int newState)
	{
		currentState = newState;
	}

    /**@internal*/
	void internalStateChange (const int newState);

    /**@internal*/
	forcedinline tchar charAt (const int indexToGet)
	{
		return (indexToGet < allText->length()) ? (*allText) [indexToGet] : T(' ');
	}

    /**@internal*/
	static forcedinline bool isNewLine (tchar& ch) {
		return (ch==T('\n')||ch==T('\r'));
	}

    /**@internal*/
	static forcedinline bool isWordChar(tchar& ch) {
		return (ch < 0x80) && (isalnum(ch) || ch == T('.') || ch == T('_'));
	}

    /**@internal*/
	static forcedinline bool isWordStart(tchar& ch) {
		return (ch < 0x80) && (isalpha(ch) || ch == T('_'));
	}

    /**@internal*/
	static forcedinline bool IsSpace(tchar& ch) {
		return (ch == T(' ')) || ((ch >= 0x09) && (ch <= 0x0d));
	}

    /**@internal*/
	static forcedinline bool isSpaceOrTab(tchar& ch) {
		return (ch == T(' ')) || (ch == T('\t'));
	}

    /**@internal*/
	static forcedinline bool isDigit(tchar& ch) {
		return (ch >= T('0')) && (ch <= T('9'));
	}

    /**@internal*/
	static forcedinline bool isDigit(tchar& ch, tchar& base) {
		if (base <= 10) {
			return (ch >= T('0')) && (ch < T('0') + base);
		} else {
			return ((ch >= T('0')) && (ch <= T('9'))) ||
				   ((ch >= T('A')) && (ch < T('A') + base - 10)) ||
				   ((ch >= T('a')) && (ch < T('a') + base - 10));
		}
	}

    /**@internal*/
	static forcedinline bool isOperator(tchar& ch) {
		if (isascii(ch) && isalnum(ch))
			return false;
		// '.' left out as it is used to make up numbers
		if (ch == T('%') || ch == T('^') || ch == T('&') || ch == T('*') ||
				ch == T('(') || ch == T(')') || ch == T('-') || ch == T('+') ||
				ch == T('=') || ch == T('|') || ch == T('{') || ch == T('}') ||
				ch == T('[') || ch == T(']') || ch == T(':') || ch == T(';') ||
				ch == T('<') || ch == T('>') || ch == T(',') || ch == T('/') ||
				ch == T('?') || ch == T('!') || ch == T('.') || ch == T('~'))
			return true;
		return false;
	}

};


#endif // __EJUCE_SYNTAXLEXER__

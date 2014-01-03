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

#ifndef __ANGELJUICE_SYNTAXLEXER_CPP_HEADER__
#define __ANGELJUICE_SYNTAXLEXER_CPP_HEADER__

#include "../AngelJuice_config.h"
#include "AngelJuice_SyntaxLexer.h"


//==============================================================================
/** Standard CPP lexer
*/
class SyntaxLexerCPP : public SyntaxLexer
{
public:

	//==============================================================================
	static SyntaxStyle styles [LEX_NUMSTYLES];


	//==============================================================================
	SyntaxLexerCPP ()
	{
/*
		wordList.insert (0,
			" void bool bit char short int long __int64 unsigned float double enum "
			"const class struct union this false true public private protected static operator "
			"namespace typedef template typename new delete sizeof try throw catch finally "
			"if else for while do switch case default break continue return asm __asm "
			"friend extern mutable inline __inline __forceinline "
			"__FILE__ __LINE__ __FUNCTION__ " );

		SyntaxLexerCPP::setStyleColour (LEX_DEFAULT,		Colours::black);
		SyntaxLexerCPP::setStyleColour (LEX_STARTCOMMENT,	Colours::green);
		SyntaxLexerCPP::setStyleColour (LEX_ENDCOMMENT,		Colours::green);
		SyntaxLexerCPP::setStyleColour (LEX_COMMENT,		Colours::green);
		SyntaxLexerCPP::setStyleColour (LEX_COMMENTLINE,	Colours::green);
		SyntaxLexerCPP::setStyleColour (LEX_NUMBER,			Colours::darkviolet);
		SyntaxLexerCPP::setStyleColour (LEX_WORD,			Colours::blue);
		SyntaxLexerCPP::setStyleColour (LEX_WORD2,			Colours::blue);
		SyntaxLexerCPP::setStyleColour (LEX_WORD3,			Colours::blue);
		SyntaxLexerCPP::setStyleColour (LEX_WORD4,			Colours::blue);
		SyntaxLexerCPP::setStyleColour (LEX_STRING,			Colours::red);
		SyntaxLexerCPP::setStyleColour (LEX_CHARACTER,		Colours::red);
		SyntaxLexerCPP::setStyleColour (LEX_PREPROCESSOR,	Colours::darkorange);
		SyntaxLexerCPP::setStyleColour (LEX_OPERATOR,		Colours::black);
		SyntaxLexerCPP::setStyleColour (LEX_IDENTIFIER,		Colours::black);
*/
	}

	//==============================================================================
	static void setStyleColour (const int styleNumber, const Colour& colour)
	{
		jassert (styleNumber >= 0);
		jassert (styleNumber < LEX_NUMSTYLES);

		SyntaxLexerCPP::styles [styleNumber].textColour = colour;
	}

	Colour getStyleColour (const int styleNumber) const
	{
		jassert (styleNumber >= 0);
		jassert (styleNumber < LEX_NUMSTYLES);

		return SyntaxLexerCPP::styles [styleNumber].textColour;
	}


	//==============================================================================
	forcedinline void testKeyWord (const String& word)
	{
		String temp = T(" ") + word + T(" ");
		if (wordList[0].indexOf (temp) >= 0)
		{
			stateOnly (LEX_WORD);
		}
//		else if (wordList2.indexOf (temp) >= 0)
//		{
//			stateOnly (LEX_WORD2);
//		}

	}

	//==============================================================================
	void parseText (String& string_, const int tokenIndex_)
	{
		setText (string_);
		tokenIndex = tokenIndex_;

		for (; more(); next())
		{
			switch (currentState)
			{
			case LEX_COMMENT:
				if (ch == T('*') && chNext == T('/')) {
					internalStateChange (LEX_ENDCOMMENT);
					next();
					next();
					internalStateChange (LEX_DEFAULT);
				}
				break;
			case LEX_COMMENTLINE:
				if (SyntaxLexer::isNewLine(ch)) {
					next();
					internalStateChange (LEX_DEFAULT);
				}
				break;
			case LEX_NUMBER:
				if (!SyntaxLexer::isWordChar(ch)) {
					internalStateChange (LEX_DEFAULT);
				}
				break;
			case LEX_STRING:
				if (SyntaxLexer::isNewLine(ch)) {
					internalStateChange (LEX_STRINGEOL);
				} else if (ch == T('\\')) {
					if (chNext == T('\"') || chNext == T('\'') || chNext == T('\\')) {
						next();
					}
				} else if (ch == T('\"')) {
					next();
					internalStateChange (LEX_DEFAULT);
				}
				break;
			case LEX_CHARACTER:
				if (SyntaxLexer::isNewLine(ch)) {
					internalStateChange (LEX_STRINGEOL);
				} else if (ch == T('\\')) {
					if (chNext == T('\"') || chNext == T('\'') || chNext == T('\\')) {
						next();
					}
				} else if (ch == '\'') {
					next();
					internalStateChange (LEX_DEFAULT);
				}
				break;
			case LEX_IDENTIFIER:
				if (!SyntaxLexer::isWordChar(ch) || (ch == T('.'))) {
					testKeyWord (tokenOnly());
					internalStateChange (LEX_DEFAULT);
				}
				break;
			case LEX_OPERATOR:
				internalStateChange (LEX_DEFAULT);
				break;
			case LEX_PREPROCESSOR:
				if (SyntaxLexer::isNewLine(ch)) {
					next();
					internalStateChange (LEX_DEFAULT);
				} else {
					if ((ch == T('/') && chNext == T('*')) ||
						(ch == T('/') && chNext == T('/')) ) {
						internalStateChange (LEX_DEFAULT);
					}
				}
				break;
			case LEX_STRINGEOL:
				// if (atLineStart) {
					internalStateChange (LEX_DEFAULT);
				// }
				break;
			}

			if (currentState == LEX_DEFAULT) {
				if (SyntaxLexer::isDigit(ch) || (ch == T('.') && SyntaxLexer::isDigit(chNext))) {
					internalStateChange (LEX_NUMBER);
				} else if (SyntaxLexer::isWordStart(ch)) {
					internalStateChange (LEX_IDENTIFIER);
				} else if (ch == T('*') && chNext == T('/')) {
					internalStateChange (LEX_ENDCOMMENT);
					next();
					next();
					internalStateChange (LEX_DEFAULT);
				} else if (ch == T('/') && chNext == T('*')) {
					internalStateChange (LEX_STARTCOMMENT);
					next();
					next();
					internalStateChange (LEX_COMMENT);
				} else if (ch == T('/') && chNext == T('/')) {
					internalStateChange (LEX_COMMENTLINE);
					next();
				} else if (ch == T('\"')) {
					internalStateChange (LEX_STRING);
				} else if (ch == T('\'')) {
					internalStateChange (LEX_CHARACTER);
				} else if (ch == T('#')) {
					internalStateChange (LEX_PREPROCESSOR);
					do {
						next();
					} while ((ch == T(' ') || ch == T('\t')) && more());
					if (SyntaxLexer::isNewLine(ch)) {
						internalStateChange (LEX_DEFAULT);
					}
				} else if (SyntaxLexer::isOperator(ch)) {
					internalStateChange (LEX_OPERATOR);
				}
			}
		}
		complete ();
	}

};


#endif // __EJUCE_SYNTAXLEXER_CPP__

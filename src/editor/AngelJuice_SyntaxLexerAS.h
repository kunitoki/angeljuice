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

#ifndef __ANGELJUICE_SYNTAXLEXER_ANGELSCRIPT_HEADER__
#define __ANGELJUICE_SYNTAXLEXER_ANGELSCRIPT_HEADER__


#include "../AngelJuice_config.h"
#include "AngelJuice_SyntaxLexerCPP.h"


//==============================================================================
/** Standard AngelScript lexer
*/
class SyntaxLexerAngelScript : public SyntaxLexerCPP
{
public:

	//==============================================================================
	SyntaxLexerAngelScript ()
	{
		GlobalConfig* config = GlobalConfig::getInstance();

		wordList.insert (0,
			" void bool bits bits8 bits16 bits32 int int8 int16 int32 int64 uint uint8 uint16 uint32 float double "
			"const class struct any this false true in inout out and or not xor "
			"if else for while do switch case default break continue return import cast "
			"quit abort print println clear execute alert error ask throw " // to be kept in classes
			"__FILE__ __LINE__ __VERSION__ ");

		wordList.insert (1,
			" String RegExp InputStream FileOutputStream FileInputStream File URL DirectoryIterator FileChooser "
			"Random SystemStats MD5 Time "
			"Colour Image ImageConvolutionKernel Font Point Line Rectangle Path PathStrokeType AffineTransform Graphics ImagePreview "
			"ModifierKeys KeyPress MouseEvent Component ComponentPeer ComponentBoundsConstrainer ComponentDragger Desktop "
			"TextButton ");

		SyntaxLexerCPP::setStyleColour(LEX_DEFAULT,			config->textColours [0]);
		SyntaxLexerCPP::setStyleColour(LEX_STARTCOMMENT,	config->textColours [1]);
		SyntaxLexerCPP::setStyleColour(LEX_ENDCOMMENT,		config->textColours [1]);
		SyntaxLexerCPP::setStyleColour(LEX_COMMENT,			config->textColours [1]);
		SyntaxLexerCPP::setStyleColour(LEX_COMMENTLINE,		config->textColours [1]);
		SyntaxLexerCPP::setStyleColour(LEX_NUMBER,			config->textColours [2]);
		SyntaxLexerCPP::setStyleColour(LEX_WORD,			config->textColours [3]);
		SyntaxLexerCPP::setStyleColour(LEX_WORD2,			config->textColours [4]);
//		SyntaxLexerCPP::setStyleColour(LEX_WORD3,			config->textColours [3]);
//		SyntaxLexerCPP::setStyleColour(LEX_WORD4,			config->textColours [3]);
		SyntaxLexerCPP::setStyleColour(LEX_STRING,			config->textColours [5]);
		SyntaxLexerCPP::setStyleColour(LEX_CHARACTER,		config->textColours [5]);
		SyntaxLexerCPP::setStyleColour(LEX_PREPROCESSOR,	config->textColours [6]);
		SyntaxLexerCPP::setStyleColour(LEX_OPERATOR,		config->textColours [7]);
		SyntaxLexerCPP::setStyleColour(LEX_IDENTIFIER,		config->textColours [7]);
	}

	//==============================================================================
	static void setStyleGroupColour (const int styleGroup, const Colour& colour)
	{
		switch (styleGroup)
		{
		case 0: // LEX_DEFAULT
			SyntaxLexerCPP::setStyleColour (LEX_DEFAULT, colour);
			break;
		case 1: // LEX_COMMENT / LEX_COMMENTLINE
			SyntaxLexerCPP::setStyleColour (LEX_STARTCOMMENT, colour);
			SyntaxLexerCPP::setStyleColour (LEX_ENDCOMMENT, colour);
			SyntaxLexerCPP::setStyleColour (LEX_COMMENT, colour);
			SyntaxLexerCPP::setStyleColour (LEX_COMMENTLINE, colour);
			break;
		case 2: // LEX_NUMBER
			SyntaxLexerCPP::setStyleColour (LEX_NUMBER, colour);
			break;
		case 3: // LEX_WORD / LEX_WORD3 / LEX_WORD4
			SyntaxLexerCPP::setStyleColour (LEX_WORD, colour);
			SyntaxLexerCPP::setStyleColour (LEX_WORD3, colour);
			SyntaxLexerCPP::setStyleColour (LEX_WORD4, colour);
			break;
		case 4: // LEX_WORD2
			SyntaxLexerCPP::setStyleColour (LEX_WORD2, colour);
			break;
		case 5: // LEX_STRING / LEX_CHARACTER
			SyntaxLexerCPP::setStyleColour (LEX_STRING, colour);
			SyntaxLexerCPP::setStyleColour (LEX_CHARACTER, colour);
			break;
		case 6: // LEX_PREPROCESSOR
			SyntaxLexerCPP::setStyleColour (LEX_PREPROCESSOR, colour);
			break;
		case 7: // LEX_OPERATOR / LEX_IDENTIFIER
			SyntaxLexerCPP::setStyleColour (LEX_OPERATOR, colour);
			SyntaxLexerCPP::setStyleColour (LEX_IDENTIFIER, colour);
			break;
		default:
			break;
		}
	}

	//==============================================================================
	forcedinline void testKeyWord (const String& word)
	{
		String temp = T(" ") + word + T(" ");
		if (wordList[0].indexOf (temp) >= 0)
		{
			stateOnly (LEX_WORD);
		}
		else if (wordList[1].indexOf (temp) >= 0)
		{
			stateOnly (LEX_WORD2);
		}
	}

};


#endif // __ANGELJUICE_SYNTAXLEXERANGELSCRIPT_HEADER__

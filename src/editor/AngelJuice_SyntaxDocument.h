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

#ifndef __ANGELJUICE_SYNTAXDOCUMENT_HEADER__
#define __ANGELJUICE_SYNTAXDOCUMENT_HEADER__

#include "../AngelJuice_config.h"
#include "AngelJuice_SyntaxLexer.h"


//==============================================================================
/** A word or space that can't be broken down any further

*/
struct TextAtom
{
    String atomText;
    float width;
    uint16 numChars;
	uint8 status;

    forcedinline bool isWhitespace() const
	{
		return CharacterFunctions::isWhitespace (atomText[0]);
	}

	forcedinline bool isTab() const
	{
		return atomText[0] == T('\t');
	}

	forcedinline bool isNewLine() const
	{
		return atomText[0] == T('\r') || atomText[0] == T('\n');
	}
};


//==============================================================================
/** A syntax text editor text holder

*/
class SyntaxDocument
{
public:

    SyntaxDocument (const String& text, const Font& font_);
    virtual ~SyntaxDocument();

    void clear();
    int getNumAtoms() const throw();
    TextAtom* getAtom (const int atomIndex) const throw();
    int addAtoms (const String& textToParse, int atomIndexToInsert = 0, uint8 status = 0);
	int indexToAtom (const int charIndex);
	int prevLineAtomIndex (const int charIndex);
	int nextLineAtomIndex (const int charIndex);

    int append (const String& text);
	int insert (const String& text, const int indexToInsertAt);
	int remove (const int indexToRemoveFrom, const int indexToRemoveTo);
    void split (const int indexToBreakAt);

    const String getAllText() const throw();
    const String getTextSubstring (const int startCharacter, const int endCharacter) const throw();
    int getTotalLength() const throw();

	void setFont (const Font& font);
//	void setWords (const int wordsNumber, const String& wordList);

	void setLexer (SyntaxLexer* lexer);
	SyntaxLexer* getLexer ();

	void updateSyntaxSections ();
	void updateSyntaxSections (const int startIndex, const int stopIndex,
                               int& finalStartIndex, int& finalStopIndex);

    juce_UseDebuggingNewOperator

    Font font;
	VoidArray atoms;

protected:

	int tabCharSize;
	SyntaxLexer* lexer;
};


//==============================================================================
class SyntaxDocumentIterator
{
public:
    //==============================================================================
    SyntaxDocumentIterator (SyntaxDocument* doc) throw()
      : indexInText (0),
        lineY (0),
        lineHeight (0),
        maxDescent (0),
        atomX (0),
        atomRight (0),
        atom (0),
        document (doc),
		lexer (doc->getLexer()),
        atomIndex (0),
		lastStatus (-1),
		lastAtom (0)
    {
		lineHeight = document->font.getHeight();
		maxDescent = document->font.getDescent();
    }

    ~SyntaxDocumentIterator() throw()
    {
    }

    //==============================================================================
    bool next()
    {
		if (atomIndex >= document->getNumAtoms())
        {
			moveToEndOfLastAtom ();
			return false;
        }

        if (atom != 0)
        {
            atomX = atomRight;
            indexInText += atom->numChars;

            if (atom->isNewLine())
            {
                atomX = 0;
                lineY += lineHeight;
            }
		}

        atom = document->getAtom (atomIndex);
        atomRight = atomX + atom->width;
        ++atomIndex;

        return true;
    }

    //==============================================================================
    void draw (Graphics& g)
    {
        if (! atom->isWhitespace() && atom->atomText.isNotEmpty())
        {
			if (lastStatus != atom->status)
			{
				if (lexer)
					g.setColour (lexer->getStyleColour(atom->status));

				lastStatus = atom->status;
			}

            g.drawSingleLineText (atom->atomText,
                                  roundFloatToInt (atomX),
                                  roundFloatToInt (lineY + lineHeight - maxDescent));

        }
    }

    void drawSelection (Graphics& g,
                        const int selectionStart,
                        const int selectionEnd)
    {
        const int startX = roundFloatToInt (indexToX (selectionStart));
        const int endX   = roundFloatToInt (indexToX (selectionEnd));

        const int y = roundFloatToInt (lineY);
        const int nextY = roundFloatToInt (lineY + lineHeight);

        g.fillRect (startX, y, endX - startX, nextY - y);
    }

    //==============================================================================
    float indexToX (const int indexToFind) const
    {
        if (indexToFind <= indexInText)
            return atomX;

        if (indexToFind >= indexInText + atom->numChars)
            return atomRight;

        GlyphArrangement g;
        g.addLineOfText (document->font,
                         atom->atomText,
                         atomX, 0.0f);

        return jmin (atomRight, g.getGlyph (indexToFind - indexInText).getLeft());
    }

    int xToIndex (const float xToFind) const
    {
        if (xToFind <= atomX || atom->isNewLine())
            return indexInText;

        if (xToFind >= atomRight)
            return indexInText + atom->numChars;

        GlyphArrangement g;
        g.addLineOfText (document->font,
                         atom->atomText,
                         atomX, 0.0f);

        int j;
        for (j = 0; j < atom->numChars; ++j)
            if ((g.getGlyph(j).getLeft() + g.getGlyph(j).getRight()) / 2 > xToFind)
                break;

        return indexInText + j;
    }

    //==============================================================================
    juce_UseDebuggingNewOperator

    int indexInText;
    float lineY, lineHeight, maxDescent;
    float atomX, atomRight;
    const TextAtom* atom;
    const SyntaxDocument* document;
    const SyntaxLexer* lexer;

private:
    int atomIndex;
	int lastStatus;
	const TextAtom* lastAtom;

    SyntaxDocumentIterator (const SyntaxDocumentIterator&);
    const SyntaxDocumentIterator& operator= (const SyntaxDocumentIterator&);

    void moveToEndOfLastAtom()
    {
        if (atom != 0)
        {
            atomX = atomRight;

            if (atom->isNewLine())
            {
                atomX = 0.0f;
                lineY += lineHeight;
            }
        }
    }
};


#endif // __EJUCE_SYNTAXDOCUMENT__

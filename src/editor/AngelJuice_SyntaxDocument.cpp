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

#include "AngelJuice_SyntaxDocument.h"


//==============================================================================
SyntaxDocument::SyntaxDocument (const String& text,
								const Font& font_)
  : font (font_),
    atoms (128),
    tabCharSize (4),
    lexer (0)
{
    addAtoms (text);
}

SyntaxDocument::~SyntaxDocument()
{
    // (no need to delete the atoms, as they're explicitly deleted by the caller)
	clear();

	if (lexer)
		delete lexer;
}

//==============================================================================
void SyntaxDocument::clear()
{
    for (int i = atoms.size(); --i >= 0;)
        delete (TextAtom*) atoms.getUnchecked (i);

    atoms.clear();
}

//==============================================================================
const String SyntaxDocument::getAllText() const throw()
{
    String s;

    for (int i = 0; i < atoms.size(); ++i)
        s += getAtom(i)->atomText;

    return s;
}

const String SyntaxDocument::getTextSubstring (const int startCharacter, const int endCharacter) const throw()
{
    String s;
    int index = 0;

    for (int i = 0; i < atoms.size(); ++i)
    {
        const TextAtom* const atom = getAtom (i);
        const int nextIndex = index + atom->numChars;

        if (startCharacter < nextIndex)
        {
            if (endCharacter <= index)
                break;

            const int start = jmax (index, startCharacter);
            s += atom->atomText.substring (start - index, endCharacter - index);
        }

        index = nextIndex;
    }

    return s;
}

int SyntaxDocument::getTotalLength() const throw()
{
    int c = 0;

    for (int i = atoms.size(); --i >= 0;)
        c += getAtom(i)->numChars;

    return c;
}


//==============================================================================
TextAtom* SyntaxDocument::getAtom (const int index) const throw()
{
    return (TextAtom*) atoms.getUnchecked (index);
}

int SyntaxDocument::getNumAtoms() const throw()
{
    return atoms.size();
}

int SyntaxDocument::indexToAtom (const int charIndex)
{
	int index = 0;
	int nextIndex = 0;

    for (int i = 0; i < atoms.size(); ++i)
    {
        TextAtom* const atom = getAtom(i);

        nextIndex = index + atom->numChars;
		if (charIndex >= index && charIndex < nextIndex)
		{
			return i;
		}

		index = nextIndex;
	}

	return -1;
}

int SyntaxDocument::prevLineAtomIndex (const int charIndex)
{
	int currentAtomIndex = indexToAtom (charIndex);
	if (currentAtomIndex < 0)
		return 0;

    TextAtom* const firstAtom = getAtom(currentAtomIndex--);

    if (lexer)
    {
        for (; currentAtomIndex >= 0 && currentAtomIndex < atoms.size(); --currentAtomIndex)
        {
            TextAtom* const atom = getAtom(currentAtomIndex);

            switch (firstAtom->status)
            {
            case LEX_COMMENT:
                if (atom->status == LEX_STARTCOMMENT)
                {
                    goto finish;
                }
                break;
            case LEX_ENDCOMMENT:
                if (atom->status == LEX_STARTCOMMENT)
                {
                    goto finish;
                }
                break;
            case LEX_STARTCOMMENT:
            default:
                if ((atom->isNewLine() && atom->status != LEX_COMMENT) ||
                    atom->status == LEX_STARTCOMMENT ||
                    atom->status == LEX_ENDCOMMENT)
                {
                    goto finish;
                }
                break;
            }
        }
	}

finish:

	return jmin (jmax (currentAtomIndex, 0), atoms.size());
}

int SyntaxDocument::nextLineAtomIndex (const int charIndex)
{
	int currentAtomIndex = indexToAtom (charIndex);
	if (currentAtomIndex < 0)
		return atoms.size();

	TextAtom* const firstAtom = getAtom(currentAtomIndex++);

    if (lexer)
    {
        for (; currentAtomIndex >= 0 && currentAtomIndex < atoms.size(); ++currentAtomIndex)
        {
            TextAtom* const atom = getAtom(currentAtomIndex);

            switch (firstAtom->status)
            {
            case LEX_ENDCOMMENT:
                if (atom->isNewLine())
                {
                    goto finish;
                }
                else if (atom->status == LEX_STARTCOMMENT)
                {
                    --currentAtomIndex;
                    goto finish;
                }
                break;
            case LEX_STARTCOMMENT:
            case LEX_COMMENT:
                if (atom->status == LEX_ENDCOMMENT)
                {
                    ++currentAtomIndex;
                    goto finish;
                }
                break;
            default:
                if ((atom->isNewLine() && atom->status != LEX_COMMENT) ||
                    atom->status == LEX_STARTCOMMENT ||
                    atom->status == LEX_ENDCOMMENT)
                {
                    // currentIndex;
                    goto finish;
                }
                break;
            }
        }
    }

finish:

	return jmin (jmax (currentAtomIndex, 0), atoms.size());
}

//==============================================================================
int SyntaxDocument::insert (const String& text, const int charIndex)
{
	int index = 0;
	int nextIndex = 0;
	int atomsAdded = 0;

    int finalStartIndex, finalStopIndex;

    for (int i = 0; i < atoms.size(); ++i)
    {
        TextAtom* const atom = getAtom(i);

        nextIndex = index + atom->numChars;

        if (charIndex == index)
        {
			atomsAdded += addAtoms (text, i, atom->status);
			break;
		}
        else if (charIndex >= index && charIndex < nextIndex)
		{
			String textToSplit = atom->atomText;
			int status = atom->status;
			delete atom;
			atoms.remove (i);

			--atomsAdded;
			atomsAdded += addAtoms (
				textToSplit.substring (0, charIndex - index) +
				text +
				textToSplit.substring (charIndex - index), i, status);
			break;
		}

		index = nextIndex;
	}

	if (charIndex == nextIndex)
	{
		atomsAdded += addAtoms (text, atoms.size());
	}

	updateSyntaxSections (charIndex - 1, charIndex + text.length(),
                          finalStartIndex, finalStopIndex);

	return atomsAdded;
}

int SyntaxDocument::append (const String& text)
{
	int charIndex = getTotalLength() - 1;
	int atomsAdded = addAtoms (text, atoms.size());

    int finalStartIndex, finalStopIndex;

	// @TODO - check syntax here !
	updateSyntaxSections (charIndex, charIndex + text.length(),
                          finalStartIndex, finalStopIndex);

	return atomsAdded;
}

int SyntaxDocument::remove (const int indexToRemoveFrom, const int indexToRemoveTo)
{
	int index = 0;
	int i = 0;
	int newLinesRemoved = 0;
	int thisStartIndex = indexToRemoveFrom;
	int thisStopIndex = indexToRemoveTo;
	int charToRemove = indexToRemoveTo - indexToRemoveFrom;

    int finalStartIndex, finalStopIndex;

	for (i = 0; i < atoms.size() && charToRemove > 0; ++i)
    {
        TextAtom* const atom = getAtom(i);

        const int nextIndex = index + atom->numChars;

        if (thisStartIndex >= index && thisStartIndex < nextIndex)
        {
			int nextStartIndex = thisStartIndex - index;
			int nextStopIndex = jmin (thisStopIndex - index, atom->numChars);

			if ((nextStopIndex - nextStartIndex) == atom->numChars)
			{
				if (atom->isNewLine())
					++newLinesRemoved;

				delete atom;
				atoms.remove (i--);
			}
			else
			{
				atom->atomText =
					atom->atomText.substring (0, nextStartIndex) +
					atom->atomText.substring (nextStopIndex, atom->numChars);
                atom->width = font.getStringWidthFloat (atom->atomText);
                atom->numChars = (uint16) (atom->atomText.length());
			}

			charToRemove -= (nextStopIndex - nextStartIndex);
			thisStartIndex = index + nextStopIndex;
        }

        index = nextIndex;
	}

	updateSyntaxSections (indexToRemoveFrom, indexToRemoveTo,
                          finalStartIndex, finalStopIndex);

	return newLinesRemoved;
}

void SyntaxDocument::split (const int indexToBreakAt)
{
    int index = 0;
    int finalStartIndex, finalStopIndex;

    for (int i = 0; i < atoms.size(); ++i)
    {
        TextAtom* const atom = getAtom(i);

        const int nextIndex = index + atom->numChars;

        if (index == indexToBreakAt)
        {
			break;
        }
        else if (indexToBreakAt > index && indexToBreakAt < nextIndex)
        {
			addAtoms (atom->atomText.substring (indexToBreakAt - index), index + 1);

            atom->atomText = atom->atomText.substring (0, indexToBreakAt - index);
            atom->width = font.getStringWidthFloat (atom->atomText);
            atom->numChars = (uint16) (indexToBreakAt - index);

			break;
        }

        index = nextIndex;
    }

	updateSyntaxSections (indexToBreakAt, indexToBreakAt,
                          finalStartIndex, finalStopIndex);
}


//==============================================================================
int SyntaxDocument::addAtoms (const String& textToParse, int indexToInsert, uint8 status)
{
    int i = 0;
    const int len = textToParse.length();
    const tchar* const text = (const tchar*) textToParse;
	int atomsAdded = 0;
//	int startIndex = indexToInsert;
	int tabSize = 1;

    while (i < len)
    {
        const int start = i;
        int end = i;

		tabSize = 1;

        // create a whitespace atom unless it starts with non-ws
        if ( CharacterFunctions::isWhitespace (text[i])
			 && text[i] != T('\t')
             && text[i] != T('\r')
             && text[i] != T('\n'))
        {
            while (i < len
                    && CharacterFunctions::isWhitespace (text[i])
					&& text[i] != T('\t')
                    && text[i] != T('\r')
                    && text[i] != T('\n'))
            {
                ++i;
            }

            end = i;
        }
        else
        {
            if (text[i] == T('\r'))
            {
				++i;
                end = i;

                if ((i < len) && (text[i] == T('\n')))
                    ++i;
            }
            else if (text[i] == T('\n'))
            {
                ++i;
                end = i;

                if ((i < len) && (text[i] == T('\r')))
                    ++i;
            }
            else if (text[i] == T('\t'))
            {
                ++i;
                end = i;
				tabSize = tabCharSize;
            }
            else
            {
                while ((i < len) && ! CharacterFunctions::isWhitespace (text[i]))
                    ++i;

                end = i;
            }
        }

		TextAtom* const atom = new TextAtom();
        atom->atomText = textToParse.substring (start, end).replace (T("\r"),T("\n"));
		atom->width = font.getStringWidthFloat (atom->atomText) * tabSize;
        atom->numChars = (uint16) (end - start);
		atom->status = status;

		atoms.insert (indexToInsert++, atom);

		atomsAdded++;
    }

	return atomsAdded;
}


//==============================================================================
void SyntaxDocument::setFont (const Font& font_)
{
	font = font_;

	for (int i = 0; i < atoms.size(); i++)
	{
		TextAtom* atom = getAtom (i);
		atom->width = font.getStringWidthFloat (atom->atomText) *
												(atom->isTab() ? tabCharSize : 1);
	}
}

//==============================================================================
void SyntaxDocument::setLexer (SyntaxLexer* lexer_)
{
	if (lexer)
		delete lexer;

	lexer = lexer_;

    if (lexer)
		lexer->setDocument (this);

    updateSyntaxSections ();
}

SyntaxLexer* SyntaxDocument::getLexer ()
{
	return lexer;
}


//==============================================================================
void SyntaxDocument::updateSyntaxSections ()
{
	if (lexer)
	{
	    String allText = getAllText();
		clear ();

		lexer->parseText (allText, 0);
	}
}

void SyntaxDocument::updateSyntaxSections (const int startIndex, const int stopIndex,
                                           int& finalStartIndex, int& finalStopIndex)
{
	if (lexer)
	{
		int startAtom = jmax (0, prevLineAtomIndex (startIndex));
		int stopAtom = jmin (atoms.size(), nextLineAtomIndex (stopIndex));

		// remove range and reparse parse
		if (stopAtom - startAtom > 0)
		{
            DBG ("1st: " + String (startAtom) + " " + String (stopAtom) );

            // collect the text to update
            String textToUpdate;
            for (int i = startAtom; i < stopAtom; i++)
            {
                TextAtom* atom = getAtom (i);
                textToUpdate += atom->atomText;

                delete atom;
            }

			atoms.removeRange (startAtom, stopAtom - startAtom);

			lexer->parseText (textToUpdate, startAtom);

			// second parse
			int newStartAtom = jmax (0, prevLineAtomIndex (startIndex));
			int newStopAtom = jmin (atoms.size(), nextLineAtomIndex (stopIndex));

			if (startAtom != newStartAtom ||
				stopAtom != newStopAtom)
			{
				// collect the text to update
				String textToUpdate;
				for (int i = newStartAtom; i < newStopAtom; i++)
				{
					TextAtom* atom = getAtom (i);
					textToUpdate += atom->atomText;

					delete atom;
				}

				if (newStopAtom - newStartAtom > 0)
				{
					atoms.removeRange (newStartAtom, newStopAtom - newStartAtom);

					lexer->parseText (textToUpdate, newStartAtom);

                    DBG ("2nd: " + String (newStartAtom) + " " + String (newStopAtom) );

				}
			}
			// end second parse
		}
	}
}

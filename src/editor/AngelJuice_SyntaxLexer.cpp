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

#include "AngelJuice_SyntaxLexer.h"
#include "AngelJuice_SyntaxLexerCPP.h"
#include "AngelJuice_SyntaxDocument.h"


SyntaxStyle SyntaxLexerCPP::styles [LEX_NUMSTYLES];


//==============================================================================
SyntaxLexer::SyntaxLexer () :
		ch (T(' ')),
		chNext (T(' ')),
		startPosition (0),
		currentIndex (0),
		maxLength (0),
		currentState (0),
		tokenIndex (0),
		allText (0),
		document (0)
{
}

/** Destructor */
SyntaxLexer::~SyntaxLexer ()
{
}

//==============================================================================
void SyntaxLexer::setDocument (SyntaxDocument* documentToLink)
{
	document = documentToLink;
}

//==============================================================================
void SyntaxLexer::internalStateChange (const int newState)
{
	if (currentIndex > 0 &&
		(startPosition < maxLength && startPosition < currentIndex))
	{
		tokenIndex +=
			document->addAtoms (tokenAdvance(), tokenIndex, currentState);
	}

	currentState = newState;
}

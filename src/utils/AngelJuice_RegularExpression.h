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

   @coder   Asnaghi Lucio a.k.a. kRAkEn/gORe

  ==============================================================================
*/

#ifndef __ANGELJUICE_EGULAREXPRESSION_HEADER__
#define __ANGELJUICE_EGULAREXPRESSION_HEADER__

#include "juce.h"


//==============================================================================
/**
    This class is designed around PCRE library for regular expression
    parsing and evaluating.

    @code
        RegularExpression re("\\d{3}");
        int found = re.match("123.345");

        if (found >= 0)
        {
            String result;
            int startOffset, endOffset;
            for (int i = 0; i < found; i++)
            {
                result = re.getMatch (i, startOffset, endOffset);
            }
        }
        else
        {
            DBG ("nothing found");
        }
    @endcode

*/
class RegularExpression
{
public:

    //==============================================================================
    /** These are the errors that the match functions could return */
    enum ReturnErrors
    {
        compileFailed = -100,
        bufferSizeError = -101,
        matchNotFound = -102,
        matchFindError = -103
    };

    //==============================================================================
    /** Construct an empty expression */
    RegularExpression ();

    /** Construct a regular expression with a pattern */
    RegularExpression (const String& pattern);

    /** Destructor */
    ~RegularExpression ();

    //==============================================================================
    /**
        This try to match the pattern in the given subject

        @param subject      string where to search in
        @return             number of matches, < 0 is like error
    */
    int match (const String& subject);

    /**
        This try to match the pattern in the given subject

        @param pattern      pattern string to search
        @param subject      string where search in
        @return             number of matches, < 0 is like error
    */
    int match (const String& pattern, const String& subject);

    //==============================================================================
    /**
        This returns the string start and end position in the subject string, with
        the given index.

        @param indexToGet   match string at index
        @param startOffset  string start offset in the whole subject string
        @param endOffset    string end offset in the whole subject string
        @return             the string matched
    */
    String getMatch (int indexToGet, int& startOffset, int& endOffset);


protected:

    class ExpressionIndex {
    public:
        ExpressionIndex (int s, int e)
            : start(s), end(e) {}
        int start, end;
    };

    OwnedArray<ExpressionIndex> index;
    int numSubStrings;
    String pattern;
    String subject;

private:

    RegularExpression (const RegularExpression& other);
};

#endif // __EJUCE_REGULAREXPRESSION__

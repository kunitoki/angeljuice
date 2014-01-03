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

#include "../libraries/pcre/pcre.h"

#include "AngelJuice_RegularExpression.h"

#define OVECOUNT 60

//==============================================================================
RegularExpression::RegularExpression () :
    numSubStrings (0),
    pattern (String::empty),
    subject (String::empty)
{
}

RegularExpression::RegularExpression (const String& pattern) :
    numSubStrings (0),
    pattern (pattern),
    subject (String::empty)
{
}

RegularExpression::~RegularExpression ()
{
}

//==============================================================================
int RegularExpression::match (const String& pattern_, const String& subject_)
{
    pattern = pattern_;
    return match(subject_);
}

int RegularExpression::match (const String& subject_)
{
    subject = subject_;

    pcre* re;
    const char *error;
    int erroffset;
    int ovector [OVECOUNT];
    memset (ovector, 0, OVECOUNT * sizeof(int));

    index.clear();

    // try to compile
    re = pcre_compile(
            (const char*) pattern,    // the pattern
            0,                        // default options
            &error,                    // for error message
            &erroffset,                // for error offset
            0);                        // use default character tables

    // compilation failed
    if (re == 0)
    {
        return compileFailed;
    }

    // execute
    numSubStrings = pcre_exec(
            re,                        // the compiled pattern
            0,                        // no extra data - we didn't study the pattern
            (const char*) subject,    // the subject string
            subject.length(),        // the length of the subject
            0,                        // start at offset 0 in the subject
            0,                        // default options
            ovector,                // output vector for substring information
            OVECOUNT);                // number of elements in the output vector

    // matching error checking
    if (numSubStrings < 0)
    {
        switch(numSubStrings)
        {
            case PCRE_ERROR_NOMATCH:
                free(re);
                return matchNotFound;
            default:
                free(re);
                return matchFindError;
        }
    }

    // The match succeeded, but the output vector wasn't big enough.
    if (numSubStrings == 0)
    {
        return bufferSizeError;
    }

    // else add stuff
    for (int i = 0; i < numSubStrings; i++)
    {
        index.add (new ExpressionIndex (ovector[2*i], ovector[2*i+1]));
    }

    for (;;)
    {
        int options = 0;
        int start_offset = ovector[1];

        if (ovector[0] == ovector[1])
        {
            if (ovector[0] == subject.length())
                break;
            options = PCRE_NOTEMPTY | PCRE_ANCHORED;
        }

        int thisSubStrings = pcre_exec(
            re,                        // pattern
            0,                        // no extra
            (const char*) subject,    // the subject string
            subject.length(),        // the length of the subject
            start_offset,            // starting offset in the subject
            options,                // options
            ovector,                // output vector for substring information
            OVECOUNT);            // number of elements in the output vector

        if (thisSubStrings == PCRE_ERROR_NOMATCH)
        {
            if (options == 0) break;
            ovector[1] = start_offset + 1;
            continue;    // Go round the loop again
        }

        // Other matching errors are not recoverable.
        if (thisSubStrings < 0)
        {
            free(re);
            return matchFindError;
        }

        // The match succeeded, but the output vector wasn't big enough.
        if (thisSubStrings == 0)
        {
            continue;
        }

        for (int i = 0; i < thisSubStrings; i++)
        {
            index.add (new ExpressionIndex (ovector[2*i], ovector[2*i+1]));
        }

        numSubStrings += thisSubStrings;
    }

    free(re);

    return (numSubStrings);
}

//==============================================================================
String RegularExpression::getMatch (int indexToGet, int& startOffset, int& endOffset)
{
    jassert( indexToGet < numSubStrings );

    startOffset = index[indexToGet]->start;
    endOffset = index[indexToGet]->end;

    return subject.substring (startOffset, endOffset);
}


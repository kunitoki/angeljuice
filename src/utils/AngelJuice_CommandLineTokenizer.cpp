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

#include "AngelJuice_CommandLineTokenizer.h"


//==============================================================================
void CommandLineTokenizer::parseCommandLine (const String& commandLine)
{
	int section;
	String value, parse = commandLine.trim();

	while (parse.length() > 0)
	{
		section = parse.indexOf (0,T(" "));
		if (section == -1)
			section = parse.length();

		argv.add (parse.substring (0, section));

		if (section < parse.length() )
			parse = parse.substring (section+1,parse.length()).trim();
		else
			parse = String::empty;
	}
}

//==============================================================================
const String& CommandLineTokenizer::operator[] (const int index) const throw()
{
	jassert (index >= 0 && index < argv.size())
	return argv[index];
}

const int CommandLineTokenizer::size()
{
	return argv.size();
}

//==============================================================================
int CommandLineTokenizer::searchToken (const String& tokenToSearch, const bool caseSensitive)
{
	if (caseSensitive)
	{
		for (int i = 0; i < argv.size(); i++ )
			if (tokenToSearch.compare (argv[i]) == 0)
				return i;
	}
	else
	{
		for (int i = 0; i < argv.size(); i++ )
			if (tokenToSearch.compareIgnoreCase (argv[i]) == 0)
				return i;
	}
	return -1;
}

//==============================================================================
String CommandLineTokenizer::getOptionString (const String& tokenToSearch,
											  const String& defValue,
											  const bool caseSensitive)
{
	int i = searchToken (tokenToSearch, caseSensitive);
	if (i++ < 0)
		return defValue;

	if (i >= 0 && i < argv.size())
		return argv[i];
	else
		return defValue;
}

bool CommandLineTokenizer::getOptionBool (const String& tokenToSearch,
										  const bool defValue,
										  const bool caseSensitive)
{
	int i = searchToken (tokenToSearch, caseSensitive);
	if (i++ < 0)
		return defValue;

	if (i >= 0 && i < argv.size())
		return argv[i].getIntValue()==0 ? false : true;
	else
		return defValue;
}

int CommandLineTokenizer::getOptionInt (const String& tokenToSearch,
										const int defValue,
										const bool caseSensitive)
{
	int i = searchToken (tokenToSearch, caseSensitive);
	if (i++ < 0)
		return defValue;

	if (i >= 0 && i < argv.size())
		return argv[i].getIntValue();
	else
		return defValue;
}

double CommandLineTokenizer::getOptionDouble (const String& tokenToSearch,
											  const double defValue,
											  const bool caseSensitive)
{
	int i = searchToken (tokenToSearch, caseSensitive);
	if (i++ < 0)
		return defValue;

	if (i >= 0 && i < argv.size())
		return argv[i].getDoubleValue();
	else
		return defValue;
}


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

#ifndef __ANGELJUICE_TABBEDSUPPORT_HEADER__
#define __ANGELJUICE_TABBEDSUPPORT_HEADER__


#include "../AngelJuice_config.h"
#include "AngelJuice_DebugOutput.h"
#include "AngelJuice_ErrorOutput.h"
#include "AngelJuice_CallstackOutput.h"
#include "AngelJuice_SearchComponent.h"


//==============================================================================
class AngelJuiceComponent;


//==============================================================================
/**
    This component is actually a tab component which holds a set of support
    components: mainly the utils components for outputting compiler messages,
    errors and general debugging informations.

    It is hold by the parent AngelJuice component, and provides a easy interface
    for setting multiple values, without the need of remembering each
    sub-component pointer.
*/
class TabbedSupportComponent  : public TabbedComponent
{
public:

    //==============================================================================
    /** Constructor */
    TabbedSupportComponent (AngelJuiceComponent* holder);

    /** Destructor */
    ~TabbedSupportComponent ();

    //==============================================================================
    /**
        When u right click on the tab selector, you could set specific
        support component options.
    */
	void popupMenuClickOnTab (const int tabIndex, const String& tabName);

    //==============================================================================
    /**
        Manipulate the output console.
    */
	void appendOutputText (const String& text);
	void replaceOutputText (const String& text);
	void clearOutputText ();

    //==============================================================================
    /** These let you deal with single errors, typically triggered by the
        scripting engine. Errors are accumulated in the ErrorOutputComponent.
    */
	void appendErrorLine (const String& errorType,
                          const String& errorString,
						  const String& fileName,
						  const int lineNumber);
	void clearErrors ();

    //==============================================================================
    /**
        Manipulate a callstack text line, which is actually a text editor.
    */
	void appendCallstackText (const String& text);
	void replaceCallstackText (const String& text);
	void clearCallstackText ();

    //==============================================================================
    /**
        Manipulate a variable on stack text line, which is actually a text editor.
    */
	void appendVariablesText (const String& text);
	void replaceVariablesText (const String& text);
	void clearVariablesText ();

protected:

	AngelJuiceComponent* holder;

	DebugOutputComponent* outputTextEditor;
	ErrorOutputComponent* errorTableComponent;
	CallstackOutputComponent* callstackComponent;
	SearchComponent* searchComponent;
};


#endif // __ANGELJUICE_TABBEDSUPPORT_HEADER__

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

#include "../AngelJuice.h"
#include "../AngelJuice_config.h"
#include "AngelJuice_TabbedSupport.h"


//==============================================================================
TabbedSupportComponent::TabbedSupportComponent (AngelJuiceComponent* holder_) :
	TabbedComponent (TabbedButtonBar::TabsAtBottom),
	holder (holder_),
	outputTextEditor (0),
	callstackComponent (0),
	searchComponent (0)
{
	setTabBarDepth (26);
	// setIndent (3);
	setWantsKeyboardFocus (true);

	outputTextEditor = new DebugOutputComponent (ANGELJUICE_WELCOME);
	errorTableComponent = new ErrorOutputComponent (holder);
	callstackComponent = new CallstackOutputComponent ();
//	searchComponent = new SearchComponent ();

	addTab (T("output"), ANGELJUICE_COLOR, outputTextEditor, true);
	addTab (T("errors"), ANGELJUICE_COLOR, errorTableComponent, true);
	addTab (T("callstack"), ANGELJUICE_COLOR, callstackComponent, true);
//	addTab (T("breakpoints"), ANGELJUICE_COLOR, 0, false);
//	addTab (T("find"), ANGELJUICE_COLOR, searchComponent, true);
}

TabbedSupportComponent::~TabbedSupportComponent ()
{
}

void TabbedSupportComponent::popupMenuClickOnTab (const int tabIndex, const String& tabName)
{
}

//==============================================================================
void TabbedSupportComponent::appendOutputText (const String& text)
{
	String textToInsert = outputTextEditor->getText() + text;

	outputTextEditor->setText (textToInsert);
	outputTextEditor->setCaretPosition (textToInsert.length() + 1);
}

void TabbedSupportComponent::replaceOutputText (const String& text)
{
	outputTextEditor->setText (text);
}

void TabbedSupportComponent::clearOutputText ()
{
	outputTextEditor->setText (T(""));
}

//==============================================================================
void TabbedSupportComponent::appendErrorLine (const String& errorType,
					                          const String& errorString,
											  const String& fileName,
											  const int lineNumber)
{
	errorTableComponent->appendErrorLine (errorType,errorString,fileName,lineNumber);
}

void TabbedSupportComponent::clearErrors ()
{
	errorTableComponent->clearErrors ();
}

//==============================================================================
void TabbedSupportComponent::appendCallstackText (const String& text)
{
	callstackComponent->appendCallstackText (text);
}

void TabbedSupportComponent::replaceCallstackText (const String& text)
{
	callstackComponent->replaceCallstackText (text);
}

void TabbedSupportComponent::clearCallstackText ()
{
	callstackComponent->clearCallstackText ();
}

//==============================================================================
void TabbedSupportComponent::appendVariablesText (const String& text)
{
	callstackComponent->appendVariablesText (text);
}

void TabbedSupportComponent::replaceVariablesText (const String& text)
{
	callstackComponent->replaceVariablesText (text);
}

void TabbedSupportComponent::clearVariablesText ()
{
	callstackComponent->clearVariablesText ();
}


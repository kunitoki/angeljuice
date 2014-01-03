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
#include "AngelJuice_CallstackOutput.h"


//==============================================================================
CallstackOutputComponent::CallstackOutputComponent () :
	callstackTextEditor (0),
	variablesTextEditor (0)
{
	// horizontal layout
	horizontalLayout.setItemLayout (0, -0.200, -0.800, -0.500);
	horizontalLayout.setItemLayout (1, 3, 3, 3);
	horizontalLayout.setItemLayout (2, -0.200, -0.800, -0.500);

	verticalDividerBar = new StretchableLayoutResizerBar (&horizontalLayout, 1, true);
    addAndMakeVisible (verticalDividerBar);

	addAndMakeVisible (callstackTextEditor = new DebugOutputComponent (T("")));
	addAndMakeVisible (variablesTextEditor = new DebugOutputComponent (T("")));
}

CallstackOutputComponent::~CallstackOutputComponent ()
{
	deleteAllChildren ();
}

void CallstackOutputComponent::resized ()
{

	// lay out the list box and vertical divider..
    Component* vcomps[] = { callstackTextEditor, verticalDividerBar, variablesTextEditor };

    horizontalLayout.layOutComponents (vcomps, 3, 
                                       0, 0,
									   getWidth(), getHeight(),
                                       false,     // vertical
                                       true);    // resize the components' heights as well as width
}

//------------------------------------------------------------------------------
void CallstackOutputComponent::appendCallstackText (const String& text)
{
	callstackTextEditor->setText (callstackTextEditor->getText() + text);
}

void CallstackOutputComponent::replaceCallstackText (const String& text)
{
	callstackTextEditor->setText (text);
}

void CallstackOutputComponent::clearCallstackText ()
{
	callstackTextEditor->setText (T(""));
}

//------------------------------------------------------------------------------
void CallstackOutputComponent::appendVariablesText (const String& text)
{
	variablesTextEditor->setText (callstackTextEditor->getText() + text);
}

void CallstackOutputComponent::replaceVariablesText (const String& text)
{
	variablesTextEditor->setText (text);
}

void CallstackOutputComponent::clearVariablesText ()
{
	variablesTextEditor->setText (T(""));
}


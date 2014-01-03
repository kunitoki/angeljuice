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

#include "../AngelJuice.h"
#include "../AngelJuice_config.h"
#include "../AngelJuice_command.h"
#include "../resources/AngelJuice_Resource.h"

#include "AngelJuice_OptionWindow.h"
#include "AngelJuice_CompilerPage.h"
#include "AngelJuice_FontsPage.h"
#include "AngelJuice_AboutPage.h"



//==============================================================================
class DummyPage  : public Component
{
public:
    DummyPage()
    {
		addAndMakeVisible (label = new Label (String::empty,T("Sorry :( not implemented !")));
		label->setJustificationType (Justification::centred);
		label->setFont (Font(20.0f,Font::bold));
    }

    ~DummyPage()
    {
        deleteAllChildren();
    }

    void resized()
    {
		label->setBounds (0, (getHeight() - 20) / 2, getWidth(), 20);
    }

protected:

    Label* label;
};

//==============================================================================
static const tchar* compilerPage = T("Config");
static const tchar* fontsPage = T("Fonts");
static const tchar* keysPage = T("Keys");
static const tchar* aboutPage = T("About");

class OptionsComponent  : public PreferencesPanel
{
public:

    OptionsComponent()
    {
        addSettingsPage (compilerPage, Resource::options_compiler, Resource::options_compiler_size);
        addSettingsPage (keysPage, Resource::options_keyboard, Resource::options_keyboard_size);
        addSettingsPage (fontsPage, Resource::options_font, Resource::options_font_size);
        addSettingsPage (aboutPage, Resource::options_about, Resource::options_about_size);
    }

    ~OptionsComponent()
    {
    }

    Component* createComponentForPage (const String& pageName)
    {
        if (pageName == compilerPage)
        {
            return new DummyPage();
//            return new CompilerPage();
        }
        else if (pageName == fontsPage)
        {
			return new FontsPage ();
        }
        else if (pageName == keysPage)
        {
			return new KeyMappingEditorComponent (
				CommandManager::getInstance()->getKeyMappings(), true);
		}
        else if (pageName == aboutPage)
        {
            return new AboutPage();
        }

        return new DummyPage();
    }
};

//==============================================================================
static String prefsWindowPos;

OptionWindow::OptionWindow (AngelJuiceComponent* holder_) :
	DialogWindow (T("AngelJuice Options"), Colour::greyLevel (0.92f), true, false),
	holder (holder_)
{
    OptionsComponent* const p = new OptionsComponent();
    p->setSize (514, 600);

    setContentComponent (p, true, true);

//    if (! restoreWindowStateFromString (prefsWindowPos))
//        centreAroundComponent (0, getWidth(), getHeight());

	setTitleBarHeight (24);
    setResizable (true, true);
    setResizeLimits (400, 500, 700, 900);

	addToDesktop (getDesktopWindowStyleFlags());
}

OptionWindow::~OptionWindow()
{
//    prefsWindowPos = getWindowStateAsString();
}

int OptionWindow::getDesktopWindowStyleFlags() const
{
    return ComponentPeer::windowHasDropShadow;
}

void OptionWindow::closeButtonPressed()
{
	if (isCurrentlyModal())
		exitModalState (0);

    setVisible (false);
}

void OptionWindow::show()
{
    centreAroundComponent (0, getWidth(), getHeight());

	runModalLoop();
}

void OptionWindow::showAbout()
{
	OptionsComponent* option = (OptionsComponent*) getContentComponent();
	option->setCurrentPage (aboutPage);

	show ();
}


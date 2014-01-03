/*
  ==============================================================================

   This file is part of AngelJuice

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

  ==============================================================================
*/

#ifndef __ANGELJUICE_MAINCOMPONENT_H_INCLUDED__
#define __ANGELJUICE_MAINCOMPONENT_H_INCLUDED__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../CommandIDs.h"

class MainWindow;


//==============================================================================
/*
*/
class MainComponent : public Component
{
public:
    MainComponent(MainWindow* mainWindow);
    ~MainComponent();

    void paint (Graphics&);
    void resized();

private:
    MainWindow* mainWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // __ANGELJUICE_MAINCOMPONENT_H_INCLUDED__

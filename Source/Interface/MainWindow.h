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

#ifndef __ANGELJUICE_MAINWINDOW_H_INCLUDED__
#define __ANGELJUICE_MAINWINDOW_H_INCLUDED__

#include "../../JuceLibraryCode/JuceHeader.h"


//==============================================================================
class MainWindow  : public DocumentWindow
{
public:
    MainWindow();
    ~MainWindow();

    // called when the close button is pressed or esc is pushed
    void closeButtonPressed();

    // the command manager object used to dispatch command events
    ApplicationCommandManager commandManager;

private:
    //ScopedPointer<Component> taskbarIcon;
};


#endif  // __ANGELJUICE_MAINWINDOW_H_INCLUDED__

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

#ifndef __ANGELJUICE_COMMANDIDS_H_INCLUDED__
#define __ANGELJUICE_COMMANDIDS_H_INCLUDED__

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================

//------------------------------------------------------------------------------

namespace CommandIDs
{
    enum
    {
        fileNew            = 0x2000,
        fileLoad           = 0x2001,
        fileSave           = 0x2002,
        fileSaveAs         = 0x2003,
        fileSaveAll        = 0x2004,
        fileClose          = 0x2005,
        fileCloseAll       = 0x2006,
        fileRevert         = 0x2007,
        fileClone          = 0x2008,

        editUndo           = 0x2009,
        editRedo           = 0x2010,
        editCut            = 0x2011,
        editCopy           = 0x2012,
        editPaste          = 0x2013,

        projectLoad        = 0x2014, // TODO
        projectSave        = 0x2015, // TODO
        projectBundle      = 0x2016, // TODO
        projectClose       = 0x2017, // TODO

        scriptCompile      = 0x2018,
        scriptDebug        = 0x2019,
        scriptRun          = 0x2020,
        scriptAbort        = 0x2021,
        scriptContinue     = 0x2022,
        scriptStepNext     = 0x2023,
        scriptStepInto     = 0x2024, // TODO
        scriptStepOut      = 0x2025, // TODO
        scriptLoadByteCode = 0x2026,
        scriptSaveByteCode = 0x2027,

        breakPointToggle   = 0x2028,
        breakPointClear    = 0x2029,

        pluginInstall      = 0x2030, // TODO

        appOptions         = 0x2031,
        appToolbar         = 0x2032,
        appFontUpdate      = 0x2033,
        appColoursUpdate   = 0x2034,
        appFullScreen      = 0x2035,
        appUpdateCheck     = 0x2036,
        appAboutBox        = 0x2037,
        appClose           = 0x2038
    };
};


//------------------------------------------------------------------------------

namespace CommandCategoriesSourceCode
{
    static const char* const file = "File";
    static const char* const edit = "Edit";
    static const char* const project = "Project";
    static const char* const view = "View";
    static const char* const compiler = "Compiler";
    static const char* const help = "?";
}


#endif // __ANGELJUICE_COMMANDIDS_H_INCLUDED__

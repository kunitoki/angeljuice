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

#ifndef __ANGELJUICE_COMMAND_HEADER__
#define __ANGELJUICE_COMMAND_HEADER__


#include "juce.h"


//==============================================================================
namespace CommandIDs
{
    static const int fileNew			= 0x2000;
    static const int fileLoad			= 0x2001;
    static const int fileSave			= 0x2002;
    static const int fileSaveAs			= 0x2003;
    static const int fileSaveAll		= 0x2004;
	static const int fileClose			= 0x2005;
	static const int fileCloseAll		= 0x2006;
	static const int fileRevert			= 0x2007;
	static const int fileClone			= 0x2008;

	static const int editUndo			= 0x2009;
	static const int editRedo			= 0x2010;
	static const int editCut			= 0x2011;
	static const int editCopy			= 0x2012;
	static const int editPaste			= 0x2013;

	static const int projectLoad		= 0x2014; // @TODO
    static const int projectSave		= 0x2015; // @TODO
    static const int projectBundle		= 0x2016; // @TODO
    static const int projectClose		= 0x2017; // @TODO

	static const int scriptCompile		= 0x2018;
	static const int scriptDebug		= 0x2019;
    static const int scriptRun			= 0x2020;
    static const int scriptAbort		= 0x2021;
	static const int scriptContinue		= 0x2022;
    static const int scriptStepNext		= 0x2023;
    static const int scriptStepInto		= 0x2024; // @TODO
    static const int scriptStepOut		= 0x2025; // @TODO
	static const int scriptLoadByteCode	= 0x2026;
    static const int scriptSaveByteCode	= 0x2027;

	static const int breakPointToggle	= 0x2028;
	static const int breakPointClear	= 0x2029;

	static const int pluginInstall		= 0x2030; // @TODO

	static const int appOptions			= 0x2031;
	static const int appToolbar			= 0x2032;
	static const int appFontUpdate		= 0x2033;
	static const int appColoursUpdate	= 0x2034;
	static const int appFullScreen		= 0x2035;
	static const int appUpdateCheck		= 0x2036;
	static const int appAboutBox		= 0x2037;
	static const int appClose			= 0x2038;
};


//==============================================================================
namespace CommandCategories
{
    static const tchar* const file = T("File");
    static const tchar* const edit = T("Edit");
    static const tchar* const project = T("Project");
    static const tchar* const view = T("View");
    static const tchar* const compiler = T("Compiler");
    static const tchar* const help = T("?");
}


//==============================================================================
class CommandManager : public ApplicationCommandManager
{
public:

	CommandManager ();
    ~CommandManager ();

	juce_DeclareSingleton (CommandManager, true)

};


#endif // __ANGELJUICE_COMMAND_HEADER__

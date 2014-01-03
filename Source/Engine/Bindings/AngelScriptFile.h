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

#ifndef __ANGELJUICE_ANGELSCRIPTFILE_H_INCLUDED__
#define __ANGELJUICE_ANGELSCRIPTFILE_H_INCLUDED__

#include "../../../JuceLibraryCode/JuceHeader.h"

#include "../ScriptablePlugin.h"

namespace Bindings {


//==============================================================================
/** Manages File in angel scripts

    @see AngelScriptengine, File
*/
class ScriptableFile : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


//==============================================================================
/** Manages InputStreams angel scripts

    @see AngelScriptengine, InputStream
*/
class ScriptableInputStream : public ScriptableExtensionObjectCreator
{
public:
	void registerTypes(asIScriptEngine* engine) const;
	void registerFunctions(asIScriptEngine* engine) const;
};


} // end namespace

#endif	// __ANGELJUICE_ANGELSCRIPTFILE_H_INCLUDED__

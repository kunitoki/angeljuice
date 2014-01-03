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
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,, 
   Boston, MA 02111-1307 USA

  ==============================================================================
*/

#include "AngelScriptCrypt.h"

#include "../ScriptableEngine.h"

namespace Bindings {


//==============================================================================

//------------------------------------------------------------------------------

void BlowFishConstructor(void* key, uint32 keylength, BlowFish* thisPointer)
{
	new(thisPointer) BlowFish(key, keylength);
}

void BlowFishConstructorByBlowFish(const BlowFish& bf, BlowFish* thisPointer)
{
	new(thisPointer) BlowFish(bf);
}

void BlowFishDestructor(BlowFish* thisPointer)
{
	thisPointer->~BlowFish();
}


//------------------------------------------------------------------------------

void ScriptableBlowFish::registerTypes(asIScriptEngine* engine) const
{
	int r;

	r = engine->RegisterObjectType("BlowFish", sizeof(BlowFish), asOBJ_VALUE | asOBJ_APP_CLASS_CDA); jassert(r>=0);
}


void ScriptableBlowFish::registerFunctions(asIScriptEngine* engine) const
{
    int r;

    // constructors / destructors
	r = engine->RegisterObjectBehaviour("BlowFish", asBEHAVE_CONSTRUCT, "void f(void_ptr, uint32)",    asFUNCTION(BlowFishConstructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("BlowFish", asBEHAVE_CONSTRUCT, "void f(const BlowFish& in)",  asFUNCTION(BlowFishConstructorByBlowFish), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("BlowFish", asBEHAVE_DESTRUCT,  "void f()",                    asFUNCTION(BlowFishDestructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	
	// operators
	r = engine->RegisterObjectMethod("BlowFish", "BlowFish& opAssign(const BlowFish& in)",             asMETHODPR(BlowFish, operator=, (const BlowFish&), BlowFish&), asCALL_THISCALL); jassert( r >= 0 );
	
    // methods
	r = engine->RegisterObjectMethod("BlowFish", "void encrypt(uint32& inout, uint32& inout) const",   asMETHOD(BlowFish, encrypt), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BlowFish", "void decrypt(uint32& inout, uint32& inout) const",   asMETHOD(BlowFish, decrypt), asCALL_THISCALL); jassert(r>=0);
}


} // end namespace

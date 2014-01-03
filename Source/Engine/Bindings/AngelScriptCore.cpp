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

//#include "AngelJuice_AngelScriptCommon.h"
#include "AngelScriptCore.h"
#include "AngelScriptString.h"

#include "../ScriptableEngine.h"

namespace Bindings {


//==============================================================================

static uint32 dummy32bit = 0;

void DummyConstructor(void* thisPointer)
{
    (void) thisPointer;
}

void DummyDestructor(void* thisPointer)
{
    (void) thisPointer;
}

template<class A, class B>
B* ReferenceCast(A* a)
{
    // If the handle already is a null handle, then just return the null handle
    if( !a ) return 0;
    
    // Now try to dynamically cast the pointer to the wanted type
    B* b = dynamic_cast<B*>(a);
    if( b != 0 )
    {
        // Since the cast was made, we need to increase the ref counter for the returned handle
        b->addref();
    }

    return b;
}

//r = engine->RegisterObjectBehaviour("base", asBEHAVE_REF_CAST, "derived@ f()", asFUNCTION((refCast<base,derived>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );
//r = engine->RegisterObjectBehaviour("derived", asBEHAVE_IMPLICIT_REF_CAST, "base@ f()", asFUNCTION((refCast<derived,base>)), asCALL_CDECL_OBJLAST); assert( r >= 0 );



//==============================================================================

//------------------------------------------------------------------------------

void AssertWrapper(bool condition)
{
    asIScriptContext* ctx = asGetActiveContext();
    asIScriptEngine* ase = ctx->GetEngine();
    
    ScriptableEngine* engine = (ScriptableEngine*)ase->GetUserData(ScriptableEngine::SCRIPT_ENGINE_PTR);
    if (engine)
    {
        if (! condition)
        {
            const int lineNumber = ctx->GetLineNumber();
            const String file = engine->resolveOriginalFile(lineNumber);
		    const int line = engine->resolveOriginalLine(lineNumber);
            
            if (engine->getEngineModel())
		        engine->getEngineModel()->reportErrors("Assert", "Condition not met", file, line);

		    if (engine->isDebugEnabled())
		        engine->abortExecution();
        }
    }
}

void ClearFunctionWrapper()
{
    asIScriptContext* ctx = asGetActiveContext();
    asIScriptEngine* ase = ctx->GetEngine();
    
    ScriptableEngine* engine = (ScriptableEngine*)ase->GetUserData(ScriptableEngine::SCRIPT_ENGINE_PTR);
	if (engine && engine->getEngineModel())
	{
		engine->getEngineModel()->reportOutput("", 0);
	}
}

void PrintFunctionWrapper(const String& message)
{
    asIScriptContext* ctx = asGetActiveContext();
    asIScriptEngine* ase = ctx->GetEngine();
    
    ScriptableEngine* engine = (ScriptableEngine*)ase->GetUserData(ScriptableEngine::SCRIPT_ENGINE_PTR);
	if (engine && engine->getEngineModel())
	{
		engine->getEngineModel()->reportOutput(message, 1);
	}
}

void PrintlnFunctionWrapper(const String& message)
{
    asIScriptContext* ctx = asGetActiveContext();
    asIScriptEngine* ase = ctx->GetEngine();
    
    ScriptableEngine* engine = (ScriptableEngine*)ase->GetUserData(ScriptableEngine::SCRIPT_ENGINE_PTR);
	if (engine && engine->getEngineModel())
	{
      	String messageToSend = message + "\n";
		engine->getEngineModel()->reportOutput(messageToSend, 1);
	}
}

void WarningAlertWrapper(const String& text)
{
	AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Alert", text);
}

void ErrorAlertWrapper(const String& text)
{
	AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Error", text);
}

int AskAlertWrapper(const String& text)
{
	return (int)AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "Question", text);
}

//void ExecuteScriptWrapper(const String& text)
//{
//	ScriptableEngine::getInstance()->executeString(text);
//}

void ThrowExceptionWrapper(const String& text)
{
	asIScriptContext* context = asGetActiveContext();

	context->SetException((const char*)text.toUTF8());
}

void AbortApplicationWrapper()
{
    asIScriptContext* ctx = asGetActiveContext();
    asIScriptEngine* ase = ctx->GetEngine();
    ScriptableEngine* engine = (ScriptableEngine*)ase->GetUserData(ScriptableEngine::SCRIPT_ENGINE_PTR);
    if (engine && engine->isRunningScript())
    {
        engine->abortExecution();
    }
}

void QuitApplicationWrapper()
{
    // TODO - allow only when run guiless
	JUCEApplication::getInstance()->systemRequestedQuit();
}


//------------------------------------------------------------------------------

void ScriptableCore::registerTypes(asIScriptEngine* engine) const
{
	int r;

	r = engine->RegisterObjectType("void_ptr", sizeof(void*), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_PRIMITIVE); jassert(r>=0);
}

void ScriptableCore::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	// register default debugger output
	r = engine->RegisterGlobalFunction("void assert(bool)",                 asFUNCTION(AssertWrapper),   asCALL_CDECL); jassert (r >= 0);
	r = engine->RegisterGlobalFunction("void clear()",                      asFUNCTION(ClearFunctionWrapper),   asCALL_CDECL); jassert (r >= 0);
	r = engine->RegisterGlobalFunction("void print(const String&)",         asFUNCTION(PrintFunctionWrapper),   asCALL_CDECL); jassert (r >= 0);
	r = engine->RegisterGlobalFunction("void println(const String&)",       asFUNCTION(PrintlnFunctionWrapper), asCALL_CDECL); jassert (r >= 0);
	//r = engine->RegisterGlobalFunction("void execute(const String&)",       asFUNCTION(ExecuteScriptWrapper), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void throw(const String&)",         asFUNCTION(ThrowExceptionWrapper), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void alert(const String&)",         asFUNCTIONPR(WarningAlertWrapper, (const String&), void), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void error(const String&)",         asFUNCTIONPR(ErrorAlertWrapper, (const String&), void), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("int ask(const String&)",            asFUNCTIONPR(AskAlertWrapper, (const String&), int), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void quit()",                       asFUNCTION(QuitApplicationWrapper), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void abort()",                      asFUNCTION(AbortApplicationWrapper), asCALL_CDECL); jassert( r >= 0 );
}


//==============================================================================

//------------------------------------------------------------------------------

void ScriptableMath::registerTypes(asIScriptEngine* engine) const
{
	int r;

	// global variables
	r = engine->RegisterGlobalProperty("float float_Pi", (void*)&float_Pi);
	r = engine->RegisterGlobalProperty("double double_Pi", (void*)&double_Pi);
}


void ScriptableMath::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	// math functions
	r = engine->RegisterGlobalFunction("double sin(double)",					asFUNCTION(sin), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float sinf(float)",						asFUNCTION(sinf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double cos(double)",					asFUNCTION(cos), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float cosf(float)",						asFUNCTION(cosf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double sqrt(double)",					asFUNCTION(sqrt), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float sqrtf(float)",					asFUNCTION(sqrtf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double asin(double)",					asFUNCTION(asin), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float asinf(float)",					asFUNCTION(asinf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double acos(double)",					asFUNCTION(acos), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float acosf(float)",					asFUNCTION(acosf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double tan(double)",					asFUNCTION(tan), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float tanf(float)",						asFUNCTION(tanf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double atan(double)",					asFUNCTION(atan), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float atanf(float)",					asFUNCTION(atanf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double log(double)",					asFUNCTION(log), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float logf(float)",						asFUNCTION(logf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double log10(double)",					asFUNCTION(log10), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float log10f(float)",					asFUNCTION(log10f), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double pow(double, double)",			asFUNCTION(pow), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float powf(float, float)",				asFUNCTION(powf), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int8 min(int8, int8)",				    asFUNCTIONPR(jmin, (int8, int8), int8), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int8 max(int8, int8)",					asFUNCTIONPR(jmax, (int8, int8), int8), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int8 limit(int8, int8, int8)",			asFUNCTION(jlimit<int8>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int16 min(int8, int16)",			    asFUNCTIONPR(jmin, (int16, int16), int16), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int16 max(int8, int16)",				asFUNCTIONPR(jmax, (int16, int16), int16), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int16 limit(int16, int16, int16)",		asFUNCTION(jlimit<int16>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int min(int, int)",						asFUNCTIONPR(jmin, (int32, int32), int32), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int max(int, int)",						asFUNCTIONPR(jmax, (int32, int32), int32), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int limit(int, int, int)",				asFUNCTION(jlimit<int32>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int64 min(int64, int64)",				asFUNCTIONPR(jmin, (int64, int64), int64), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int64 max(int64, int64)",				asFUNCTIONPR(jmax, (int64, int64), int64), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("int64 limit(int64, int64, int64)",		asFUNCTION(jlimit<int64>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float min(float, float)",				asFUNCTIONPR(jmin, (float, float), float), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float max(float, float)",				asFUNCTIONPR(jmax, (float, float), float), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("float limit(float, float, float)",		asFUNCTION(jlimit<float>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double min(double, double)",			asFUNCTIONPR(jmin, (double, double), double), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double max(double, double)",			asFUNCTIONPR(jmax, (double, double), double), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("double limit(double, double, double)",	asFUNCTION(jlimit<double>), asCALL_CDECL); jassert(r >= 0);
	//r = engine->RegisterGlobalFunction("double hypot(double, double)",			asFUNCTION(hypot), asCALL_CDECL); jassert(r >= 0);
	//r = engine->RegisterGlobalFunction("double j0(double)",					    asFUNCTION(j0), asCALL_CDECL); jassert(r >= 0);
	//r = engine->RegisterGlobalFunction("double j1(double)",					    asFUNCTION(j1), asCALL_CDECL); jassert(r >= 0);
	//r = engine->RegisterGlobalFunction("double jn(int, double)",				asFUNCTION(jn), asCALL_CDECL); jassert(r >= 0);
	//r = engine->RegisterGlobalFunction("double y0(double)",					    asFUNCTION(y0), asCALL_CDECL); jassert(r >= 0);
	//r = engine->RegisterGlobalFunction("double y1(double)",					    asFUNCTION(y1), asCALL_CDECL); jassert(r >= 0);
	//r = engine->RegisterGlobalFunction("double yn(int, double)",				asFUNCTION(yn), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("void swap(bool&, bool&)",				asFUNCTION(swapVariables<bool>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("void swap(int8&, int8&)",				asFUNCTION(swapVariables<int8>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("void swap(int16&, int16&)",				asFUNCTION(swapVariables<int16>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("void swap(int&, int&)",					asFUNCTION(swapVariables<int32>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("void swap(int64&, int64&)",				asFUNCTION(swapVariables<int64>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("void swap(float&, float&)",				asFUNCTION(swapVariables<float>), asCALL_CDECL); jassert(r >= 0);
	r = engine->RegisterGlobalFunction("void swap(double&, double&)",			asFUNCTION(swapVariables<double>), asCALL_CDECL); jassert(r >= 0);
}


//==============================================================================

//------------------------------------------------------------------------------

void ScriptableByteOrder::registerTypes(asIScriptEngine* engine) const
{
}


void ScriptableByteOrder::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	// math functions
    r = engine->SetDefaultNamespace("ByteOrder"); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("uint16 swap(uint16)",                                asFUNCTIONPR(ByteOrder::swap, (uint16), uint16), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint32 swap(uint32)",                                asFUNCTIONPR(ByteOrder::swap, (uint32), uint32), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint64 swap(uint64)",                                asFUNCTIONPR(ByteOrder::swap, (uint64), uint64), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint16 swapIfBigEndian(uint16)",                     asFUNCTIONPR(ByteOrder::swapIfBigEndian, (uint16), uint16), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint32 swapIfBigEndian(uint32)",                     asFUNCTIONPR(ByteOrder::swapIfBigEndian, (uint32), uint32), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint64 swapIfBigEndian(uint64)",                     asFUNCTIONPR(ByteOrder::swapIfBigEndian, (uint64), uint64), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint16 swapIfLittleEndian(uint16)",                  asFUNCTIONPR(ByteOrder::swapIfLittleEndian, (uint16), uint16), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint32 swapIfLittleEndian(uint32)",                  asFUNCTIONPR(ByteOrder::swapIfLittleEndian, (uint32), uint32), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint64 swapIfLittleEndian(uint64)",                  asFUNCTIONPR(ByteOrder::swapIfLittleEndian, (uint64), uint64), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint32 littleEndianInt(const void_ptr)",             asFUNCTION(ByteOrder::littleEndianInt), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint64 littleEndianInt64(const void_ptr)",           asFUNCTION(ByteOrder::littleEndianInt64), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint16 littleEndianShort(const void_ptr)",           asFUNCTION(ByteOrder::littleEndianShort), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint32 bigEndianInt(const void_ptr)",                asFUNCTION(ByteOrder::bigEndianInt), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint64 bigEndianInt64(const void_ptr)",              asFUNCTION(ByteOrder::bigEndianInt64), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint16 bigEndianShort(const void_ptr)",              asFUNCTION(ByteOrder::bigEndianShort), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("bool isBigEndian()",                                 asFUNCTION(ByteOrder::isBigEndian), asCALL_CDECL); jassert(r>=0);
	r = engine->SetDefaultNamespace(""); jassert(r >= 0);

	/*
    static int 	littleEndian24Bit (const char *bytes) noexcept
    static int 	bigEndian24Bit (const char *bytes) noexcept
    static void 	littleEndian24BitToChars (int value, char *destBytes) noexcept
    static void 	bigEndian24BitToChars (int value, char *destBytes) noexcept
    static bool 	isBigEndian () noexcept
    */
}


//==============================================================================

//------------------------------------------------------------------------------

void BigIntegerConstructor(BigInteger* thisPointer)
{
	new(thisPointer) BigInteger();
}

void BigIntegerConstructorInt32(int32 value, BigInteger* thisPointer)
{
	new(thisPointer) BigInteger(value);
}

void BigIntegerConstructorUInt32(uint32 value, BigInteger* thisPointer)
{
	new(thisPointer) BigInteger(value);
}

void BigIntegerConstructorInt64(int64 value, BigInteger* thisPointer)
{
	new(thisPointer) BigInteger(value);
}

void BigIntegerConstructorBigInteger(const BigInteger& other, BigInteger* thisPointer)
{
	new(thisPointer) BigInteger(other);
}

void BigIntegerDestructor(BigInteger* thisPointer)
{
	thisPointer->~BigInteger();
}


//------------------------------------------------------------------------------

String BigIntegerToString1(int a, BigInteger& bigint)
{
    return bigint.toString(a);
}

String BigIntegerToString2(int a, int b, BigInteger& bigint)
{
    return bigint.toString(a, b);
}


//------------------------------------------------------------------------------

bool BigIntegerAt(int i, BigInteger& bigint)
{
	if (i >= 0 && i < bigint.getHighestBit())
	{
	    return bigint[i];
	}
	
	// Set a script exception
	asIScriptContext *ctx = asGetActiveContext();
	ctx->SetException("BigInteger index out of range");

    return false;
}


//------------------------------------------------------------------------------

void ScriptableBigInteger::registerTypes(asIScriptEngine* engine) const
{
	int r;

	r = engine->RegisterObjectType("BigInteger", sizeof(BigInteger), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); jassert(r>=0);
}


void ScriptableBigInteger::registerFunctions(asIScriptEngine* engine) const
{
    int r;

    // constructors / destructors
	r = engine->RegisterObjectBehaviour("BigInteger", asBEHAVE_CONSTRUCT, "void f()",                     asFUNCTION(BigIntegerConstructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("BigInteger", asBEHAVE_CONSTRUCT, "void f(const int32)",          asFUNCTION(BigIntegerConstructorInt32), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("BigInteger", asBEHAVE_CONSTRUCT, "void f(const uint32)",         asFUNCTION(BigIntegerConstructorUInt32), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("BigInteger", asBEHAVE_CONSTRUCT, "void f(const int64)",          asFUNCTION(BigIntegerConstructorInt64), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("BigInteger", asBEHAVE_CONSTRUCT, "void f(const BigInteger& in)", asFUNCTION(BigIntegerConstructorBigInteger), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("BigInteger", asBEHAVE_DESTRUCT,  "void f()",                     asFUNCTION(BigIntegerDestructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	
	// operators
	/*
    bool 	operator== (const BigInteger &other) const noexcept
    bool 	operator!= (const BigInteger &other) const noexcept
    bool 	operator< (const BigInteger &other) const noexcept
    bool 	operator<= (const BigInteger &other) const noexcept
    bool 	operator> (const BigInteger &other) const noexcept
    bool 	operator>= (const BigInteger &other) const noexcept    
    */
	r = engine->RegisterObjectMethod("BigInteger", "bool opIndex(int) const",                             asFUNCTION(BigIntegerAt), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opAssign(const BigInteger& in)",          asMETHODPR(BigInteger, operator=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opAddAssign(const BigInteger& in)",       asMETHODPR(BigInteger, operator+=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opSubAssign(const BigInteger& in)",       asMETHODPR(BigInteger, operator-=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opMulAssign(const BigInteger& in)",       asMETHODPR(BigInteger, operator*=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opDivAssign(const BigInteger& in)",       asMETHODPR(BigInteger, operator/=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opOrAssign(const BigInteger& in)",        asMETHODPR(BigInteger, operator|=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opAndAssign(const BigInteger& in)",       asMETHODPR(BigInteger, operator&=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opXorAssign(const BigInteger& in)",       asMETHODPR(BigInteger, operator^=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opModAssign(const BigInteger& in)",       asMETHODPR(BigInteger, operator%=, (const BigInteger&), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opShlAssign(int)",                        asMETHODPR(BigInteger, operator<<=, (int), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opShrAssign(int)",                        asMETHODPR(BigInteger, operator>>=, (int), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opPreInc()",                              asMETHODPR(BigInteger, operator++, (), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger& opPreDec()",                              asMETHODPR(BigInteger, operator--, (), BigInteger&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opPostInc(int)",                           asMETHODPR(BigInteger, operator++, (int), BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opPostDec(int)",                           asMETHODPR(BigInteger, operator--, (int), BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opNeg() const",                            asMETHODPR(BigInteger, operator-, () const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opAdd(const BigInteger& in) const",        asMETHODPR(BigInteger, operator+, (const BigInteger&) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opSub(const BigInteger& in) const",        asMETHODPR(BigInteger, operator-, (const BigInteger&) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opMul(const BigInteger& in) const",        asMETHODPR(BigInteger, operator*, (const BigInteger&) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opDiv(const BigInteger& in) const",        asMETHODPR(BigInteger, operator/, (const BigInteger&) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opOr(const BigInteger& in) const",         asMETHODPR(BigInteger, operator|, (const BigInteger&) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opAnd(const BigInteger& in) const",        asMETHODPR(BigInteger, operator&, (const BigInteger&) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opXor(const BigInteger& in) const",        asMETHODPR(BigInteger, operator^, (const BigInteger&) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opMod(const BigInteger& in) const",        asMETHODPR(BigInteger, operator%, (const BigInteger&) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opShl(int) const",                         asMETHODPR(BigInteger, operator<<, (int) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger opShr(int) const",                         asMETHODPR(BigInteger, operator>>, (int) const, BigInteger), asCALL_THISCALL); jassert( r >= 0 );
	
	// methods
	r = engine->RegisterObjectMethod("BigInteger", "void swapWith(BigInteger& inout)",                    asMETHOD(BigInteger, swapWith), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "bool isZero() const",                                 asMETHOD(BigInteger, isZero), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "bool isOne() const",                                  asMETHOD(BigInteger, isOne), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "int toInteger() const",                               asMETHOD(BigInteger, toInteger), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void clear()",                                        asMETHOD(BigInteger, clear), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void clearBit(int)",                                  asMETHOD(BigInteger, clearBit), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void setBit(int)",                                    asMETHODPR(BigInteger, setBit, (int), void), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void setBit(int, bool)",                              asMETHODPR(BigInteger, setBit, (int, bool), void), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void setRange(int, int, bool)",                       asMETHOD(BigInteger, setRange), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void insertBit(int, bool)",                           asMETHOD(BigInteger, insertBit), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger getBitRange(int, int) const",              asMETHOD(BigInteger, getBitRange), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "uint32 getBitRangeAsInt(int, int) const",             asMETHOD(BigInteger, getBitRangeAsInt), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void setBitRangeAsInt(int, int, uint32)",             asMETHOD(BigInteger, setBitRangeAsInt), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void shiftBits(int, int)",                            asMETHOD(BigInteger, shiftBits), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "int countNumberOfSetBits() const",                    asMETHOD(BigInteger, countNumberOfSetBits), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "int findNextSetBit(int) const",                       asMETHOD(BigInteger, findNextSetBit), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "int findNextClearBit(int) const",                     asMETHOD(BigInteger, findNextClearBit), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "int getHighestBit() const",                           asMETHOD(BigInteger, getHighestBit), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "int compare(const BigInteger& in) const",             asMETHOD(BigInteger, compare), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "int compareAbsolute(const BigInteger& in) const",     asMETHOD(BigInteger, compareAbsolute), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "int divideBy(const BigInteger& in, BigInteger& in)",  asMETHOD(BigInteger, divideBy), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "BigInteger findGreatestCommonDivisor(BigInteger) const",          asMETHOD(BigInteger, findGreatestCommonDivisor), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void exponentModulo(const BigInteger& in, const BigInteger& in)", asMETHOD(BigInteger, exponentModulo), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void inverseModulo(const BigInteger& in)",                        asMETHOD(BigInteger, inverseModulo), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "bool isNegative() const",                                         asMETHOD(BigInteger, isNegative), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void setNegative(bool)",                                          asMETHOD(BigInteger, setNegative), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void negate()",                                       asMETHOD(BigInteger, negate), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "String toString(int)",                                asFUNCTION(BigIntegerToString1), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "String toString(int, int)",                           asFUNCTION(BigIntegerToString2), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void parseString(const String& in, int)",             asMETHOD(BigInteger, parseString), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "MemoryBlock toMemoryBlock() const",                   asMETHOD(BigInteger, toMemoryBlock), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("BigInteger", "void loadFromMemoryBlock(const MemoryBlock&)",        asMETHOD(BigInteger, loadFromMemoryBlock), asCALL_THISCALL); jassert(r>=0);
}


//==============================================================================

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

class ScriptableRandomClass : public Random,
                              public ReferenceCountedObject
{
public:
    ScriptableRandomClass()
        : Random()
    {
        incReferenceCount();
    }

    ScriptableRandomClass(const int64 seed)
        : Random(seed)
    {
        incReferenceCount();
    }
};

ScriptableRandomClass* ScriptableRandomFactory()
{
    return new ScriptableRandomClass();
}

ScriptableRandomClass* ScriptableRandomFactoryWithArgs(const int64 seed)
{
    return new ScriptableRandomClass(seed);
}

/*
void RandomConstructor(Random* thisPointer)
{
	new(thisPointer) Random();
}

void RandomConstructorInt64(const int64 seed, Random* thisPointer)
{
	new(thisPointer) Random(seed);
}

void RandomDestructor(Random* thisPointer)
{
	thisPointer->~Random();
}
*/

//------------------------------------------------------------------------------

void ScriptableRandom::registerTypes(asIScriptEngine* engine) const
{
	int r;

	r = engine->RegisterObjectType("Random", 0, asOBJ_REF); jassert(r>=0);
	//r = engine->RegisterObjectType("Random", sizeof(Random), asOBJ_VALUE | asOBJ_APP_CLASS_CD); jassert(r>=0);
}


void ScriptableRandom::registerFunctions(asIScriptEngine* engine) const
{
    int r;

    // factory behaviour
    r = engine->RegisterObjectBehaviour("Random", asBEHAVE_FACTORY, "Random@ f()",           asFUNCTION(ScriptableRandomFactory), asCALL_CDECL); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("Random", asBEHAVE_FACTORY, "Random@ f(int64)",      asFUNCTION(ScriptableRandomFactoryWithArgs), asCALL_CDECL); jassert( r >= 0 );

    // Registering the addref/release behaviours
    r = engine->RegisterObjectBehaviour("Random", asBEHAVE_ADDREF,  "void f()",              asMETHOD(ScriptableRandomClass, incReferenceCount), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("Random", asBEHAVE_RELEASE, "void f()",              asMETHOD(ScriptableRandomClass, decReferenceCount), asCALL_THISCALL); jassert( r >= 0 );

    // constructors / destructors
    /*
	r = engine->RegisterObjectBehaviour("Random", asBEHAVE_CONSTRUCT, "void f()",            asFUNCTION(RandomConstructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Random", asBEHAVE_CONSTRUCT, "void f(const int64)", asFUNCTION(RandomConstructorInt64), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Random", asBEHAVE_DESTRUCT, "void f()",             asFUNCTION(RandomDestructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	*/
	
	// methods
	r = engine->RegisterObjectMethod("Random", "int nextInt()",                              asMETHODPR(ScriptableRandomClass, nextInt, (void), int), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "int nextInt(int)",                           asMETHODPR(ScriptableRandomClass, nextInt, (int), int), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "int64 nextInt64()",                          asMETHODPR(ScriptableRandomClass, nextInt64, (void), int64), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "float nextFloat()",                          asMETHOD(ScriptableRandomClass, nextFloat), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "double nextDouble()",                        asMETHOD(ScriptableRandomClass, nextDouble), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "bool nextBool()",                            asMETHOD(ScriptableRandomClass, nextBool), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "void setSeed(int64)",                        asMETHOD(ScriptableRandomClass, setSeed), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "int64 getSeed()",                            asMETHOD(ScriptableRandomClass, getSeed), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "void combineSeed(int64)",                    asMETHOD(ScriptableRandomClass, combineSeed), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "void setSeedRandomly()",                     asMETHOD(ScriptableRandomClass, setSeedRandomly), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "BigInteger nextLargeNumber(const BigInteger& in)", asMETHOD(ScriptableRandomClass, nextLargeNumber), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "void fillBitsRandomly(BigInteger& in, int, int)",  asMETHODPR(ScriptableRandomClass, fillBitsRandomly, (BigInteger&, int, int), void), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Random", "void fillBitsRandomly(void_ptr, uint)",      asMETHODPR(ScriptableRandomClass, fillBitsRandomly, (void*, size_t), void), asCALL_THISCALL); jassert(r>=0);
	
	r = engine->SetDefaultNamespace("Random"); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("Random& getSystemRandom()",                          asFUNCTION(Random::getSystemRandom), asCALL_CDECL); jassert(r>=0);
	r = engine->SetDefaultNamespace(""); jassert(r >= 0);
}


//==============================================================================

//------------------------------------------------------------------------------

void ScriptableSystemStats::registerTypes(asIScriptEngine* engine) const
{
    int r;
	r = engine->RegisterObjectType("SystemStats_", sizeof(SystemStats), asOBJ_VALUE | asOBJ_APP_CLASS_CD); jassert(r>=0);

	r = engine->RegisterGlobalProperty("SystemStats_ SystemStats", (void*)&dummy32bit); jassert(r>=0);
}

void ScriptableSystemStats::registerFunctions(asIScriptEngine* engine) const
{
    int r;

    // constructors / destructors
	r = engine->RegisterObjectBehaviour("SystemStats_", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DummyConstructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("SystemStats_", asBEHAVE_DESTRUCT, "void f()",  asFUNCTION(DummyDestructor), asCALL_CDECL_OBJLAST); jassert(r>=0);

	// static methods/properties
	r = engine->SetDefaultNamespace("SystemStats"); jassert( r >= 0 );
	r = engine->RegisterEnum ("OperatingSystemType"); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "UnknownOS", SystemStats::UnknownOS); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "Linux", SystemStats::Linux); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "Android", SystemStats::Android); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "iOS", SystemStats::iOS); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "MacOSX_10_4", SystemStats::MacOSX_10_4); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "MacOSX_10_5", SystemStats::MacOSX_10_5); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "MacOSX_10_6", SystemStats::MacOSX_10_6); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "MacOSX_10_7", SystemStats::MacOSX_10_7); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "MacOSX_10_8", SystemStats::MacOSX_10_8); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "Win2000", SystemStats::Win2000); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "WinXP", SystemStats::WinXP); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "WinVista", SystemStats::WinVista); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "Windows7", SystemStats::Windows7); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "Windows8", SystemStats::Windows8); jassert(r>=0);
	r = engine->RegisterEnumValue ("OperatingSystemType", "Windows", SystemStats::Windows); jassert(r>=0);
	r = engine->SetDefaultNamespace(""); jassert(r >= 0);

	// methods
	r = engine->RegisterObjectMethod("SystemStats_", "String getJUCEVersion()",         asFUNCTION(SystemStats::getJUCEVersion), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "SystemStats::OperatingSystemType getOperatingSystemType()", asFUNCTION(SystemStats::getOperatingSystemType), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getOperatingSystemName()", asFUNCTION(SystemStats::getOperatingSystemName), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool isOperatingSystem64Bit()",   asFUNCTION(SystemStats::isOperatingSystem64Bit), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectMethod("SystemStats_", "String getEnvironmentVariable(const String&, const String&)",  asFUNCTION(SystemStats::getEnvironmentVariable), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getLogonName()",           asFUNCTION(SystemStats::getLogonName), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getFullUserName()",        asFUNCTION(SystemStats::getFullUserName), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getComputerName()",        asFUNCTION(SystemStats::getComputerName), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getUserLanguage()",        asFUNCTION(SystemStats::getUserLanguage), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getUserRegion()",          asFUNCTION(SystemStats::getUserRegion), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getDisplayLanguage()",     asFUNCTION(SystemStats::getDisplayLanguage), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "int getNumCpus()",                asFUNCTION(SystemStats::getNumCpus), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "int getCpuSpeedInMegaherz()",     asFUNCTION(SystemStats::getCpuSpeedInMegaherz), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getCpuVendor()",           asFUNCTION(SystemStats::getCpuVendor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool hasMMX()",                   asFUNCTION(SystemStats::hasMMX), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool hasSSE()",                   asFUNCTION(SystemStats::hasSSE), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool hasSSE2()",                  asFUNCTION(SystemStats::hasSSE2), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool hasSSE3()",                  asFUNCTION(SystemStats::hasSSE3), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "bool has3DNow()",                 asFUNCTION(SystemStats::has3DNow), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "int getMemorySizeInMegabytes()",  asFUNCTION(SystemStats::getMemorySizeInMegabytes), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "int getPageSize()",               asFUNCTION(SystemStats::getPageSize), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("SystemStats_", "String getStackBacktrace()",      asFUNCTION(SystemStats::getStackBacktrace), asCALL_CDECL_OBJLAST); jassert(r>=0);
}


//==============================================================================

//------------------------------------------------------------------------------

void ConstructTime(Time* thisPointer)
{
	new(thisPointer) Time();
}

void DestructTime(Time* thisPointer)
{
	thisPointer->~Time();
}

void ConstructTimeByTime(const Time& other, Time* thisPointer)
{
	new(thisPointer) Time(other);
}

void ConstructTimeByInt64(int64 tm, Time* thisPointer)
{
	new(thisPointer) Time(tm);
}

void ConstructTime1(int year, int month, int day, int hours, int minutes, Time* thisPointer)
{
	new(thisPointer) Time(year, month, day, hours, minutes);
}

void ConstructTime2(int year, int month, int day, int hours, int minutes, int seconds, Time* thisPointer)
{
	new(thisPointer) Time(year, month, day, hours, minutes, seconds);
}

void ConstructTime3(int year, int month, int day, int hours, int minutes, int seconds, int milliseconds, Time* thisPointer)
{
	new(thisPointer) Time(year, month, day, hours, minutes, seconds, milliseconds);
}

void ConstructTime4(int year, int month, int day, int hours, int minutes, int seconds, int milliseconds, bool useLocalTime, Time* thisPointer)
{
	new(thisPointer) Time(year, month, day, hours, minutes, seconds, milliseconds, useLocalTime);
}


//------------------------------------------------------------------------------

String TimeToString1(bool a, bool b, const Time& time)
{
    return time.toString(a, b);
}

String TimeToString2(bool a, bool b, bool c, const Time& time)
{
    return time.toString(a, b, c);
}

String TimeToString3(bool a, bool b, bool c, bool d, const Time& time)
{
    return time.toString(a, b, c, d);
}


//------------------------------------------------------------------------------

void ScriptableTime::registerTypes(asIScriptEngine* engine) const
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("Time", sizeof(Time), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); jassert( r >= 0 );
}

void ScriptableTime::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	// constructors
	r = engine->RegisterObjectBehaviour("Time", asBEHAVE_CONSTRUCT, "void f()",                                 asFUNCTION(ConstructTime), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Time", asBEHAVE_CONSTRUCT, "void f(const Time& in)",                   asFUNCTION(ConstructTimeByTime), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Time", asBEHAVE_CONSTRUCT, "void f(int64)",                            asFUNCTION(ConstructTimeByInt64), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Time", asBEHAVE_CONSTRUCT, "void f(int,int,int,int,int)",              asFUNCTION(ConstructTime1), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Time", asBEHAVE_CONSTRUCT, "void f(int,int,int,int,int,int)",          asFUNCTION(ConstructTime2), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Time", asBEHAVE_CONSTRUCT, "void f(int,int,int,int,int,int,int)",      asFUNCTION(ConstructTime3), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Time", asBEHAVE_CONSTRUCT, "void f(int,int,int,int,int,int,int,bool)", asFUNCTION(ConstructTime4), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Time", asBEHAVE_DESTRUCT,  "void f()",                                 asFUNCTION(DestructTime), asCALL_CDECL_OBJLAST); jassert(r>=0);

	// operators
	r = engine->RegisterObjectMethod("Time", "Time& opAssign(const Time& in)",                                  asMETHODPR(Time, operator=, (const Time&), Time&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Time", "Time& opAddAssign(RelativeTime)",                                 asMETHODPR(Time, operator+=, (RelativeTime), Time&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Time", "Time& opSubAssign(RelativeTime)",                                 asMETHODPR(Time, operator-=, (RelativeTime), Time&), asCALL_THISCALL); jassert( r >= 0 );

	// methods
	r = engine->RegisterObjectMethod("Time", "int64 toMilliseconds() const",                                    asMETHOD(Time, toMilliseconds), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getYear() const",                                             asMETHOD(Time, getYear), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getMonth() const",                                            asMETHOD(Time, getMonth), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "String getMonthName(bool) const",                                 asMETHODPR(Time, getMonthName, (bool) const, String), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getDayOfMonth() const",                                       asMETHOD(Time, getDayOfMonth), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getDayOfWeek() const",                                        asMETHOD(Time, getDayOfWeek), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getDayOfYear() const",                                        asMETHOD(Time, getDayOfYear), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "String getWeekdayName(bool) const",                               asMETHODPR(Time, getWeekdayName, (bool) const, String), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getHours() const",                                            asMETHOD(Time, getHours), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "bool isAfternoon() const",                                        asMETHOD(Time, isAfternoon), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getHoursInAmPmFormat() const",                                asMETHOD(Time, getHoursInAmPmFormat), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getMinutes() const",                                          asMETHOD(Time, getMinutes), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getSeconds() const",                                          asMETHOD(Time, getSeconds), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "int getMilliseconds() const",                                     asMETHOD(Time, getMilliseconds), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "bool isDaylightSavingTime() const",                               asMETHOD(Time, isDaylightSavingTime), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "String getTimeZone() const",                                      asMETHOD(Time, getTimeZone), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "String toString(bool, bool) const",                               asFUNCTION(TimeToString1), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "String toString(bool, bool, bool) const",                         asFUNCTION(TimeToString2), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "String toString(bool, bool, bool, bool) const",                   asFUNCTION(TimeToString3), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "String formatted(const String& in) const",                        asMETHOD(Time, formatted), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Time", "bool setSystemTimeToThisTime() const",                            asMETHOD(Time, setSystemTimeToThisTime), asCALL_THISCALL); jassert(r>=0);

	// static methods
	r = engine->SetDefaultNamespace("Time"); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("Time getCurrentTime()",                                          asFUNCTION(Time::getCurrentTime), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("String getWeekdayName(int, bool)",                               asFUNCTIONPR(Time::getWeekdayName, (int, bool), String), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("String getMonthName(int, bool)",                                 asFUNCTIONPR(Time::getMonthName, (int, bool), String), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("int64 currentTimeMillis()",                                      asFUNCTION(Time::currentTimeMillis), asCALL_CDECL); jassert(r>=0);
    r = engine->RegisterGlobalFunction("uint32 getMillisecondCounter()",                                 asFUNCTION(Time::getMillisecondCounter), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("double getMillisecondCounterHiRes()",                            asFUNCTION(Time::getMillisecondCounterHiRes), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("uint32 getApproximateMillisecondCounter()",                      asFUNCTION(Time::getApproximateMillisecondCounter), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("int64 getHighResolutionTicks()",                                 asFUNCTION(Time::getHighResolutionTicks), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("int64 getHighResolutionTicksPerSecond()",                        asFUNCTION(Time::getHighResolutionTicksPerSecond), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("double highResolutionTicksToSeconds(int64)",                     asFUNCTION(Time::highResolutionTicksToSeconds), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("int64 secondsToHighResolutionTicks(double)",                     asFUNCTION(Time::secondsToHighResolutionTicks), asCALL_CDECL); jassert(r>=0);
	r = engine->SetDefaultNamespace(""); jassert(r >= 0);
}


//==============================================================================

//------------------------------------------------------------------------------

void ConstructRelativeTime(RelativeTime* thisPointer)
{
	new(thisPointer) RelativeTime();
}

void DestructRelativeTime(RelativeTime* thisPointer)
{
	thisPointer->~RelativeTime();
}

void ConstructRelativeTimeByRelativeTime(const RelativeTime& other, RelativeTime* thisPointer)
{
	new(thisPointer) RelativeTime(other);
}

void ConstructRelativeTimeByDouble(double seconds, RelativeTime* thisPointer)
{
	new(thisPointer) RelativeTime(seconds);
}


//------------------------------------------------------------------------------

String RelativetimeGetDescription(const RelativeTime& time)
{
    return time.getDescription();
}

String RelativetimeGetDescriptionWithString(const String& str, const RelativeTime& time)
{
    return time.getDescription(str);
}


//------------------------------------------------------------------------------

void ScriptableRelativeTime::registerTypes(asIScriptEngine* engine) const
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("RelativeTime", sizeof(RelativeTime), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); jassert( r >= 0 );
}

void ScriptableRelativeTime::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	// constructors
	r = engine->RegisterObjectBehaviour("RelativeTime", asBEHAVE_CONSTRUCT, "void f()",                       asFUNCTION(ConstructRelativeTime), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("RelativeTime", asBEHAVE_CONSTRUCT, "void f(const RelativeTime& in)", asFUNCTION(ConstructRelativeTimeByRelativeTime), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("RelativeTime", asBEHAVE_CONSTRUCT, "void f(double)",                 asFUNCTION(ConstructRelativeTimeByDouble), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("RelativeTime", asBEHAVE_DESTRUCT,  "void f()",                       asFUNCTION(DestructRelativeTime), asCALL_CDECL_OBJLAST); jassert(r>=0);

	// operators
	r = engine->RegisterObjectMethod("RelativeTime", "RelativeTime& opAssign(const RelativeTime& in)",        asMETHODPR(RelativeTime, operator=, (const RelativeTime&), RelativeTime&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("RelativeTime", "RelativeTime opAddAssign(RelativeTime)",                asMETHODPR(RelativeTime, operator+=, (RelativeTime), RelativeTime), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("RelativeTime", "RelativeTime opSubAssign(RelativeTime)",                asMETHODPR(RelativeTime, operator-=, (RelativeTime), RelativeTime), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("RelativeTime", "RelativeTime opAddAssign(double)",                      asMETHODPR(RelativeTime, operator+=, (double), RelativeTime), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("RelativeTime", "RelativeTime opSubAssign(double)",                      asMETHODPR(RelativeTime, operator-=, (double), RelativeTime), asCALL_THISCALL); jassert( r >= 0 );

	// methods
	r = engine->RegisterObjectMethod("RelativeTime", "int64 inMilliseconds() const",                          asMETHOD(RelativeTime, inMilliseconds), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("RelativeTime", "double inSeconds() const",                              asMETHOD(RelativeTime, inSeconds), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("RelativeTime", "double inMinutes() const",                              asMETHOD(RelativeTime, inMinutes), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("RelativeTime", "double inHours() const",                                asMETHOD(RelativeTime, inHours), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("RelativeTime", "double inDays() const",                                 asMETHOD(RelativeTime, inDays), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("RelativeTime", "double inWeeks() const",                                asMETHOD(RelativeTime, inWeeks), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("RelativeTime", "String getDescription() const",                         asFUNCTION(RelativetimeGetDescription), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("RelativeTime", "String getDescription(const String& in) const",         asFUNCTION(RelativetimeGetDescriptionWithString), asCALL_CDECL_OBJLAST); jassert(r>=0);

	// static methods
	r = engine->SetDefaultNamespace("RelativeTime"); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("RelativeTime milliseconds(int32)",                                    asFUNCTIONPR(RelativeTime::milliseconds, (int), RelativeTime), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("RelativeTime milliseconds(int64)",                                    asFUNCTIONPR(RelativeTime::milliseconds, (int64), RelativeTime), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("RelativeTime seconds(double)",                                        asFUNCTION(RelativeTime::seconds), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("RelativeTime minutes(double)",                                        asFUNCTION(RelativeTime::minutes), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("RelativeTime hours(double)",                                          asFUNCTION(RelativeTime::hours), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("RelativeTime days(double)",                                           asFUNCTION(RelativeTime::days), asCALL_CDECL); jassert(r>=0);
	r = engine->RegisterGlobalFunction("RelativeTime weeks(double)",                                          asFUNCTION(RelativeTime::weeks), asCALL_CDECL); jassert(r>=0);
	r = engine->SetDefaultNamespace(""); jassert(r >= 0);
}


//==============================================================================

//------------------------------------------------------------------------------

void ConstructMemoryBlock(MemoryBlock* thisPointer)
{
	new(thisPointer) MemoryBlock();
}

void DestructMemoryBlock(MemoryBlock* thisPointer)
{
	thisPointer->~MemoryBlock();
}

void ConstructMemoryBlockByMemoryBlock(const MemoryBlock& other, MemoryBlock* thisPointer)
{
	new(thisPointer) MemoryBlock(other);
}

void ConstructMemoryBlockBySize(uint32 size, MemoryBlock* thisPointer)
{
	new(thisPointer) MemoryBlock(size);
}

void ConstructMemoryBlockBySizeZero(uint32 size, bool zero, MemoryBlock* thisPointer)
{
	new(thisPointer) MemoryBlock(size, zero);
}


//------------------------------------------------------------------------------

bool MemoryBlockEquals(const MemoryBlock& lhs, const MemoryBlock& rhs)
{
    return lhs == rhs;
}


//------------------------------------------------------------------------------

void MemoryBlockGetSize1(uint32 size, MemoryBlock& self)
{
    self.setSize(size);
}

void MemoryBlockGetSize2(uint32 size, bool zerofill, MemoryBlock& self)
{
    self.setSize(size, zerofill);
}

void MemoryBlockEnsureSize1(uint32 size, MemoryBlock& self)
{
    self.ensureSize(size);
}

void MemoryBlockEnsureSize2(uint32 size, bool zerofill, MemoryBlock& self)
{
    self.ensureSize(size, zerofill);
}


//------------------------------------------------------------------------------

void ScriptableMemoryBlock::registerTypes(asIScriptEngine* engine) const
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("MemoryBlock", sizeof(MemoryBlock), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); jassert( r >= 0 );
}

void ScriptableMemoryBlock::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	// constructors
	r = engine->RegisterObjectBehaviour("MemoryBlock", asBEHAVE_CONSTRUCT, "void f()",                       asFUNCTION(ConstructMemoryBlock), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("MemoryBlock", asBEHAVE_CONSTRUCT, "void f(uint)",                   asFUNCTION(ConstructMemoryBlockBySize), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("MemoryBlock", asBEHAVE_CONSTRUCT, "void f(uint, bool)",             asFUNCTION(ConstructMemoryBlockBySizeZero), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("MemoryBlock", asBEHAVE_CONSTRUCT, "void f(const MemoryBlock& in)",  asFUNCTION(ConstructMemoryBlockByMemoryBlock), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("MemoryBlock", asBEHAVE_DESTRUCT,  "void f()",                       asFUNCTION(DestructMemoryBlock), asCALL_CDECL_OBJLAST); jassert(r>=0);

	// operators
	r = engine->RegisterObjectMethod("MemoryBlock", "MemoryBlock& opAssign(const MemoryBlock& in)",          asMETHODPR(MemoryBlock, operator=, (const MemoryBlock&), MemoryBlock&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "bool opEquals(const MemoryBlock &in) const",            asFUNCTION(MemoryBlockEquals), asCALL_CDECL_OBJFIRST); jassert( r >= 0 );

	// methods
	r = engine->RegisterObjectMethod("MemoryBlock", "uint getSize() const",                                  asMETHOD(MemoryBlock, getSize), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void setSize(uint)",                                    asFUNCTION(MemoryBlockGetSize1), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void setSize(uint, bool)",                              asFUNCTION(MemoryBlockGetSize2), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void ensureSize(uint)",                                 asFUNCTION(MemoryBlockEnsureSize1), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void ensureSize(uint, bool)",                           asFUNCTION(MemoryBlockEnsureSize2), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void fillWith(uint8)",                                  asMETHOD(MemoryBlock, fillWith), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void removeSection(uint, uint)",                        asMETHOD(MemoryBlock, removeSection), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void swapWith(MemoryBlock& inout)",                     asMETHOD(MemoryBlock, swapWith), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "String toString() const",                               asMETHOD(MemoryBlock, toString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void loadFromHexString(const String& in)",              asMETHOD(MemoryBlock, loadFromHexString), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void setBitRange(uint, uint, int)",                     asMETHOD(MemoryBlock, setBitRange), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "int getBitRange(uint, uint) const",                     asMETHOD(MemoryBlock, getBitRange), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "String toBase64Encoding() const",                       asMETHOD(MemoryBlock, toBase64Encoding), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "bool fromBase64Encoding(const String& in)",             asMETHOD(MemoryBlock, fromBase64Encoding), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void_ptr getData() const",                              asMETHOD(MemoryBlock, getData), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "bool matches(const void_ptr, uint) const",              asMETHOD(MemoryBlock, matches), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void append(const void_ptr, uint)",                     asMETHOD(MemoryBlock, append), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void replaceWith(const void_ptr, uint)",                asMETHOD(MemoryBlock, replaceWith), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void insert(const void_ptr, uint, uint)",               asMETHOD(MemoryBlock, insert), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void copyFrom(const void_ptr, int, uint)",              asMETHOD(MemoryBlock, copyFrom), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MemoryBlock", "void copyTo(const void_ptr, int, uint) const",          asMETHOD(MemoryBlock, copyTo), asCALL_THISCALL); jassert( r >= 0 );

	/*
    template<typename Type > char & 	operator[] (const Type offset) const noexcept
    */
}


//==============================================================================

//------------------------------------------------------------------------------

class ScriptableArray : public Array<void*>,
                        public ReferenceCountedObject
{
public:

    ScriptableArray(asIObjectType* ot, int32 length)
    {
        incReferenceCount();

        objType = ot;
	    objType->AddRef();
	
        subTypeId = objType->GetSubTypeId();
        
        if (subTypeId & asTYPEID_MASK_OBJECT)
		    elementSize = sizeof(asPWORD);
	    else
		    elementSize = objType->GetEngine()->GetSizeOfPrimitiveType(subTypeId);

		if (length > 0)
            resize(length); // or is ensureStorageAllocated ?
    }

    ~ScriptableArray()
    {
        decReferenceCount();
    }
    
    const void* at(int32 index) const
    {
        /*
	    if (buffer == 0 || index >= buffer->numElements )
	    {
		    // If this is called from a script we raise a script exception
		    asIScriptContext *ctx = asGetActiveContext();
		    if( ctx )
			    ctx->SetException("Index out of bounds");
		    return 0;
	    }

		*/
	
        if ((subTypeId & asTYPEID_MASK_OBJECT) && ! (subTypeId & asTYPEID_OBJHANDLE))
        {
            void** data = begin();

            void* element = (void*)(data + index);
            
            //printf("Accessing object %d, %s\n", index, data[index]->GetName());
            
            return element;
        }
	    else
        {
            void** data = begin();

            void* element = (void*)(data + elementSize * index);
            
            //printf("Accessing primitive or handle %d, %s\n", index, data[elementSize*index]->GetName());

            return element;
        }
    }
    
    void* at(int32 index)
    {
	    return const_cast<void*>(const_cast<const ScriptableArray*>(this)->at(index));
    }

protected:
    asIObjectType*    objType;
	int               elementSize;
	int               subTypeId;    
};


//------------------------------------------------------------------------------

ScriptableArray* ScriptArrayFactory2(asIObjectType* ot, int32 length)
{
	ScriptableArray* a = new ScriptableArray(ot, length);

	// It's possible the constructor raised a script exception, in which case we 
	// need to free the memory and return null instead, else we get a memory leak.
	asIScriptContext *ctx = asGetActiveContext();
	if (ctx && ctx->GetState() == asEXECUTION_EXCEPTION)
	{
		a->decReferenceCount();
		return 0;
	}

	return a;
}

ScriptableArray* ScriptArrayFactory1(asIObjectType* ot)
{
	return ScriptArrayFactory2(ot, 0);
}


//------------------------------------------------------------------------------

void ScriptableArrayTemplate::registerTypes(asIScriptEngine* engine) const
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("Array<class T>", 0, asOBJ_REF | /*asOBJ_GC |*/ asOBJ_TEMPLATE); jassert( r >= 0 );
}

void ScriptableArrayTemplate::registerFunctions(asIScriptEngine* engine) const
{
	int r;

	//r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_TEMPLATE_CALLBACK, "bool f(int& in, bool& out)", asFUNCTION(ScriptArrayTemplateCallback), asCALL_CDECL); assert( r >= 0 );
	
	//r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f()",                asFUNCTION(ScriptArrayFactory), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f(int& in)",           asFUNCTION(ScriptArrayFactory1), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f(int& in, int)",      asFUNCTION(ScriptArrayFactory2), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_LIST_FACTORY, "Array<T>@ f(int& in, int)", asFUNCTION(ScriptArrayFactory2), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_ADDREF, "void f()",                        asMETHOD(ScriptableArray, incReferenceCount), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_RELEASE, "void f()",                       asMETHOD(ScriptableArray, decReferenceCount), asCALL_THISCALL); jassert( r >= 0 );
	
	//r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_GETREFCOUNT, "int f()",                   asMETHOD(ScriptableArray, getReferenceCount), asCALL_THISCALL); jassert( r >= 0 );
	//r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_SETGCFLAG, "void f()", asMETHOD(CScriptArray, SetFlag), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_GETGCFLAG, "bool f()", asMETHOD(CScriptArray, GetFlag), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_ENUMREFS, "void f(int&in)", asMETHOD(CScriptArray, EnumReferences), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_RELEASEREFS, "void f(int&in)", asMETHOD(CScriptArray, ReleaseAllHandles), asCALL_THISCALL); assert( r >= 0 );

	// The index operator returns the template subtype
	r = engine->RegisterObjectMethod("Array<T>", "T& opIndex(int)",                                     asMETHODPR(ScriptableArray, at, (int32), void*), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Array<T>", "const T& opIndex(int) const",                         asMETHODPR(ScriptableArray, at, (int32) const, const void*), asCALL_THISCALL); jassert( r >= 0 );
}


} // end namespace

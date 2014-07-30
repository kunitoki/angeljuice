/*
 AngelCode Scripting Library
 Copyright (c) 2003-2012 Andreas Jonsson
 
 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any
 damages arising from the use of this software.
 
 Permission is granted to anyone to use this software for any
 purpose, including commercial applications, and to alter it and
 redistribute it freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you
 must not claim that you wrote the original software. If you use
 this software in a product, an acknowledgment in the product
 documentation would be appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and
 must not be misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source
 distribution.
 
 The original version of this library can be located at:
 http://www.angelcode.com/angelscript/
 
 Andreas Jonsson
 andreas@angelcode.com
*/

#include "sdk/angelscript/source/as_atomic.cpp"
#include "sdk/angelscript/source/as_builder.cpp"
#include "sdk/angelscript/source/as_bytecode.cpp"
#include "sdk/angelscript/source/as_callfunc_arm.cpp"
#include "sdk/angelscript/source/as_callfunc_mips.cpp"
#include "sdk/angelscript/source/as_callfunc_ppc_64.cpp"
#include "sdk/angelscript/source/as_callfunc_ppc.cpp"
#include "sdk/angelscript/source/as_callfunc_sh4.cpp"
#include "sdk/angelscript/source/as_callfunc_x64_gcc.cpp"
#include "sdk/angelscript/source/as_callfunc_x64_mingw.cpp"
#include "sdk/angelscript/source/as_callfunc_x64_msvc.cpp"
#include "sdk/angelscript/source/as_callfunc_x86.cpp"
#include "sdk/angelscript/source/as_callfunc_xenon.cpp"
#include "sdk/angelscript/source/as_callfunc.cpp"
#include "sdk/angelscript/source/as_compiler.cpp"
#include "sdk/angelscript/source/as_configgroup.cpp"
#include "sdk/angelscript/source/as_context.cpp"
#include "sdk/angelscript/source/as_datatype.cpp"
#include "sdk/angelscript/source/as_gc.cpp"
#include "sdk/angelscript/source/as_generic.cpp"
#include "sdk/angelscript/source/as_globalproperty.cpp"
#include "sdk/angelscript/source/as_memory.cpp"
#include "sdk/angelscript/source/as_module.cpp"
#include "sdk/angelscript/source/as_objecttype.cpp"
#include "sdk/angelscript/source/as_outputbuffer.cpp"
#include "sdk/angelscript/source/as_parser.cpp"
#include "sdk/angelscript/source/as_restore.cpp"
#include "sdk/angelscript/source/as_scriptcode.cpp"
#include "sdk/angelscript/source/as_scriptengine.cpp"
#include "sdk/angelscript/source/as_scriptfunction.cpp"
#include "sdk/angelscript/source/as_scriptnode.cpp"
#include "sdk/angelscript/source/as_scriptobject.cpp"
#include "sdk/angelscript/source/as_string_util.cpp"
#include "sdk/angelscript/source/as_string.cpp"
#include "sdk/angelscript/source/as_thread.cpp"
#include "sdk/angelscript/source/as_tokenizer.cpp"
#include "sdk/angelscript/source/as_typeinfo.cpp"
#include "sdk/angelscript/source/as_variablescope.cpp"

/*
#pragma clang diagnostic ignored "-Wall"
#include "sdk/add_on/contextmgr/contextmgr.cpp"
#include "sdk/add_on/debugger/debugger.cpp"
#include "sdk/add_on/scriptany/scriptany.cpp"
//#include "sdk/add_on/scriptarray/scriptarray.cpp"
#include "sdk/add_on/scriptbuilder/scriptbuilder.cpp"
//#include "sdk/add_on/scriptdictionary/scriptdictionary.cpp"
#include "sdk/add_on/scriptfile/scriptfile.cpp"
#include "sdk/add_on/scripthandle/scripthandle.cpp"
//#include "sdk/add_on/scripthelper/scripthelper.cpp"
#include "sdk/add_on/scriptmath/scriptmath.cpp"
#include "sdk/add_on/scriptmath/scriptmathcomplex.cpp"
//#include "sdk/add_on/scriptstdstring/scriptstdstring_utils.cpp"
//#include "sdk/add_on/scriptstdstring/scriptstdstring.cpp"
#include "sdk/add_on/serializer/serializer.cpp"
#include "sdk/add_on/weakref/weakref.cpp"
#pragma clang diagnostic pop
*/

//#include "jit/as_jit.cpp"
//#ifdef _MSC_VER
// #include "jit/virtual_asm_windows.cpp"
//#else
// #include "jit/virtual_asm_linux.cpp"
//#endif
//
//#if defined(__LP64__) || defined(__amd64__) || defined(__x86_64__) || defined(_M_X64)
// #include "jit/virtual_asm_x64.cpp"
//#else
// #include "jit/virtual_asm_x86.cpp"
//#endif

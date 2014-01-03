/*
** $Id: lua.h,v 1.285 2013/03/15 13:04:22 roberto Exp $
** Lua - A Scripting Language
** Lua.org, PUC-Rio, Brazil (http://www.lua.org)
** See Copyright Notice at the end of this file
*/

#ifdef __cplusplus
extern "C"
{
#endif

/* luaconf.h only declares some things if it is being included
   from certain source files. We define all the relevant macros
   and include luaconf.h once so we get all the declarations.
*/
#define LUA_CORE
#define loslib_c
#include "sdk/src/luaconf.h"
#undef LUA_CORE
#undef loslib_c

#if _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4244) /* Possible loss of data */
#pragma warning (disable: 4702) /* Unreachable code */
#endif

/* Include this early to prevent the conflict with luai_hashnum
   and supress the warning caused by #define lua_assert
*/
#include "sdk/src/lapi.c"
#include "sdk/src/lauxlib.c"
#include "sdk/src/lbaselib.c"
#include "sdk/src/lcode.c"
#include "sdk/src/ldblib.c"
#include "sdk/src/ldebug.c"
#include "sdk/src/ldo.c"
#include "sdk/src/ldump.c"
#include "sdk/src/lfunc.c"
#include "sdk/src/lgc.c"
#include "sdk/src/linit.c"
#include "sdk/src/liolib.c"
#include "sdk/src/llex.c"
#include "sdk/src/lmathlib.c"
#include "sdk/src/lmem.c"
#include "sdk/src/lobject.c"
#include "sdk/src/lopcodes.c"
#include "sdk/src/loslib.c"
#include "sdk/src/lparser.c"
#include "sdk/src/lstate.c"
#include "sdk/src/lstring.c"
#include "sdk/src/lstrlib.c"
#include "sdk/src/ltable.c"
#include "sdk/src/ltablib.c"
#include "sdk/src/ltm.c"
#include "sdk/src/lundump.c"
#include "sdk/src/lvm.c"
#include "sdk/src/lzio.c"
//#include "sdk/src/print.c"

/* loadlib.c includes Windows.h, which defines the LoadString macro,
   so include it last to prevent errors.
*/
#include "sdk/src/loadlib.c"

#if _MSC_VER
#pragma warning (pop)
#endif

#ifdef __cplusplus
}
#endif

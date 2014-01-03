# Microsoft Developer Studio Project File - Name="angeljuice" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=angeljuice - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "angeljuice.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "angeljuice.mak" CFG="angeljuice - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "angeljuice - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "angeljuice - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "angeljuice - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GR /GX /O2 /I "../../../juce" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"../../angeljuice.exe" /libpath:"../../../juce/bin"

!ELSEIF  "$(CFG)" == "angeljuice - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../../angeljuice.exe" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "angeljuice - Win32 Release"
# Name "angeljuice - Win32 Debug"
# Begin Group "document"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\document\AngelJuice_OpenDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\document\AngelJuice_OpenDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\src\document\AngelJuice_ProjectTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\document\AngelJuice_ProjectTree.h
# End Source File
# Begin Source File

SOURCE=..\..\src\document\AngelJuice_TabbedEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\document\AngelJuice_TabbedEditor.h
# End Source File
# End Group
# Begin Group "editor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\editor\AngelJuice_SyntaxDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\editor\AngelJuice_SyntaxDocument.h
# End Source File
# Begin Source File

SOURCE=..\..\src\editor\AngelJuice_SyntaxLexer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\editor\AngelJuice_SyntaxLexer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\editor\AngelJuice_SyntaxLexerAS.h
# End Source File
# Begin Source File

SOURCE=..\..\src\editor\AngelJuice_SyntaxLexerCPP.h
# End Source File
# Begin Source File

SOURCE=..\..\src\editor\AngelJuice_SyntaxTextEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\editor\AngelJuice_SyntaxTextEditor.h
# End Source File
# End Group
# Begin Group "libraries"

# PROP Default_Filter ""
# Begin Group "pcre"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\libraries\pcre\config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_chartables.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_compile.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_config.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_dfa_exec.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_exec.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_fullinfo.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_get.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_globals.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_info.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_maketables.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_ord2utf8.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_refcount.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_study.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_tables.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_try_flipped.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_ucp_findchar.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_valid_utf8.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_version.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcre_xclass.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcreposix.c
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\pcreposix.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\ucp.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\ucpinternal.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\pcre\ucptable.c
# End Source File
# End Group
# Begin Group "angelscript"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\angelscript.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_anyobject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_anyobject.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_array.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_arrayobject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_arrayobject.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_builder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_builder.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_bytecode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_bytecode.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_bytecodedef.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_c.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_callfunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_callfunc.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_callfunc_mips.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_callfunc_ppc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_callfunc_sh4.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_callfunc_x86.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_compiler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_compiler.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_configgroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_configgroup.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_context.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_context.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_datatype.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_datatype.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_debug.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_gcobject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_gcobject.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_generic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_generic.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_map.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_module.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_module.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_objecttype.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_objecttype.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_outputbuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_outputbuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_parser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_parser.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_property.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_restore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_restore.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptcode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptcode.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptengine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptengine.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptfunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptfunction.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptnode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptnode.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptstruct.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_scriptstruct.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_string.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_string.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_string_util.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_string_util.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_texts.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_thread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_thread.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_tokendef.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_tokenizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_tokenizer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_typeinfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_typeinfo.h
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_variablescope.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\libraries\angelscript\as_variablescope.h
# End Source File
# End Group
# End Group
# Begin Group "options"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_AboutPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_AboutPage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_ColourEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_CompilerPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_CompilerPage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_FontsPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_FontsPage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_OptionWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\options\AngelJuice_OptionWindow.h
# End Source File
# End Group
# Begin Group "resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\angeljuice.rc
# End Source File
# Begin Source File

SOURCE=..\..\src\resources\AngelJuice_Resource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\resources\AngelJuice_Resource.h
# End Source File
# End Group
# Begin Group "scripting"

# PROP Default_Filter ""
# Begin Group "bindings"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptComponent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptCore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptCore.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptFile.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptImaging.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptImaging.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptOpenGL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptOpenGL.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\bindings\AngelJuice_AngelScriptString.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\AngelJuice_ScriptableEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\AngelJuice_ScriptableEngine.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\AngelJuice_ScriptableEngineModel.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\AngelJuice_ScriptablePlugin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\AngelJuice_ScriptablePlugin.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\AngelJuice_ScriptablePreprocessor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scripting\AngelJuice_ScriptablePreprocessor.h
# End Source File
# End Group
# Begin Group "support"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_CallstackOutput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_CallstackOutput.h
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_DebugOutput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_DebugOutput.h
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_ErrorOutput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_ErrorOutput.h
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_SearchComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_SearchComponent.h
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_StatusBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_StatusBar.h
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_TabbedSupport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_TabbedSupport.h
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_Toolbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\support\AngelJuice_Toolbar.h
# End Source File
# End Group
# Begin Group "utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_AngelicLookAndFeel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_AngelicLookAndFeel.h
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_CommandLineTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_CommandLineTokenizer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_DynamicLibraryLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_DynamicLibraryLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_InternetUpdateChecker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_InternetUpdateChecker.h
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_RegularExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\AngelJuice_RegularExpression.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\AngelJuice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\AngelJuice.h
# End Source File
# Begin Source File

SOURCE=..\..\src\AngelJuice_command.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\AngelJuice_command.h
# End Source File
# Begin Source File

SOURCE=..\..\src\AngelJuice_config.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\AngelJuice_config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\AngelJuice_main.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\AngelJuice_window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\AngelJuice_window.h
# End Source File
# End Target
# End Project

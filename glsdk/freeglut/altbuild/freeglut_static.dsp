# Microsoft Developer Studio Project File - Name="freeglut_static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=freeglut_static - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "freeglut_static.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "freeglut_static.mak" CFG="freeglut_static - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "freeglut_static - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "freeglut_static - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "freeglut_static - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release_static"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release_static"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".." /I "../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "FREEGLUT_STATIC" /D "HAVE_CONFIG_H" /D _WIN32_WINNT=0x0500 /D WINVER=0x0500 /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "freeglut_static - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug_static"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug_static"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "FREEGLUT_STATIC" /D "HAVE_CONFIG_H" /D _WIN32_WINNT=0x0500 /D WINVER=0x0500 /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\freeglut_staticd.lib"

!ENDIF 

# Begin Target

# Name "freeglut_static - Win32 Release"
# Name "freeglut_static - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\config.h
# End Source File
# Begin Source File

SOURCE=..\src\fg_callback_macros.h
# End Source File
# Begin Source File

SOURCE=..\src\fg_callbacks.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_cmap_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_cursor.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_cursor_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_display.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_display_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_ext.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_ext_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_font.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_font_data.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_gamemode.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_gamemode_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_geometry.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_gl2.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_gl2.h
# End Source File
# Begin Source File

SOURCE=..\src\fg_init.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_init.h
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_init_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_input_devices.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_input_devices_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_internal_mswin.h
# End Source File
# Begin Source File

SOURCE=..\src\fg_joystick.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_joystick_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_main.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_main_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_menu.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_menu_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_misc.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_overlay.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_spaceball.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_spaceball_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_state.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_state_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_stroke_mono_roman.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_stroke_roman.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_structure.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_structure_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_teapot.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_teapot_data.h
# End Source File
# Begin Source File

SOURCE=..\src\fg_version.h
# End Source File
# Begin Source File

SOURCE=..\src\fg_videoresize.c
# End Source File
# Begin Source File

SOURCE=..\src\fg_window.c
# End Source File
# Begin Source File

SOURCE=..\src\mswin\fg_window_mswin.c
# End Source File
# Begin Source File

SOURCE=..\src\util\xparsegeometry_repl.c
# End Source File
# Begin Source File

SOURCE=..\src\util\xparsegeometry_repl.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\Gl\freeglut.h
# End Source File
# Begin Source File

SOURCE=..\include\Gl\freeglut_ext.h
# End Source File
# Begin Source File

SOURCE=..\include\Gl\freeglut_std.h
# End Source File
# Begin Source File

SOURCE=..\include\Gl\freeglut_ucall.h
# End Source File
# Begin Source File

SOURCE=..\include\Gl\glut.h
# End Source File
# End Group
# End Target
# End Project

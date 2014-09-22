# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=lpfltr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to lpfltr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "lpfltr - Win32 Release" && "$(CFG)" != "lpfltr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "lpfltr.mak" CFG="lpfltr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lpfltr - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "lpfltr - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "lpfltr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "lpfltr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
ProjDir=.
# End Custom Macros

ALL : "$(OUTDIR)\lpfltr.exe" "..\..\bindosr\lpfltr.exe"

CLEAN : 
	-@erase "..\..\bindosr\lpfltr.exe"
	-@erase ".\Release\lpfltr.exe"
	-@erase ".\Release\smooth.obj"
	-@erase ".\Release\convolve1.obj"
	-@erase ".\Release\lpfltr.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\libimage" /I " ..\..\libtiff\libtiff" /I " ..\..\libip" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\libimage" /I\
 " ..\..\libtiff\libtiff" /I " ..\..\libip" /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/lpfltr.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lpfltr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\libimage\Release\libimage.lib ..\..\libtiff\libtiff\Release\libtiff.lib ..\..\libip\Release\libip.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\libimage\Release\libimage.lib\
 ..\..\libtiff\libtiff\Release\libtiff.lib ..\..\libip\Release\libip.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/lpfltr.pdb" /machine:I386\
 /out:"$(OUTDIR)/lpfltr.exe" 
LINK32_OBJS= \
	".\Release\smooth.obj" \
	".\Release\convolve1.obj" \
	".\Release\lpfltr.obj"

"$(OUTDIR)\lpfltr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
ProjDir=.
InputPath=.\Release\lpfltr.exe
InputName=lpfltr
SOURCE=$(InputPath)

"$(ProjDir)\..\..\bindosr\$(InputName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(InputPath) $(ProjDir)\..\..\bindosr

# End Custom Build

!ELSEIF  "$(CFG)" == "lpfltr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
ProjDir=.
# End Custom Macros

ALL : "$(OUTDIR)\lpfltr.exe" "..\..\bindosd\lpfltr.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\lpfltr.ilk"
	-@erase ".\Debug\lpfltr.obj"
	-@erase ".\Debug\smooth.obj"
	-@erase ".\Debug\convolve1.obj"
	-@erase ".\Debug\lpfltr.pdb"
	-@erase "..\..\bindosd\lpfltr.exe"
	-@erase ".\Debug\lpfltr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\..\libimage" /I " ..\..\libtiff\libtiff" /I " ..\..\libip" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\..\libimage" /I\
 " ..\..\libtiff\libtiff" /I " ..\..\libip" /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/lpfltr.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lpfltr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\libimage\Debug\libimage.lib ..\..\libtiff\libtiff\Debug\libtiff.lib ..\..\libip\Debug\libip.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\libimage\Debug\libimage.lib\
 ..\..\libtiff\libtiff\Debug\libtiff.lib ..\..\libip\Debug\libip.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/lpfltr.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/lpfltr.exe" 
LINK32_OBJS= \
	".\Debug\lpfltr.obj" \
	".\Debug\smooth.obj" \
	".\Debug\convolve1.obj"

"$(OUTDIR)\lpfltr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
ProjDir=.
InputPath=.\Debug\lpfltr.exe
InputName=lpfltr
SOURCE=$(InputPath)

"$(ProjDir)\..\..\bindosd\$(InputName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(InputPath) $(ProjDir)\..\..\bindosd

# End Custom Build

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "lpfltr - Win32 Release"
# Name "lpfltr - Win32 Debug"

!IF  "$(CFG)" == "lpfltr - Win32 Release"

!ELSEIF  "$(CFG)" == "lpfltr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\lpfltr.c
DEP_CPP_LPFLT=\
	".\..\..\libimage\images.h"\
	".\..\..\libimage\tiffimage.h"\
	

"$(INTDIR)\lpfltr.obj" : $(SOURCE) $(DEP_CPP_LPFLT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\convolve1.c
DEP_CPP_CONVO=\
	".\..\..\libimage\images.h"\
	".\..\..\libimage\tiffimage.h"\
	

"$(INTDIR)\convolve1.obj" : $(SOURCE) $(DEP_CPP_CONVO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\smooth.c
DEP_CPP_SMOOT=\
	".\..\..\libimage\images.h"\
	".\..\..\libimage\tiffimage.h"\
	

"$(INTDIR)\smooth.obj" : $(SOURCE) $(DEP_CPP_SMOOT) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################

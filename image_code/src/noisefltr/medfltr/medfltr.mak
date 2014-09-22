# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=medfltr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to medfltr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "medfltr - Win32 Release" && "$(CFG)" !=\
 "medfltr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "medfltr.mak" CFG="medfltr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "medfltr - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "medfltr - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "medfltr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "medfltr - Win32 Release"

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

ALL : "$(OUTDIR)\medfltr.exe" "..\..\bindosr\medfltr.exe"

CLEAN : 
	-@erase "..\..\bindosr\medfltr.exe"
	-@erase ".\Release\medfltr.exe"
	-@erase ".\Release\medfltr.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\libimage" /I " ..\..\libtiff\libtiff" /I " ..\..\libip" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\libimage" /I\
 " ..\..\libtiff\libtiff" /I " ..\..\libip" /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/medfltr.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/medfltr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\libimage\Release\libimage.lib ..\..\libtiff\libtiff\Release\libtiff.lib ..\..\libip\Release\libip.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\libimage\Release\libimage.lib\
 ..\..\libtiff\libtiff\Release\libtiff.lib ..\..\libip\Release\libip.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/medfltr.pdb" /machine:I386\
 /out:"$(OUTDIR)/medfltr.exe" 
LINK32_OBJS= \
	".\Release\medfltr.obj"

"$(OUTDIR)\medfltr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
ProjDir=.
InputPath=.\Release\medfltr.exe
InputName=medfltr
SOURCE=$(InputPath)

"$(ProjDir)\..\..\bindosr\$(InputName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(InputPath) $(ProjDir)\..\..\bindosr

# End Custom Build

!ELSEIF  "$(CFG)" == "medfltr - Win32 Debug"

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

ALL : "$(OUTDIR)\medfltr.exe" "..\..\bindosd\medfltr.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\medfltr.ilk"
	-@erase ".\Debug\medfltr.obj"
	-@erase ".\Debug\medfltr.pdb"
	-@erase "..\..\bindosd\medfltr.exe"
	-@erase ".\Debug\medfltr.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\..\libimage" /I " ..\..\libtiff\libtiff" /I " ..\..\libip" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\..\libimage" /I\
 " ..\..\libtiff\libtiff" /I " ..\..\libip" /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/medfltr.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/medfltr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\libimage\Debug\libimage.lib ..\..\libtiff\libtiff\Debug\libtiff.lib ..\..\libip\Debug\libip.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\libimage\Debug\libimage.lib\
 ..\..\libtiff\libtiff\Debug\libtiff.lib ..\..\libip\Debug\libip.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/medfltr.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/medfltr.exe" 
LINK32_OBJS= \
	".\Debug\medfltr.obj"

"$(OUTDIR)\medfltr.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
ProjDir=.
InputPath=.\Debug\medfltr.exe
InputName=medfltr
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

# Name "medfltr - Win32 Release"
# Name "medfltr - Win32 Debug"

!IF  "$(CFG)" == "medfltr - Win32 Release"

!ELSEIF  "$(CFG)" == "medfltr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\medfltr.c
DEP_CPP_MEDFL=\
	".\..\..\libimage\images.h"\
	".\..\..\libimage\tiffimage.h"\
	

"$(INTDIR)\medfltr.obj" : $(SOURCE) $(DEP_CPP_MEDFL) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################

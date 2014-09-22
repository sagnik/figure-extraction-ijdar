# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=bcd - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to bcd - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "bcd - Win32 Release" && "$(CFG)" != "bcd - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "bcd.mak" CFG="bcd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bcd - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "bcd - Win32 Debug" (based on "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "bcd - Win32 Debug"
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "bcd - Win32 Release"

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

ALL : "$(OUTDIR)\bcd.exe" "..\..\bindosr\bcd.exe"

CLEAN : 
	-@erase "..\..\bindosr\bcd.exe"
	-@erase ".\Release\bcd.exe"
	-@erase ".\Release\loc.obj"
	-@erase ".\Release\ctor.obj"
	-@erase ".\Release\filter.obj"
	-@erase ".\Release\edge_map.obj"
	-@erase ".\Release\conv.obj"
	-@erase ".\Release\hyst.obj"
	-@erase ".\Release\write.obj"
	-@erase ".\Release\thin.obj"
	-@erase ".\Release\det.obj"
	-@erase ".\Release\dtor.obj"
	-@erase ".\Release\bcd.obj"
	-@erase ".\Release\find_edg.obj"
	-@erase ".\Release\thld.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "." /I " ..\..\libip" /I " ..\..\libimage" /I " ..\..\libtiff\libtiff" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "." /I " ..\..\libip" /I " ..\..\libimage"\
 /I " ..\..\libtiff\libtiff" /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/bcd.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/bcd.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\libimage\Release\libimage.lib ..\..\libtiff\libtiff\Release\libtiff.lib ..\..\libip\Release\libip.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\libimage\Release\libimage.lib\
 ..\..\libtiff\libtiff\Release\libtiff.lib ..\..\libip\Release\libip.lib /nologo\
 /subsystem:console /incremental:no /pdb:"$(OUTDIR)/bcd.pdb" /machine:I386\
 /out:"$(OUTDIR)/bcd.exe" 
LINK32_OBJS= \
	".\Release\loc.obj" \
	".\Release\ctor.obj" \
	".\Release\filter.obj" \
	".\Release\edge_map.obj" \
	".\Release\conv.obj" \
	".\Release\hyst.obj" \
	".\Release\write.obj" \
	".\Release\thin.obj" \
	".\Release\det.obj" \
	".\Release\dtor.obj" \
	".\Release\bcd.obj" \
	".\Release\find_edg.obj" \
	".\Release\thld.obj"

"$(OUTDIR)\bcd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
ProjDir=.
InputPath=.\Release\bcd.exe
InputName=bcd
SOURCE=$(InputPath)

"$(ProjDir)\..\..\bindosr\$(InputName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(InputPath) $(ProjDir)\..\..\bindosr

# End Custom Build

!ELSEIF  "$(CFG)" == "bcd - Win32 Debug"

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

ALL : "$(OUTDIR)\bcd.exe" "..\..\bindosd\bcd.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\bcd.ilk"
	-@erase ".\Debug\bcd.obj"
	-@erase ".\Debug\hyst.obj"
	-@erase ".\Debug\edge_map.obj"
	-@erase ".\Debug\thin.obj"
	-@erase ".\Debug\dtor.obj"
	-@erase ".\Debug\conv.obj"
	-@erase ".\Debug\filter.obj"
	-@erase ".\Debug\thld.obj"
	-@erase ".\Debug\ctor.obj"
	-@erase ".\Debug\write.obj"
	-@erase ".\Debug\loc.obj"
	-@erase ".\Debug\find_edg.obj"
	-@erase ".\Debug\det.obj"
	-@erase ".\Debug\bcd.pdb"
	-@erase "..\..\bindosd\bcd.exe"
	-@erase ".\Debug\bcd.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "." /I " ..\..\libip" /I " ..\..\libimage" /I " ..\..\libtiff\libtiff" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "." /I " ..\..\libip" /I\
 " ..\..\libimage" /I " ..\..\libtiff\libtiff" /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/bcd.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/bcd.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\libimage\Debug\libimage.lib ..\..\libtiff\libtiff\Debug\libtiff.lib ..\..\libip\Debug\libip.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\libimage\Debug\libimage.lib\
 ..\..\libtiff\libtiff\Debug\libtiff.lib ..\..\libip\Debug\libip.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)/bcd.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/bcd.exe" 
LINK32_OBJS= \
	".\Debug\bcd.obj" \
	".\Debug\hyst.obj" \
	".\Debug\edge_map.obj" \
	".\Debug\thin.obj" \
	".\Debug\dtor.obj" \
	".\Debug\conv.obj" \
	".\Debug\filter.obj" \
	".\Debug\thld.obj" \
	".\Debug\ctor.obj" \
	".\Debug\write.obj" \
	".\Debug\loc.obj" \
	".\Debug\find_edg.obj" \
	".\Debug\det.obj"

"$(OUTDIR)\bcd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
ProjDir=.
InputPath=.\Debug\bcd.exe
InputName=bcd
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

# Name "bcd - Win32 Release"
# Name "bcd - Win32 Debug"

!IF  "$(CFG)" == "bcd - Win32 Release"

!ELSEIF  "$(CFG)" == "bcd - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\bcd.c

!IF  "$(CFG)" == "bcd - Win32 Release"

DEP_CPP_BCD_C=\
	".\edge_finder.h"\
	".\..\..\libip\ip.h"\
	".\..\..\libip\ph.h"\
	".\..\..\libtiff\libtiff\tiffio.h"\
	".\..\..\libimage\draw.h"\
	".\..\..\libip\lldef.h"\
	".\..\..\libip\sgl_stat.h"\
	".\..\..\libip\convolve.h"\
	".\..\..\libip\pcc2.h"\
	".\..\..\libip\bdy_stru.h"\
	".\..\..\libimage\misc.h"\
	".\..\..\libtiff\libtiff\tiff.h"\
	".\..\..\libimage\tiffimage.h"\
	".\..\..\libimage\gd.h"\
	".\..\..\libimage\images.h"\
	

"$(INTDIR)\bcd.obj" : $(SOURCE) $(DEP_CPP_BCD_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "bcd - Win32 Debug"

DEP_CPP_BCD_C=\
	".\edge_finder.h"\
	".\..\..\libip\ip.h"\
	".\..\..\libip\ph.h"\
	".\..\..\libtiff\libtiff\tiffio.h"\
	".\..\..\libimage\draw.h"\
	".\..\..\libip\lldef.h"\
	".\..\..\libip\sgl_stat.h"\
	".\..\..\libip\convolve.h"\
	".\..\..\libip\pcc2.h"\
	".\..\..\libip\bdy_stru.h"\
	".\..\..\libtiff\libtiff\tiff.h"\
	".\..\..\libimage\tiffimage.h"\
	".\..\..\libimage\gd.h"\
	".\..\..\libimage\misc.h"\
	".\..\..\libimage\images.h"\
	

"$(INTDIR)\bcd.obj" : $(SOURCE) $(DEP_CPP_BCD_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\conv.c
DEP_CPP_CONV_=\
	".\edge_finder.h"\
	

"$(INTDIR)\conv.obj" : $(SOURCE) $(DEP_CPP_CONV_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ctor.c
DEP_CPP_CTOR_=\
	".\edge_finder.h"\
	

"$(INTDIR)\ctor.obj" : $(SOURCE) $(DEP_CPP_CTOR_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\det.c
DEP_CPP_DET_C=\
	".\edge_finder.h"\
	

"$(INTDIR)\det.obj" : $(SOURCE) $(DEP_CPP_DET_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dtor.c
DEP_CPP_DTOR_=\
	".\edge_finder.h"\
	

"$(INTDIR)\dtor.obj" : $(SOURCE) $(DEP_CPP_DTOR_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\edge_map.c
DEP_CPP_EDGE_=\
	".\edge_finder.h"\
	

"$(INTDIR)\edge_map.obj" : $(SOURCE) $(DEP_CPP_EDGE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\filter.c
DEP_CPP_FILTE=\
	".\edge_finder.h"\
	

"$(INTDIR)\filter.obj" : $(SOURCE) $(DEP_CPP_FILTE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\find_edg.c
DEP_CPP_FIND_=\
	".\edge_finder.h"\
	

"$(INTDIR)\find_edg.obj" : $(SOURCE) $(DEP_CPP_FIND_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hyst.c
DEP_CPP_HYST_=\
	".\edge_finder.h"\
	

"$(INTDIR)\hyst.obj" : $(SOURCE) $(DEP_CPP_HYST_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\loc.c
DEP_CPP_LOC_C=\
	".\edge_finder.h"\
	

"$(INTDIR)\loc.obj" : $(SOURCE) $(DEP_CPP_LOC_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\thin.c
DEP_CPP_THIN_=\
	".\edge_finder.h"\
	

"$(INTDIR)\thin.obj" : $(SOURCE) $(DEP_CPP_THIN_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\thld.c
DEP_CPP_THLD_=\
	".\edge_finder.h"\
	

"$(INTDIR)\thld.obj" : $(SOURCE) $(DEP_CPP_THLD_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\write.c
DEP_CPP_WRITE=\
	".\edge_finder.h"\
	

"$(INTDIR)\write.obj" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################

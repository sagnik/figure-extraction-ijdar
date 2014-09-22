# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=libimage - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to libimage - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "libimage - Win32 Release" && "$(CFG)" !=\
 "libimage - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "libimage.mak" CFG="libimage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libimage - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libimage - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "libimage - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "libimage - Win32 Release"

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

ALL : "$(OUTDIR)\libimage.lib"

CLEAN : 
	-@erase ".\Release\libimage.lib"
	-@erase ".\Release\gdfontmb.obj"
	-@erase ".\Release\gdfontl.obj"
	-@erase ".\Release\tiffimage.obj"
	-@erase ".\Release\gdfontg.obj"
	-@erase ".\Release\gdfontt.obj"
	-@erase ".\Release\getopt.obj"
	-@erase ".\Release\draw.obj"
	-@erase ".\Release\gdfonts.obj"
	-@erase ".\Release\misc.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\libtiff\libtiff" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\libtiff\libtiff" /D "NDEBUG" /D "WIN32"\
 /D "_WINDOWS" /Fp"$(INTDIR)/libimage.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/libimage.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/libimage.lib" 
LIB32_OBJS= \
	"$(INTDIR)/gdfontmb.obj" \
	"$(INTDIR)/gdfontl.obj" \
	"$(INTDIR)/tiffimage.obj" \
	"$(INTDIR)/gdfontg.obj" \
	"$(INTDIR)/gdfontt.obj" \
	"$(INTDIR)/getopt.obj" \
	"$(INTDIR)/draw.obj" \
	"$(INTDIR)/gdfonts.obj" \
	"$(INTDIR)/misc.obj"

"$(OUTDIR)\libimage.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "libimage - Win32 Debug"

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

ALL : "$(OUTDIR)\libimage.lib"

CLEAN : 
	-@erase ".\Debug\libimage.lib"
	-@erase ".\Debug\tiffimage.obj"
	-@erase ".\Debug\getopt.obj"
	-@erase ".\Debug\draw.obj"
	-@erase ".\Debug\gdfontl.obj"
	-@erase ".\Debug\gdfontg.obj"
	-@erase ".\Debug\misc.obj"
	-@erase ".\Debug\gdfontmb.obj"
	-@erase ".\Debug\gdfontt.obj"
	-@erase ".\Debug\gdfonts.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I "..\libtiff\libtiff" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /I "..\libtiff\libtiff" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /Fp"$(INTDIR)/libimage.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/libimage.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/libimage.lib" 
LIB32_OBJS= \
	"$(INTDIR)/tiffimage.obj" \
	"$(INTDIR)/getopt.obj" \
	"$(INTDIR)/draw.obj" \
	"$(INTDIR)/gdfontl.obj" \
	"$(INTDIR)/gdfontg.obj" \
	"$(INTDIR)/misc.obj" \
	"$(INTDIR)/gdfontmb.obj" \
	"$(INTDIR)/gdfontt.obj" \
	"$(INTDIR)/gdfonts.obj"

"$(OUTDIR)\libimage.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

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

# Name "libimage - Win32 Release"
# Name "libimage - Win32 Debug"

!IF  "$(CFG)" == "libimage - Win32 Release"

!ELSEIF  "$(CFG)" == "libimage - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\tiffimage.c
DEP_CPP_TIFFI=\
	".\..\libtiff\libtiff\tiffio.h"\
	".\tiffimage.h"\
	"..\libtiff\libtiff\tiff.h"\
	

"$(INTDIR)\tiffimage.obj" : $(SOURCE) $(DEP_CPP_TIFFI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\draw.c
DEP_CPP_DRAW_=\
	".\draw.h"\
	".\mtables.c"\
	".\tiffimage.h"\
	".\gd.h"\
	".\misc.h"\
	

"$(INTDIR)\draw.obj" : $(SOURCE) $(DEP_CPP_DRAW_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdfontg.c
DEP_CPP_GDFON=\
	".\gdfontg.h"\
	".\gd.h"\
	

"$(INTDIR)\gdfontg.obj" : $(SOURCE) $(DEP_CPP_GDFON) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdfontl.c
DEP_CPP_GDFONT=\
	".\gdfontl.h"\
	".\gd.h"\
	

"$(INTDIR)\gdfontl.obj" : $(SOURCE) $(DEP_CPP_GDFONT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdfontmb.c
DEP_CPP_GDFONTM=\
	".\gdfontmb.h"\
	".\gd.h"\
	

"$(INTDIR)\gdfontmb.obj" : $(SOURCE) $(DEP_CPP_GDFONTM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdfonts.c
DEP_CPP_GDFONTS=\
	".\gdfonts.h"\
	".\gd.h"\
	

"$(INTDIR)\gdfonts.obj" : $(SOURCE) $(DEP_CPP_GDFONTS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdfontt.c
DEP_CPP_GDFONTT=\
	".\gdfontt.h"\
	".\gd.h"\
	

"$(INTDIR)\gdfontt.obj" : $(SOURCE) $(DEP_CPP_GDFONTT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\misc.c
DEP_CPP_MISC_=\
	".\misc.h"\
	

"$(INTDIR)\misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\getopt.c
DEP_CPP_GETOP=\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	".\getopt.h"\
	

"$(INTDIR)\getopt.obj" : $(SOURCE) $(DEP_CPP_GETOP) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################

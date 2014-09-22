# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103
# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=mkg3states - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to mkg3states - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "libtiff - Win32 Release" && "$(CFG)" !=\
 "libtiff - Win32 Debug" && "$(CFG)" != "mkg3states - Win32 Release" && "$(CFG)"\
 != "mkg3states - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "libtiff.mak" CFG="mkg3states - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libtiff - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libtiff - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mkg3states - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "mkg3states - Win32 Debug" (based on\
 "Win32 (x86) Console Application")
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
# PROP Target_Last_Scanned "mkg3states - Win32 Debug"

!IF  "$(CFG)" == "libtiff - Win32 Release"

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

ALL : "mkg3states - Win32 Release" "$(OUTDIR)\libtiff.lib"

CLEAN : 
	-@erase ".\Release\libtiff.lib"
	-@erase ".\Release\tif_strip.obj"
	-@erase ".\Release\tif_predict.obj"
	-@erase ".\Release\tif_aux.obj"
	-@erase ".\Release\tif_win32.obj"
	-@erase ".\Release\tif_dirread.obj"
	-@erase ".\Release\tif_error.obj"
	-@erase ".\Release\tif_fax3.obj"
	-@erase ".\Release\tif_codec.obj"
	-@erase ".\Release\tif_dumpmode.obj"
	-@erase ".\Release\tif_compress.obj"
	-@erase ".\Release\tif_swab.obj"
	-@erase ".\Release\tif_close.obj"
	-@erase ".\Release\tif_getimage.obj"
	-@erase ".\Release\tif_dirinfo.obj"
	-@erase ".\Release\tif_packbits.obj"
	-@erase ".\Release\tif_dir.obj"
	-@erase ".\Release\tif_jpeg.obj"
	-@erase ".\Release\tif_read.obj"
	-@erase ".\Release\tif_dirwrite.obj"
	-@erase ".\Release\tif_print.obj"
	-@erase ".\Release\tif_open.obj"
	-@erase ".\Release\tif_tile.obj"
	-@erase ".\Release\tif_version.obj"
	-@erase ".\Release\tif_next.obj"
	-@erase ".\Release\tif_warning.obj"
	-@erase ".\Release\tif_flush.obj"
	-@erase ".\Release\tif_write.obj"
	-@erase ".\Release\tif_thunder.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W2 /GX /Zd /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__WIN32__" /YX /Oxa /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W2 /GX /Zd /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__WIN32__" /Fp"$(INTDIR)/libtiff.pch" /YX /Fo"$(INTDIR)/" /Oxa /c 
CPP_OBJS=.\Release/
CPP_SBRS=

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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/libtiff.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/libtiff.lib" 
LIB32_OBJS= \
	".\Release\tif_strip.obj" \
	".\Release\tif_predict.obj" \
	".\Release\tif_aux.obj" \
	".\Release\tif_win32.obj" \
	".\Release\tif_dirread.obj" \
	".\Release\tif_error.obj" \
	".\Release\tif_fax3.obj" \
	".\Release\tif_codec.obj" \
	".\Release\tif_dumpmode.obj" \
	".\Release\tif_compress.obj" \
	".\Release\tif_swab.obj" \
	".\Release\tif_close.obj" \
	".\Release\tif_getimage.obj" \
	".\Release\tif_dirinfo.obj" \
	".\Release\tif_packbits.obj" \
	".\Release\tif_dir.obj" \
	".\Release\tif_jpeg.obj" \
	".\Release\tif_read.obj" \
	".\Release\tif_dirwrite.obj" \
	".\Release\tif_print.obj" \
	".\Release\tif_open.obj" \
	".\Release\tif_tile.obj" \
	".\Release\tif_version.obj" \
	".\Release\tif_next.obj" \
	".\Release\tif_warning.obj" \
	".\Release\tif_flush.obj" \
	".\Release\tif_write.obj" \
	".\Release\tif_thunder.obj"

"$(OUTDIR)\libtiff.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "libtiff - Win32 Debug"

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

ALL : "mkg3states - Win32 Debug" "$(OUTDIR)\libtiff.lib"

CLEAN : 
	-@erase ".\Debug\libtiff.lib"
	-@erase ".\Debug\tif_tile.obj"
	-@erase ".\Debug\tif_codec.obj"
	-@erase ".\Debug\tif_dirinfo.obj"
	-@erase ".\Debug\tif_aux.obj"
	-@erase ".\Debug\tif_dirread.obj"
	-@erase ".\Debug\tif_jpeg.obj"
	-@erase ".\Debug\tif_dumpmode.obj"
	-@erase ".\Debug\tif_close.obj"
	-@erase ".\Debug\tif_strip.obj"
	-@erase ".\Debug\tif_getimage.obj"
	-@erase ".\Debug\tif_version.obj"
	-@erase ".\Debug\tif_open.obj"
	-@erase ".\Debug\tif_warning.obj"
	-@erase ".\Debug\tif_dirwrite.obj"
	-@erase ".\Debug\tif_thunder.obj"
	-@erase ".\Debug\tif_print.obj"
	-@erase ".\Debug\tif_next.obj"
	-@erase ".\Debug\tif_dir.obj"
	-@erase ".\Debug\tif_swab.obj"
	-@erase ".\Debug\tif_predict.obj"
	-@erase ".\Debug\tif_compress.obj"
	-@erase ".\Debug\tif_flush.obj"
	-@erase ".\Debug\tif_write.obj"
	-@erase ".\Debug\tif_read.obj"
	-@erase ".\Debug\tif_packbits.obj"
	-@erase ".\Debug\tif_win32.obj"
	-@erase ".\Debug\tif_fax3.obj"
	-@erase ".\Debug\tif_error.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W2 /GX /Zd /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__WIN32__" /YX /Oxa /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W2 /GX /Zd /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "__WIN32__" /Fp"$(INTDIR)/libtiff.pch" /YX /Fo"$(INTDIR)/" /Oxa /c 
CPP_OBJS=.\Debug/
CPP_SBRS=

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

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/libtiff.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/libtiff.lib" 
LIB32_OBJS= \
	".\Debug\tif_tile.obj" \
	".\Debug\tif_codec.obj" \
	".\Debug\tif_dirinfo.obj" \
	".\Debug\tif_aux.obj" \
	".\Debug\tif_dirread.obj" \
	".\Debug\tif_jpeg.obj" \
	".\Debug\tif_dumpmode.obj" \
	".\Debug\tif_close.obj" \
	".\Debug\tif_strip.obj" \
	".\Debug\tif_getimage.obj" \
	".\Debug\tif_version.obj" \
	".\Debug\tif_open.obj" \
	".\Debug\tif_warning.obj" \
	".\Debug\tif_dirwrite.obj" \
	".\Debug\tif_thunder.obj" \
	".\Debug\tif_print.obj" \
	".\Debug\tif_next.obj" \
	".\Debug\tif_dir.obj" \
	".\Debug\tif_swab.obj" \
	".\Debug\tif_predict.obj" \
	".\Debug\tif_compress.obj" \
	".\Debug\tif_flush.obj" \
	".\Debug\tif_write.obj" \
	".\Debug\tif_read.obj" \
	".\Debug\tif_packbits.obj" \
	".\Debug\tif_win32.obj" \
	".\Debug\tif_fax3.obj" \
	".\Debug\tif_error.obj"

"$(OUTDIR)\libtiff.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mkg3states - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mkg3states\Release"
# PROP BASE Intermediate_Dir "mkg3states\Release"
# PROP BASE Target_Dir "mkg3states"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "mkg3states.d\Release"
# PROP Intermediate_Dir "mkg3states.d\Release"
# PROP Target_Dir "mkg3states"
OUTDIR=.\mkg3states.d\Release
INTDIR=.\mkg3states.d\Release

ALL : "$(OUTDIR)\mkg3states.exe"

CLEAN : 
	-@erase ".\mkg3states.d\Release\mkg3states.exe"
	-@erase ".\mkg3states.d\Release\mkg3states.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/mkg3states.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\mkg3states.d\Release/
CPP_SBRS=

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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mkg3states.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/mkg3states.pdb" /machine:I386 /out:"$(OUTDIR)/mkg3states.exe" 
LINK32_OBJS= \
	".\mkg3states.d\Release\mkg3states.obj"

"$(OUTDIR)\mkg3states.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mkg3states - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mkg3states\Debug"
# PROP BASE Intermediate_Dir "mkg3states\Debug"
# PROP BASE Target_Dir "mkg3states"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "mkg3states.d\Debug"
# PROP Intermediate_Dir "mkg3states.d\Debug"
# PROP Target_Dir "mkg3states"
OUTDIR=.\mkg3states.d\Debug
INTDIR=.\mkg3states.d\Debug

ALL : "$(OUTDIR)\mkg3states.exe"

CLEAN : 
	-@erase ".\mkg3states.d\Debug\vc40.pdb"
	-@erase ".\mkg3states.d\Debug\vc40.idb"
	-@erase ".\mkg3states.d\Debug\mkg3states.exe"
	-@erase ".\mkg3states.d\Debug\mkg3states.obj"
	-@erase ".\mkg3states.d\Debug\mkg3states.ilk"
	-@erase ".\mkg3states.d\Debug\mkg3states.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/mkg3states.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\mkg3states.d\Debug/
CPP_SBRS=

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

RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mkg3states.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/mkg3states.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/mkg3states.exe" 
LINK32_OBJS= \
	".\mkg3states.d\Debug\mkg3states.obj"

"$(OUTDIR)\mkg3states.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "libtiff - Win32 Release"
# Name "libtiff - Win32 Debug"

!IF  "$(CFG)" == "libtiff - Win32 Release"

!ELSEIF  "$(CFG)" == "libtiff - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\tif_win32.c
DEP_CPP_TIF_W=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_win32.obj" : $(SOURCE) $(DEP_CPP_TIF_W) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_close.c
DEP_CPP_TIF_C=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_close.obj" : $(SOURCE) $(DEP_CPP_TIF_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_codec.c
DEP_CPP_TIF_CO=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_codec.obj" : $(SOURCE) $(DEP_CPP_TIF_CO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_compress.c
DEP_CPP_TIF_COM=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_compress.obj" : $(SOURCE) $(DEP_CPP_TIF_COM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_dir.c
DEP_CPP_TIF_D=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_dir.obj" : $(SOURCE) $(DEP_CPP_TIF_D) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_dirinfo.c
DEP_CPP_TIF_DI=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_dirinfo.obj" : $(SOURCE) $(DEP_CPP_TIF_DI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_dirread.c
DEP_CPP_TIF_DIR=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_dirread.obj" : $(SOURCE) $(DEP_CPP_TIF_DIR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_dirwrite.c
DEP_CPP_TIF_DIRW=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_dirwrite.obj" : $(SOURCE) $(DEP_CPP_TIF_DIRW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_dumpmode.c
DEP_CPP_TIF_DU=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_dumpmode.obj" : $(SOURCE) $(DEP_CPP_TIF_DU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_error.c
DEP_CPP_TIF_E=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_error.obj" : $(SOURCE) $(DEP_CPP_TIF_E) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_flush.c
DEP_CPP_TIF_F=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_flush.obj" : $(SOURCE) $(DEP_CPP_TIF_F) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_getimage.c
DEP_CPP_TIF_G=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_getimage.obj" : $(SOURCE) $(DEP_CPP_TIF_G) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_jpeg.c
DEP_CPP_TIF_J=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	
NODEP_CPP_TIF_J=\
	".\jpeglib.h"\
	".\jerror.h"\
	

"$(INTDIR)\tif_jpeg.obj" : $(SOURCE) $(DEP_CPP_TIF_J) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_next.c
DEP_CPP_TIF_N=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_next.obj" : $(SOURCE) $(DEP_CPP_TIF_N) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_open.c
DEP_CPP_TIF_O=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_open.obj" : $(SOURCE) $(DEP_CPP_TIF_O) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_packbits.c
DEP_CPP_TIF_P=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_packbits.obj" : $(SOURCE) $(DEP_CPP_TIF_P) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_predict.c
DEP_CPP_TIF_PR=\
	".\tiffiop.h"\
	".\tif_predict.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_predict.obj" : $(SOURCE) $(DEP_CPP_TIF_PR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_print.c
DEP_CPP_TIF_PRI=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_print.obj" : $(SOURCE) $(DEP_CPP_TIF_PRI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_read.c
DEP_CPP_TIF_R=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_read.obj" : $(SOURCE) $(DEP_CPP_TIF_R) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_strip.c
DEP_CPP_TIF_S=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_strip.obj" : $(SOURCE) $(DEP_CPP_TIF_S) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_swab.c
DEP_CPP_TIF_SW=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_swab.obj" : $(SOURCE) $(DEP_CPP_TIF_SW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_thunder.c
DEP_CPP_TIF_T=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_thunder.obj" : $(SOURCE) $(DEP_CPP_TIF_T) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_tile.c
DEP_CPP_TIF_TI=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_tile.obj" : $(SOURCE) $(DEP_CPP_TIF_TI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_version.c
DEP_CPP_TIF_V=\
	".\tiffiop.h"\
	".\version.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_version.obj" : $(SOURCE) $(DEP_CPP_TIF_V) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_warning.c
DEP_CPP_TIF_WA=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_warning.obj" : $(SOURCE) $(DEP_CPP_TIF_WA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_aux.c
DEP_CPP_TIF_A=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_aux.obj" : $(SOURCE) $(DEP_CPP_TIF_A) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tif_write.c
DEP_CPP_TIF_WR=\
	".\tiffiop.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\tif_write.obj" : $(SOURCE) $(DEP_CPP_TIF_WR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Project Dependency

# Project_Dep_Name "mkg3states"

!IF  "$(CFG)" == "libtiff - Win32 Release"

"mkg3states - Win32 Release" : 
   $(MAKE) /$(MAKEFLAGS) /F .\libtiff.mak CFG="mkg3states - Win32 Release" 

!ELSEIF  "$(CFG)" == "libtiff - Win32 Debug"

"mkg3states - Win32 Debug" : 
   $(MAKE) /$(MAKEFLAGS) /F .\libtiff.mak CFG="mkg3states - Win32 Debug" 

!ENDIF 

# End Project Dependency
################################################################################
# Begin Source File

SOURCE=.\tif_fax3.c
DEP_CPP_TIF_FA=\
	".\tiffiop.h"\
	".\tif_fax3.h"\
	".\g3states.h"\
	".\t4.h"\
	".\port.h"\
	".\tiffconf.h"\
	".\tiffcomp.h"\
	".\tiffio.h"\
	".\tif_dir.h"\
	".\tiff.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\tif_fax3.obj" : $(SOURCE) $(DEP_CPP_TIF_FA) "$(INTDIR)"


# End Source File
# End Target
################################################################################
# Begin Target

# Name "mkg3states - Win32 Release"
# Name "mkg3states - Win32 Debug"

!IF  "$(CFG)" == "mkg3states - Win32 Release"

!ELSEIF  "$(CFG)" == "mkg3states - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\mkg3states.c
DEP_CPP_MKG3S=\
	".\port.h"\
	".\tif_fax3.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\tiff.h"\
	

"$(INTDIR)\mkg3states.obj" : $(SOURCE) $(DEP_CPP_MKG3S) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################

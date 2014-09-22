# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=libip - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to libip - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "libip - Win32 Release" && "$(CFG)" != "libip - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "libip.mak" CFG="libip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libip - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libip - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "libip - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "libip - Win32 Release"

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

ALL : "$(OUTDIR)\libip.lib"

CLEAN : 
	-@erase ".\Release\libip.lib"
	-@erase ".\Release\pccfct2.obj"
	-@erase ".\Release\drawline8.obj"
	-@erase ".\Release\psaf.obj"
	-@erase ".\Release\ip.obj"
	-@erase ".\Release\license.obj"
	-@erase ".\Release\histogram.obj"
	-@erase ".\Release\pccfctde.obj"
	-@erase ".\Release\acm_io.obj"
	-@erase ".\Release\tlc1fct.obj"
	-@erase ".\Release\sgl_stat.obj"
	-@erase ".\Release\tlc3fct.obj"
	-@erase ".\Release\convolve.obj"
	-@erase ".\Release\pccfct.obj"
	-@erase ".\Release\llist.obj"
	-@erase ".\Release\fft.obj"
	-@erase ".\Release\p_app.obj"
	-@erase ".\Release\pmom.obj"
	-@erase ".\Release\descript.obj"
	-@erase ".\Release\fltrbttr.obj"
	-@erase ".\Release\xytoline.obj"
	-@erase ".\Release\fft2d.obj"
	-@erase ".\Release\pv.obj"
	-@erase ".\Release\n2_pv.obj"
	-@erase ".\Release\fltrgaus.obj"
	-@erase ".\Release\ph.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\libtiff\libtiff" /I " ..\libimage" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\libtiff\libtiff" /I " ..\libimage" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/libip.pch" /YX /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/libip.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/libip.lib" 
LIB32_OBJS= \
	".\Release\pccfct2.obj" \
	".\Release\drawline8.obj" \
	".\Release\psaf.obj" \
	".\Release\ip.obj" \
	".\Release\license.obj" \
	".\Release\histogram.obj" \
	".\Release\pccfctde.obj" \
	".\Release\acm_io.obj" \
	".\Release\tlc1fct.obj" \
	".\Release\sgl_stat.obj" \
	".\Release\tlc3fct.obj" \
	".\Release\convolve.obj" \
	".\Release\pccfct.obj" \
	".\Release\llist.obj" \
	".\Release\fft.obj" \
	".\Release\p_app.obj" \
	".\Release\pmom.obj" \
	".\Release\descript.obj" \
	".\Release\fltrbttr.obj" \
	".\Release\xytoline.obj" \
	".\Release\fft2d.obj" \
	".\Release\pv.obj" \
	".\Release\n2_pv.obj" \
	".\Release\fltrgaus.obj" \
	".\Release\ph.obj"

"$(OUTDIR)\libip.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

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

ALL : "$(OUTDIR)\libip.lib"

CLEAN : 
	-@erase ".\Debug\libip.lib"
	-@erase ".\Debug\p_app.obj"
	-@erase ".\Debug\fft.obj"
	-@erase ".\Debug\fltrgaus.obj"
	-@erase ".\Debug\drawline8.obj"
	-@erase ".\Debug\pccfct2.obj"
	-@erase ".\Debug\fft2d.obj"
	-@erase ".\Debug\n2_pv.obj"
	-@erase ".\Debug\histogram.obj"
	-@erase ".\Debug\license.obj"
	-@erase ".\Debug\psaf.obj"
	-@erase ".\Debug\tlc1fct.obj"
	-@erase ".\Debug\pccfctde.obj"
	-@erase ".\Debug\pmom.obj"
	-@erase ".\Debug\descript.obj"
	-@erase ".\Debug\acm_io.obj"
	-@erase ".\Debug\tlc3fct.obj"
	-@erase ".\Debug\sgl_stat.obj"
	-@erase ".\Debug\pv.obj"
	-@erase ".\Debug\convolve.obj"
	-@erase ".\Debug\ph.obj"
	-@erase ".\Debug\pccfct.obj"
	-@erase ".\Debug\llist.obj"
	-@erase ".\Debug\ip.obj"
	-@erase ".\Debug\fltrbttr.obj"
	-@erase ".\Debug\xytoline.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I "..\libtiff\libtiff" /I " ..\libimage" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /I "..\libtiff\libtiff" /I " ..\libimage"\
 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/libip.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/libip.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/libip.lib" 
LIB32_OBJS= \
	".\Debug\p_app.obj" \
	".\Debug\fft.obj" \
	".\Debug\fltrgaus.obj" \
	".\Debug\drawline8.obj" \
	".\Debug\pccfct2.obj" \
	".\Debug\fft2d.obj" \
	".\Debug\n2_pv.obj" \
	".\Debug\histogram.obj" \
	".\Debug\license.obj" \
	".\Debug\psaf.obj" \
	".\Debug\tlc1fct.obj" \
	".\Debug\pccfctde.obj" \
	".\Debug\pmom.obj" \
	".\Debug\descript.obj" \
	".\Debug\acm_io.obj" \
	".\Debug\tlc3fct.obj" \
	".\Debug\sgl_stat.obj" \
	".\Debug\pv.obj" \
	".\Debug\convolve.obj" \
	".\Debug\ph.obj" \
	".\Debug\pccfct.obj" \
	".\Debug\llist.obj" \
	".\Debug\ip.obj" \
	".\Debug\fltrbttr.obj" \
	".\Debug\xytoline.obj"

"$(OUTDIR)\libip.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "libip - Win32 Release"
# Name "libip - Win32 Debug"

!IF  "$(CFG)" == "libip - Win32 Release"

!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\p_app.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_P_APP=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\p_app.obj" : $(SOURCE) $(DEP_CPP_P_APP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_P_APP=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\p_app.obj" : $(SOURCE) $(DEP_CPP_P_APP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ph.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_PH_C2=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\ph.obj" : $(SOURCE) $(DEP_CPP_PH_C2) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_PH_C2=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\ph.obj" : $(SOURCE) $(DEP_CPP_PH_C2) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pmom.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_PMOM_=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\pmom.obj" : $(SOURCE) $(DEP_CPP_PMOM_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_PMOM_=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\pmom.obj" : $(SOURCE) $(DEP_CPP_PMOM_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pv.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_PV_C6=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\pv.obj" : $(SOURCE) $(DEP_CPP_PV_C6) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_PV_C6=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\pv.obj" : $(SOURCE) $(DEP_CPP_PV_C6) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ip.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_IP_C8=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\ip.obj" : $(SOURCE) $(DEP_CPP_IP_C8) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_IP_C8=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\ip.obj" : $(SOURCE) $(DEP_CPP_IP_C8) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fft.c

"$(INTDIR)\fft.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\fft2d.c

"$(INTDIR)\fft2d.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\fltrbttr.c

"$(INTDIR)\fltrbttr.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\fltrgaus.c

"$(INTDIR)\fltrgaus.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\sgl_stat.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_SGL_S=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\sgl_stat.obj" : $(SOURCE) $(DEP_CPP_SGL_S) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_SGL_S=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\sgl_stat.obj" : $(SOURCE) $(DEP_CPP_SGL_S) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\llist.c
DEP_CPP_LLIST=\
	".\lldef.h"\
	

"$(INTDIR)\llist.obj" : $(SOURCE) $(DEP_CPP_LLIST) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\convolve.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_CONVO=\
	".\ip.h"\
	".\convolve.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\convolve.obj" : $(SOURCE) $(DEP_CPP_CONVO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_CONVO=\
	".\ip.h"\
	".\convolve.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\convolve.obj" : $(SOURCE) $(DEP_CPP_CONVO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pccfct.c
DEP_CPP_PCCFC=\
	".\pcc2.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\pccfct.obj" : $(SOURCE) $(DEP_CPP_PCCFC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\pccfct2.c
DEP_CPP_PCCFCT=\
	".\pcc2.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\pccfct2.obj" : $(SOURCE) $(DEP_CPP_PCCFCT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\pccfctde.c
DEP_CPP_PCCFCTD=\
	".\..\libimage\images.h"\
	".\pcc2.h"\
	

"$(INTDIR)\pccfctde.obj" : $(SOURCE) $(DEP_CPP_PCCFCTD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\n2_pv.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_N2_PV=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\n2_pv.obj" : $(SOURCE) $(DEP_CPP_N2_PV) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_N2_PV=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\n2_pv.obj" : $(SOURCE) $(DEP_CPP_N2_PV) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\acm_io.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_ACM_I=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\acm_io.obj" : $(SOURCE) $(DEP_CPP_ACM_I) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_ACM_I=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\acm_io.obj" : $(SOURCE) $(DEP_CPP_ACM_I) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\descript.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_DESCR=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\descript.obj" : $(SOURCE) $(DEP_CPP_DESCR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_DESCR=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\descript.obj" : $(SOURCE) $(DEP_CPP_DESCR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\psaf.c

!IF  "$(CFG)" == "libip - Win32 Release"

DEP_CPP_PSAF_=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\misc.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\psaf.obj" : $(SOURCE) $(DEP_CPP_PSAF_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "libip - Win32 Debug"

DEP_CPP_PSAF_=\
	".\ip.h"\
	".\ph.h"\
	".\..\libtiff\libtiff\tiffio.h"\
	".\..\libimage\draw.h"\
	".\lldef.h"\
	".\sgl_stat.h"\
	".\convolve.h"\
	".\pcc2.h"\
	".\bdy_stru.h"\
	".\..\libimage\misc.h"\
	".\..\libtiff\libtiff\tiff.h"\
	".\..\libimage\tiffimage.h"\
	".\..\libimage\gd.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\psaf.obj" : $(SOURCE) $(DEP_CPP_PSAF_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\license.c

"$(INTDIR)\license.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\histogram.c

"$(INTDIR)\histogram.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tlc1fct.c
DEP_CPP_TLC1F=\
	".\..\libimage\images.h"\
	".\pcc2.h"\
	

"$(INTDIR)\tlc1fct.obj" : $(SOURCE) $(DEP_CPP_TLC1F) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tlc3fct.c
DEP_CPP_TLC3F=\
	".\pcc2.h"\
	".\..\libimage\images.h"\
	

"$(INTDIR)\tlc3fct.obj" : $(SOURCE) $(DEP_CPP_TLC3F) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\xytoline.c
DEP_CPP_XYTOL=\
	".\..\libimage\images.h"\
	".\pcc2.h"\
	

"$(INTDIR)\xytoline.obj" : $(SOURCE) $(DEP_CPP_XYTOL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\drawline8.c
DEP_CPP_DRAWL=\
	".\..\libimage\images.h"\
	

"$(INTDIR)\drawline8.obj" : $(SOURCE) $(DEP_CPP_DRAWL) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################

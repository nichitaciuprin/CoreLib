@echo off
setlocal

set deps=%~dp0..
set build=%~dp0build
set dir1=%deps%\ReactPhysics3D
set dir2=%deps%\ReactPhysics3DWrap

set src=
set src=%src% %deps%\ReactPhysics3DWrap\src\ReactPhysics3DWrap.cpp

set include=
set include=%include% -I%deps%\Base\include
set include=%include% -I%deps%\ReactPhysics3D\include
set include=%include% -I%deps%\ReactPhysics3DWrap\include

set lib=%lib% -L%deps%\ReactPhysics3D\lib -lreactphysics3d

if exist %build% rmdir /S /Q %build%
   mkdir %build%

set fileo=%build%\librp3dwrap.o
set filea=%build%\librp3dwrap.a

g++ -c %src% -o %fileo% %include% %lib%
ar rcs %filea% %fileo%
del %fileo%

@REM ar -x %lib1% --output=build
@REM ar rcs librp3dwrap.a %build%\*.obj

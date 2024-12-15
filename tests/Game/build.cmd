@echo off
setlocal

set deps=%~dp0..\..\deps
set main=%~dp0main.cpp

set flags=
set flags=%flags% -g3 -Og -std=c++17 -pthread -m64
set flags=%flags% -Werror -Wall -Wno-missing-braces

set include=
set include=%include% -I%~dp0src
set include=%include% -I%deps%\corelib\include
set include=%include% -I%deps%\sys\include
set include=%include% -I%deps%\Raylib\include
set include=%include% -I%deps%\RaylibWrap\include
set include=%include% -I%deps%\ReactPhysics3D\include
set include=%include% -I%deps%\ReactPhysics3DWrap\include

set src=
set src=%src% %deps%\Sys\src\SysHelper.c
set src=%src% %deps%\Sys\src\SysWindow.c
set src=%src% %deps%\Sys\src\SysNet.c
set src=%src% %deps%\RaylibWrap\src\RaylibWrap.cpp

set lib=
set lib=%lib% -L%deps%\raylib\lib -lraylib -lgdi32 -lwinmm
set lib=%lib% -L%deps%\ReactPhysics3D\lib -lreactphysics3d
set lib=%lib% -lgdi32
set lib=%lib% -lWs2_32

@REM set src=%src% %~dp0src\ParticlesGroup.cpp
@REM set src=%src% %~dp0src\Magnet.cpp
@REM set src=%src% %~dp0src\Arrow.cpp
@REM set src=%src% %~dp0src\Projectile.cpp
@REM set src=%src% %~dp0src\WorldPhysics.cpp
@REM set src=%src% %~dp0src\RigidBody.cpp
@REM set src=%src% %~dp0src\StaticBound.cpp
@REM set src=%src% %~dp0src\Enemy.cpp
@REM set src=%src% %~dp0src\World.cpp
@REM set src=%src% %~dp0src\WorldWindow.cpp

if exist build rmdir /S /Q build
   mkdir build

@REM echo %time%

g++ %main% %src% -o build/main.exe %include% %lib% %flags%

@REM echo %time%

@echo off

if [%1]==[] (
echo "Use 'pc', 'web' or 'all' as parameter"
goto :eof
)
if /I [%1] EQU [web] (
call :buildWeb
goto :eof
)
if /I [%1] EQU [pc] (
call :buildPC
goto :eof
)
if /I [%1] EQU [all] (
call :buildPC
call :buildWeb
goto :eof
)

echo Unknown parameter "%1", please use 'pc', 'web' or 'all'
goto :eof

::-----------build for PC-----::
:buildPC
echo Build for pc
if not exist build_PC_Win mkdir build_PC_Win
pushd build_PC_Win
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
..\Tools\win\ninja.exe
popd
exit /B
::----------------------------::

::-----------build for Web-----::
:buildWeb
echo Build for Web
if not exist build_Web mkdir build_Web
pushd build_Web 
# TODO Make it with Ninja
emcmake cmake -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-s USE_GLFW=3" -DCMAKE_EXECUTABLE_SUFFIX=".html" -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..
emmake make PLATFORM=PLATFORM_WEB -B -j12
popd
exit /B
::----------------------------::
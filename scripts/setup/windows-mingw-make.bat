@echo off

pushd ..\..
premake5 --os=windows --cc=mingw gmake
popd
pause
@echo off

pushd ..\..
premake5 --os=windows --cc=gcc gmake2
popd
pause
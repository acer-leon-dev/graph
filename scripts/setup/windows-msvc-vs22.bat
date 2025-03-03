@echo off

pushd ..\..
premake5 --os=windows --cc=msc-v143 vs2022
popd
pause
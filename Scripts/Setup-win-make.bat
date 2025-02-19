@echo off

pushd ..
Vendor\Binaries\Premake\Windows\premake5.exe --file=Build.lua --os=windows gmake2
popd
pause
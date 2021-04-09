@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\vsdevcmd.bat" -no_logo

pushd ..\build\

set CommonCompilerFlags=-diagnostics:column -WL -nologo -fp:fast -Gm- -GR- -EHa- -Od -FC -Zi -w
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib opengl32.lib

del *.pdb > NUL 2> NUL
echo WAITING FOR PDB > lock.tmp

cl %CommonCompilerFlags% ..\code\win32_va.cpp -link %CommonLinkerFlags%

del lock.tmp
del *.obj

popd
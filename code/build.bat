@echo off

set CommonCompilerFlags=-Od -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo- -Oi- -EHsc- 
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib

IF NOT EXIST ..\handmade_ray_build mkdir ..\handmade_ray_build
pushd ..\handmade_ray_build

cl %CommonCompilerFlags% ..\code\Ray.cpp /link %CommonLinkerFlags% 
popd


pushd ..\handmade_ray_data
..\handmade_ray_build\ray.exe
start test.bmp
popd

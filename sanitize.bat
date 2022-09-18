@echo off
pushd bin
cl -fsanitize=address /Zi ..\src\main.c user32.lib gdi32.lib Opengl32.lib Kernel32.lib
popd

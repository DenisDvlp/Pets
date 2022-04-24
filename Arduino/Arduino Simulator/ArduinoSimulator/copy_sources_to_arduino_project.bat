echo off

call :CopySource Animation.h
call :CopySource Core.h
call :CopySource Core.cpp
call :CopySource Images.h
call :CopySource Images.cpp
call :CopySource Font.h
call :CopySource FontCirillic.h
call :CopySource FontCirillic.cpp
call :CopySource Graphics.h
call :CopySource Graphics.cpp
call :CopySource Sprite.h

pause
exit /b 0

:CopySource %1
echo %1
copy /Y %1 ..\..\main
exit /b 0
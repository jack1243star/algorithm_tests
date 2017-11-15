@IF "%1"=="" @GOTO Make
@IF "%1"=="run" @GOTO Run
@IF "%1"=="clean" @GOTO Clean
@ECHO Usage: make.bat [run|clean]
@GOTO End

:Make
  g++ -Wall -Wextra main.c -o main.exe
@GOTO End

:Run
  g++ -Wall -Wextra main.c -o main.exe
  main.exe
  love love2d-visualize
@GOTO End

:Clean
  del main.exe love2d-visualize\output.lua
@GOTO End

:End
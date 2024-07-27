set SRC=src/*.c
 set CC=gcc
 set CFLAGS=-Wall -Wextra
 set IDIR=C:/msys64/ucrt64/include
 set LDIR=C:/msys64/ucrt64/lib
 set SRC=src/*.c
 set LIBS=-lm -lSDL3 -lGLEW -lopengl32
 set EXE=main
 %CC% %CFLAGS% %SRC% -o %EXE% -I%IDIR% -L%LDIR% %LIBS%
 pause

#!/bin/bash

CC="gcc"
CCFLAGS="-Wall -Wextra"
IDIR="/usr/local/include"
LDIR="/usr/local/lib"
LIBS="-lm -lSDL3 -lGLEW"
SRC="src/*.c"
RPATH=""
FRAMEWORKS=""
EXE="main"
BAT="set SRC=$SRC\n
set CC=$CC\n
set CFLAGS=$CCFLAGS\n
set IDIR=C:/msys64/ucrt64/include\n
set LDIR=C:/msys64/ucrt64/lib\n
set SRC=$SRC\n
set LIBS=$LIBS -lopengl32\n
set EXE=$EXE\n
%CC% %CFLAGS% %SRC% -o %EXE% -I%IDIR% -L%LDIR% %LIBS%\n
pause"

echo -e $BAT > build_win.bat

LIBS+=" -lGL"
if [ `uname` = "Darwin" ]; then
    FRAMEWORKS+="-framework OpenGL"
    RPATH+="-rpath $LDIR"
fi
if [ `uname` = "Linux" ]; then
    LIBS+=" -lpthread -ldl"
fi

$CC $CCFLAGS $SRC -o $EXE -I$IDIR -L$LDIR $LIBS $FRAMEWORKS $RPATH 

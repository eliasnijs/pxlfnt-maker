#!/bin/sh

# IMPORTANT(Elias): Assumes you are on linux!

# files
SOURCE="./maker/src/sdl_maker.cpp"
OUTPUT="./build/font-maker"

# includes and libs
INCS=""
LIBS="-lSDL2main -lSDL2"

#  -fsanitize=address

# flags
WFLAGS="-Wno-deprecated-declarations -Wno-unused-variable -Wno-unused-function -Wno-write-strings"
DFLAGS="-DENABLE_ASSERT"
CPPFLAGS="-D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\""
#CFLAGS="-Wall ${WFLAGS} -O0 -O2 ${INCS} ${CPPFLAGS}"
CFLAGS="-g -Wall ${WFLAGS} ${INCS} ${CPPFLAGS}"
LDFLAGS=${LIBS}

# compiler and linker
CC="g++" 

# building
cd $(dirname $0)
${CC} $CFLAGS $DFLAGS -o $OUTPUT $SOURCE $LDFLAGS

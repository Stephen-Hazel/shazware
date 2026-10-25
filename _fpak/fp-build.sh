#!/bin/sh
# fp-build.sh - build n install everything into /app n /var for flatpak

# load up /app/share
cp -pr _fpak/share /app   || exit 1

# each app gets common "stv" include code
for d in ftx big flatten l ned recent renem undup; do
   ln -sfn ../stv $d/stv  || exit 1
done

# build all apps at once via _fpak/CMakeLists.txt
cmake -G Ninja -S _fpak -B _b --log-level=WARNING \
      -DCMAKE_BUILD_TYPE=${1:-Debug} -DCMAKE_INSTALL_MESSAGE=NEVER \
                               -DCMAKE_INSTALL_PREFIX=/app &&
cmake --build   _b  &&
cmake --install _b        || exit 1

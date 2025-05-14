#!/bin/sh

SRC_DIR=$(dirname -- "$( readlink -f -- "$0"; )")

# -=-=-=-=-=-=-=- SETUP CLIENT -=-=-=-=-=-=-=-

# REMOVE BUILD DIRECTORY IF IS EXIST
if [ -d "$TMP/logma-client" ]; then
	rm -rf $TMP/logma-client
fi 

# CLONE CLIENT
git clone https://github.com/DStener/loGMa-Finance-Client.git $TMP/logma-client
cd $TMP/logma-client
git checkout devel

# BUILD CLIENT
npm install
npm run -s build

cp -rf dist/* $SRC_DIR/root

# -=-=-=-=-=-=-=- SETUP SERVER -=-=-=-=-=-=-=-

cd $SRC_DIR
cmake -B build .
cd build
cmake --build . -j $(nproc)
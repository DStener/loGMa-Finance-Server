#!/bin/sh

SRC_DIR=$(dirname -- "$( readlink -f -- "$0"; )")

# sh $SRC_DIR/setup.sh

exec $(find $SRC_DIR -type f -executable -name "server" -print)
#!/bin/bash
APP_NAME=open311-proxy
BUILD=./build
DIST=./dist

if [ ! -d $BUILD ]
	then mkdir $BUILD
fi

if [ ! -d $DIST ]
	then mkdir $DIST
fi

rsync -rlv --exclude-from=./buildignore --delete ./ ./build/

tar czvf $DIST/$APP_NAME.tar.gz --transform=s/build/$APP_NAME/ $BUILD

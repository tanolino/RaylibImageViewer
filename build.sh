#!/bin/bash

buildPC () {
	echo "Build for pc"
	mkdir -p buildPC
	pushd buildPC
	cmake -G Ninja ..
	../Tools/linux/ninja
	popd
}

buildWeb () {
	echo "Build for Web"
	mkdir -p buildWeb
	pushd buildWeb 
	# TODO Make it with Ninja
	emcmake cmake -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-s USE_GLFW=3" -DCMAKE_EXECUTABLE_SUFFIX=".html" -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..
	emmake make PLATFORM=PLATFORM_WEB -B
	popd
}

if [ -z "$1" ]
then
    echo "Use 'pc', 'web' or 'all' as parameter"
elif [ "$1" == "web" ]
then
	buildWeb
elif [ "$1" == "pc" ]
then
	buildPC
elif [ "$1" == "all" ]
then
	buildPC
	buildWeb
else
	echo "Unknown parameter '$1', please use 'pc', 'web' or 'all'"
fi

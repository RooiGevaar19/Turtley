#!/bin/bash

# ====== ARGS

modules=modules/Application.cpp
flags=(-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)
output=turtley.run

# ====== COMPILE

g++ $modules main.cpp -std=c++2a -w ${flags[*]} -o $output

# ====== IF COMPILED

if [ $? -eq 0 ] ; then
	echo "Successfully compiled! Run \"./$output\" to run Turtley!"
fi

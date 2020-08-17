#!/bin/bash
modules=modules/Application.cpp

output=turtley.run

g++ $modules main.cpp -std=c++2a -w -lSDL2 -o $output

if [ $? -eq 0 ] ; then
	echo "Successfully compiled! Run \"./$output\" to run Turtley!"
fi

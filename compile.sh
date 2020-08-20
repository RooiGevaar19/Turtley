#!/bin/bash

# ====== ARGS

modules=(
	modules/ApplicationTest.cpp
    modules/ApplicationTest2.cpp
)
flags=(
	-lSDL2 
	-lSDL2_image 
	-lSDL2_ttf 
	-lSDL2_mixer
)
standard=c++2a
output=turtley.run


# ====== COMPILE

echo -ne "\e[5;93mCompiling...\e[m\n"
g++ ${modules[*]} main.cpp -std=$standard -w ${flags[*]} -o $output

# ====== IF COMPILED

if [ $? -eq 0 ] ; then
	echo -ne "\r\e[1A\e[1;32mSuccessfully compiled!\n\e[mRun \"\e[1m./$output\e[m\" to run Turtley!\n"
else
    echo -ne "\n\e[1;31mError when compiling the project!\n\e[mCheck the details above.\n"
fi

#!/bin/sh

CURRENT_PATH=$(pwd)
echo $CURRENT_PATH

ctags -R $CURRENT_PATH/


find $CURRENT_PATH/ -iname "*.cc" -o -iname "*.hh" -o -iname "*.java" -o -iname "*.c" -o -iname "*.cpp" -o -iname "*.h" > cscope.files

cscope -Rkqb

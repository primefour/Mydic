#!/bin/sh


#current directory
scan_dir=$('pwd')
#parameter list
echo $@ 
echo $1

if [ -n "$1" ]; then
    scan_dir=$@
fi


echo $scan_dir

if [ -n "$scan_dir" ]; then
    echo "######################start scan #####################"
    ctags -R $scan_dir
    find $scan_dir  -iname "*.c" -o -iname "*.cpp" -o -iname "*.h" -o -iname "*.java" -o -iname "*.s"  > cscope.files
    cscope -Rkqb
fi

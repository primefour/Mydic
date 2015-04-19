#!/bin/sh

LOCAL_DIR=WorkDir

RES_DIR=ResDir

DECOMPILE_ROOT_DIR=/home/crazyhorse/MyProject/AppToolDecompile

mkdir -p ${LOCAL_DIR}/${RES_DIR} 

cp $1 ${LOCAL_DIR}/${RES_DIR}/

cd ${LOCAL_DIR}/${RES_DIR}/

${DECOMPILE_ROOT_DIR}/apktool/aapt d badging $1 > property.txt

${DECOMPILE_ROOT_DIR}/apktool/apktool d $1 

cd ../../

cp $1 ./${LOCAL_DIR}/sample.zip

cd ${LOCAL_DIR} 

echo ${PWD}

unzip sample.zip

echo ${PWD}

ls

${DECOMPILE_ROOT_DIR}/dex2jar/dex2jar.sh ./classes.dex 

echo ${PWD}

mkdir ./javaSrc

mkdir ./classSrc
mv classes_dex2jar.jar ./classSrc/

cd ./classSrc/

unzip classes_dex2jar.jar  

cd ..

${DECOMPILE_ROOT_DIR}/jadDir/jad -o -r -sjava -djavaSrc 'classSrc/**/*.class'



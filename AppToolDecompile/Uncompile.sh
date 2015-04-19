#!/bin/sh

LOCAL_DIR=WorkDir
mkdir ./${LOCAL_DIR}

cp $1 ./${LOCAL_DIR}/sample.zip

cd ${LOCAL_DIR} 

echo ${PWD}

unzip sample.zip

echo ${PWD}

ls

/home/crazyhorse/MyProject/AppToolDecompile/dex2jar/dex2jar.sh ./classes.dex 

echo ${PWD}

mkdir ./javaSrc

mkdir ./classSrc
mv classes_dex2jar.jar ./classSrc/

cd ./classSrc/

unzip classes_dex2jar.jar  

cd ..

/home/crazyhorse/MyProject/AppToolDecompile/jadDir/jad -o -r -sjava -djavaSrc 'classSrc/**/*.class'



#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "usage: makefullrelease.sh versionnumber"
  exit 1
fi

if [ -d $1 ]; then
  rm -rf $1
fi

echo "Deploying firmware"
mkdir $1
mkdir $1/firmware
cp -rf ./SOURCES/WEBAPP/ESP32/aurora/aurora.ino.esp32.bin $1/firmware/aurora.ino.esp32.bin

echo "Deploying updater"
mkdir $1/updater
cp -rf ./SOURCES/updater/* $1/updater/
cp -rf ./SOURCES/WEBAPP/ESP32/aurora/aurora.ino.esp32.bin $1/updater/aurora.ino.esp32.bin

echo "Deploying documentation"
cp -rf ./DOCUMENTATION/UserManual_*.pdf $1

echo "Compressing JavaScript"
cd SOURCES/WEBAPP/js
cat aurora.js | gzip > aurora.jgz
cd ../../..

echo "Deploying plugins"
cd SOURCES/sigma2aurora
python sigma2aurora.py ../SIGMASTUDIO/8channels/8channels.xml 8channels --version v2.2.2 --gui ../WEBAPP/plugins/8channels/dsp.html --outputdir plugins
python sigma2aurora.py ../SIGMASTUDIO/HomeCinema71/HomeCinema71.xml HomeCinema71 --version v2.2.2 --gui ../WEBAPP/plugins/HomeCinema71/dsp.html --outputdir plugins
python sigma2aurora.py ../SIGMASTUDIO/4FIRs/4FIRs.xml 4FIRs --version v2.2.2 --gui ../WEBAPP/plugins/4FIRs/dsp.html --outputdir plugins

cd ../..

echo "Cleaning up"
mv -f ./SOURCES/sigma2aurora/plugins $1

echo "Finished"
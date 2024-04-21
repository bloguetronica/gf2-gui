#!/bin/sh

echo Obtaining required packages...
apt-get -qq update
apt-get -qq install build-essential
apt-get -qq install qt5-default
apt-get -qq install qtbase5-dev
echo Copying source code files...
mkdir -p /usr/local/src/gf2-gui/icons
mkdir -p /usr/local/src/gf2-gui/misc
cp -f src/about.cpp /usr/local/src/gf2-gui/.
cp -f src/about.h /usr/local/src/gf2-gui/.
cp -f src/about.ui /usr/local/src/gf2-gui/.
cp -f src/gf2-gui.pro /usr/local/src/gf2-gui/.
cp -f src/GPL.txt /usr/local/src/gf2-gui/.
cp -f src/icons/active64.png /usr/local/src/gf2-gui/icons/.
cp -f src/icons/gf2-gui.png /usr/local/src/gf2-gui/icons/.
cp -f src/icons/greyed64.png /usr/local/src/gf2-gui/icons/.
cp -f src/icons/selected64.png /usr/local/src/gf2-gui/icons/.
cp -f src/main.cpp /usr/local/src/gf2-gui/.
cp -f src/mainwindow.cpp /usr/local/src/gf2-gui/.
cp -f src/mainwindow.h /usr/local/src/gf2-gui/.
cp -f src/mainwindow.ui /usr/local/src/gf2-gui/.
cp -f src/misc/gf2-gui.desktop /usr/local/src/gf2-gui/misc/.
cp -f src/resources.qrc /usr/local/src/gf2-gui/.
cp -f src/README.txt /usr/local/src/gf2-gui/.
cp -f src/serial.cpp /usr/local/src/gf2-gui/.
cp -f src/serial.h /usr/local/src/gf2-gui/.
cp -f src/serial.ui /usr/local/src/gf2-gui/.
echo Building and installing application...
cd /usr/local/src/gf2-gui
qmake
make install clean
rm -f gf2-gui
echo Done!

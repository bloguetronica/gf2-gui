#!/bin/sh

echo Removing application...
rm -f /usr/local/share/applications/gf2-gui.desktop
rmdir --ignore-fail-on-non-empty /usr/local/share/applications
rm -f /usr/local/share/icons/hicolor/128x128/apps/gf2-gui.png
rmdir --ignore-fail-on-non-empty /usr/local/share/icons/hicolor/128x128/apps
rmdir --ignore-fail-on-non-empty /usr/local/share/icons/hicolor/128x128
rmdir --ignore-fail-on-non-empty /usr/local/share/icons/hicolor
rmdir --ignore-fail-on-non-empty /usr/local/share/icons
rm -f /usr/local/bin/gf2-gui
echo Removing source code files...
rm -rf /usr/local/src/gf2-gui
echo Done!

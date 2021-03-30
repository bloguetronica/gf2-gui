This directory contains the QT project required for compiling GF2 GUI. A list
of relevant files follows:
– about.cpp;
– about.h;
– about.ui;
– gf2-gui.pro;
– icons/active64.png
– icons/greyed64.png
– icons/selected64.png
– main.cpp;
– mainwindow.cpp;
– mainwindow.h;
– mainwindow.ui;
– resources.qrc;
– serial.cpp;
– serial.h;
– serial.ui.

In order to compile successfully, you must have the packages "build-essential"
and "qt5-default" already installed. Given that, if you wish to simply
compile, change your working directory to the current one on a terminal
window, and invoke "qmake", followed by "make" or "make all". Notice that
invoking "qmake" is necessary to generate the Makefile, but only needs to be
done once.

It may be necessary to undo any previous operations. Invoking "make clean"
will delete all object code generated during earlier compilations. However,
the previously generated binary is preserved.

This directory contains the QT project required for compiling GF2 GUI. A list
of relevant files follows:
– about.cpp;
– about.h;
– about.ui;
– gf2-gui.pro;
– icons/active64.png
– icons/gf2-gui.png
– icons/greyed64.png
– icons/selected64.png
– main.cpp;
– mainwindow.cpp;
– mainwindow.h;
– mainwindow.ui;
– misc/gf2-gui.desktop;
– resources.qrc;
– serial.cpp;
– serial.h;
– serial.ui.

In order to compile successfully, you must have the packages "build-essential"
and "qt5-default" (or "qtbase5-dev") already installed. Given that, if you
wish to simply compile, change your working directory to the current one on a
terminal window, and invoke "qmake", followed by "make" or "make all". Notice
that invoking "qmake" is necessary to generate the Makefile, but only needs to
be done once.

You can also install using make. To do so, after invoking "qmake", you should
simply run "sudo make install". If you wish to force a rebuild before the
installation, then you must invoke "sudo make clean install" instead.

It may be necessary to undo any previous operations. Invoking "make clean"
will delete all object code generated during earlier compilations. However,
the previously generated binary is preserved. It is important to note that it
is possible to undo previous installation operations as well, by invoking
"sudo make uninstall". Such approach is not recommended, though.

P.S.:
Notice that any make operation containing the actions "install" or "uninstall"
(e.g. "make install" or "make uninstall") requires root permissions, or in
other words, must be run with sudo.

# Compiling Ra

    Robotics Erlangen e.V.
    http://www.robotics-erlangen.de/
    info@robotics-erlangen.de


All programs should work on GNU/Linux (tested on Ubuntu 14.04), Mac OS X 10.10 and Windows >= 7.

In order to build Ra you will need:
 * cmake >= 2.8.9
 * g++ >= 4.6
 * qt >= 5.1.0
 * protobuf >= 2.0.0
 * luajit >= 2.0

Certain features require additional libraries:
 * libusb-1.0 - USB communication (version >= 1.0.9)
 * libsdl2 - Joystick support (version >= 2.0.2)
 * libudev - Required for joystick support (only required if libsdl2 is not available via the package manager)
 * liblua5.1-socket2 - Lua remote debugger (see strategy/test/debug/enable.lua) (version >= 2.1!, https://github.com/diegonehab/luasocket)

Package names for Ubuntu 14.04:
* cmake
* protobuf-compiler
* qtbase5-dev
* libudev-dev
* libsdl2-dev
* libluajit-5.1-dev
* libusb-1.0-0-dev
(and you need g++, since it's not included in the default instalation)

## Unix
The recommended way of building a project with CMake is by doing an
out-of-source build. This can be done like this:

> mkdir build
> cd build
> cmake ..
> make

Ra and the Logplayer can be started from the build/bin/ directory.
To install the desktop files use this command:
> make install-menu

In order to select which Qt-Installation to use specify it using a similar command line:
> cmake -DCMAKE_PREFIX_PATH=~/Qt/5.2.1/gcc_64/lib/cmake ..

To be able to use USB devices (sender, robots) the rights for udev have to be modified.
Just copy the file at `data/udev/99-robotics-usb-devices.rules` to `/etc/udev/rules.d/99-robotics-usb-devices.rules`

To use the remote debugger download, compile and install the luasocket library (version >= 2.1!). The libraries must be installed to `/usr/local/lib` to be recognised by LuaJIT
Compile instructions: (for Ubuntu 12.04)
> make LUAINC_linux=/usr/include/lua5.1
> sudo make install

## Windows
Get dependencies (tested using the given versions):
* cmake 3.0.2 - http://www.cmake.org/files/v3.0/cmake-3.0.2-win32-x86.exe
* mingw-get - http://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.ex
* Qt 5.3.2 OpenGL - http://download.qt-project.org/official_releases/qt/5.3/5.3.2/qt-opensource-windows-x86-mingw482_opengl-5.3.2.exe
* protobuf 2.6.1 - https://github.com/google/protobuf/releases/download/2.6.1/protobuf-2.6.1.tar.bz2
* luajit 2.0.3 - http://luajit.org/download/LuaJIT-2.0.3.tar.gz
* libusb 1.19 - http://downloads.sourceforge.net/project/libusb/libusb-1.0/libusb-1.0.19/libusb-1.0.19.tar.bz2
* luasocket 3.0-rc? - https://github.com/diegonehab/luasocket/archive/master.zip
* libsdl2 2.0.2 - http://libsdl.org/release/SDL2-devel-2.0.2-mingw.tar.gz

#### install cmake
use the installer, select add to PATH

#### install qt
run installer (use default install path! ), make sure to SELECT "Tools/MinGW 4.8"!

#### install mingw-get
Run installer (use default path C:\MinGW !) and install `msys-base, msys-patch`

Run `C:\mingw\msys\1.0\postinstall\pi.bat` set mingw path to `c:/Qt/Qt5.3.2/Tools/mingw482_32`

use `msys.bat` in `msys\1.0` to open msys console

**!!! USE MSYS TO COMPILE EVERYTHING !!!**

#### compile protobuf
> mkdir build && cd build
> ../configure --prefix=/usr/local --without-zlib && make && make install

#### compile luajit
> make && make install PREFIX=/usr/local && cp src/lua51.dll /usr/local/bin

#### compile libusb
> mkdir build && cd build
> ../configure --prefix=/usr/local && make CFLAGS="-DWINVER=0x0501" && make install

#### install libsdl2(prebuilt mingw package!)
> make install-package arch=i686-w64-mingw32 prefix=/usr/local

#### compile luasocket2
> make PLAT=mingw LUAINC_mingw=/usr/local/include/luajit-2.0 LUALIB_mingw=/usr/local/bin/lua51.dll
> make install PLAT=mingw INSTALL_TOP_LDIR=../build/share INSTALL_TOP_CDIR=../build/lib

#### compile ra
> mkdir build-win && cd build-win
> cmake -G "MSYS Makefiles" -DCMAKE_PREFIX_PATH=/c/Qt/Qt5.3.2/5.3/mingw482_32/lib/cmake -DCMAKE_BUILD_TYPE=Release -DLUA_INCLUDE_DIR=C:/MinGW/msys/1.0/local/include/luajit-2.0 -DLUA_LIBRARIES=C:/MinGW/msys/1.0/local/bin/lua51.dll -DPROTOBUF_INCLUDE_DIR=C:/MinGW/msys/1.0/local/include -DPROTOBUF_LIBRARY=C:/MinGW/msys/1.0/local/lib/libprotobuf.dll.a -DSDL2_INCLUDE_DIR=C:/MinGW/msys/1.0/local/include/SDL2 -DUSB_INCLUDE_DIR=C:/MinGW/msys/1.0/local/include/libusb-1.0 ..
> make

* copy config + data directory to `"builddir"/bin`
* copy libprotobuf-9.dll, libusb-1.0.dll, lua51.dll, SDL2.dll from `C:\MinGW\msys\1.0\local\bin` to `"builddir"/bin`
* copy icudt52.dll, icuin52.dll, icuuc52.dll, libgcc_s_dw2-1.dll, libstdc++-6.dll, libwinpthread-1.dll,
	Qt5Core.dll, Qt5Gui.dll, Qt5Network.dll, Qt5OpenGL.dll, Qt5Widgets.dll from `C:/Qt/Qt5.3.2/5.3/mingw482_32/bin` to `"builddir"/bin`
* copy qwindows.dll from `C:/Qt/Qt5.3.2/5.3/mingw482_32/plugins/platforms` to `"builddir"/bin/platforms`
	copy the folders of `luasocket2/build/lib` to `"builddir"/bin`

Finished!


## Mac OS X
Get dependencies using [Homebrew](http://brew.sh):
> brew install git sdl2 luajit protobuf libusb

Download Qt 5 from http://qt-project.org and install

Build using:
> cd path/to/framework
> mkdir build-mac && cd build-mac
> cmake -DCMAKE_PREFIX_PATH=~/Qt/5.4/clang_64/lib/cmake -DCMAKE_BUILD_TYPE=Release ..
> make

(If starting ra.app the normal way doesn't work launch it from Qt Creator)

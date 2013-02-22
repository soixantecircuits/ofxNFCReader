ofxNFCReader
=========

Copyright (c) 2013 Soixante circuits

MIT License.

For information on usage and redistribution, and for a DISCLAIMER OF ALL
WARRANTIES, see the file, "LICENSE.txt," in this distribution.

See https://github.com/soixantecircuits/ofxNFCReader for documentation as well as the [OF forums](http://forum.openframeworks.cc/index.php).

Description
-----------

ofxNFCReader is an openFrameworks addon to read nfc tags. It is based on [libnfc](http://nfc-tools.org).

It is under development.

It has been tested with a [ACR122 NFC reader](http://nfc-tools.org/index.php?title=ACR122) and ISO14443A tags.

It has been tested on linux only.

The roadmap is:

* os x support
* write tags
* mutiple devices connected


openFrameworks is a cross platform open source toolkit for creative coding in C++.
[http://www.openframeworks.cc/](http://www.openframeworks.cc/)


Installation
------------

To use ofxNFCReader, first you need to download and install [Open Frameworks](https://github.com/openframeworks/openFrameworks).

To get a copy of the repository you can download the source from [http://github.com/soixantecircuits/ofxNFCReader](http://github.com/soixantecircuits/ofxNFCReader) or, alternatively, you can use git clone:
<pre>
git clone git://github.com/soixantecircuits/ofxNFCReader.git
</pre>

The addon should sit in `openFrameworks/addons/ofxNFCReader/`.

Running the Example Project
---------------------------

The example projects are in the `example` folder.

### OSX

Xcode3: Open the Xcode project and hit "Build and Run". You might want to choose "Release" instead of "Debug" for faster performance.

Xcode4: Open the Xcode project, select the "ofxNFCReaderExample" scheme, and hit "Run".

### Linux

Install the libusb-1.0 library. On Ubuntu, you can do this with:
<pre>
sudo apt-get install libusb-1.0-0-dev
</pre>

Open the Code::Blocks .cbp and hit F9 to build. Optionally, you can build the example with the Makefile.

To run it, use the terminal:
<pre>
make
cd bin
./example_debug
</pre>

Also, you should create some udev rules in order to run the app without root privileges. As the root user, write this to `/etc/udev/rules.d/51-ACR122.rules` (this works on Ubuntu 10.10):
<pre>
SUBSYSTEM=="usb", SYSFS{idVendor}=="072f", SYSFS{idProduct}=="2200", MODE="0660", GROUP="plugdev"
</pre>

From Ubuntu 12.10 the correct settings for udev rules are:
<pre>
SUBSYSTEM=="usb", ATTR{idVendor}=="072f", ATTR{idProduct}=="2200", MODE="0660", GROUP="plugdev"
</pre>


### Windows
Not supported yet.

How to Create a New ofxNFCReader Project
-----------------------------------------

To develop your own project based on ofxNFCReader, simply copy the example project and rename it. You probably want to put it in your apps folder, for example, after copying:

`openFrameworks/addons/ofxNFCReader/example/ => openFrameworks/apps/myApps/example/`

Then after renaming:

`openFrameworks/apps/myApps/myKinectProject/`

### Mac (Xcode):

Rename the project in Xcode (do not rename the .xcodeproj file in Finder!): XCode Menu->Project->Rename (Xcode3) / Slow double click the project name and rename (Xcode4)

### Codeblocks (Win & Linux):

Close Codeblocks and rename the *.cbp and *.workspace files to the same name as the project folder. Open the workspace and readd the renamed project file.

### Windows (Visual Studio):

Close Visual Studio and rename the *.sln file. Open the solution, right click on the project in the project broswer and select "Rename ...".

Adding ofxNFCReader to an Existing Project
---------------------------------------

If you want to add ofxNFCReader to another project, you need to make sure you include the src folder and the :
<pre>
openFrameworks/addons/ofxNFCReader/src
</pre>
as well as search paths for the  libs (lbnfc, libusb) required by ofxNFCReader.


### Mac (Xcode):

In the Xcode project browser:

* add the ofxNFCReader sources to the project:
  * create a new group "ofxNFCReader"
  * drag these directories from ofxNFCReader into this new group: ofxNFCReader/src & ofxNFCReader/libs
* add a search path to the libusb headers: `../../../addons/ofxNFCReader/libs/libusb/include/libusb-1.0` to your project Target build settings
  * Xcode3: under Targets->YourApp->Build->Header Search Paths (make sure All Configurations and All Settings are selected) and add the path
  * Xcode4: add the lib path to your Project.xconfig, see the example
* add the path to the libusb precompiled library: `../../../addons/ofxNFCReader/libs/libusb/osx/libs/usb-1.0.a`
  * Xcode3: under Targets->YourApp->Build->Library Search Paths (make sure All Configurations and All Settings are selected) and add the path
  * Xcode4: add the lib path to your Project.xconfig, see the example
  
### Linux (Makefiles & Codeblocks):

Edit the Makefile config files:
 
* edit addons.make in your project folder and add the following line to the end of the file: 
	<pre>ofxNFCReader</pre>
* edit config.make in your project folder and change the lines for USER_LIBS to:
	<pre>
	USER_LIBS = -lusb
	</pre>

Notes
-----

### Using multiple kinects
Not supported yet.

Troubleshooting
---------------

If you see this in the console: 

`error	libnfc.driver.acr122_usb	Unable to claim USB interface (Permission denied)`

Just kill the processus like this:

`sudo launchctl list | grep pcscd`

`sudo kill -9 thePID`

Developing ofxNFCReader
--------------------

Feel free to log bug reports and issues to the ofxNFCReader Github page: https://github.com/soixantecircuits/ofxNFCReader/issues

If you wish to help in ofxNFCReader development, please do!


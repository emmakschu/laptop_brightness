# Laptop brightness utility

**Author:**  Michael K Schumacher (github: mkschu)
**Email:**  michael@mkschumacher.com

## Background

When running the Linux kernel on some laptops (e.g. my
ThinkPad with Intel CPU and PCI bridge, but AMD Radeon
graphics) the usual procedures for adjusting display
brightness with the appropriate keys do not work. The
only viable way to change the brightness is to modify
the temp file which stores the current display
brightness value. This program provides a CLI utility
to make that quicker and easier.

## Installation

1. Check the contents of /sys/class/backlight
    * If there is a directory intel_backlight, everything
	  should be set to work
    * If there is a different directory, you will need
	  to adjust the DIR_PATH in the preprocessor
	  definitions, then rebuild the binary with make build.
	  I also make no guarantee that this will work with
	  anything other than intel_backlight, as that is all
	  I have tested the program on yet

2. Rebuild the binary (if you modified the source). This
   can easily be done via the Makefile with the command
   <code>make build</code> while in this directory.

3. If you would like to copy the binary into /usr/local/bin,
   you can do so via the make file with
   <code>make install</code> (which needs to run as sudo/
   root). Otherwise you can always call the command with
   its full path where you have saved it, or add its 
   location to your $PATH variable in bashrc.

## Usage

**To check the current brightness**
Enter <code>$ brightness</code>

**To set the brightness to a specific value**
Enter <code># brightness set [value]</code>

**To increase the brightness by a given value**
Enter <code># brightness inc [value]</code>

**To decrease the brightness by a given value**
Enter <code># brightness dec [value]</code>

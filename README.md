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

* Check the contents of /sys/class/backlight

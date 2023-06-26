# blgmr

A simple and minimal backlight/brightness manager written in under 100 lines of C

## Usage
Example uses:
```sh
blmgr +5% # Increment brightness by 5%
blmgr -200 # Decrement brightness by 200
blmgr 50% # Set brightness to 50% of total
blmgr 1000 # Set brightness to value 1000
```

## Configuration
Remember to configure `BACKLIGHT_PATH_BASE` in blmgr.c
More information on that can be found [here](https://wiki.archlinux.org/title/Backlight#ACPI)

If you intend to run the program as an unprivileged user,
please refer to this the same archwiki article for instructions on setting up the necessary udev rules

## Installation
To install the program simply run:
```sh
sudo make install
```
This will install the program to `INSTALL_PATH` which defaults to the value `/usr/local/bin`

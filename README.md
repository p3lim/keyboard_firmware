# Keyboard Firmware

This is the firmware for my hand-wired keyboard, based on the fantastic [tmk keyboard library](//github.com/tmk/tmk_keyboard/tree/master/tmk_core).  

The keyboard runs on a [Teensy 2.0](http://www.pjrc.com/store/teensy.html) and has a couple of features such as multiple layers and macros.

Images and a buildlog of the keyboard can be found [here](//imgur.com/a/zwsDN).


### Developing

This requires linux and some tools, you can run this under WSL if you're on Windows by following [this guide](//gist.github.com/p3lim/7174909c78360606f3334bad4a0262f5)

Install dependencies for building:
```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install -y git make gcc-avr avr-libc
```

Clone repository:
```bash
git clone --recursive https://github.com/p3lim/keyboard_firmware
cd keyboard_firmware
```

Create firmware files:
```
make
```

To actually flash, install [Teensy Loader CLI](https://www.pjrc.com/teensy/loader_cli.html) then run this:
```
make teensy
```

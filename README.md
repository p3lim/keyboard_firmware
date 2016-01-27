# Keyboard Firmware

This it the firmware for my hand-wired keyboard, based on the fantastic [tmk keyboard library](https://github.com/tmk/tmk_core).  

The keyboard runs on a [Teensy 2.0](http://www.pjrc.com/store/teensy.html) and has a couple of features such as multiple layers and macros.

Images and buildlog of the keyboard can be found [here](https://imgur.com/a/zwsDN).


### Cloning, building & flashing

Since this repository has a submodule the cloning needs an additional argument to init and update the submodule.

```
git clone --recursive https://github.com/p3lim/keyboard_firmware
cd keyboard_firmware
make
make teensy
```

# Keyboard Firmware

This is the firmware for [Sentraq S60-X](https://www.massdrop.com/buy/14808), based on the fantastic [tmk keyboard library](https://github.com/tmk/tmk_core).  

The keyboard runs on a [Atmel ATMEGA32U4](http://www.atmel.com/devices/ATMEGA32U4.aspx) and has a couple of features such as multiple layers and macros.


### Cloning, building & flashing

Since this repository has a submodule the cloning needs an additional argument to init and update the submodule.

You'll also need [Atmel FLIP](http://www.atmel.com/tools/FLIP.aspx) to flash the firmware to the keyboard.

```
git clone --recursive https://github.com/p3lim/keyboard_firmware
cd keyboard_firmware
git checkout sentraq
make
make flip
```

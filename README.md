# Keyboard Firmware

This is the keyboard firmware for some of my keyboards, using [QMK](https://github.com/qmk/qmk_firmware#readme).

The repository is structured as such:
- `common` - [userspace](https://docs.qmk.fm/#/feature_userspace)
- `keyboards` - keyboard definitions/overrides
- `keymaps` - keyboard keymaps

## Setup

We'll use QMK's CLI to set up dependencies for us.

```bash
pip install --user qmk # or `nix-shell -p qmk`
```

### udev

To communicate with the bootloader on Linux we need extra privileges.  
See [the official documentation](https://docs.qmk.fm/#/faq_build?id=linux-udev-rules) on how to set this up, or run `make udev && reboot`.

Teensy also needs this, see [their udev rules](https://www.pjrc.com/teensy/00-teensy.rules).

### toolkit

To flash bface we'll need `bootloadHID`, install with `make bootloadhid`.

To flash p60 we'll need [Teensy Loader](https://www.pjrc.com/teensy/loader_cli.html):
```bash
apt install teensy-loader-cli # or `nix-shell -p teensy-loader-cli`
```

## Flashing

### p60

```bash
make p60 # optional
make p60_flash
```

Press <kbd>LSHIFT</kbd> + <kbd>RSHIFT</kbd> + <kbd>B</kbd> to enter the bootloader.

### bface

```bash
make bface # optional
make bface_flash
```

Hold <kbd>LCTRL</kbd> while connecting the keyboard to enter the bootloader.

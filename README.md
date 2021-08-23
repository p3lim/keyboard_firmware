# Keyboard Firmware

This is the keyboard firmware for some of my keyboards, using [QMK](https://github.com/qmk/qmk_firmware#readme).

The repository is structured as such:
- `common` - [userspace](https://docs.qmk.fm/#/feature_userspace)
- `keyboards` - keyboard definitions/overrides
- `keymaps` - keyboard keymaps

### Setup

We'll use QMK's CLI to set up dependencies for us, but we're not going to use their toolkit.

```bash
pip install --user qmk
qmk setup -y -H /tmp/qmk ; rm -rf /tmp/qmk
```

We'll also want [Teensy Loader](https://www.pjrc.com/teensy/loader_cli.html):
```bash
apt install teensy-loader-cli
```

#### udev

To communicate with the bootloader on Linux we need extra privileges.  
See [the official documentation](https://docs.qmk.fm/#/faq_build?id=linux-udev-rules) on how to set this up.

Teensy also needs this, see [their udev rules](https://www.pjrc.com/teensy/00-teensy.rules).

### Flashing

#### p60

```bash
make p60
```

Press <kbd>LSHIFT</kbd> + <kbd>RSHIFT</kbd> + <kbd>B</kbd> to enter bootloader, then use [Teensy Loader](//www.pjrc.com/teensy/loader.html) to flash using the `hex/p60.hex` file.

#### bface

```bash
make bface # optional
make bface_flash
```

Hold <kbd>LCTRL</kbd> while connecting the keyboard to flash.

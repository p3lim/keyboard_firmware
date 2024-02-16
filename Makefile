setup: qmk

qmk:
	qmk setup -y -H $(PWD)/qmk_firmware

link: clean
	# userspace
	ln -rfs common qmk_firmware/users/custom
	# p60
	mkdir -p keyboards/p60/keymaps
	ln -rfs keymaps/p60 keyboards/p60/keymaps/custom
	ln -rfs keyboards/p60 qmk_firmware/keyboards/p60
	# bface
	ln -rfs keymaps/bface qmk_firmware/keyboards/winkeyless/bface/keymaps/custom
	ln -rfs keyboards/bface/bface.h qmk_firmware/keyboards/winkeyless/bface/bface.h

clean:
	make -C qmk_firmware clean
	git -C qmk_firmware reset --hard
	git -C qmk_firmware clean -df
	rm -rf keyboards/p60/keymaps

p60: setup link p60_build clean

p60_flash: setup link p60_build_flash clean

p60_build:
	make -C qmk_firmware p60:custom
	mkdir -p hex
	cp qmk_firmware/.build/p60_custom.hex hex/p60.hex

p60_build_flash:
	make -C qmk_firmware p60:custom:flash

bface: setup link bface_build clean

bface_flash: setup link bface_build_flash clean

bface_build_flash:
	make -C qmk_firmware winkeyless/bface:custom:flash

bface_build:
	make -C qmk_firmware winkeyless/bface:custom
	mkdir -p hex
	cp qmk_firmware/.build/winkeyless_bface_custom.hex hex/bface.hex

bootloadhid: udev
	sudo apt install -y libusb-dev gcc make
	curl -sSL https://www.obdev.at/downloads/vusb/bootloadHID.2012-12-08.tar.gz | tar -xz -C /tmp
	make -C /tmp/bootloadHID.2012-12-08/commandline
	sudo cp /tmp/bootloadHID.2012-12-08/commandline/bootloadHID /usr/local/bin/
	rm -rf /tmp/bootloadHID.2012-12-08

udev:
	sudo cp qmk_firmware/util/udev/50-qmk.rules /etc/udev/rules.d/

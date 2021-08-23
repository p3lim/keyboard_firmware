setup: qmk

qmk:
	git submodule update --init --recursive

link:
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
	rm -rf keyboards/p60/keymaps

p60: setup link p60_build clean

p60_flash: setup link p60_build_flash clean

p60_build:
	make -C qmk_firmware p60:custom
	mkdir -p hex
	cp qmk_firmware/.build/p60_custom.hex hex/p60.hex

p60_build_flash: p60_build
	teensy_loader_cli --mcu=TEENSY2 -w -v qmk_firmware/.build/p60_custom.hex

bface: setup link bface_build clean

bface_flash: setup link bface_build_flash clean

bface_build_flash:
	make -C qmk_firmware winkeyless/bface:custom:flash

bface_build:
	make -C qmk_firmware winkeyless/bface:custom
	mkdir -p hex
	cp qmk_firmware/.build/winkeyless_bface_custom.hex hex/bface.hex

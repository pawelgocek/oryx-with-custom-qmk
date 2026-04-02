QMK_HOME := $(HOME)/qmk_firmware
KEYBOARD := zsa/voyager
KEYMAP := 3WNoB
KEYMAP_DIR := $(QMK_HOME)/keyboards/$(KEYBOARD)/keymaps/$(KEYMAP)

.PHONY: help build flash clean link unlink oryx-fetch oryx-merge oryx-build draw

help:
	@echo "Usage: make <target>"
	@echo ""
	@echo "  build        Compile firmware"
	@echo "  flash        Compile + flash (enter bootloader first)"
	@echo "  clean        Remove build artifacts"
	@echo ""
	@echo "  oryx-build   Fetch from Oryx + merge + build (full pipeline)"
	@echo "  oryx-fetch   Download latest layout from Oryx → oryx branch"
	@echo "  oryx-merge   Merge oryx branch into current branch"
	@echo ""
	@echo "  draw         Generate and open SVG layout diagram"
	@echo ""
	@echo "  link         Symlink keymap into qmk_firmware"
	@echo "  unlink       Remove symlink"

build: link
	cd $(QMK_HOME) && make $(KEYBOARD):$(KEYMAP)

flash: link
	cd $(QMK_HOME) && make $(KEYBOARD):$(KEYMAP):flash

link:
	@if [ ! -L "$(KEYMAP_DIR)" ]; then \
		ln -s $(CURDIR)/$(KEYMAP) $(KEYMAP_DIR); \
		echo "Symlinked $(KEYMAP) → $(KEYMAP_DIR)"; \
	fi

unlink:
	@if [ -L "$(KEYMAP_DIR)" ]; then \
		rm $(KEYMAP_DIR); \
		echo "Removed symlink $(KEYMAP_DIR)"; \
	fi

clean:
	cd $(QMK_HOME) && make $(KEYBOARD):$(KEYMAP):clean

draw:
	./scripts/draw-layout.sh

oryx-build: oryx-fetch oryx-merge build

oryx-fetch:
	./scripts/oryx-fetch.sh

oryx-merge:
	git merge oryx

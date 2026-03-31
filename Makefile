.PHONY: init build-nucleo flash build-native run clean

init:
	west init -l
	west update
	west sdk install
	west zephyr-export

build-nucleo:
	west build -p always -b nucleo_f411re app

flash: build-nucleo
	west flash --runner openocd

build-native:
	west build -p always -b native_sim app

run: build-native
	./build/zephyr/zephyr.exe

clean:
	rm -rf build

all: init build-nucleo flash

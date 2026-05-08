.PHONY: init build-nucleo flash build-native run clean build-de-cero flash-de-cero debug-de-cero gdbserver-de-cero

init:
	west init -l
	west update
	west sdk install
	west zephyr-export

build-nucleo:
	west build -p always -b nucleo_f411re app

build-de-cero:
	west build -p always -b de_cero app

flash: build-nucleo
	west flash --runner openocd

flash-de-cero: build-de-cero
	west flash --runner openocd

debug-de-cero: build-de-cero
	west debug --runner openocd

gdbserver-de-cero:
	west debugserver --runner openocd --build-dir build

build-native:
	west build -p always -b native_sim app

run: build-native
	./build/zephyr/zephyr.exe

clean:
	rm -rf build

all: init build-nucleo flash

# Installing falshing and cross compilers for tm4123gh6pm

* [step by step guide](https://www.hackster.io/tcss/upload-code-to-ti-tm4c123-using-linux-cmake-and-lm4tools-c33cec)

* [lm4tools flashing tool](https://github.com/utzig/lm4tools)

## 1.istalling arm-none-ebi [reource](https://askubuntu.com/questions/1243252/how-to-install-arm-none-eabi-gdb-on-ubuntu-20-04-lts-focal-fossa)

* download the tool chain from [arm download page](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)  

* Extract it in `/user/share` 
    ```
    sudo tar xjf gcc-arm-none-eabi-your-version.bz2 -C /usr/share/
    ```

* export `bin` of the tool chain in order to use it
```
export PATH=$PATH:/usr/share/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin
```
* test 
 ```
arm-none-eabi-gcc --version
arm-none-eabi-g++ --version
arm-none-eabi-gdb --version
arm-none-eabi-size --version

 ```

## 2. install libusb
```
sudo apt-get install libusb-dev
```

## 3. flashing 
using this [example](https://github.com/yusefkarim/cmake-tm4c-blinky)

```
cd ~/tiva-projects
git clone https://github.com/yusef-karim/cmake-tm4c-blinky.git
cd cmake-tm4c-blinky
```

to flash the code:

```
mkdir build
cd build
cmake ..
make
sudo env PATH=$PATH make flash
```

## Solving a bug with gdb: arm-none-eabi-gdb: error while loading shared libraries: libpython3.6m.so.1.0: cannot open shared object file: No such file or directory

* The library is a subset of package `libpython3.6` as the [link](https://packages.ubuntu.com/search?searchon=contents&keywords=libpython3&mode=filename&suite=artful&arch=amd64) shows

* but we have the newes version `python3.9` we need to install the old one form and archived reposatory thanks to [solution](https://stackoverflow.com/questions/43621584/why-cant-i-install-python3-6-dev-on-ubuntu16-04)

    ```
    sudo add-apt-repository ppa:deadsnakes/ppa
    sudo apt-get update
    sudo apt-get install python3.6
    ```
* we will find the `libpython3.6m.so.1.0` in `/usr/lib/x86_64-linux-gnu/libpython3.6m.so.1.0` finally



# Debuging with [openocd](https://openocd.org/)  and arm-none-eabid-gdb [resource](https://esplatforms.blogspot.com/2014/07/armarm-toolchain-openpocd-lm4flash.html)

## Install openocd 
```
cd ~/tiva_projects
git clone http://git.code.sf.net/p/openocd/code openocd
sudo apt-get install autoconf automake texinfo
./bootstrap
./configure --enable-maintainer-mode --enable-ti-icdi
make
sudo make install
```

installation log: 
```
[sudo] password for abdullah:
make  install-recursive
make[1]: Entering directory '/home/abdullah/tiva-projects/openocd'
Making install in jimtcl
make[2]: Entering directory '/home/abdullah/tiva-projects/openocd/jimtcl'
make[2]: Nothing to be done for 'install'.
make[2]: Leaving directory '/home/abdullah/tiva-projects/openocd/jimtcl'
Making install in src/jtag/drivers/libjaylink
make[2]: Entering directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink'
Making install in libjaylink
make[3]: Entering directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink/libjaylink'
make[4]: Entering directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink/libjaylink'
make[4]: Leaving directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink/libjaylink'
make[3]: Leaving directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink/libjaylink'
make[3]: Entering directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink'
make[4]: Entering directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink'
make[4]: Nothing to be done for 'install-exec-am'.
make[4]: Leaving directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink'
make[3]: Leaving directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink'
make[2]: Leaving directory '/home/abdullah/tiva-projects/openocd/src/jtag/drivers/libjaylink'
make[2]: Entering directory '/home/abdullah/tiva-projects/openocd'
make[3]: Entering directory '/home/abdullah/tiva-projects/openocd'
 /bin/mkdir -p '/usr/local/bin'
  /bin/bash ./libtool   --mode=install /usr/bin/install -c src/openocd '/usr/local/bin'
libtool: install: /usr/bin/install -c src/openocd /usr/local/bin/openocd
 /bin/mkdir -p '/usr/local/share/openocd/OpenULINK'
 /usr/bin/install -c -m 644 src/jtag/drivers/OpenULINK/ulink_firmware.hex '/usr/local/share/openocd/OpenULINK'
 /bin/mkdir -p '/usr/local/share/info'
 /usr/bin/install -c -m 644 ./doc/openocd.info ./doc/openocd.info-1 ./doc/openocd.info-2 '/usr/local/share/info'
 install-info --info-dir='/usr/local/share/info' '/usr/local/share/info/openocd.info'
 /bin/mkdir -p '/usr/local/share/man/man1'
 /usr/bin/install -c -m 644 doc/openocd.1 '/usr/local/share/man/man1'
 /bin/mkdir -p '/usr/local/share/openocd'
 /bin/mkdir -p '/usr/local/share/openocd/contrib'
 /usr/bin/install -c -m 644  contrib/60-openocd.rules '/usr/local/share/openocd/contrib'
 /bin/mkdir -p '/usr/local/share/openocd/contrib/libdcc'
 /usr/bin/install -c -m 644  contrib/libdcc/dcc_stdio.c contrib/libdcc/dcc_stdio.h contrib/libdcc/example.c contrib/libdcc/README '/usr/local/share/openocd/contrib/libdcc'
make  install-data-hook
make[4]: Entering directory '/home/abdullah/tiva-projects/openocd'
for i in $(find ./tcl -name '*.cfg' -o -name '*.tcl' -o -name '*.txt' | sed -e 's,^./tcl,,'); do \
	j="/usr/local/share/openocd/scripts/$i" && \
	mkdir -p "$(dirname $j)" && \
	/usr/bin/install -c -m 644 ./tcl/$i $j; \
done
make[4]: Leaving directory '/home/abdullah/tiva-projects/openocd'
make[3]: Leaving directory '/home/abdullah/tiva-projects/openocd'
make[2]: Leaving directory '/home/abdullah/tiva-projects/openocd'
make[1]: Leaving directory '/home/abdullah/tiva-projects/openocd'
```

## Debug with openocd

we need to run openocd with the configuration file that matches our board
```
cd /usr/local/share/openocd/scripts/board
openocd -f ti_ek-tm4c123gxl.cfg
```
openocd will open a debug port 3333 in order to connect `arm-none-eabi-gdb` on it
```
cd "to your project binary file"
arm-none-eabi-gdb "binary_file.axf or .ulf"
tar ext :3333  #connect gdb to openocd on port 3333
monnitor reset halt # reset the processor
load #load the binary file
c # continue into the file 
```
ctl C to terminate  the continu section (exiting while(1) loop) 

to read a register 
```
x/wx 0x20000000U 
```

to disassemble a function
```
disas delay // disasseble funciton delay
```

### Using [openocd commands](https://openocd.org/doc/html/General-Commands.html) inside gdb

we use command `monitor` to use any openocd command inside gdb

* to write to a register
```
monitor write_memory 0x20000000 32 {0x00230500}
```
writes `0x00230500` inside address `0x20000000 `


* to view processor registers

```
monitor reg
```
output: 
```
===== arm v7m registers
(0) r0 (/32): 0x20000000
(1) r1 (/32): 0x00000428
(2) r2 (/32): 0x00000000
(3) r3 (/32): 0x00000000
(4) r4 (/32): 0x00000000
(5) r5 (/32): 0x00000000
(6) r6 (/32): 0x00000000
(7) r7 (/32): 0x00000000
(8) r8 (/32): 0x00000000
(9) r9 (/32): 0x00000000
(10) r10 (/32): 0x00000000
(11) r11 (/32): 0x00000000
(12) r12 (/32): 0x20000000
(13) sp (/32): 0x200000f8
(14) lr (/32): 0x000002b5
(15) pc (/32): 0x000002b4
(16) xPSR (/32): 0x61000000
(17) msp (/32): 0x200000f8
(18) psp (/32): 0x00000000
(20) primask (/1): 0x00
(21) basepri (/8): 0x00
(22) faultmask (/1): 0x00
(23) control (/3): 0x00
(42) d0 (/64): 0x0000000000000000
(43) d1 (/64): 0x0000000000000000
(44) d2 (/64): 0x0000000000000000
(45) d3 (/64): 0x0000000000000000
(46) d4 (/64): 0x0000000000000000
(47) d5 (/64): 0x0000000000000000
(48) d6 (/64): 0x0000000000000000
(49) d7 (/64): 0x0000000000000000
(50) d8 (/64): 0x0000000000000000
(51) d9 (/64): 0x0000000000000000
(52) d10 (/64): 0x0000000000000000
(53) d11 (/64): 0x0000000000000000
(54) d12 (/64): 0x0000000000000000
(55) d13 (/64): 0x0000000000000000
(56) d14 (/64): 0x0000000000000000
(57) d15 (/64): 0x0000000000000000
(58) fpscr (/32): 0x00000000
===== Cortex-M DWT registers
```

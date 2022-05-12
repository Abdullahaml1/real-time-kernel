# FreeRTOS with two timers

This project is based on `arm-none-eabi` tool chain and `TI Tivaware APIs`, and `CMake` and was built on Linux machine. We used `[openocd](https://openocd.org/)` and `arm-none-eabi-gdb` for debugging. The detailed describtion how to use the debugger is [here](../README.md)

## Project Description 

We have 4 tasks:
* vStartTimersTask for starting the timers
* vHandlerTask0 for Timer0B
* vHandlerTask1 for Timer1B
* vPortSVCHandler

and two periodic timers:
* Timer0B
* Timer1B

The timers period are faster than the Systick, so I edited the timers ISR to switch context ever 255 timer tick, then every timer will call its handler


## Compiling the project
```
mkdir build
cd build
cmake ..
make
```

The executable will be in `freertos_interrupts_more.elf`

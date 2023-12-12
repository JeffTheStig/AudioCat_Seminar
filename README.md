# AudioCat_Seminar
This repo provides the code base for the Audiocat project performed as part of the Advanced Practical IoT and Seminar from the Master Computer Science at the TU Delft, 2023.

## Structure
The repo contains 5 different projects. The different project are outlined here.

### AudioCat
Contains the STM32Cube project setup for the actual hardware. This can be opened, compiled and flashed using the STM32CubeIDE. Note that this project does not work. Only UART functions as intended.
It is possible that the SD code does work when the SD_FET_EN pin is wired to ground (set the GPIO pin to open_drain and pull it low), but this is untested.

### AudioCat_old
Old project code. Setup for the NUCLEO_U5A9ZJ development board. Setup with the STM32Cube framework. This can be opened, compiled and flashed using the STM32CubeIDE. This project was only used to test the microphone output and was later merged with the STM32-SDCard project.

### STM32-SDCard
Setup for the NUCLEO_U5A9ZJ development board. Setup with the STM32Cube framework. This can be opened, compiled and flashed using the STM32CubeIDE. This project contains code to read the microphone and then store the readings on the SD card in WAV format. SD communication goes over an SPI interface.

### Audiocat_PlatformIO_base
Setup for the Nucleo_U5A9ZJ development board. Setup with the Arduino framework using PlatformIO. This can be opened and compiled using the PlatformIO extension in VSCode. 

To flash the firmware to a chip, locate the compiled firmware in the .pio/build folder and run the following command:
```STM32_Programmer_CLI -c port=SWD freq=4000 -w ./firmware.elf```
In case of windows, you might have to replace `STM32_Programmer_CLI` with `STM32_Programmer_CLI.exe`.

This project also contains both variants for the Nucleo_U5A9ZJ and the AudioCat hardware. To switch between targets, change the following variable in the platformio.ini
```
board = AudioCatBoard  ; To target actual hardware
board = NUCLEO_U5A5ZJ ; To target the nucleo board
```

If you want to start a new with these variants, copy the project and replace the main.cpp file with a clean main.cpp file (include arduino.h and create two functions setup and loop with no arguments).

### AudiocatDataAnalyzer
This is a project written in Python used to analyze recordings. The Audiocat (dev)board will produce two separate files per recording: a JSN and a WAV file. The AudiocatDataAnalyzer project can load a folder with these files and show the sensor data in the JSN file and playback the file in the WAV file. It can also run the WAV file through Birdnet and give the user a prediction on the bird(s) that is/are recorded.

To install the dependencies, install the conda environment (https://anaconda.org/) bundled with the project by running the following commands:
```
conda env create -f environment.yml
conda activate audiocat
```

After this, the program can be started as follows:
```python main.py```

For more info, refer to the README in the AudiocatDataAnalyzer folder.

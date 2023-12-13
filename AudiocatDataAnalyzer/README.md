# AudiocatDataAnalyzer
This is a project written in Python used to analyze recordings. The Audiocat (dev)board will produce two separate files per recording: a JSN and a WAV file. The AudiocatDataAnalyzer project can load a folder with these files and show the sensor data in the JSN file and playback the file in the WAV file. It can also run the WAV file through Birdnet and give the user a prediction on the bird(s) that is/are recorded.

## Dependencies
The program has three main dependencies:
```
PySimpleGUI
birdnetlib
python-vlc
```

Refer to the section Installation on how to install them.

## Installation
To install the dependencies, install the conda environment (https://anaconda.org/) bundled with the project by running the following commands:
```
conda env create -f environment.yml
conda activate audiocat
```

It is also possible to install the dependencies manually. To do so, first follow the steps at the following link to install all dependencies for birdnetlib
https://github.com/kahst/BirdNET-Analyzer#setup

Next install all dependencies using pip:

```
pip install PySimpleGui python-vlc birdnetlib
```

## Run
To run the program, run the following command:
```python main.py```

The first start up can take a little while since it has to setup the tensorflow models. Just patiently wait for the program to start.
The same holds for the first analyzes. The program will seem unresponsive, but just let it run until it comes with a prediction. After the first prediction, other prediction will be performed way faster, even after restarting the program.

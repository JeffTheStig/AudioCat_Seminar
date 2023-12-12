"""
User interface of the face morph program
"""

import os
import PySimpleGUI as sg
import json
import vlc

from birdnetlib import Recording
from birdnetlib.analyzer import Analyzer
from datetime import datetime


def main_gui():
    """
    Main function for the UI of the data analyzer.
    Creates the window and acts accordingly on mouse clicks.
    """

    # Layout for the column for the file explorer.
    layout_file_explorer = [
        [sg.Text("Folder selection: ", size=(60,1), justification="center")],
        [sg.Input(size=(25, 1), enable_events=True, key="-DATA-FOLDER-PATH-"), sg.FolderBrowse(button_text="Select Folder")],
        [sg.Text("Files", size=(60,1), justification="center")],
        [sg.Listbox([], size=(60, 50), key='-FILES-', enable_events=True)]
    ]
    # Layout for the column of data.
    layout_data = [
        [sg.Text("Name", size=(60,1), justification="center")],
        [sg.Text("---", size=(60,1), justification="center", key="-FILENAME-")],
        [sg.HSeparator()],
        [sg.Text("Audio", size=(60,1), justification="center")],
        [sg.Button("Play", key="-PLAY-AUDIO-")],
        [sg.HSeparator()],
        [sg.Text("Data", size=(60,1), justification="center")],
        [sg.Listbox([], size=(60, 15), key='-DATA-')],
        [sg.HSeparator()],
        [sg.Text("Birdnet", size=(60,1), justification="center")],
        [sg.Button("Analyze", key="-BIRDNET-ANALYZE-")],
        [sg.Listbox([], size=(60, 25), key='-BIRDNET-DATA-')]

    ]

    # Total layout of the program. Also adds a terminal output window.
    layout = [
        [
            sg.Column(layout_file_explorer),
            sg.VSeparator(),
            sg.Column(layout_data),
        ],
    ]


    folder_path = ""
    current_file = ""
    current_data_file = ""
    audio_player = vlc.MediaPlayer()
    # media = vlc.Media("")
    player_ready = False
    analyzer = Analyzer()

    # Create the window.
    window = sg.Window("Audiocat Analysis tool", layout, resizable=True, finalize=True)

    # Initialize all necessary variables
    # UI event loop. Acts on events (button presses etc...)
    while True:
        # Load events and values.
        event, values = window.read(timeout=20)

        # Close if event is exit.
        if event == "Exit" or event == sg.WINDOW_CLOSED:
            break

        if event == "-DATA-FOLDER-PATH-":
            p = values["-DATA-FOLDER-PATH-"]
            if os.path.isdir(p):
                print("Loading folder")
                folder_path = p
                files = [f for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f)) and os.path.splitext(f)[1].lower() == ".wav"]
                window["-FILES-"].update(files)

        if event == "-FILES-":
            current_file = values["-FILES-"][0]
            window["-FILENAME-"].update(current_file)
            player_ready = True

            current_data_file = current_file.replace("R", "D", 1).replace("WAV", "JSN")
            print(current_data_file)
            data_path = os.path.join(folder_path, current_data_file)
            if os.path.isfile(data_path):
                f = open(data_path, "r")
                j_obj = json.load(f)
                dat = ["Null"]
                if j_obj != None:
                    dat = [f"{k}: {v}" for k,v in j_obj.items()]
                window["-DATA-"].update(dat)
            
            window["-BIRDNET-DATA-"].update([])
        if event == "-PLAY-AUDIO-" and player_ready:
            # media = audio_player.get_media()
            media = vlc.Media(os.path.join(folder_path, current_file))
            audio_player.set_media(media)
            audio_player.play()
            # audio_player.set_media(media)
        if event == "-BIRDNET-ANALYZE-" and player_ready:
            recording = Recording (
                analyzer,
                os.path.join(folder_path, current_file),
                min_conf=0.1,
            )
            recording.analyze()
            pred = recording.detections
            print(pred)
            dat = []
            if pred:
                for i, bird in enumerate(pred):
                    line = [f"\t{k}: {v}" for k,v in bird.items()]
                    line.insert(0, f"Prediction {i}")
                    dat = dat + line
            else:
                dat = ["Nothing found..."]
            window["-BIRDNET-DATA-"].update(dat)




            
    # When broken out of loop, close window
    window.close()


if __name__ == "__main__":
    main_gui()
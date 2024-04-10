# Nixie tube clock live wallpaper
- Inspired by the divergence meter in Steins;Gate
- Written in c++ for good performance (Not sure if the performance can be called good though. It uses only about 18mb of RAM, but CPU usage is relatively high. But not as high as one similar program that I tried.)
- Made for Linux (Works best using the Gnome DE.) - Windows stuff is commented, so uncommenting and editing it a little you could make it work on Windows.

There are some bugs that I am aware of, but too lazy to fix them. If you use this and feel like fixing them, you are welcome to do so.

The images are not mine, I got them from here: https://github.com/MKSanic/divergence-meter


## How to use it

### 1. Requirements
- Operating System: Linux
- Desktop Environment: Gnome. (Cinnamon also works somehow, but there is flickering.)
- libgraphicsmagick++-q16-12 package? (sudo apt install libgraphicsmagick++-q16-12)

### 2. Run it

Double-click the nixie-clock file.

(*Alternative way 1:* Right click the file named nixie-clock and select "execute". *Alternative way 2:* open the terminal in the folder of the program and write ./nixie-clock

You might need to right click, select "Properties", go to "Permissions" tab and enable "Allow executing file as program"

### 2. Set it as a Startup app

Open Startup Applications Preferences app.
Add a new one and search for the nixie-clock program.

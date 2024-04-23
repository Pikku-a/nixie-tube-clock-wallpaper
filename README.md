# Nixie tube clock live wallpaper
![Gif of the wallpaper in action.](https://github.com/Pikku-a/nixie-tube-clock-wallpaper/blob/master/nixie-clock-wallpaper.gif?raw=true)

- Inspired by the divergence meter in Steins;Gate
- Written in c++ for good performance (Not sure if the performance can be called good though. It uses only about 18mb of RAM, but CPU usage is relatively high. But not as high as one similar program that I tried.)
- Made for Linux (Gnome DE) - Windows stuff is commented, so uncommenting and editing it a little you could make it work on Windows.

There are some bugs that I am aware of, but too lazy to fix them. If you use this and feel like fixing them, you are welcome to do so.

The images are not mine, I got them from here: https://github.com/MKSanic/divergence-meter


## How to use it

### 1. Requirements
- Operating System: Linux
- Desktop Environment: Gnome.
- libgraphicsmagick++-q16-12 package (`sudo apt install libgraphicsmagick++-q16-12`)

### 2. Run it

Double-click the nixie-clock file.

You might need to right click, select "Properties", go to "Permissions" tab and enable "Allow executing file as program"

### 3. Set it as a Startup app (optional)

Open Startup Applications Preferences app.
Add a new one and search for the nixie-clock program.


## To do
- Make it work in dark gnome theme too
- Fix the 0s thing
- KDE support
- Windows support

# cob-taylor-games
This is the program for one of the two touchscreens in the UA Taylor Institute video wall. It contains some minigames relating to The University of Akron, Taylor Institute, and marketing. This project is coded in C++ and QML using the Qt 6 GUI library and the Qt Creator IDE.

<img src="https://github.com/dylondark/cob-taylor-games/assets/126813495/ade5947c-e088-4633-8e2c-b0dea4e4354c" width="400">

## Games List
There are/will be 6 minigames:
-  UA Trivia
-  Guess the Logo
-  Checkers
-  Zippy Hopper
-  Pong
-  Tetris

## Dev Setup
### Qt
Qt runs on Windows, Mac, and Linux. Therefore you can use any for development (although Linux will be the most accurate, see Target System Information).
-  To install qt creator on your desktop, go to https://www.qt.io/download
-  Then click Download Open Source, after clicking Download Open Source scroll down and locate Download the Qt Online Installer. Then, choose which installer you need.
-  After downloading the installer, you may or may not need to create an account to log in, then follow the next step on the screen.
-  In the select components window, choose whatever latest version of Qt 6.
-  Then follow the next couple of steps to start installing and wait, then you’re done.
### Project Dependencies
-  Make sure to install all fonts in "projectfonts" folder

## File Setup
The games require the proper files and file structure present or else they will not work correctly (if at all). All game files are expected to be in a folder called "gamefiles" in the same folder as the project executable. In this directory, the files for each game are in their own subdirectory, named after their respective game (for example: "trivia"). By default, when building from Qt Creator, the project executable will be located in a folder called something like "build-cob-taylor-games-Desktop-Debug", located in the same directory as the project folder "cob-taylor-games" (so, one directory up from inside the project folder). Below is a screenshot of the directory structure.

![image](https://github.com/dylondark/cob-taylor-games/assets/126813495/0976d1f1-2916-480b-a6cc-77b194afa821)

## Deployment
### Target System Information
This program is meant to run on a PC box connected to one of the touchscreens in the Taylor institute. The touchscreen resolution is **2160x3840 (portrait 4K)** and the box is running **Debian Linux 12**. Note that this is just the environment that the program is intended to run in, but it can run with other resolutions/operating systems for development. 
### Deploying on Target System
Instructions coming soon!
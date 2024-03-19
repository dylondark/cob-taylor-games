# Project Style Standards
This document contains a list of style, syntax and organizational standards for this project. It is expected that everyone working on the project will follow these standards, and these standards will be retroactively applied to everything that they concern, where possible.


## Official Game Names
These are the exact strings that are to be used to refer to the games in the project in things like the file and folder names and code (where possible). For example, in the main game enum in utilities.h or the "strName" properties of the game QML files.
- "Trivia"
- "GuessTheLogo"
- "Tetroos"
- "Checkers"
- "Hopper"
- "Pong"


## Git
### General Good Practices
### Commit Good Practices
### Commit Messages


## File Structure
There should be no duplicate files, and no files that are currently unused with no plans to ever be used.

### Folders
No folder should contain anything other than what is specified here. The naming scheme of files and subfolders within a folder should be consistent.
- **menufiles** - Contains all image files and their respective GIMP .xcf projects for the main menu. Should contain subfolders for menu images and background icons. GIMP project files should go in the same folder as their image exports.
- **forms** - Contains Qt Widgets forms (.ui).
- **gamefiles** - Contains data that the program reads in for the games. This folder is meant to contain the official data to be used with the program. The structure of this folder should be the exact same as what the program expects, so that you can simply copy this entire folder into the build folder to get all the data for the games to work. This folder should only contain subfolders for each game, and those subfolders should be named in accordance with the official game names.
- **include** - Contains C++ header files (.h).
- **leaderboard** - Contains data that the program reads in for the leaderboard. Since the program will generate its own leaderboard data, this folder is only meant to contain sample data to demonstrate the structure of the leaderboard files.
- **profanitycheck** - Contains data relevant to the profanity-checking system for usernames. Like the gamefiles folder, this folder should be able to be directly copied into the build folder for use in the program.
- **projectfonts** - Contains files for fonts used in the program.
- **qml** - Contains QML files (.qml).
- **src** - Contains C++ implementation files (.cpp).

### Game Data Files
The main data files for the games should be in comma-separated values (.csv) format. Images used by the game in image folders should not be buried in any more subfolders than absolutely necessary, but image folders can contain an "unedited" folder for original images.
- **Trivia**
  - Trivia.csv should contain columns: "question" (string) for the question text, "correct" (integer 1-4) for the correct answer number, "ans1" through "ans4" (string) containing the text for the answer buttons, and "img" containing the filename **(not entire path)** of the image file to use for the question.
  - Trivia subfolder in gamefiles should contain folder "images" containing all of the image files for the questions. Image files should be named "img(number).jpg" with the number representing the question number of the image (the line number of the question in the csv file minus 1 for the column header row). Ex: img43.jpg
  - Images should be in 4:3 aspect ratio, jpg format. Transparent background should be filled in with solid white.
- **GuessTheLogo**
  - GuessTheLogo.csv should contain all of the same columns as Trivia.csv, with the column "questionType" (integer 1-2) added on the end denoting the type of the question (1 for guess-the-company questions and 2 for guess-the-timeperiod questions).
  - GuessTheLogo subfolder in gamefiles should contain folders "type1" and "type2" for images belonging to question type 1 and 2 respectively.
    - Images for question type 1 should be named (company)(number).jpg. Increment number if there is more than one logo for a certain company. Ex: AirControl1.jpg
    - Images for question type 2 should be named (company)(daterange).jpg. Ex: Cat1931-1939.jpg
  - Images should be in 4:3 aspect ratio, jpg format. Transparent background should be filled in with solid white.


## C++
### Syntax
### Naming
### Comments & Documentation


## QML
### Syntax
### Naming
### Comments & Documentation


## QMake File


## Resource File

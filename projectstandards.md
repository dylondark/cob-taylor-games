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
### Commit Good Practices
- **Always pull when you begin working and push when you finish!**
- Commits should be *finished*, meaning that the commit should fully implement the change that it is for with nothing left to do.
- The changes in a commit should have a *singular* purpose or be related to a singular purpose. For example, "Trivia: fix file load issue" has a singular purpose, while "Trivia: fix file load issue and implement question shuffling" does not have a singular purpose.
- Try to make sure that commits do not break anything (that they aren't supposed to). If the project is supposed to build after a change, it should. It should also work properly.
- If commit something and then realize you need to change that commit, you can amend the last commit with the "Amend Last Commit" button in the Git menu in Qt Creator. However, this will only change the last commit.
### Commit Messages
- Commit messages should be in *present tense*. For example "Trivia: fix file load issue" rather than "Trivia: fixed file load issue".
- The first line of a commit message should be a *short sentence* describing *objectively* what the commit is for. Extra details, information, or opinions should go on the following lines.
- Commits that encompass changes on a particular system should be shortened with a prefix for that system. For example, instead of "Fix file load error in triviacontroller.cpp" it should be "Trivia: fix file load error". Commits that don't fit into any one prefix don't need a prefix.
- System prefixes:
  - **Trivia** - triviacontroller.h, triviacontroller.cpp, TriviaGame.qml, data files
  - **GTL** - guessthelogocontroller.h, triviacontroller.cpp, GuessTheLogoGame.qml, data files
  - **Tetroos** - tetrooscontroller.h, tetrooscontroller.cpp, TetroosGame.qml, data files
  - **Checkers** - checkerscontroller.h, checkerscontroller.cpp, CheckersGame.qml, data files
  - **Hopper** - hoppercontroller.h, hoppercontroller.cpp, HopperGame.qml, data files
  - **Pong** - pongcontroller.h, pongcontroller.cpp, PongGame.qml, data files
  - **MainWindow** - mainwindow.h, mainwindow.cpp, mainwindow.ui
  - **Leaderboard** - leaderboardhandler.h, leaderboardhandler.cpp
  - **ProfanityCheck** - profanitychecker.h, profanitychecker.cpp, anything in profanity folder
  - **BgWidget** - bgwidget.h, bgwidget.cpp, imgqueue.h, imgqueue.cpp
  - **DebugLabel** - debuglabel.h, debuglabel.cpp, anything in cob-taylor-games.pro concerning debug label
  - **Feedback** - feedbackcontroller.h, feedbackcontroller.cpp, Feedback.qml
  - **Menu** - MenuBase.qml
  - **GameOver** - GameOverBase.qml
  - **HomeBar** - HomeBarBase.qml
  - **Resources** - resources.qrc (anything changed in the Resources tab in Qt Creator)


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

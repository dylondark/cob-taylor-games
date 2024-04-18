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
- Curly brackets on separate lines (Allman style).
- Indentation with 4 spaces (Qt Creator default).
- Parameters in functions should always be passed as *const reference* rather than by value, unless they are basic types like `int` or `double` (`std::string` is *not* a basic type).
- No compiler warnings.
- Don't use curly brackets in if statements and loops that are only one line.
- "using namespace std" is *not* okay, but `using std::string` or any other object within a namespace is fine as long as there are no conflicts.
- Single empty lines separating blocks. This includes:
  - Blocks of code
  - Blocks of include statements
  - Blocks of using statements
  - Blocks of pragma statements (statements that start with # other than include statements, like `#ifndef`, `#define`, etc)
- Single empty lines separating function declarations and definitions.
- Code lines that have a singular purpose within functions should be separated into chunks (separated by lines).
- Functions that have similar purposes should be grouped together (for example: `on_lbGame1_pressed()`, `on_lb_Game2_pressed()`, etc. should be placed next to each other).
- Functions that are numbered should be in order (for example: `on_lbGame2_pressed()` should come after `on_lbGame1_pressed()`).
- Parameters in function definitions should be named, and they should be the same names as in the definition.
- Line comments should start with a space unless they are used for commenting out code.
  - `// this is a comment, it starts with a single space`
  - `//cout << "this is code, it starts with no spaces";`
```
/*
    Block comments should look like this.
*/
```
- No unnecessary newlines (newlines at the beginning and end of functions, more than one empty line separating anything, etc).
- Don't use `auto` type for basic types like `int` and `double`.
- Initializer lists in constructors should be on their own line.
- Lines of code should only be one line of text (not split between separate text lines), except in cases where there are long parameter lists.
- In class declarations, the order of member declarations should be **constants, then variables, then functions**.
- Declare pointers with the asterisk on the type name (where possible). For example: `int* ptr` rather than `int *ptr`.

### Naming
- Use camelCase (first word lowercase, all other words capitalized, no underscores) for function and variable names.
- Use PascalCase (first letter of every word capitalized, no underscores) for class names.
- Don't include the type in the name of a variable or function (for example `intCount`).
- Constants should be all caps with underscores for spaces (for example `LOOP_SECONDS` is a constant, while `loopSeconds` is a variable).
- File names should be all lowercase and should be the same as the class or namespace within them (for example, class "TriviaController" will have files "triviacontroller.h" and "triviacontroller.cpp", and namespace Utilities will have "utilities.h" and "utilities.cpp").

### Comments & Documentation
- Comments should have proper grammar and punctuation.
- All .h and .cpp files should have a block comment at the top with the filename and short description of the file.
- All functions should be documented with block comments containing description of function followed by description of parameters and return value if applicable, in both the h and cpp files.
```
/*
    Setter for frameInterval.
    This MUST be used to set the same interval value as the timer that is connected to this object.
    TODO: Find a better way to enforce frameInterval being set to the same value as the interval of the timer connected to this object.

    int ms: Milliseconds value to set
    return int: Status code indicating 0 for success and 1 for failure.
*/
int setFrameInterval(int ms);
```
- Variables in class declarations should have a line comment preceding them (or a block comment if there is a lot to explain).
- Chunks of code should have comments preceding them.
- Classes should have a block comment preceding them (in the header file) explaining what the class is for and any other important information about it.
- Any comments containing TODO messages should have `TODO:` in them.


## QML

### Structure
- All *game* QML files should have an Item object as the root object, with `id: root`.
- The root object for every game must contain the following properties and signals (minus the comments which are just for explanation):
```
id: root
width: 2160 // target width
height: 3840 // target height

signal quit // to be called when the game wants to quit and return to menu
signal saveScore(int game, string username, int score) // to be called to save the user's score to the leaderboard

property real scaleFactor: height / 3840 // the current scale factor of the game since height and width are dynamically adjusted to the window size. 3840 is the target width
property int points: 0 // to contain the user's points
property string strName: "Trivia" // this should contain the official name of whatever game this file is for (trivia in this example)
property string username: "unset" // stores the user's name. should be "unset" by default, it will be filled in once the user enters their name
property int gameEnum: 0 // the enum number of the game. should be whatever int corresponds to the value for the game in gameEnum in utilities.h
```
- The root object for every game should contain the controller object for the game (with `id: controller`).
- QML files that are not game files should have a root Item object with `id: base`.

### Syntax
- Only closing curly bracket on separate line (K&R style).
- Indentation with 4 spaces (Qt Creator default).
- No compiler warnings.
- id property should always be the first property of an object.
- Semicolons should be used at the end of lines for code in functions.
- Object properties should always go on separate lines.
- Object declarations should be separated by single empty lines.
- *Do not* use the beautify (auto-formatting) setting in Qt Creator
- Related properties should be grouped together (for example: rows and columns should be placed next to each other).
- Use same comment syntax from C++.
- There should be a single space before property values (for example: `id: timerBase` is good while `id:timerBase` is not).
- There should be a single space between object types and the opening curly bracket (for example: `Rectangle {` is good while `Rectangle{` is not).
- Lines of code should only be one line of text (not split between separate text lines).
- Code in functions should be separated into blocks of related code just like in C++.
- No unnecessary newlines (newlines at the beginning and end of functions, more than one empty line separating anything, etc).

### Naming
- Use camelCase (first word lowercase, all other words capitalized, no underscores) for object ids, variable names, and function names.
- Use PascalCase (first letter of every word capitalized, no underscores) for file names (for example: "TriviaGame.qml").
- Don't include the type in the name of a variable or function (for example: `intCount`).
- Filenames for game QML files should end in "Game.qml" (for example: "TriviaGame.qml").
- Filenames for other QML files should end in "Base.qml" (for example: "MenuBase.qml").
- Any comments containing TODO messages should have `TODO:` in them.

### Comments & Documentation
- Comments should have propper grammar and punctuation.
- All .qml files should have a block comment at the top with the filename and short description of the file.
- All functions should be documented with block comments in Doxygen style (description of function followed by description of parameters and return value if applicable).
- Chunks of code in functions should have comments preceding them.

## QMake File 
The QMake file (cob-taylor-games.pro) specifies how the project should be built, and serves as the project file when opening in Qt Creator.
- Any folders that house files used in the QMake file should be listed in `INCLUDEPATH` (for example: `./include`).
- Code files in HEADERS and SOURCES should not have path prefixes since they are already listed in `INCLUDEPATH` (for example: `include/bgwidget.h \` should just be `bgwidget.h \`).
  - **Qt Creator will automatically add these path prefixes when creating code files, so make sure to remove them!**
- Files in `HEADERS` and `SOURCES` should go on separates lines.
- For functions, only closing curly bracket on separate line (K&R style).

## Resource File 
The resource (resources.qrc) file contains files that are baked into the program executable for faster and more reliable access. 
- Should contain 3 prefixes:
  - **/menu** - for menu images and background icons.
  - **/game** - for files used by games.
  - **/qml** - for QML files.
- Resources file should not contain any files that are not being used by the program. 

# cob-taylor-games
This is the program for one of the two touchscreens in the UA Taylor Institute video wall. It contains some minigames relating to The University of Akron, Taylor Institute, and marketing. This project is coded in C++ using the Qt 6 GUI library. It is currently intended to run on a portrait touchscreen at 2160x3840 resolution.

## Setup

## Development Info + Plans
- Window has a QFrame "canvas" that is coded to always appear portrait. It is named that because it is intended to be the "canvas" for the application and all widgets except for the background should be children of it.
  - Canvas should have something like 50% transparency so the background can be seen.
- Behind canvas will be a background widget covering the entire window. This can be just an image but I would like to try out fancy scrolling graphics with an OpenGL widget.
- In canvas is a vertical layout "menuLayout" containing the menu widgets.
  - lblTitle should contain a title image and is displayed at the top of the menu.
  - leaderboardPlaceholder is a placeholder widget for the leaderboard. Not sure what widget type to use for the leaderboard yet. Probably going to be a list or table widget. Or it could even be a QQuickWidget to make it even fancier.
  - Buttons will either be customized with stylesheets or have images on them.
- Currently I am thinking that the games should be implemented entirely in QQuickWidgets with QML/QtQuick because QML can apparently do graphics and animation easier than QtWidgets.
  - Ideally each game will be its own QQuickWidget. To my understanding this should allow the games to be basically standalone objects that can be easily manipulated by the program.
  - Thinking some class/object should be used to control which game is active (being shown on the canvas) or if none are active it will instead show the menu. This object could also control the state of the games.
    - For example, if user clicks game button 1 it will call controlObject.game1() which will create the game1 QQuickWidget and show it on the canvas above the menu.
    - Then when the user clicks the back button or the game times out it will call controlObject.backToMenu() which will destroy the current game widget, returning to the menu.
- There should also be a system that monitors for inactivity. This system should probably interact with the aforementioned control object to manage the state of the program.
  - For instance, calling backToMenu() after a certain period of inactivity.
- Games will most likely store high scores and other data in text files. This could be utilized by the leaderboard.

## Game Plans
There will be 6 games. Currently we have the following ideas:
- Chess with Zippy pieces
- UA trivia
- "Guess the logo"

# Tic-Tac-Toe Game &#x274C; &#x2B55;

## Introduction

This project is a simple implementation of the classic Tic Tac Toe game developed by Group 7 for Computer Graphics Course. The game is designed to run on a computer and provides a graphical user interface for players to interact with.

## Team Members

1. Rediet Teklay
2. Yoseph Zewdu
3. Yoseph Shemeles
4. Yordanos Negusu
5. Yordanos Bekele

## Requirements

- Graphics Library: [OpenGL] (https://www.opengl.org/), [GLUT] (https://freeglut.sourceforge.net/)
- Language: C++
- Development Environment: [IDE or Text Editor of your choice]

## Installation

1. Clone the repository to your local machine using the following command:

```bash
git clone https://github.com/Yosinan/CG-Group-Project.git
```

2. Navigate to the project directory:

```bash
cd CG-Group-Project
cd Tic-Tac-Toe
```

3. Compile the project using the following command:

```bash
g++ tic_tac_toe.cpp -o main -lGL -lGLU -lglut
```

or run the start.sh file using the following commands:

```bash
chmod +x start.sh
./start.sh
```

4. Run the compiled file using the following command:

```bash
./main
```

## How to Play

1. The game is designed to be played by two players.
2. Players input their names at the start of the game.
3. The game starts with an empty &#x003;x&#x0033; grid.
4. Players take turns to place their mark (&#x274C; or &#x2B55;) on the grid.
5. The first player to get three of their marks in a row (horizontally, vertically, or diagonally) wins the game.
6. If the grid is full and no player has won, the game ends in a draw/tie.
7. Players can restart the game at any time by pressing the 'r' key.
8. Players can exit the game at any time by pressing the 's' key.

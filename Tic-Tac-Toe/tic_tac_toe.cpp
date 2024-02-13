#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <cctype>
using namespace std;
#include <vector>
#include <algorithm>
#include <ctime>

// Constants
const int windowWidth = 700;
const int windowHeight = 700;

// Game state
char board[3][3] = {{' ', ' ', ' '},
                    {' ', ' ', ' '},
                    {' ', ' ', ' '}};
bool player1Turn = true;
bool gameWon = false;
string player1Name;
string player2Name;

// Particle structure for spark effect
struct Particle
{
    float x, y;
    float r, g, b;
    float lifetime;
};

vector<Particle> particles;

// Function to draw the X or O on the board
void drawSymbol(int row, int col)
{
    if (board[row][col] == 'X')
    {
        glBegin(GL_LINES);

        // \ top left to bottom right

        glVertex2f(col * (windowWidth / 3.0), row * (windowHeight / 3.0));
        glVertex2f((col + 1) * (windowWidth / 3.0), (row + 1) * (windowHeight / 3.0));

        // / bottom left to top right

        glVertex2f(col * (windowWidth / 3.0), (row + 1) * (windowHeight / 3.0));
        glVertex2f((col + 1) * (windowWidth / 3.0), row * (windowHeight / 3.0));
        glEnd();
    }
    else if (board[row][col] == 'O')
    {
        glBegin(GL_TRIANGLE_FAN);
        float centerX = (col + 0.5) * (windowWidth / 3.0);
        float centerY = (row + 0.5) * (windowHeight / 3.0);
        glVertex2f(centerX, centerY);
        for (int i = 0; i <= 100; ++i)
        {
            float angle = i * 2.0f * 3.14159 / 100;
            float x = centerX + 0.5 * cos(angle) * (windowWidth / 3.0);
            float y = centerY + 0.5 * sin(angle) * (windowHeight / 3.0);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

// Function to draw the game board
void drawBoard()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw grid
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 1; i < 3; ++i)
    {
        // vertical
        glVertex2f(i * (windowWidth / 3.0), 0);
        glVertex2f(i * (windowWidth / 3.0), windowHeight);

        // horizontal
        glVertex2f(0, i * (windowHeight / 3.0));
        glVertex2f(windowWidth, i * (windowHeight / 3.0));
    }
    glEnd();

    // Draw X and O symbols
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            drawSymbol(i, j);
        }
    }

    // Check for a tie
    bool tie = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                tie = false;
                break;
            }
        }
        if (!tie)
            break;
    }

    // Display winner
    if (gameWon)
    {
        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2f(windowWidth / 2 - 50, windowHeight / 2);
        string winner = player1Turn ? player2Name : player1Name;

        // Convert each character to uppercase
        for (char &c : winner)
        {
            c = std::toupper(c);
        }

        winner += " Won!";

        for (char c : winner)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        // Display options to quit or restart
        glColor3f(0.0, 0.0, 1.0);

        glRasterPos2f(windowWidth / 2 - 130, windowHeight / 2 + 60);
        string input = "Press 'R' to restart or 'S' to quit.";
        for (char c : input)
        {
            
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            
        }

        // Spark effect
        glPointSize(8.0f);
        glBegin(GL_POINTS);
        for (const Particle &p : particles)
        {
            glColor3f(p.r, p.g, p.b);
            glVertex2f(p.x, p.y);
        }
        glEnd();

    }
    else if (tie)
    {
        // Display tie
        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2f(windowWidth / 2 - 50, windowHeight / 2);
        string tieMessage = "It's a Tie!";

        for (char c : tieMessage)
        {
            
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            
        }
    }

    glutSwapBuffers();
}

// Function to check for a winner
bool checkWinner()
{
    // Check rows and columns
    for (int i = 0; i < 3; ++i)
    {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' '))
        {
            gameWon = true;
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
    {
        gameWon = true;
        return true;
    }

    return false;
}

// Function to handle mouse clicks
void onMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !gameWon)
    {
        int row = y / (windowHeight / 3);
        int col = x / (windowWidth / 3);

        if (row < 3 && col < 3 && board[row][col] == ' ')
        {
            if (player1Turn)
            {
                board[row][col] = 'X';
            }
            else
            {
                board[row][col] = 'O';
            }

            if (checkWinner())
            {
                string winnerName = player1Turn ? player1Name : player2Name;
                cout << winnerName << " won!\U0001F389" << endl;
                // Spark effect when a player wins
                particles.clear();
                for (int i = 0; i < 100; ++i)
                {
                    Particle p;
                    p.x = rand() % windowWidth;
                    p.y = rand() % windowHeight;
                    p.r = static_cast<float>(rand() % 256) / 255.0f;
                    p.g = static_cast<float>(rand() % 256) / 255.0f;
                    p.b = static_cast<float>(rand() % 256) / 255.0f;
                    p.lifetime = 2.0f;
                    particles.push_back(p);
                }
            }

            player1Turn = !player1Turn;
        }
    }
}

// Function to update particle positions
void updateParticles(float deltaTime)
{
    for (auto &p : particles)
    {
        p.lifetime -= deltaTime;
    }
    particles.erase(remove_if(particles.begin(), particles.end(),
                              [](const Particle &p)
                              { return p.lifetime <= 0.0f; }),
                    particles.end());
}

// Function to reset the game
void resetGame()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            board[i][j] = ' ';
        }
    }

    player1Turn = true;
    gameWon = false;

    glutPostRedisplay();
}

// Function to initialize OpenGL
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, windowWidth, windowHeight, 0);
}

// Function to handle updates in the animation
void update(int value)
{
    updateParticles(0.016f);      // Update particles every frame (assuming 60 FPS)
    glutTimerFunc(16, update, 0); // 60 FPS
    glutPostRedisplay();
}

// Function to handle window resizing
void reshape(int w, int h)
{
    glViewport(0, 0, w, h); // Set the viewport to cover the entire window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0); // Use the entire window as the coordinate system
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    srand(static_cast<unsigned int>(time(0))); // Seed for random numbers

    cout << "Enter name for Player 1 (X): ";
    cin >> player1Name;
    cout << "Enter name for Player 2 (O): ";
    cin >> player2Name;

    if (player1Name.empty())
    {
        player1Name = "Player 1";
    }
    if (player2Name.empty())
    {
        player2Name = "Player 2";
    }

    if (player1Name == player2Name)
    {
        player1Name += " 1";
        player2Name += " 2";
    }

    if (player1Name != "" && player2Name != "")
    {
        cout << "Player 1: " << player1Name << endl;
        cout << "Player 2: " << player2Name << endl;
        glutInit(&argc, argv);
    }

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Tic Tac Toe");
    glutDisplayFunc(drawBoard);
    glutReshapeFunc(reshape);
    glutMouseFunc(onMouseClick);
    glutTimerFunc(0, update, 0); // Start the update timer

    // Add a key callback to reset or stop the game
    glutKeyboardFunc([](unsigned char key, int x, int y)
                     {
        if (key == 'r' || key == 'R')
        {
            resetGame();
        }

        if (key == 's' || key == 'S')
        {
            exit(0);
        } });

    init();

    glutMainLoop();

    return 0;
}

#include <iostream>
#include <conio.h>
#include <windows.h>

const int WIDTH = 50;
const int HEIGHT = 10;
int dinoPos = HEIGHT - 2;
int obstaclePos = WIDTH - 1;
bool isJumping = false;
int jumpHeight = 0;
bool isFalling = false;

void ClearScreen() {
    system("cls");
}

bool IsKeyPressed() {
    return _kbhit();
}

char GetKeyPressed() {
    return _getch();
}

void DrawGame() {
    ClearScreen();

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == dinoPos && j == 1) {
                std::cout << "🦖";
            } else if (i == HEIGHT - 1 && j == obstaclePos) {
                std::cout << "🌵";
            } else if (i == HEIGHT - 1) {
                std::cout << "_";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void UpdateGame() {
    
    obstaclePos--;
    if (obstaclePos < 0) {
        obstaclePos = WIDTH - 1;
    }

    
    if (isJumping) {
        dinoPos--;
        jumpHeight++;
        if (jumpHeight > 3) {
            isJumping = false;
            isFalling = true;
        }
    } else if (isFalling) {
        dinoPos++;
        if (dinoPos >= HEIGHT - 2) {
            dinoPos = HEIGHT - 2;
            isFalling = false;
        }
    }

    
    if (dinoPos == HEIGHT - 2 && obstaclePos == 1) {
        std::cout << "Game Over!" << std::endl;
        exit(0);
    }
}

int main() {
    while (true) {
        DrawGame();
        UpdateGame();

        
        if (IsKeyPressed()) {
            char key = GetKeyPressed();
            if (key == ' ' && !isJumping && !isFalling) {
                isJumping = true;
                jumpHeight = 0;
            }
        }

        Sleep(100); // 100 мс задержка (Windows)
    }

    return 0;
}

#include <iostream>
#include <conio.h>  // Для _kbhit() и _getch()
#include <windows.h> // Для Sleep()

const int WIDTH = 50;
const int HEIGHT = 10;
int dinoPos = HEIGHT - 2; // Позиция динозаврика по вертикали
int obstaclePos = WIDTH - 1; // Позиция препятствия
bool isJumping = false; // Флаг для прыжка
int jumpHeight = 0; // Высота прыжка
bool isFalling = false; // Флаг падения

// Очистка экрана (Windows)
void ClearScreen() {
    system("cls");
}

// Проверка, нажата ли клавиша
bool IsKeyPressed() {
    return _kbhit();
}

// Получение символа, если клавиша нажата
char GetKeyPressed() {
    return _getch();
}

void DrawGame() {
    ClearScreen();

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == dinoPos && j == 1) {
                std::cout << "🦖"; // Динозаврик
            } else if (i == HEIGHT - 1 && j == obstaclePos) {
                std::cout << "🌵"; // Кактус
            } else if (i == HEIGHT - 1) {
                std::cout << "_"; // Земля
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void UpdateGame() {
    // Движение препятствия
    obstaclePos--;
    if (obstaclePos < 0) {
        obstaclePos = WIDTH - 1; // Препятствие возвращается в начало
    }

    // Логика прыжка и падения
    if (isJumping) {
        dinoPos--;
        jumpHeight++;
        if (jumpHeight > 3) { // Достиг максимальной высоты
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

    // Проверка столкновения
    if (dinoPos == HEIGHT - 2 && obstaclePos == 1) {
        std::cout << "Game Over!" << std::endl;
        exit(0);
    }
}

int main() {
    while (true) {
        DrawGame();
        UpdateGame();

        // Обработка ввода (пробел для прыжка)
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
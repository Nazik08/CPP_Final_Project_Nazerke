#include <iostream>
#include <conio.h>  // Для _kbhit() и _getch()
#include <windows.h> // Для Sleep()

const int WIDTH = 50; // Ширина экрана
const int HEIGHT = 10; // Высота экрана
int dinoPos = HEIGHT - 2; // Позиция динозавра по высоте
int obstaclePos = WIDTH - 1; // Начальная позиция препятствия
bool isJumping = false; // Флаг прыжка
int jumpHeight = 0; // Текущая высота прыжка
bool isFalling = false; // Флаг падения
int score = 0; // Счетчик очков

// Очистка экрана (Windows)
void ClearScreen() {
    system("cls");
}

// Проверка нажатия клавиши
bool IsKeyPressed() {
    return _kbhit();
}

// Получение символа нажатой клавиши
char GetKeyPressed() {
    return _getch();
}

// Отрисовка игрового поля
void DrawGame() {
    ClearScreen();

    std::cout << "Score: " << score << "\n"; // Выводим очки

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == dinoPos && j == 1) {
                std::cout << "🦖"; // Динозавр (можно заменить на 🦖)
            } else if (i == HEIGHT - 1 && j == obstaclePos) {
                std::cout << "🌵"; // Кактус (можно заменить на 🌵)
            } else if (i == HEIGHT - 1) {
                std::cout << "_"; // Земля
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Обновление логики игры
void UpdateGame() {
    // Двигаем препятствие
    obstaclePos--;
    if (obstaclePos < 0) {
        obstaclePos = WIDTH - 1; // Перезапуск препятствия
        score++; // Увеличиваем счет
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
        ClearScreen();
        std::cout << "Game Over! Final Score: " << score << std::endl;
        exit(0);
    }
}

int main() {
    while (true) {
        DrawGame();
        UpdateGame();

        // Обработка ввода (пробел - прыжок)
        if (IsKeyPressed()) {
            char key = GetKeyPressed();
            if (key == ' ' && !isJumping && !isFalling) {
                isJumping = true;
                jumpHeight = 0;
            }
        }

        Sleep(100); // Задержка в 100 мс
    }

    return 0;
}

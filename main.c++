#include "raylib.h"
#include <string>
#include <vector>
#include <cctype>
#include <iostream>

using namespace std;

void DrawHangman(int lives) {
    if (lives <= 4) DrawCircle(300, 130, 30, BLACK);
    if (lives <= 3) DrawLine(300, 160, 300, 300, BLACK);
    if (lives <= 2) DrawLine(300, 200, 250, 250, BLACK);
    if (lives <= 1) DrawLine(300, 200, 350, 250, BLACK);
    if (lives == 0) {
        DrawLine(300, 300, 250, 350, BLACK);
        DrawLine(300, 300, 350, 350, BLACK);
    }
}

bool PlayLevel(const string& word) {
    string userAnswer(word.length(), '_');
    vector<bool> ifGuessCorrect(word.length(), false);

    int lives = 5;
    int numCorrectGuesses = 0;
    char currentGuess = '\0';

    SetTargetFPS(60);

    while (lives > 0 && numCorrectGuesses < word.length()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Hangman Game", 20, 20, 40, DARKBLUE);
        DrawHangman(lives);

        for (size_t i = 0; i < word.length(); ++i) {
            DrawText((string(1, userAnswer[i])).c_str(), 50 + i * 40, 400, 40, BLACK);
        }

        DrawText(("Lives: " + to_string(lives)).c_str(), 20, 80, 20, RED);
        DrawText("Type a letter and press ENTER:", 20, 500, 20, DARKGRAY);
        if (currentGuess != '\0') {
            DrawText(("Your guess: " + string(1, currentGuess)).c_str(), 20, 530, 20, DARKGRAY);
        }

        EndDrawing();

        while (int key = GetCharPressed()) {
            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
                currentGuess = tolower(key);
            }
        }

        if (IsKeyPressed(KEY_ENTER) && currentGuess != '\0') {
            bool found = false;
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] == currentGuess && !ifGuessCorrect[i]) {
                    userAnswer[i] = currentGuess;
                    ifGuessCorrect[i] = true;
                    numCorrectGuesses++;
                    found = true;
                }
            }
            if (!found) {
                lives--;
            }
            currentGuess = '\0';
        }
    }

    if (lives == 0) {
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("You lost! Better luck next time.", 150, 300, 30, RED);
            EndDrawing();
        }
        return false;
    }

    return true;
}

int main() {
    InitWindow(800, 600, "Hangman Game");

    vector<string> words = { "hello", "elephant", "artificial" };
    for (const auto& word : words) {
        if (!PlayLevel(word)) {
            CloseWindow();
            return 0;
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congratulations! You completed all levels!", 100, 300, 30, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

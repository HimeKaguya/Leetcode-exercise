#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;
const char EMPTY = ' ';
const char BLOCK = '#';
const int BLOCK_SIZE = 2;

vector<vector<char>> board(HEIGHT, vector<char>(WIDTH, EMPTY));
vector<vector<char>> currentPiece;
int currentX, currentY;

vector<vector<vector<char>>> pieces = {
    {{BLOCK, BLOCK, BLOCK, BLOCK}},
    {{BLOCK, BLOCK}, {BLOCK, BLOCK}},
    {{BLOCK, BLOCK, BLOCK}, {0, BLOCK, 0}},
    {{BLOCK, BLOCK, 0}, {0, BLOCK, BLOCK}},
    {{0, BLOCK, BLOCK}, {BLOCK, BLOCK, 0}},
    {{BLOCK, BLOCK, BLOCK}, {BLOCK, 0, 0}},
    {{BLOCK, BLOCK, BLOCK}, {0, 0, BLOCK}}
};

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void sleep(int milliseconds) {
    #ifdef _WIN32
    Sleep(milliseconds);
    #else
    usleep(milliseconds * 1000);
    #endif
}

void drawBoard() {
    clearScreen();
    vector<vector<char>> tempBoard = board;
    
    // 将当前方块添加到临时板上
    for (int i = 0; i < currentPiece.size(); i++) {
        for (int j = 0; j < currentPiece[i].size(); j++) {
            if (currentPiece[i][j] == BLOCK) {
                int y = currentY + i;
                int x = currentX + j;
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    tempBoard[y][x] = BLOCK;
                }
            }
        }
    }
    
    cout << "+";
    for (int i = 0; i < WIDTH * BLOCK_SIZE; i++) {
        cout << "-";
    }
    cout << "+\n";
    
    for (int i = 0; i < HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < WIDTH; j++) {
            if (tempBoard[i][j] == BLOCK) {
                cout << string(BLOCK_SIZE, BLOCK);
            } else {
                cout << string(BLOCK_SIZE, EMPTY);
            }
        }
        cout << "|\n";
    }
    
    cout << "+";
    for (int i = 0; i < WIDTH * BLOCK_SIZE; i++) {
        cout << "-";
    }
    cout << "+\n";
}

bool isCollision() {
    for (int i = 0; i < currentPiece.size(); i++) {
        for (int j = 0; j < currentPiece[i].size(); j++) {
            if (currentPiece[i][j] == BLOCK) {
                int x = currentX + j;
                int y = currentY + i;
                if (x < 0 || x >= WIDTH || y >= HEIGHT || (y >= 0 && board[y][x] == BLOCK)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void mergePiece() {
    for (int i = 0; i < currentPiece.size(); i++) {
        for (int j = 0; j < currentPiece[i].size(); j++) {
            if (currentPiece[i][j] == BLOCK) {
                int y = currentY + i;
                int x = currentX + j;
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    board[y][x] = BLOCK;
                }
            }
        }
    }
}

void rotatePiece() {
    vector<vector<char>> rotated(currentPiece[0].size(), vector<char>(currentPiece.size()));
    for (int i = 0; i < currentPiece.size(); i++) {
        for (int j = 0; j < currentPiece[i].size(); j++) {
            rotated[j][currentPiece.size() - 1 - i] = currentPiece[i][j];
        }
    }
    currentPiece = rotated;
}

void clearLines() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        bool fullLine = true;
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == EMPTY) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int k = i; k > 0; k--) {
                board[k] = board[k - 1];
            }
            board[0] = vector<char>(WIDTH, EMPTY);
        }
    }
}

void newPiece() {
    int index = rand() % pieces.size();
    currentPiece = pieces[index];
    currentX = WIDTH / 2 - currentPiece[0].size() / 2;
    currentY = 0;
    if (isCollision()) {
        cout << "Game Over!" << endl;
        exit(0);
    }
}

int main() {
    srand(time(0));
    newPiece();
    char key;
    
    while (true) {
        drawBoard();
        
        cout << "Controls: a-left, d-right, s-down, w-rotate, q-quit\n";
        
        sleep(500);
        
        if (cin.peek() != EOF) {
            cin >> key;
            cin.ignore(1000, '\n');
        } else {
            key = 's';
        }
        
        if (key == 'q') break;
        
        int oldX = currentX;
        int oldY = currentY;
        vector<vector<char>> oldPiece = currentPiece;
        
        switch (key) {
            case 'a': currentX--; break;
            case 'd': currentX++; break;
            case 's': currentY++; break;
            case 'w': rotatePiece(); break;
        }
        
        if (isCollision()) {
            currentX = oldX;
            currentY = oldY;
            currentPiece = oldPiece;
            if (key == 's') {
                mergePiece();
                clearLines();
                newPiece();
            }
        }
    }
    
    cout << "Thanks for playing!" << endl;
    return 0;
}
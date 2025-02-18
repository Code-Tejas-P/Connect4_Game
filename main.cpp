#include <iostream>
#include <vector>
using namespace std;

const int ROWS = 6;
const int COLS = 7;

void printBoard(const vector<vector<char>>& board) {
    for (int row = ROWS - 1; row >= 0; --row) {
        cout << "|";
        for (int col = 0; col < COLS; ++col) {
            cout << board[row][col] << "|";
        }
        cout << endl;
    }
    cout << " ";
    for (int col = 0; col < COLS; ++col) {
        cout << col+1 << " ";
    }
    cout << endl << endl;
}

bool isValidMove(const vector<vector<char>>& board, int col) {
    return (col >= 0 && col < COLS && board[0][col] == ' ');
}

int dropDisc(vector<vector<char>>& board, int col, char disc) {
    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][col] == ' ') {
            board[row][col] = disc;
            return row;
        }
    }
    return -1;
}

bool checkWin(const vector<vector<char>>& board, int row, int col) {
    char disc = board[row][col];
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (auto& dir : directions) {
        int dx = dir[0];
        int dy = dir[1];
        int count = 1;

        int current_row = row + dx;
        int current_col = col + dy;
        while (current_row >= 0 && current_row < ROWS &&
               current_col >= 0 && current_col < COLS &&
               board[current_row][current_col] == disc) {
            count++;
            current_row += dx;
            current_col += dy;
        }

        current_row = row - dx;
        current_col = col - dy;
        while (current_row >= 0 && current_row < ROWS &&
               current_col >= 0 && current_col < COLS &&
               board[current_row][current_col] == disc) {
            count++;
            current_row -= dx;
            current_col -= dy;
        }

        if (count >= 4) return true;
    }
    return false;
}

bool isBoardFull(const vector<vector<char>>& board) {
    for (int col = 0; col < COLS; ++col)
        if (board[0][col] == ' ') return false;
    return true;
}

int main() {
    vector<vector<char>> board(ROWS, vector<char>(COLS, ' '));
    char currentPlayer = 'Y';
    bool gameOver = false;

    while (!gameOver) {
        printBoard(board);
        int col;
        cout << "Player " << currentPlayer << ", enter column (1-7): ";
        cin >> col;
        col--;

        if (col < 0 || col >= COLS || !isValidMove(board, col)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        int row = dropDisc(board, col, currentPlayer);
        if (checkWin(board, row, col)) {
            printBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        } else if (isBoardFull(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            gameOver = true;
        } else {
            currentPlayer = (currentPlayer == 'R') ? 'Y' : 'R';
        }
    }

    return 0;
}
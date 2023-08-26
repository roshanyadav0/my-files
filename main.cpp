#include <iostream>
#include <cstdlib>
#include <ctime>

class Board {
public:
    Board();
    void display();
    bool makeMove(char playerSymbol, int row, int col);
    bool isGameOver();
    bool checkWin(char playerSymbol);
    void printResult();

//private:
    char grid[3][3];
    int movesMade;
};

Board::Board() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j] = ' ';
        }
    }
    movesMade = 0;
}

void Board::display() {
    std::cout << "  1 2 3\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            std::cout << grid[i][j];
            if (j < 2) std::cout << '|';
        }
        std::cout << "\n";
        if (i < 2) std::cout << "  -----\n";
    }
}

bool Board::makeMove(char playerSymbol, int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' ') {
        std::cout << "Invalid move. Try again.\n";
        return false;
    }

    grid[row][col] = playerSymbol;
    movesMade++;
    return true;
}

bool Board::isGameOver() {
    return checkWin('X') || checkWin('O') || movesMade >= 9;
}

bool Board::checkWin(char playerSymbol) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] == playerSymbol && grid[i][1] == playerSymbol && grid[i][2] == playerSymbol) {
            return true;
        }
        if (grid[0][i] == playerSymbol && grid[1][i] == playerSymbol && grid[2][i] == playerSymbol) {
            return true;
        }
    }
    if (grid[0][0] == playerSymbol && grid[1][1] == playerSymbol && grid[2][2] == playerSymbol) {
        return true;
    }
    if (grid[0][2] == playerSymbol && grid[1][1] == playerSymbol && grid[2][0] == playerSymbol) {
        return true;
    }
    return false;
}

void Board::printResult() {
    if (checkWin('X')) {
        std::cout << "You win!\n";
    } else if (checkWin('O')) {
        std::cout << "Computer wins!\n";
    } else {
        std::cout << "It's a draw!\n";
    }
}

// ... Rest of the code ...

class ComputerPlayer {
public:
    void makeMove(Board &board);
    int minimax(Board &board, int depth, bool isMaximizing);
};
/*
void ComputerPlayer::makeMove(Board &board) {
    int bestScore = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    // First, check if the computer can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.grid[i][j] == ' ') {
                board.grid[i][j] = 'O';

                if (board.checkWin('O')) {
                    board.grid[i][j] = ' ';
                    board.makeMove('O', i, j); // Make the winning move
                    return;
                }

                board.grid[i][j] = ' ';
            }
        }
    }

    // Next, check if the user can win in the next move and block it
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.grid[i][j] == ' ') {
                board.grid[i][j] = 'X';

                if (board.checkWin('X')) {
                    board.grid[i][j] = 'O'; // Block the user's winning move
                    return;
                }

                board.grid[i][j] = ' ';
            }
        }
    }

    // If no winning moves are found, use the minimax algorithm
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.grid[i][j] == ' ') {
                board.grid[i][j] = 'O';
                int score = minimax(board, 0, false);
                board.grid[i][j] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    if (bestMoveRow != -1 && bestMoveCol != -1) {
        board.makeMove('O', bestMoveRow, bestMoveCol);
    }
//}
//
//
//// ... Rest of the code ...
// ... Rest of the code ...
*/
void ComputerPlayer::makeMove(Board &board) {
    int bestScore = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    // First, check if the computer can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.grid[i][j] == ' ') {
                board.grid[i][j] = 'O';

                if (board.checkWin('O')) {
                    board.grid[i][j] = ' ';
                    board.makeMove('O', i, j); // Make the winning move
                    return;
                }

                board.grid[i][j] = ' ';
            }
        }
    }

    // Next, check if the user can win in the next move and block it
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.grid[i][j] == ' ') {
                board.grid[i][j] = 'X';

                if (board.checkWin('X')) {
                    board.grid[i][j] = 'O'; // Block the user's winning move
                    return;
                }

                board.grid[i][j] = ' ';
            }
        }
    }

    // If no winning moves are found, use the minimax algorithm
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.grid[i][j] == ' ') {
                board.grid[i][j] = 'O';
                int score = minimax(board, 0, false);
                board.grid[i][j] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    if (bestMoveRow != -1 && bestMoveCol != -1) {
        board.makeMove('O', bestMoveRow, bestMoveCol);
    } else {
        std::cout << "It's a draw!\n";
        exit(0); // Exit the program when the game is a draw
    }
}

// ... Rest of the code ...


int ComputerPlayer::minimax(Board &board, int depth, bool isMaximizing) {
    if (board.checkWin('O')) {
        return 1;
    } else if (board.checkWin('X')) {
        return -1;
    } else if (board.isGameOver()) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.grid[i][j] == ' ') {
                    board.grid[i][j] = 'O';
                    int score = minimax(board, depth + 1, false);
                    board.grid[i][j] = ' ';
                    bestScore = std::max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.grid[i][j] == ' ') {
                    board.grid[i][j] = 'X';
                    int score = minimax(board, depth + 1, true);
                    board.grid[i][j] = ' ';
                    bestScore = std::min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

int main() {
    char playAgain;
    do {
        Board board;
        ComputerPlayer computer;

        board.display();

        while (!board.isGameOver()) {
            int row, col;

            // Player's move
            do {
                std::cout << "Enter row and column (1-3) for your move: ";
                std::cin >> row >> col;
                row--;
                col--;
            } while (!board.makeMove('X', row, col));

            board.display();

            if (board.isGameOver()) {
                break;
            }

            // Computer's move
            computer.makeMove(board);
            board.display();
        }

        board.printResult();

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Thanks for playing! Goodbye.\n";

    return 0;
}


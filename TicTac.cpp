#include <iostream>
#include <vector>
#include <limits>

const char human = 'X';
const char ai = 'O';
const char empty = ' ';

std::vector<int> scores = {0, -10, 10};

struct Move
{
    int row;
    int col;
};

void createBoard(std::vector<std::vector<char>> &board)
{
    for (int i = 0; i < 3; i++)
    {
        std::vector<char> temp(3, empty);
        board.push_back(temp);
    }
}

bool isMovesLeft(const std::vector<std::vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            if (cell == empty)
                return true;
        }
    }
    return false;
}

int evaluate(const std::vector<std::vector<char>> &board)
{
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == ai)
                return scores[2];
            else if (board[i][0] == human)
                return scores[1];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == ai)
                return scores[2];
            else if (board[0][i] == human)
                return scores[1];
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == ai)
            return scores[2];
        else if (board[0][0] == human)
            return scores[1];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == ai)
            return scores[2];
        else if (board[0][2] == human)
            return scores[1];
    }
    return scores[0]; // Draw
}

int minimax(std::vector<std::vector<char>> &board, int depth, bool isMaximizing)
{
    int score = evaluate(board);

    if (score != scores[0])
        return score;

    if (!isMovesLeft(board))
        return scores[0];

    if (isMaximizing)
    {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == empty)
                {
                    board[i][j] = ai;
                    int currentScore = minimax(board, depth + 1, false);
                    bestScore = std::max(bestScore, currentScore);
                    board[i][j] = empty;
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == empty)
                {
                    board[i][j] = human;
                    int currentScore = minimax(board, depth + 1, true);
                    bestScore = std::min(bestScore, currentScore);
                    board[i][j] = empty;
                }
            }
        }
        return bestScore;
    }
}

Move findBestMove(std::vector<std::vector<char>> &board)
{
    int bestScore = std::numeric_limits<int>::min();
    Move bestMove;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == empty)
            {
                board[i][j] = ai;
                int currentScore = minimax(board, 0, false);
                if (currentScore > bestScore)
                {
                    bestScore = currentScore;
                    bestMove.row = i;
                    bestMove.col = j;
                }
                board[i][j] = empty;
            }
        }
    }
    return bestMove;
}

void printBoard(const std::vector<std::vector<char>> &board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<std::vector<char>> board;
    createBoard(board);

    std::cout << "Initial board:" << std::endl;
    printBoard(board);

    while (isMovesLeft(board))
    {
        Move bestMove = findBestMove(board);
        board[bestMove.row][bestMove.col] = ai;
        std::cout << "AI's move:" << std::endl;
        printBoard(board);
        if (evaluate(board) != scores[0])
            break;

        // Assuming human's move is manual input for simplicity
        int humanRow, humanCol;
        std::cout << "Enter your move (row and column): ";
        std::cin >> humanRow >> humanCol;
        board[humanRow][humanCol] = human;
        std::cout << "After your move:" << std::endl;
        printBoard(board);
        if (evaluate(board) != scores[0])
            break;
    }

    int result = evaluate(board);
    if (result == scores[1])
        std::cout << "Human wins!" << std::endl;
    else if (result == scores[2])
        std::cout << "AI wins!" << std::endl;
    else
        std::cout << "It's a draw!" << std::endl;

    return 0;
};
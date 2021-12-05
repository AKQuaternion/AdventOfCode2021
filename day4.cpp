#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

const int boardSize = 5;
using Board = std::array<std::array<int, boardSize>, boardSize>;

void mark(Board &b, int number) {
    for (auto &row: b)
        for (auto &num: row)
            if (num == number)
                num = -1;
}

bool hasWon(const Board &b) {
    for (const auto &row: b)
        if (std::all_of(row.begin(), row.end(), [](int num) { return num == -1; }))
            return true;
    for (int col = 0; col < boardSize; ++col) {
        bool allMinusOneSoFar = true;
        for (int row = 0; row < boardSize; ++row)
            if (b[row][col] != -1)
                allMinusOneSoFar = false;
        if (allMinusOneSoFar)
            return true;
    }
    return false;
}

int calculateScore(const Board &b) {
    int score = 0;
    for (const auto &row: b)
        for (auto num: row)
            if (num != -1)
                score += num;
    return score;
}

std::pair<int, int> scoreGame(std::vector<Board> &boards, const std::vector<int> &numbers) {
    int boardsWon = 0;
    int star1 = 0;
    for (auto num: numbers) {
        for (auto &b: boards) {
            bool alreadyWon = hasWon(b);
            mark(b, num);
            if (hasWon(b)) {
                if (!alreadyWon)
                    ++boardsWon;
                if (boardsWon == 1)
                    star1 = calculateScore(b) * num;
                if (boardsWon == boards.size())
                    return {star1, calculateScore(b) * num};
            }
        }
    }
    return {-1, -1};
}

void day4() {
    std::ifstream ifile("../day4.txt");
    std::string line;
    getline(ifile, line);
    std::vector<int> numbers;
    std::istringstream numberStream(line);
    int number = 0;
    char comma = 0;
    while (numberStream) {
        numberStream >> number >> comma;
        numbers.push_back(number);
    }
    std::vector<Board> boards;
    while (true) {
        getline(ifile, line); //read blank line
        if (!ifile)
            break;
        Board b;
        for (int i = 0; i < boardSize; ++i) {
            getline(ifile, line);
            std::istringstream iline(line);
            for (int j = 0; j < boardSize; ++j) {
                iline >> number;
                b[i][j] = number;
            }
        }
        boards.emplace_back(b);
    }

    auto[star1, star2] = scoreGame(boards, numbers);
    std::cout << "Day 4 star 1 = " << star1 << "\n";
    std::cout << "Day 4 star 2 = " << star2 << "\n";
}

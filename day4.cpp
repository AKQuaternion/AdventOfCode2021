#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using std::abs;
using std::array;
using std::ceil;
using std::ceil;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::map;
using std::max;
using std::max_element;
using std::min;
using std::pair;
using std::set;
using std::queue;
using std::sqrt;
using std::string;
using std::forward_as_tuple;
using std::tie;
using std::tuple;
using std::swap;
using std::vector;

const int boardSize = 5;
using Board = array<array<int, boardSize>, boardSize>;

void mark(Board &b, int number) {
    for (auto &row: b)
        for (auto &num: row)
            if (num == number)
                num = -1;
}

bool hasWon(const Board &b) {
    for (auto row: b)
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
    for (auto row: b)
        for (auto num: row)
            if (num != -1)
                score += num;
    return score;
}

int scoreWinner(vector<Board> &boards, const vector<int> &numbers) {
    for (auto num: numbers) {
        for (auto &b: boards) {
            mark(b, num);
            if (hasWon(b))
                return calculateScore(b) * num;
        }
    }
    return -1;
}

pair<int,int> scoreGame(vector<Board> &boards, const vector<int> &numbers) {
    int boardsWon = 0;
    int star1 = 0;
    for (auto num: numbers) {
        for (auto &b: boards) {
            bool alreadyWon = hasWon(b);
            mark(b, num);
            if (hasWon(b)) {
                if (star1==0)
                    star1 = calculateScore(b) * num;
                if(!alreadyWon)
                    ++boardsWon;
                if(boardsWon == boards.size())
                    return {star1, calculateScore(b) * num};
                if (star1==0)
                    star1 = calculateScore(b) * num;
            }
        }
    }
    return {-1,-1};
}

void day4() {
    ifstream ifile("../day4.txt");
    string line;
    getline(ifile, line);
    vector<int> numbers;
    istringstream numberStream(line);
    int number = 0;
    char comma = 0;
    while (numberStream) {
        numberStream >> number >> comma;
        numbers.push_back(number);
    }
    vector<Board> boards;
    while (true) {
        getline(ifile, line); //read blank line
        if (!ifile)
            break;
        Board b;
        for (int i = 0; i < boardSize; ++i) {
            getline(ifile, line);
            istringstream iline(line);
            for (int j = 0; j < boardSize; ++j) {
                iline >> number;
                b[i][j] = number;
            }
        }
        boards.emplace_back(b);
    }
//    mark(boards[0],34); //34 90 18 33 83
//    mark(boards[0],27); //34 90 18 33 83
//    mark(boards[0],43); //34 90 18 33 83
//    mark(boards[0],24); //34 90 18 33 83
//    mark(boards[0],77); //34 90 18 33 83
//    cout << hasWon(boards[0]) << endl;

auto [star1,star2] = scoreGame(boards,numbers);
cout << "Day 4 star 1 = " << star1 << "\n";
cout << "Day 4 star 2 = " << star2 << "\n";
}

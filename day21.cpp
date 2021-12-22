#include <algorithm>
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

//Player 1 starting position: 4
//Player 2 starting position: 9
int rollDie() {
    static int die = 0;
    ++die;
    if (die == 101)
        die = 1;
    return die;
}

struct State {
    int p1Pos;
    int p2Pos;
    int p1Score;
    int p2Score;
};

std::ostream &operator<<(std::ostream &os, const State &s) {
    return os << "P1: " << s.p1Pos << "," << s.p1Score << "  P2: " << s.p2Pos << "," << s.p2Score << endl;
}

bool operator<(const State &s1, const State &s2) {
    return std::make_tuple(s1.p1Pos, s1.p2Pos, s1.p1Score, s1.p2Score)
           < std::make_tuple(s2.p1Pos, s2.p2Pos, s2.p1Score, s2.p2Score);
}


void day21() {
    uint64_t star1 = 0;
    uint64_t star2 = 0;
    int p1 = 4;
    int p2 = 9;
    int die = 1;
    int p1score = 0;
    int p2score = 0;
    uint64_t numRolls = 0;
    while (true) {
        p1 += rollDie() + rollDie() + rollDie();
        p1 = (p1 - 1) % 10 + 1;
        p1score += p1;
        numRolls += 3;
//        cout << "p1 " << p1score << endl;
        if (p1score >= 1000) {
            star1 = p2score * numRolls;
            break;
        }
        p2 += rollDie() + rollDie() + rollDie();
        p2 = (p2 - 1) % 10 + 1;
        p2score += p2;
        numRolls += 3;
//        cout << "p2 " << p2score << endl;
        if (p2score >= 1000) {
            star1 = p1score * numRolls;
            break;
        }
    }

    map<int, int> outcomes;
    for (int d1 = 1; d1 <= 3; ++d1)
        for (int d2 = 1; d2 <= 3; ++d2)
            for (int d3 = 1; d3 <= 3; ++d3)
                outcomes[d1 + d2 + d3]++;
//    for(auto [roll,count]:outcomes)
//        cout << roll << " " << count << endl;
    //Player 1 starting position: 4
    //Player 2 starting position: 9
    map<State, uint64_t> u;
    u[{4, 9, 0, 0}] = 1;
    uint64_t p1Wins = 0;
    uint64_t p2Wins = 0;
    while (!u.empty()) {
//        cout << p1Wins << " " << p2Wins << endl;
//        uint64_t num=0;
//        for (auto[oldState, count]: u)
//            (num+=count),cout << count << ": " << oldState;
//        cout << "Size: " << u.size() << " Universes: " << num << endl;
//        cout << num+p1Wins+p2Wins<< endl;
        map<State, uint64_t> next;
        for (auto[oldState, count]: u) {
            for (auto[roll, rollCount]: outcomes) {
                auto state = oldState;
                state.p1Pos += roll;
                state.p1Pos = (state.p1Pos - 1) % 10 + 1;
                state.p1Score += state.p1Pos;
                if (state.p1Score >= 21)
                    p1Wins += rollCount *count;
                else
                    next[state] += rollCount * count;
            }
        }
        u = next;
        next.clear();
//        num=0;
//        for (auto[oldState, count]: u)
//            (num+=count),cout << count << ": " << oldState;
//        cout << "Size: " << u.size() << " Universes: " << num << endl;

        for (auto[oldState, count]: u) {
            for (auto[roll, rollCount]: outcomes) {
                auto state = oldState;
                state.p2Pos += roll;
                state.p2Pos = (state.p2Pos - 1) % 10 + 1;
                state.p2Score += state.p2Pos;
                if (state.p2Score >= 21)
                    p2Wins += rollCount *count;
                else
                    next[state] += rollCount * count;
            }
        }
        u = next;
//        uint64_t num=0;
//        for (auto[oldState, count]: u)
//            (num+=count),cout << count << ": " << oldState;
//        cout << num << endl;
    }
    star2 = max(p1Wins, p2Wins);
    cout << p2Wins << endl;
    cout << "Day 21 star 1 = " << star1 << "\n";
    cout << "Day 21 star 2 = " << star2 << "\n";
}
// 444356092776315
// 114277904592198
// 87717061716389
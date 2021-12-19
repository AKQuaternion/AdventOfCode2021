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

int fixLine(const string &line) {
    vector<char> v;
    int val=0;
    for(auto c:line) {
        switch (c) {
            case '(':
            case '[' :
            case '{':
            case '<':
                v.push_back(c);
                break;
            case ')':
                if(v.back() == '(')
                    v.pop_back();
                else {
                    val = val*5 +1;
                    v.pop_back();
                }
                break;
            case ']':
                if(v.back() == '[')
                    v.pop_back();
                else {
                    val = val*5 +2;
                    v.pop_back();
                }
                break;
            case '}':
                if(v.back() == '{')
                    v.pop_back();
                else {
                    val = val*5 +3;
                    v.pop_back();
                }
                break;
            case '>':
                if(v.back() == '<')
                    v.pop_back();
                else {
                    val = val*5 +4;
                    v.pop_back();
                }
                break;
        }
    }
    return val;
}

vector<uint64_t> scores;

uint64_t valueLine(const string &line) {
    vector<char> v;
    for(auto c:line) {
        switch (c) {
            case '(':
            case '[' :
            case '{':
            case '<':
                v.push_back(c);
                break;
            case ')':
                if(v.back() == '(')
                    v.pop_back();
                else
                    return 3;
                break;
            case ']':
                if(v.back() == '[')
                    v.pop_back();
                else
                    return 57;
                break;
            case '}':
                if(v.back() == '{')
                    v.pop_back();
                else
                    return 1197;
                break;
            case '>':
                if(v.back() == '<')
                    v.pop_back();
                else
                    return 25137;
                break;
        }
    }
    reverse(v.begin(),v.end());
    uint64_t val=0;
    for(auto c:v) {
        switch (c) {
            case '(':
                val = val * 5 + 1;
                break;
            case '[' :
                val = val * 5 + 2;
                break;
            case '{':
                val = val * 5 + 3;
                break;
            case '<':
                val = val * 5 + 4;
                break;
        }
    }
    scores.push_back(val);
    return 0;
}

void day10() {
   auto star1 = 0;
   uint64_t star2 = 0;
   ifstream ifile("../day10.txt");
   string line;
   // ): 3 points.
    //]: 57 points.
    //}: 1197 points.
    //>: 25137 points.
   while (getline(ifile, line)) {
       star1 += valueLine(line);
   }

   sort(scores.begin(),scores.end());
   star2 = scores[scores.size()/2];
   cout << "Day 10 star 1 = " << star1 << "\n";
   cout << "Day 10 star 2 = " << star2 << "\n";
}
// 442131 too low
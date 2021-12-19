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

vector<string> digits = {
        "abcefg",
        "cf",
        "acdeg",
        "acdfg",
        "bcdf",
        "abdfg",
        "abdefg",
        "acf",
        "abcdefg",
        "abcdfg"};

void day8() {
    map<string, int> digitMap;
    int digit = 0;
    for (auto s: digits) {
        digitMap[s] = digit;
        ++digit;
    }
    auto star1 = 0;
    auto star2 = 0;
    ifstream ifile("../day8.txt");
    string line;
    vector<string> notes;
    auto sortedDigits = digits;
    sort(sortedDigits.begin(), sortedDigits.end());

    vector<vector<string>> inputs;
    vector<vector<string>> outputs;
    while (getline(ifile, line)) {
        inputs.push_back({});
        string s;
        istringstream iline(line);
        while (true) {
            iline >> s;
            if (s == "|")
                break;
            inputs.back().push_back(s);
        }
//        cout << inputs.back().size() << endl;
        outputs.push_back({});
        while (iline >> s) {
            outputs.back().push_back(s);
            if (s.size() == 2 || s.size() == 3 || s.size() == 4 || s.size() == 7)
                ++star1;
        }
//        cout << endl;
    }

    for (int i = 0; i < inputs.size(); ++i) {
        auto &input = inputs[i];
        auto &output = outputs[i];
        vector<int> perm = {0, 1, 2, 3, 4, 5, 6};
        do {
            vector<string> newDigits;
            for (auto s: input) {
                for (auto &c: s) {
                    c = 'a' + perm[c - 'a'];
                }
                sort(s.begin(),s.end());
                newDigits.push_back(s);
            }
            auto sortedNewDigits = newDigits;
            sort(sortedNewDigits.begin(), sortedNewDigits.end());
            if (sortedNewDigits == sortedDigits) {
                auto val=0;
                for (auto s: output) {
                    for (auto &c: s) {
                        c = 'a' + perm[c - 'a'];
                    }
                    sort(s.begin(),s.end());
                    cout << digitMap.at(s);
                    val = val*10+digitMap.at(s);
                }
                star2+=val;
            }
        } while (std::next_permutation(perm.begin(), perm.end()));
    }
    cout << "Day 8 star 1 = " << star1 << "\n";
    cout << "Day 8 star 2 = " << star2 << "\n";
}
//
//be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb |
//fdgacbe cefdb cefbgd gcbe
//edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec |
//fcgedb cgb dgebacf gc
//fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef |
//cg cg fdcagb cbg
//fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega |
//efabcd cedba gadfec cb
//aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga |
//gecf egdcabf bgf bfgea
//fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf |
//gebdcfa ecba ca fadegcb
//dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf |
//cefg dcbef fcge gbcadfe
//bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd |
//ed bcgafe cdgba cbgef
//egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg |
//gbdfcae bgc cg cgb
//gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc |
//fgae cfgab fg bagce

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
using std::shared_ptr;
using std::make_shared;

using Number = vector<int>;

Number parse(istream &is) {
    Number num;
    while (is) {
        if (isdigit(is.peek())) {
            int i;
            is >> i;
            num.push_back(i);
        } else {
            char c;
            is >> c;
            if (!is)
                break;
            if (c == '[')
                num.push_back(-1);
            else if (c == ']')
                num.push_back(-2);
            else if (c == ',')
                num.push_back(-3);
        }
    }
    return num;
}

bool explode(Number &nums) {
    int depth = 0;
    for (auto i = nums.begin(); i < nums.end(); ++i) {
        auto cur = *i;
        if (*i == -1)
            ++depth;
        else if (*i == -2)
            --depth;
        if (depth == 5) {
            auto left = *(i + 1);
            for (auto goLeft = i; goLeft >= nums.begin(); --goLeft)
                if (*goLeft >= 0) {
                    *goLeft += left;
                    break;
                }
            auto right = *(i + 3);
            for (auto goRight = i + 4; goRight < nums.end(); ++goRight)
                if (*goRight >= 0) {
                    *goRight += right;
                    break;
                }
            i = nums.erase(i, i + 4);
            *i = 0;
            return true;
        }
    }
    return false;
}

bool split(Number &nums) {
    int depth = 0;
    for (auto i = nums.begin(); i < nums.end(); ++i) {
        auto cur = *i;
        if (cur >= 10) {
            *i = -2;
            i = nums.insert(i, {-1, cur / 2, -3, (cur + 1) / 2});

            return true;
        }
    }
    return false;
}

void print(const Number &nums) {
    for (auto n: nums)
        if (n == -1)
            cout << "[";
        else if (n == -2)
            cout << "]";
        else if (n == -3)
            cout << ",";
        else
            cout << n << " ";
    cout << endl;
}

Number add(const Number &lhs, const Number &rhs) {
    Number out;
    out.push_back(-1);
    out.insert(out.end(), lhs.begin(), lhs.end());
    out.push_back(-3);
    out.insert(out.end(), rhs.begin(), rhs.end());
    out.push_back(-2);
    while (true) {
//        print(out);
        bool didSomething = false;
        if (explode(out))
            continue;
        if (split(out))
            continue;
        break;
    }
    return out;
}

uint64_t magnitude(const Number &nums, int &pos) {
    uint64_t left = 0;
    uint64_t right = 0;
    if (nums[pos] >= 0)
        return nums[pos++];
    if (nums[pos] == -1) {
        ++pos;
        left = magnitude(nums, pos);
        ++pos;
        right = magnitude(nums, pos);
        ++pos;
    }
    return 3 * left + 2 * right;
}

void day18() {
    uint64_t star1 = 0;
    uint64_t star2 = 0;

    ifstream ifile("../day18.txt");
    string line;
    getline(ifile, line);
    istringstream iline(line);
    Number nums = parse(iline);
    vector<Number> numbers;
    numbers.push_back(nums);
    while (getline(ifile, line)) {
        istringstream iline(line);
        Number rhs = parse(iline);
        numbers.push_back(rhs);
        nums = add(nums, rhs);
    }
    print(nums);
    int pos = 0;
    star1 = magnitude(nums, pos);

    for (int i = 0; i < numbers.size(); ++i) {
        for (int j = 0; j < numbers.size(); ++j) {
            if (i == j)
                continue;

            auto lhs = numbers[i];
            auto rhs = numbers[j];
            auto result = add(lhs, rhs);
            int pos=0;
            auto mag = magnitude(result,pos);
            star2 = max(star2,mag);
        }
    }
    cout << "Day 18 star 1 = " << star1 << "\n";
    cout << "Day 18 star 2 = " << star2 << "\n";
}
//not 2283, not 4471
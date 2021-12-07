#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void day6() {
    uint64_t star1 = 0;
    uint64_t star2 = 0;
    std::ifstream ifile("../day6.txt");
    std::string line;
    std::vector<int> timers;
    int i;
    char c;
    while(ifile>>i) {
        timers.push_back(i);
        ifile >> c;
    }

    std::cout << timers.size() << std::endl;

    std::vector<uint64_t> hist2(9);
    for(auto t:timers)
        hist2[t]++;

    for(int i=0;i<256;++i) {
        if(i==80)
            star1 = std::accumulate(hist2.begin(),hist2.end(),uint64_t(0));
        hist2[(i+7)%9] += hist2[i%9];
    }
    star2=std::accumulate(hist2.begin(),hist2.end(),uint64_t(0));
    std::cout << "Day 6 star 1 = " << star1 << "\n";
    std::cout << "Day 6 star 2 = " << star2 << "\n";
}
//Day 6 star 1 = 396210
//Day 6 star 2 = 1770823541496
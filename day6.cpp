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

    std::vector<uint64_t> histogram(9);
    for(auto t:timers)
        histogram[t]++;

    for(int i=0;i<256;++i) {
        if(i==80)
            star1 = std::accumulate(histogram.begin(),histogram.end(),uint64_t(0));
        std::rotate(histogram.begin(),histogram.begin()+1,histogram.end());
        histogram[6] += histogram[8];
    }
    star2=std::accumulate(histogram.begin(),histogram.end(),uint64_t(0));
    std::cout << "Day 6 star 1 = " << star1 << "\n";
    std::cout << "Day 6 star 2 = " << star2 << "\n";
}
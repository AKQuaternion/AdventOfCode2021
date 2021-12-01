#include <fstream>
#include <iostream>
#include <vector>

void day1() {
    auto star1 = 0;
    auto star2 = 0;
    std::ifstream ifile("../day1.txt");

    int data=-1;
    std::vector<int> numbers;
    while (ifile >> data)
        numbers.push_back(data);
    auto last1 = numbers[0];
    auto last3 = numbers[0]+numbers[1]+numbers[2];
    for(auto i=1;i<numbers.size();++i){
        auto current1 = numbers[i];
        if (current1 > last1)
            ++star1;
        last1 = current1;

        if(i+2<numbers.size()) {
            auto current3 = numbers[i] + numbers[i + 1] + numbers[i + 2];
            if (current3 > last3)
                ++star2;
            last3 = current3;
        }
    }
    std::cout << "Day nnn star 1 = " << star1 << "\n";
    std::cout << "Day nnn star 2 = " << star2 << "\n";
}

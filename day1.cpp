#include <iostream>
#include <iterator>
#include <set>
#include <vector>
#include <chrono>

int main()
{
    typedef std::istream_iterator<int> in;
    std::vector<int> v(in(std::cin), in());
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& x : v) {
        std::set<int> s;
        for (const auto& y : v) {
            auto z = 2020 - (x + y);
            if (s.find(z) != s.end()) {
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
                std::cout << x << " " << y << " " << z << " " << x*y*z << std::endl;
                std::cout << "Time: " << duration.count() << std::endl;
                return 0; 
            }
            s.insert(y);
        }
        s.insert(x);
    }
    return 1;
}
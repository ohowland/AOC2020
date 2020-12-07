#include <iostream>
#include <iterator>
#include <optional>
#include <set>
#include <vector>
#include <boost/regex.hpp>
#include <string>

boost::regex range_split{"(\\d+)-(\\d+)"};

int main() {
    typedef std::istream_iterator<std::string> in;
    std::vector<std::string> input_list(in(std::cin), in());
    
    int counter = 0;
    for (auto it = input_list.begin(); it != input_list.end(); it++) {

        boost::smatch what;
        int l_bound = 0;
        int h_bound = 0;
        if (boost::regex_search(*it, what, range_split)) {
            l_bound = std::stoi(what[1]);
            h_bound = std::stoi(what[2]);
        }
        
        it++;
        auto ch = it->substr(0,1);

        it++;
        auto password = *it;

        if ((password[l_bound-1] == ch[0]) ^ (password[h_bound-1] == ch[0])) {
            counter++;
        }
    }
    std::cout << counter << std::endl;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/regex.hpp>


struct Bag {
    std::string name;
    std::vector<Bag> contains;

    Bag()
    : name{},
      contains{}
    {}

    Bag(std::string t_name, std::vector<Bag> t_bags)
    : name{t_name},
      contains{t_bags}
      {}

    Bag(std::string t_name)
    : name{t_name},
      contains{}
      {}

};

boost::regex re_bag{"^(\\w+ \\w+) bags contain (.*)$"};
boost::regex re_contains{"^[\\s]?(\\d+) (\\w+ \\w+) bag[s.]?$"};

std::istream& operator>>(std::istream& is, Bag& b) {
    std::string line;
    std::getline(is, line, '\n');
    
    boost::smatch what;
    if (boost::regex_search(line, what, re_bag)) {
        b.name = what[1];
        
        std::string tmp{what[2]};
        std::vector<Bag> contents;
        size_t pos = 0;
        while ((pos = tmp.find(',', 0)) != std::string::npos) { 
            std::string c{tmp.substr(0, pos)};
            if (boost::regex_search(c, what, re_contains)) {
               contents.push_back(Bag(std::string{what[1]}));
            }
            tmp.erase(0, pos+1);
        } 
        b.contains = contents;
    }
    return is;
}

int main() {
    std::ifstream ifs{"./day7test.in", std::ifstream::in};
    std::istream_iterator<Bag> in(ifs);
    std::vector<Bag> bags(in, std::istream_iterator<Bag>());

    for (const auto& b : bags) {
        std::cout << b.name << std::endl;
    }

    return EXIT_SUCCESS;
}

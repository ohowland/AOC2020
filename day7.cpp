#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

#include <boost/regex.hpp>
#include <chrono>


struct Bag {
    typedef std::pair<Bag, int> bagCount;

    std::string name;
    std::vector<bagCount> contains;

    Bag()
    : name{},
      contains{}
    {}

    Bag(std::string t_name, std::vector<bagCount> t_bags)
    : name{t_name},
      contains{t_bags}
      {}

    Bag(std::string t_name)
    : name{t_name},
      contains{}
      {}

};

typedef std::pair<Bag, int> BagCount;

boost::regex re_bag{"^(\\w+ \\w+) bags contain (.*)$"};
boost::regex re_contains{"^[\\s]?(\\d+) (\\w+ \\w+) bag[s,.]*?$"};

std::istream& operator>>(std::istream& is, Bag& b) {
    std::string line;
    std::getline(is, line, '\n');
    
    boost::smatch what;
    if (boost::regex_search(line, what, re_bag)) {
        b.name = what[1];
        
        std::string tmp{what[2]};
        std::vector<BagCount> contents;
        size_t pos = 0;
        while ((pos = tmp.find(',', 0)) != std::string::npos) { 
            std::string c{tmp.substr(0, pos)};
            if (boost::regex_search(c, what, re_contains)) {
                contents.push_back(
                    BagCount{
                        Bag{std::string{what[2]}}, 
                        atoi(std::string{what[1]}.c_str())}
                        );
            }
            tmp.erase(0, pos+1);
        } 
        if (boost::regex_search(tmp, what, re_contains)) {
            contents.push_back(
                BagCount{
                    Bag{std::string{what[2]}},
                    atoi(std::string{what[1]}.c_str())}
                    );
        }
        b.contains = contents;
    }
    return is;
}

typedef std::unordered_map<std::string, std::vector<BagCount>> BagLookup;

int process_iter(const BagLookup& t_lookup, const std::vector<BagCount>& t_contents) {
    if (t_contents.empty()) {
        return 0;
    }

    for (const auto& c : t_contents) {
        if (c.first.name == "shiny gold") {
            return 1;
        }
    }

    for (const auto& c: t_contents) {
        int found = process_iter(t_lookup, t_lookup.at(c.first.name));
        if (found > 0) {
            return 1;
        }
    }
    
    return 0;
}

int process(BagLookup t_lookup) {
    int cnt = 0;
    for (const auto& b : t_lookup) {
        if (process_iter(t_lookup, b.second) > 0) {
            cnt++;
        }
    }


    return cnt;
};

int main() {
    std::istream_iterator<Bag> in(std::cin);
    std::vector<Bag> bags(in, std::istream_iterator<Bag>());

    BagLookup bagLookup{};
    for (const auto& b : bags) {
        std::pair<std::string, std::vector<BagCount>> p{b.name, b.contains};
        bagLookup.insert(p);
    }

    /*
    for (const auto& b : bags) {
        std::cout << b.name << ": " ;
        for (const auto& c : b.contains) {
            std::cout << "(" << c.second << ") " << c.first.name << ", ";
        }
        std::cout << std::endl;
    }
    */

    auto t1 = std::chrono::high_resolution_clock::now();
    int cnt{process(bagLookup)};
    auto t2 = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
    std::cout << cnt << std::endl;
    std::cout << "@" << duration.count() << " ms" << std::endl;

    return EXIT_SUCCESS;
}

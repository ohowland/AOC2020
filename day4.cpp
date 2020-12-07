#include <fstream>
#include <boost/regex.hpp>
#include "advent.hpp"

struct line {
    std::string data;
    
    operator std::string() const { return data; }

    friend std::istream& operator>>(std::istream &is, line &l) {
        std::getline(is, l.data, '\n');
        return is;
    }
};

typedef std::vector<std::string> credential;
typedef std::vector<credential> credentials;

credentials chunk(std::vector<std::string> t_data) {
    credentials cs;
    credential c;
    for (auto&& x : t_data) {
        x.erase(std::remove(x.begin(), x.end(), '\n'), x.end());
        if (x.empty()) {
            //std::cout << "found empty" << std::endl << "{ ";
            //for (auto&& xs : c) {
            //    std::cout << xs << " ";
            //}
            //std::cout << "}" << std::endl;
            cs.push_back(c);
            c.clear();
        } else {
            c.push_back(x);
        }
    }
    if (!c.empty()){
        cs.push_back(c);
    }
    return cs;
}

bool valid(credential c) {
    boost::regex year_re{"^([0-9]{4})$"};
    boost::regex full_re{"^(\\w+):(.+)$"};
    boost::regex height_re{"^(\\d+)(in|cm)$"};
    boost::regex hair_re{"^[0-9a-f]{6}$"};
    boost::regex pid_re{"^[0-9]{9}$"};
    boost::regex eye_re{"^(\\w{3})$"};
    boost::smatch entry;
    boost::smatch val;
    std::set<std::string> s;
    s.insert("byr");
    s.insert("iyr");
    s.insert("eyr");
    s.insert("hgt");
    s.insert("hcl");
    s.insert("ecl");
    s.insert("pid");
    s.insert("cid");

    for (const auto& x : c) {
        if (boost::regex_search(x, entry, full_re)) {
            if (entry[1] == "byr") {
                std::string e = entry[2];
                if (boost::regex_match(e, year_re)) {
                    s.erase("byr");
                }
            }
        }
    }

    std::set<std::string> cid;
    cid.insert("cid");
    if (s.empty() || (s == cid)) {
        return true;
    }
    return false;
}

int main() {
    std::ifstream ifs("./day4test.in", std::ifstream::in);
    std::istream_iterator<line> in(ifs);
    
    std::vector<std::string> lines(in, std::istream_iterator<line>());

    credentials cs = chunk(lines);
    int count(0);
    for (auto&& c : cs) {
        if (valid(c)) {
            count++;
        }
    }

    std::cout << "valid: " << count << std::endl;
    return EXIT_SUCCESS;
}
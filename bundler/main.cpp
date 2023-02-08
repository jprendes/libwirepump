#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <regex>

std::smatch match(std::string & input, std::string const & pattern) {
    std::regex regex{pattern, std::regex_constants::ECMAScript};
    std::smatch match;
    std::regex_match(input, match, regex);
    return match;
}

struct bundler {
  private:
    std::unordered_set<std::string> m_done;
    std::unordered_map<std::string, std::string> m_mapping;
    std::stringstream m_output;

  public:
    std::string run(std::string entry) {
        m_done.clear();
        m_output.str("");
        add(entry);
        return m_output.str();
    }

    void map(std::string const & from, std::string const & to) {
        m_mapping[from] = to;
    }

  private:
    void add(std::string path) {
        if (m_done.count(path)) return;
        m_done.insert(path);

        std::string line;
        std::fstream file{path};

        if (!file) {
            std::cerr << "Could not open " << path << '\n';
            std::exit(1);
        }
        
        while (std::getline(file, line)) {
            auto pattern = R"xx(\s*#include\s*"([^/]+)/(.+)"\s*)xx";
            if (auto m = match(line, pattern); !m.empty() && m_mapping.count(m[1])) {
                add(m_mapping[m[1]] + "/" + std::string{m[2]});
            } else {
                m_output << line << '\n';
            }
        }
    }
};

int main(int argc, char * argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " entry.hpp lib=path [lib=path [...]]\n";
        std::exit(1);
    }

    bundler bundle;

    auto pattern = R"xx(([^=]+)=(.+))xx";
    for (size_t i = 2; i < argc; ++i) {
        std::string argument{argv[i]};
        if (auto m = match(argument, pattern); !m.empty()) {
            bundle.map(m[1], m[2]);
        } else {
            std::cerr << "Invalid library mapping `" << argument << "`\n";
            std::exit(1);
        }
    }

    std::cout << bundle.run(argv[1]);

    return 0;
}

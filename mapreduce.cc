#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <algorithm>



std::vector<std::pair<std::string, int>> map(const std::string& filename) {
    std::ifstream file(filename);
    std::string s = "";
    std::vector<std::pair<std::string, int>> pairs;
    char ch;
    while(file.get(ch)) {
        if(ch == ' ' || ch == '\n' || ch == '.') {
            if (s.length() > 0) {
                pairs.push_back({s, 1});
            }
            s = "";
        }
        else {
            s.push_back(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    if (s.length() > 0) {
        pairs.push_back({s, 1});
    }
    return pairs;
}

int reduce(const std::vector<int>& values) {
    int sum = 0;
    for(int v : values) {
        sum += v;
    }
    return sum;
}

std::unordered_map<std::string, std::vector<int>> shuffle(std::vector<std::pair<std::string, int>>& pairs) {
    std::unordered_map<std::string, std::vector<int>> m;
    for(size_t i = 0; i < pairs.size(); i++) {
        m[pairs[i].first].push_back(pairs[i].second);
    }
    return m;
}

int main(int argc, char* argv[]) {
    auto pairs = map("words.txt");
    auto m = shuffle(pairs);
    std::vector<std::pair<std::string, int>> results;
    for (const auto& [word, values] : m) {
        results.push_back({word, reduce(values)});
    }
    std::sort(results.begin(), results.end());
    for (const auto& [word, count] : results) {
        std::cout << word << ": " << count << "\n";
    }
    return 0;
}



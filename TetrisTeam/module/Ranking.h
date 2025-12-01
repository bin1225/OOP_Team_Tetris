#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

class Ranking {
private:
    struct Entry {
        std::string name;
        int score;

        Entry(const std::string& n = "", int s = 0) : name(n), score(s) {}

        bool operator<(const Entry& other) const {
            return score > other.score; 
        }
    };

    vector<Entry> top10;
    const string filename;
    static const int MAX_ENTRIES = 10;

public:
    Ranking(const std::string& file = "tetris_rank.dat");

    void load();
    void save() const; 

    bool isTop10(int score) const;    
    void add(const std::string& name, int score);
    void show() const; 
};
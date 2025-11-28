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

        // 정렬을 위한 비교 연산자
        bool operator<(const Entry& other) const {
            return score > other.score; // 내림차순 정렬
        }
    };

    vector<Entry> top10;
    const string filename;
    static const int MAX_ENTRIES = 10;

public:
    Ranking(const std::string& file = "tetris_rank.dat");

    void load();                                    // 파일에서 랭킹 로드
    void save() const;                              // 파일에 랭킹 저장

    bool isTop10(int score) const;                  // Top10 진입 여부 확인
    void add(const std::string& name, int score);   // 랭킹 추가 및 정렬
    void show() const;                              // 콘솔에 랭킹 출력
};
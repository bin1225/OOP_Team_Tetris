#include "Ranking.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

Ranking::Ranking(const std::string& file) : filename(file) {
    load();
}

void Ranking::load() {
    top10.clear();

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        return;
    }

    int count = 0;
    inFile.read(reinterpret_cast<char*>(&count), sizeof(int));

    for (int i = 0; i < count && i < MAX_ENTRIES; i++) {
        int nameLength = 0;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(int));

        std::string name(nameLength, '\0');
        inFile.read(&name[0], nameLength);

        int score = 0;
        inFile.read(reinterpret_cast<char*>(&score), sizeof(int));

        top10.push_back(Entry(name, score));
    }

    inFile.close();
}

void Ranking::save() const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot save ranking file." << std::endl;
        return;
    }

    int count = static_cast<int>(top10.size());
    outFile.write(reinterpret_cast<const char*>(&count), sizeof(int));

    for (const auto& entry : top10) {
        int nameLength = static_cast<int>(entry.name.length());
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));
        outFile.write(entry.name.c_str(), nameLength);
        outFile.write(reinterpret_cast<const char*>(&entry.score), sizeof(int));
    }

    outFile.close();
}

bool Ranking::isTop10(int score) const {
    if (top10.size() < MAX_ENTRIES) {
        return true;
    }

    return score > top10.back().score;
}

void Ranking::add(const std::string& name, int score) {
    top10.push_back(Entry(name, score));

    std::sort(top10.begin(), top10.end());

    if (top10.size() > MAX_ENTRIES) {
        top10.resize(MAX_ENTRIES);
    }

    save();
}

void Ranking::show() const {
    std::cout << "\n========================================\n";
    std::cout << "           TOP 10 RANKINGS\n";
    std::cout << "========================================\n";

    if (top10.empty()) {
        std::cout << "No rankings yet.\n";
    }
    else {
        std::cout << std::left << std::setw(5) << "Rank"
            << std::setw(20) << "Name"
            << std::right << std::setw(10) << "Score" << "\n";
        std::cout << "----------------------------------------\n";

        for (size_t i = 0; i < top10.size(); i++) {
            std::cout << std::left << std::setw(5) << (i + 1)
                << std::setw(20) << top10[i].name
                << std::right << std::setw(10) << top10[i].score << "\n";
        }
    }

    std::cout << "========================================\n\n";
}
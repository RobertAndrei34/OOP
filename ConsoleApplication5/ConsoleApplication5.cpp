#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <queue>

using namespace std;

struct WordData {
    string word; 
    int frequency;
    bool operator<(const WordData& other) const {
       
        if (frequency != other.frequency) {
            return frequency < other.frequency;
        }
        return word > other.word; 
    }
};

int main() {
    ifstream fin("file.txt"); 

    if (!fin.is_open()) {
        cout << "error" << endl;
        return 1;
    }

    string proposition;
    getline(fin, proposition);

    for (int i = 0; i < proposition.size(); i++) {
        proposition[i] = tolower(proposition[i]);
    }

    map<string, int> word_map; 
    string limitator = " ,.!?"; 
    size_t index = proposition.find_first_of(limitator);

    while (index < proposition.size()) {
        while (index == 0) { 
            proposition = proposition.substr(1);
            index = proposition.find_first_of(limitator);
        }
        
        word_map[proposition.substr(0, index)]++;
        proposition = proposition.substr(index + 1);
        index = proposition.find_first_of(limitator); 
    }

    priority_queue<WordData> word_queue;

    for (const auto& pair : word_map) {
        word_queue.push({ pair.first, pair.second });
    }

    while (!word_queue.empty()) {
        cout << word_queue.top().word << " => " << word_queue.top().frequency << endl;
        word_queue.pop(); 
    }


    fin.close();

    return 0; 
}
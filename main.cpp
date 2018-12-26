//
//  main.cpp
//  MasterMind
//
//  Created by Jaeyoon Kim on 12/25/18.
//  Copyright © 2018 Jaeyoon Kim. All rights reserved.
//

#include <iostream>
#include <utility>
#include "Row.hpp"
#include <set>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

int main(int argc, const char * argv[]) {
    vector<Row> all_possibilities;
    all_possibilities.reserve(pow(num_colors, col_size));
    for (int c1 = 0; c1 < num_colors; ++c1) {
        for (int c2 = 0; c2 < num_colors; ++c2) {
            for (int c3 = 0; c3 < num_colors; ++c3) {
                for (int c4 = 0; c4 < num_colors; ++c4) {
                    all_possibilities.emplace_back(c1,c2,c3,c4);
                }
            }
        }
    }
    set<Row> remaining(all_possibilities.begin(), all_possibilities.end());
    int turn = 1;
    while (true) {
        int min_mesh = numeric_limits<int>::max();
        auto guess_it = all_possibilities.begin();
        for (auto it = all_possibilities.begin(); it != all_possibilities.end(); ++it) {
            int test_mesh = it->mesh(remaining);
            if (test_mesh < min_mesh) {
                min_mesh = test_mesh;
                guess_it = it;
            }
        }
        cout << "Turn: " << turn++ << " My guess is: ";
        guess_it->print();
        
        cout << "Number of black pins: ";
        int black;
        if (!(cin >> black)) {
            cout << "You didn't enter a number!\n";
            return 0;
        }
        cout << "Number of white pins: ";
        int white;
        if (!(cin >> white)) {
            cout << "You didn't enter a number!\n";
            return 0;
        }
        if (black == 4) {
            cout << "So I was right!\n";
            return 0;
        }
        
        auto it = remaining.begin();
        while (it != remaining.end()) {
            pair<int, int> outcome = guess_it->match(*it);
            if (outcome.first != white || outcome.second != black) {
                remaining.erase(it++);
            } else {
                ++it;
            }
        }
        cout << "Number of potential solutions: " << remaining.size() << endl;
        
        if (remaining.empty()) {
            cout << "Oops! Something went wrong. Finishing the program\n";
            return 0;
        }
        if (remaining.size() == 1) {
            cout << "Solved it! The answer is ";
            remaining.begin()->print();
            return 0;
        }
    }
    
    return 0;
}

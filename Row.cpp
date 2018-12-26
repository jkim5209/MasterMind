//
//  Row.cpp
//  MasterMind
//
//  Created by Jaeyoon Kim on 12/26/18.
//  Copyright © 2018 Jaeyoon Kim. All rights reserved.
//

#include "Row.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Row::Row(int c1, int c2, int c3, int c4) : colors({c1, c2, c3, c4}) {
    vector<int> temp(num_colors, 0);
    for (int c: colors) {
        ++temp[c];
    }
    colors_repeat = move(temp);
}

pair<int, int> Row::match(const Row& panswer) const {
    int num_match = 0;
    for (int i = 0; i < num_colors; ++i) {
        num_match += min(panswer.colors_repeat[i], colors_repeat[i]);
    }
    
    int black = 0;
    for (int i = 0; i < col_size; ++i) {
        if (panswer.colors[i] == colors[i]) ++black;
    }
    
    return make_pair(num_match - black, black);
}

bool Row::operator< (const Row& other) const {
    return colors < other.colors;
}

int Row::mesh(const set<Row>& possibilities) const {
    vector<vector<int>> repeats;
    for (int i = 0; i <= col_size; ++i) {
        repeats.emplace_back(col_size + 1, 0);
    }
    
    for (auto r : possibilities) {
        auto output = match(r);
        ++repeats[output.first][output.second];
    }
    
    int max = 0;
    for (int i = 0; i <= col_size; ++i) {
        for (int j = 0; j <= col_size; ++j) {
            if (repeats[i][j] > max) {
                max = repeats[i][j];
            }
        }
    }
    return max;
}

void Row::print() const {
    static const vector<string> int_to_color = {"black ", "white ", "red ", "yellow ", "green ", "blue "};
    for (auto c : colors) {
        cout << int_to_color[c];
    }
    cout << endl;
}

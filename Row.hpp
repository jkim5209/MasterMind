//
//  Row.hpp
//  MasterMind
//
//  Created by Jaeyoon Kim on 12/25/18.
//  Copyright © 2018 Jaeyoon Kim. All rights reserved.
//

#ifndef Row_hpp
#define Row_hpp

#include <utility>
#include <vector>
#include <set>

const int col_size = 4;
const int num_colors = 6;

class Row {
public:
    Row(int, int, int, int);
    std::pair<int, int> match(const Row& panswer) const; // given potential answer, returns number of white and block pins
    bool operator< (const Row&) const;
    int mesh(const std::set<Row>& possibilities) const;
    void print() const;
private:
    std::vector<int> colors;
    std::vector<int> colors_repeat;
};
#endif /* Row_hpp */

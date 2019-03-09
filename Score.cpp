/********************
 *  Created by Manxin Zhang
 *  CIS29 / Group #4
 ********************/
#include "Score.h"

bool Score::operator>(const Score obj) const {
    return score > obj.score;
}

string Score::toString() {
    stringstream ss;
    ss << left << setw(20) << name;
    ss << setw(5) << score;
    return ss.str();
}

ostream& operator<<(ostream& out, Score s) {
    out << left << setw(20) << s.getName();
    out << setw(5) << s.getScore();
    return out;
}

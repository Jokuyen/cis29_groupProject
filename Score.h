/********************
 *  Created by Manxin Zhang
 *  CIS29 / Group #4
 ********************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;


class Score
{
    int score;
    string name;
public:
    Score() : score(0), name() {}
    Score(int s, string nm) : score(s), name(nm) {}
    int getScore() { return score; }
    string getName() { return name; }
    bool operator>(const Score obj) const;
    string toString();
};

ostream& operator<<(ostream& out, Score s);

/********************
 *  Created by Manxin Zhang
 *  CIS29 / Group #4
 ********************/
#include "Score.h"

/*
 Description: This function overloads the greater than operator and returns true or false accordingly.
 Parameters: Score object to compare with
 
 */
bool Score::operator>(const Score obj) const {
    return score > obj.score;
}

/*
 Description: This function converts the score object to a string in a specific format.
 Return: String containing details of the score object.

 */
string Score::toString() {
    stringstream ss;
    ss << left << setw(20) << name;
    ss << setw(5) << score;
    return ss.str();
}

/*
 Description: This function overloads insertion operator, adding a string with a specific format to the output stream.
 Parameters: output stream, score object to be used
 Return: Ouput stream containing formatted string.
 
 
 */
ostream& operator<<(ostream& out, Score s) {
    out << left << setw(20) << s.getName();
    out << setw(5) << s.getScore();
    return out;
}

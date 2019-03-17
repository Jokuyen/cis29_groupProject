/********************
 *  Created by Manxin Zhang
 *  CIS29 / Group #4
 ********************/

/*
 This screen includes a display of the high scores.
 */

#include <iostream>
#include <fstream>
using namespace std;

#include "cScreen.h"
#include "Score.h"
#include <SFML/Graphics.hpp>

const size_t MAXNUMOFSCORES = 10;
int processScores(const char* filename, Score scores[]);
bool sort(Score scores[]);
bool writeScoresToFile(const char* ScoresFile, Score scores[]);
void storeScore(const char* filename, Score scores[], Score score);
void initializeScores(Score scores[]);
void eraseScoreFile(const char* filename);

class screen_5 : public cScreen
{
public:
    screen_5(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_5::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    const char* filename = "ScoreFile.bin";
    Score scores[MAXNUMOFSCORES];
    initializeScores(scores);
    eraseScoreFile(filename);
    Score iris(100, "iris");
    Score a(15, "a");
    Score b(20, "b");
    Score c(23, "c");
    Score d(52, "d");
    Score e(40, "e");
    Score f(98, "f");
    Score g(140, "g");
    Score h(86, "h");
    Score i(15, "i");
    Score j(200, "j");
    storeScore(filename, scores, iris);
    storeScore(filename, scores, a);
    storeScore(filename, scores, b);
    storeScore(filename, scores, c);
    storeScore(filename, scores, d);
    storeScore(filename, scores, e);
    storeScore(filename, scores, f);
    storeScore(filename, scores, g);
    storeScore(filename, scores, h);
    storeScore(filename, scores, i);
    storeScore(filename, scores, j);
    for (int i = 0; i < 10; i++) {
        cout << scores[i] << endl;
    }
    
    bool Running = true;
    
    
    sf::Font font;
    try { // throws error if file not opened
        if(!font.loadFromFile(FONTIMAGE))
        {
            throw FileOpenException(FONTIMAGE);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    
    
    sf::Text text("", font);
    ostringstream sout;
    sout << "Score Board" << endl;
    for (int i = 0; i < MAXNUMOFSCORES; i++) {
        sout << setw(2) << (i + 1) << " " << scores[i].toString() << "\n";
    }
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::White);
    
    text.setString(sout.str());
    
    // Center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
    
    sf::Event event;
    while (Running)
    {
        // Verifying events
        while (App.pollEvent(event))
        {
            // Window closed
            if (event.type == sf::Event::EventType::Closed)
                return (-1);
            // Key pressed
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Return: // Progress to screen_0
                        return (0);
                        break;
                    case sf::Keyboard::Backspace: // Return to screen_4
                        return (4);
                        break;
                    default:
                        break;
                }
            }
        }
        
        App.clear();
        App.draw(text);
        App.display();
    }
    
    return (-1);
}

int processScores(const char* filename, Score scores[]) {
    int count = 0;
    ifstream fin(filename, ios::binary | ios::in);
    if (!fin) {
        cout << "File not found. Creating new file: " << filename << endl;
        ofstream fout(filename);
        fout.close();
        return count;
    }
    fin.seekg(0, ios_base::beg);
    int c = fin.peek();
    while (c != EOF) {
        fin.read(reinterpret_cast<char*>(&scores[count]), sizeof(scores[count]));
        if (fin.eof()) break;
        count++;
        c = fin.peek();
    }
    fin.close();
    return count;
}

bool sort(Score scores[]) {
    bool swapOccurred;
    do
    {
        swapOccurred = false;
        for (int i = 0; i < MAXNUMOFSCORES - 1; i++)
        {
            if (scores[i + 1] > scores[i])
            {
                swap(scores[i], scores[i + 1]);
                swapOccurred = true;
            }
        }
    } while (swapOccurred);
    return true;
}

bool writeScoresToFile(const char* filename, Score scores[]) {
    ofstream fout(filename, ios::binary);
    if (!fout)
    {
        cerr << "Unable to open input text file " << filename << endl;
        exit(2);
    }
    for (int i = 0; i < MAXNUMOFSCORES; i++) {
        fout.write(reinterpret_cast<const char*>(&scores[i]), sizeof(Score));
    }
    fout.close();
    return true;
}

void storeScore(const char* filename, Score scores[], Score score) {
    int count = processScores(filename, scores);
    if (count < MAXNUMOFSCORES) {
        scores[count++] = score;
    }
    else if (score > scores[MAXNUMOFSCORES - 1])
        scores[MAXNUMOFSCORES - 1] = score;
    else return;
    sort(scores);
    writeScoresToFile(filename, scores);
}

void initializeScores(Score scores[]) {
    for (int i = 0; i < 10; i++) {
        scores[i] = Score(0, "None");
    }
}

void eraseScoreFile(const char* filename) {
    ofstream fout(filename);
}

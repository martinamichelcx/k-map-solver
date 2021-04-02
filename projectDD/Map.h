#ifndef MAP_H
#define MAP_H

#include "Header.h"



class Maps {
public:
    int variables;
    vector<int> mins;
    vector<string> minterms;
    vector<vector<int>> kmap;
    vector<vector<RectangleShape>> guiMap;

    Maps(int);

    //void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

    // a function to create the letters to be used in this kind of map
    vector<char> getVariables();

    // a function to convert the decimal minterm input into binary
    void createSMin();

    // a function which changes decimal to binary
    string toBinary(int n);

    // a function which adds zeros to the terms (according to the number of variables) after converting from decimal to binary
    string addZeros(string term);

    // a function which checks if two terms differ by one bit
    bool isConsecutive(string term1, string term2);

    // a function which returns the minterms without the unnecessary letters ( to be used in refining )
    vector<string> removeStars();

    // a function which changes the letters that are not important between two terms
    string changeUnwanted(string term1, string term2);

    // a function which reduces the current minterms to a simpler form
    vector<string> minimize();

    // a function that changes the binary minterms to letters equivalent
    string getImplicants(string s);

    // a function that creates the vector that represents the kmap
    void initializeMap();

    // a function which maps each minterm to its place then prints the kmap
    void printKmap(bool, string);

    // a function to remove unecessary minterms that their ones are already used in an implicant
    void refine();

    // a function that gets the minterms from the user
    vector<int> getMinterms();

    // a function that minimizes till convergence and then refines the output to display it
    string printSimplified(bool);

    // a function to check if two vectors are equal
    bool VectorsEqual(vector<string> a, vector<string> b);

};

#endif
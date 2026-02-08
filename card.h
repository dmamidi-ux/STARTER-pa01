// card.h
// Author: Devesh Mamidi
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

class Card {
    public:
        Card(const string& s);
        char getSuite();
        int getNumber();

        bool operator<(const card& other);
    private:
        int number;
        char suite;
};

#endif

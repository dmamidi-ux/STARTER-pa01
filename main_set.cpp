// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  set<Card> player1;
  set<Card> player2;
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    player1.insert(Card(line[0], line[2]));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    player2.insert(Card(line[0], line[2]));
  }
  cardFile2.close();
  
  auto it1 = player1.begin();
  auto end = player2.begin();
  auto it2 = player2.begin();
  end++;

  while(end != player2.end()) {
    it2 = end;
    end++;
  }

  while(it1 != player1.end() && it2 != player2.end() && (it2 != player2.begin())) {
    while(it1 != player1.end() && player2.find(*it1) == player2.end()) {
      it1++;
    }
    if(it1 != player1.end() && (player2.find(*it1) != player2.end())) {
      cout << "Alice picked matching card " << *it1 << endl;
      auto temp = it1;
      it1++;
      if(*it2 == *temp) {
        it2--;
      }
      player2.erase(*temp);
      player1.erase(temp);
    }
    if(it1 != player1.end()) {
      while(it2 != player2.end() && it2 != player2.begin() && (player1.find(*it2) == player1.end())) {
        it2--;
      }
      if(it2 != player2.end() && player1.find(*it2) != player1.end()) {
        cout << "Bob picked matching card " << *it2 << endl;
        auto temp = it2;
        it2--;
        if(*it1 == *temp) {
          it1++;
        }
        player1.erase(*temp);
        player2.erase(temp);
      }
    }
  }

  it1 = player1.begin();
  it2 = player2.begin();
  
  cout << endl;

  cout << "Alice's cards:" << endl;
  while(it1 != player1.end()) {
    cout << *it1 << endl;
    it1++;
  }

  cout << endl;

  cout << "Bob's cards:" << endl;
  while(it2 != player2.end()) {
    cout << *it2 << endl;
    it2++;
  }

  return 0;
}

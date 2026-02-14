#include "card.h"
#include "card_list.h"
#include <iostream>
#include <string>

using namespace std;

string result(bool b) {
    if(b) {
        return "PASSED";
    } else {
        return "FAILED";
    }
}

int main() {
    Card_List c;

    cout << "contains() & iterator check on empty Card_List: " << result(!c.contains(Card('c','2')) && c.begin() == c.end() && c.rbegin() == c.rend()) << endl;

    c.insert(Card('c', '5'));
    auto it = c.begin();

    cout << "insert() on empty Card_List then contains() & iterator dereferencing: " << result(c.contains(Card('c', '5')) && *it == Card('c', '5')) << endl;

    c.insert(Card('s', '1'));
    it++;

    cout << "insert() on single size Card_List then contains() & iterator traversal: " << result(c.contains(Card('s', '1')) && *it == Card('s','1')) << endl;

    c.insert(Card('c', '5'));
    c.remove(Card('c', '5'));

    cout << "insert() with duplicate then remove() then contains(): " << result(!c.contains(Card('c', '5'))) << endl;

    c.remove(Card('h', '9'));

    cout << "remove() non-existent card then contains(): " << result(c.contains(Card('s', '1'))) << endl;

    it++;
    c.remove(Card('s', '1'));

    cout << "iterator traversal past end & remove() on single size Card_List: " << result(it == c.end() && !c.contains(Card('c','2'))) << endl;

    c.remove(Card('d', '2'));

    cout << "remove() on empty Card_List: " << result(!c.contains(Card('c','2'))) << endl;

    c.insert(Card('h', 'k'));
    c.insert(Card('h', 'q'));

    it = c.rbegin();
    it--;
    it--;
    it--;

    cout << "insert() 2 consecutive times & reverse traversal from rbegin to rend: " << result(c.contains(Card('h', 'k')) && c.contains(Card('h', 'q')) && it == c.rend()) << endl;

    c.insert(Card('c', 'j'));
    c.remove(Card('h', 'k'));
    it = c.begin();
    it++;

    cout << "insert() 1 time then remove() 1 time & compare different iterators: " << result(it != c.begin() && *it == Card('h', 'q') && *c.begin() == Card('c', 'j')) << endl;

    Card_List a;
    Card_List b;

    a.insert(Card('d', '7'));
    a.insert(Card('d', '5'));
    a.insert(Card('h', 'a'));

    cout << "- - - playGame() w/ one empty hand expected output:" << endl << endl;

    cout << "Alice's cards:" << endl;
    cout << "d 5" << endl;
    cout << "d 7" << endl;
    cout << "h a" << endl;
    cout << endl;
    cout << "Bob's cards:" << endl;
    cout << endl;

    cout << "- - - actual output:" << endl << endl;
    playGame(a, b);

    b.insert(Card('s', '9'));
    b.insert(Card('d', '5'));
    b.insert(Card('h', 'a'));

    cout << "- - - playGame() w/ two matches & removals expected output:" << endl << endl;

    cout << "Alice picked matching card d 5" << endl;
    cout << "Bob picked matching card h a" << endl;
    cout << endl;
    cout << "Alice's cards:" << endl;
    cout << "d 7" << endl;
    cout << endl;
    cout << "Bob's cards:" << endl;
    cout << "s 9" << endl;
    cout << endl;

    cout << "- - - actual output:" << endl << endl;
    playGame(a, b);

    a.insert(Card('c', '6'));
    a.insert(Card('d', '2'));
    b.insert(Card('h', 'k'));
    b.insert(Card('c', '3'));

    cout << "- - - playGame() w/ no matches expected output:" << endl << endl;

    cout << "Alice's cards:" << endl;
    cout << "c 6" << endl;
    cout << "d 2" << endl;
    cout << "d 7" << endl;
    cout << endl;
    cout << "Bob's cards:" << endl;
    cout << "c 3" << endl;
    cout << "s 9" << endl;
    cout << "h k" << endl;
    cout << endl;

    cout << "- - - actual output:" << endl << endl;
    playGame(a, b);

    return 0;
}
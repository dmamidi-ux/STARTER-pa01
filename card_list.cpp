// card_list.cpp
// Author: Devesh Mamidi and Jeremiah De Guzman
// Implementation of the classes defined in card_list.h

#include "card_list.h"

Card_List::Card_List() {
    root = nullptr;
}

Card_List::~Card_List() {
    clear(root);
}

void Card_List::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

void Card_List::insert(const Card& c) {
    if (!root) {
        root = new Node(c);
        root->parent = nullptr;
        return;
    }
    insert(root, c);
}

void Card_List::insert(Node* n, const Card& c) {
    if (c < n->data) {
        if (!n->left) {
            n->left = new Node(c);
            n->left->parent = n;
        } else {
            insert(n->left, c);
        }
    }
    else if (n->data < c) {
        if (!n->right) {
            n->right = new Node(c);
            n->right->parent = n;
        } else {
            insert(n->right, c);
        }
    }
}

bool Card_List::contains(const Card& c) const {
    Node* n = root;

    while (n) {
        if (c < n->data)
            n = n->left;
        else if (n->data < c)
            n = n->right;
        else
            return true;
    }
    return false;
}

void Card_List::remove(Card c) {
    Node* n = root;

    while (n && n->data != c) {
        if (c < n->data)
            n = n->left;
        else if (n->data < c)
            n = n->right;
    }

    if (!n) return;

    if (n->left && n->right) {
        Node* s = successor(n);
        n->data = s->data;
        n = s;
    }

    Node* child = (n->left) ? n->left : n->right;

    if (child)  child->parent = n->parent;
    if (!n->parent) root = child;
    else if (n == n->parent->left) n->parent->left = child;
    else n->parent->right = child;

    delete n;
}

Card_List::Node* Card_List::minimum(Node* n) const {
    while (n && n->left)
        n = n->left;
    return n;
}

Card_List::Node* Card_List::maximum(Node* n) const {
    while (n && n->right)
        n = n->right;
    return n;
}

Card_List::Node* Card_List::successor(Node* n) const {
    if (!n) return nullptr;

    if (n->right)
        return minimum(n->right);

    Node* p = n->parent;
    while (p && n == p->right) {
        n = p;
        p = p->parent;
    }
    return p;
}

Card_List::Node* Card_List::predecessor(Node* n) const {
    if (!n) return nullptr;

    if (n->left)
        return maximum(n->left);

    Node* p = n->parent;
    while (p && n == p->left) {
        n = p;
        p = p->parent;
    }
    return p;
}

const Card& Card_List::Iterator::operator*() const {
    return node->data;
}

const Card* Card_List::Iterator::operator->() const {
    return &(node->data);
}

Card_List::Iterator Card_List::Iterator::operator++() {
    if (node) {
        node = tree->successor(node);
    }
    return *this;
}

Card_List::Iterator Card_List::Iterator::operator--() {
    if (node) {
        node = tree->predecessor(node);
    }
    return *this; 
}

Card_List::Iterator Card_List::begin() {
    return Iterator(minimum(root), this);
}

Card_List::Iterator Card_List::end() {
    return Iterator(nullptr, this);
}

Card_List::Iterator Card_List::rbegin() {
    return Iterator(maximum(root), this);
}

Card_List::Iterator Card_List::rend() {
    return Iterator(nullptr, this);
}

void playGame(Card_List & p1, Card_List & p2) {
    bool foundMatch = true;

    while (foundMatch) {
        foundMatch = false;

        for (auto it1 = p1.begin(); it1 != p1.end(); ++it1) {
            if (p2.contains(*it1)) {
                Card match = *it1;
                cout << "Alice picked matching card " << match << endl;
                
                p1.remove(match);
                p2.remove(match);
                
                foundMatch = true;
                break; 
            }
        }

        if (!foundMatch) break; 

        foundMatch = false;
        for (auto it2 = p2.rbegin(); it2 != p2.rend(); --it2) {
            if (p1.contains(*it2)) {
                Card match = *it2;
                cout << "Bob picked matching card " << match << endl;
                
                p1.remove(match);
                p2.remove(match);
                
                foundMatch = true;
                break; 
            }
        }
    }

    cout << endl << "Alice's cards:" << endl;
    for (auto it = p1.begin(); it != p1.end(); ++it) {
        cout << *it << endl;
    }

    cout << endl << "Bob's cards:" << endl;
    for (auto it = p2.begin(); it != p2.end(); ++it) {
        cout << *it << endl;
    }
}
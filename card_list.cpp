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

Card_List::Iterator Card_List::Iterator::operator++(int) {
    Iterator temp = *this;
    if (node) {
        node = tree->successor(node);
    }
    return temp;
}

Card_List::Iterator Card_List::Iterator::operator--(int) {
    Iterator temp = *this;
    if (node) {
        node = tree->predecessor(node);
    } 
    return temp;
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
  auto it1 = p1.begin();
  auto it2 = p2.rbegin();

  while(it1 != p1.end() && it2 != p2.rend()) {
    while(it1 != p1.end() && !p2.contains(*it1)) {
      it1++;
    }
    if(it1 != p1.end() && p2.contains(*it1)) {
      cout << "Alice picked matching card " << *it1 << endl;
      auto temp = it1;
      it1++;
      if(*it2 == *temp) {
        it2--;
      }
      p2.remove(*temp);
      p1.remove(*temp);
    }
    if(it1 != p1.end()) {
      while(it2 != p2.rend() && !p1.contains(*it2)) {
        it2--;
      }
      if(it2 != p2.rend() && p1.contains(*it2)) {
        cout << "Bob picked matching card " << *it2 << endl;
        auto temp = it2;
        it2--;
        if(*it1 == *temp) {
          it1++;
        }
        p1.remove(*temp);
        p2.remove(*temp);
      }
    }
  }

  it1 = p1.begin();
  it2 = p2.begin();
  
  cout << endl;

  cout << "Alice's cards:" << endl;
  while(it1 != p1.end()) {
    cout << *it1 << endl;
    it1++;
  }

  cout << endl;

  cout << "Bob's cards:" << endl;
  while(it2 != p2.end()) {
    cout << *it2 << endl;
    it2++;
  }
}
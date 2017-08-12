#include "Node.h"

Node::Node() {
  this->isGuard = true;
}

Node::Node(int symbol) {
  this->isGuard = false;
  this->symbol = symbol;
}

Node::Node(bool isGuard) {
  this->isGuard = isGuard;
}

//Return the hashCode of the pair
int Node::hashCode() {
  int combined = ((this->symbol << 16) | (this->symbol >> 16)) ^ (this->next->symbol);
  return (combined * (combined + 3));
}


bool Node::digramOverlap(Node* other) {
  return this->next == other || this->prev == other;
}

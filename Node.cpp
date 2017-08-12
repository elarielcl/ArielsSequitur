#include "Node.h"
#include "Rule.h"

Node::Node(Rule* rule) {
  this->isGuard = true;
  this->rule = rule;
}

Node::Node(Rule* rule, int symbol) {
  this->isGuard = false;
  this->symbol = symbol;
  this->rule = rule;
}

Node::Node(Rule* rule, bool isGuard) {
  this->isGuard = isGuard;
  this->rule = rule;
}

//Return the hashCode of the pair
int Node::hashCode() {
  int combined = ((this->symbol << 16) | (this->symbol >> 16)) ^ (this->next->symbol);
  return (combined * (combined + 3));
}


bool Node::digramOverlap(Node* other) {
  return this->next == other || this->prev == other;
}

void Node::printRule() {
  Node* current = this;
  while (!current->isGuard) current = current->next;
  current->rule->print();
}

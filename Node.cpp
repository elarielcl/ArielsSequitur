#include "Node.h"
#include "Rule.h"
#include "SequiturGrammar.h"
#include <iostream>

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
  return this->next == other || this->prev == other; // same?
}

void Node::printRule() {
  Node* guard = this;
  while (!guard->isGuard) guard=guard->next;
  std::cout << "RULE USAGE=" << guard->rule->usage << ", ";
  std::cout << guard->prev->symbol;
  std::cout << " -> ";
  Node* t = guard->next;
  while (!t->isGuard) {
    if (t->symbol<this->rule->grammar->M)
      std::cout <<  (char)t->symbol<< " ";
    else {
      std::cout <<  t->symbol<< " ";
    //  std::cout << "RULE TO PRINT=" << t->rule->guard->prev->symbol << std::endl;
    }
    t = t->next;
  }
  std::cout << std::endl;
}

void Node::printDigram() {
  if (this->symbol < this->rule->grammar->M)
    std::cout << (char)this->symbol << ",";
  else
    std::cout << this->symbol << ",";

  if (this->next->symbol < this->rule->grammar->M)
    std::cout << (char)this->next->symbol << std::endl;
  else
    std::cout << this->next->symbol << std::endl;
}

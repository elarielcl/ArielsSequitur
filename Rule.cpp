#include <iostream> //Remove
#include "Rule.h"
#include "Node.h"
#include "Dictionary.h"

Rule::Rule(int c, Dictionary* index) {
  Node* nonTerminal = new Node(c);
  Node* guard = new Node(true);
  nonTerminal->next = guard;
  guard->prev = nonTerminal;
  guard->next = guard;

  this->guard = guard;
  this->last = guard;
  this->index = index;
  this->n = 0;
  this->usage = 0;
}

void Rule::put(int c) {
  ++this->n;
  Node* n = new Node(c);
  this->last->next = n;
  n->prev = this->last;
  n->next = this->guard;
  this->last = n;
  if (this->n >= 2) {
    if (!this->index->get(this->last->prev))
      this->index->put(this->last->prev);
  }
}

void Rule::print() {
  std::cout << (char)this->guard->prev->symbol;
  std::cout << " -> ";
  Node* t = this->guard->next;
  while (!t->isGuard) {
    std::cout <<  (char)t->symbol;
    t = t->next;
  }
  std::cout << std::endl;

}

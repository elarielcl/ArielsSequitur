#include <iostream> //Remove
#include "Rule.h"
#include "Node.h"
#include "Dictionary.h"
#include "SequiturGrammar.h"
#include <vector>

Rule::Rule(int c, SequiturGrammar* grammar) {
  Node* nonTerminal = new Node(this, c);
  Node* guard = new Node(this, true);
  nonTerminal->next = guard;
  guard->prev = nonTerminal;
  guard->next = guard;

  this->guard = guard;
  this->last = guard;
  this->grammar = grammar;
  this->n = 0;
  this->usage = 0;
  this->printed = false;
}

void Rule::put(int c) {
  ++this->n;
  Node* n = new Node(this, c);
  this->last->next = n;
  n->prev = this->last;
  n->next = this->guard;
  this->last = n;
  if (this->n >= 2) {
    this->grammar->index->putUnique(this->last->prev);
  }
}


void Rule::print() {
  std::vector<Rule*> v;
  this->printed = true;
  //std::cout << "RULE USAGE=" << this->usage << ", ";
  std::cout << this->guard->prev->symbol-this->grammar->M;
  std::cout << "->";
  Node* t = this->guard->next;
  while (!t->isGuard) {
    if (t->symbol<this->grammar->M)
      std::cout <<  (char)t->symbol<< " ";
    else {
      std::cout <<  t->symbol-this->grammar->M<< " ";
    //  std::cout << "RULE TO PRINT=" << t->rule->guard->prev->symbol << std::endl;
      if (!t->rule->printed) {
        v.push_back(t->rule);
        //std::cout << "\nPutting printed to=" << t->rule->guard->prev->symbol << std::endl;
      }
    }
    t = t->next;
  }
  std::cout << std::endl;
  //std::cout << "SUB RULES TO PRINT=" << v.size() << std::endl;
  for (int i = 0; i<v.size(); ++i) {
    if (!v[i]->printed)v[i]->print();
    //std::cout << "\nPutting UNprinted to=" << v[i]->guard->prev->symbol << std::endl;

  }
}

void Rule::printUncompress() {
  Node* current = this->guard->next;
  while (!current->isGuard) {
    if (current->symbol < this->grammar->M)
      std::cout << (char)current->symbol;
    else
      current->rule->printUncompress();
    current = current->next;
  }
}

#include "Rule.h"
#include "Node.h"
#include "SequiturGrammar.h"
#include <iostream>
#include <vector>
#include <string>

SequiturGrammar* Rule::grammar = NULL;

Rule::Rule(int c, SequiturGrammar* grammar):
symbol(c),
usage(0),
printed(false) {
  Node* guard = new Node(this);
  guard->connect(guard);
  this->guard = guard;
  this->grammar = grammar;
}

void Rule::print() {
  std::vector<Rule*> v;
  this->printed = true;
  std::cout << "S" << this->symbol-this->grammar->M;
  std::cout << "->";
  Node* t = this->guard->next;
  while (!t->isGuard()) {
    if (t->symbol<this->grammar->M)
      std::cout <<  (char)t->symbol<< " ";
    else {
      std::cout <<  "S" << t->symbol-this->grammar->M << " ";
      if (!t->rule->printed)
        v.push_back(t->rule);
    }
    t = t->next;
  }
  std::cout << std::endl;
  for (int i = 0; i<v.size(); ++i)
    if (!v[i]->printed)v[i]->print();
}

void Rule::printUncompress() {
  Node* current = this->guard->next;
  while (!current->isGuard()) {
    if (current->symbol < this->grammar->M)
      std::cout << (char)current->symbol;
    else
      current->rule->printUncompress();
    current = current->next;
  }
}

void Rule::getUncompress(std::string* s) {
  Node* current = this->guard->next;
  while (!current->isGuard()) {
    if (current->symbol < this->grammar->M)
      (*s)+= (char)current->symbol;
    else
      current->rule->getUncompress(s);
    current = current->next;
  }
}

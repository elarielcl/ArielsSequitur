#include <iostream>//Delete
#include "SequiturGrammar.h"
#include "Dictionary.h"
#include "Rule.h"
SequiturGrammar::SequiturGrammar() {
  this->index = new Dictionary(10000, this);
  //128 first value after ASCII values
  this->initialRule = new Rule(128, this); //Every rule will have a reference to the global index
  this->numberOfRules = 1;

}

void SequiturGrammar::put(int c) {
  this->initialRule->put(c);
  //this->initialRule->print();
  //this->index->print();
}

void SequiturGrammar::print() {
  this->initialRule->print();
}

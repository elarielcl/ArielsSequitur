#include <iostream>//Delete
#include "SequiturGrammar.h"
#include "Dictionary.h"
#include "Rule.h"
SequiturGrammar::SequiturGrammar() {
  this->index = new Dictionary(13);
  this->initialRule = new Rule('S', this->index); //Every rule will have a reference to the global index
}

void SequiturGrammar::put(int c) {
  this->initialRule->put(c);
}

void SequiturGrammar::print() {
  this->index->print();

  this->initialRule->print();
}

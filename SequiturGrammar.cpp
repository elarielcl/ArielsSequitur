#include <iostream>//Delete
#include "SequiturGrammar.h"
#include "Dictionary.h"
#include "Rule.h"
SequiturGrammar::SequiturGrammar() {
  this->M = 256; //Index of the min rule value
  this->index = new Dictionary(125100000, this);
  //128 first value after ASCII values
  this->initialRule = new Rule(this->M, this); //Every rule will have a reference to the global index
  this->numberOfRules = 1;

}

void SequiturGrammar::put(int c) {
  if (c >= this->M){ std::cout << c << std::endl; std::cout << this->numberOfRules << std::endl; exit(0);}
  else this->initialRule->put(c);
  //this->initialRule->print();
  //this->index->print();
}

void SequiturGrammar::print() {
  this->initialRule->print();
}

void SequiturGrammar::printUncompress() {
  this->initialRule->printUncompress();
}

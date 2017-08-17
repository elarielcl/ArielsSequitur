#include <iostream>//Delete
#include "SequiturGrammar.h"
#include "Dictionary.h"
#include "Rule.h"
#include "Node.h"

SequiturGrammar::SequiturGrammar() {
  this->M = 256; //Index of the min rule value
  this->index = new Dictionary(125100000, this);
  //this->index = new Dictionary(30, this);
  //128 first value after ASCII values
  this->initialRule = new Rule(this->M, this); //Every rule will have a reference to the global index
  this->numberOfRules = 1;
  this->inputSize = 0;
  this->grammarSize = 0;

}

void SequiturGrammar::put(int c) {
  this->inputSize++;
  this->grammarSize++;

  if (c >= this->M){
    std::cout << "Encoding error, value " << c << " not supported"  << std::endl;
    exit(0);
  }else {
    Node* n = new Node(this->initialRule, c);
    Node* prevLast = this->initialRule->guard->prev;
    prevLast->next = n;
    n->prev = prevLast;
    n->next = this->initialRule->guard;
    initialRule->guard->prev = n;

    if (this->inputSize >= 2) //I
      this->index->putUnique(prevLast);
  }
}

void SequiturGrammar::print() {
  this->initialRule->print();
}

void SequiturGrammar::printUncompress() {
  this->initialRule->printUncompress();
}

void SequiturGrammar::getUncompress(std::string* s) {
  this->initialRule->getUncompress(s);
}

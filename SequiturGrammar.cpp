#include <iostream>
#include "SequiturGrammar.h"
#include "Dictionary.h"
#include "Rule.h"
#include "Node.h"

SequiturGrammar::SequiturGrammar(int M, int indexSize):
M(M),
index(new Dictionary(indexSize, this)),
initialRule(new Rule(M, this)),
nextRuleName(M+1),
numberOfRules(1),
inputSize(0),
grammarSize(0) {}

void SequiturGrammar::put(int c) {
  this->inputSize++;
  this->grammarSize++;

  if (c >= this->M){
    std::cout << "Encoding error, value " << c << " not supported"  << std::endl;
    exit(0);
  }else {
    Node* n = new Node(this->initialRule, c);
    Node* prevLast = this->initialRule->guard->prev;
    prevLast->connect(n);
    n->connect(this->initialRule->guard);
    
    if (this->inputSize >= 2) // when there are digrams
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


#include <iostream>
#include "SequiturGrammar.h"
#include "Node.h"
#include "Dictionary.h"
#include "Rule.h"

using namespace std;

void inputTest();
void automatedTest();
void digramOverlapTest();

int main() {
  inputTest();
  //automatedTest();
  //digramOverlapTest();
}


void digramOverlapTest() {
  Rule* testRule = new Rule(256 ,new SequiturGrammar());
  testRule->put('a');
  testRule->put('a');
  testRule->put('a');
  testRule->put('a');
  testRule->print();
  cout << testRule->guard->next->digramOverlap(testRule->guard->next->next) << endl;
  cout << testRule->guard->next->next->digramOverlap(testRule->guard->next) << endl;

  cout << testRule->guard->next->next->next->digramOverlap(testRule->guard->next) << endl;
  cout << testRule->guard->next->digramOverlap(testRule->guard->next->next->next) << endl;
}

void inputTest() {
  SequiturGrammar grammar;
  int chars = 0;

  while (!feof(stdin)) {
    int c = fgetc(stdin);
    if (c == EOF) break;
    grammar.put(c);
    if(++ chars % 1000000 == 0) cerr << (chars)/1000000 << endl << 1.0*grammar.index->a/grammar.index->n << endl;
    //if ((chars)/1000000 == 68) exit(0);

  }
  //grammar.print();
  //grammar.printUncompress();
  //cout << grammar.numberOfRules << endl ;
}


void automatedTest() {
  SequiturGrammar grammar;

  grammar.put('a');
  grammar.put('a');
  grammar.put('a');
  grammar.put('a');
  grammar.put('a');
  grammar.put('a');
  grammar.put('a');

  grammar.print();
}

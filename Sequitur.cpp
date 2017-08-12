
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
  Rule* testRule = new Rule('S' ,new Dictionary(13));
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

  while (!feof(stdin)) {
    int c = fgetc(stdin);
    if (c == EOF) break;
    grammar.put(c);
  }
  grammar.print();
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
  cout << "-----------------" << endl;
  Node f('a');
  f.next=&f;

  grammar.index->remove(&f);
  grammar.print();
  cout << "-----------------" << endl;
  grammar.index->put(&f);
  grammar.print();
  cout << "-----------------" << endl;
}

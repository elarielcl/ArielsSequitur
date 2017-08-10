
#include <iostream>
#include "SequiturGrammar.cpp"
using namespace std;

void inputTest();
void automatedTest();
int main() {
  //inputTest();
  automatedTest();
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

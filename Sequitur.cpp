
#include <iostream>
#include "SequiturGrammar.cpp"
using namespace std;

int main() {
  SequiturGrammar grammar;

  while (!feof(stdin)) {
    int c = fgetc(stdin);
    if (c == EOF) break;
    grammar.put(c);
  }
  grammar.print();
  return 0;
}

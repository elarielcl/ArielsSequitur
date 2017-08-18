
#include <iostream>
#include "SequiturGrammar.h"
#include "Node.h"
#include "Dictionary.h"
#include "Rule.h"

using namespace std;
int blog (int x) {
  int l=0;
  while (x) { x>>=1; l++; }
  return l;
}

int main() {
  SequiturGrammar grammar;
  int chars = 0;

  while (!feof(stdin)) {
    int c = fgetc(stdin);
    if (c == EOF) break;
    grammar.put(c);
  }
  fprintf (stderr,"\nSequitur succeeded\n\n");
  fprintf (stderr,"Grammar\n\n");
  grammar.print();

  fprintf (stderr,"Original chars: %i\n",grammar.inputSize);
  fprintf (stderr,"Number of rules: %i\n",grammar.numberOfRules);
  fprintf (stderr,"Grammar Size: %i\n",grammar.grammarSize);
  fprintf (stderr,"Compression ratio: %0.2f%%\n",
			100.0*blog(grammar.M+grammar.numberOfRules)*grammar.grammarSize/(8.0*grammar.inputSize)); // In case we code the grammar with log |R|+|$\Sigma$| bits
}

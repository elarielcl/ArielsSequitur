
#include <iostream>
#include <unistd.h>
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

int main(int argc, char **argv) {
  extern char *optarg;
  extern int optind, opterr;
  FILE *fp = stdin;

  int c;

  while ((c = getopt(argc, argv, "f:")) != -1) {
    switch (c) {
      case 'f':
      fp = fopen(optarg, "r");
      if (fp == NULL) {
        cerr << "Error oppening \"" << optarg << "\" file" << endl;
        exit(1);
      } break;
    }
  }

  SequiturGrammar grammar;
  while (!feof(fp)) {
    int c = fgetc(fp);
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

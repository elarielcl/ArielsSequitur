
#include <iostream>
#include "SequiturGrammar.h"
#include "Node.h"
#include "Dictionary.h"
#include "Rule.h"

#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <map>


using namespace std;

void inputTest();
void automatedTest();
void digramUniquenessTest();
void ruleUsageTest();
int main() {
  //ruleUsageTest();
  //digramUniquenessTest();
  inputTest();
  //automatedTest();
}



void inputTest() {
  SequiturGrammar grammar;
  int chars = 0;

  while (!feof(stdin)) {
    int c = fgetc(stdin);
    if (c == EOF) break;
    grammar.put(c);
    if(++ chars % 1000000 == 0) cerr << "MB processed: " << (chars)/1000000 << endl << "HashTable Occupancy: " << 1.0*grammar.index->a/grammar.index->n << endl;
    //if ((chars)/1000000 == 68) exit(0);

  }

  cerr << "Compression ratio= " << 1.0*grammar.grammarSize/grammar.inputSize;
  grammar.print();
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

void getRules(Rule* rule, map<Rule*,int>* rules) {
  (*rules)[rule] = 0;
  for (Node* current = rule->guard->next; !current->isGuard(); current = current->next)
    if (current->symbol >=rule->grammar->M) getRules(current->rule, rules);

}

bool digramEquality(Node* n1, Node* n2) {
  return (n1->symbol < n2->symbol || (n1->symbol == n2->symbol && n1->next->symbol < n2->next->symbol ));
}

void ruleUsageTest() {
  SequiturGrammar* grammar = new SequiturGrammar();
  while (!feof(stdin)) {
    int c = fgetc(stdin);
    if (c == EOF) break;
    grammar->put(c);
    //if(++ chars % 1000000 == 0) cerr << "MB processed: " << (chars)/1000000 << endl << "HashTable Occupancy: " << 1.0*grammar.index->a/grammar.index->n << endl;
    //if ((chars)/1000000 == 68) exit(0);

  }

  map<Rule*, int> rules;
  map<Rule*, int>  :: iterator r;

  getRules(grammar->initialRule, &rules);

  bool correctUsage = true;
  for (r = rules.begin(); r != rules.end(); ++r) {
    if (r->first!= grammar->initialRule && r->first->usage <= 1) {
      correctUsage = false;
      cout << "WRONG TEST" << endl;
      cout << "Rule for " << r->first->guard->prev->symbol << " referenced " << r->first->usage << " times" << endl;
      exit(1);
    }
    if(rules.find(r->first) == rules.end()) rules[r->first] = 0;
    for (Node* current = r->first->guard->next; !current->isGuard(); current = current->next)
      if (current->symbol >= grammar->M)
        if(rules.find(current->rule) == rules.end()) rules[current->rule] = 1;
        else rules[current->rule]++;


  }
  for (r = rules.begin(); r != rules.end(); ++r) {
    if (r->first != grammar->initialRule && r->second <= 1) {
      correctUsage = false;
      cout << "WRONG TEST" << endl;
      cout << "Rule for " << r->first->guard->prev->symbol << " referenced " << r->second << " times" << endl;
      exit(1);
    }


  }
  if (correctUsage) cout << "SUCCESSFUL TEST" << endl;
  cout << "================" << endl << endl;
}


void digramUniquenessTest() {
  SequiturGrammar* grammar = new SequiturGrammar();
  while (!feof(stdin)) {
    int c = fgetc(stdin);
    if (c == EOF) break;
    grammar->put(c);
    //if(++ chars % 1000000 == 0) cerr << "MB processed: " << (chars)/1000000 << endl << "HashTable Occupancy: " << 1.0*grammar.index->a/grammar.index->n << endl;
    //if ((chars)/1000000 == 68) exit(0);

  }
  map<Rule*, int> rules;
  map<Rule*, int>  :: iterator r;

  bool(*fn_pt)(Node*,Node*) = digramEquality;
  set<Node*,bool(*)(Node*,Node*)> digrams (fn_pt);


  getRules(grammar->initialRule, &rules);

  bool hasRepeatedDigram = false;
  for (r = rules.begin(); r != rules.end(); ++r) {
    for (Node* current = r->first->guard->next; !current->isGuard() && !current->next->isGuard(); current = current->next) {
        if(digrams.find(current) == digrams.end()) {
          digrams.insert(current);
        }else if (!(current->symbol == current->prev->symbol && current->symbol == current->next->symbol)){
          (*(digrams.find(current)))->printDigram();
          hasRepeatedDigram = true;
          cout << "WRONG TEST" << endl;
          cout << "Digram: ";
          current->printDigram();
          cout << "is not unique"  << endl;
          exit(1);;
        }
      }
      if (hasRepeatedDigram) break;

  }
  if (!hasRepeatedDigram) cout << "SUCCESSFUL TEST" << endl;
  cout << "================" << endl << endl;
}

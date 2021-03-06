
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <map>
#include "SequiturGrammar.h"
#include "Node.h"
#include "Dictionary.h"
#include "Rule.h"

using namespace std;

void simpleTest(char[]);
void ruleUsageTest(char[]);
void digramUniquenessTest(char[]);
void grammarSizeTest(char[], int);
void numberOfRulesTest(char string[], int expectedNOR);

int main() {
  vector<char*> v;
  vector <char*> :: iterator s;

  v.push_back((char*)"abcdbcabcd");
  v.push_back((char*)"cdddcdaddcd");
  v.push_back((char*)"cdddcdaddcdcdddcdaddcdcdddcdaddcdcdddcdaddcdcdddcdaddcdcdddcdaddcdcdddcdaddcdcdddcdaddcd");
  v.push_back((char*)"aaaaaaaaaaaaaaaaaaaaaaaa");
  v.push_back((char*)"ababababababababab");

  cout << "SIMPLE TEST" << endl << "=====================================" << endl << endl;
  for (s = v.begin(); s != v.end(); ++s)
    simpleTest(*s);

  vector<int> nOR;
  nOR.push_back(3);
  nOR.push_back(3);
  nOR.push_back(6);
  nOR.push_back(4);
  nOR.push_back(4); // Precomputed Values
  cout << "GRAMMAR SIZE TEST" << endl << "=====================================" << endl << endl;
  for (int i = 0; i < nOR.size(); ++i)
    numberOfRulesTest(v[i], nOR[i]);


  vector<int> sizes;
  sizes.push_back(8);
  sizes.push_back(9);
  sizes.push_back(15);
  sizes.push_back(9);
  sizes.push_back(9); // Precomputed Values
  cout << "GRAMMAR SIZE TEST" << endl << "=====================================" << endl << endl;
  for (int i = 0; i < sizes.size(); ++i)
    grammarSizeTest(v[i], sizes[i]);

  cout << "RULE USAGE TEST" << endl << "=====================================" << endl << endl;
  for (s = v.begin(); s != v.end(); ++s)
    ruleUsageTest(*s);

  cout << "DIGRAM UNIQUENESS TEST" << endl << "=====================================" << endl << endl;
  for (s = v.begin(); s != v.end(); ++s)
    digramUniquenessTest(*s);

}
void getRules(Rule* rule, map<Rule*,int>* rules) {
  (*rules)[rule] = 0;
  for (Node* current = rule->guard->next; !current->isGuard(); current = current->next)
    if (current->symbol >=rule->grammar->M) getRules(current->rule, rules);

}

bool digramEquality(Node* n1, Node* n2) {
  return (n1->symbol < n2->symbol || (n1->symbol == n2->symbol && n1->next->symbol < n2->next->symbol ));
}

void ruleUsageTest(char string[]) {
  cout << "INPUT=" << string << endl;
  SequiturGrammar* grammar = new SequiturGrammar();
  for (int i = 0; string[i]!=0; ++i)
    grammar->put(string[i]);

  map<Rule*, int> rules;
  map<Rule*, int>  :: iterator r;

  getRules(grammar->initialRule, &rules);

  bool correctUsage = true;
  for (r = rules.begin(); r != rules.end(); ++r) {
    if (r->first!= grammar->initialRule && r->first->usage <= 1) {
      correctUsage = false;
      cout << "WRONG TEST" << endl;
      cout << "Rule for " << r->first->symbol << " referenced " << r->first->usage << " times" << endl;
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
      cout << "Rule for " << r->first->symbol << " referenced " << r->second << " times" << endl;
      exit(1);
    }


  }
  if (correctUsage) cout << "SUCCESSFUL TEST" << endl;
  cout << "================" << endl << endl;
}

void grammarSizeTest(char string[], int expectedGrammarSize) {
  cout << "INPUT=" << string << endl;
  SequiturGrammar* grammar = new SequiturGrammar();
  for (int i = 0; string[i]!=0; ++i)
    grammar->put(string[i]);
  if (grammar->grammarSize == expectedGrammarSize) cout << "SUCCESSFUL TEST (GrammarSize == expected)" << endl;
  else {
    cout << "WRONG TEST (GrammarSize(" << grammar->grammarSize << ") != expected("<< expectedGrammarSize << "))" << endl;
    exit(1);
  }

  cout << "================" << endl << endl;
}

void numberOfRulesTest(char string[], int expectedNOR) {
  cout << "INPUT=" << string << endl;
  SequiturGrammar* grammar = new SequiturGrammar();
  for (int i = 0; string[i]!=0; ++i)
    grammar->put(string[i]);
  if (grammar->numberOfRules == expectedNOR) cout << "SUCCESSFUL TEST (GrammarSize == expected)" << endl;
  else {
    cout << "WRONG TEST (NumberOfRules(" << grammar->numberOfRules << ") != expected("<< expectedNOR << "))" << endl;
    exit(1);
  }

  cout << "================" << endl << endl;
}

void simpleTest(char string[]) {
  cout << "INPUT=" << string << endl;
  SequiturGrammar* grammar = new SequiturGrammar();
  for (int i = 0; string[i]!=0; ++i)
    grammar->put(string[i]);
  cout << "GRAMMAR" << endl;
  grammar->print();

  cout << "OUTPUT=";
  grammar->printUncompress();
  cout << endl;
  std::string s="";
  grammar->getUncompress(&s);
  if (s == string) cout << "SUCCESSFUL TEST (OUTPUT == INPUT)" << endl;
  else {
    cout << "WRONG TEST (OUTPUT != INPUT)" << endl;
    exit(1);
  }

  cout << "================" << endl << endl;
}

void digramUniquenessTest(char string[]) {
  cout << "INPUT=" << string << endl;
  SequiturGrammar* grammar = new SequiturGrammar();
  for (int i = 0; string[i]!=0; ++i)
    grammar->put(string[i]);

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

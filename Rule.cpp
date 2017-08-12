#include <iostream> //Remove
#include "Rule.h"
#include "Node.h"
#include "Dictionary.h"
#include "SequiturGrammar.h"
#include <vector>

Rule::Rule(int c, SequiturGrammar* grammar) {
  Node* nonTerminal = new Node(this, c);
  Node* guard = new Node(this, true);
  nonTerminal->next = guard;
  guard->prev = nonTerminal;
  guard->next = guard;

  this->guard = guard;
  this->last = guard;
  this->grammar = grammar;
  this->n = 0;
  this->usage = 0;
  this->printed = false;
}

void Rule::put2(int c) {
  ++this->n;
  Node* n = new Node(this, c);
  this->last->next = n;
  n->prev = this->last;
  n->next = this->guard;
  this->last = n;
  if (this->n >= 2) {
    this->grammar->index->putUnique(this->last->prev);
  }
}


void Rule::put(int c) {
  ++this->n;
  Node* n = new Node(this, c);
  this->last->next = n;
  n->prev = this->last;
  n->next = this->guard;
  this->last = n;
  if (this->n >= 2) {
    Node* anotherDigram = this->grammar->index->get(this->last->prev);
    if (!anotherDigram)
      this->grammar->index->put(this->last->prev);
    else {
      //Information
      std::cout << "Violation of " << (char)this->last->prev->symbol << "," << (char)this->last->symbol << " uniqueness" << std::endl;
      if (anotherDigram->prev->isGuard && anotherDigram->next->next->isGuard) {
        std::cout << "Rule exists:" << std::endl;
        anotherDigram->rule->print();
      }else {
        std::cout << "In Rule:" << std::endl;
        anotherDigram->rule->print();
      }
      //Information

      if (anotherDigram->prev->isGuard && anotherDigram->next->next->isGuard) {
        this->grammar->index->print();
        Rule* existentRule = anotherDigram->rule;

        //Create one new node
        Node* one = new Node(existentRule, existentRule->guard->prev->symbol);

        //Remove ab from index
        if (!this->last->prev->prev->isGuard) {
          this->grammar->index->remove(this->last->prev->prev);
        }


        //Insert one
        this->last->prev->prev->next = one;
        one->prev = this->last->prev->prev;
        one->next = this->last->next; //Delete the digram or put this on the rule
        this->last = one;

        //Here put in the index the new digram (could generate another violation)
        this->grammar->index->put(this->last->prev); //Modify for check that, and doing it recursive


        this->print();
        this->grammar->index->print();

      }else { //Check for overlap
        this->grammar->index->print();
        int ruleName = (this->grammar->numberOfRules ++) + 128;
        Rule* newRule = new Rule(ruleName, this->grammar);

        //Create two new nodes
        Node* one = new Node(newRule, ruleName);
        Node* two = new Node(newRule, ruleName);

        //Remove ab from index
        if (!this->last->prev->prev->isGuard) {
          this->grammar->index->remove(this->last->prev->prev);
        }

        //Insert one
        this->last->prev->prev->next = one;
        one->prev = this->last->prev->prev;
        one->next = this->last->next; //Delete the digram or put this on the rule
        this->last = one;
        //Here put in the index the new digram (case not before)
        this->grammar->index->put(this->last->prev);

        //Remove x1b and cx2 from index
        if (!anotherDigram->prev->isGuard) {
          this->grammar->index->remove(anotherDigram->prev);
        }
        if (!anotherDigram->next->isGuard) {
          this->grammar->index->remove(anotherDigram->next);
        }

        //Insert two
        anotherDigram->prev->next = two;
        two->prev = anotherDigram->prev;
        two->next = anotherDigram->next->next;
        //Here put in the index the new digrams (case not before)
        if (!two->prev->isGuard)
          this->grammar->index->put(two->prev);
        if (!two->next->isGuard)
          this->grammar->index->put(two);

        //Put the symbols in the new rule
        newRule->guard->next = anotherDigram;
        newRule->last = anotherDigram->next;
        anotherDigram->prev = newRule->guard;
        anotherDigram->next->next = newRule->guard;
        anotherDigram->rule = newRule;
        anotherDigram->next->rule = newRule;
        newRule->n = 2;

        this->print();
        this->grammar->index->print();
      }

    }
  }
}

void Rule::print() {
  std::vector<Rule*> v;
  this-> printed = true;
  std::cout << this->guard->prev->symbol;
  std::cout << " -> ";
  Node* t = this->guard->next;
  while (!t->isGuard) {
    if (t->symbol<128)
      std::cout <<  (char)t->symbol<< " ";
    else {
      std::cout <<  t->symbol<< " ";
      if (!t->rule->printed) {
        v.push_back(t->rule);
        t->rule->printed = true;
      }
    }
    t = t->next;
  }
  std::cout << std::endl;

  for (int i = 0; i<v.size(); ++i) {
    v[i]->print();
  }
  this->printed = false;
}

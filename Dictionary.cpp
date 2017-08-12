#include <math.h>
#include <iostream>//Delete
#include "Dictionary.h"
#include "Node.h"
#include "Rule.h"
#include "SequiturGrammar.h"

Dictionary::Dictionary(const unsigned int n, SequiturGrammar* grammar) {

  // find a prime less than the maximum table size
  this->n = n;
  if (this->n % 2 == 0)
    this->n --;
  int max_factor = int(sqrt(float(this->n)));
  while (1) {
    int prime = 1;
    for (int i = 3; i < max_factor; i += 2)
     if (this->n % i == 0) {
        prime = 0;
         break;
     }
    if (prime)
     break;
    this->n -= 2;
  }
  this->table = new Node*[this->n];
  this->deleted = new Node(NULL, true); // A guard node represents a deleted  one in the table :D
  this->grammar = grammar;
}

void Dictionary::put(Node* node) {
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17);
  while (1) {
    Node* m = this->table[i];
    if (m==NULL || m->isGuard) {
      this->table[i] = node;
      break;
    }
    i = (i + jump) % this->n;
  }
}

void Dictionary::putUnique(Node* node) {
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17);
  while (1) {
    Node* m = this->table[i];
    if (m==NULL || m->isGuard) {
      this->table[i] = node;
      return;
    }else if(node->symbol == m->symbol && node->next->symbol==m->next->symbol) { //Is not Unique
      if (m->digramOverlap(node)) return;
///IMPLEMENTING
      //Information
      std::cout << "Violation of " << (char)node->symbol << "," << (char)node->next->symbol << " uniqueness" << std::endl;
      if (m->prev->isGuard && m->next->next->isGuard) {
        std::cout << "Rule exists:" << std::endl;
        m->printRule();
      }else {
        std::cout << "In Rule(careful with rule impresion):" << std::endl;
        m->printRule();
      }
      //Information

      if (m->prev->isGuard && m->next->next->isGuard) {
        this->print();
        Rule* existentRule = m->rule;

        //Create one new node
        Node* one = new Node(existentRule, existentRule->guard->prev->symbol);

        //Remove ab from index
        if (!node->prev->isGuard) {
          this->remove(node->prev); //DO IT RECURSIVE
        }
        //Remove cd from index
        if (!node->next->next->isGuard) {
          this->remove(node->next); //DO IT RECURSIVE
        }

        //Insert one
        node->prev->next = one;
        one->prev = node->prev;
        one->next = node->next->next; //Delete the digram or put this on the rule

        if (one->next->isGuard) // In case the digram was the last of the rule
          one->next->rule->last = one;

        if (!one->prev->isGuard)
          this->putUnique(one->prev);
        if (!one->next->isGuard)
          this->putUnique(one);


        one->printRule();
        this->print();

      }else {
        this->print();
        int ruleName = (this->grammar->numberOfRules ++) + 128; // Another idea?
        Rule* newRule = new Rule(ruleName, this->grammar);

        //Create two new nodes
        Node* one = new Node(newRule, ruleName);
        Node* two = new Node(newRule, ruleName);

        //Remove ab from index
        if (!node->prev->isGuard) {
          this->remove(node->prev); //DO IT RECURSIVE
        }
        //Remove cd from index
        if (!node->next->next->isGuard) {
          this->remove(node->next); //DO IT RECURSIVE
        }

        //Insert one
        node->prev->next = one;
        one->prev = node->prev;
        one->next = node->next->next; //Delete the digram or put this on the rule

        if (one->next->isGuard) // In case the digram was the last of the rule
          one->next->rule->last = one;

        //Here put in the index the new digram (case not before)
        if (!one->prev->isGuard)
          this->put(one->prev); //Not recursive
        if (!one->next->isGuard)
          this->put(one); //Not recursive

        //Remove x1b and cx2 from index
        if (!m->prev->isGuard) {
          this->remove(m->prev); //DO IT RECURSIVE
        }
        if (!m->next->isGuard) {
          this->remove(m->next); //DO IT RECURSIVE
        }

        //Insert two
        m->prev->next = two;
        two->prev = m->prev;
        two->next = m->next->next;

        if (two->next->isGuard) // In case the digram was the last of the rule
          two->next->rule->last = two;

        //Here put in the index the new digrams (case not before)
        if (!two->prev->isGuard)
          this->put(two->prev); //Not recursive
        if (!two->next->isGuard)
          this->put(two); //Not recursive


        //Put the symbols in the new rule
        newRule->guard->next = m;
        newRule->last = m->next;
        m->prev = newRule->guard;
        m->next->next = newRule->guard;
        m->rule = newRule;
        m->next->rule = newRule;
        newRule->n = 2;

        one->printRule();
        this->print();
      }


//IMPLEMENTING

      return;
    }
    i = (i + jump) % this->n;
  }
}

Node* Dictionary::get(int i) {
  return this->table[i];
}

Node* Dictionary::get(Node* node) {
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17);
  while (1) {
    Node* m = this->table[i];
    if (m==NULL) {
      break;
    }else if(!m->isGuard && node->symbol == m->symbol && node->next->symbol==m->next->symbol) {
      return m;
    }
    i = (i + jump) % this->n;
  }
  return NULL;
}

void Dictionary::remove(Node* node) {
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17);
  while (1) {
    Node* m = this->table[i];
    if (m==NULL) {
      return;
    }else if(!m->isGuard && node->symbol == m->symbol && node->next->symbol==m->next->symbol) {
      this->table[i] = deleted;
      return;
    }
    i = (i + jump) % this->n;
  }
}

void Dictionary::print() {
  std::cout << "INDEX" << std::endl;
  for (int i = 0; i < this->n; ++i) {
    Node* current = this->get(i);
    if (current && !current->isGuard) {
      if (current->symbol < 128)
        std::cout << (char)current->symbol << ",";
      else
        std::cout << current->symbol << ",";
      if (current->next->symbol < 128)
        std::cout << (char)current->next->symbol << std::endl;
      else
        std::cout << current->next->symbol << std::endl;
    }
    else
     std::cout << "No value" << std::endl;
  }
}

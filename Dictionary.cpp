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
  this->deleted = new Node(NULL); // A guard node represents a deleted  one in the table :D
  this->grammar = grammar;
  this->a = 0;
}

void Dictionary::put(Node* node) {
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17); // open addressing, copied from craig
  while (1) {
    Node* m = this->table[i];
    if (m==NULL || m->isGuard()) {
      this->table[i] = node;
      this->a++;
      break;
    }
    i = (i + jump) % this->n;
  }
}


void Dictionary::putUnique(Node* node) {
  Node** insertAt = this->get(node);
  if ((*insertAt) == NULL || (*insertAt) ->isGuard()){ // is there a better way?
    *insertAt = node;
    this->a++;
  }
  else {
    Node* m = *insertAt;
    if (m->digramOverlap(node)) return;

    if (m->prev->isGuard() && m->next->next->isGuard()) {

      this->grammar->grammarSize--;

      Rule* existentRule = m->prev->rule;
      existentRule->usage++;

      //Create one new node
      Node* one = new Node(existentRule, existentRule->symbol);

      // remove existent digrams in the index
      if (!node->prev->isGuard())
        this->remove(node->prev);
      if (!node->next->next->isGuard())
        this->remove(node->next);

      //Insert one
      node->prev->connect(one);
      one->connect(node->next->next);

      // put new digrams in the index
      if (!one->prev->isGuard())
        this->putUnique(one->prev);
      if (!one->next->isGuard())
        this->putUnique(one);

        //DELETING
        delete node->next;
        delete node;
        //DELETING

        // delete deprecatedOcurrences
        Node* dOcc = existentRule->guard->next; //deprecatedOccurrence
        while (!dOcc->isGuard()) {
          if(dOcc->symbol>=this->grammar->M) {
            dOcc->rule->usage--;
            if (dOcc->rule->usage <= 1) {
              this->grammar->numberOfRules--;
              this->grammar->grammarSize--;

              // remove existent digrams in the index
              if (!dOcc->prev->isGuard())
                this->remove(dOcc->prev);
              if (!dOcc->next->isGuard())
                this->remove(dOcc);

              // restructure pointers
              dOcc->prev->connect(dOcc->rule->guard->next);
              dOcc->rule->guard->prev->connect(dOcc->next);

              // put new digrams in the index
              if (!dOcc->next->isGuard())
                this->putUnique(dOcc->next->prev);
              if (!dOcc->prev->isGuard())
                this->putUnique(dOcc->prev);

              Node* next = dOcc->next;

              //DELETING
              delete dOcc->rule->guard;
              delete dOcc->rule;
              delete dOcc;
              //DELETING
              dOcc = next;
            }else dOcc = dOcc->next;
          }else dOcc = dOcc->next;
      }
    }else {
      this->grammar->numberOfRules++;
      int ruleName = (this->grammar->nextRuleName ++); // Another idea?
      Rule* newRule = new Rule(ruleName, this->grammar);
      newRule->usage = 2;

      //Create two new nodes
      Node* one = new Node(newRule, ruleName);
      Node* two = new Node(newRule, ruleName);

      // remove existent digrams in the index
      if (!node->prev->isGuard())
        this->remove(node->prev);
      if (!node->next->next->isGuard())
        this->remove(node->next);

      //Insert one
      node->prev->connect(one);
      one->connect(node->next->next);

      //Here put in the index the new digram (case not before)
      if (!one->prev->isGuard())
        this->put(one->prev); //Not recursive
      if (!one->next->isGuard())
        this->put(one); //Not recursive

      // remove existent digrams in the index
      if (!m->prev->isGuard())
        this->remove(m->prev);
      if (!m->next->next->isGuard())
        this->remove(m->next);

      //Insert two
      m->prev->connect(two);
      two->connect(m->next->next);

      //Here put in the index the new digrams (case not before)
      if (!two->prev->isGuard())
        this->put(two->prev); //Not recursive
      if (!two->next->isGuard())
        this->put(two); //Not recursive

      //Put the symbols in the new rule
      newRule->guard->connect(m);
      m->next->connect(newRule->guard);

      //DELETING
      delete node->next;
      delete node;
      //DELETING

      // delete deprecatedOcurrences
      Node* dOcc = newRule->guard->next; //deprecatedOccurrence
      while (!dOcc->isGuard()) {
        if(dOcc->symbol>=this->grammar->M) {
          dOcc->rule->usage--;
          if (dOcc->rule->usage <= 1) {
            this->grammar->grammarSize--;
            this->grammar->numberOfRules--;

            // remove existent digrams in the index
            if (!dOcc->prev->isGuard())
              this->remove(dOcc->prev);
            if (!dOcc->next->isGuard())
              this->remove(dOcc);

            // restructure pointers
            dOcc->prev->connect(dOcc->rule->guard->next);
            dOcc->rule->guard->prev->connect(dOcc->next);

            // put new digrams in the index
            if (!dOcc->next->isGuard())
              this->putUnique(dOcc->next->prev);
            if (!dOcc->prev->isGuard())
              this->putUnique(dOcc->prev);

            Node* next = dOcc->next;

            //DELETING
            delete dOcc->rule->guard;
            delete dOcc->rule;
            delete dOcc;
            //DELETING
            dOcc = next;
          }else dOcc = dOcc->next;
        }else dOcc = dOcc->next;
      }
    }
  }
}

Node** Dictionary::get(Node* node) {
  int insertingIndex = -1;
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17); // open addressing, copied from craig
  while (1) {
    Node* m = this->table[i];
    if (m==NULL)
      if (insertingIndex == -1)
        return &(this->table[i]);
      else
          return &(this->table[insertingIndex]);
    else if(m->isGuard() && insertingIndex == -1)
      insertingIndex = i;
    else if(!m->isGuard() && node->symbol == m->symbol && node->next->symbol==m->next->symbol) {
      return &(this->table[i]);
    }
    i = (i + jump) % this->n;
  }
  return NULL;
}

void Dictionary::remove(Node* node) {
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17); // open addressing, copied from craig
  while (1) {
    Node* m = this->table[i];
    if (m==NULL) {
      return;
    }else if(!m->isGuard() && node->symbol == m->symbol && node->next->symbol==m->next->symbol) {
      if (m->digramOverlap(node)) return; // don't delete overlap occurence
      else if (m == node && !m->next->next->isGuard() && m->symbol == m->next->symbol && m->symbol == m->next->next->symbol) // change the table pointer if the digram already exists on the grammar
        this->table[i] = m->next;
      else {
        this->table[i] = deleted; // lazy deletion, open addressing
        this->a--;
      }
      return;
    }
    i = (i + jump) % this->n;
  }
}

void Dictionary::print() {
  std::cout << "INDEX" << std::endl;
  for (int i = 0; i < this->n; ++i) {
    Node* current = this->table[i];
    if (current && !current->isGuard())
      current->printDigram();
    else
     std::cout << "No value" << std::endl;
  }
}

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
  std::cerr << "Espacio ocupado por el diccionario: " << ((sizeof (Node*))*this->n)/1000000 << "MB" << std::endl;
  this->table = new Node*[this->n];
  this->deleted = new Node(NULL); // A guard node represents a deleted  one in the table :D
  this->grammar = grammar;
  this->a = 0;
}

void Dictionary::put(Node* node) {
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17);
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
  if (this->get(node) == NULL) this->put(node); //IMPROVE
  else {
  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17);
  while (1) {
    Node* m = this->table[i];
    if(node->symbol == m->symbol && node->next->symbol==m->next->symbol) { //Is not Unique
      if (m->digramOverlap(node)) return;


      if (m->prev->isGuard() && m->next->next->isGuard()) {

        this->grammar->grammarSize--;

        Rule* existentRule = m->prev->rule;
        existentRule->usage++;

        //Create one new node
        Node* one = new Node(existentRule, existentRule->symbol);

        //Remove ab from index
        if (!node->prev->isGuard()) {
          this->remove(node->prev);
        }
        //Remove cd from index
        if (!node->next->next->isGuard()) {
          this->remove(node->next);
        }

        //Insert one
        node->prev->next = one;
        one->prev = node->prev;
        one->next = node->next->next; //Delete the digram or put this on the rule
        node->next->next->prev = one;



        if (!one->prev->isGuard())
          this->putUnique(one->prev);
        if (!one->next->isGuard())
          this->putUnique(one);

          //DELETING

          delete node->next;
          delete node;

          //DELETING

          //CHECK DELETION HERE
          Node* dOcc = existentRule->guard->next; //deprecatedOccurrence
          while (!dOcc->isGuard()) {
            if(dOcc->symbol>=this->grammar->M) {
              dOcc->rule->usage--;
              if (dOcc->rule->usage <= 1) {
                this->grammar->grammarSize--;
                //Delete x1B and Bx2
                if (!dOcc->prev->isGuard()) {
                  this->remove(dOcc->prev);
                }
                if (!dOcc->next->isGuard()) {
                  this->remove(dOcc);
                }

                // Delete things
                dOcc->rule->guard->next->prev = dOcc->prev;
                dOcc->prev->next = dOcc->rule->guard->next;
                dOcc->rule->guard->prev->next = dOcc->next;
                dOcc->next->prev = dOcc->rule->guard->prev;


                if (!dOcc->next->isGuard()){
                  this->putUnique(dOcc->next->prev);
                }
                if (!dOcc->prev->isGuard()) {
                  this->putUnique(dOcc->prev);
                }

                Node* next = dOcc->next;

                //DELETING

                delete dOcc->rule->guard;
                delete dOcc->rule;
                delete dOcc;

                //DELETING
                dOcc = next;
                //Revisar por el last
              }else dOcc = dOcc->next;
            }
            else dOcc = dOcc->next;
        }
        //one->printRule();
        //this->print();

      }else {
        int ruleName = (this->grammar->numberOfRules ++) + this->grammar->M; // Another idea?
        Rule* newRule = new Rule(ruleName, this->grammar);
        newRule->usage = 2;
        //Create two new nodes
        Node* one = new Node(newRule, ruleName);
        Node* two = new Node(newRule, ruleName);

        //Remove ab from index
        if (!node->prev->isGuard()) {
          this->remove(node->prev);
        }
        //Remove cd from index
        if (!node->next->next->isGuard()) {
          this->remove(node->next);
        }



        //Insert one
        node->prev->next = one;
        one->prev = node->prev;
        one->next = node->next->next; //Delete the digram or put this on the rule
        node->next->next->prev = one;


        //this->grammar->index->print();
        //Here put in the index the new digram (case not before)
        if (!one->prev->isGuard()) {
          this->put(one->prev); //Not recursive
        }


        if (!one->next->isGuard()) {
          this->put(one); //Not recursive
        }



        //Remove x1b and cx2 from index
        if (!m->prev->isGuard()) {
          this->remove(m->prev);
        }


        if (!m->next->next->isGuard()) {
          this->remove(m->next);
        }

        //Insert two
        m->prev->next = two;
        two->prev = m->prev;
        two->next = m->next->next;
        m->next->next->prev = two;

        //Here put in the index the new digrams (case not before)
        if (!two->prev->isGuard()) {
          this->put(two->prev); //Not recursive
        }
        if (!two->next->isGuard()) {
          this->put(two); //Not recursive
        }


        //Put the symbols in the new rule
        newRule->guard->next = m;
        newRule->guard->prev = m->next;
        m->prev = newRule->guard;
        m->next->next = newRule->guard;


        //DELETING

        delete node->next;
        delete node;

        //DELETING

        //one->printRule();
        //this->print();

        Node* dOcc = newRule->guard->next; //deprecatedOccurrence
        while (!dOcc->isGuard()) { //DONT FORGET CHANGE THE OTHER
          if(dOcc->symbol>=this->grammar->M) {
            dOcc->rule->usage--;
            if (dOcc->rule->usage <= 1) {
              this->grammar->grammarSize--;
              //Delete x1B and Bx2
              if (!dOcc->prev->isGuard()) {
                this->remove(dOcc->prev);
              }
              if (!dOcc->next->isGuard()) {
                this->remove(dOcc);
              }

              // Delete things
              dOcc->rule->guard->next->prev = dOcc->prev;
              dOcc->prev->next = dOcc->rule->guard->next;
              dOcc->rule->guard->prev->next = dOcc->next;
              dOcc->next->prev = dOcc->rule->guard->prev;



              if (!dOcc->next->isGuard()){
                this->putUnique(dOcc->next->prev);
              }
              if (!dOcc->prev->isGuard()) {
                this->putUnique(dOcc->prev);
              }
              Node* next = dOcc->next;

              //DELETING

              delete dOcc->rule->guard;
              delete dOcc->rule;
              delete dOcc;

              //DELETING
              dOcc = next;
              //Revisar por el last
            }else dOcc = dOcc->next;
          }
          else dOcc = dOcc->next;
        }

      }


      return;
    }
    i = (i + jump) % this->n;
  }}
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
    }else if(!m->isGuard() && node->symbol == m->symbol && node->next->symbol==m->next->symbol) {
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
    }else if(!m->isGuard() && node->symbol == m->symbol && node->next->symbol==m->next->symbol) {
      if (m->digramOverlap(node)) return;
      else if (m == node && !m->next->next->isGuard() && m->symbol == m->next->symbol && m->symbol == m->next->next->symbol)
        this->table[i] = m->next;
      else {this->table[i] = deleted; this->a--;}
      return;
    }
    i = (i + jump) % this->n;
  }
}

void Dictionary::print() {
  std::cout << "INDEX" << std::endl;
  for (int i = 0; i < this->n; ++i) {
    Node* current = this->get(i);
    if (current && !current->isGuard())
      current->printDigram();
    else
     std::cout << "No value" << std::endl;
  }
}

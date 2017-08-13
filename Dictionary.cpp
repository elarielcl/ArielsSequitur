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
  std::cout << "Putting Unique: ";
  node->printDigram();

  int i = node->hashCode() % this->n;
  int jump = 17 - (node->symbol % 17);
  while (1) {
    Node* m = this->table[i];
    if (m==NULL || m->isGuard) {
      this->table[i] = node;
      return;
    }else if(node->symbol == m->symbol && node->next->symbol==m->next->symbol) { //Is not Unique
      if (m->digramOverlap(node)) return;

/*
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
*/
      if (m->prev->isGuard && m->next->next->isGuard) {
        std::cout <<  "Existent Rule: ";
        m->printDigram();
        Rule* existentRule = m->prev->rule;
        existentRule->usage++;
        //Create one new node
        Node* one = new Node(existentRule, existentRule->guard->prev->symbol);

        //Remove ab from index
        if (!node->prev->isGuard) {
          this->remove(node->prev);
        }
        //Remove cd from index
        if (!node->next->next->isGuard) {
          this->remove(node->next);
        }

        //Insert one
        node->prev->next = one;
        one->prev = node->prev;
        one->next = node->next->next; //Delete the digram or put this on the rule
        if (!node->next->next->isGuard) node->next->next->prev = one;


        if (one->next->isGuard) // In case the digram was the last of the rule
          one->next->rule->last = one;

        if (!one->prev->isGuard)
          this->putUnique(one->prev);
        if (!one->next->isGuard)
          this->putUnique(one);

          Node* dOcc = existentRule->guard->next; //deprecatedOccurrence
          while (!dOcc->isGuard) {
            if(dOcc->symbol>=128) {
              dOcc->rule->usage--;
              if (dOcc->rule->usage <= 1) {

                //Delete x1B and Bx2
                if (!dOcc->prev->isGuard) {
                  this->remove(dOcc->prev);
                }
                if (!dOcc->next->isGuard) {
                  this->remove(dOcc);
                }
                // Delete things
                dOcc->rule->guard->next->prev = dOcc->prev;
                dOcc->prev->next = dOcc->rule->guard->next;
                dOcc->rule->last->next = dOcc->next;
                dOcc->next->prev = dOcc->rule->last;
                if (dOcc->next->isGuard) {
                  dOcc->next->rule->last = dOcc->rule->last;
                }
                if (!dOcc->next->isGuard){
                  this->putUnique(dOcc->next->prev);
                }
                if (!dOcc->prev->isGuard) {
                  this->putUnique(dOcc->prev);
                }

                //Revisar por el last
              }
            }
            dOcc = dOcc->next;
        }
        //one->printRule();
        //this->print();

      }else {
        std::cout <<  "New Rule for: ";
        m->printDigram();

        int ruleName = (this->grammar->numberOfRules ++) + 128; // Another idea?
        Rule* newRule = new Rule(ruleName, this->grammar);
        newRule->usage = 2;
        //Create two new nodes
        Node* one = new Node(newRule, ruleName);
        Node* two = new Node(newRule, ruleName);

        //Remove ab from index
        if (!node->prev->isGuard) {
          std::cout << "REMOVE: ";
          node->prev->printDigram();
          this->remove(node->prev);
        }
        //Remove cd from index
        if (!node->next->next->isGuard) {
          std::cout << "REMOVE: ";
          node->next->printDigram();
          this->remove(node->next);
        }



        //Insert one
        node->prev->next = one;
        one->prev = node->prev;
        one->next = node->next->next; //Delete the digram or put this on the rule
        if (!node->next->next->isGuard) node->next->next->prev = one;

        if (one->next->isGuard) // In case the digram was the last of the rule
          one->next->rule->last = one;

        this->grammar->initialRule->print();
        //Here put in the index the new digram (case not before)
        if (!one->prev->isGuard) {
          std::cout << "Insert: ";
          one->prev->printDigram();
          this->putUnique(one->prev); //Not recursive
        }
        if (!one->next->isGuard) {
          std::cout << "Insert: ";
          one->printDigram();
          this->putUnique(one); //Not recursive
        }



        //Remove x1b and cx2 from index
        if (!m->prev->isGuard) {
          std::cout << "REMOVE: ";
          m->prev->printDigram();
          m->printDigram();

          m->next->printDigram();
          this->remove(m->prev);
        }


        if (!m->next->next->isGuard) {
          std::cout << "REMOVE: ";
          m->next->printDigram();
          this->remove(m->next);
        }

        //Insert two
        m->prev->next = two;
        two->prev = m->prev;
        two->next = m->next->next;
        if (!m->next->next->isGuard) m->next->next->prev = two;

        if (two->next->isGuard) // In case the digram was the last of the rule
          two->next->rule->last = two;
        //Here put in the index the new digrams (case not before)
        if (!two->prev->isGuard) {
          std::cout << "Insert: ";
          two->prev->printDigram();
          this->putUnique(two->prev); //Not recursive
        }
        if (!two->next->isGuard) {
          std::cout << "Insert: ";
          two->printDigram();
          this->putUnique(two); //Not recursive
        }


        //Put the symbols in the new rule
        newRule->guard->next = m;
        newRule->last = m->next;
        m->prev = newRule->guard;
        m->next->next = newRule->guard;
        newRule->n = 2;

        //one->printRule();
        //this->print();

        Node* dOcc = newRule->guard->next; //deprecatedOccurrence
        while (!dOcc->isGuard) { //DONT FORGET CHANGE THE OTHER
          if(dOcc->symbol>=128) {
            dOcc->rule->usage--;
            if (dOcc->rule->usage <= 1) {
              //Delete x1B and Bx2
              if (!dOcc->prev->isGuard) {
                this->remove(dOcc->prev);
              }
              if (!dOcc->next->isGuard) {
                this->remove(dOcc);
              }

              // Delete things
              dOcc->rule->guard->next->prev = dOcc->prev;
              dOcc->prev->next = dOcc->rule->guard->next;
              dOcc->rule->last->next = dOcc->next;
              dOcc->next->prev = dOcc->rule->last;
              if (dOcc->next->isGuard) {
                dOcc->next->rule->last = dOcc->rule->last;
              }
              if (!dOcc->next->isGuard){
                this->putUnique(dOcc->next->prev);
              }
              if (!dOcc->prev->isGuard) {
                this->putUnique(dOcc->prev);
              }

              //Revisar por el last
            }
          }
          dOcc = dOcc->next;
        }

      }


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
      if (node->symbol == node->next->symbol && !node->next->next->isGuard && node->symbol == node->next->next->symbol) //TEST THIS
        this->table[i] = node->next;
      else if (node->symbol == node->next->symbol && !node->prev->isGuard && node->symbol == node->prev->symbol) //TEST THIS
        this->table[i] = node->prev;
      else this->table[i] = deleted;
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

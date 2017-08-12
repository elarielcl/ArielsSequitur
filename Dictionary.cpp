#include <math.h>
#include <iostream>//Delete
#include "Dictionary.h"
#include "Node.h"

Dictionary::Dictionary(const unsigned int n) {

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
  this->deleted = new Node(true); // A guard node represents a deleted  one in the table :D
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
    }else if(!node->isGuard && node->symbol == m->symbol && node->next->symbol==m->next->symbol) {
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
    }else if(node->symbol == m->symbol && node->next->symbol==m->next->symbol) {
      this->table[i] = deleted;
      return;
    }
    i = (i + jump) % this->n;
  }
}

void Dictionary::print() {
  for (int i = 0; i < this->n; ++i) {
    Node* current = this->get(i);
    if (current && !current->isGuard)
      std::cout << (char)current->symbol << (char)current->next->symbol << std::endl;
    else
     std::cout << "No value" << std::endl;
  }
}

#include "Node.cpp"
#include <math.h>
#include <iostream>//Delete


class Dictionary {
  public:
    Node ** table; //Points to the first of the pairs
    unsigned int n; //Maximum number of pairs in the Dictionary
    Dictionary(const unsigned int n) {
      
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

    }

    void put(Node* node) {
      int i = node->hashCode() % this->n;
      int jump = 17 - (node->symbol % 17);
      while (1) {
        Node* m = this->table[i];
        if (m==NULL) {
          this->table[i] = node;
          break;
        }
        i = (i + jump) % this->n;
      }
    }

    Node* get(int i) {
      return this->table[i];
    }

    void print() {
      for (int i = 0; i < this->n; ++i) {
        Node* current = this->get(i);
        if (current)
          std::cout << std::endl << (char)current->symbol << (char)current->next->symbol;
        else
         std::cout << std::endl << "No value";
      }
    }
};

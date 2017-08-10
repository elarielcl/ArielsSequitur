#include <iostream>//Delete
#include "Dictionary.cpp"

class SequiturGrammar {
  private:
    int n;

    //Does I need a Rule?
    Node* initialGuard;
    Node* last;
    //Does I need a Rule?

  public:
    Dictionary* index; // change to private as the others

    SequiturGrammar() {
      this->index = new Dictionary(13);
      this->n = 0;

      Node* S = new Node('S'); //Use another symbol, another thing(?)
      this-> initialGuard = new Node();
      this->last = this->initialGuard;

      S->next = this->initialGuard;
      this->initialGuard->prev = S;
      this->last->next = this->initialGuard;
    }

    void put(int c) {
      Node* n = new Node(c);
      Node* prevLast = this->last;
      prevLast->next = n;
      n->prev = prevLast;
      this->last = n;
      this->last->next = this->initialGuard;
      ++this->n;

      if (this->n >= 2)
        this->index->put(prevLast);
    }

    void print() {
      this->index->print();

      std::cout << std::endl;
      Node* t = this->initialGuard->prev;
      while (!t->isGuard) {
        std::cout << (char)t->symbol;
        t = t->next;
      }

      std::cout << " -> ";
      t = t->next;
      while (!t->isGuard) {
        std::cout <<  (char)t->symbol;
        t = t->next;
      }
      std::cout << std::endl;
    }

};

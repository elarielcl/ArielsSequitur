#include <vector>//Delete
#include <string>//Delete
#include <iostream>//Delete
#include "Dictionary.cpp"

class SequiturGrammar {
  private:
    std::string grammar;//Remove
    std::vector<Node*> vec; //Remove
    Dictionary* index;

  public:
    SequiturGrammar() {
      //grammar = "";//Remove
      index = new Dictionary(13);
    }
    ~SequiturGrammar() {
      delete index;
    }

    void put(int c) {
      Node* n = new Node(c);
      if (this->vec.size() >= 1) {
        Node* last = this->vec.back();
        last->next=n;
        n->prev=last;
        this->index->put(*last);
      }
      vec.push_back(n);
    }

    std::string get() {
      return grammar;//Remove
    }

    void print() {
      //this->index->print();//Delete
      Node* head = this->vec.front();
      Node* t = head;
      while (1) {
        std::cout << std::endl << t->symbol;
        if (t->next == NULL) break;
        t = t->next;
      }

      while (1) {
        std::cout << std::endl << t->symbol;
        if (t->prev == NULL) break;
        t = t->prev;
      }
    }

};

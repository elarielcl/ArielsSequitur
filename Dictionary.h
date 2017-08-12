class Node;
class SequiturGrammar;
class Dictionary {
  public:
    Node ** table; //Points to the first of the pairs
    unsigned int n; //Maximum number of pairs in the Dictionary
    Node* deleted;
    SequiturGrammar* grammar;

    Dictionary(const unsigned int n, SequiturGrammar* grammar);

    void put(Node* node);

    void putUnique(Node* node);

    Node* get(int i);

    Node* get(Node* node);

    void remove(Node* node);

    void print();
};

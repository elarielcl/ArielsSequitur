class Node;
class SequiturGrammar;
class Dictionary {
  public:
    SequiturGrammar* grammar; // grammar of the index
    Node ** table; // digram's table
    unsigned int n; // maximum number of digrams in the Dictionary
    int a;// actual number of digrams in the Dictionary
    Node* deleted; // node representing a deleted node in the table (open addressing)


    Dictionary(const unsigned int n, SequiturGrammar* grammar);

    void put(Node* node);

    void putUnique(Node* node);

    Node* get(Node* node);

    void remove(Node* node);

    void print();
};

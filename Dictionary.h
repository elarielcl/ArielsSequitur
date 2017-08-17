class Node;
class SequiturGrammar;
class Dictionary {
  public:
    SequiturGrammar* grammar; // Grammar
    Node ** table; // Digram's table
    unsigned int n; // Maximum number of pairs in the Dictionary
    int a;// Actual number of pairs in the Dictionary
    Node* deleted; // Node representing a deleted node in the table (open addressing)


    Dictionary(const unsigned int n, SequiturGrammar* grammar);

    void put(Node* node);

    void putUnique(Node* node);

    Node* get(int i);

    Node* get(Node* node);

    void remove(Node* node);

    void print();
};

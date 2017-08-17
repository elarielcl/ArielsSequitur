class Node;
class SequiturGrammar;
class Dictionary {
  public:
    SequiturGrammar* grammar; // grammar of the index
    Node ** table; // digram's table
    unsigned int n; // maximum number of digrams in the Dictionary
    int a;// actual number of digrams in the Dictionary
    Node* deleted; // node representing a deleted node in the table (open addressing)

    // construct a Dictionary of <=n elements for the specified grammar
    Dictionary(const unsigned int n, SequiturGrammar* grammar);

    // put a digram starting at node in the Dictionary
    void put(Node* node);

    // put a digram starting at node in the Dictionary runs the Sequitur algorithm if digram Uniqueness condition is broken
    void putUnique(Node* node);

    // return a pointer to the specified digram (digram comparation) in the table, if this digram doesn't exist a pointer to its insertion position
    Node** get(Node* node);

    // delete a digram starting at node in the Dictionary
    void remove(Node* node);

    // print all the elements in the table (in table order)
    void print();
};

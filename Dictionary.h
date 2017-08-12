class Node;
class Dictionary {
  public:
    Node ** table; //Points to the first of the pairs
    unsigned int n; //Maximum number of pairs in the Dictionary
    Node* deleted;
    Dictionary(const unsigned int n);

    void put(Node* node);

    Node* get(int i);

    Node* get(Node* node);

    void remove(Node* node);

    void print();
};

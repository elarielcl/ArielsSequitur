class Dictionary;
class Node;
class Rule {
public:
    Node* guard;
    Node* last;
    Dictionary* index;
    int n;
    int usage;

    Rule(int c, Dictionary* index);

    void put(int c);

    void print();
};

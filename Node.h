class Rule;
class Node {
  public:
    int symbol; // symbol of the node
    Node* next; // next node in the double linkedList
    Node* prev; // prev node in the double linkedList
    Rule* rule; // ff nonTerminal rule of the nonTerminal, else rule where this Node is in

    // construct a symbol node, if no symbol specified then construct a guard node
    Node(Rule* rule, int symbol = 0);

    // wheter or not the Node is a guard node
    bool isGuard();

    // whether or not the digram have (only one) node in common
    bool digramOverlap(Node* other);

    // double links "this" followed by other
    void connect(Node* other);

    // return the hashCode of the pair (for HashTable)
    int hashCode();

    // print the rule where this Node is in
    void printRule();

    // print the digram starting at this node
    void printDigram();
};

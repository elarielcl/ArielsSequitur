class Rule;
class Node {
  public:
    int symbol;
    Node* next;
    Node* prev;
    Rule* rule;

    Node(Rule* rule);

    Node(Rule* rule, int symbol);

    bool isGuard();
    
    bool digramOverlap(Node* other);

    //Return the hashCode of the pair
    int hashCode();

    void printRule();

    void printDigram();
};

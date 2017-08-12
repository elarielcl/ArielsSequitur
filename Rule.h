class SequiturGrammar;
class Node;
class Rule {
public:
    Node* guard;
    Node* last;
    SequiturGrammar* grammar;
    int n;
    int usage;
    bool printed;
    
    Rule(int c, SequiturGrammar* grammar);

    void put(int c);

    void print();
};

#include <string>
class SequiturGrammar;
class Node;
class string;
class Rule {
public:
    static SequiturGrammar* grammar; // grammar of which the rule is part of (shared among rules)
    Node* guard; // guard node
    int usage; // number of times the rule is being referenced
    int symbol; // right symbol of the rule

    bool printed; // to output the grammar

    // construct a rule with the c symbol in the specified grammar
    Rule(int c, SequiturGrammar* grammar);

    // recursive print of rules (can be used only once)
    void print();

    // derive and print the result (recursive)
    void printUncompress();

    // derive and put the result on the string argument (recursive)
    void getUncompress(std::string*);
};

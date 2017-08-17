#include <string>
class SequiturGrammar;
class Node;
class string;
class Rule {
public:
    static SequiturGrammar* grammar;
    Node* guard;
    int n;
    int usage;
    int symbol;
    bool printed;

    Rule(int c, SequiturGrammar* grammar);

    void put(int c);

    void print();

    void printUncompress();

    void getUncompress(std::string*);
};

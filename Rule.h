#include <string>
class SequiturGrammar;
class Node;
class string;
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

    void printUncompress();

    void getUncompress(std::string*);
};

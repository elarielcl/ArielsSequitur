#include <string>
class Rule;
class Dictionary;
class SequiturGrammar {
  public:
    Rule* initialRule; // first rule of the grammar
    Dictionary* index; // index of digrams
    int grammarSize; // number of left-side symbols in the grammar
    int inputSize; // number of symbols put on the grammar
    int numberOfRules; // for counting the rules
    int nextRuleName; // for naming the rules
    int M; // smaller positive value not in the input symbols

    // constructor: optional arguments: M and indexSize(elements)
    SequiturGrammar(int M = 256 ,int indexSize = 125100000);

    // put a symbol on the grammar
    void put(int);

    // print the rules of the grammar
    void print();

    // derive and print the result
    void printUncompress();

    // derive and put the result on the string argument
    void getUncompress(std::string*);
};

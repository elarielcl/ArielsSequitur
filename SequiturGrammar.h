#include <string>
class Rule;
class Dictionary;
class SequiturGrammar {
  //private:



  public:
    Rule* initialRule;
    Dictionary* index; // change to private as the others
    int grammarSize;
    int inputSize;
    int numberOfRules;
    int M;
    SequiturGrammar();

    void put(int c);

    void print();

    void printUncompress();

    void getUncompress(std::string*);

};

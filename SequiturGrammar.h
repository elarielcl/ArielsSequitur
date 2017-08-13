class Rule;
class Dictionary;
class SequiturGrammar {
  //private:



  public:
    Rule* initialRule;
    Dictionary* index; // change to private as the others
    int numberOfRules;
    SequiturGrammar();

    void put(int c);

    void print();

    void printUncompress();

};

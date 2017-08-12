class Rule;
class Dictionary;
class SequiturGrammar {
  private:

    Rule* initialRule;

  public:
    Dictionary* index; // change to private as the others

    SequiturGrammar();

    void put(int c);

    void print();

};

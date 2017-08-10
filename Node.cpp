class Node {
  public:
    int symbol;
    bool isGuard;
    Node* next;
    Node* prev;

    Node() {
      this->isGuard = true;
    }
    Node(int symbol) {
      this->isGuard = false;
      this->symbol = symbol;
    }
    Node(bool isGuard) {
      this->isGuard = isGuard;
    }

    //Return the hashCode of the pair
    int hashCode() {
      int combined = ((this->symbol << 16) | (this->symbol >> 16)) ^ (this->next->symbol);
      return (combined * (combined + 3));
    }
};

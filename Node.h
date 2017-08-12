class Node {
  public:
    int symbol;
    bool isGuard;
    Node* next;
    Node* prev;

    Node();

    Node(int symbol);

    Node(bool isGuard);

    bool digramOverlap(Node* other);

    //Return the hashCode of the pair
    int hashCode();
};

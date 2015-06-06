#include <iostream>
#include <cstdlib>

using namespace std;

class Node {
public:
  int data;
  Node* left;
  Node* right;
  bool childrenSwapped;

  Node() : childrenSwapped(false) {
  }
};

void printInorder(Node* curr, int height, int level) {
  if (!curr) return;
  curr -> childrenSwapped ^= (height % level == 0);

  printInorder((curr -> childrenSwapped) ? curr -> right : curr -> left, height + 1, level);
  cout << curr -> data << " ";
  printInorder((curr -> childrenSwapped) ? curr -> left : curr -> right, height + 1, level);
}

int main() {
  int N;
  cin >> N;
  Node* myTree[N];
  for (int i = 0; i < N; i++) {
    Node* node = new Node();
    node -> data = i + 1;
    node -> left = NULL;
    node -> right = NULL;
    myTree[i] = node;
  }
  int lNode, rNode;
  for (int i = 0; i < N; i++) {
    cin >> lNode >> rNode;
    Node* node = myTree[i];
    node -> left = (lNode > 1) ? myTree[lNode - 1] : NULL;
    node -> right = (rNode > 1) ? myTree[rNode - 1] : NULL;
  }

  //printInorder(myTree[0]);
  int cases, lvl;
  cin >> cases;
  for (int i = 0; i < cases; ++i) {
    cin >> lvl;
    printInorder(myTree[0], 1, lvl);
    cout << endl;
  }
  return 0;
}

Node* reverse(Node *head) {
  Node *curr = head, *prev = NULL;

  while (curr != NULL) {
    Node *cdr = curr -> next;
    curr -> next = prev;
    prev = curr;
    curr = cdr;
  }
  return prev;
}

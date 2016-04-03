#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

//  Removes tnodes from the transaction list
void delete_tnode(tnode **n, int id) {
  tnode *temp;

  //  Head case
  if (graph_getID((*n)->transaction_acc) == id) {
    temp = (*n)->next;
    free(*n);
    *n = temp;
    return;
  }

  //  Any other part of the list
  tnode *current = *n;
  while (current->next != NULL) {
    if (graph_getID(current->next->transaction_acc) == id) {
      temp = current->next;
      current->next = temp->next;
      free(temp);
      break;
    }
    current = current->next;
  }
}

//  Frees the tlist allocated memory
void destroy_tlist(tnode **n) {
  tnode *current = *n;
  tnode *temp;
  while (current != NULL) {
    temp = current->next;
    free(current);
    current = temp;
  }
  *n = NULL;
}

//  Creates a new transaction (either sent or received)
//  and adds the amount and the associated bank account
void transaction_tnode(tnode **n, double amount, Graph *id) {
  //  Empty list
  if (*n == NULL) {
    *n = malloc(sizeof(tnode));
    (*n)->transaction_acc = id;
    (*n)->amount = amount;
    (*n)->next = NULL;
    return;
  }
  //  Already existing transaction
  tnode *current = *n;
  while (current != NULL) {
      if (current->transaction_acc == id) {
        current->amount += amount;
        return;
      }
      current = current->next;
  }
  //  New tnode on the end of the list
  tnode *temp = *n;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = malloc(sizeof(tnode));
  temp->next->transaction_acc = id;
  temp->next->amount = amount;
  temp->next->next = NULL;
}

//  Returns the total amount saved in this list
double amount_tnode(tnode *n) {
  tnode *current = n;
  double total = 0.0;

  while (current != NULL) {
      total += current->amount;
      current = current->next;
  }

  return total;
}

//  Returns 1 if the id passed is inside this list
int find_tnode(tnode *n, int id) {
  tnode *current = n;

  while (current != NULL) {
      if (graph_getID(current->transaction_acc) == id) {
        return 1;
      }
      current = current->next;
  }
  return 0;
}

//  Returns the account associated
//  with the specific tnode argument
Graph *get_graph(tnode *n) {
  return n->transaction_acc;
}

//  Prints all the transactions of this list
void print_tlist(tnode *n) {
    tnode *current = n;

    while (current != NULL) {
        printf("(%d , %f) ", graph_getID(current->transaction_acc), current->amount);
        current = current->next;
    }
    printf("\n");
}

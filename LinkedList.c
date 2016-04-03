#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

//  Adds nodes to the end of the list
void add_node(node **n, Graph *graph, int x) {
  if (*n == NULL) {
    *n = malloc(sizeof(node));
    (*n)->id = x;
    (*n)->bank_account = graph;
    (*n)->next = NULL;
    return;
  }
  node *temp = *n;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = malloc(sizeof(node));
  temp->next->id = x;
  temp->next->bank_account = graph;
  temp->next->next = NULL;
}

//  Removes nodes from the list
void delete_node(node **n, int x) {
  node *temp;

  if ((*n)->id == x) {
    temp = (*n)->next;
    free(*n);
    *n = temp;
    return;
  }

  node *current = *n;
  while (current->next != NULL) {
    if (current->next->id == x) {
      temp = current->next;
      current->next = temp->next;
      free(temp);
      break;
    }
    current = current->next;
  }
}

//  Frees the list allocated memory
void destroy_list(node **n) {
  node *current = *n;
  node *temp;
  while (current != NULL) {
    temp = current->next;
    graph_delete(current->bank_account);
    free(current);
    current = temp;
  }
  *n = NULL;
}

//  Returns true if there is a node with a given id
int find_node(node *n, int x) {
  node *current = n;

  while (current != NULL) {
      if (current->id == x) {
        return 1;
      }
      current = current->next;
  }
  return 0;
}

//  Returns the node with a given id
Graph *get_node(node *n, int x) {
  node *current = n;

  while (current != NULL) {
      if (current->id == x) {
        return current->bank_account;
      }
      current = current->next;
  }
  return NULL;
}

//  Prints the whole list
void print_list(node *n) {
    node *current = n;

    while (current != NULL) {
        graph_print(current->bank_account);
        current = current->next;
    }
}

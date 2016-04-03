#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Graph.h"

struct node {
  int id;
  struct node *next;
  struct Graph *bank_account;
};

typedef struct node node;

void add_node(node **n, Graph *graph, int x);
void delete_node(node **n, int x);
void destroy_list(node **n);
int find_node(node *n, int x);
Graph *get_node(node *n, int x);
void print_list(node *n);

#endif /* LINKEDLIST_H_ */

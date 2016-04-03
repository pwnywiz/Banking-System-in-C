#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

//  Creates a graph with a given id
Graph *graph_create(int id) {
  Graph *graph = malloc(sizeof(Graph));
  graph->id = id;
  graph->visited = 0;
  graph->sent = NULL;
  graph->received = NULL;

  return graph;
}

//  Inserts the given amount from / to the id, depending on the flag value
void graph_insert(Graph *graph, double amount, Graph *id, int flag) {
  if (flag) {
    transaction_tnode(&(graph->sent), amount, id);
  }
  else {
    transaction_tnode(&(graph->received), amount, id);
  }
}

//  Deletes either a sent or received transaction
//  with the id bank account, depending on the flag value
void graph_shorten(Graph *graph, int id, int flag) {
  if (flag) {
    if (find_tnode(graph->sent, id)) {
      delete_tnode(&(graph->sent), id);
    }
    else {
      printf("The transaction you are trying to delete does not exist\n");
    }
  }
  else {
    if (find_tnode(graph->received, id)) {
      delete_tnode(&(graph->received), id);
    }
    else {
      printf("The transaction you are trying to delete does not exist\n");
    }
  }
}

//  Deletes a graph
void graph_delete(Graph *graph) {
  destroy_tlist(&(graph->sent));
  destroy_tlist(&(graph->received));
  free(graph);
}

//  Returns true if the graph has no active transactions
int graph_empty(Graph *graph) {
  if ((graph->sent == NULL) && (graph->received == NULL)) {
    return 1;
  }
  return 0;
}

//  Returns the total amount of received or sent
//  transactions depending on the flag input value
int graph_amount(Graph *graph, int flag) {
  if (flag) {
    return amount_tnode(graph->sent);
  }
  else {
    return amount_tnode(graph->received);
  }
}

//  Marks the graph as visited
void graph_visited(Graph *graph) {
  graph->visited = 1;
}

//  Marks the graph as unvisited
void graph_unvisited(Graph *graph) {
  graph->visited = 0;
}

//  Returns the id of a graph
int graph_getID(Graph *graph) {
  return graph->id;
}

//  Prints the graph values
void graph_print(Graph *bnk_acc) {
  printf("vertex(%d) = ", bnk_acc->id);
  print_tlist(bnk_acc->sent);
}

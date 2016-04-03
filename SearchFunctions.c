#include <stdio.h>
#include <stdlib.h>
#include "BaseFunctions.h"

//  The recursive search parts of the BaseFunctions

void triangle_search(Graph *graph, visitors *vis, double limit) {
  //  If the graph has already been visited, skip it
  if (graph->visited) {
    return;
  }
  tnode *current = graph->sent;
  tnode *temp = graph->sent;
  if (current == NULL) {
    return;
  }
  //  When exactly 3 ids are into the array, search
  //  if the last account is pointing at the beggining
  if (vis->visits == 2) {
    while (temp != NULL) {
      if ((temp->amount >= limit) && (graph_getID(temp->transaction_acc) == vis->found[0])) {
        printf("Success: triangle(%d,%f)=\n", vis->found[0], limit);
        printf("(%d , %d , %d)\n", vis->found[0], vis->found[1], graph->id);
        return;
      }
      temp = temp->next;
    }
    return;
  }
  //  Add the account into the array
  vis->found[vis->visits] = graph->id;
  vis->visits++;
  graph->visited = 1;
  //  Perform a recursive search
  while (current != NULL) {
    if (current->amount >= limit) {
      triangle_search(get_graph(current), vis, limit);
    }
    current = current->next;
  }
  vis->visits--;
  graph_unvisited(graph);
}

int conn_search(Graph *graph, visitors *vis, int id_end) {
  if (graph->visited) {
    return 0;
  }
  //  If a path to the id_end was found, print it and exit
  if (graph->id == id_end) {
    int i;
    printf("success: conn(%d,%d) = (", vis->found[0], id_end);
    for (i = 0; i < vis->visits; i++) {
      printf("%d , ", vis->found[i]);
    }
    printf("%d)\n", id_end);
    return 1;
  }
  tnode *current = graph->sent;
  if (current == NULL) {
    return 0;
  }
  //  If there is not enough space in the array, double it
  if (vis->visits == vis->array_size) {
    vis->found = realloc(vis->found, (2*(vis->array_size))*sizeof(int));
    vis->array_size *= 2;
  }
  vis->found[vis->visits] = graph->id;
  vis->visits++;
  graph->visited = 1;
  while (current != NULL) {
    //  If a connection has been found, stop searching
    if (conn_search(get_graph(current), vis, id_end)) {
      graph_unvisited(graph);
      return 1;
    }
    current = current->next;
  }
  vis->visits--;
  graph_unvisited(graph);
  return 0;
}

void allcycles_search(Graph *graph, visitors *vis) {
  //  If there is at minimum a triangle formed, print it
  if ((graph->id == vis->found[0]) && (vis->visits > 2)) {
    int i;
    printf("success: cycles %d = \n(", vis->found[0]);
    for (i = 0; i < vis->visits - 1; i++) {
      printf("%d , ", vis->found[i]);
    }
    printf("%d)\n", vis->found[i]);
    return;
  }
  if (graph->visited) {
    return;
  }
  tnode *current = graph->sent;
  if (current == NULL) {
    return;
  }
  if (vis->visits == vis->array_size) {
    vis->found = realloc(vis->found, (2*(vis->array_size))*sizeof(int));
    vis->array_size *= 2;
  }
  vis->found[vis->visits] = graph->id;
  vis->visits++;
  graph->visited = 1;
  while (current != NULL) {
    allcycles_search(get_graph(current), vis);
    current = current->next;
  }
  vis->visits--;
  graph_unvisited(graph);
}

void traceflow_search(Graph *graph, visitors *vis, int depth, double *total) {
  if (graph->visited) {
    return;
  }
  if (vis->visits == depth) {
    int i;
    //  If the depth is reached, print the path and the total money sent
    printf("success: traceflow(%d,%d) = \n(", vis->found[0], depth);
    for (i = 0; i < vis->visits; i++) {
      printf("%d , ", vis->found[i]);
    }
    printf("%d, %f)\n", graph->id, *total);
    return;
  }
  tnode *current = graph->sent;
  if (current == NULL) {
    return;
  }
  vis->found[vis->visits] = graph->id;
  vis->visits++;
  graph->visited = 1;
  while (current != NULL) {
    *total += current->amount;
    traceflow_search(get_graph(current), vis, depth, total);
    //  Remove the money sent after the printing or searching;
    *total -= current->amount;
    current = current->next;
  }
  vis->visits--;
  graph_unvisited(graph);
}

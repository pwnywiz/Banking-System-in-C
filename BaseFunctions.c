#include <stdio.h>
#include <stdlib.h>
#include "BaseFunctions.h"

//  Creates a new graph with id and adds it
//  to the correct table of the hashtable ht
void createnodes(Hashtable *ht, int id) {
  if (hash_search(ht, id)) {
    printf("failure: Bank account already exists\n");
    return;
  }
  Graph *graph = graph_create(id);
  hash_insert(ht, graph, id);
  printf("success: created %d\n", id);
}

//  Deletes the graph with id as long as
//  there are no active sent or received transactions
void delnodes(Hashtable *ht, int id) {
  if (!hash_search(ht, id)) {
    printf("failure: The bank account you are trying to delete does not exist\n");
    return;
  }
  Graph *graph = hash_getBucket(ht, id);
  if (graph_empty(graph)) {
    graph_delete(graph);
    hash_delete(ht, id);
    printf("success: deleted %d\n", id);
  }
  else {
    printf("failure: The bank account you are trying to delete has active transactions\n");
  }
}

//  Adds a new transaction between the graph sender_id and receiver_id
void addtran(Hashtable *ht, double amount, int sender_id, int receiver_id) {
  if ((hash_search(ht, sender_id) == 0) || (hash_search(ht, receiver_id) == 0)) {
    printf("failure: Transaction can't be completed because a non existing account was entered\n");
    return;
  }
  Graph *sender = hash_getBucket(ht, sender_id);
  Graph *receiver = hash_getBucket(ht, receiver_id);

  graph_insert(sender, amount, receiver, 1);
  graph_insert(receiver, amount, sender, 0);
  printf("success: added transaction %d %d with %f\n", sender_id, receiver_id, amount);
}

//  Deletes a transaction between sender_id and receiver_id regardless the amount
void deltran(Hashtable *ht, int sender_id, int receiver_id) {
  if ((hash_search(ht, sender_id) == 0) || (hash_search(ht, receiver_id) == 0)) {
    printf("failure: Transaction can't be completed because a non existing account was entered\n");
    return;
  }
  Graph *sender = hash_getBucket(ht, sender_id);
  Graph *receiver = hash_getBucket(ht, receiver_id);

  graph_shorten(sender, receiver_id, 1);
  graph_shorten(receiver, sender_id, 0);
  printf("success: deleted transaction %d %d\n", sender_id, receiver_id);
}

//  Finds and prints the total income, outcome and sum
//  depending on the lookfor outcome that has been provided
void lookup(Hashtable *ht, int id, int lookfor) {
  if (!hash_search(ht, id)) {
    printf("failure: The bank account you are asking for does not exist\n");
    return;
  }
  Graph *graph = hash_getBucket(ht, id);
  double total = 0.0;

  if (lookfor == 1) { //  Search for total income
    total = graph_amount(graph, 0);
    printf("success: in(%d) = %f\n", id, total);
  }
  else if (lookfor == 2) { // Search for total outcome
    total = graph_amount(graph, 1);
    printf("success: out(%d) = %f\n", id, total);
  }
  else { //  Search for total income - outcome
    total = graph_amount(graph, 0);
    total -= graph_amount(graph, 1);
    printf("success: sum(%d) = %f\n", id, total);
  }
}

//  Finds and prints all the circular transactions between 3 accounts
void triangle(Hashtable *ht, int id, double limit) {
  if (!hash_search(ht, id)) {
    printf("failure: The bank account you are asking for does not exist\n");
    return;
  }
  Graph *graph = hash_getBucket(ht, id);
  visitors *vis = malloc(sizeof(visitors));
  vis->found = malloc(3*sizeof(int));
  vis->visits = 0;
  triangle_search(graph, vis, limit);
  free(vis->found);
  free(vis);
}

//  Finds and prints a possible connection
//  between the id_start and id_end account
void conn(Hashtable *ht, int id_start, int id_end) {
  if ((!hash_search(ht, id_start)) || (!hash_search(ht, id_end))) {
    printf("failure: At least one of the bank accounts you are asking for does not exist\n");
    return;
  }
  Graph *graph_start = hash_getBucket(ht, id_start);
  visitors *vis = malloc(sizeof(visitors));
  vis->found = malloc(4*sizeof(int));
  int i;
  for (i = 0; i < 4; i++) {
    vis->found[i] = 0;
  }
  vis->visits = 0;
  vis->array_size = 4;
  if (!conn_search(graph_start, vis, id_end)) {
    printf("success: conn (%d , %d) no connection between them\n", id_start, id_end);
  }
  free(vis->found);
  free(vis);
}

//  Finds and prints all the possible circular transactions that start from id
void allcycles(Hashtable *ht, int id) {
  if (!hash_search(ht, id)) {
    printf("failure: The bank account you are asking for does not exist\n");
    return;
  }
  Graph *graph = hash_getBucket(ht, id);
  visitors *vis = malloc(sizeof(visitors));
  vis->found = malloc(4*sizeof(int));
  int i;
  for (i = 0; i < 4; i++) {
    vis->found[i] = 0;
  }
  vis->found[0] = 0;
  vis->visits = 0;
  vis->array_size = 4;
  allcycles_search(graph, vis);
  free(vis->found);
  free(vis);
}

//  Finds and prints all possible transactions of id in the depth provided
void traceflow(Hashtable *ht, int id, int depth) {
  if (!hash_search(ht, id)) {
    printf("failure: The bank account you are asking for does not exist\n");
    return;
  }
  double total = 0;
  Graph *graph = hash_getBucket(ht, id);
  visitors *vis = malloc(sizeof(visitors));
  vis->found = malloc(depth*sizeof(int));
  int i;
  for (i = 0; i < depth; i++) {
    vis->found[i] = 0;
  }
  vis->found[0] = 0;
  vis->visits = 0;
  vis->array_size = depth;
  traceflow_search(graph, vis, depth, &total);
  free(vis->found);
  free(vis);
}

//  Deletes all the graphs created so far
void bye(Hashtable *ht) {
  hash_destroy(ht);
  printf("success: cleaned memory\n");
}

//  Prints every graph account and
//  its outcoming transactions with others
void print(Hashtable *ht) {
  hash_printall(ht);
}

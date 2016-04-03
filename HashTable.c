#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"

//  Create a hash array of n tables
//  as well as allocate the required memory
Hashtable *hash_create(int n) {
  int i;

  Hashtable *hash = malloc(sizeof(Hashtable));
  hash->tables = n;
  hash->hashtable = malloc(n*sizeof(node));
  for (i = 0; i < n; i++) {
    hash->hashtable[i] = NULL;
  }

  return hash;
}

//  Check if the id has already been inserted
//  Then insert the new id into the hashtable
void hash_insert(Hashtable *ht, Graph *graph, int id) {
  int n = ht->tables;
  add_node(&(ht->hashtable[id%n]), graph, id);
}

//  Clear a specific account from the hashtable
void hash_delete(Hashtable *ht, int id) {
  int n = ht->tables;
  delete_node(&(ht->hashtable[id%n]), id);
}

//  Clear all the hashtable nodes
void hash_destroy(Hashtable *ht) {
  int i;
  int n = ht->tables;
  for (i = 0; i < n; i++) {
    destroy_list(&ht->hashtable[i]);
  }
  for (i = 0; i < n; i++) {
    ht->hashtable[i] = NULL;
  }
  //  Use here only if user input gets removed
  // free(ht->hashtable);
  // free(ht);
}

//  Get a graph with the specified id
Graph *hash_getBucket(Hashtable *ht, int id) {
  int n = ht->tables;
  return get_node(ht->hashtable[id%n], id);
}

//  Print the whole hashtable
void hash_printall(Hashtable *ht) {
  int i;
  int size = ht->tables;
  for (i = 0; i < size; i++) {
    if (ht->hashtable[i] != NULL) {
      print_list(ht->hashtable[i]);
    }
  }
}

//  Search if if an account with id is inside the table
int hash_search(Hashtable *ht, int id) {
  int n = ht->tables;
  return find_node(ht->hashtable[id%n], id);
}

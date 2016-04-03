#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "LinkedList.h"

struct Hashtable {
  int tables;
  node **hashtable;
};

typedef struct Hashtable Hashtable;

Hashtable *hash_create(int n);
void hash_insert(Hashtable *ht, Graph *graph, int id);
void hash_delete(Hashtable *ht, int id);
void hash_destroy(Hashtable *ht);
Graph *hash_getBucket(Hashtable *ht, int id);
void hash_printall(Hashtable *ht);
int hash_search(Hashtable *ht, int id);

#endif /* HASHTABLE_H_ */

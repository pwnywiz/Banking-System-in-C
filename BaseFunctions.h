#ifndef BASEFUNCTIONS_H_
#define BASEFUNCTIONS_H_

#include "HashTable.h"

struct visitors {
  int visits;
  int array_size;
  int *found;
};

typedef struct visitors visitors;

//  Required functions
void createnodes(Hashtable *ht, int id);
void delnodes(Hashtable *ht, int id);
void addtran(Hashtable *ht, double amount, int sender_id, int receiver_id);
void deltran(Hashtable *ht, int sender_id, int receiver_id);
void lookup(Hashtable *ht, int id, int lookfor);
void triangle(Hashtable *ht, int id, double limit);
void conn(Hashtable *ht, int id_start, int id_end);
void allcycles(Hashtable *ht, int id_start);
void traceflow(Hashtable *ht, int id, int depth);
void bye(Hashtable *ht);
void print(Hashtable *ht);

//  Recursive helpful functions
void triangle_search(Graph *graph, visitors *vis, double limit);
int conn_search(Graph *graph, visitors *vis, int id_end);
void allcycles_search(Graph *graph, visitors *vis);
void traceflow_search(Graph *graph, visitors *vis, int depth, double *total);

#endif /* BASEFUNCTIONS_H_ */

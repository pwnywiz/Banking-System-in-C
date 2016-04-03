#ifndef GRAPH_H_
#define GRAPH_H_

struct Graph {
  int id;
  int visited;
  struct tnode *sent;
  struct tnode *received;
};

struct tnode {
  struct Graph *transaction_acc;
  double amount;
  struct tnode *next;
};

typedef struct Graph Graph;
typedef struct tnode tnode;

//  Graph functions
Graph *graph_create(int id);
void graph_insert(Graph *graph, double amount, Graph *id, int flag);
void graph_shorten(Graph *graph, int id, int flag);
void graph_delete(Graph *graph);
int graph_empty(Graph *graph);
int graph_amount(Graph *graph, int flag);
void graph_visited(Graph *graph);
void graph_unvisited(Graph *graph);
int graph_getID(Graph *graph);
Graph *get_graph(tnode *n);
void graph_print();

//  tnode functions
void delete_tnode(tnode **n, int id);
void destroy_tlist(tnode **n);
void transaction_tnode(tnode **n, double amount, Graph *idm);
double amount_tnode(tnode *n);
int find_tnode(tnode *n, int id);
void print_tlist(tnode *n);

#endif /* GRAPH_H_ */

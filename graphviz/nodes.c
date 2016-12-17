#include <gvc.h>

int main(int argc, char **argv)
{
  /* toplevel graph: */
  Agraph_t *g;

  /* digraph G {} */
  g = agopen("G", Agdirected, NULL);

  /* so far same as first.c */

  /* two new nodes: */
  Agnode_t *n1, *n2;
  /* add them to graph: */
  n1 = agnode(g,"node28",TRUE);	
  n2 = agnode(g,"node29",TRUE);
  /* 1st: (sub)graph; 
     2nd: name (NULL if anonymous)
     3rd: if TRUE: create if does not exist,
          if FALSE: search, and return NULL if not found
  */

  /* degree:
     in-degree:
     agdegree(g,n,TRUE,FALSE) 

     out-degree:
     agdegree(g,n,FALSE,TRUE)

     sum of above two:
     agdegree(g,n,TRUE,TRUE)

     using:
     agcountuniqedges
     counts loops only ones, if last two are TRUE
   */

  /* delete from subgraph:
     agdelnode(g,n)
 */

  g = agwrite(g,stdout);

  return 0;
}

#include <gvc.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  /* toplevel graph: */
  Agraph_t *g;

  /* digraph G {} */
  g = agopen("G", Agdirected, NULL);

  /* two new nodes: */
  Agnode_t *n1, *n2;
  /* add them to graph: */
  n1 = agnode(g,"node28",TRUE);	
  n2 = agnode(g,"node29",TRUE);

  /* so far same as nodes.c */

  /* and edge has: a "head" and a "tail"
     if undirected, both endpoints can be either
   */

  /* an edge */
  Agedge_t *e;

  /* connect n1 and n2 in graph g */
  e = agedge(g,n1,n2,"e28",TRUE); 
  /* "e28" is the edge identifier: should be unique */
  
  /* agtail(e) and aghead(e) return the endpoints of e */
  //fprintf(stderr,"head %s, tail %s\n",aghead(e),agtail(e)); //needed: some way to get things from agnode structure

  /* The value e->node is the “other” endpoint with respect to 
     the node from which e was obtained. 
     That is, 
     if e is an out-edge of node n 
     (equivalently, n is the tail of e), 
     then e->node is the head of e 
  */
  //for (e = agfstout(g,n); e; e = agnxtout(g,e))
    /* do something with e->node */

  /* finds any u,v edge */
  //e = agedge(g,u,v,NULL,FALSE);
  /* finds a u,v edge with name "e8" */
  //e = agedge(g,u,v,"e8",FALSE);

  /*  evaluates to true if the two pointers represent the same abstract edge
      used for edge comparison
      ageqedge(Agedge_t *e0, Agedge_t *e1)
   */

  /* write out results */
  g = agwrite(g,stdout);

  return 0;
}

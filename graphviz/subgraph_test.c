#include <gvc.h>

int main(int argc, char **argv)
{
  /* toplevel graph: */
  Agraph_t *g, *s1, *s2;

  /* digraph G {} */
  g = agopen("G", Agundirected, NULL);
  s1 = agsubg(g,"cluster0",TRUE);
  s2 = agsubg(g,"cluster1",TRUE);
  //agattr(g,AGRAPH,"style","filled");
  //agattr(g,AGRAPH,"color","pink");
  //agattr(g,AGRAPH,"label","g");

  //agsafeset(g,"style","filled","");
  //agsafeset(g,"color","pink","");
  //agsafeset(g,"label","g","");

  agsafeset(s1,"style","filled","");
  agsafeset(s1,"color","lightgrey","");
  agsafeset(s1,"label","s1","");

  agsafeset(s2,"style","filled","");
  agsafeset(s2,"color","lightblue","");
  agsafeset(s2,"label","s2","");

  /* so far same as first.c */

  /* two new nodes: */
  Agnode_t *n0,*n1, *n2, *n3, *n4;
  n0 = agnode(g,"node00",TRUE);	
  /* add them to graph: */
  n1 = agnode(s1,"node28",TRUE);	
  n2 = agnode(s1,"node29",TRUE);

  n3 = agnode(s2,"node30",TRUE);	
  n4 = agnode(s2,"node31",TRUE);
  
  /* an edge */
  Agedge_t *e00,*e01,*e02,*e03;

  /* connect n1 and n2 in graph g */
  e00 = agedge(g,n0,n1,"e00",TRUE); 
  e01 = agedge(g,n0,n3,"e01",TRUE); 
  e02 = agedge(s1,n1,n2,"e02",TRUE); 
  e03 = agedge(s2,n3,n4,"e03",TRUE); 
  //Agedge_t *e04;
  //e04 = agedge(g,n2,n4,"e04",TRUE); 

  agsafeset(e00,"color","grey","");
  agsafeset(e01,"color","cyan","");
  agsafeset(e02,"color","yellow","");
  agsafeset(e03,"color","red","");

  agwrite(g,stdout);

  return 0;
}

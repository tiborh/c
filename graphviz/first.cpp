#include <gvc.h>

/*
  Agraph_t: a graph or subgraph
  Agnode_t: a node from a particular graph or subgraph
  Agedge_t: an edge from a particular graph or subgraph
  Agsym_t: a descriptor for a string-value pair attribute
  Agrec_t: an internal C data record attribute of a graph object
*/

int main(int argc, char **argv)
{
  /* toplevel graph: */
  Agraph_t *g;

  /* "G" is the name of the node
     "Agdirected" is the directed graph
  */

  g = agopen("G", Agdirected, NULL); /* instead of NULL, method overriding defaults can be used */

  /* other options: 
     Agdirected 
     Agstrictdirected
     Agundirected
     Agstrictundirected
  */

  /* To get the name of the graph: 
     agnameof(g) 

     to get its properties:
     agisdirected(g)
     agisstrict(g)
  */

  /* graph read from file:
     g = agread(stdin,NULL); //NULL:  optional method pointer
  */

  /* graph created from string:
     g = agmemread (str);
  */

  /* write graph to file:
     g = agwrite(g,stdout); // makes pointer out of integer warning
  */
  agwrite(g,stdout); 	/* empty graph{} is printed */

  /* return the count of
     nodes:
     agnnodes(g)

     edges:
     agnedges(g)

     subgraphs in a graph or subgraph:
     agnsubg(g)
   */

  /* concatenate the contents of a graph file onto an existing graph
     g = agconcat(g,stdin,NULL);
   */

  /* to delete a graph data structure:
     agclose(g); //segfault, not recommended
   */

  return 0;
}

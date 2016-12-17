#include <gvc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int NU_OF_NODES = 10;

Agnode_t** fillgraph(Agraph_t *g)
{
  /* nodes: */
  Agnode_t **nodes = malloc(NU_OF_NODES * sizeof(Agnode_t));

  char* nodename = malloc(((int)(NU_OF_NODES/10)+3)*sizeof(char));
  *nodename = 'n';
  *(nodename+2) = '\0';
  for (int i = 0; i < NU_OF_NODES; i++)
    {
      *(nodename+1) = (char)(i+0x30);
      nodes[i] = agnode(g,nodename,TRUE);
    }
  free(nodename);

  return nodes;
}

template <typename 
Agedge_t** connect_graph(Agraph_t *g,Agnode_t **nodes)
{
  int arr_length = (int)(NU_OF_NODES/10)+3;
  Agedge_t **edges = malloc(NU_OF_NODES * sizeof(Agedge_t));

  char* edgename = malloc(arr_length*sizeof(char));

  //fprintf(stderr,"in edges\n");
  *edgename = 'e';
  *(edgename+2) = '\0';
  for (int i = 0; i < NU_OF_NODES; ++i)
    {
      //fprintf(stderr,"\tin loop, i == %d\n",i);
      if (i+1 < NU_OF_NODES)
	{
	  *(edgename+1) = (char)(i+0x30);
	  //fprintf(stderr,"\t\tin if, edgename == %s\n",edgename);
	  edges[i] = agedge(g,nodes[i],nodes[i+1],edgename,TRUE);
	  if(i+2 < NU_OF_NODES)
	    {
	      *(edgename+1) = (char)(i+1+0x30);
	      edges[i+1] = agedge(g,nodes[i],nodes[i+2],edgename,TRUE);
	      ++i;
	    }
	  //fprintf(stderr,"\t\tpassed\n");
	}
    }
  free(edgename);

  return edges;
}

int main(int argc, char **argv)
{
  /* toplevel graph: */
  Agraph_t *g, *subg;

  /* digraph G {} */
  g = agopen("G", Agdirected, NULL);

  /* generate nodes */
  Agnode_t** nodes = fillgraph(g);
  //fprintf(stderr,"nodes have been set\n");
  
  /* connect nodes */
  Agedge_t **edges = connect_graph(g,nodes);

  /* create a subgraph */
  /* search for subgraph by name */
  subg = agsubg(g,"asubgraph",FALSE);
  /* create if it does not exist */
  if (!subg)
      subg = agsubg(g,"asubgraph",TRUE);

  /* iteration over subgraphs */
  for (subg = agfstsubg(g); subg; subg = agnxtsubg(subg)) {
    /* agparent is up one level */
    assert (g == agparent(subg));
    /* Use subgraph h */
  }

  /* write out results */
  agwrite(g,stdout);


  /*  agsubnode and agsubedge can be used to populate subgraph with earlier created elements */
  agsubnode(subg, nodes[4], TRUE);

  free(edges);
  free(nodes);
  free(subg);
  free(g);

  return 0;
}

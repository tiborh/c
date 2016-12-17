#include <gvc.h>
#include <stdio.h>
#include <stdlib.h>

const int NU_OF_NODES = 10;
char* shapes[] = {"box",
		  "polygon",
		  "ellipse",
		  "oval",
		  "circle",
		  "egg",
		  "triangle",
		  "diamond",
		  "trapezium",
		  "parallelogram"};

char* colours[] = {"chartreuse",
		  "goldenrod",
		  "darkolivegreen",
		  "aquamarine",
		  "deeppink",
		  "brown",
		  "deepskyblue",
		  "magenta",
		  "turquoise",
		  "darkred"};

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

void traverse_nodes(Agraph_t *g, char* attrib, char** values)
{
  Agnode_t *n;
  int i = 0;
  for (n = agfstnode(g); n; n = agnxtnode(g,n), i++)
      agsafeset(n, attrib, values[i], "");
}

void traverse_edges(Agraph_t *g, char* attrib, char** values)
{
  Agnode_t *n;
  Agedge_t *e;
  int i = 0;
  int j = 0;
  for (n = agfstnode(g); n; n = agnxtnode(g,n), i++)
    for (e = agfstout(g,n); e; e = agnxtout(g,e),j++)
      agsafeset(e, attrib, values[j], "");
}



int main(int argc, char **argv)
{
  /* toplevel graph: */
  Agraph_t *g;

  /* digraph G {} */
  g = agopen("G", Agdirected, NULL);

  /* generate nodes */
  Agnode_t** nodes = fillgraph(g);
  //fprintf(stderr,"nodes have been set\n");
  
  /* connect nodes */
  Agedge_t **edges = connect_graph(g,nodes);

  /* set basic shape */
  agattr(g,AGNODE,"shape","box");

  /* traversal */
  traverse_nodes(g,"shape",shapes);
  traverse_edges(g,"color",colours);

  /* write out results */
  g = agwrite(g,stdout);

  free(edges);
  free(nodes);

  return 0;
}

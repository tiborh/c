#include <gvc.h>
#include <stdio.h>
#include <stdlib.h>

const int NU_OF_NODES = 10;
const char* shapes[] = {"box",
		  "polygon",
		  "ellipse",
		  "oval",
		  "circle",
		  "egg",
		  "triangle",
		  "diamond",
		  "trapezium",
		  "parallelogram"};

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
  Agsym_t *sym;
  sym = agattr(g,AGNODE,"shape","box");
  /* second can be: AGRAPH, AGNODE and AGEDGE */
  
  /* search for attribute */
  sym = agattr(g,AGNODE,"shape",0);
  if (sym)
    fprintf(stderr,"The default shape is %s.\n",sym->defval);

  Agsym_t* sym1 = agattrsym (nodes[0],"shape");
  if (sym1)
    fprintf(stderr,"The default shape is %s.\n",sym->defval);
  /* Both functions return NULL if the attribute is not defined. */

  /* iterate over attributes: */
  Agsym_t* sym2 = 0; /* to get the first one */
  while ((sym2 = agnxtattr(g,AGNODE,sym2)))
    fprintf(stderr,"%s = %s\n",sym2->name,sym2->defval);

  /* agget: to get the attribute value */
  char* str = agget(nodes[0],"shape");
  fprintf(stderr,"value of str: %s\n",str);

  /* to set an attribute */
  agset(nodes[0],"shape","hexagon");
  agset(nodes[1],"shape","none"); /* no frame */
  str = agget(nodes[1],"shape");
  fprintf(stderr,"value of str (after node set to \"none\") : %s\n",str);

  /* If an attribute will be referenced often, 
     it is faster to use its descriptor as an index 
  */
  Agsym_t *sym3 = agattr(g,AGNODE,"shape","star"); /* initialise */
  str = agxget(nodes[2],sym3);			   /* connect, and get */
  fprintf(stderr,"nodes[2]: %s\n",str);
  agxset(nodes[2],sym3,"house"); /* set */
  /* Set an attribute - in this case one that affects the visible rendering */
  agsafeset(nodes[3], "color", "red", "");
  agsafeset(nodes[2], "color", "blue", "");

  /* copy attribs */
  agcopyattr(nodes[2], nodes[4]);

  /* write out results */
  g = agwrite(g,stdout);

  free(edges);
  free(nodes);

  return 0;
}

#include <gvc.h>
#include <stdio.h>
//#include <stdlib.h>

int main(int argc, char** argv)
{
  /* creating record to attach: */
  typedef struct mynode_s {
    Agrec_t     h;		/* important, header */
    int         count;		/* the payload comes from here */
  } mynode_t;
 
  /* toplevel graph: */
  Agraph_t *g;

  /* digraph G {} */
  g = agopen("G", Agdirected, NULL);

  mynode_t *data;
  Agnode_t *n;
  n = agnode(g,"mynodename",TRUE);
  /* uninterpreted record can be attached: */
  data = (mynode_t*)agbindrec(n,"mynode_t",sizeof(mynode_t),FALSE);
  data->count = 1;		/* referencing record */

  /* search for record:
     aggetrec

     remove record from object:
     agdelrec

     all nodes updated:
     void aginit(Agraph_t *g, int kind, char *rec_name, 
                 int rec_size, int move_to_front);
     void agclean(Agraph_t *g, int kind, char* rec_name);
     
     additional heap memory to a record is the resp of the programmer
*/

  agwrite(g,stdout);

  return 0;
}

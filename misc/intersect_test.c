#include <stdio.h>
#include <stdbool.h>

#define DIM 2
typedef struct apoint {
  int x;
  int y;
} Point;

int area2 (Point a, Point b, Point c)
{
  return ((b.x - a.x) * (c.y - a.y) -
	  (c.y - a.x) * (b.y - a.y));
}

bool colinear(Point a, Point b, Point c)
{
  return area2( a,b,c ) == 0;
}

bool xor(bool x, bool y)
{
  return !x ^ !y;
}

bool left(Point a, Point b, Point c)
{
  return area2(a,b,c) > 0;
}

bool intersectProp(Point a, Point b, Point c, Point d)
{
  if (   colinear(a,b,c)
      || colinear(a,b,d)
      || colinear(c,d,a)
      || colinear(c,d,b)
      )
    return false;

  return (xor(left(a,b,c),left(a,b,d)) &&
	  xor(left(c,d,a),left(c,d,b))
	  );
}

bool between(Point a, Point b, Point c)
{
  //Point ba,ca;
  
  if ( colinear(a,b,c) )
       return false;

  if ( a.x != b.x )
    return (((a.x <= c.x) && (c.x <= b.x)) ||
	    ((a.x >= c.x) && (c.x >= b.x)));
  else
    return (((a.y <= c.y) && (c.y <= b.y)) ||
	    ((a.y >= c.y) && (c.y >= b.y)));
}

bool intersect(Point a, Point b, Point c, Point d)
{
  if (intersectProp(a,b,c,d))
    return true;
  else if (    between(a,b,c)
	    || between(a,b,d)
	    || between(c,d,a)
	    || between(c,d,b)
	       )
    return true;
  else return false;
}

bool doLinesIntersect(Point a, Point b, Point c, Point d) {
  int x1 = a.x;
  int x2 = b.x;
  int x3 = c.x;
  int x4 = d.x;
  int y1 = a.y;
  int y2 = b.y;
  int y3 = c.y;
  int y4 = d.y;
  double m1,m2;
  
  if (x1 == x2) {
    return !(x3 == x4 && x1 != x3);
  } else if (x3 == x4) {
    return true;
  } else {
    // Both lines are not parallel to the y-axis
    m1 = ((y1-y2)/(x1-x2));
    m2 = ((y3-y4)/(x3-x4));
    printf("m1: %lf, m2: %lf\n",m1,m2);
    return m1 != m2;
  }
}

int main(int argc, char** argv)
{
  //segment 1
  Point a,b;
  a.x = 1;
  a.y = 2;
  b.x = 3;
  b.y = 4;
  printf("a: (%d,%d)\n",a.x,a.y);
  printf("b: (%d,%d)\n",b.x,b.y);

  //segment 2
  Point c,d;
  c.x = 3;
  c.y = 4;
  d.x = 5;
  d.y = 6;
  printf("c: (%d,%d)\n",c.x,c.y);
  printf("d: (%d,%d)\n",d.x,d.y);
  printf("Intersect? %d\n",intersect(a,b,c,d));
  printf("Intersect? %d (a,b twice)\n",intersect(a,b,a,b));
  printf("Intersect? %d (a,c,a,b twice)\n",intersect(a,c,a,b));

  //segment 3
  Point e,f;
  e.x = 2;
  e.y = 5;
  f.x = 3;
  f.y = 2;
  printf("e: (%d,%d)\n",e.x,e.y);
  printf("f: (%d,%d)\n",f.x,f.y);
  printf("Intersect? %d (a,b,e,f)\n",intersect(a,b,e,f));
  printf("other method: %d\n",doLinesIntersect(a,b,e,f));
  printf("Intersect? %d (e,f,c,d)\n",intersect(e,f,c,d));
  printf("other method: %d\n",doLinesIntersect(e,f,c,d));

  //segment 4
  Point g,h;
  g.x = 2;
  g.y = 1;
  h.x = 4;
  h.y = 3;
  printf("g: (%d,%d)\n",g.x,g.y);
  printf("f: (%d,%d)\n",h.x,h.y);
  printf("Intersect? %d (a,b,g,h)\n",intersect(a,b,g,h));
  printf("other method: %d\n",doLinesIntersect(a,b,g,h));
  return 0;
}

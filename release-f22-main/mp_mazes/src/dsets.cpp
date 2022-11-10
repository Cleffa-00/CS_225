#include "dsets.h"
#include <iostream>

using namespace std;

void DisjointSets::addelements(int num)
{
  while (num -- ) p.push_back(-1);
}

int DisjointSets::find(int elem)
{
  if (p[elem] >= 0) return p[elem] = find(p[elem]);
  return elem;
}

void DisjointSets::setunion(int a, int b)
{
  int pa = find(a), pb = find(b);
  if (p[pa] <= p[pb])
  {
    p[pa] += p[pb];
    p[pb] = pa;
  }
  else 
  {
    p[pb] += p[pa];
    p[pa] = pb;
  }
}

int DisjointSets::size(int elem)
{
  return -p[find(elem)];
}
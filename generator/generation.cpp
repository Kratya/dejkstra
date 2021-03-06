#include <fstream>
#include <iostream>
#include <ctime> 
#include <string>
#include <set>
#include <filesystem>

using namespace std;

typedef unsigned int UINT;

const UINT TESTS_NUMBER = 1;
const UINT MAX_WEIGHT = 1000;

void generate(const UINT &v, const UINT &e, ofstream &out);

bool copy_file(const string &src, const string &dest);

int main()
{
   ofstream out;
   UINT n = 0, m = 0;

   srand(time(NULL));

   for (UINT i = 0; i < TESTS_NUMBER; i++)
   {
      string path = "C:/Users/User/source/repos/dejkstra/dejkstra/tests/graph" + to_string(i + 1) + ".txt";
      string pq_path = "C:/Users/User/source/repos/dejkstra/dejkstra_pq/tests/graph" + to_string(i + 1) + ".txt";
      out.open(path);
      
      cin >> n >> m;
      generate(n, m, out);

      copy_file(path, pq_path);

      out.close();
   }

   return 0;
}

void generate(const UINT &v, const UINT &e, ofstream &out)
{
   UINT vertices = v, edges = e, v1 = 0, v2 = 0;

   set<pair<UINT, UINT>> c;

   if (vertices == 1)
      edges = 0;
   else if (edges > vertices * (vertices - 1) / 2)
      edges = rand() % (vertices * (vertices - 1) / 2);

   out << vertices << " " << edges << endl;

   for (UINT i = 0; i < edges; i++)
   {
      v1 = rand() % vertices + 1;

      do
         v2 = rand() % vertices + 1;
      while (v1 == v2);

      if (c.find(make_pair(v1, v2)) != c.end() || c.find(make_pair(v2, v1)) != c.end())
         i--;
      else
      {
         c.insert(make_pair(v1, v2));
         out << v1 << " " << v2 << " " << rand() % MAX_WEIGHT + 1 << endl;
      }
   }

   out << rand() % vertices + 1 << endl;
}

bool copy_file(const string &src, const string &dest)
{
   ifstream source(src);
   ofstream destination(dest);

   destination << source.rdbuf();

   return source && destination;
}

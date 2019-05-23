#include <fstream>
#include <vector>
#include <limits>
#include <chrono>
#include <string>

typedef unsigned int UINT;
typedef unsigned __int64 UINT64;

using namespace std;

const UINT TESTS_NUMBER = 1;
const UINT64 INF = numeric_limits<UINT64>::max();

vector<vector<pair<UINT, UINT>>> scan(ifstream &in, const UINT &n, const UINT &m);

vector<UINT64> dejkstra(const vector<vector<pair<UINT, UINT>>> &graph, const UINT &n, const UINT &start);

int main()
{
   for (UINT cnt = 0; cnt < TESTS_NUMBER; cnt++)
   {
      ifstream in("tests/graph" + to_string(cnt + 1) + ".txt");

      UINT n = 0, m = 0;
      in >> n >> m;

      vector<vector<pair<UINT, UINT>>> graph = scan(in, n, m);

      UINT start = 0;
      in >> start;

      in.close();

      auto t_start = chrono::high_resolution_clock().now();

      vector<UINT64> res = dejkstra(graph, n, start);

      auto t_end = chrono::high_resolution_clock().now() - t_start;
      double elapsed_time = chrono::duration<double>(t_end).count();

      ofstream out("results/out" + to_string(cnt + 1) + ".txt");

      out << "Elapsed time: " << fixed << elapsed_time << " seconds" << endl;

      for (UINT i = 0; i < res.size(); i++)
      {
         out << start << "-" << i + 1 << " = ";

         if (res[i] == INF)
            out << "there is no way" << endl;
         else
            out << res[i] << endl;
      }

      out.close();
   }

   return 0;
}

vector<vector<pair<UINT, UINT>>> scan(ifstream &in, const UINT &n, const UINT &m)
{
   vector<vector<pair<UINT, UINT>>> graph(n);

   for (UINT i = 0; i < m; i++)
   {
      UINT u = 0, v = 0, w = 0;
      in >> u >> v >> w;

      graph[u - 1].push_back(make_pair(v - 1, w));
      graph[v - 1].push_back(make_pair(u - 1, w));
   }

   return graph;
}

vector<UINT64> dejkstra(const vector<vector<pair<UINT, UINT>>> &graph, const UINT &n, const UINT &start)
{
   vector<UINT64> d(n, INF);
   vector<bool> marks(n, false);

   d[start - 1] = 0;

   for (UINT i = 0; i < n; i++)
   {
      int t = -1;

      for (UINT j = 0; j < n; j++)
         if (!marks[j] && (t == -1 || d[j] < d[t]))
            t = j;

      if (d[t] == INF)
         break;

      marks[t] = true;

      for (UINT k = 0; k < graph[t].size(); k++)
      {
         UINT to = graph[t][k].first;
         UINT len = graph[t][k].second;

         if (d[t] + len < d[to])
            d[to] = d[t] + len;
      }
   }

   return d;
}
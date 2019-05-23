#include <fstream>
#include <queue>
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

vector<UINT64> dejkstra_pq(const vector<vector<pair<UINT, UINT>>> graph, const UINT &n, const UINT &start);

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

      vector<UINT64> res = dejkstra_pq(graph, n, start);

      auto t_end = chrono::high_resolution_clock().now() - t_start;
      double elapsed_time = chrono::duration<double>(t_end).count();

      ofstream out("results/out" + to_string(cnt + 1) + ".txt");

      out << "N = " << n << ", M = " << m << endl << "Elapsed time: " << fixed << elapsed_time << " seconds" << endl;

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

vector<UINT64> dejkstra_pq(const vector<vector<pair<UINT, UINT>>> graph, const UINT &n, const UINT &start)
{
   priority_queue<pair<UINT, UINT>, vector<pair<UINT, UINT>>, greater<pair<UINT, UINT>>> pq;
   vector<UINT64> res(n, INF);

   pq.push(make_pair(0, start - 1));
   res[start - 1] = 0;

   while (!pq.empty())
   {
      UINT u = pq.top().second;
      pq.pop();

      for (auto x : graph[u])
      {
         UINT v = x.first, w = x.second;

         if (res[v] > res[u] + w)
         {
            res[v] = res[u] + w;
            pq.push(make_pair(res[v], v));
         }
      }
   }

   return res;
}
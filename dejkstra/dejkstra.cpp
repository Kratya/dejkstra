#include <fstream>
#include <vector>
#include <limits>
#include <chrono>
#include <string>

using namespace std;

const int TESTS_NUMBER = 5;
const unsigned __int64 INF = numeric_limits<unsigned __int64>::max();

vector<vector<pair<int, int>>> scan(ifstream &in, const int &n, const int &m);

vector<unsigned __int64> dejkstra(const vector<vector<pair<int, int>>> &graph, const int &n, const int &start);

int main()
{
   for (int cnt = 0; cnt < TESTS_NUMBER; cnt++)
   {
      ifstream in("tests/graph" + to_string(cnt + 1) + ".txt");

      int n = 0, m = 0;
      in >> n >> m;

      vector<vector<pair<int, int>>> graph = scan(in, n, m);

      int start = 0;
      in >> start;

      in.close();

      auto t_start = chrono::high_resolution_clock().now();

      vector<unsigned __int64> res = dejkstra(graph, n, start);

      auto t_end = chrono::high_resolution_clock().now() - t_start;
      double elapsed_time = chrono::duration<double>(t_end).count();

      ofstream out("results/out" + to_string(cnt + 1) + ".txt");

      out << "Elapsed time: " << fixed << elapsed_time << " seconds" << endl;

      for (int i = 0; i < res.size(); i++)
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

vector<vector<pair<int, int>>> scan(ifstream &in, const int &n, const int &m)
{
   vector<vector<pair<int, int>>> graph(n);

   for (int i = 0; i < m; i++)
   {
      int u = 0, v = 0, w = 0;
      in >> u >> v >> w;

      graph[u - 1].push_back(make_pair(v - 1, w));
      graph[v - 1].push_back(make_pair(u - 1, w));
   }

   return graph;
}

vector<unsigned __int64> dejkstra(const vector<vector<pair<int, int>>> &graph, const int &n, const int &start)
{
   vector<unsigned __int64> d(n, INF);
   vector<bool> marks(n, false);

   d[start - 1] = 0;

   for (int i = 0; i < n; i++)
   {
      int t = -1;

      for (int j = 0; j < n; j++)
         if (!marks[j] && (t == -1 || d[j] < d[t]))
            t = j;

      if (d[t] == INF)
         break;

      marks[t] = true;

      for (int k = 0; k < graph[t].size(); k++)
      {
         int to = graph[t][k].first;
         int len = graph[t][k].second;

         if (d[t] + len < d[to])
            d[to] = d[t] + len;
      }
   }

   return d;
}
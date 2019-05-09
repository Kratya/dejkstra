#include <fstream>
#include <queue>
#include <vector>
#include <limits>
#include <chrono>
#include <string>

using namespace std;

const int TESTS_NUMBER = 5;
const unsigned __int64 INF = numeric_limits<unsigned __int64>::max();

vector<vector<int>> scan(ifstream &in, const int &n, const int &m);

vector<unsigned __int64> dejkstra_pq(const vector<vector<int>> graph, const int &n, const int &start);

int main()
{
   for (int cnt = 0; cnt < TESTS_NUMBER; cnt++)
   {
      ifstream in("tests/graph" + to_string(cnt + 1) + ".txt");

      int n = 0, m = 0;
      in >> n >> m;

      vector<vector<int>> graph = scan(in, n, m);

      int start = 0;
      in >> start;

      in.close();

      auto t_start = chrono::high_resolution_clock().now();

      vector<unsigned __int64> res = dejkstra_pq(graph, n, start);

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

vector<vector<int>> scan(ifstream &in, const int &n, const int &m)
{
   vector<vector<int>> graph(n, vector<int>(n));

   for (int i = 0; i < m; i++)
   {
      int u = 0, v = 0, w = 0;
      in >> u >> v >> w;

      graph[u - 1][v - 1] = graph[v - 1][u - 1] = w;
   }

   return graph;
}

vector<unsigned __int64> dejkstra_pq(const vector<vector<int>> graph, const int &n, const int &start)
{
   priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
   vector<unsigned __int64> res(n, INF);

   pq.push(make_pair(0, start - 1));
   res[start - 1] = 0;

   while (!pq.empty())
   {
      pair<int, int> s = pq.top();
      pq.pop();

      for (int i = 0; i < n; i++)
         if (graph[s.second][i] && res[i] > res[s.second] + graph[s.second][i])
         {
            res[i] = res[s.second] + graph[s.second][i];
            pq.push(make_pair(res[i], i));
         }
   }

   return res;
}
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

const int N_MAX = 1000;
const int MAX_WEIGHT = 1000;
const int TESTS_NUMBER = 5;

void generate(ofstream& out)
{
   int M = 0, N = rand() % N_MAX + 1, c = 0;

   vector<vector<int>> matrix(N);

   for (auto& x : matrix)
      x.resize(N);

   if (N == 1)
      M = 0;
   else
      M = rand() % (N * (N - 1) / 2) + 1;

   for (int i = 1; i < N; i++)
      for (int j = i; j < N; j++)
      {
         if (c < M)
            matrix[i][j] = rand() % 2 + 0;

         if (matrix[i][j] == 1)
            c++;
      }

   if (c < M)
      for (int i = 1; i < N; i++)
      {
         if (c == M)
            break;

         for (int j = i; j < N; j++)
         {
            if (c == M)
               break;

            if (matrix[i][j] == 0)
            {
               matrix[i][j] = 1;
               c++;
            }
         }
      }

   out << N << " " << M << endl;

   for (int i = 1; i < N; i++)
      for (int j = i; j < N; j++)
      {
         if (matrix[i][j] == 1)
            out << i << " ";

         if (matrix[i][j] == 1)
            out << j + 1 << " " << rand() % MAX_WEIGHT + 1 << endl;
      }

   out << rand() % N + 1 << endl;
}

int main()
{
   ofstream out;

   srand(time(NULL));

   for (int i = 0; i < TESTS_NUMBER; i++)
   {
      out.open("C:/Users/User/source/repos/dejkstra/generator/tests/graph" + to_string(i + 1) + ".txt");
      generate(out);
      out.close();
   }

   return 0;
}
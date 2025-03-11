#include <bits/stdc++.h>

using namespace std;

const int inf = INT_MAX;

vector<vector<int>> floyd_warshall(vector<vector<int>> adj_matrix,
                                   vector<vector<int>> &pi) {
  int n = adj_matrix.size();
  vector<vector<int>> prev_matrix = adj_matrix;
  vector<vector<int>> prev_pi = pi;

  for (int k = 0; k < n; k++) {
    vector<vector<int>> next_matrix(n, vector<int>(n, 0));
    vector<vector<int>> next_pi(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        next_matrix[i][j] = prev_matrix[i][j];
        next_pi[i][j] = prev_pi[i][j];

        // checking if k is an intermediate vertex on path from i -> j
        if (prev_matrix[i][k] < INT_MAX && prev_matrix[k][j] < INT_MAX) {
          if (next_matrix[i][j] > prev_matrix[i][k] + prev_matrix[k][j]) {
            next_matrix[i][j] = prev_matrix[i][k] + prev_matrix[k][j];
            next_pi[i][j] = prev_pi[k][j];
          }
        }
      }
    }
    prev_matrix = next_matrix;
    prev_pi = next_pi;
  }

  // updating the predecessors matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      pi[i][j] = prev_pi[i][j];
  }

  return prev_matrix;
}

int main() {
  int inf = INT_MAX;
  vector<vector<int>> adj_matrix = {{0, 3, 8, inf, -4},
                                    {inf, 0, inf, 1, 7},
                                    {inf, 4, 0, inf, inf},
                                    {2, inf, -5, 0, inf},
                                    {inf, inf, inf, 6, 0}};
  int n = adj_matrix.size();

  vector<vector<int>> prev(n, vector<int>(n, -1));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (adj_matrix[i][j] != INT_MAX)
        prev[i][j] = i;
    }
  }

  vector<vector<int>> shortest_path_matrix = floyd_warshall(adj_matrix, prev);

  cout << "ALL PAIR SHORTEST MATRIX" << endl;
  for (auto row : shortest_path_matrix) {
    for (auto col : row)
      cout << col << " ";
    cout << endl;
  }
  cout << "SHORTEST SUBGRAPH MATRIX" << endl;
  for (auto row : prev) {
    for (auto col : row)
      cout << col << " ";
    cout << endl;
  }
}
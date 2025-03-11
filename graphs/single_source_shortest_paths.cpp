// again djikstra is a greedy algorithm. so try to prove it
#include <bits/stdc++.h>


using namespace std;

// proof for this done by looking at the loop invariant
// this is the implmenetation of the flow give in the text book
// but in this we won't get the path
vector<int> dijkstra(int n, vector<vector<int>> edges) {
  vector<int> distance(
      n, -1); // used to store whether the vertex's min distance is calculated

  // x -> w, y
  unordered_map<int, vector<pair<int, int>>> adj_list;
  for (auto edge : edges) {
    adj_list[edge[0]].push_back({edge[2], edge[1]});
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push({0, 0});

  while (!pq.empty()) {
    int d = pq.top().first, node = pq.top().second;
    pq.pop();

    // check if node was visited
    if (distance[node] != -1)
      continue;
    distance[node] = d;

    // relaxation step
    for (auto adj_node : adj_list[node]) {
      pq.push({d + adj_node.first, adj_node.second});
    }
  }

  return distance;
}

// another way to implement the algorith
// we need to return the path here
vector<int> dijkstraPath(int n, vector<vector<int>> edges, int source,
                         int destination) {
  vector<int> d(n, INT_MAX);
  vector<int> prev(n, 0);

  for (int i = 0; i < n; i++)
    prev[i] = i;

  unordered_map<int, vector<pair<int, int>>> adj_list;

  for (auto edge : edges) {
    adj_list[edge[0]].push_back({edge[2], edge[1]});
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

  pq.push({0, source});
  d[source] = 0;

  while (!pq.empty()) {
    int currDist = pq.top().first;
    int node = pq.top().second;
    pq.pop();

    for (auto it : adj_list[node]) {
      int edgeWeight = it.first, nextNode = it.second;
      if (d[nextNode] > currDist + edgeWeight) {
        prev[nextNode] = node;
        d[nextNode] = currDist + edgeWeight;
        pq.push({d[nextNode], nextNode});
      }
    }
  }

  if (d[destination] == INT_MAX)
    return {-1};

  vector<int> path;
  int node = destination;
  while (prev[node] != node) {
    path.push_back(node);
    node = prev[node];
  }
  path.push_back(source);
  reverse(path.begin(), path.end());

  return path;
}

#include <bits/stdc++.h>

using namespace std;

// the more important part of this algorithm is it's proof
// why the distances at the end are minimum? - using path relaxation property
// (look at proof) why if the given condition below fails it means there is
// negative cycle. why if will return true in case of no negative cycle why if
// will return false in case of negative cycle
vector<int> bellman_ford(int V, vector<vector<int>> edges) {
  unordered_map<int, vector<pair<int, int>>> adj_list;
  for (auto edge : edges)
    adj_list[edge[0]].push_back({edge[2], edge[1]});

  vector<int> distance(V, INT_MAX);
  distance[0] = 0;
  for (int i = 0; i < V - 1; i++) {
    for (auto edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      if (distance[u] != INT_MAX && distance[u] + w <= distance[v]) {
        distance[v] = distance[u] + w;
      }
    }
  }

  for (auto edge : edges) {
    int u = edge[0], v = edge[1], w = edge[2];
    if (distance[v] > distance[u] + w)
      return {};
  }

  return distance;
}

int main() {
  int n = 5;
  vector<vector<int>> edges = {{0, 1, 10}, {0, 4, 5}, {1, 2, 1}, {1, 4, 2},
                               {2, 3, 4},  {3, 2, 6}, {3, 0, 7}, {4, 1, 3},
                               {4, 2, 9},  {4, 3, 2}};

  vector<int> distance = dijkstra(n, edges);
  vector<int> path = dijkstraPath(n, edges, 0, 2);

  for (int i = 0; i < n; i++) {
    cout << "{" << i << ", " << distance[i] << "} ";
  }
  cout << endl;

  for (auto node : path)
    cout << node << " -> ";
  cout << endl;
}
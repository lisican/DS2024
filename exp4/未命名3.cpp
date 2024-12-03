#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <utility>
using namespace std;

struct GraphNode {
    int vertex;
    int weight;  
    GraphNode(int v, int w) : vertex(v), weight(w) {}
};

class GraphAdjList {
private:
    int numVertices;
    vector<list<GraphNode> > adjList;

public:
    GraphAdjList(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back(GraphNode(dest, weight));
        adjList[dest].push_back(GraphNode(src, weight));
    }

    vector<int> dijkstra(int startVertex) {
        vector<int> dist(numVertices, numeric_limits<int>::max()); 
        vector<bool> visited(numVertices, false);  

        dist[startVertex] = 0;  

        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push(make_pair(0, startVertex));

        while (!pq.empty()) {
            int u = pq.top().second;  
            pq.pop();

            if (visited[u]) continue;  
            visited[u] = true;

            list<GraphNode>::iterator it;
            for (it = adjList[u].begin(); it!= adjList[u].end(); ++it) {
                int v = (*it).vertex;
                int weight_uv = (*it).weight;
                if (!visited[v] && dist[u] + weight_uv < dist[v]) {
                    dist[v] = dist[u] + weight_uv;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return dist;
    }

    int prim() {
        vector<int> key(numVertices, numeric_limits<int>::max()); 
        vector<bool> inMST(numVertices, false); 

        key[0] = 0;  

        int mstWeight = 0;  

        for (int count = 0; count < numVertices - 1; ++count) {
            int minKey = numeric_limits<int>::max();
            int minIndex = -1;

            for (int v = 0; v < numVertices; ++v) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }

            if (minIndex == -1) break;

            inMST[minIndex] = true;
            mstWeight += minKey;

            list<GraphNode>::iterator it;
            for (it = adjList[minIndex].begin(); it!= adjList[minIndex].end(); ++it) {
                int v = (*it).vertex;
                int weight = (*it).weight;
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                }
            }
        }

        return mstWeight;
    }
};

void testDijkstra() {
    GraphAdjList graph(6); 

    graph.addEdge(0, 1, 7);
    graph.addEdge(0, 2, 9);
    graph.addEdge(0, 5, 14);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 11);
    graph.addEdge(2, 5, 2);
    graph.addEdge(3, 4, 6);
    graph.addEdge(4, 5, 9);

    vector<int> shortestDistances = graph.dijkstra(0);
    cout << "Shortest distances from vertex 0: ";
    for (int i = 0; i < shortestDistances.size(); ++i) {
        if (shortestDistances[i] == numeric_limits<int>::max()) {
            cout << "INF ";
        } else {
            cout << shortestDistances[i] << " ";
        }
    }
    cout << endl;
}

void testPrim() {
    GraphAdjList graph(6);  

    graph.addEdge(0, 1, 7);
    graph.addEdge(0, 2, 9);
    graph.addEdge(0, 5, 14);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 11);
    graph.addEdge(2, 5, 2);
    graph.addEdge(3, 4, 6);
    graph.addEdge(4, 5, 9);

    int mstWeight = graph.prim();
    cout << "Weight of the minimum spanning tree: " << mstWeight << endl;
}

int main() {
    testDijkstra();
    testPrim();
    return 0;
}

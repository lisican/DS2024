#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

struct GraphNode {
    int vertex;
    GraphNode(int v) : vertex(v) {}
};

class GraphAdjList {
private:
    int numVertices;
    vector<list<GraphNode> > adjList;

public:
    GraphAdjList(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(GraphNode(dest));
        adjList[dest].push_back(GraphNode(src));
    }

    void BFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";

            list<GraphNode>::iterator it;
            for (it = adjList[currentVertex].begin(); it!= adjList[currentVertex].end(); ++it) {
                if (!visited[(*it).vertex]) {
                    visited[(*it).vertex] = true;
                    q.push((*it).vertex);
                }
            }
        }
        cout << endl;
    }

    void DFSUtil(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        list<GraphNode>::iterator it;
        for (it = adjList[vertex].begin(); it!= adjList[vertex].end(); ++it) {
            if (!visited[(*it).vertex]) {
                DFSUtil((*it).vertex, visited);
            }
        }
    }

    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        DFSUtil(startVertex, visited);
        cout << endl;
    }
};

void testBFS() {
    GraphAdjList graph(7); 
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);

    cout << "BFS starting from vertex 0: ";
    graph.BFS(0);
}

void testDFS() {
    GraphAdjList graph(7); 
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);

    cout << "DFS starting from vertex 0: ";
    graph.DFS(0);
}

int main() {
    testBFS();
    testDFS();
    return 0;
}

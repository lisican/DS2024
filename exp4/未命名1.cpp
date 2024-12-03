#include <iostream>
#include <vector>
using namespace std;

class GraphAdjMatrix {
private:
    int numVertices;  
    vector<vector<int> > adjMatrix;  

public:

    GraphAdjMatrix(int vertices) : numVertices(vertices) {
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addEdge(int src, int dest) {

        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1;
    }

    void printGraph() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    GraphAdjMatrix graph(5); 
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);

    graph.printGraph();
    return 0;
}

#include <iostream>

using namespace std;

class Graph;

class Edge {
friend class Graph;
private:
    int latency;
    int bandwidth;
};

class Graph {
public:
    Graph(int v);
    void inputLatency();
    void insertEdge(int u, int v, int latency);
    void result();
private:
    int n;
    bool* s;
    int* vertexLatency;
    int* dist;
    int* bandwidth;
    int** adjacentMatrix;
    int minDist();
    int maxDist();
    void minLatency(int v);
    void maxBandwidth(int v);
};

int main()
{
    int n;
    int e;
    cin >> n;

    Graph* network = new Graph(n);

    network->inputLatency();

    cin >> e;

    int u;
    int v;
    int latency;
    int bandwidth;
    for(int i = 0; i < e; i++) {
        cin >> u;
        cin >> v;
        cin >> latency;
        network->insertEdge(u, v, latency);
    }

    network->result();
    return 0;
}

Graph::Graph(int v){
    n = v;
    s = new bool[n];
    vertexLatency = new int[n];
    dist = new int[n];
    bandwidth = new int[n];

    adjacentMatrix = new int*[n];
    for(int i = 0; i < n; i++)
    {
        adjacentMatrix[i] = new int[n];
        for(int j = 0; j < n; j++) {
            adjacentMatrix[i][j] = 0;
        }
    }
}

void Graph::inputLatency() {
    for(int i = 0; i < n; i++) {
	cin >> vertexLatency[i];
    }
    return;
}

void Graph::insertEdge(int u, int v, int latency) {
    adjacentMatrix[u][v] = latency;
    return;
}

void Graph::result() {
    minLatency(0);

    for(int i = 1; i < n; i++) {
        cout << i << " ";
        if(dist[i] != 0)
            cout << dist[i] << " "  << endl;
        else
            cout << "inf" << " " << endl;;
    }

    return;
}

int Graph::minDist() {
    int min = 0;
    int minVertex;
    for(int i = 0; i < n; i++) {
        if(dist[i] != 0 && !s[i])
        {
            if(min == 0) {
                min = dist[i];
                minVertex = i;
            }
            if(min > dist[i]) {
                min = dist[i];
                minVertex = i;
            }
        }
    }

    return minVertex;
}

int Graph::maxDist() {
    int max = 0;
    int maxVertex;
    for(int i = 0; i < n; i++) {
        if(max < bandwidth[i] && !s[i]) {
            max = bandwidth[i];
            maxVertex = i;
        }
    }

    return maxVertex;
}

void Graph::minLatency(int v) {
    for(int i = 0; i < n; i++) {
        s[i] = false;
	if(adjacentMatrix[v][i] != 0)
            dist[i] = vertexLatency[0] + adjacentMatrix[v][i] + vertexLatency[i];
	else
	    dist[i] = 0;
    }

    s[v] = true;

    int u;
    for(int i = 0; i < n-1; i++) {
        u = minDist();
        s[u] = true;
        for(int w = 0; w < n; w++) {
            if(!s[w]
               && ( (dist[u] + adjacentMatrix[u][w] + vertexLatency[w]) < dist[w] || dist[w] == 0)
               && adjacentMatrix[u][w] != 0 )
            {
                dist[w] = dist[u] + adjacentMatrix[u][w] + vertexLatency[w];
            }
        }
    }

    return;
}

/*
void Graph::maxBandwidth(int v) {
    for(int i = 0; i < n; i++) {
        s[i] = false;
        bandwidth[i] = adjacentMatrix[v][i].bandwidth;
    }

    s[v] = true;

    int u;
    int path;
    for(int i = 0; i < n-1; i++) {
        u = maxDist();
        s[u] = true;
        for(int w = 0; w < n; w++) {
            if(!s[w] && adjacentMatrix[u][w].bandwidth != 0) {
                if(adjacentMatrix[u][w].bandwidth < bandwidth[u])
                    path = adjacentMatrix[u][w].bandwidth;
                else
                    path = bandwidth[u];

                if(path > bandwidth[w])
                    bandwidth[w] = path;
            }
        }
    }

    return;
}
*/


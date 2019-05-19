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
    void insertEdge(int u, int v, int latency, int bandwidth);
    void result();
private:
    int n;
    bool* s;
    int* dist;
    int* bandwidth;
    Edge** adjacentMatrix;
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
    cin >> e;

    Graph* network = new Graph(n);

    int u;
    int v;
    int latency;
    int bandwidth;
    for(int i = 0; i < e; i++) {
        cin >> u;
        cin >> v;
        cin >> latency;
        cin >> bandwidth;
        network->insertEdge(u, v, latency, bandwidth);
    }

    network->result();
    return 0;
}

Graph::Graph(int v){
    n = v;
    s = new bool[n];
    dist = new int[n];
    bandwidth = new int[n];

    adjacentMatrix = new Edge*[n];
    for(int i = 0; i < n; i++)
    {
        adjacentMatrix[i] = new Edge[n];
        for(int j = 0; j < n; j++) {
            adjacentMatrix[i][j].latency = 0;
            adjacentMatrix[i][j].bandwidth = 0;
        }
    }
}

void Graph::insertEdge(int u, int v, int latency, int bandwidth) {
    adjacentMatrix[u][v].latency = latency;
    adjacentMatrix[u][v].bandwidth = bandwidth;
    return;
}

void Graph::result() {
    minLatency(0);
    maxBandwidth(0);

    for(int i = 1; i < n; i++) {
        cout << i << " ";
        if(dist[i] != 0)
            cout << dist[i] << " " << bandwidth[i] << endl;
        else
            cout << "inf" << " " << bandwidth[i] << endl;;
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
        dist[i] = adjacentMatrix[v][i].latency;
    }

    s[v] = true;

    int u;
    for(int i = 0; i < n-1; i++) {
        u = minDist();
        s[u] = true;
        for(int w = 0; w < n; w++) {
            if(!s[w]
               && ( (dist[u] + adjacentMatrix[u][w].latency) < dist[w] || dist[w] == 0)
               && adjacentMatrix[u][w].latency != 0 )
            {
                dist[w] = dist[u] + adjacentMatrix[u][w].latency;
            }
        }
    }

    return;
}

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

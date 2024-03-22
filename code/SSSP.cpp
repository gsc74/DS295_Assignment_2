#include<iostream>
#include<queue>
#include<vector>
#include<climits>
#include<fstream>

// Reads adjacency list from graph.mtx file
void readGraph(std::vector<std::vector<std::pair<int, int>>> &adjList, int &n, int &m) {
    std::cerr << " Start reading graph" << std::endl;
    std::ifstream file("../input/test_graph.mtx");
    if (!file) {
        std::cerr << "File not found\n";
        exit(1);
    }
    std::cerr << " Finished reading graph" << std::endl;
    // if line starts with % skip it
    while (file.peek() == '%') {
        file.ignore(INT_MAX, '\n');
    }
    std::cerr << " Start filling adjList" << std::endl;
    int e;
    file >> n >> m >> e;
    std::cerr << " Vertices : " << n << " Edges : " << e << std::endl;
    adjList.resize(n);
    for (int i = 0; i < n; i++) {
        int u, v, w;
        file >> u >> v >> w;
        u = u - 1;
        v = v - 1;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w}); // symmetric graph
    }
    std::cerr << " Finished filling adjList" << std::endl;
    file.close();
}


// Dijkstra's algorithm for SSSP
void dijkstra(std::vector<std::vector<std::pair<int, int>>> &adjList, int n, int src) {
    std::vector<int> dist(n, INT_MAX);
    std::vector<bool> visited(n, false);
    std::vector<std::vector<int>> shortestPath(n);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
    // push the source vertex into the shortest path
    shortestPath[src].push_back(src);
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (auto &i : adjList[u]) {
            int v = i.first;
            int w = i.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                shortestPath[v] = shortestPath[u];
                shortestPath[v].push_back(v);
            }
        }
    }
    std::string filename = "../output/output_" + std::to_string(src + 1) + ".bin";
    std::ofstream file(filename, std::ios::binary);
    std::vector<std::vector<int>> list_vtx(n);
    for (int i = 0; i < n; i++) {
        list_vtx[i].push_back(dist[i]);
        // std::cerr << " cost : " << dist[i] << " path size : ";
        list_vtx[i].push_back(shortestPath[i].size());
        // std::cerr << shortestPath[i].size() << " path : ";
        for (int j = 0; j < shortestPath[i].size(); j++) {
            list_vtx[i].push_back(shortestPath[i][j] + 1);
            // std::cerr << shortestPath[i][j] + 1 << " "<< std::endl;
        }
    }
    file.write((char *)list_vtx.data(), list_vtx.size() * sizeof(list_vtx[0]));
    file.close();
}

int main(int argc, char *argv[]) {
    int n, m;
    int src = atoi(argv[1]);
    std::cerr << "src : " << src << std::endl;
    // correction src = src - 1
    src = src - 1;
    if (src == -1)
    {
        std::cerr << " Start reading graph" << std::endl;
        std::vector<std::vector<std::pair<int, int>>> adjList;
        readGraph(adjList, n, m);
        std::cerr << " Finished reading graph" << std::endl;
        std::cerr << " Vertices : " << n << " Edge : " << m << " source : " << src << std::endl;
        std::string filename = "../output/output_" + std::to_string(0) + ".bin";
        std::ofstream file(filename, std::ios::binary);
        for (int i = 0; i < n; i++) {
            file << -1 << "0" << std::endl;
        }
        file.close();
    }else
    {
        std::vector<std::vector<std::pair<int, int>>> adjList;
        readGraph(adjList, n, m);
        dijkstra(adjList, n, src);
    }
    
    
    return 0;
}
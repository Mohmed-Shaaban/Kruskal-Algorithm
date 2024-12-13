#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge in the graph
struct Edge
{
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset
{
    int parent;
    int rank;
};

// Comparator function to sort edges by weight
bool compareEdges(Edge a, Edge b)
{
    return a.weight < b.weight;
}

// Function to find the parent of a node (with path compression)
int find(Subset subsets[], int node)
{
    if (subsets[node].parent != node)
        subsets[node].parent = find(subsets, subsets[node].parent);
    return subsets[node].parent;
}

// Function to perform union of two subsets
void Union(Subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to implement Kruskal's Algorithm
void kruskalMST(vector<Edge>& edges, int V)
{
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Allocate memory for subsets
    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<Edge> result; // To store the resultant MST

    for (Edge edge : edges)
    {
        int x = find(subsets, edge.src);
        int y = find(subsets, edge.dest);

        // If including this edge doesn't form a cycle
        if (x != y)
        {
            result.push_back(edge);
            Union(subsets, x, y);
        }

        // Stop if MST has (V-1) edges
        if (result.size() == V - 1)
            break;
    }

    // Display the resulting MST
    cout << "Edges in the MST:\n";
    int totalWeight = 0;
    for (Edge e : result)
    {
        cout << e.src << " -- " << e.dest << " == " << e.weight << endl;
        totalWeight += e.weight;
    }
    cout << "Total weight of MST: " << totalWeight << endl;

    delete[] subsets;
}

int main()
{
    int V = 4;
    vector<Edge> edges =
    {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };

    kruskalMST(edges, V);

    return 0;
}

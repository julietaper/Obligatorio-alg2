#include "iostream"
using namespace std;

struct Node
{
    int data;
    Node *next;
};

struct Queue
{
private:
    Node *first;
    Node *last;

public:
    Queue()
    {
        first = NULL;
        last = NULL;
    }

    void enqueue(int data)
    {
        Node *node = new Node;
        node->data = data;
        node->next = NULL;

        if (first == NULL)
        {
            first = node;
        }
        else
        {
            last->next = node;
        }
        last = node;
    }

    int firstElem()
    {
        return first->data;
    };

    void dequeue()
    {
        Node *toDelete = first;
        first = first->next;
        delete toDelete;
    }

    bool isEmpty()
    {
        return first == NULL;
    }
};

class Edge
{
public:
    int to;
    int weight;
    Edge *next;
};

class Graph
{
private:
    struct Node
    {
        int vertex;
        int edgesCount;
        Edge *edges;
    };
    Node **vec;
    int tope;
    int cant;

public:
    Graph(int tope)
    {
        this->tope = tope + 1;
        this->cant = 0;

        this->vec = new Node *[tope];
        for (int i = 0; i < tope; i++)
        {
            this->vec[i] = NULL;
        }
    }
    void addVertex(int vertex)
    {
        Node *node = new Node;
        node->vertex = vertex;
        node->edges = NULL;
        this->vec[vertex - 1] = node;

        cant++;
    }

    void addEdge(int from, int to, int weigth)
    {
        Node *node = this->vec[from - 1];

        Edge *edge = new Edge;
        edge->to = to;
        edge->weight = weigth;
        edge->next = node->edges;

        node->edges = edge;
        node->edgesCount++;
    }

    Edge *getAdjacents(int vertex)
    {
        return this->vec[vertex - 1]->edges;
    }

    int getAdjacentsCount(int vertex)
    {
        return this->vec[vertex - 1]->edgesCount;
    }

    int dijkstra(int origin, int end)
    {
        int *dist = new int[tope];
        for (int i = 0; i < tope; i++)
        {
            dist[i] = 999999;
        }

        dist[origin] = 0;

        Queue *queue = new Queue();
        queue->enqueue(origin);
        while (!queue->isEmpty())
        {
            int pos = queue->firstElem();
            queue->dequeue();

            Edge *edges = getAdjacents(pos);
            int edgesCount = getAdjacentsCount(pos);

            while (edges != NULL)
            {
                int to = edges->to;
                int weight = edges->weight;

                if (dist[to] > dist[pos] + weight)
                {
                    dist[to] = dist[pos] + weight;
                    queue->enqueue(to);
                }
                edges = edges->next;
            }
        }
        int distance = dist[end] != 999999 ? dist[end] : -1;

        delete[] dist;
        return distance;
    }
};

int main()
{

    int v;
    cin >> v;

    int e;
    cin >> e;

    Graph *g = new Graph(v);

    for (int i = 1; i <= v; i++)
    {
        g->addVertex(i);
    }
    for (int i = 0; i < e; i++)
    {
        int from, to, weigth;
        cin >> from;
        cin >> to;
        cin >> weigth;

        g->addEdge(from, to, weigth);
    }
    int dijk;
    cin >> dijk;
    for (int i = 0; i < dijk; i++)
    {
        int count = 0;
        int fromDijk;
        cin >> fromDijk;
        for (int j = 1; j <= v; j++)
        {
            if (fromDijk == j)
            {
                cout << -1 << endl;
            }
            else
            {
                cout << g->dijkstra(fromDijk, j) << endl;
            }
        }
    }

    return 0;
};
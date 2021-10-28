#include "iostream"
#define INF 999999
using namespace std;

class Edge
{
public:
    int cost;
    bool exists;

    Edge() : cost(0), exists(false) {}
    Edge(int cost) : cost(cost), exists(true) {}
};

class Grafo
{

private:
    Edge ***mat;
    int length;
    int cant;
    int **vertices;

    int posVertex(int v)
    {
        for (int i = 0; i < length; i++)
        {
            if (vertices[i] && *(vertices[i]) == v)
            {
                return i;
            }
        }
        return -1;
    }

    int verticeNoVisDeMenorDist(int *dist, bool *vis)
    {
        int posMin = -1, min = INF;
        for (int i = 0; i < length; i++)
        {
            if (!vis[i] && dist[i] < min)
            {
                min = dist[i];
                posMin = i;
            }
        }
        return posMin;
    }

public:
    Grafo(int length)
    {
        this->length = length;
        this->cant = 0;

        this->vertices = new int *[length];
        for (int i = 0; i < length; this->vertices[i++] = NULL)
            ;

        this->mat = new Edge **[length];

        for (int i = 0; i < length; i++)
        {
            this->mat[i] = new Edge *[length];
        }
        for (int i = 0; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                this->mat[i][j] = this->mat[j][i] = new Edge();
            }
        }
    }

    ~Grafo()
    {
        for (int i = 0; i < length; i++)
        {
            delete vertices[i];
        }
        delete[] vertices;

        for (int i = 0; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                delete mat[i][j];
            }

            delete[] mat[i];
        }
        delete[] mat;
    }

    void insertarVertice(int v)
    {
        int pos = -1;
        for (int i = 0; i < length; i++)
        {
            if (!vertices[i])
            {
                pos = i;
                break;
            }
        }
        vertices[pos] = new int(v);
        cant++;
    }

    // Pre: existsVertice(vOri) && existsVertice(vDes)
    void insertarEdge(int vOri, int vDes, int cost)
    {
        int posOri = posVertex(vOri);
        int posDes = posVertex(vDes);
        mat[posOri][posDes]->cost = cost;
        mat[posOri][posDes]->exists = true;
    }

    // Pre: existsVertice(vOri) && existsVertice(vDes)
    void borrarEdge(int vOri, int vDes)
    {
        int posOri = posVertex(vOri);
        int posDes = posVertex(vDes);
        mat[posOri][posDes]->exists = false;
    }

    bool existsVertice(int v)
    {
        return posVertex(v) != -1;
    }

    int prim(bool cubrirTodasLasComponentes)
    {
        int pos = -1;
        for (int i = 0; i < length; i++)
        {
            if (vertices[i])
            {
                pos = i;
                break;
            }
        }

        bool *vis = new bool[length];
        for (int i = 0; i < length; vis[i++] = false)
            ;

        vis[pos] = true;

        int totalCount = 0;
        for (int k = 0; k < cant; k++)
        {
            int posI = -1, posJ = -1, minimo = INF;
            for (int i = 0; i < length; i++)
            {
                if (vis[i])
                {
                    for (int j = 0; j < length; j++)
                    {
                        if (!vis[j] && vertices[j] && mat[i][j]->exists && mat[i][j]->cost < minimo)
                        {
                            posI = i;
                            posJ = j;
                            minimo = mat[i][j]->cost;
                        }
                    }
                }
            }
            if (k + 1 == cant)
            {
                return totalCount;
            }
            else
            {
                totalCount += minimo;
                vis[posJ] = true;
            }
            if (posI == -1)
            {
                return -1;
            }
        }
        delete[] vis;
        return totalCount;
    }
};

int main()
{
    int vertices, edges;
    cin >> vertices;
    cin >> edges;
    Grafo *graph = new Grafo(vertices);

    for (int i = 1; i <= vertices; i++)
    {
        graph->insertarVertice(i);
    }
    int from;
    int to;
    int cost;
    for (int i = 0; i < edges; i++)
    {
        cin >> from;
        cin >> to;
        cin >> cost;
        graph->insertarEdge(from, to, cost);
    }
    cout << graph->prim(true) << endl;
    return 0;
}
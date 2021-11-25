#include "iostream"
#define INF 999999
using namespace std;


class stack
{
    private:
        int *array;
        int tope;
        int cota;

    public:
        stack(int cota)
        {
            this->tope = 0;
            this->array = new int[cota];
            this->cota = cota;
        }

        void push(int i)
        {
            if (!full())
            {
                this->array[this->tope] = i;
                this->tope++;
            }
        }

        int top()
        {
            if(this->tope > 0)
                return this->array[this->tope - 1];
            
            return -1;
        }

        void pop()
        {
            if(this->tope > 0)
                this->tope--;
        }

        bool empty()
        {
            return (this->tope == 0);
        }

        bool full()
        {
            return (this->tope == this->cota);
        }

        ~stack()
        {
            delete[] this->array;
        }
};

class Edge
{
public:
    bool exist;
    int origin;
    int final;

    Edge() : exist(false) {}
    Edge(int origin, int final) : exist(true), origin(origin), final(final) {}
};

class Graph
{

private:
    Edge ***mat;
    int tope;
    int cant;
    int **vertices;

    int getHole()
    {
        for (int i = 0; i < tope; i++)
        {
            if (!vertices[i])
            {
                return i;
            }
        }
        return -1;
    }

    int posVertex(int v)
    {
        for (int i = 0; i <tope; i++)
        {
            if (vertices[i] && *(vertices[i]) == v)
            {
                return i;
            }
        }
        return -1;
    }


public:
    Graph(int tope)
    {
        this->tope = tope;
        this->cant = 0;

        this->vertices = new int *[tope];
        for (int i = 0; i < tope; this->vertices[i++] = NULL)
            ;

        this->mat = new Edge **[tope];

        for (int i = 0; i < tope; i++)
        {
            this->mat[i] = new Edge *[tope];
        }
        for (int i = 0; i < tope; i++)
        {
            for (int j = i; j < tope; j++)
            {
            this->mat[i][j] = this->mat[j][i] = new Edge();
            }
        }
    }

    void addVertex(int v)
    {
        int pos = getHole();
        vertices[pos] = new int(v);
        cant++;
    }


    void addEdge(int vOri, int vDes)
    {
        int posOri = posVertex(vOri);
        int posDes = posVertex(vDes);
        mat[posOri][posDes]->exist = true;
    }

    int ConnectedComponents(Graph* graph){
        
        bool* visited = new bool[tope+1];
        for(int i=0; i<tope; i++)
            visited[i] = false;

        int componentCount = 1;

        stack s = stack(tope);
        s.push(0);

        while(!s.empty()){

            while(!s.empty()){
                int current = s.top();
                s.pop();

                visited[current] = true;
                for(int i=0; i<tope; i++){
                    if(mat[current][i]->exist && !visited[i]){
                        s.push(i);
                    }
                }
            }

            for(int i = 0; i < tope; i++){
                if(!visited[i]){
                    s.push(i);
                    componentCount++;
                    break;
                }
                
            }
        }
        return componentCount;
    }
};

int main()
{

    int vertices, edges;
    cin >> vertices;
    cin >> edges;
    Graph *graph = new Graph(vertices);

    for (int i = 1; i <=vertices; i++)
    {
        graph->addVertex(i);
    }
    int from;
    int to;
    for (int i = 1; i <= edges; i++)
    {
        cin >> from;
        cin >> to;
        graph->addEdge(from, to);
    }
    cout << graph->ConnectedComponents(graph) << endl;
    return 0;

}
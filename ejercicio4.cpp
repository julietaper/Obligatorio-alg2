#include <iostream>
using namespace std;

    struct NodeList
    {
        int dato;
        NodeList *next;
        NodeList(int c) : dato(c), next(NULL){};
    };


class Graph{
  public:
      Graph(int v) {
        this->v = v;
        this->adyList = new NodeList*[v];
        for (int i = 0; i < v; i++)
        {
            adyList[1] = NULL;
        }
      }


    void agregarAdy(int nodo1, int nodo2){
        insertFirst(this->adyList[nodo1], nodo2);
    }

      void insertFirst(NodeList *&l, int dato)
      {
          if (l == NULL)
          {
              l = new NodeList(dato);
          }
          else
          {
              NodeList *aux = l;
              l = new NodeList(dato);
              l->next = aux;
          }
      }

      void deleteFirst(NodeList *&l)
      {
          NodeList *aux = l;
          l = l->next;
          delete aux;
      }

      bool hasCycle(int * entryGrade)
      {
        int visited = 0;
        NodeList *solitary = NULL;

        for (int i = 1; i <= v; i++)
        {
            if (entryGrade[i] == 0)
            {
                insertFirst(solitary, i);
            }
        }

        while (solitary != NULL)
        {
            int dato = solitary->dato;
            deleteFirst(solitary);
            visited++;

            while (adyList[dato] != NULL)
            {
                int data = adyList[dato]->dato;
                entryGrade[data]--;
                if (entryGrade[data] == 0)
                {
                    insertFirst(solitary, data);
                }
                adyList[dato] = adyList[dato]->next;
            }
        }
        if (visited == v)
            return false;
        else
            return true;
      }

  private:
    int v;
    NodeList **adyList;
};



int main()
{
    int v;
    cin >> v;

    int e;
    cin >> e;

    Graph *g = new Graph(v);

    int* entryGrade = new int[v + 1];
    for(int i=0; i<=v; i++)
    {
        entryGrade[i] = 0;
    }
    for (int i = 0; i < e; i++)
    {
        int origin;
        cin >> origin;
        int final;
        cin >> final;
        g->agregarAdy(origin, final);
        entryGrade[final]++;
    }

    if (g->hasCycle(entryGrade))
    {
        cout << "1" << endl;
    }
    else
    {
        cout << "0" << endl;
    }

    delete[] entryGrade;
    delete g;
}
#include <iostream>
#include <fstream>
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

class Heap
{
public:
    Heap(int expectedElements)
    {
        size = expectedElements + 1;
        count = 0;
        heap = new HeapNode *[size];
        allElements = 0;
        for (int i = 0; i < size; i++)
        {
            heap[i] = NULL;
        }
    }
    void insert(Queue *list, int listElements)
    {
        count += 1;
        int hole = count;

        heap[hole] = new HeapNode();
        heap[hole]->list = list;
        heap[hole]->elements = listElements;

        allElements = allElements + listElements;

        percolateUp(hole);
    }
    int min()
    {
        return heap[1]->list->firstElem();
    }
    void deleteMin()
    {
        int hole = 1;
        if (heap[hole]->elements == 1)
        {
            Queue *toDelete = heap[hole]->list;
            delete toDelete;

            heap[hole]->list = heap[count]->list;
            heap[hole]->elements = heap[count]->elements;

            HeapNode *heapNode = heap[count];
            delete heapNode;
            heap[count] = NULL;
            count--;
        }
        else
        {
            heap[hole]->list->dequeue();
            heap[hole]->elements--;
        }
        allElements--;

        percolateDown(hole);
    }
    bool elements()
    {
        return this->allElements > 0;
    }

private:
    struct HeapNode
    {
        Queue *list;
        int elements;
    };
    HeapNode **heap;
    int count;
    int size;
    int allElements;
    void percolateUp(int hole)
    {
        while (hole > 1 && heap[hole]->list->firstElem() < heap[hole / 2]->list->firstElem())
        {
            swap(heap[hole], heap[hole / 2]);
            hole /= 2;
        }
    }
    void percolateDown(int hole)
    {
        while (hole * 2 <= count)
        {
            unsigned int child = hole * 2;
            if (child + 1 <= count && heap[child + 1]->list->firstElem() < heap[child]->list->firstElem())
                child++;

            if (heap[child]->list->firstElem() < heap[hole]->list->firstElem())
            {
                swap(heap[child], heap[hole]);
                hole = child;
            }
            else
                break;
        }
    }
};
int main()
{
    int lists;
    cin >> lists;
    Heap *heap = new Heap(lists);
    int listElements;

    for (int i = 0; i < lists; i++)
    {
        cin >> listElements;
        int element;
        Queue *list = new Queue();

        for (int i = 0; i < listElements; i++)
        {
            cin >> element;
            list->enqueue(element);
        }
        heap->insert(list, listElements);
    }
    while (heap->elements())
    {
        cout << heap->min() << endl;
        heap->deleteMin();
    }
}

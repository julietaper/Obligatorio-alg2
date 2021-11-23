#include <iostream>
using namespace std;

struct Triplet{
    int posI;
    int posF;
    int height;

    Triplet(int posi, int posf, int height) : posI(posi) , posF (posf), height(height) {};
};
struct Doble{
    int pos;
    int height;
    Doble* next;
};
int max(int a , int b){
    return (a > b) ? a : b;
};
    int available = 0;

    void addFigure(int pos1, int pos2, int pos3, Triplet** t1){
        Triplet* triplet = new Triplet(pos1,pos2,pos3);
        t1[available] = triplet;
        available++;
    }

    void addLast(Doble*& d, int a, int b){
        if(d == NULL){
            Doble* doble = new Doble;
            doble->pos = a;
            doble->height = b;
            d = doble;
        }
        Doble* aux = d;
        while(aux->next != NULL){
            aux = aux->next;
        }
        Doble* newDoble = new Doble;
        newDoble->pos = a;
        newDoble->height = b;
        newDoble->next = NULL;  
        aux->next = newDoble;
    }


    Doble* merge(Doble* d1, Doble* d2){
        Doble* doble = NULL;
        int height1 = 0;
        int height2 = 0;
        int used = -1;

        while(d1 != NULL && d2 != NULL){
            if(d1->pos < d2->pos){
                height1 = d1->height;
                if(max(height1,height2) != used){
                    used = max(height1,height2);
                    addLast(doble, d1->pos,max(height1,height2));
                }
                d1 = d1->next;
            }   
        
            else if(d1->pos > d2->pos){
                height2 = d2->height;
                if(max(height1,height2) != used){
                    used = max(height1,height2);
                    addLast(doble, d2->pos,max(height1,height2));
                }
                d2 = d2->next;
            }
            else if(max(d1->height,d2->height) != used){
                height1 = d1->height;
                height2 = d2->height;
                used = max(height1,height2);
                if(max(height1,height2) == height1){
                    addLast(doble, d1->pos,max(height1,height2));
                }else{
                    addLast(doble, d2->pos,max(height1,height2));

                }
                d1 = d1->next;
                d2 = d2->next;
            }
        }
        if(d1 != NULL){
            while(d1 != NULL){
                if(max(d1->height,height2) != used){
                    height1 = d1->height;
                    addLast(doble, d1->pos,max(height1,height2));
                    used = max(height1,height2);
                }
                d1 = d1->next;    
            }
        }
        if(d2 != NULL){
            while(d2 != NULL){
                if(max(height1,d2->height) != used){
                    height2 = d2->height;
                    used = max(height1,height2);
                    addLast(doble, d2->pos,max(height1,height2));

                }
                d2 = d2->next;    
            }
        }
        return doble;
    }

    Doble* maxBorder(int pos1, int pos2,Triplet** t1){
        if(pos1 == pos2){
            Doble* newDoble = new Doble;
            newDoble->pos = t1[pos1]->posI;
            newDoble->height = t1[pos1]->height;
            newDoble->next = new Doble;
            newDoble->next->pos = t1[pos1]->posF;
            newDoble->next->height = 0;
            newDoble->next->next = NULL;            
            return newDoble;
        }
        int middle = (pos2-pos1)/2 + pos1;
        Doble* toReturn = merge(maxBorder(pos1,middle,t1), maxBorder(middle+1, pos2, t1));
        return toReturn;
    }


int main(){

    unsigned int triplets;
    unsigned int posI;
    unsigned int posF;
    unsigned int height;

    cin >> triplets;

    Triplet** figures = new Triplet*[triplets];

    for(unsigned int i=0; i<triplets; i++){
        cin >> posI;
        cin >> posF;
        cin >> height;
        addFigure(posI, posF, height, figures);
    }

    Doble* result = maxBorder(0, triplets-1, figures);

    result = result->next;
    while(result != NULL){
        cout << result->pos << " " << result->height << endl;
        result = result->next;
    }

    return 0;
}
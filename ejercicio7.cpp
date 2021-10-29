#include <iostream>
#include <stack>


using namespace std;

struct ListNode{
    int dato1;
    int dato2;
    ListNode* next;
    ListNode(int d1, int d2) : dato1(d1), dato2(d2), next(0) {}
    ListNode(int d1, int d2, ListNode* unNext) : dato1(d1), dato2(d2), next(unNext) {}
};

class Cola 
{
    private: 
        ListNode* first;
        ListNode* last;
        int countElem;

    public:

        Cola(){
            this->first=NULL;
            this->last=NULL;
            this->countElem=0;
        }

        void insert(int data1, int data2){
            if (this->countElem==0){
                this->first = new ListNode(data1, data2);
                this->last=this->first;
            }
            else{
                ListNode*  newNode = new ListNode(data1, data2);
                this->last->next=newNode;
                this->last=newNode;
            }
            this->countElem++;
        }

        bool isEmpty(){
            if (this->countElem==0){
                return true;
            }
            else{
                return false;
            }
        }

        ListNode* getMin(){
            return this->first;
        }

        void dequeue(){
            assert(!this->isEmpty());
            ListNode* quit =this->first;
            this->first=this->first->next;
            delete quit;
            this->countElem--;
        }

};


void MinPases(int** mat,int rowCount, int colCount, int row, int col) {

    Cola* c = new Cola();
    int count =  0;

    bool finished = false;
    while(finished == false){
        finished = true;
        for(int i=0; i<rowCount; i++){
            for(int j=0; j<colCount; j++){
                if(mat[i][j] > 0){
                    c->insert(i,j);   
                }else if(mat[i][j]<0){
                    finished = false; 
                }  
            } 
        } 
        if(finished == true)break;
        while(!c->isEmpty()){ 
            row = c->getMin()->dato1;
            col = c->getMin()->dato2;
            c->dequeue();



            if((row + 1) < rowCount && mat[row+1][col] < 0 ){
                mat[row+1][col] = -(mat[row+1][col]);  

            }
            if((row - 1) >= 0 && mat[row-1][col] < 0 ){
                mat[row-1][col] = -(mat[row-1][col]);
            }
            if((col + 1) < colCount && mat[row][col + 1] < 0 ){
                mat[row][col+1] = -(mat[row][col+1]);
            }
            if((col - 1) >= 0 && mat[row][col - 1] < 0 ){
                mat[row][col-1] = -(mat[row][col-1]);
            }
        }
        count++;
    }
    cout << count;
}

int main(){

    int rowCount;
    int colCount;


    cin >> rowCount;
    cin >> colCount;

    int data;

    int row;
    int col;
    int** mat= new int*[rowCount];
    
    for(int i= 0; i< rowCount; i++){
        mat[i] = new int[colCount];
       for(int j= 0; j< colCount; j++){
           cin >> data;
           mat[i][j] = data;
       }
    }

    MinPases(mat, rowCount, colCount, row, col );

    return 0;
}
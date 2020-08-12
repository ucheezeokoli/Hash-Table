#include <iostream>
#include <stdlib.h>
using namespace std;

struct node{
    node* next;
    node* prev;
    int data;

    //default constructor
    node(){
        this->next = nullptr;
        this->prev = nullptr;
        this->data = 0;
    }

    //constructor with data
    node(int val): data(val){
        this->next = nullptr;
        this->prev = nullptr;
    }
};
struct LinkedList{
    node* head;

    //default constructor
    LinkedList(){
        this->head = nullptr;
    }

    //create new node, place at head
    void push(int val){
        node* temp = new node(val);

        if(this->head == NULL){
            this->head = temp;
        }

        else{
            head->prev = temp;
            temp->next = head;
            head = temp;
        }
    }

    //remove current head
    void pop(){
        if(head == NULL)
            return;

        node* curr = this->head;
        this->head = this->head->next;
        delete curr;
    }

    //searches for value by traversal, if found set pointer and return 1, else return 0;
    // function overloading to support regular search, and remove.
    bool search(int val, int* hops){
        if(head == NULL){
            return 0;
        }

        int j = 0; //j will be set to lateral hops when found.

        if(head->data == val){
            *hops = j;
            return 1;
        }

        //traverse until found
        node* curr = this->head;
        while(curr->next != NULL){
            if(curr->data == val){
                *hops = j;
                return 1;
            }
            curr = curr->next;
            j++;
        }

        if(curr->data == val){
            *hops = j;
            return 1;
        }

        return 0;
    }
   
    bool search(int val, node* found){
        if(head == NULL){
            return 0;
        }

        if(head->data == val){
            found = head;
            return 1;
        }

        //traverse until found
        node* curr = this->head;
        while(curr->next != NULL){
            if(curr->data == val){
                found = curr;
                return 1;
            }
            curr = curr->next;
        }

        if(curr->data == val){
            found = curr;
            return 1;
        }

        return 0;
    }

    //find then remove node
    bool remove(int val){
        if(head == NULL){
            return 0;
        }
        //element found at head
        if(head->data == val){
            this->pop();
            return 1;
        }

        node* found = this->head;
        while(found->next != NULL){
            if(found->data == val){  
                found->prev->next = found->next;
                found->next->prev = found->prev;
                delete found;
                return 1;
            }

            found = found->next;
        }

        //element found at tail
        if(found->data == val){
            found->prev->next = found->next;
            delete found;
            return 1;
        }
        return 0;
    }

    void print(){
        if(head != NULL){
            node* curr = head;
            while(curr->next != NULL){
                cout << curr->data << "->";
                curr = curr->next;
            }
            cout << curr->data << "->";
        }
    }

    ~LinkedList(){
        while(head != NULL){
            this->pop();
        }
    }
};

class hashTable{
    int key_size; //max key

    public:
    LinkedList** table;

    //defult constructor
    hashTable(){
        this->key_size = 0;
    }

    //constructor, creates a table that supports max keys
    hashTable(int m): key_size(m){
        table = new LinkedList*[m];

        for(int i = 0; i < m; i++){
            table[i] = new LinkedList;
        }
    }

    //return hashed index
    int getIndex(int k){
        return k % this->key_size;
    }

    //push key at hashed index
    void insert(int key){
        table[getIndex(key)]->push(key);
    }

    //search, return TRUE if found + updating i and j, else return FALSE
    bool search(int key, int *i, int *j){
        *i = getIndex(key);
        return table[getIndex(key)]->search(key, j);
    }

    bool del(int key){
        return table[getIndex(key)]->remove(key);
    }

    //print elements at each key
    void print(){
        for(int i = 0; i < key_size; i++){
            //cout << "printing table[" << i << "]" << endl;
            cout << i << ":";
            table[i]->print();
            cout << ";" << endl;
        }
    }

    ~hashTable(){
        for(int i = key_size-1; i >= 0; i--){
            //cout << "deleting table[" << i << "]" << endl;
            delete table[i];
        }
    }

};

//functions
int getVal(char*);

int main(int argc, const char * argv[]){
    char letter[5] = {'A','A','A','A','A'};
    int m;
    int valF; 

    //create a hashtable for amount of keys
    cin >> m;
    hashTable* bucket = new hashTable(m);

    //begin hashing table event
    cin >> letter;
    while(letter[0] != 'e'){
        switch(letter[0]){
           
            //insert key into table, on collision insert at beginning
            case 'i':{
                valF = getVal(letter);
                bucket->insert(valF);
            }
            break;

            //search for key, returning hash and list indices; or return NOT FOUND
            case 's':{
                int i = 0;
                int j = 0;

                valF = getVal(letter);
                if(bucket->search(valF, &i , &j)){
                    cout << valF << ":FOUND_AT" << i << "," << j << ";" << endl;
                }
                else{
                    cout << valF << ":NOT_FOUND;" << endl;
                }  
            }
            break;

            //delete key from table, if multiple elements with same key, delete first element.
            //  Return: if (key deleted): DELETED (element deleted), if (no key deleted): DELETE FAILED
            case 'd':{
                valF = getVal(letter);
                if(bucket->del(valF)){
                    cout << ""<< valF << ":DELETED;" << endl;
                }
                else{
                    cout << ""<< valF << ":DELETE_FAILED;" << endl;
                }
            }
            break;

            case 'o':{
                bucket->print();
            }
            break;
        }
        cin >> letter;
    }//end switch

    delete bucket;
    return 0;
}

//act as atoi() function, converting a char input to integer value
int getVal(char* letter){
    int val1, val2, val3, valF;

    
    if(letter[1] >= '0' && letter[1] <= '9'){    
        val1 = letter[1] - '0';
        valF = val1;
    }
    else{
        cout << "unsupported input" << endl;
        return -1;
    }

    if(letter[2] >= '0' && letter[2] <= '9'){
        val2 = letter[2] - '0';
        val1 *= 10;
        valF = val1+val2;
    }

    if(letter[3] >= '0' && letter[3] <= '9'){
        val3 = letter[3] - '0';
        val2 *= 10;
        val1 *= 10;
        valF = val1 + val2 + val3;
    }

    return valF;
}

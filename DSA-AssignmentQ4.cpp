/*
Example 4: Dynamic Array Operation
*/

#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* arr;
    int size;
    int capacity;

    void resize(int newCapacity) {
        int* newArr=new int[newCapacity];
        for(int i=0;i<size;i++)newArr[i]=arr[i];
        delete[] arr;
        arr=newArr;
        capacity=newCapacity;
    }

public:
    DynamicArray():size(0),capacity(2){arr=new int[capacity];}

    ~DynamicArray(){delete[] arr;}

    void insert(int element,int position) {
        if(position<0||position>size){cout<<"Invalid position!\n";return;}
        if(size==capacity)resize(capacity*2);
        for(int i=size;i>position;i--)arr[i]=arr[i-1];
        arr[position]=element;
        size++;
    }

    void remove(int position) {
        if(position<0||position>=size){cout<<"Invalid position!\n";return;}
        for(int i=position;i<size-1;i++)arr[i]=arr[i+1];
        size--;
        if(size>0&&size<=capacity/4)resize(capacity/2);
    }

    void display() {
        for(int i=0;i<size;i++)cout<<arr[i]<<" ";
        cout<<endl;
    }
};

int main() {
    DynamicArray arr;
    arr.insert(10,0);
    arr.insert(20,1);
    arr.insert(30,2);
    arr.display();

    arr.insert(15,1);
    arr.display();

    arr.remove(2);
    arr.display();

    return 0;
}


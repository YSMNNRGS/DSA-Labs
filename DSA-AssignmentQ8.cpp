/*
Example 7:Car Showroom Management
*/

#include <iostream>
using namespace std;

class Car {
public:
    string brand;
	string model;
    float price;

    Car(string b,string m,float p){
        brand=b;
        model=m;
        price=p;
    }
};

class Showroom {
private:
    Car** cars;
    int capacity;
    int count;

public:
    Showroom(int size){
        capacity=size;
        count=0;
        cars=new Car*[capacity];
        for(int i=0;i<capacity;i++)cars[i]=NULL;
    }

    ~Showroom(){
        for(int i=0;i<capacity;i++)if(cars[i])delete cars[i];
        delete[] cars;
    }

    void addCar(string brand,string model,float price){
        if(count==capacity){cout<<"Showroom full!\n";return;}
        for(int i=0;i<capacity;i++){
            if(cars[i]==NULL){
                cars[i]=new Car(brand,model,price);
                count++;
                cout<<"Car added at slot "<<i+1<<endl;
                return;
            }
        }
    }

    void displayCars(){
        for(int i=0;i<capacity;i++){
            if(cars[i])cout<<"Slot "<<i+1<<": "<<cars[i]->brand<<" "<<cars[i]->model<<" - $"<<cars[i]->price<<endl;
            else cout<<"Slot "<<i+1<<": Empty\n";
        }
    }

    void deleteCar(int slot){
        if(slot<1||slot>capacity||cars[slot-1]==NULL){
            cout<<"Invalid slot or already empty!\n";
            return;
        }
        delete cars[slot-1];
        cars[slot-1]=NULL;
        count--;
        cout<<"Car removed from slot "<<slot<<endl;
    }

    void searchByBrand(string brand){
        bool found=false;
        for(int i=0;i<capacity;i++){
            if(cars[i]&&cars[i]->brand==brand){
                cout<<"Found: "<<cars[i]->brand<<" "<<cars[i]->model<<" - $"<<cars[i]->price<<endl;
                found=true;
            }
        }
        if(!found)cout<<"No cars found for brand "<<brand<<endl;
    }
};

int main(){
    Showroom s(5);
    s.addCar("Toyota","Corolla",20000);
    s.addCar("Honda","Civic",22000);
    s.displayCars();

    s.deleteCar(1);
    s.displayCars();

    s.searchByBrand("Honda");

    return 0;
}


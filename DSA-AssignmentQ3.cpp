/*
Example number 8: Vehicle Management System
*/
#include <iostream>
using namespace std;

class Vehicle {
public:
    string regNumber;
    int slotNumber;

    Vehicle(string reg,int slot){
        regNumber=reg;
        slotNumber=slot;
    }
};

class ParkingLot {
private:
    Vehicle** slots;
    int capacity;
    int occupied;

public:
    ParkingLot(int size){
        capacity=size;
        occupied=0;
        slots=new Vehicle*[capacity];
        for(int i=0;i<capacity;i++)slots[i]=NULL;
    }

    ~ParkingLot(){
        for(int i=0;i<capacity;i++)
		if(slots[i])delete slots[i];
        delete[] slots;
    }

    void addVehicle(string reg){
        if(occupied==capacity){cout<<"Parking full!\n";return;}
        for(int i=0;i<capacity;i++){
            if(slots[i]==NULL){
                slots[i]=new Vehicle(reg,i+1);
                occupied++;
                cout<<"Vehicle parked at slot "<<i+1<<endl;
                return;
            }
        }
    }

    void removeVehicle(int slot){
        if(slot<1||slot>capacity||slots[slot-1]==NULL){
            cout<<"Slot empty or invalid!\n";
            return;
        }
        delete slots[slot-1];
        slots[slot-1]=NULL;
        occupied--;
        cout<<"Vehicle removed from slot "<<slot<<endl;
    }

    void displaySlots(){
        for(int i=0;i<capacity;i++){
            if(slots[i])cout<<"Slot "<<i+1<<": "<<slots[i]->regNumber<<endl;
            else cout<<"Slot "<<i+1<<": Empty\n";
        }
    }
};

int main(){
    ParkingLot lot(5);
    lot.addVehicle("ABC123");
    lot.addVehicle("XYZ789");
    lot.displaySlots();

    lot.removeVehicle(1);
    lot.displaySlots();

    return 0;
}


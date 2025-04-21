/*
Example number 10: Product Inventry Management
*/

#include <iostream>
using namespace std;

class Product {
public:
    int productID,stockQuantity;
    string name;
    float price;

    Product(int id,string n,float p,int qty){
        productID=id;
        name=n;
        price=p;
        stockQuantity=qty;
    }

    void updateStock(int soldQty){
        if(stockQuantity>=soldQty){
            stockQuantity-=soldQty;
            cout<<"Stock updated! Remaining: "<<stockQuantity<<endl;
            if(stockQuantity<5)cout<<"Warning: Low stock!\n";
        }else cout<<"Not enough stock available!\n";
    }

    void display(){
        cout<<"ID: "<<productID<<", Name: "<<name<<", Price: $"<<price<<", Stock: "<<stockQuantity<<endl;
    }
};

class Inventory {
private:
    Product** products;
    int size,capacity;

    void resize(int newCapacity){
        Product** newProducts=new Product*[newCapacity];
        for(int i=0;i<size;i++)newProducts[i]=products[i];
        delete[] products;
        products=newProducts;
        capacity=newCapacity;
    }

public:
    Inventory():size(0),capacity(2){products=new Product*[capacity];}

    ~Inventory(){
        for(int i=0;i<size;i++)delete products[i];
        delete[] products;
    }

    void addProduct(int id,string name,float price,int qty){
        if(size==capacity)resize(capacity*2);
        products[size]=new Product(id,name,price,qty);
        size++;
    }

    void sellProduct(int id,int qty){
        for(int i=0;i<size;i++)if(products[i]->productID==id){products[i]->updateStock(qty);return;}
        cout<<"Product not found!\n";
    }

    void displayAll(){
        if(size==0){cout<<"No products in inventory!\n";return;}
        for(int i=0;i<size;i++)products[i]->display();
    }
};

int main(){
    Inventory inv;
    inv.addProduct(101,"Laptop",999.99,10);
    inv.addProduct(102,"Mouse",25.50,4);
    inv.displayAll();

    inv.sellProduct(102,2);
    inv.sellProduct(102,3);
    inv.displayAll();

    return 0;
}


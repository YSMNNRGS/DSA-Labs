/*
Example number 9: Contact Book
*/

#include <iostream>
using namespace std;

class Contact {
public:
    string name,phone;
    Contact* next;

    Contact(string n,string p){
        name=n;
        phone=p;
        next=NULL;
    }
};

class ContactBook {
private:
    Contact* head;

public:
    ContactBook(){head=NULL;}

    ~ContactBook(){
        while(head){
            Contact* temp=head;
            head=head->next;
            delete temp;
        }
    }

    void addContact(string name,string phone){
        Contact* newContact=new Contact(name,phone);
        newContact->next=head;
        head=newContact;
        cout<<"Contact added!\n";
    }

    void deleteContact(string name){
        Contact* temp=head,*prev=NULL;
        while(temp&&temp->name!=name){
            prev=temp;
            temp=temp->next;
        }
        if(!temp){cout<<"Contact not found!\n";return;}
        if(!prev)head=temp->next;
        else prev->next=temp->next;
        delete temp;
        cout<<"Contact deleted!\n";
    }

    void displayContacts(){
        if(!head){cout<<"No contacts available!\n";return;}
        Contact* temp=head;
        while(temp){
            cout<<"Name: "<<temp->name<<", Phone: "<<temp->phone<<endl;
            temp=temp->next;
        }
    }

    void searchContact(string name){
        Contact* temp=head;
        while(temp){
            if(temp->name==name){cout<<"Found! Phone: "<<temp->phone<<endl;return;}
            temp=temp->next;
        }
        cout<<"Contact not found!\n";
    }
};

int main(){
    ContactBook cb;
    cb.addContact("Yasamin","03454545454");
    cb.addContact("Zara","031443432984");
    cb.displayContacts();

    cb.searchContact("Sahar");
    cb.deleteContact("Maryam");
    cb.displayContacts();

    return 0;
}


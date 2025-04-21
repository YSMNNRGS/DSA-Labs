#include <iostream>
#include <string>
#include <windows.h> // for PlaySound & mciSendString
#pragma comment(lib, "winmm.lib") // link to Windows multimedia library

using namespace std;

struct Node {
    string name;
    string path;
    Node* next;
    Node* prev;
};

Node* head = NULL;
Node* current = NULL;

void playSong(const string& filepath) {
    string command = "open \"" + filepath + "\" type mpegvideo alias mp3";
    mciSendString(command.c_str(), NULL, 0, NULL);
    mciSendString("play mp3", NULL, 0, NULL);
}

void stopSong() {
    mciSendString("stop mp3", NULL, 0, NULL);
    mciSendString("close mp3", NULL, 0, NULL);
}

void insert() {
    string name, path;
    cout<<"Enter Song Name: ";
    getline(cin >> ws, name);
    cout<<"Enter File Path (e.g., C:\\\\Music\\\\song.mp3): ";
    getline(cin, path);

    Node* newNode = new Node;
	newNode->name = name;
	newNode->path = path;
	newNode->next = NULL;
	newNode->prev = NULL;

    if (!head) {
        newNode->next = newNode->prev = newNode;
        head = current = newNode;
        return;
    }

    Node* last = head->prev;
    newNode->prev = last;
    newNode->next = head;
    last->next = newNode;
    head->prev = newNode;
}

void removeMusic() {
    if (!head) {
        cout<<"No Music to delete!\n";
        return;
    }
    string temp;
    cout << "Enter Music Name to delete: ";
    getline(cin>>ws, temp);
    Node* ptr = head;
    do {
        if (ptr->name == temp) {
            if (ptr->next == ptr) {
                delete ptr;
                head = current = NULL;
                cout<<"Playlist is Empty Now!\n";
            } else {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                if (ptr == head) head = ptr->next;
                if (ptr == current) current = ptr->next;
                delete ptr;
                cout<<"Music deleted!\n";
            }
            return;
        }
        ptr = ptr->next;
    } while (ptr != head);
    cout<<"Music not found!\n";
}

void show() {
    if (!head) {
        cout<<"Playlist is Empty!\n";
        return;
    }
    Node* ptr = head;
    int i = 1;
    cout<<"\n--- Playlist ---\n";
    do {
        cout << i++ << ". " <<ptr->name << " (" <<ptr->path << ")\n";
        ptr = ptr->next;
    } while (ptr != head);
}

void playCurrent() {
    if (!current) {
        cout<<"No song loaded.\n";
        return;
    }
    cout << "Playing: " << current->name << endl;
    playSong(current->path);
}

void playNext() {
    if (!current) {
        cout<<"No songs in Playlist!\n";
    } else {
        current = current->next;
        playCurrent();
    }
}

void playPrev() {
    if (!current) {
        cout<<"No songs in Playlist!\n";
    } else {
        current = current->prev;
        playCurrent();
    }
}

void playFirst() {
    if (!head) cout<<"Playlist is Empty!\n";
    else {
        current = head;
        playCurrent();
    }
}

void playLast() {
    if (!head) cout<<"Playlist is Empty!\n";
    else {
        current = head->prev;
        playCurrent();
    }
}

void playSpecific() {
    if (!head) {
        cout<<"Playlist is empty!\n";
        return;
    }
    string temp;
    cout<<"Enter Song Name: ";
    getline(cin>>ws, temp);
    Node* ptr = head;
    do {
        if (ptr->name == temp) {
            current = ptr;
            playCurrent();
            return;
        }
        ptr = ptr->next;
    } while (ptr != head);
    cout<<"Music not found!\n";
}

int main() {
    while (true) {
        cout <<"\n===== Song Playlist =====\n"
             <<"1. Add Music\n"
             <<"2. Remove Music\n"
             <<"3. Show Playlist\n"
             <<"4. Play Current\n"
             <<"5. Play Next\n"
             <<"6. Play Previous\n"
             <<"7. Play First\n"
             <<"8. Play Last\n"
             <<"9. Play Specific\n"
             <<"10. Stop Music\n"
             <<"11. Exit\n";

        int choice;
        cin>>choice;

        switch (choice) {
            case 1:
			insert();
			break;
            case 2:
			removeMusic();
			break;
            case 3:show();
			break;
            case 4:
			playCurrent();
			break;
            case 5:
			playNext();
			break;
            case 6:
			playPrev();
			break;
            case 7:
			playFirst();
			break;
            case 8:
			playLast();
			break;
            case 9:
			playSpecific();
			break;
            case 10:
			stopSong();
			break;
            case 11:
			stopSong();
			return 0;
            default:
			cout<<"Invalid choice!\n";
        }
    }
}


#include <iostream>
#include <string>

using namespace std;

// İstenilen Node yapısı
struct Node {
    string songTitle;
    Node* next;
};

// 1. Şarkı Ekleme (Listenin başına - Prepend)
void addSong(Node*& head, const string& title) {
    Node* newNode = new Node(); // Yeni düğüm oluştur
    newNode->songTitle = title; // Şarkı adını ata
    newNode->next = head;       // Yeni düğümün next'i eski head'i göstersin
    head = newNode;             // Artık yeni head'imiz bu düğüm olsun
    cout << "\"" << title << "\" listenin basina eklendi!\n";
}

// 2. Şarkı Arama
void searchSong(Node* head, const string& title) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->songTitle == title) {
            cout << "Bulundu: \"" << title << "\" su anda playlist'te yer aliyor!\n";
            return; // Bulunca fonksiyondan çık
        }
        temp = temp->next; // Bir sonraki düğüme geç
    }
    cout << "Bulunamadi: \"" << title << "\" playlist'te yok.\n";
}

// 3. Şarkıları Listeleme
void listSongs(Node* head) {
    if (head == nullptr) {
        cout << "Playlist su an bos.\n";
        return;
    }
    
    Node* temp = head;
    int order = 1;
    cout << "\n--- PLAYLIST ---\n";
    while (temp != nullptr) {
        cout << order << ". " << temp->songTitle << "\n";
        temp = temp->next;
        order++;
    }
    cout << "----------------\n";
}

int main() {
    Node* head = nullptr; // Başlangıçta listemiz boş
    int choice;
    string songName;

    while (true) {
        // Main Menu
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Add Song\n";
        cout << "2. Search Song\n";
        cout << "3. List Songs\n";
        cout << "4. Exit\n";
        cout << "Seciminiz (1-4): ";
        cin >> choice;

        // Buffer'da kalan boşluk veya enter karakterini temizlemek için (getline düzgün çalışsın diye)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Gecersiz giris!\n";
            continue;
        }
        cin.ignore(); 

        switch (choice) {
            case 1:
                cout << "Eklenecek sarkinin adi: ";
                getline(cin, songName); // Boşluklu isimleri de alabilmek için getline kullanıyoruz
                addSong(head, songName);
                break;
            case 2:
                cout << "Aranacak sarkinin adi: ";
                getline(cin, songName);
                searchSong(head, songName);
                break;
            case 3:
                listSongs(head);
                break;
            case 4:
                cout << "Cikis yapiliyor...\n";
                // Bellek sızıntısını (Memory Leak) önlemek için listeyi temizliyoruz
                while (head != nullptr) {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
                return 0;
            default:
                cout << "Lutfen menuden gecerli bir secenek girin!\n";
        }
    }
    return 0;
}
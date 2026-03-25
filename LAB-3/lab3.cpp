#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// 1. Structure Tanımlama
struct Page {
    string url;
    string title;
    int accessTime[3]; // {Saat, Dakika, Saniye}
    Page *next;
    Page *prev;

    Page(string u, string t, int h, int m, int s) {
        url = u;
        title = t;
        accessTime[0] = h;
        accessTime[1] = m;
        accessTime[2] = s;
        next = nullptr;
        prev = nullptr;
    }
};

class BrowserHistory {
private:
    Page* head;
    Page* current;

public:
    BrowserHistory() : head(nullptr), current(nullptr) {}

    // Visit (Append): Yeni sayfa ekle
    void visit(string url, string title, int h, int m, int s) {
        Page* newPage = new Page(url, title, h, m, s);
        
        if (!head) {
            head = newPage;
            current = head;
        } else {
            // Mevcut konumdan sonrasını temizleyip yeni sayfa eklemek 
            // gerçek tarayıcı mantığıdır, ancak ödev "Append" dediği için sona ekliyoruz.
            Page* temp = head;
            while (temp->next) temp = temp->next;
            
            temp->next = newPage;
            newPage->prev = temp;
            current = newPage; // Yeni eklenen sayfaya git
        }
        cout << "Ziyaret edildi: " << title << endl;
    }

    // Back: Geri git
    void back() {
        if (current && current->prev) {
            current = current->prev;
            cout << "Geri gidildi: " << current->title << endl;
        } else {
            cout << "Geri gidecek sayfa yok!" << endl;
        }
    }

    // Forward: İleri git
    void forward() {
        if (current && current->next) {
            current = current->next;
            cout << "İleri gidildi: " << current->title << endl;
        } else {
            cout << "İleri gidecek sayfa yok!" << endl;
        }
    }

    // Delete Entry: Mevcut sayfayı sil ve bağlantıları kur
    void deleteEntry() {
        if (!current) return;

        Page* toDelete = current;

        if (toDelete->prev) toDelete->prev->next = toDelete->next;
        if (toDelete->next) toDelete->next->prev = toDelete->prev;

        if (toDelete == head) head = toDelete->next;

        // Sildikten sonra yeni current belirle
        if (toDelete->next) current = toDelete->next;
        else if (toDelete->prev) current = toDelete->prev;
        else current = nullptr;

        delete toDelete;
        cout << "Sayfa gecmisten silindi." << endl;
    }

    // Display History: Tüm listeyi yazdır
    void displayHistory() {
        if (!head) {
            cout << "Gecmis bos." << endl;
            return;
        }

        cout << "\n--- TARAYICI GECMISI ---" << endl;
        for (Page* temp = head; temp != nullptr; temp = temp->next) {
            if (temp == current) cout << "-> [SU ANKI] ";
            else cout << "   ";

            cout << temp->title << " (" << temp->url << ") - Zaman: ";
            
            // for loop ile accessTime formatlama
            for (int i = 0; i < 3; i++) {
                cout << setfill('0') << setw(2) << temp->accessTime[i] << (i < 2 ? ":" : "");
            }
            cout << endl;
        }
        cout << "------------------------\n" << endl;
    }

    // Memory Management: EXIT durumunda bellek temizliği
    ~BrowserHistory() {
        Page* temp = head;
        while (temp) {
            Page* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        cout << "Bellek temizlendi, cikiliyor..." << endl;
    }
};

int main() {
    BrowserHistory history;
    string command;

    while (true) {
        cout << "\nKomutlar: VISIT, BACK, FORWARD, DELETE, DISPLAY, EXIT\nSecim: ";
        cin >> command;

        if (command == "VISIT") {
            string url, title;
            int h, m, s;
            cout << "URL: "; cin >> url;
            cout << "Baslik: "; cin >> title;
            cout << "Saat Dakika Saniye (boslukla): "; cin >> h >> m >> s;
            history.visit(url, title, h, m, s);
        } 
        else if (command == "BACK") history.back();
        else if (command == "FORWARD") history.forward();
        else if (command == "DELETE") history.deleteEntry();
        else if (command == "DISPLAY") history.displayHistory();
        else if (command == "EXIT") break;
    }

    return 0;
}
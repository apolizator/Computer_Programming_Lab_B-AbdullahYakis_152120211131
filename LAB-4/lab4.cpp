#include <iostream>
#include <string>

using namespace std;

// --- DATA STRUCTURES ---

// 1. Money Stack Yapısı (Linked List)
struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3]; // [0]: 100s, [1]: 50s, [2]: 20s
    MoneyBundle* next;
};

// 2. Customer Queue Yapısı
struct Customer {
    string customerName;
    string transactionType;
};

// --- MONEY STACK CLASS (Linked List Implementation) ---
class MoneyStack {
private:
    MoneyBundle* top;

public:
    MoneyStack() { top = nullptr; }

    void push(string serial, string type, int c100, int c50, int c20) {
        MoneyBundle* newNode = new MoneyBundle;
        newNode->serialNumber = serial;
        newNode->currencyType = type;
        newNode->billCounts[0] = c100;
        newNode->billCounts[1] = c50;
        newNode->billCounts[2] = c20;
        newNode->next = top;
        top = newNode;
        cout << "Para destesi kasaya eklendi (Serial: " << serial << ")\n";
    }

    void pop() {
        if (top == nullptr) {
            cout << "Kasa bos, islem yapilamiyor!\n";
            return;
        }
        MoneyBundle* temp = top;
        top = top->next;
        cout << "Kasadan para cikisi yapildi (Serial: " << temp->serialNumber << ")\n";
        delete temp;
    }

    void display() {
        if (top == nullptr) {
            cout << "Kasada para yok.\n";
            return;
        }
        MoneyBundle* curr = top;
        cout << "\n--- KASADAKI PARA DESTELERI (Stack) ---\n";
        while (curr != nullptr) {
            cout << "Seri No: " << curr->serialNumber << " | Tur: " << curr->currencyType 
                 << " | (100s: " << curr->billCounts[0] << ", 50s: " << curr->billCounts[1] << ", 20s: " << curr->billCounts[2] << ")\n";
            curr = curr->next;
        }
    }

    bool isEmpty() { return top == nullptr; }
};

// --- CUSTOMER QUEUE CLASS (Circular Array Implementation) ---
class CustomerQueue {
private:
    Customer arr[5];
    int front, rear, size;
    const int capacity = 5;

public:
    CustomerQueue() {
        front = 0;
        rear = -1;
        size = 0;
    }

    void enqueue(string name, string type) {
        if (size == capacity) {
            cout << "Sira dolu! Yeni musteri alinmiyor.\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear].customerName = name;
        arr[rear].transactionType = type;
        size++;
        cout << "Musteri siraya girdi: " << name << "\n";
    }

    void dequeue() {
        if (size == 0) {
            cout << "Sira bos, bekleyen musteri yok.\n";
            return;
        }
        cout << "Musteri islemi tamamlandi: " << arr[front].customerName << "\n";
        front = (front + 1) % capacity;
        size--;
    }

    void display() {
        if (size == 0) {
            cout << "Sira su an bos.\n";
            return;
        }
        cout << "\n--- BEKLEYEN MUSTERILER (Circular Queue) ---\n";
        int count = 0;
        int i = front;
        while (count < size) {
            cout << (count + 1) << ". " << arr[i].customerName << " (" << arr[i].transactionType << ")\n";
            i = (i + 1) % capacity;
            count++;
        }
    }

    bool isEmpty() { return size == 0; }
};

// --- MAIN FUNCTION ---
int main() {
    MoneyStack safe;
    CustomerQueue bankLine;
    int choice;

    while (true) {
        cout << "\n--- BANKA YONETIM SISTEMI ---\n";
        cout << "1. Para Destesi Al (Push)\n";
        cout << "2. Yeni Musteri Ekle (Enqueue)\n";
        cout << "3. Islem Gerceklestir (Pop & Dequeue)\n";
        cout << "4. Durumu Goruntule (Display)\n";
        cout << "0. Cikis\n";
        cout << "Seciminiz: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                string sn, type;
                int c100, c50, c20;
                cout << "Seri No: "; cin >> sn;
                cout << "Doviz Turu (TL/USD): "; cin >> type;
                cout << "100'luk, 50'lik ve 20'lik adetlerini girin: ";
                cin >> c100 >> c50 >> c20;
                safe.push(sn, type, c100, c50, c20);
                break;
            }
            case 2: {
                string name, trans;
                cout << "Musteri Adi: "; cin >> name;
                cout << "Islem Turu (Deposit/Withdraw): "; cin >> trans;
                bankLine.enqueue(name, trans);
                break;
            }
            case 3: {
                if (safe.isEmpty() || bankLine.isEmpty()) {
                    cout << "Hata: Kasada para yok veya sira bos!\n";
                } else {
                    bankLine.dequeue();
                    safe.pop();
                }
                break;
            }
            case 4:
                safe.display();
                bankLine.display();
                break;
            default:
                cout << "Gecersiz secim!\n";
        }
    }

    return 0;
}
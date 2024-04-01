#include <iostream>
#include <cstring>

using namespace std;

// Structure untuk menyimpan informasi tanggal
struct Date {
    int day;
    int month;
    int year;
};

// Structure untuk menyimpan informasi tugas
struct Task {
    char name[50];
    Date deadline; // Deadline dalam bentuk tanggal
    bool isTugasKuliah; // true jika tugas sekolah, false jika tugas organisasi
};

// Node untuk linked list
struct Node {
    Task data;
    Node* next;
};

// Struktur untuk menyimpan daftar tugas yang sudah selesai
struct TugasSelesai {
    Task tasks[50]; // Maksimal 50 tugas yang sudah selesai
    int count; // Jumlah tugas yang sudah selesai
};

// Fungsi untuk menambahkan tugas ke linked list
void addTask(Node*& head, Task task) {
    Node* newNode = new Node;
    newNode->data = task;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Fungsi untuk menampilkan daftar tugas sesuai jenisnya
void tampilkanDaftarTugas(Node* head, bool isTugasKuliah) {
    Node* temp = head;
    bool found = false;

    while (temp != nullptr) {
        if (temp->data.isTugasKuliah == isTugasKuliah) {
            cout << " Nama Tugas : " << temp->data.name << endl;
            cout << " Deadline   : " << temp->data.deadline.day << "/" << temp->data.deadline.month << "/" << temp->data.deadline.year << endl;
            cout << " -----------------------------------------" << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Tidak ada tugas " << (isTugasKuliah ? "sekolah" : "organisasi") << " yang ditemukan." << endl;
    }
}

// Fungsi untuk menampilkan daftar tugas yang sudah selesai
void tampilkanTugasSelesai(const TugasSelesai& tugasSelesai) {
    for (int i = 0; i < tugasSelesai.count; i++) {
        cout << " Nama Tugas  : " << tugasSelesai.tasks[i].name << endl;
        cout << " Deadline    : " << tugasSelesai.tasks[i].deadline.day << "/" << tugasSelesai.tasks[i].deadline.month << "/" << tugasSelesai.tasks[i].deadline.year << endl;
        cout << " Jenis Tugas : " << (tugasSelesai.tasks[i].isTugasKuliah ? "Kuliah" : "Organisasi") << endl; // Perbaikan disini
        cout << " -----------------------------------------" << endl;
    }
}

// Fungsi untuk menandai tugas sebagai selesai dan memindahkannya ke daftar tugas yang sudah selesai
void markTugasSelesai(Node*& head, TugasSelesai& tugasSelesai, const char* taskName) {
    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr) {
        if (strcmp(temp->data.name, taskName) == 0) {
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            tugasSelesai.tasks[tugasSelesai.count++] = temp->data;
            cout << " Tugas '" << taskName << "' ditandai sebagai selesai." << endl;
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Tugas '" << taskName << "' tidak ditemukan." << endl;
}

// Fungsi untuk mencari tugas berdasarkan nama
void cariTugasByName(Node* head, const char* taskName) {
    Node* temp = head;
    bool found = false;

    while (temp != nullptr) {
        if (strcmp(temp->data.name, taskName) == 0) {
            cout << " Tugas '" << taskName << "' ditemukan :" << endl;
            cout << " Deadline    : " << temp->data.deadline.day << "/" << temp->data.deadline.month << "/" << temp->data.deadline.year << endl;
            cout << " Jenis Tugas : " << (temp->data.isTugasKuliah ? "Kuliah" : "Organisasi") << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Tugas '" << taskName << "' tidak ditemukan." << endl;
    }
}


int main() {
    Node* head = nullptr; // Inisialisasi linked list kosong
    TugasSelesai tugasSelesai; // Inisialisasi daftar tugas yang sudah selesai
    tugasSelesai.count = 0;

    int pilihan;
    char yt;

    do {
        // Fungsi untuk menampilkan menu
        cout << " ================================================" << endl;
        cout << " |          ^o^ KELOLA TUGASMU ^o^              |" << endl;
        cout << " ================================================" << endl;
        cout << " | 1. Input Tugas                               |" << endl;
        cout << " | 2. Tampilkan Daftar Tugas Kuliah             |" << endl;
        cout << " | 3. Tampilkan Daftar Tugas Organisasi         |" << endl;
        cout << " | 4. Tampilkan Daftar Tugas yang Sudah Selesai |" << endl;
        cout << " | 5. Tandai Tugas sebagai Selesai              |" << endl;
        cout << " | 6. Cari Tugas berdasarkan Nama               |" << endl;
        cout << " | 7. Selesai                                   |" << endl;
        cout << " ================================================" << endl;
        cout << " Masukkan pilihanmu: ";
        cin >> pilihan;
        system ("cls");


        switch (pilihan) {
            case 1: {

                Task newTask;
                cout << " =========================================================" << endl;
                cout << "                       Input Tugas                        " << endl;
                cout << " =========================================================" << endl;
            do {
                cout << endl;
                cout << " Masukkan nama tugas: ";
                cin.ignore();
                cin.getline(newTask.name, sizeof(newTask.name));
                cout << " Masukkan deadline (tanggal/bulan/tahun): ";
                cin >> newTask.deadline.day >> newTask.deadline.month >> newTask.deadline.year;
                cout << endl;
                cout << " Apakah tugas ini tugas kuliah (1) atau organisasi (0)?: ";
                cin >> newTask.isTugasKuliah;
                addTask(head, newTask);
                cout << " =========================================================" << endl;
                cout << " Input tugas lagi?(Y/T) : "; cin >> yt;
                }while (yt == 'Y' || yt == 'y');
                system("pause");
                system ("cls");
                break;
            }
            case 2:
                cout << " =========================================" << endl;
                cout << "           Daftar Tugas Kuliah            " << endl;
                cout << " =========================================" << endl;
                tampilkanDaftarTugas(head, true);
                system("pause");
                system ("cls");
                break;
            case 3:
                cout << " =========================================" << endl;
                cout << "         Daftar Tugas Organisasi          " << endl;
                cout << " =========================================" << endl;
                tampilkanDaftarTugas(head, false);
                system("pause");
                system ("cls");
                break;
            case 4:
                cout << " =========================================" << endl;
                cout << "        ^-^ Tugas Selesaaaii ^-^          " << endl;
                cout << " =========================================" << endl;
                tampilkanTugasSelesai(tugasSelesai);
                system("pause");
                system ("cls");
                break;
            case 5: {
                char taskName[50];
                cout << "=============================================================" << endl;
                cout << "                Tandai Tugas sebagai Selesai                 " << endl;
                cout << "=============================================================" << endl;
                cout << "Masukkan nama tugas yang ingin ditandai sebagai selesai: ";
                cout << endl;
                cin.ignore();
                cin.getline(taskName, sizeof(taskName));
                markTugasSelesai(head, tugasSelesai, taskName);
                system("pause");
                system ("cls");
                break;
            }
            case 6: {
                char cariTugas[50];
                cout << " =====================================================" << endl;
                cout << "             Cari Tugas berdasarkan Nama              " << endl;
                cout << " =====================================================" << endl;
                cout << " Masukkan nama tugas yang dicari: ";
                cin.ignore();
                cin.getline(cariTugas, sizeof(cariTugas));
                cariTugasByName(head, cariTugas);
                system("pause");
                system ("cls");
                break;
            }
            case 7:
                cout << " Program selesai. Terimakasii dan semangat mengerjakan tugasnyaa ^-^" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
                break;
        }

        cout << endl;

    } while (pilihan != 7);

    // Dealokasi memori linked list
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}

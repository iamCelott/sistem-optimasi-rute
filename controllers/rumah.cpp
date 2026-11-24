#include "../headers/rumah.h"
#include <iostream>

using namespace std;

/* 
   I.S. sembarang
   F.S. Terbentuk list rumah kosong dengan head = nullptr dan tail = nullptr
*/
void InitList(ListRumah &list) {
  list.head = nullptr;
  list.tail = nullptr;
}

/* 
   I.S. Terdefinisi list rumah L (mungkin kosong), nama, latitude, dan longitude
   F.S. Elemen baru dialokasikan dan dimasukkan di akhir list (Insert Last)
*/
void TambahRumah(ListRumah &list, string nama, double latitude,
                 double longitude) {
  int id = 1;

  if (list.tail != nullptr) {
    id = list.tail->id + 1;
  }

  Rumah *baru = new Rumah{id, nama, latitude, longitude, nullptr, nullptr};

  if (list.head == nullptr) {
    list.head = baru;
    list.tail = baru;
  } else {
    baru->prev = list.tail;
    list.tail->next = baru;
    list.tail = baru;
  }
}

/* 
   I.S. List L terdefinisi, id terdefinisi
   F.S. Mengembalikan pointer ke elemen rumah dengan id yang dicari, atau nullptr jika tidak ditemukan
   Catatan: Sesuai Aturan 2.f, tidak menggunakan break/return di dalam perulangan
*/
Rumah *CariRumahByID(ListRumah list, int id) {
  Rumah *current = list.head;
  Rumah *found = nullptr;

  while (current != nullptr && found == nullptr) {
    if (current->id == id) {
      found = current;
    } else {
      current = current->next;
    }
  }

  return found;
}

/* 
   I.S. List L terdefinisi, nama terdefinisi
   F.S. Mengembalikan pointer ke elemen rumah dengan nama yang dicari, atau nullptr jika tidak ditemukan
   Catatan: Sesuai Aturan 2.f, tidak menggunakan break/return di dalam perulangan
*/
Rumah *CariRumahByNama(ListRumah list, string nama) {
  Rumah *current = list.head;
  Rumah *found = nullptr;

  while (current != nullptr && found == nullptr) {
    if (current->nama == nama) {
      found = current;
    } else {
      current = current->next;
    }
  }

  return found;
}

/* 
   I.S. List L terdefinisi (mungkin kosong)
   F.S. Seluruh data rumah pada list dicetak ke layar
*/
void TampilRumah(ListRumah list) {
  Rumah *current = list.head;

  while (current != nullptr) {
    cout << "ID: " << current->id << endl;
    cout << "Nama: " << current->nama << endl;
    cout << "Latitude: " << current->latitude << endl;
    cout << "Longitude: " << current->longitude << endl;
    cout << "====================================" << endl;

    current = current->next;
  }
}

/* 
   I.S. List L terdefinisi, id terdefinisi, nama, latitude, dan longitude baru terdefinisi
   F.S. Jika id ditemukan, data rumah diperbarui dan mengembalikan true. Jika tidak, mengembalikan false
*/
bool UbahRumah(ListRumah &list, int id, string nama, double latitude,
               double longitude) {
  Rumah *rumah = CariRumahByID(list, id);

  if (rumah == nullptr) {
    return false;
  }

  rumah->nama = nama;
  rumah->latitude = latitude;
  rumah->longitude = longitude;

  return true;
}

/* 
   I.S. List L terdefinisi, id terdefinisi
   F.S. Jika id ditemukan, elemen rumah dihapus dari list dan didealokasi, lalu mengembalikan true. Jika tidak, mengembalikan false
*/
bool HapusRumah(ListRumah &list, int id) {
  Rumah *rumah = CariRumahByID(list, id);

  if (rumah == nullptr) {
    return false;
  }

  if (rumah->prev != nullptr) {
    rumah->prev->next = rumah->next;
  } else {
    list.head = rumah->next;
  }

  if (rumah->next != nullptr) {
    rumah->next->prev = rumah->prev;
  } else {
    list.tail = rumah->prev;
  }

  delete rumah;
  return true;
}

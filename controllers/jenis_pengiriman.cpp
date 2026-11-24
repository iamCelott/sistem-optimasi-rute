#include "../headers/jenis_pengiriman.h"
#include <iostream>

using namespace std;

/* 
   I.S. sembarang
   F.S. List terinisialisasi dengan head = nullptr
*/
void InitList(ListJenisPengiriman &list) {
  list.head = nullptr;
}

/* 
   I.S. List L terdefinisi (mungkin kosong), nama terdefinisi
   F.S. Elemen baru dialokasikan dan disisipkan di awal list (Insert First) sesuai Aturan 2.c
*/
void TambahJenisPengiriman(ListJenisPengiriman &list, string nama) {
  int maxId = 0;
  JenisPengiriman *curr = list.head;

  // Mencari ID tertinggi yang sudah ada tanpa return/break dalam loop
  while (curr != nullptr) {
    if (curr->id > maxId) {
      maxId = curr->id;
    }
    curr = curr->next;
  }

  int id = maxId + 1;
  JenisPengiriman *baru = new JenisPengiriman{id, nama, list.head};
  list.head = baru;
}

/* 
   I.S. List L terdefinisi, id terdefinisi
   F.S. Mengembalikan pointer ke elemen jenis pengiriman yang dicari, atau nullptr jika tidak ditemukan
   Catatan: Sesuai Aturan 2.f, tidak menggunakan break/return di dalam perulangan
*/
JenisPengiriman *CariJenisPengirimanByID(ListJenisPengiriman list, int id) {
  JenisPengiriman *current = list.head;
  JenisPengiriman *found = nullptr;

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
   F.S. Mengembalikan pointer ke elemen dengan nama yang dicari, atau nullptr jika tidak ditemukan
   Catatan: Sesuai Aturan 2.f, tidak menggunakan break/return di dalam perulangan
*/
JenisPengiriman *CariJenisPengirimanByNama(ListJenisPengiriman list,
                                           string nama) {
  JenisPengiriman *current = list.head;
  JenisPengiriman *found = nullptr;

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
   F.S. Semua elemen pada list ditampilkan ke layar
*/
void TampilJenisPengiriman(ListJenisPengiriman list) {
  JenisPengiriman *current = list.head;

  while (current != nullptr) {
    cout << "ID: " << current->id << endl;
    cout << "Nama: " << current->nama << endl;
    cout << "====================================" << endl;

    current = current->next;
  }
}

/* 
   I.S. List L terdefinisi, id dan nama baru terdefinisi
   F.S. Jika ID ditemukan, nama diperbarui dan mengembalikan true. Jika tidak, mengembalikan false
*/
bool UbahJenisPengiriman(ListJenisPengiriman &list, int id, string nama) {
  JenisPengiriman *jenisPengiriman = CariJenisPengirimanByID(list, id);

  if (jenisPengiriman == nullptr) {
    return false;
  }

  jenisPengiriman->nama = nama;
  return true;
}

/* 
   I.S. List L terdefinisi, id terdefinisi
   F.S. Elemen dengan ID tersebut dihapus dari list dan didealokasi jika ditemukan (tanpa tail sesuai Aturan 2.a)
   Catatan: Sesuai Aturan 2.f, tidak menggunakan break/return di dalam perulangan
*/
bool HapusJenisPengiriman(ListJenisPengiriman &list, int id) {
  JenisPengiriman *current = list.head;
  JenisPengiriman *prev = nullptr;
  bool found = false;

  while (current != nullptr && !found) {
    if (current->id == id) {
      found = true;
    } else {
      prev = current;
      current = current->next;
    }
  }

  if (!found) {
    return false;
  }

  if (prev == nullptr) {
    list.head = current->next;
  } else {
    prev->next = current->next;
  }

  delete current;
  return true;
}

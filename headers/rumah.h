#ifndef RUMAH_H
#define RUMAH_H

#include <string>
using namespace std;

struct Rumah {
  int id;
  string nama;
  double latitude;
  double longitude;
  Rumah *next;
  Rumah *prev;
};

// Sesuai Aturan 2.a: Doubly Linked List standar memiliki pointer head dan tail
struct ListRumah {
  Rumah *head;
  Rumah *tail;
};

/* 
   I.S. sembarang
   F.S. Terbentuk list rumah kosong dengan head = nullptr dan tail = nullptr
*/
void InitList(ListRumah &list);

/* 
   I.S. Terdefinisi list rumah L (mungkin kosong), nama, latitude, dan longitude
   F.S. Elemen baru dialokasikan dan dimasukkan sebagai elemen terakhir (Insert Last) pada list
*/
void TambahRumah(ListRumah &list, string nama, double latitude,
                 double longitude);

/* 
   I.S. List L terdefinisi, id terdefinisi
   F.S. Mengembalikan pointer ke elemen rumah dengan id yang dicari, atau nullptr jika tidak ditemukan
*/
Rumah *CariRumahByID(ListRumah list, int id);

/* 
   I.S. List L terdefinisi, nama terdefinisi
   F.S. Mengembalikan pointer ke elemen rumah dengan nama yang dicari, atau nullptr jika tidak ditemukan
*/
Rumah *CariRumahByNama(ListRumah list, string nama);

/* 
   I.S. List L terdefinisi (mungkin kosong)
   F.S. Menampilkan seluruh data rumah pada list ke layar
*/
void TampilRumah(ListRumah list);

/* 
   I.S. List L terdefinisi, id terdefinisi, nama, latitude, dan longitude baru terdefinisi
   F.S. Jika id ditemukan, data rumah diperbarui dan mengembalikan true. Jika tidak, mengembalikan false
*/
bool UbahRumah(ListRumah &list, int id, string nama, double latitude,
               double longitude);

/* 
   I.S. List L terdefinisi, id terdefinisi
   F.S. Jika id ditemukan, elemen rumah dihapus dari list, memori didealokasi, dan mengembalikan true. Jika tidak, false
*/
bool HapusRumah(ListRumah &list, int id);

#endif

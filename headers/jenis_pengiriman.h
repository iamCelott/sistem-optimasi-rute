#ifndef JENIS_PENGIRIMAN_H
#define JENIS_PENGIRIMAN_H

#include <string>
using namespace std;

struct JenisPengiriman {
  int id;
  string nama;
  JenisPengiriman *next;
};

// Sesuai Aturan 2.a: Singly Linked List standar hanya memiliki pointer head (tanpa tail/last)
struct ListJenisPengiriman {
  JenisPengiriman *head;
};

/* 
   I.S. sembarang
   F.S. Terbentuk list jenis pengiriman kosong dengan head = nullptr
*/
void InitList(ListJenisPengiriman &list);

/* 
   I.S. Terdefinisi list jenis pengiriman L (mungkin kosong) dan nama
   F.S. Elemen baru dialokasikan dan disisipkan di awal list (Insert First) sesuai Aturan 2.c
*/
void TambahJenisPengiriman(ListJenisPengiriman &list, string nama);

/* 
   I.S. List L terdefinisi, id terdefinisi
   F.S. Mengembalikan pointer ke elemen dengan id yang dicari, atau nullptr jika tidak ditemukan
*/
JenisPengiriman *CariJenisPengirimanByID(ListJenisPengiriman list, int id);

/* 
   I.S. List L terdefinisi, nama terdefinisi
   F.S. Mengembalikan pointer ke elemen dengan nama yang dicari, atau nullptr jika tidak ditemukan
*/
JenisPengiriman *CariJenisPengirimanByNama(ListJenisPengiriman list,
                                           string nama);

/* 
   I.S. List L terdefinisi (mungkin kosong)
   F.S. Seluruh elemen jenis pengiriman ditampilkan ke layar
*/
void TampilJenisPengiriman(ListJenisPengiriman list);

/* 
   I.S. List L terdefinisi, id dan nama baru terdefinisi
   F.S. Jika id ditemukan, data jenis pengiriman diperbarui dan mengembalikan true. Jika tidak, false
*/
bool UbahJenisPengiriman(ListJenisPengiriman &list, int id, string nama);

/* 
   I.S. List L terdefinisi, id terdefinisi
   F.S. Jika id ditemukan, elemen dihapus dari list, memori didealokasi, dan mengembalikan true. Jika tidak, false
*/
bool HapusJenisPengiriman(ListJenisPengiriman &list, int id);

#endif

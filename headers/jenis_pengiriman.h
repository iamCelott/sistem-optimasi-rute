#ifndef JENIS_PENGIRIMAN_H
#define JENIS_PENGIRIMAN_H

#include <string>
using namespace std;

struct JenisPengiriman {
  int id;
  string nama;
  JenisPengiriman *next;
};

struct ListJenisPengiriman {
  JenisPengiriman *head;
  JenisPengiriman *tail;
};

void InitList(ListJenisPengiriman &list);
void TambahJenisPengiriman(ListJenisPengiriman &list, string nama);
JenisPengiriman *CariJenisPengirimanByID(ListJenisPengiriman list, int id);
JenisPengiriman *CariJenisPengirimanByNama(ListJenisPengiriman list,
                                           string nama);
void TampilJenisPengiriman(ListJenisPengiriman list);
bool UbahJenisPengiriman(ListJenisPengiriman &list, int id, string nama);
bool HapusJenisPengiriman(ListJenisPengiriman &list, int id);

#endif
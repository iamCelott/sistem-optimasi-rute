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

struct ListRumah {
  Rumah *head;
  Rumah *tail;
};

void InitList(ListRumah &list);
void TambahRumah(ListRumah &list, int id, string nama, double latitude,
                 double longitude);
Rumah *CariRumah(ListRumah list, int id);
void TampilRumah(ListRumah list);
bool UbahRumah(ListRumah &list, int id, string nama, double latitude,
               double longitude);
bool HapusRumah(ListRumah &list, int id);

#endif
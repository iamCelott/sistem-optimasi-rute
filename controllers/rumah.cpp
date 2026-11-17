#include "../headers/rumah.h"
#include <iostream>

using namespace std;

void InitList(ListRumah &list) {
  list.head = nullptr;
  list.tail = nullptr;
}

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
    return;
  }

  baru->prev = list.tail;
  list.tail->next = baru;
  list.tail = baru;
}

Rumah *CariRumahByID(ListRumah list, int id) {
  Rumah *current = list.head;

  while (current != nullptr) {
    if (current->id == id) {
      return current;
    }

    current = current->next;
  }

  return nullptr;
}

Rumah *CariRumahByNama(ListRumah list, string nama) {
  Rumah *current = list.head;

  while (current != nullptr) {
    if (current->nama == nama) {
      return current;
    }

    current = current->next;
  }

  return nullptr;
}

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
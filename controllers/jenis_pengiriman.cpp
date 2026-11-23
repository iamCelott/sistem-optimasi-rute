#include "../headers/jenis_pengiriman.h"
#include <iostream>

using namespace std;

void InitList(ListJenisPengiriman &list) {
  list.head = nullptr;
  list.tail = nullptr;
}

void TambahJenisPengiriman(ListJenisPengiriman &list, string nama) {
  int id = 1;

  if (list.tail != nullptr) {
    id = list.tail->id + 1;
  }

  JenisPengiriman *baru = new JenisPengiriman{id, nama, nullptr};

  if (list.head == nullptr) {
    list.head = baru;
    list.tail = baru;
    return;
  }

  list.tail->next = baru;
  list.tail = baru;
}

JenisPengiriman *CariJenisPengirimanByID(ListJenisPengiriman list, int id) {
  JenisPengiriman *current = list.head;

  while (current != nullptr) {
    if (current->id == id) {
      return current;
    }

    current = current->next;
  }

  return nullptr;
}

JenisPengiriman *CariJenisPengirimanByNama(ListJenisPengiriman list,
                                           string nama) {
  JenisPengiriman *current = list.head;

  while (current != nullptr) {
    if (current->nama == nama) {
      return current;
    }

    current = current->next;
  }

  return nullptr;
}

void TampilJenisPengiriman(ListJenisPengiriman list) {
  JenisPengiriman *current = list.head;

  while (current != nullptr) {
    cout << "ID: " << current->id << endl;
    cout << "Nama: " << current->nama << endl;
    cout << "====================================" << endl;

    current = current->next;
  }
}

bool UbahJenisPengiriman(ListJenisPengiriman &list, int id, string nama) {
  JenisPengiriman *jenisPengiriman = CariJenisPengirimanByID(list, id);

  if (jenisPengiriman == nullptr) {
    return false;
  }

  jenisPengiriman->nama = nama;

  return true;
}

bool HapusJenisPengiriman(ListJenisPengiriman &list, int id) {
  JenisPengiriman *current = list.head;
  JenisPengiriman *prev = nullptr;

  while (current != nullptr && current->id != id) {
    prev = current;
    current = current->next;
  }

  if (current == nullptr) {
    return false;
  }

  if (prev == nullptr) {
    list.head = current->next;
  } else {
    prev->next = current->next;
  }

  if (current == list.tail) {
    list.tail = prev;
  }

  delete current;

  return true;
}
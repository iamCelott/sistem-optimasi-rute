#include "headers/haversine.h"
#include "headers/jenis_pengiriman.h"
#include "headers/normalize_coordinate.h"
#include "headers/rumah.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

int main() {
  cout << endl << "SISTEM OPTIMASI RUTE" << endl;
  cout << "====================================" << endl;

  string rawInput;
  double latitudeTitikBerangkat, longitudeTitikBerangkat;

  cout << "Masukkan titik keberangkatan kurir: ";
  getline(cin, rawInput);

  try {
    auto koordinat = NormalizeCoordinate(rawInput);
    latitudeTitikBerangkat = koordinat.first;
    longitudeTitikBerangkat = koordinat.second;
  } catch (const exception &e) {
    cout << endl << "Input tidak valid: " << e.what() << endl;
    cout << endl;
    return 1;
  }

  ListRumah listRumah;
  InitList(listRumah);

  ListJenisPengiriman listJenisPengiriman;
  InitList(listJenisPengiriman);
  TambahJenisPengiriman(listJenisPengiriman, "Express");
  TambahJenisPengiriman(listJenisPengiriman, "Regular");
  TambahJenisPengiriman(listJenisPengiriman, "Instant");
  TambahJenisPengiriman(listJenisPengiriman, "Same-Day");
  TambahJenisPengiriman(listJenisPengiriman, "Cargo");

  bool isRunning = true;

  while (isRunning) {
    cout << endl << "====================================" << endl;
    cout << "Silahkan Pilih Opsi di Bawah:" << endl;
    cout << "[1] Manajemen Rumah" << endl;
    cout << "[2] Manajemen Jenis Pengiriman" << endl;
    cout << "[3] Kalkulasi Rute Terbaik" << endl;
    cout << "[4] Keluar" << endl;

    int option;

    cout << "Pilih Opsi: ";
    cin >> option;

    switch (option) {
    case 1: {
      bool isRumahRunning = true;

      while (isRumahRunning) {
        int optionRumah;

        cout << endl << "====================================" << endl;
        cout << "MANAJEMEN RUMAH" << endl;
        cout << "====================================" << endl;
        cout << "[1] Lihat Seluruh Rumah" << endl;
        cout << "[2] Cari Rumah Berdasarkan Nama" << endl;
        cout << "[3] Tambah Rumah" << endl;
        cout << "[4] Edit Rumah" << endl;
        cout << "[5] Hapus Rumah" << endl;
        cout << "[6] Kembali" << endl;

        cout << "Pilih Opsi: ";
        cin >> optionRumah;

        switch (optionRumah) {
        case 1: {
          if (listRumah.head == nullptr) {
            cout << endl << "Belum ada rumah yang terdaftar!" << endl;
          } else {
            cout << endl << "====================================" << endl;
            cout << "DAFTAR SELURUH RUMAH" << endl;
            cout << "====================================" << endl;
            TampilRumah(listRumah);
          }

          break;
        }

        case 2: {
          if (listRumah.head == nullptr) {
            cout << endl << "Belum ada rumah yang terdaftar!" << endl;
            break;
          }

          string namaRumah;

          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          cout << endl << "Masukkan nama rumah yang dicari: ";
          getline(cin, namaRumah);

          Rumah *rumah = CariRumahByNama(listRumah, namaRumah);

          if (rumah == nullptr) {
            cout << endl
                 << "Rumah dengan nama \"" << namaRumah << "\" tidak ditemukan!"
                 << endl;
          } else {
            cout << endl << "====================================" << endl;
            cout << "DATA RUMAH DITEMUKAN" << endl;
            cout << "====================================" << endl;
            cout << "ID: " << rumah->id << endl;
            cout << "Nama: " << rumah->nama << endl;
            cout << "Latitude: " << rumah->latitude << endl;
            cout << "Longitude: " << rumah->longitude << endl;
            cout << "====================================" << endl;
          }

          break;
        }

        case 3: {
          string namaRumah;
          string titik;
          double latitude, longitude;

          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          cout << endl << "Masukkan nama rumah: ";
          getline(cin, namaRumah);

          cout << "Masukkan titik lokasi rumah: ";
          getline(cin, titik);

          try {
            auto koordinat = NormalizeCoordinate(titik);
            latitude = koordinat.first;
            longitude = koordinat.second;
          } catch (const exception &e) {
            cout << endl << "Input tidak valid: " << e.what() << endl;
            break;
          }

          TambahRumah(listRumah, namaRumah, latitude, longitude);

          cout << endl << "Rumah berhasil ditambahkan!" << endl;

          break;
        }

        case 4: {
          if (listRumah.head == nullptr) {
            cout << endl << "Belum ada rumah yang terdaftar!" << endl;
            break;
          }

          int id;

          cout << endl << "Masukkan ID rumah yang ingin diedit: ";
          cin >> id;

          Rumah *rumah = CariRumahByID(listRumah, id);

          if (rumah == nullptr) {
            cout << endl
                 << "Rumah dengan ID " << id << " tidak ditemukan!" << endl;
            break;
          }

          string namaRumah;
          string titik;
          double latitude, longitude;

          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          cout << "Masukkan nama baru rumah: ";
          getline(cin, namaRumah);

          cout << "Masukkan titik lokasi baru rumah: ";
          getline(cin, titik);

          try {
            auto koordinat = NormalizeCoordinate(titik);
            latitude = koordinat.first;
            longitude = koordinat.second;
          } catch (const exception &e) {
            cout << endl << "Input tidak valid: " << e.what() << endl;
            break;
          }

          UbahRumah(listRumah, id, namaRumah, latitude, longitude);

          cout << endl << "Data rumah berhasil diperbarui!" << endl;

          break;
        }

        case 5: {
          if (listRumah.head == nullptr) {
            cout << endl << "Belum ada rumah yang terdaftar!" << endl;
            break;
          }

          int id;

          cout << endl << "Masukkan ID rumah yang ingin dihapus: ";
          cin >> id;

          if (HapusRumah(listRumah, id)) {
            cout << endl << "Rumah berhasil dihapus!" << endl;
          } else {
            cout << endl
                 << "Rumah dengan ID " << id << " tidak ditemukan!" << endl;
          }

          break;
        }

        case 6:
          isRumahRunning = false;
          break;

        default:
          cout << endl << "Opsi yang anda masukkan tidak valid!" << endl;
          break;
        }
      }

      break;
    }

    case 2: {
      bool isJenisPengirimanRunning = true;

      while (isJenisPengirimanRunning) {
        int optionJenisPengiriman;

        cout << endl << "====================================" << endl;
        cout << "MANAJEMEN JENIS PENGIRIMAN" << endl;
        cout << "====================================" << endl;
        cout << "[1] Lihat Seluruh Jenis Pengiriman" << endl;
        cout << "[2] Cari Jenis Pengiriman Berdasarkan Nama" << endl;
        cout << "[3] Tambah Jenis Pengiriman" << endl;
        cout << "[4] Edit Jenis Pengiriman" << endl;
        cout << "[5] Hapus Jenis Pengiriman" << endl;
        cout << "[6] Kembali" << endl;

        cout << "Pilih Opsi: ";
        cin >> optionJenisPengiriman;

        switch (optionJenisPengiriman) {
        case 1: {
          if (listJenisPengiriman.head == nullptr) {
            cout << endl
                 << "Belum ada jenis pengiriman yang terdaftar!" << endl;
          } else {
            cout << endl << "====================================" << endl;
            cout << "DAFTAR SELURUH JENIS PENGIRIMAN" << endl;
            cout << "====================================" << endl;
            TampilJenisPengiriman(listJenisPengiriman);
          }

          break;
        }

        case 2: {
          if (listJenisPengiriman.head == nullptr) {
            cout << endl
                 << "Belum ada jenis pengiriman yang terdaftar!" << endl;
            break;
          }

          string namaJenisPengiriman;

          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          cout << endl << "Masukkan nama jenis pengiriman yang dicari: ";
          getline(cin, namaJenisPengiriman);

          JenisPengiriman *jenisPengiriman = CariJenisPengirimanByNama(
              listJenisPengiriman, namaJenisPengiriman);

          if (jenisPengiriman == nullptr) {
            cout << endl
                 << "Jenis pengiriman dengan nama \"" << namaJenisPengiriman
                 << "\" tidak ditemukan!" << endl;
          } else {
            cout << endl << "====================================" << endl;
            cout << "DATA JENIS PENGIRIMAN DITEMUKAN" << endl;
            cout << "====================================" << endl;
            cout << "ID: " << jenisPengiriman->id << endl;
            cout << "Nama: " << jenisPengiriman->nama << endl;
            cout << "====================================" << endl;
          }

          break;
        }

        case 3: {
          string namaJenisPengiriman;

          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          cout << endl << "Masukkan nama jenis pengiriman: ";
          getline(cin, namaJenisPengiriman);

          TambahJenisPengiriman(listJenisPengiriman, namaJenisPengiriman);

          cout << endl << "Jenis pengiriman berhasil ditambahkan!" << endl;

          break;
        }

        case 4: {
          if (listJenisPengiriman.head == nullptr) {
            cout << endl
                 << "Belum ada jenis pengiriman yang terdaftar!" << endl;
            break;
          }

          int id;
          string namaJenisPengiriman;

          cout << endl << "Masukkan ID jenis pengiriman yang ingin diedit: ";
          cin >> id;

          JenisPengiriman *jenisPengiriman =
              CariJenisPengirimanByID(listJenisPengiriman, id);

          if (jenisPengiriman == nullptr) {
            cout << endl
                 << "Jenis pengiriman dengan ID " << id << " tidak ditemukan!"
                 << endl;
            break;
          }

          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          cout << "Masukkan nama baru jenis pengiriman: ";
          getline(cin, namaJenisPengiriman);

          UbahJenisPengiriman(listJenisPengiriman, id, namaJenisPengiriman);

          cout << endl << "Data jenis pengiriman berhasil diperbarui!" << endl;

          break;
        }

        case 5: {
          if (listJenisPengiriman.head == nullptr) {
            cout << endl
                 << "Belum ada jenis pengiriman yang terdaftar!" << endl;
            break;
          }

          int id;

          cout << endl << "Masukkan ID jenis pengiriman yang ingin dihapus: ";
          cin >> id;

          if (HapusJenisPengiriman(listJenisPengiriman, id)) {
            cout << endl << "Jenis pengiriman berhasil dihapus!" << endl;
          } else {
            cout << endl
                 << "Jenis pengiriman dengan ID " << id << " tidak ditemukan!"
                 << endl;
          }

          break;
        }

        case 6:
          isJenisPengirimanRunning = false;
          break;

        default:
          cout << endl << "Opsi yang anda masukkan tidak valid!" << endl;
          break;
        }
      }

      break;
    }

    case 3: {
      vector<Rumah *> daftarRumah;

      Rumah *current = listRumah.head;

      while (current != nullptr) {
        daftarRumah.push_back(current);
        current = current->next;
      }

      if (daftarRumah.empty()) {
        cout << endl << "Belum ada rumah yang terdaftar!" << endl;
        break;
      }

      sort(daftarRumah.begin(), daftarRumah.end(),
           [](Rumah *a, Rumah *b) { return a->id < b->id; });

      double jarakMinimum = numeric_limits<double>::max();
      double totalJarak;
      vector<Rumah *> ruteTerbaik;

      do {
        totalJarak = 0;

        double latitudeAwal = latitudeTitikBerangkat;
        double longitudeAwal = longitudeTitikBerangkat;

        for (Rumah *rumah : daftarRumah) {
          totalJarak += Haversine(latitudeAwal, longitudeAwal, rumah->latitude,
                                  rumah->longitude);

          latitudeAwal = rumah->latitude;
          longitudeAwal = rumah->longitude;
        }

        if (totalJarak < jarakMinimum) {
          jarakMinimum = totalJarak;
          ruteTerbaik = daftarRumah;
        }

      } while (
          next_permutation(daftarRumah.begin(), daftarRumah.end(),
                           [](Rumah *a, Rumah *b) { return a->id < b->id; }));

      cout << endl << "====================================" << endl;
      cout << "HASIL OPTIMASI RUTE" << endl;
      cout << "====================================" << endl;

      cout << fixed << setprecision(2);

      cout << "Titik Keberangkatan Kurir" << endl;

      for (int i = 0; i < ruteTerbaik.size(); i++) {
        cout << i + 1 << ". " << ruteTerbaik[i]->nama << endl;
        cout << "   Latitude  : " << ruteTerbaik[i]->latitude << endl;
        cout << "   Longitude : " << ruteTerbaik[i]->longitude << endl;
      }

      cout << "====================================" << endl;
      cout << "Total Jarak Tempuh: " << jarakMinimum << " km" << endl;
      cout << "====================================" << endl;

      break;
    }

    case 4:
      isRunning = false;
      break;

    default:
      cout << endl << "Opsi yang anda masukkan tidak valid!" << endl;
      break;
    }
  }

  return 0;
}
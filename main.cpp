
#include "headers/haversine.h"
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

  bool isRunning = true;

  while (isRunning) {
    cout << endl << "====================================" << endl;
    cout << "Silahkan Pilih Opsi di Bawah:" << endl;
    cout << "[1] Lihat Seluruh Rumah" << endl;
    cout << "[2] Cari Rumah Berdasarkan Nama" << endl;
    cout << "[3] Tambah Rumah" << endl;
    cout << "[4] Edit Rumah" << endl;
    cout << "[5] Hapus Rumah" << endl;
    cout << "[6] Kalkulasi Jarak Terdekat" << endl;
    cout << "[7] Keluar" << endl;

    int option;
    cout << "Pilih Opsi: ";
    cin >> option;

    switch (option) {
    case 1:
      /* code */
      break;

    case 2:
      /* code */
      break;

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

    case 4:
      /* code */
      break;

    case 5:
      /* code */
      break;

    case 6: {
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
    case 7:
      isRunning = false;
      break;
    default:
      cout << endl << "Opsi yang anda masukkan tidak valid!" << endl;
      break;
    }
  }

  return 0;
}

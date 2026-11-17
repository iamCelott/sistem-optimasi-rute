#include "headers/normalize_link.h"
#include "headers/rumah.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  cout << endl << "SISTEM OPTIMASI RUTE" << endl;
  cout << "====================================" << endl;

  string rawInput, latitudeTitikBerangkat, longitudeTitikBerangkat;
  cout << "Masukkan titik keberangkatan kurir: ";
  getline(cin, rawInput);

  try {
    auto koordinat = NormalizeLink(rawInput);
    double latitudeTitikBerangkat = koordinat.first;
    double longitudeTitikBerangkat = koordinat.second;
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
    cout << "[2] Tambah Rumah" << endl;
    cout << "[3] Edit Rumah" << endl;
    cout << "[4] Hapus Rumah" << endl;
    cout << "[5] Kalkulasi Jarak Terdekat" << endl;
    cout << "[6] Keluar" << endl;

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
    case 3:
      /* code */
      break;
    case 4:
      /* code */
      break;
    case 5:
      /* code */
      break;
    case 6:
      isRunning = false;
      break;
    default:
      cout << endl << "Opsi yang anda masukkan tidak valid!" << endl;
      break;
    }
  }

  return 0;
}

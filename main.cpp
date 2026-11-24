#include "headers/haversine.h"
#include "headers/jenis_pengiriman.h"
#include "headers/normalize_coordinate.h"
#include "headers/rumah.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/* 
   I.S. Terdefinisi array pointer semuaRumah, ruteSementara, status dikunjungi, index penempatan, koordinat titik awal kurir
   F.S. Ditemukan susunan rute pengantaran terbaik dengan jarak minimum (Brute Force TSP secara rekursif manual tanpa STL <algorithm> atau <vector>)
*/
void CariRuteOptimal(Rumah *semuaRumah[], Rumah *ruteSementara[], bool dikunjungi[],
                     int index, int totalRumah,
                     double latAwal, double lonAwal,
                     Rumah *ruteTerbaik[], double &jarakMinimum) {
  if (index == totalRumah) {
    double totalJarak = 0.0;
    double latSebelumnya = latAwal;
    double lonSebelumnya = lonAwal;

    int i = 0;
    while (i < totalRumah) {
      totalJarak += Haversine(latSebelumnya, lonSebelumnya,
                              ruteSementara[i]->latitude, ruteSementara[i]->longitude);
      latSebelumnya = ruteSementara[i]->latitude;
      lonSebelumnya = ruteSementara[i]->longitude;
      i++;
    }

    if (totalJarak < jarakMinimum) {
      jarakMinimum = totalJarak;
      int j = 0;
      while (j < totalRumah) {
        ruteTerbaik[j] = ruteSementara[j];
        j++;
      }
    }
    return;
  }

  int k = 0;
  while (k < totalRumah) {
    if (!dikunjungi[k]) {
      dikunjungi[k] = true;
      ruteSementara[index] = semuaRumah[k];
      CariRuteOptimal(semuaRumah, ruteSementara, dikunjungi, index + 1, totalRumah,
                      latAwal, lonAwal, ruteTerbaik, jarakMinimum);
      dikunjungi[k] = false;
    }
    k++;
  }
}

int main() {
  cout << endl << "SISTEM OPTIMASI RUTE" << endl;
  cout << "====================================" << endl;

  string rawInput;
  double latitudeTitikBerangkat = 0.0;
  double longitudeTitikBerangkat = 0.0;

  cout << "Masukkan titik keberangkatan kurir: ";
  getline(cin, rawInput);

  try {
    auto koordinat = NormalizeCoordinate(rawInput);
    latitudeTitikBerangkat = koordinat.first;
    longitudeTitikBerangkat = koordinat.second;
  } catch (const string &e) {
    cout << endl << "Input tidak valid: " << e << endl;
    cout << endl;
    return 1;
  } catch (const exception &e) {
    cout << endl << "Input tidak valid: " << e.what() << endl;
    cout << endl;
    return 1;
  }

  ListRumah listRumah;
  InitList(listRumah);

  // Inisialisasi jenis pengiriman (Insert First sesuai Aturan 2.c & tanpa tail sesuai Aturan 2.a)
  ListJenisPengiriman listJenisPengiriman;
  InitList(listJenisPengiriman);
  TambahJenisPengiriman(listJenisPengiriman, "Cargo");
  TambahJenisPengiriman(listJenisPengiriman, "Same-Day");
  TambahJenisPengiriman(listJenisPengiriman, "Instant");
  TambahJenisPengiriman(listJenisPengiriman, "Regular");
  TambahJenisPengiriman(listJenisPengiriman, "Express");

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
          } else {
            string namaRumah;
            cin.ignore(1000, '\n');

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
          }
          break;
        }

        case 3: {
          string namaRumah;
          string titik;
          double latitude = 0.0;
          double longitude = 0.0;

          cin.ignore(1000, '\n');

          cout << endl << "Masukkan nama rumah: ";
          getline(cin, namaRumah);

          cout << "Masukkan titik lokasi rumah: ";
          getline(cin, titik);

          bool inputValid = true;
          try {
            auto koordinat = NormalizeCoordinate(titik);
            latitude = koordinat.first;
            longitude = koordinat.second;
          } catch (const string &e) {
            cout << endl << "Input tidak valid: " << e << endl;
            inputValid = false;
          } catch (const exception &e) {
            cout << endl << "Input tidak valid: " << e.what() << endl;
            inputValid = false;
          }

          if (inputValid) {
            TambahRumah(listRumah, namaRumah, latitude, longitude);
            cout << endl << "Rumah berhasil ditambahkan!" << endl;
          }
          break;
        }

        case 4: {
          if (listRumah.head == nullptr) {
            cout << endl << "Belum ada rumah yang terdaftar!" << endl;
          } else {
            int id;
            cout << endl << "Masukkan ID rumah yang ingin diedit: ";
            cin >> id;

            Rumah *rumah = CariRumahByID(listRumah, id);

            if (rumah == nullptr) {
              cout << endl
                   << "Rumah dengan ID " << id << " tidak ditemukan!" << endl;
            } else {
              string namaRumah;
              string titik;
              double latitude = 0.0;
              double longitude = 0.0;

              cin.ignore(1000, '\n');

              cout << "Masukkan nama baru rumah: ";
              getline(cin, namaRumah);

              cout << "Masukkan titik lokasi baru rumah: ";
              getline(cin, titik);

              bool inputValid = true;
              try {
                auto koordinat = NormalizeCoordinate(titik);
                latitude = koordinat.first;
                longitude = koordinat.second;
              } catch (const string &e) {
                cout << endl << "Input tidak valid: " << e << endl;
                inputValid = false;
              } catch (const exception &e) {
                cout << endl << "Input tidak valid: " << e.what() << endl;
                inputValid = false;
              }

              if (inputValid) {
                UbahRumah(listRumah, id, namaRumah, latitude, longitude);
                cout << endl << "Data rumah berhasil diperbarui!" << endl;
              }
            }
          }
          break;
        }

        case 5: {
          if (listRumah.head == nullptr) {
            cout << endl << "Belum ada rumah yang terdaftar!" << endl;
          } else {
            int id;
            cout << endl << "Masukkan ID rumah yang ingin dihapus: ";
            cin >> id;

            if (HapusRumah(listRumah, id)) {
              cout << endl << "Rumah berhasil dihapus!" << endl;
            } else {
              cout << endl
                   << "Rumah dengan ID " << id << " tidak ditemukan!" << endl;
            }
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
          } else {
            string namaJenisPengiriman;
            cin.ignore(1000, '\n');

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
          }
          break;
        }

        case 3: {
          string namaJenisPengiriman;
          cin.ignore(1000, '\n');

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
          } else {
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
            } else {
              cin.ignore(1000, '\n');

              cout << "Masukkan nama baru jenis pengiriman: ";
              getline(cin, namaJenisPengiriman);

              UbahJenisPengiriman(listJenisPengiriman, id, namaJenisPengiriman);
              cout << endl << "Data jenis pengiriman berhasil diperbarui!" << endl;
            }
          }
          break;
        }

        case 5: {
          if (listJenisPengiriman.head == nullptr) {
            cout << endl
                 << "Belum ada jenis pengiriman yang terdaftar!" << endl;
          } else {
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
      int totalRumah = 0;
      Rumah *curr = listRumah.head;
      while (curr != nullptr) {
        totalRumah++;
        curr = curr->next;
      }

      if (totalRumah == 0) {
        cout << endl << "Belum ada rumah yang terdaftar!" << endl;
        break;
      }

      Rumah **semuaRumah = new Rumah *[totalRumah];
      curr = listRumah.head;
      int idx = 0;
      while (curr != nullptr) {
        semuaRumah[idx] = curr;
        idx++;
        curr = curr->next;
      }

      Rumah **ruteSementara = new Rumah *[totalRumah];
      Rumah **ruteTerbaik = new Rumah *[totalRumah];
      bool *dikunjungi = new bool[totalRumah];

      int i = 0;
      while (i < totalRumah) {
        dikunjungi[i] = false;
        ruteSementara[i] = nullptr;
        ruteTerbaik[i] = nullptr;
        i++;
      }

      double jarakMinimum = 999999999.0;

      // Pencarian rute terbaik secara Brute Force TSP menggunakan fungsi rekursif manual (tanpa STL)
      CariRuteOptimal(semuaRumah, ruteSementara, dikunjungi, 0, totalRumah,
                      latitudeTitikBerangkat, longitudeTitikBerangkat,
                      ruteTerbaik, jarakMinimum);

      cout << endl << "====================================" << endl;
      cout << "HASIL OPTIMASI RUTE" << endl;
      cout << "====================================" << endl;

      cout << fixed << setprecision(2);
      cout << "Titik Keberangkatan Kurir" << endl;

      int j = 0;
      while (j < totalRumah) {
        cout << j + 1 << ". " << ruteTerbaik[j]->nama << endl;
        cout << "   Latitude  : " << ruteTerbaik[j]->latitude << endl;
        cout << "   Longitude : " << ruteTerbaik[j]->longitude << endl;
        j++;
      }

      cout << "====================================" << endl;
      cout << "Total Jarak Tempuh: " << jarakMinimum << " km" << endl;
      cout << "====================================" << endl;

      delete[] semuaRumah;
      delete[] ruteSementara;
      delete[] ruteTerbaik;
      delete[] dikunjungi;
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

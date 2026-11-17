#include "headers/normalize_link.h"
#include "headers/rumah.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  cout << endl << "SISTEM OPTIMASI RUTE" << endl;
  cout << "--------------------------------------" << endl;

  string rawInput, latitudeTitikBerangkat, longitudeTitikBerangkat;
  cout << "Masukkan titik keberangkatan kurir: ";
  getline(cin, rawInput);

  try {
    auto koordinat = NormalizeLink(rawInput);
    double latitudeTitikBerangkat = koordinat.first;
    double longitudeTitikBerangkat = koordinat.second;
  } catch (const exception &e) {
    cout << endl << "Input tidak valid: " << e.what() << endl;
    return 1;
  }

  ListRumah listRumah;
  InitList(listRumah);

  return 0;
}

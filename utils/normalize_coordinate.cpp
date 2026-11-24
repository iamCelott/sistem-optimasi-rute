#include "../headers/normalize_coordinate.h"
#include <string>

using namespace std;

/* 
   Fungsi pembantu untuk membersihkan spasi di awal dan akhir string
*/
static string Trim(const string &str) {
  size_t first = 0;
  while (first < str.length() && (str[first] == ' ' || str[first] == '\t' || str[first] == '\r' || str[first] == '\n')) {
    first++;
  }
  if (first >= str.length()) {
    return "";
  }
  size_t last = str.length() - 1;
  while (last > first && (str[last] == ' ' || str[last] == '\t' || str[last] == '\r' || str[last] == '\n')) {
    last--;
  }
  return str.substr(first, last - first + 1);
}

/* 
   I.S. Terdefinisi string input koordinat atau link Google Maps
   F.S. Mengembalikan std::pair<double, double> (latitude, longitude) tanpa menggunakan library regex (Aturan 2.f)
*/
pair<double, double> NormalizeCoordinate(const string &input) {
  if (input.empty()) {
    throw string("Input tidak boleh kosong!");
  }

  double latitude = 0.0;
  double longitude = 0.0;
  string latStr = "";
  string lonStr = "";

  if (input.find("google.com/maps") != string::npos) {
    size_t atPos = input.find("/@");
    if (atPos == string::npos) {
      throw string("Format link Google Maps tidak valid!");
    }

    size_t startCoord = atPos + 2;
    size_t commaPos = input.find(',', startCoord);
    if (commaPos == string::npos) {
      throw string("Format link Google Maps tidak valid!");
    }

    latStr = input.substr(startCoord, commaPos - startCoord);

    size_t nextComma = input.find(',', commaPos + 1);
    size_t endLon = (nextComma != string::npos) ? nextComma : input.find('/', commaPos + 1);
    if (endLon == string::npos) {
      endLon = input.length();
    }

    lonStr = input.substr(commaPos + 1, endLon - (commaPos + 1));
  } else {
    size_t commaPos = input.find(',');
    if (commaPos == string::npos) {
      throw string("Input harus berupa koordinat desimal (lat, lon) atau link Google Maps!");
    }

    latStr = input.substr(0, commaPos);
    lonStr = input.substr(commaPos + 1);
  }

  latStr = Trim(latStr);
  lonStr = Trim(lonStr);

  if (latStr.empty() || lonStr.empty()) {
    throw string("Koordinat latitude atau longitude tidak lengkap!");
  }

  try {
    latitude = stod(latStr);
    longitude = stod(lonStr);
  } catch (...) {
    throw string("Format angka koordinat tidak valid!");
  }

  if (latitude < -90.0 || latitude > 90.0) {
    throw string("Latitude harus berada di antara -90 sampai 90!");
  }

  if (longitude < -180.0 || longitude > 180.0) {
    throw string("Longitude harus berada di antara -180 sampai 180!");
  }

  return {latitude, longitude};
}

#define _USE_MATH_DEFINES
#include <cmath>
#include "../headers/haversine.h"

using namespace std;

/* 
   I.S. Terdefinisi koordinat titik 1 (latitude1, longitude1) dan titik 2 (latitude2, longitude2)
   F.S. Mengembalikan jarak geodesik antara dua titik di permukaan bumi dalam satuan kilometer (km)
*/
double Haversine(double latitude1, double longitude1, double latitude2,
                 double longitude2) {
  const double R = 6371.0;

  double lat1 = latitude1 * M_PI / 180.0;
  double lon1 = longitude1 * M_PI / 180.0;
  double lat2 = latitude2 * M_PI / 180.0;
  double lon2 = longitude2 * M_PI / 180.0;

  double deltaLat = lat2 - lat1;
  double deltaLon = lon2 - lon1;

  double a = pow(sin(deltaLat / 2), 2) +
             cos(lat1) * cos(lat2) * pow(sin(deltaLon / 2), 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  return R * c;
}

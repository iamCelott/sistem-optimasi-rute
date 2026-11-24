#ifndef NORMALIZE_COORDINATE_H
#define NORMALIZE_COORDINATE_H

#include <string>
#include <utility>

/* 
   I.S. Terdefinisi string input berupa koordinat desimal "lat, lon" atau URL Google Maps
   F.S. Mengembalikan pasangan nilai latitude dan longitude (std::pair<double, double>) yang valid
*/
std::pair<double, double> NormalizeCoordinate(const std::string &input);

#endif

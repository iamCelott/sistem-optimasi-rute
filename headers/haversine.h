#ifndef HAVERSINE_H
#define HAVERSINE_H

/* 
   I.S. Terdefinisi koordinat titik 1 (latitude1, longitude1) dan titik 2 (latitude2, longitude2) dalam derajat desimal
   F.S. Mengembalikan jarak geodesik antara dua titik di permukaan bumi dalam satuan kilometer (km)
*/
double Haversine(double latitude1, double longitude1, double latitude2,
                 double longitude2);

#endif

#ifndef CHINA_SHIFT_H
#define CHINA_SHIFT_H
typedef struct {
    double lng;
    double lat;
} Location;   //the first param is longtitude,the second param is latitude

Location transformFromWGSToGCJ(Location wgLoc);
Location transformFromGCJToWGS(Location gcLoc);
Location bd_encrypt(Location gcLoc);
Location bd_decrypt(Location bdLoc);
#endif // CHINA_SHIFT_H

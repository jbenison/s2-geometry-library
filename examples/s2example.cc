#include "s2.h"
#include "s2cellid.h"
#include "s2latlng.h"

#include <iostream>
using std::cout;
using std::endl;

int main() {
    S2LatLng latlong = S2LatLng::FromDegrees(-30.043800, -51.140220);
    S2CellId cellid = S2CellId::FromLatLng(latlong);
    cout << cellid.level() << endl;
    cout << cellid.id() << endl;
    return 0;
}
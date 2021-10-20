#ifndef FK_POS3D_H
#define FK_POS3D_H

#include "math.h"

namespace fk {
    struct Pos3d {
    public:
        double x;
        double y;
        double z;

        double *to_array() {
            return new double[3]{x, y, z};
        }

        double distance(Pos3d p) {
            return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2) + pow(p.z - z, 2));
        }

        Pos3d diff(Pos3d p) const {
            return {p.x - x, p.y - y, p.z - z};
        }
    };

}
#endif
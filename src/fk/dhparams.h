#ifndef FK_DH_PARAMS_H
#define FK_DH_PARAMS_H

namespace fk {
    struct DHParams {
        float r = 0;
        float alpha = 0;
        float d = 0;

        DHParams() : r(0), alpha(0), d(0) {}

        DHParams(float r, float alpha, float d) : r(r), alpha(alpha), d(d) {}
    };
}

#endif
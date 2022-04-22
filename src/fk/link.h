#ifndef FK_JOINT_H
#define FK_JOINT_H

#include "dhparams.h"
#include "matrix.h"
#include "math.h"

namespace fk {
    constexpr double RADIANS = 0.0174533;

    class Link {
    protected:

        double theta;
        double theta_base;
        DHParams dh;
        Matrix *matrix = nullptr;

    public:
        Link() : theta(0), theta_base(0), dh({0.0, 0.0, 0.0}) {}

        Link(double theta_base, DHParams dh) : theta_base(theta_base), theta(theta_base), dh(dh) {
            fillMatrix();
        }

        DHParams getDHParams() {
            return dh;
        }

        Matrix *getMatrix() {
            return matrix;
        }

        float getThetaBase() const {
            return theta_base;
        }

        float getTheta() const {
            return theta;
        }

        void setTheta(float v) {
            theta = v;
            fillMatrix();
        }

        void fillMatrix() {

            float *data = new float[16];
            float cosTheta = cos(theta * RADIANS);
            float sinTheta = sin(theta * RADIANS);
            float cosAlpha = cos(dh.alpha * RADIANS);
            float sinAlpha = sin(dh.alpha * RADIANS);
            data[0] = cosTheta;
            data[1] = -sinTheta * cosAlpha;
            data[2] = sinTheta * sinAlpha;
            data[3] = dh.r * cosTheta;
            data[4] = sinTheta;
            data[5] = cosTheta * cosAlpha;
            data[6] = -cosTheta * sinAlpha;
            data[7] = dh.r * sinTheta;
            data[8] = 0;
            data[9] = sinAlpha;
            data[10] = cosAlpha;
            data[11] = dh.d;
            data[12] = 0;
            data[13] = 0;
            data[14] = 0;
            data[15] = 1;

            matrix = new Matrix(4, 4, data);
        };
    };
}

#endif
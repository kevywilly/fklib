#ifndef FK_CHAIN_H
#define FK_CHAIN_H

#include "link.h"
#include "matrix.h"
#include "pos3d.h"

namespace fk {

    class Chain {
    public:
        int numLinks;
        Link *links = nullptr;
        Matrix *matrix = nullptr;
        Pos3d position;
        float *angles = nullptr;

        Chain() : numLinks(0) {}

        Chain(int numLinks, Link *links) : numLinks(numLinks), links(links) {
            angles = new float[numLinks];
            buildMatrix();
        }

        Pos3d calcPosition() {
            buildMatrix();
            return position;
        }

        Pos3d calcPosition(float *angles) {
            for (int i = 0; i < numLinks; i++) {
                links[i].setTheta(angles[i]);
            }
            return calcPosition();
        }

        Pos3d calcPosition(int16_t *angles) {
            for (int i = 0; i < numLinks; i++) {
                links[i].setTheta(angles[i]);
            }
            return calcPosition();
        }

        void buildMatrix() {
            matrix = links[0].getMatrix()->copy();
            for (int i = 0; i < numLinks; i++) {
                angles[i] = links[i].getTheta();
                links[i].fillMatrix();
                if (i > 0)
                    matrix = (*matrix * links[i].getMatrix());
            }
            position = Pos3d({matrix->x[3], matrix->x[7], matrix->x[11]});
        }

    };
}

#endif
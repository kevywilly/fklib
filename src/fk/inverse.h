//
// Created by Kevin Williams on 4/21/22.
//

#ifndef FK_INVERSE_H
#define FK_INVERSE_H

#include "pos3d.h"
#include "chain.h"

#ifndef DEGREES
#define DEGREES 57.296
#endif
#ifndef PI
#define PI 3.14159
#endif

namespace fk {
    Pos3d estimate3dof(Chain *chain, Pos3d pos) {

        float coxa_length = chain->links[0].getDHParams().r;
        float femur_length = chain->links[1].getDHParams().r;
        float tibia_length = chain->links[2].getDHParams().r;

        float lenFemurToTibia;                       // Length between Femur and Tibia
        float radiansFemurTibiaGround;  // Angle of the line Femur and Tibia with respect to the ground in radians
        float radiansFemurTibia;        // Angle of the line Femur and Tibia with respect to the femur in radians
        float distCoxaToGround;                // Distance between the Coxa and Ground Contact

        // Distance between the Coxa and Ground Contact
        distCoxaToGround = sqrt(pow(pos.x, 2) + pow(pos.y, 2));

        // lenFemurToTibia - Length between Femur axis and Tibia
        lenFemurToTibia = sqrt(pow((distCoxaToGround - coxa_length), 2) + pow(pos.z, 2));

        // radiansFemurTibiaGround - Angle between Femur and Tibia line and the ground in radians
        radiansFemurTibiaGround = atan2(distCoxaToGround - coxa_length, pos.z);

        // radiansFemurTibia - Angle of the line Femur and Tibia with respect to the Femur in radians
        radiansFemurTibia = acos(((pow(femur_length, 2) - pow(tibia_length, 2)) + pow(lenFemurToTibia, 2)) /
                                 (2 * femur_length * lenFemurToTibia));

        // ikCoxaAngle in degrees
        float coxa = atan2(pos.y, pos.x) * 180 / PI - chain->links[0].getThetaBase();

        // ikFemurAngle in degrees
        float femur = -(radiansFemurTibiaGround + radiansFemurTibia) * 180 / PI + 90;

        // ikTibiaAngle in degrees
        float tibia = -(chain->links[2].getThetaBase() - (((acos((pow(femur_length, 2) + pow(tibia_length, 2) - pow(lenFemurToTibia, 2)) /
                                      (2 * femur_length * tibia_length))) * 180) / PI));

        return (Pos3d) {coxa, femur, tibia};

    }
}
#endif //FK_INVERSE_H

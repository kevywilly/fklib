#include <iostream>

#include "src/fk/chain.h"
#include "src/fk/link.h"

using namespace fk;
int main() {
    Link * links = new Link[3] {
       Link(0,DHParams{24, 90, 0}),
       Link(0,DHParams{38, -180, 0}),
       Link(90,DHParams{77, 0, 0})
    };
    Chain c = Chain(3, links);
    Pos3d position = c.calcPosition(new int16_t[3]{0,0,90});
    std::cout << position.x << "," << position.y << "," << position.z << std::endl;
    return 0;
}

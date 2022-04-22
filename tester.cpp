#include <iostream>
#include <cassert>
#include "src/fk/link.h"
#include "src/fk/chain.h"

using namespace fk;
using namespace std;

void test_position_2(Chain &chain) {
    cout << "Testing Position Move 2" << endl;
    Pos3d position = chain.calcPosition(new int16_t[3]{0,0,90});
    std::cout << position.x << "," << position.y << "," << position.z << std::endl;
    assert((int)position.x == 61);
    assert((int)position.y == 0);
    assert((int)position.z == -77);
}

void test_position_1(Chain &chain) {
    cout << "Testing Position Move 1" << endl;
    Pos3d position = chain.calcPosition(new int16_t[3]{0,0,0});
    std::cout << position.x << "," << position.y << "," << position.z << std::endl;
    assert((int)position.x == 139);
    assert((int)position.y == 0);
    assert((int)position.z == 0);
}

int main() {

    Link * links = new Link[3] {
            Link(0,DHParams{24, 90, 0}),
            Link(0,DHParams{38, -180, 0}),
            Link(90,DHParams{77, 0, 0})
    };

    Chain c = Chain(3, links);

    test_position_1(c);
    test_position_2(c);

    return 0;
}
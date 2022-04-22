#include <stdio.h>
#include "src/fk/chain.h"
#include "src/fk/link.h"
#include "src/fk/inverse.h"
using namespace fk;

class Quadruped{
public:
    Chain * chains;
    const int numChains = 4;

    Quadruped(Chain *chains, const int numChains) : chains(chains), numChains(numChains) {

    }

};

Chain * chains;

int main() {
    chains = new Chain[4];
    for(int i=0; i < 4; i++) {
        Link * links = new Link[3] {
                Link(45,DHParams{24, 90, 0}),
                Link(0,DHParams{38, 0, 0}),
                Link(90,DHParams{77, 0, 0})
        };
        chains[i] = Chain(3, links);
    }

    Quadruped q = Quadruped(chains, 4);

    q.chains[0].links[0].setTheta(-10);
    //chains[0].calcPosition().print();

    for(int i=0; i < 4; i++) {
        Pos3d position = chains[i].calcPosition();
        position.print();
        Pos3d angles = estimate3dof(&q.chains[i], q.chains[i].position);
        angles.print();
    }

    return 0;
}

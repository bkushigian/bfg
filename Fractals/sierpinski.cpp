#include "sierpinski.hpp"

STNode::STNode(){
    STNode(6);      // Create with depth = 6
}

STNode::STNode(int depth){
    STNode(0.5, 1.0, 0.0, 0.0, 0.0, 1.0, depth);
}

STNode::STNode(
    double tX, double tY,
    double lX, double lY,
    double rX, double rY, int depth)
{
    this->tX = tX;
    this->tY = tY;
    this->lX = lX;
    this->lY = lY;
    this->rX = rX;
    this->rY = rY;
    if (depth == 0) {
        top = NULL; left = NULL; right = NULL;
    }
    else{
        top  = new STNode(   tX,           tY,
                             (tX-lX)/2,    (tY - lY)/2,
                             (rX-tX)/2,    (tY - lY)/2,
                             depth-1
                         );

        left = new STNode(   (tX-lX)/2,    (tY - lY)/2,
                             lX,           lY,
                             tX,           lY,
                             depth-1
                         );
        right = new STNode((rX-tX)/2,    (tY - rY)/2,
                           tX,           rY,
                           rX,           rY,
                           depth-1
                      );
    }
}

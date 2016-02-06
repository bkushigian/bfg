#ifndef SIERPINSKI_HPP
#define SIERPINSKI_HPP

class STriangle {

};

class STNode : public fractal {
private:
    STNode();
    STNode(int depth);  // Recursively build tree of Sierpinski Triangle Nodes
    STNode(double tX, double tY, double lX, double lY, double rX, double rY, int depth);
    double tX, tY, lX, lY, rX, rY;
    STNode* top;
    STNode* left;
    STNode* right;
public:
    void drawTree();
    void draw();
};

#endif

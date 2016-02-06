#ifndef MY_BUTTON_HPP
#define MY_BUTTON_HPP

#include <string>


class Button{
public:
    Button(std::string text, void(*func)(), bool active){
        this->active = active; onClick = func; this->text = text;
    }
    Button(std::string text, void(*func)()){
        this->active = true; onClick = func; this->text = text;
    }

    void click(){ onClick();}
    void activate(){ active = true;}
    void deactivate(){ active = false;}
    bool isActive(){ return active;}
    int getWidth(){ return width;}
    int getHeight(){return height;}
    void setWidth(int w){ if (w > 0) width = w;}
    void setHeight(int h){if (h > 0) height = h;}
    int getx() { return x; }
    int gety() { return y; }
    void setx(int x) { if (x > 0) this->x = x; }
    void sety(int y) { if (y > 0) this->y = y; }
    void setClick(void(*f)()) { onClick = f;}
private:
    bool active;                // Is this button available?
    std::string text;           // To display
    void (*onClick)();          // What to do on click
    int width;                  // In pixels
    int height;                 // In pixels
    int x;
    int y;
};

#endif

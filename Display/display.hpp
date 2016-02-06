#ifndef FRACTALS_DISPLAY_SFML_HPP
#define FRACTALS_DISPLAY_SFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <string>
//#include <vector>

using namespace sf;

enum DISPLAY_MODE{ NONE, GUI, PIXARRAY, TRIANGLES };
enum TOOLBAR_POS { POS_NONE, POS_LEFT, POS_RIGHT, POS_TOP, POS_BOTTOM };

class MainWindow{
private:
    DISPLAY_MODE displayMode;
    RenderWindow win;
    TOOLBAR_POS toolbarPosition;
    int width;
    int height;
    std::string title;
    static Color clearColor = Color::Black;
public:
    MainWindow();
    MainWindow(int w, int h);
    MainWindow(int w, int h, std::string t);

    void setWidth( int w){ if (w > 0) width = w;}
    void setHeight( int h){ if (h > 0) height = h;}
    int getWidth() { return width; }
    int getHeight() { return height; }
    RenderWindow* getWindow() { return &win; }

    void display() { win.display(); }

};



#endif

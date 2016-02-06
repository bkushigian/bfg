#include "display.hpp"

MainWindow::MainWindow(){
    toolbarPosition = POS_LEFT;
    displayMode = GUI;
    title = "Untitled Window";
    width = 1200;
    height = 700;
    win.create(VideoMode(width, height), title);
}
MainWindow::MainWindow(int w, int h){
    width = w; height = h;
    toolbarPosition = POS_LEFT;
    displayMode = GUI;
    title = "Untitled Window";
    win.create(VideoMode(width, height), title);
}
MainWindow::MainWindow(int w, int h, std::string t){
    width = w; height = h;
    toolbarPosition = POS_LEFT;
    displayMode = GUI;
    title = t;
    win.create(VideoMode(width, height), title);
}


#include "headers/mainWindow.h"


sf::RenderWindow& mainWindow::getWindow(){
    return this->Window;
}

mainWindow::mainWindow(sf::RenderWindow& window) : Window(window){

}

mainWindow& mainWindow::getMainWindow(){
    static mainWindow instance;
    return instance;
}


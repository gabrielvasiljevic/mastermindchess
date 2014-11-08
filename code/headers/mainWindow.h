#ifndef _MAINWINDOW
#define _MAINWINDOW
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class mainWindow{
    private:
        //Singleton
        static mainWindow* instance;
        mainWindow(mainWindow const&);
        void operator=(mainWindow const&);
        sf::RenderWindow Window;

    public:

        static mainWindow& getMainWindow();
        sf::RenderWindow& getWindow();
        mainWindow(sf::RenderWindow& window);

} ;



#endif // _MAINWINDOW

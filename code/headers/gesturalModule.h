#ifndef _GESTURAL
#define _GESTURAL
#include "networkHandler.h"

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#ifndef gesturalModule
#define gesturalModule GesturalModule::getGesturalModule()
#endif



class GesturalModule{
    private:
        //Singleton
        static GesturalModule* instance;
        GesturalModule(){x = 0; y = 0;};
        GesturalModule(GesturalModule const&);
        void operator=(GesturalModule const&);

    public:
        int x, y;
        static GesturalModule& getGesturalModule();
        sf::Clock clickClock;
        sf::Clock clickDelayClock;
        UdpSocket               application;
        TcpListener             listener;
        Packet                  packet;
        int clicked;


        void connectToApplication();
        void receiveGesturalMovement();
        int convertCoordinate(int x, int originalX, int goalX, int precision);
        int calculateDistance(int x1, int y1, int x2, int y2);


};

#endif // _MASTER

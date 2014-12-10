#include "headers/gesturalModule.h"
#include <iostream>
#include <math.h>

using namespace std;

extern sf::RenderWindow window;

GesturalModule& GesturalModule::getGesturalModule(){
    static GesturalModule instance;
    return instance;
}

void GesturalModule::connectToApplication(){
    if (application.bind(14293) == Socket::Done) {
        application.setBlocking (false);
        cout << "Gestural Module connected!" << endl;
    }
}


int GesturalModule::calculateDistance(int x1, int y1, int x2, int y2){
    int result = ceil(sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
    cout << "Result: " << result << endl;
    return result;
}


void GesturalModule::receiveGesturalMovement(){
    //Byte buffer[4];
    char buffer [7];
    //int x = 0;
    size_t received;
    sf::IpAddress sender;
    unsigned short port;
    if(application.receive(buffer, 7, received, sender, port) == Socket::Done){
        //cout << "Buffer: [" << (int)buffer[0]  << "][" << (int)buffer[1] << "][" << (int)buffer [2] << "]" <<
        //                "[" << (int)buffer[3]  << "][" << (int)buffer[4] << "][" << (int)buffer [5] << "]" << endl;
        int x1 = (int)buffer[0] + (int)buffer[1]*10 + (int)buffer[2]*100;
        int y1 = (int)buffer[3] + (int)buffer[4]*10 + (int)buffer[5]*100;
        //y1 -= 104;
        x1 = convertCoordinate(x1, 933, 500, 1000);
        y1 = convertCoordinate(y1, 700, 480, 1000);

        y1 *= -1;
        y1 += 970;
        x1 -= 50;
        //Only recognize the click after a certain amount of time
        if(clickClock.getElapsedTime().asMilliseconds() >= 800){
            clickClock.restart();
            if(calculateDistance(x, y, x1, y1) <= 5){
                //This assures that the user do not accidentally clicks 2 times in a row
                if(clickDelayClock.getElapsedTime().asMilliseconds() >= 800){
                    clickDelayClock.restart();
                    clicked = true;
                    cout << "Clicked!" << endl;
                }
            }
            else{
                clicked = false;
            }
            x = x1;
            y = y1;
        }
        else clicked = false;

        sf::Vector2i position(x1, y1);
        sf::Mouse::setPosition(position, window);
        //clicked = (int)buffer[6];
    }
}

int GesturalModule::convertCoordinate(int x, int originalX, int goalX, int precision){
    int x1 = x*precision;
    float rate = ((float)originalX)/goalX;
    rate *= precision;
    x1 *= rate;
    x1 /= precision*precision;
    return x1;
}

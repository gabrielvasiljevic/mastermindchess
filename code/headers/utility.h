#ifndef _UTIL
#define _UTIL

#include "dataTypes.h"

#include <SFML/Network.hpp>
#include <SFML/System.hpp>


using namespace std;

class Utility{
    public:
        static bool isEmpty(std::ifstream& pFile);

        static int StringToNumber ( const string &Text );

        static string getDatestamp (char separator);

        static string getTimestamp ();

        static string getDatestamp (bool date, bool hour);
};


#endif // _UTIL


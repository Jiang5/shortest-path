#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "City.h"
#ifndef MAP_H
#define MAP_H


class Map{
    private:
        std::vector<City*> array, path;
        int distance(City *a, City *b);
        City* closestCity(City * a);
    public:
        Map(std::string filename);
        City* findByName(std::string cityName);
        std::vector<City *> shortestPath(City * start, City * dest);
        unsigned int pathDistance(City * start, City * dest); 



};
#endif
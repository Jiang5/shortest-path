#include <iostream>
#include <string>
#include <list>
#include <vector>


#ifndef CITY_H
#define CITY_H

class City{
  private:
    std::string cityName;
    int xCoor, yCoor;
    
  public:
    std::list<City*> ajacency;
    bool tag = false;
    int dis = 9999;
    City * pre = 0;
    City(std::string cityName, int xCoor,int yCoor);
    std::string getName();
    int getXCoor();
    int getYCoor();
    std::list<City*> getAdjacent();
    bool operator<(City &c);
    void addEdge(City *city);
};


#endif
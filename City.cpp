#include "City.h"

using namespace std;

City::City(string cityName, int xCoor,int yCoor){
    this->cityName = cityName;
    this->xCoor = xCoor;
    this->yCoor = yCoor;
}

std::string City::getName(){
    return this->cityName;    
}

int City::getXCoor(){
    return this->xCoor;
}

int City::getYCoor(){
    return this->yCoor;
}

list<City*> City::getAdjacent(){
    return ajacency;
}

bool City::operator<(City &c){
    return this->getName() < c.getName();
}

void City::addEdge(City *city){
    ajacency.push_back(city);
    return;
}
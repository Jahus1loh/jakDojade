#include <stdio.h>
#include <iostream>
#include "OwnPair.h"
#include "OwnTuple.h"
#include "OwnVector.h"
#include "OwnUnorderedMap.h"
#include "OwnString.hpp"

using namespace std;

class Map {
private:
    ownVector<ownVector<char>> map;
    ownVector<ownVector<int>> passable;
    OwnPair<int, int>* cityCoords;
    ownUnorderedMap<ownString, OwnPair<int, int>> cities;
    int width, height, cityCount;
    ownString cityName;
public:
    Map(ownString input);
    void setWidth(int width);
    void setHeight(int height);
    void createMap(int width, int height);
    void setMap(const ownVector<ownVector<char>>& map);
    void setPassable(const ownVector<ownVector<int>>& passable);
    ownVector<ownVector<char>> getMap();
    bool isOnEdge(int i, int j) const;
    bool isPassable(int i, int j) const;
    bool isCity(int i, int j) const;
    bool isLetter(int i, int j) const;
    ownVector<ownVector<int>> getPassable() const;
    OwnPair<int, int> findWhereIsName(int i, int j);
    OwnPair<int, int> findFirstLetter(int i, int j);
    ownString findCityName(int i, int j);
    void findAllCities();
    void addToUnorderedMap(ownString cityName, OwnPair<int, int> coordinates);
    OwnPair<int, int> getCityCoordinates(ownString cityName);
    ownString getCityNameFromCoords(int x, int y);
    ownVector<OwnPair<int, int>> removeNoneCityCoords(OwnPair<int, int>* routeList, int size);
};

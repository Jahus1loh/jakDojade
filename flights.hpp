#pragma once
#include <iostream>
#include "OwnUnorderedMap.h"
#include "OwnTuple.h"
#include "OwnVector.h"
#include "OwnPair.h"
#include "OwnString.hpp"

using namespace std;

const int INF2 = INT_MAX;

class Flights {
private:
    ownVector<ownVector<int>> graph;
    ownUnorderedMap<ownString, int> cities;
    int cityCount;
    ownVector<ownString> checkedCities;
    ownVector<int> dist;
    ownVector<int> path;
    int start;
    int end;
    struct Node {
        int prev;
        int dist;
        Node() : prev(INF2), dist(-1) {}
        Node(int prev, int dist) : prev(prev), dist(dist) {}
    };
public:
    Flights();
    void addFlight(ownString startCity, ownString destination, int time);
    void addNewCity(ownString cityName);
    void setGraph(const ownVector<ownVector<int>>& graph);
    void setPath(const ownVector<int>& path);
    ownVector<int> getPath() const;
    ownUnorderedMap<ownString, int> getCities() const;
    void readFlights(int numberOfFlights);
    OwnTuple<ownString, ownString, int> readInput(ownString input);
    int dijkstra(ownString startCity, ownString destination);
    int minDistance(const ownVector<bool>& visited, const ownVector<int>& dist);
};

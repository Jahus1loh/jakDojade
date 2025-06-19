#pragma once
#include <iostream>
#include <climits>
#include "OwnPair.h"
#include "OwnVector.h"
#include "OwnQueue.h"

using namespace std;

typedef OwnPair<int, int> pii;

const int INF = INT_MAX;

class ShortestPath {
private:
    ownVector<ownVector<int>> map;
    ownVector<OwnPair<int,int>> path;
    ownVector<ownVector<int>> dist;
    int width;
    int height;
    bool isValid(int x, int y);
    struct Node {
        int x, y, dist;
        Node() : x(0), y(0), dist(0) {}
        Node(int x, int y, int d) : x(x), y(y), dist(d) {}
    };
    ownVector<OwnPair<int,int>> reconstructPath(int startX, int startY, int endX, int endY, ownVector<ownVector<Node>>& prev);
public:
    ShortestPath(ownVector<ownVector<int>> inputMap);
    void setDist(const ownVector<ownVector<int>>& dist);
    void setPath(const ownVector<OwnPair<int, int>>& path);
    ownVector<OwnPair<int, int>> findShortestPath(int startX, int startY, int endX, int endY);
    int djikstra(int startX, int startY, int endX, int endY);
};

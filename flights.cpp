#include "Flights.hpp"

Flights::Flights() {}

void Flights::setGraph(const ownVector<ownVector<int>>& graph) {
    this->graph = graph;
}

void Flights::setPath(const ownVector<int>& path) {
    this->path = path;
}

// add flight to correct position in adjacency matrix
void Flights::addFlight(ownString startCity, ownString destination, int time) {
    int u = cities[startCity];
    int v = cities[destination];
    ownVector<int>& uRow = graph.get(u);
    ownVector<int>& vRow = graph.get(v);
    int vTime = uRow.get(v);
    if (vTime > time || vTime == 0) {
        uRow.set(v, time);
    }
}

ownVector<int> Flights::getPath() const {
    return path;
}

void Flights::addNewCity(ownString cityName) {
    if (cities.count(cityName) == 0) {
        int id = cities.getSize();
        cities.push(cityName, id);
    }
}

void Flights::readFlights(int numberOfFlights) {
    ownVector<OwnTuple<ownString, ownString, int>> resultsList;
    ownString flight;
    cityCount = 0;
    OwnTuple<ownString, ownString, int> result;
    // read all flights and add start, destination and time to resultsList and append new cities to unordered map
    for (int i = 0; i < numberOfFlights; i++) {
        cin >> flight;
        result = readInput(flight);
        resultsList.push(result);
        addNewCity(result.getFirst());
        addNewCity(result.getSecond());
    }
    // initialize a graph of size of number of cities
    for (int i = 0; i < cities.getSize(); i++) {
        ownVector<int> graphRow;
        for (int j = 0; j < cities.getSize(); j++) {
            graphRow.push(0);
        }
        graph.push(graphRow);
    }
    setGraph(graph);
    // add flights to adjacency matrix
    for (int i = 0; i < numberOfFlights; i++) {
        result = resultsList.get(i);
        addFlight(result.getFirst(), result.getSecond(), result.getThird());
    }
}

OwnTuple<ownString, ownString, int> Flights::readInput(ownString input) {
    int whereFirstSpace = input.findPos(' ');
    ownString startCity = input.substring(0, whereFirstSpace);
    startCity.removeSpaces();
    ownString secondString = input.substring(whereFirstSpace + 1, input.getLen());
    int whereSecondSpace = secondString.findPos(' ');
    ownString destination = secondString.substring(0, whereSecondSpace);
    destination.removeSpaces();
    ownString thirdString = secondString.substring(whereSecondSpace + 1, secondString.getLen());
    int time = thirdString.convertToInt();
    return OwnTuple<ownString, ownString, int>(startCity, destination, time);
}

// return index of node with the minimum distance that hasnt been visited yet
int Flights::minDistance(const ownVector<bool>& visited, const ownVector<int>& dist) {
    int minDist = INF2;
    int minIndex = -1;
    for (int i = 0; i < cities.getSize(); i++) {
        if (!visited.get(i) && dist.get(i) < minDist) {
            minDist = dist.get(i);
            minIndex = i;
        }
    }
    return minIndex;
}

int Flights::dijkstra(ownString startCity, ownString destination) {
    ownVector<bool> visited;
    ownVector<Node> nodes;
    ownVector<int> dist;
    ownVector<int> prev;
    
    int numNodes = cities.getSize();
    int start = cities[startCity];
    int end = cities[destination];
    
    // initialize vectors with default values
    for (int i = 0; i < numNodes; i++) {
        visited.push(false);
        nodes.push(Node(-1, INF2));
        dist.push(INF2);
        prev.push(-1);
    }
    // set distance at start to 0 and node at start to node with previous value as start and distance equal to 0
    nodes.set(start, Node(start, 0));
    dist.set(start, 0);
    
    
    for (int i = 0; i < numNodes - 1; i++) {
        // find the unvisited node with the smallest distance
        int u = minDistance(visited, dist);
        if (u == -1 || u == end) {
            break;
        }
        
        visited.set(u, true);
        ownVector<int> graphRow = graph.get(u);
        // get minimum distance to current node
        int distU = dist.get(u);
        for (int j = 0; j < numNodes; j++) {
            // get the weight of the edge from the current node
            int graphJ = graphRow.get(j);
            // check if neighbour was visited and there is weight value and distance is different than INF2 and the distance to the neighbour through current node is smaller than current smallest distance
            if (!visited.get(j) && u != -1 && graphJ && distU != INF2 && distU + graphJ < dist.get(j)) {
                nodes.set(j, Node(u, nodes.get(u).dist + graphJ));
                dist.set(j, distU + graphJ);
            }
        }
    }
    
    // construct a shortest path
    ownVector<int> path;
    int curr = end;
    while (curr != start) {
        path.push(curr);
        curr = nodes.get(curr).prev;
    }
    reverse(path.begin(), path.end());
    setPath(path);
    return nodes.get(end).dist;
}

ownUnorderedMap<ownString, int> Flights::getCities() const {
    return cities;
}

#include <iostream>
#include "Map.hpp"
#include "Flights.hpp"
#include "Dijkstra.hpp"
#include "OwnString.hpp"

using namespace std;

OwnTuple<ownString, ownString, int> readQuery(ownString input) {
    int whereFirstSpace = input.findPos(' ');
    ownString startCity = input.substring(0, whereFirstSpace);
    startCity.removeSpaces();
    ownString secondString = input.substring(whereFirstSpace + 1, input.getLen());
    int whereSecondSpace = secondString.findPos(' ');
    ownString destination = secondString.substring(0, whereSecondSpace);
    destination.removeSpaces();
    ownString thirdString = secondString.substring(whereSecondSpace + 1, secondString.getLen());
    int type = thirdString.convertToInt();
    return OwnTuple<ownString, ownString, int>(startCity, destination, type);
}


int main() {
    ownString input = "";
    OwnTuple<ownString, ownString, int> flight;
    bool printed = false;
    ownString startCity = "";
    ownString destination = "";
    int type = 0;
    int flightConnections = 0;
    int queries = 0;
    // read map dimensions
    cin >> input;
    
    // create a map with dimensions provided in input
    Map myMap(input);
    Flights flightsList;
    ShortestPath findShortestPath(myMap.getPassable());
    
    // read number of flights
    cin >> input;
    
    // if there are no flights skip
    if (input != "0") {
        flightConnections = input.convertToInt();
        flightsList.readFlights(flightConnections);
    }
    
    // read number of queries
    cin >> input;
    queries = input.convertToInt();
    
    for (int i = 0; i < queries; i++) {
        printed = false;
        // read a query
        cin >> input;
        
        flight = readQuery(input);
        startCity = flight.getFirst();
        destination = flight.getSecond();
        type = flight.getThird();
        
        // if start equals destination then there is no distance
        if (startCity == destination) {
            cout << 0 << endl;
        } else {
            // get start and destination coords from the map
            OwnPair<int, int> startCityCoords = myMap.getCityCoordinates(startCity);
            OwnPair<int, int> destinationCoords = myMap.getCityCoordinates(destination);
            
            // find shortest path between those coords
            ownVector<OwnPair<int, int>> path = findShortestPath.findShortestPath(startCityCoords.getFirst(), startCityCoords.getSecond(), destinationCoords.getFirst(), destinationCoords.getSecond());
            int distance = path.getSize() - 1;
            
            // check whether any flights were provided
            if (flightConnections > 0) {
                // find flightTime using dijsktra algorithm on graph represented as adjacency matrix
                int flightTime = flightsList.dijkstra(startCity, destination);
                
                // check if the distance and flightTime have proper values and if flight time is shortert than distance
                if (distance < 1 || (distance > flightTime && flightTime != 0)) {
                    
                    // check type of query and if values weren't printed yet
                    if (type == 1 && !printed) {
                        // get path of a flight
                        ownVector<int> flightPath = flightsList.getPath();
                        // get cities stores in unordered map
                        ownUnorderedMap<ownString, int> citiesMap = flightsList.getCities();
                        
                        // print time of flight
                        cout << flightTime;
                        for (int i = 0; i < flightPath.getSize() - 1; i++) {
                            // search for city name based on its value in unordered map
                            ownString result = citiesMap.searchByValue(citiesMap, flightPath.get(i));
                            cout << " ";
                            cout << result;
                        }
                        cout << endl;
                        printed = true;
                    } else if (!printed) {
                        cout << flightTime << endl;
                        printed = true;
                    }
                }
            }
            if (type == 1 && !printed) {
                // print distance
                cout << distance;
                for (int i = 0; i < path.getSize(); i++) {
                    // find x and y coords from path
                    int coordX = path.get(i).getFirst();
                    int coordY = path.get(i).getSecond();
                    // check whether there is a city on coords x and y
                    if (myMap.isCity(coordX, coordY)) {
                        // get city name from its coords
                        ownString cityName = myMap.getCityNameFromCoords(coordX, coordY);
                        // print city name if its not starting city nor destination
                        if (cityName != startCity && cityName != destination) {
                            cout << " " << cityName;
                        }
                    }
                }
                cout << endl;
            } else if (!printed) {
                cout << distance << endl;
            }
        }
    }

return 0;
}

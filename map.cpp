#include "Map.hpp"

Map::Map(ownString input) {
    int whereSpace = input.findPos(' ');
    int width = input.substring(0, whereSpace).convertToInt();
    int height = input.substring(whereSpace + 1, input.getLen()).convertToInt();
    setWidth(width);
    setHeight(height);
    createMap(width, height);
}

void Map::setWidth(int width) {
    this->width = width;
}

void Map::setHeight(int height) {
    this->height = height;
}

void Map::createMap(int width, int height) {
    cityCount = 0;
    ownVector<ownVector<int>> passable;
    ownVector<ownVector<char>> map;
    cityCoords = new OwnPair<int, int>[height*width];
    for (int i = 0; i < height; i++) {
        ownVector<char> mapRow;
        ownVector<int> passableRow;
        ownString input;
        cin >> input;
        for (int j = 0; j < width; j++) {
            mapRow.push(input[j]);
            // check if input is a city
            if (input[j] == '*') {
                // add new value to city coords
                cityCoords[cityCount] = OwnPair<int, int>(i, j);
                cityCount++;
                // set value of passable[i][j] as 2 indicating city
                passableRow.push(2);
            } else if (input[j] == '#') {
                // set value of passable[i][j] as 1 indicating passable
                passableRow.push(1);
            } else {
                // set value of passable[i][j] as 0 indicating unpassable road
                passableRow.push(0);
            }
        }
        passable.push(passableRow);
        map.push(mapRow);
        setMap(map);
        setPassable(passable);
    }
    findAllCities();
}

void Map::setMap(const ownVector<ownVector<char>>& map) {
    this->map = map;
}

void Map::setPassable(const ownVector<ownVector<int>>& passable) {
    this->passable = passable;
}

bool Map::isCity(int i, int j) const {
    if (map.get(i).get(j) == '*') {
        return true;
    }
    return false;
}

bool Map::isLetter(int i, int j) const {
    char sign = map.get(i).get(j);
    if (sign != '*' && sign != '#' && sign != '.' && sign != '\0') {
        return true;
    }
    return false;
}

OwnPair<int, int> Map::findWhereIsName(int i, int j) {
    int x = i;
    int y = j;
    
    // left and above
    if (x > 0 && y > 0 && isLetter(x - 1, y - 1)) {
        return OwnPair<int, int>(x - 1, y - 1);
    }
    
    // left and below
    if (x < height - 1 && y > 0 && isLetter(x + 1, y - 1)) {
        return OwnPair<int, int>(x + 1, y - 1);
    }
    
    // right and above
    if (x > 0 && y < width - 1 && isLetter(x - 1, y + 1)) {
        return OwnPair<int, int>(x - 1, y + 1);
    }
    
    // right and below
    if (x < height - 1 && y < width - 1 && isLetter(x + 1, y + 1)) {
        return OwnPair<int, int>(x + 1, y + 1);
    }

    // above
    if (x > 0 && isLetter(x - 1, y)) {
        return OwnPair<int, int>(x - 1, y);
    }

    // left
    if (y > 0 && isLetter(x, y - 1)) {
        return OwnPair<int, int>(x, y - 1);
    }

    // right
    if (y < width - 1 && isLetter(x, y + 1)) {
        return OwnPair<int, int>(x, y + 1);
    }

    // below
    if (x < height - 1 && isLetter(x + 1, y)) {
        return OwnPair<int, int>(x + 1, y);
    }
    
    return OwnPair<int, int>(-1, -1);
}

OwnPair<int, int> Map::findFirstLetter(int i, int j) {
    int x = i;
    int y = j;
    // check if current sign is letter until there is left border or the sign isnt letter and return the left-most letter coordinates
    while (y > 0 && isLetter(x, y - 1)) {
        y -= 1;
    }
    return OwnPair<int, int>(x, y);
}

ownString Map::findCityName(int i, int j) {
    OwnPair<int, int> start = findFirstLetter(i, j);
    ownString result = "";
    char buffer[20];
    int k = 0;
    int y = start.getSecond();
    int x = start.getFirst();
    // check if current sign is letter and if yes add it to buffer and move to the next spot on the right
    while (y < width && isLetter(x, y)) {
        char letter = map.get(x).get(y);
        buffer[k] = letter;
        y++;
        k++;
    }
    buffer[k] = '\0';
    result = ownString(buffer);
    return result;
}

void Map::addToUnorderedMap(ownString cityName, OwnPair<int, int> coordinates) {
    cities.push(cityName, coordinates);
}

// find all cities that are on the map and add them to an unordered map
void Map::findAllCities() {
    for (int i = 0; i < cityCount; i++) {
        int cityX = cityCoords[i].getFirst();
        int cityY = cityCoords[i].getSecond();
        OwnPair<int, int> nameCoords = findWhereIsName(cityX, cityY);
        ownString cityName = findCityName(nameCoords.getFirst(), nameCoords.getSecond());
        addToUnorderedMap(cityName, OwnPair<int, int>(cityX, cityY));
    }
}

OwnPair<int, int> Map::getCityCoordinates(ownString cityName) {
    return cities[cityName];
}


ownVector<ownVector<int>> Map::getPassable() const {
    return passable;
}

// returns key which has values x,y assigned to it
ownString Map::getCityNameFromCoords(int x, int y) {
    return cities.searchByValue(cities, OwnPair<int, int>(x, y));
}


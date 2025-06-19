# Jak Dojade? – Pathfinding in a City Map

## Overview

This C++ project solves a pathfinding problem on a rectangular grid-based map with cities, roads, and one-way flights using **Dijkstra’s algorithm**. It is designed to meet strict constraints such as **no STL containers**, **no `std::string`**, and includes **custom implementations of common structures**.

The goal is to compute the shortest travel time between two cities, optionally providing the route.

## Problem Description

* The map is a grid where each cell is either:

  * `.`: impassable
  * `#`: road (passable)
  * `*`: a part of a city (passable)
  * letter/number: part of a city name (impassable)
* Movement is only allowed between side-adjacent cells.
* Some cities are connected via **one-way air routes** with specific travel times.
* The shortest path can include walking and flying.

## Input Format

```
w h               # map width and height
<map rows>        # h lines of w characters each
k                 # number of air routes
<k lines>         # air routes: from_city to_city time
q                 # number of queries
<q lines>         # queries: from_city to_city type (0 = time only, 1 = time + path)
```

## Output Format

```
<shortest time> [<intermediate cities if type==1>]
```

## Example

**Input:**

```
20 20
.........GDANSK.....
........*...........
........#...........
...
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1
```

**Output:**

```
5
40
40 KIELCE SZCZECIN
```

## Project Structure

```
.
├── main.cpp              # Program entry and logic integration
├── dijkstra.cpp/hpp      # Dijkstra's shortest path algorithm
├── flights.cpp/hpp       # One-way flight handling
├── map.cpp/hpp           # Map/grid and movement handling
├── ownpair.h             # Custom pair data type
├── ownqueue.h            # Custom queue implementation
├── ownstring.cpp         # Custom string handling
```

## Compilation

```bash
g++ -std=c++17 -o jakdojade main.cpp dijkstra.cpp flights.cpp map.cpp ownstring.cpp
./jakdojade < input.txt > output.txt
```

## License

This project is educational and used in academic contest settings. Redistribution requires author attribution.

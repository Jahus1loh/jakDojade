#include "Dijkstra.hpp"

ShortestPath::ShortestPath(ownVector<ownVector<int>> inputMap) {
    map = inputMap;
    height = map.getSize();
    width = map.get(0).getSize();
}

bool ShortestPath::isValid(int x, int y) {
    return (x >= 0 && x < height && y >= 0 && y < width);
}

ownVector<OwnPair<int,int>> ShortestPath::reconstructPath(int startX, int startY, int endX, int endY, ownVector<ownVector<Node>> &prev) {
    ownVector<OwnPair<int, int>> path;
    OwnPair<int, int> curr(endX, endY);
    OwnPair<int, int> start(startX, startY);
    while (curr != start) {
        // add current point to path
        path.push(curr);
        // set current point to previous node in the shortest path
        curr = OwnPair<int, int>(prev.get(curr.getFirst()).get(curr.getSecond()).x, prev.get(curr.getFirst()).get(curr.getSecond()).y);
    }
    // add starting point to path
    path.push(start);
    // reverse the path
    reverse(path.begin(), path.end());
    return path;
}

void ShortestPath::setDist(const ownVector<ownVector<int>>& dist) {
    this->dist = dist;
}

void ShortestPath::setPath(const ownVector<OwnPair<int, int>>& path) {
    this->path = path;
}

ownVector<OwnPair<int, int>> ShortestPath::findShortestPath(int startX, int startY, int endX, int endY) {
    ownVector<ownVector<Node>> prev;
    ownVector<ownVector<int>> dist;
    
    // initialize prev and dist vectors
    for (int i = 0; i < height; i++) {
        ownVector<Node> prevRow;
        ownVector<int> distRow;
        for (int j = 0; j < width; j++) {
            distRow.push(-1);
            prevRow.push(Node(-1, -1, -1));
        }
        prev.push(prevRow);
        dist.push(distRow);
    }
    setDist(dist);
    setPath(path);
    // create a queue to store nodes to be visited
    ownQueue<Node> queue;
    OwnPair<int, int> start(startX, startY);
    OwnPair<int, int> end(endX, endY);
    // push starting node to queue
    queue.push(Node(start.getFirst(), start.getSecond(), 0));
    // set distance to starting point to 0
    dist.get(start.getFirst()).set(start.getSecond(), 0);
    
    // check nodes until queue is empty
    while (!queue.empty()) {
        // get next node from queue and then remove it
        Node curr = queue.front();
        queue.pop();
        
        // check if curr x and y are equal to end x and y and if yes reconstruct path
        if (curr.x == end.getFirst() && curr.y == end.getSecond()) {
            path = reconstructPath(start.getFirst(), start.getSecond(), end.getFirst(), end.getSecond(), prev);
            return path;
        }
        
        // loop through each neighbour
        for (int drow = -1; drow <= 1; drow++) {
            for (int dcol = -1; dcol <= 1; dcol++) {
                // check if cell is valid to visit
                if (abs(drow) + abs(dcol) == 1 && isValid(curr.x + drow, curr.y + dcol) && map.get(curr.x + drow).get(curr.y + dcol) != 0) {
                    // calculate distance to neighbour cell
                    int newDist = curr.dist + 1;
                    // check if the neighbour wasnt visited or newdist is smaller than current one
                    if (dist.get(curr.x + drow).get(curr.y + dcol) == -1 || newDist < dist.get(curr.x + drow).get(curr.y + dcol)) {
                        // set dist to newDist and previous distance to current one and add new node to queue with coordinates of neighour and newDist
                        dist.get(curr.x + drow).set(curr.y + dcol, newDist);
                        prev.get(curr.x + drow).set(curr.y + dcol, curr);
                        queue.push(Node(curr.x + drow, curr.y + dcol, newDist));
                    }
                }
            }
        }
    }
    return path;
}

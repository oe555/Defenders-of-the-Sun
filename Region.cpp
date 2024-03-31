#include <vector>
#include <map>
#include "Location.h"
#include "Region.h"

Region::Region(){
    adj = {};
    locations = {};
    visitArray = {};
}

void Region::addLocation(Location location){
    locations.push_back(location);
    visitArray.push_back(false);
}

void Region::addConnection(int firstLocation, int secondLocation){
    adj[firstLocation].push_back(secondLocation);
    adj[secondLocation].push_back(firstLocation);
}

std::vector<int> Region::getAdj(int locationIndex){
    return adj[locationIndex];
}

Location Region::getLocation(int index){
    return locations[index];
}

bool Region::hasBeenVisited(int index){
    return visitArray[index];
}

void Region::markAsVisited(int index){
    visitArray[index] = true;
}
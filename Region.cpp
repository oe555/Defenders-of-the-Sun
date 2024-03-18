#include <vector>
#include <map>
#include "Location.h"
#include "Region.h"

Region::Region(){
    adj = {};
    locations = {};
}

void Region::addLocation(Location location){
    locations.push_back(location);
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
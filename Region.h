#ifndef REGION_H
#define REGION_H

#include <vector>
#include <map>
#include "Location.h"
#include "Rest.h"

class Region{
private:
    // adj[i] = locations adjacent to i
    std::map<int, std::vector<int>> adj;

    std::vector<bool> visitArray;
public:
    // Maps integers to corresponding locations... locations[0] is the starting location and locations[n-1] is the end
    std::vector<Location> locations;
    // This is the rest that happens at the end of this region
    Rest endingRest;

    Region();

    void addLocation(Location location);
    void addConnection(int firstLocation, int secondLocation);

    std::vector<int> getAdj(int locationIndex);
    Location getLocation(int index); // Probably not needed

    bool hasBeenVisited(int index);
    void markAsVisited(int index);
};

#endif
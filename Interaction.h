#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <vector>
#include <map>
#include "Dialogue.h"

class Interaction{
private:
    // We run these dialogues and use the return values to decide what to do
    std::vector<Dialogue> dialogues;
    // The navigator maps an index and a return value to another index
    std::map<std::pair<int, int>, int> interactionNavigator;

    // This is special stuff that might be needed when the interaction ends
    // ADDING THESE THINGS IS A TODO
public:
    Interaction(std::vector<Dialogue> dialogues_);

    // Adds to the navigator
    void addNav(int oldIndex, int returnVal, int newIndex);

    // Runs the interaction (takes in meta to get player stats and stuff). The return value decides if something special happens
    int runInteraction(Meta meta);
};

#endif
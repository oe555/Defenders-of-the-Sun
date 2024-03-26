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

    // {{old id, {new id, type}},{name, description}}. An old id of -1 means new quest, a new id of -1 means quest is complete
    std::vector<std::pair<std::pair<int, std::pair<int, int>>, std::pair<std::string, std::string>>> questUpdates;
    // This is the companion that joins the party if that's a result
    Companion companion;
    // Story variable update
    int storyVariableUpdate;

    Weapon weapon;
    Armor armor;
    int silver;
public:
    Interaction(std::vector<Dialogue> dialogues_);
    Interaction();

    // Adds to the navigator
    void addNav(int oldIndex, int returnVal, int newIndex);

    // Runs the interaction (takes in meta to get player stats and stuff). The return value decides if something special happens
    // Return values: 0 - Nothing, 1 - Encounter, 2 - Companion, 3 - Silver, 4 - Weapon, 5 - Armor, 6 - Quest
    int runInteraction(Meta &meta);

    // Special stuff
    void addQuestUpdate(int oldId, int newId, int type, std::string name, std::string description);
    void addCompanion(std::string name, std::string deity);
    void addWeapon(Weapon weapon_);
    void addArmor(Armor armor_);
    void setSilver(int silver_);
    void setStoryVariableUpdate(int storyVariableUpdate_);
};

#endif
#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include "Interaction.h"
#include "Enemy.h"

class Location{
private:
    bool hasPrimaryInteraction;
    bool hasPostEncounterInteraction;
    Interaction primaryInteraction;
    Interaction postEncounterInteraction; // This interaction runs after an econunter (if there is one)

    std::vector<Enemy> encounter;

    int numOptionalInteractions;
    // The string is what is displayed in the menu when the player is selecting what to do at the location
    std::vector<std::pair<std::string, Interaction>> optionalInteractions;
public:
    Location();

    bool getHasPrimaryInteraction();
    bool getHasPostEncounterInteraction();

    Interaction getPrimaryInteraction();
    void setPrimaryInteraction(Interaction interaction_);

    Interaction getPostEncounterInteraction();
    void setPostEncounterInteraction(Interaction interaction_);

    std::vector<Enemy> getEnemies();
    void addEnemy(Enemy enemy_);

    int getNumOptionalInteractions();
    // The string is what is displayed in the menu when the player is selecting what to do at the location
    std::pair<std::string, Interaction> getOptionalInteraction(int index_);
    // The string is what is displayed in the menu when the player is selecting what to do at the location
    void addOptionalInteraction(std::pair<std::string, Interaction> interaction_);
};

#endif
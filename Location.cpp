#include "Location.h"
#include <string>

Location::Location(){
    hasPrimaryInteraction = false;
    hasPostEncounterInteraction = false;
    encounter = {};
    optionalInteractions = {};
    numOptionalInteractions = 0;
    // Interaction has a default constructor
}

bool Location::getHasPrimaryInteraction(){
    return hasPrimaryInteraction;
}

bool Location::getHasPostEncounterInteraction(){
    return hasPostEncounterInteraction;
}

Interaction Location::getPrimaryInteraction(){
    return primaryInteraction;
}

void Location::setPrimaryInteraction(Interaction interaction_){
    hasPrimaryInteraction = true;
    primaryInteraction = interaction_;
}

Interaction Location::getPostEncounterInteraction(){
    return postEncounterInteraction;
}

void Location::setPostEncounterInteraction(Interaction interaction_){
    hasPostEncounterInteraction = true;
    postEncounterInteraction = interaction_;
}

std::vector<Enemy> Location::getEnemies(){
    return encounter;
}

void Location::addEnemy(Enemy enemy_){
    encounter.push_back(enemy_);
}

int Location::getNumOptionalInteractions(){
    return numOptionalInteractions;
}

std::pair<std::string, Interaction> Location::getOptionalInteraction(int index_){
    return optionalInteractions[index_];
}

void Location::addOptionalInteraction(std::pair<std::string, Interaction> interaction_){
    numOptionalInteractions++;
    optionalInteractions.push_back(interaction_);
}



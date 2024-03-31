#include "Armor.h"
#include <string>

Armor::Armor(){
    name = "";
    description = "";
    defenseBonus = 0;
    isClothes = false;
}

Armor::Armor(std::string name_, std::string description_, int defenseBonus_, bool isClothes_){
    name = name_;
    description = description_;
    defenseBonus = defenseBonus_;
    isClothes = isClothes_;
}

std::string Armor::getName(){
    return name;
}

void Armor::setName(std::string name_){
    name = name_;
}

std::string Armor::getDescription(){
    return description;
}

void Armor::setDescription(std::string description_){
    description = description_;
}

int Armor::getDefenseBonus(){
    return defenseBonus;
}

void Armor::setDefenseBonus(int defenseBonus_){
    defenseBonus = defenseBonus_;
}

bool Armor::getIsClothes(){
    return isClothes;
}
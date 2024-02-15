#include "Weapon.h"
#include <string>

Weapon::Weapon(){
    name = "";
    description = "";
    attackDice = 0;
    attackMultiplier = 0;
    attackBonus = 0;
    precisionBonus = 0;
}

Weapon::Weapon(std::string name_, std::string description_, int attackDice_, int attackMultiplier_, int attackBonus_, int precisionBonus_){
    name = name_;
    description = description_;
    attackDice = attackDice_;
    attackMultiplier = attackMultiplier_;
    attackBonus = attackBonus_;
    precisionBonus = precisionBonus_;
}

std::string Weapon::getName(){
    return name;
}

void Weapon::setName(std::string name_){
    name = name_;
}

std::string Weapon::getDescription(){
    return description;
}

void Weapon::setDescription(std::string description_){
    description = description_;
}

int Weapon::getAttackDice(){
    return attackDice;
}

void Weapon::setAttackDice(int attackDice_){
    attackDice = attackDice_;
}

int Weapon::getAttackMultiplier(){
    return attackMultiplier;
}

void Weapon::setAttackMultiplier(int attackMultiplier_){
    attackMultiplier = attackMultiplier_;
}

int Weapon::getAttackBonus(){
    return attackBonus;
}

void Weapon::setAttackBonus(int attackBonus_){
    attackBonus = attackBonus_;
}

int Weapon::getPrecisionBonus(){
    return precisionBonus;
}

void Weapon::setPrecisionBonus(int precisionBonus_){
    precisionBonus = precisionBonus_;
}

int Weapon::dealDamage(){
    //srand(time(NULL));
    return (attackMultiplier * ((rand() % attackDice) + 1)) + attackBonus; 
}
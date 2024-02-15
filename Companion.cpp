#include "Companion.h"
#include "Armor.h"
#include "Weapon.h"
#include <string>
#include <vector>
#include <iostream>

Companion::Companion(std::string name_, std::string type_){
    name = name_;
    type = type_;
    addAction("Attack");
    addAction("Drink Protein");
    maxHealth = 5;
    defense = 3;
    if(type == "Barbarian") defense++;
    if(type == "Wizard") defense--;
    if(type == "Rogue") defense--;
    if(type == "Paladin") defense += 2;
    level = 0; // Constructor creates a level 1 character
    levelUp();
    health = maxHealth;
    Weapon starterWeapon = Weapon("Simple Dagger", "A simple dagger made for simple stabbing.", 6, 1, 0, 0);
    if(type == "Monk") starterWeapon = Weapon("Fist", "Ready to beat the shit out of something.", 6, 1, 0, 1);
    Armor starterArmor = Armor("Simple Clothes", "It might be useless but it's quite fashionable.", 0);
    weapon = starterWeapon;
    armor = starterArmor;
}

std::string Companion::getName(){
    return name;
}

void Companion::setName(std::string name_){
    name = name_;
}

std::string Companion::getType(){
    return type;
}
    
void Companion::setType(std::string type_){
    type = type_;
}

std::vector<std::string> Companion::getActions(){
    return actions;
}

void Companion::addAction(std::string action_){
    actions.push_back(action_);
}

void Companion::removeAction(std::string action_){
    for(int i = 0; i < (int)actions.size(); i++){
        if(actions[i] == action_){
            actions.erase(actions.begin() + i);
        }
    }
}

int Companion::getMaxHealth(){
    return maxHealth;
}

void Companion::setMaxHealth(int maxHealth_){
    maxHealth = maxHealth_;
}

int Companion::getHealth(){
    return health;
}

void Companion::setHealth(int health_){
    health = health_;
}

int Companion::getDefense(){
    return defense;
}

void Companion::setDefense(int defense_){
    defense = defense_;
}

int Companion::getLevel(){
    return level;
}

void Companion::levelUp(){
    level++;
    if(type == "Barbarian") maxHealth += 4;
    if(type == "Wizard") maxHealth += 2;
    if(type == "Rogue") maxHealth += 2;
    if(type == "Druid") maxHealth += 3;
    if(type == "Necromancer") maxHealth += 2;
    if(type == "Monk") maxHealth += 3;
    if(type == "Cleric") maxHealth += 3;
    if(type == "Paladin") maxHealth += 5;
    if(level == 1){
        if(type == "Rogue") addAction("Hide");
        if(type == "Cleric") addAction("Heal");
    }
}

bool Companion::isHiding(){
    return hiding;
}

void Companion::setHiding(bool hiding_){
    hiding = hiding_;
}

Weapon Companion::getWeapon(){
    return weapon;
}
    
void Companion::setWeapon(Weapon weapon_){
    if(type == "Monk") return;
    weapon = weapon_;
}

Armor Companion::getArmor(){
    return armor;
}

void Companion::setArmor(Armor armor_){
    if(type == "Monk") return;
    armor = armor_;
}

int Companion::dealDamage(){
    bool hidingTemp = hiding;
    hiding = false;
    return weapon.dealDamage() + (hidingTemp ? 2*level : 0);
}

bool Companion::takeDamage(int damage){
    if(hiding) return false; // This should never happen
    //srand(time(NULL));
    if(((rand() % 10) + 1) > defense){
        health -= damage;
        return true;
    }
    return false;
}

void Companion::getDetails(){
    std::cout << name << "'s current level: " << level << "\n";
    std::cout << name << "'s class: " << type << "\n";
    std::cout << name << "'s max health: " << maxHealth << "\n";
    std::cout << name << "'s defense: " << defense << "\n\n";

    std::cout << name << "'s equipment:\n";
    std::cout << "Weapon: " << weapon.getName() << "\n";
    std::cout << "-- " << weapon.getDescription() << "\n";
    std::cout << "Damage: " << weapon.getAttackMultiplier() << "d" << weapon.getAttackDice() << " + " << weapon.getAttackBonus() << "\n";
    std::cout << "Armor: " << armor.getName() << "\n";
    std::cout << "-- " << armor.getDescription() << "\n";
    std::cout << "Defense bonus: " << armor.getDefenseBonus() << "\n"; 
}
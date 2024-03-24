#include "Companion.h"
#include "Armor.h"
#include "Weapon.h"
#include <string>
#include <vector>
#include <iostream>

Companion::Companion(){}

Companion::Companion(std::string name_, std::string type_, std::string deity_){
    name = name_;
    type = type_;
    deity = deity_;
    addAction("Attack");
    addAction("Drink Protein");
    maxHealth = 0;

    if(type == "Barbarian") maxHealth = 23;
    if(type == "Wizard") maxHealth = 12;
    if(type == "Rogue") maxHealth = 15;
    if(type == "Druid") maxHealth = 18;
    if(type == "Hunter") maxHealth = 18;
    if(type == "Monk") maxHealth = 17;
    if(type == "Cleric") maxHealth = 20;
    if(type == "Paladin") maxHealth = 25;
    if(type == "Artisan") maxHealth = 15;
    if(type == "Explorer") maxHealth = 15;
    
    if(type == "Noam") maxHealth = 11;
    if(type == "Shrugmini") maxHealth = 17;
    if(type == "Vivian") maxHealth = 19;
    if(type == "Raven") maxHealth = 16;
    if(type == "Huburt") maxHealth = 16;
    if(type == "Iris") maxHealth = 25;

    defense = 3; // Everyone has base 3 defense
    if(type == "Barbarian") defense++;
    if(type == "Wizard") defense--;
    if(type == "Rogue") defense--;
    if(type == "Paladin") defense += 2;
    level = 0; // Constructor creates a level 0 character
    // levelUp();
    health = maxHealth;
    Weapon starterWeapon = Weapon("Simple Dagger", "A simple dagger made for simple stabbing.", 6, 1, 0, 0);
    if(type == "Monk") starterWeapon = Weapon("Fist", "Ready to beat the shit out of something.", 6, 1, 0, 1);
    Armor starterArmor = Armor("Simple Clothes", "It might be useless but it's quite fashionable.", 0);
    weapon = starterWeapon;
    armor = starterArmor;
    resetStatusEffects();
}

void Companion::resetStatusEffects(){
    hiding = false;
    raging = false;
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

std::string Companion::getDeity(){
    return deity;
}
    
void Companion::setDeity(std::string deity_){
    deity = deity_;
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
    std::cout << "\n#-----#-----#\n\n";
    const std::string boldtext("\033[0;1m");
    const std::string resettext("\033[0;0m");
    level++;
    std::cout << boldtext << name << " is now level " << level << "!\n\n" << resettext;
    /*
        LEVEL 1
    */
    if(level == 1){ // TODO: Expand as the game gets longer
        if(type == "Barbarian"){
            addAction("Rage");
            std::cout << name << " can now use " << boldtext << "rage" << resettext << ". \nEnemies cannot miss attacks against you when you rage, but your attacks deal extra damage equal to 4 + your level.\n\n";
        }
        if(type == "Wizard"){
            addAction("Zap");
            std::cout << name << " can now use " << boldtext << "zap" << resettext << ". \nZap cannot miss and always deals damage equal to 2 times your level.\n\n";
        }
        if(type == "Rogue"){
            addAction("Hide");
            std::cout << name << " can now use " << boldtext << "hide" << resettext << ". \nEnemies cannot hit you while you are hiding. Attacking while hiding causes you to stop hiding but deals extra damage equal to 2 times your level.\n\n";
        }
        if(type == "Druid"){
            addAction("Snake Bite");
            std::cout << name << " can now use " << boldtext << "snake bite" << resettext << ". \nSnake bite inflicts poison onto an enemy, which deals 1d4 damage per turn but cannot kill.\n\n";
        }
        if(type == "Cleric"){
            addAction("Heal");
            std::cout << name << " can now use " << boldtext << "heal" << resettext << ". \nHeal restores HP to any ally equal to 5 + your level (potentially restoring their consciousness).\n\n";
        }
    }
    std::string trashLine;
    std::cout << "<Press Enter to continue>";
    getline(std::cin, trashLine);
    std::cout << "\n#-----#-----#\n";
}

Weapon Companion::getWeapon(){
    return weapon;
}
    
void Companion::setWeapon(Weapon weapon_){
    // TODO output something to player
    if(type == "Monk") return;
    weapon = weapon_;
}

Armor Companion::getArmor(){
    return armor;
}

void Companion::setArmor(Armor armor_){
    // TODO output something to player
    if(type == "Monk") return;
    armor = armor_;
}

// Returns damage based on the weapon and handles status effect related things
int Companion::dealDamage(){
    bool hidingTemp = hiding; // Damage increases by 2*level if the companion is hiding
    hiding = false; // Companion can't hide through an attack
    return weapon.dealDamage() + (hidingTemp ? 2*level : 0) + (raging ? 4+level : 0);
}

// The companion will take damage only if the attack hits (based on a d10 and the defense)
bool Companion::takeDamage(int damage){
    if(hiding) return false; // This should never happen based on how encounters are implemented
    if(((rand() % 10) + 1) > defense || raging){ // Always take damage while raging
        health -= damage;
        health = std::max(health, 0); // We never go to negative HP
        return true;
    }
    return false;
}

// Outputs details to the terminal
void Companion::getDetails(){
    std::cout << name << "'s current level: " << level << "\n";
    std::cout << name << "'s class: " << type << "\n";
    std::cout << name << "'s health: " << maxHealth << "\n";
    std::cout << name << "'s defense: " << defense << "\n\n";

    std::cout << name << "'s equipment:\n";
    std::cout << "Weapon: " << weapon.getName() << "\n";
    std::cout << "-- " << weapon.getDescription() << "\n";
    std::cout << "Damage: " << weapon.getAttackMultiplier() << "d" << weapon.getAttackDice() << " + " << weapon.getAttackBonus() << "\n";
    std::cout << "Armor: " << armor.getName() << "\n";
    std::cout << "-- " << armor.getDescription() << "\n";
    std::cout << "Defense bonus: " << armor.getDefenseBonus() << "\n"; 
}
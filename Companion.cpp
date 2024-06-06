#include "Companion.h"
#include "Armor.h"
#include "Weapon.h"
#include <string>
#include <vector>
#include <iostream>

Companion::Companion(){}

Companion::Companion(std::string name_, std::string type_, std::string deity_){
    approval = 0;
    name = name_;
    type = type_;
    deity = deity_;
    addAction("Attack");
    if(type_ != "Wolf") addAction("Drink Protein");
    maxHealth = 0;
    attackCount = 1;
    agonizeCount = 1;

    if(type == "Barbarian") maxHealth = 23;
    if(type == "Wizard") maxHealth = 12;
    if(type == "Rogue") maxHealth = 15;
    if(type == "Druid") maxHealth = 18;
    if(type == "Hunter") maxHealth = 18;
    if(type == "Wolf") maxHealth = 15;
    if(type == "Monk") maxHealth = 17;
    if(type == "Cleric") maxHealth = 20;
    if(type == "Paladin") maxHealth = 25;
    if(type == "Artisan") maxHealth = 15;
    if(type == "Explorer") maxHealth = 15;
    
    if(type == "Noam") maxHealth = 11;
    if(type == "Shrugmini") maxHealth = 17;
    if(type == "Vivian") maxHealth = 19;
    if(type == "Raven") maxHealth = 16;
    if(type == "Hubert") maxHealth = 16;
    if(type == "Iris") maxHealth = 25;

    defense = 3; // Everyone has base 3 defense
    if(type == "Barbarian") defense++;
    if(type == "Wizard") defense--;
    if(type == "Rogue") defense--;
    if(type == "Paladin") defense += 2;
    if(type == "Iris") defense += 2;
    if(type == "Noam") defense--;
    level = 0; // Constructor creates a level 0 character
    // levelUp();
    health = maxHealth;
    Weapon starterWeapon = Weapon("Simple Dagger", "A simple dagger made for simple stabbing.", 6, 1, 0, 0, {"Dagger"});
    if(type == "Monk") starterWeapon = Weapon("Fist", "Ready to beat the shit out of something.", 6, 1, 0, 1, {"Fist"});
    if(type == "Wolf") starterWeapon = Weapon("Teeth", "Chomp!!!", 6, 1, 0, 3, {"Teeth"});
    if(type == "Noam") starterWeapon = Weapon("Noam's Quarterstaff", "Good for magic, but also good for bonking things.", 4, 1, 0, -1, {"Quarterstaff"}); 
    if(type == "Shrugmini") starterWeapon = Weapon("Shrugmini\'s Dagger", "A nicer dagger made for nicer stabbing.", 6, 1, 1, 1, {"Dagger"});
    Armor starterArmor = Armor("Simple Clothes", "It might be useless but it's quite fashionable.", 0, true);
    if(type == "Raven") starterArmor = Armor("Raven\'s Clothes", "If wearing a hoodie at a funeral was acceptable, this is what you\'d wear.", 0, true);
    if(type == "Vivian") starterArmor = Armor("Vivan\'s Clothes", "A white top and skirt dedicated to Her.", 0, true);
    if(type == "Hubert") starterArmor = Armor("Hubert\'s Clothes", "Ripped jeans and a awkwardly colored jacket.", 0, true);
    if(type == "Noam") starterArmor = Armor("Noam\'s Clothes", "Who managed to design a robe that fits him?", 0, true);
    if(type == "Shrugmini") starterArmor = Armor("Shrugmini\'s Clothes", "Cool girl vibes.", 0, true);
    if(type == "Iris") starterArmor = Armor("Iris\' Armor", "It has the symbol of Solari on the left shoulder.", 1, false);
    if(type == "Wolf") starterArmor = Armor("Fur", "Rawr!!!", 0, false);
    weapon = starterWeapon;
    armor = starterArmor;
    resetStatusEffects();
}

void Companion::resetStatusEffects(){
    hiding = false;
    raging = false;
    inspired = false;
    healUsed = false;
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
            std::cout << name << " can now use " << boldtext << "Rage" << resettext << ". \nEnemies will always miss attacks against you when you rage, but your attacks deal extra damage equal to 4 + your level.\n\n";
        }
        if(type == "Wizard" || type == "Noam"){
            addAction("Zap");
            std::cout << name << " can now use " << boldtext << "Zap" << resettext << ". \nZap cannot miss and always deals 5 damage.\n\n";
        }
        if(type == "Rogue" || type == "Shrugmini"){
            addAction("Hide");
            std::cout << name << " can now use " << boldtext << "Hide" << resettext << ". \nEnemies cannot hit you while you are hiding, but may still try to target you.\nAttacking while hiding causes you to stop hiding but deals extra damage equal to 2 times your level and guarantees a hit.\n\n";
        }
        if(type == "Druid" || type == "Vivian"){
            addAction("Snake Bite");
            std::cout << name << " can now use " << boldtext << "Snake Bite" << resettext << ". \nSnake bite cannot miss and inflicts poison onto an enemy, which deals 1d4 damage per turn but cannot kill.\n\n";
        }
        if(type == "Monk"){
            increaseAttackCount();
            std::cout << name << " has gained an extra attack.\n\n";
        }
        if(type == "Cleric" || type == "Vivian"){
            addAction("Heal");
            std::cout << name << " can now use " << boldtext << "Heal" << resettext << ". \nHeal uses the caster's adrenaline and thus can only be used during combat.\nThe first heal of each combat restores HP equal to 5 + your level to any ally (potentially restoring their consciousness).\nEach heal after the first heal only restores 1 HP.\n\n";
        }
        if(type == "Raven"){
            addAction("Agonize");
            std::cout << name << " can now use " << boldtext << "Agonize" << resettext << ". \nAgonize is a beam of dark energy that deals damage equal to 3 times your level.\n\n";
        }
        if(type == "Hubert"){
            addAction("Inspire");
            std::cout << name << " can now use " << boldtext << "Inspire" << resettext << ". \nYou can perform an inspiring tune using your bagpipes, increasing the damage of an ally's attacks by 1 + your level.\n\n";
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
    if(type == "Monk") return;
    if(type == "Wolf") return;
    weapon = weapon_;
}

Armor Companion::getArmor(){
    return armor;
}

void Companion::setArmor(Armor armor_){
    if(type == "Monk") return;
    if(type == "Wolf") return;
    armor = armor_;
}

// Returns damage based on the weapon and handles status effect related things
int Companion::dealDamage(){
    bool hidingTemp = hiding; // Damage increases by 2*level if the companion is hiding
    hiding = false; // Companion can't hide through an attack
    return weapon.dealDamage() + (hidingTemp ? 2*level : 0) + (raging ? 4+level : 0) + (inspired ? 1+level : 0);
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
    std::string tempType = type;
    if(type == "Raven") tempType = "Witch";
    if(type == "Hubert") tempType = "Musician";
    if(type == "Vivian") tempType = "Archdruid";
    if(type == "Shrugmini") tempType = "Half-Devil Rogue";
    if(type == "Noam") tempType = "Wizard";
    if(type == "Iris") tempType = "Paladin";
    if(deity != "None") tempType = tempType + " of " + deity;

    std::cout << name << "'s current level: " << level << "\n";
    std::cout << name << "'s class: " << tempType << "\n";
    std::cout << name << "'s health: " << health << "\n";
    std::cout << name << "'s max health: " << maxHealth << "\n";
    std::cout << name << "'s defense: " << defense << "\n\n";

    std::cout << name << "'s equipment:\n";
    std::cout << "Weapon: " << weapon.getName() << "\n";
    std::cout << "-- " << weapon.getDescription() << "\n";
    std::cout << "Damage: " << weapon.getAttackMultiplier() << "d" << weapon.getAttackDice() << " + " << weapon.getAttackBonus() << "\n";
    std::cout << "Precision bonus: " << weapon.getPrecisionBonus() << "\n\n";
    std::cout << "Armor: " << armor.getName() << "\n";
    std::cout << "-- " << armor.getDescription() << "\n";
    std::cout << "Defense bonus: " << armor.getDefenseBonus() << "\n"; 
}

void Companion::increaseAttackCount(){
    attackCount++;
}

int Companion::getAttackCount(){
    return attackCount;
}

void Companion::increaseAgonizeCount(){
    agonizeCount++;
}

int Companion::getAgonizeCount(){
    return agonizeCount;
}

void Companion::adjustApproval(int change){
    approval += change;
}

int Companion::getApproval(){
    return approval;
}
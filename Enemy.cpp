#include "Enemy.h"
#include <string>

Enemy::Enemy(std::string name_, int health_, int defense_, int attackDice_, int attackMultiplier_, int attackBonus_, bool intelligent_){
    name = name_;
    health = health_;
    defense = defense_;
    attackDice = attackDice_;
    attackMultiplier = attackMultiplier_;
    attackBonus = attackBonus_;
    intelligent = intelligent_;
    statusEffects = {};
}

std::string Enemy::getName(){
    return name;
}

void Enemy::setName(std::string name_){
    name = name_;
}

int Enemy::getHealth(){
    return health;
}

void Enemy::setHealth(int health_){
    health = health_;
}

int Enemy::getDefense(){
    return defense;
}

void Enemy::setDefense(int defense_){
    defense = defense_;
}

int Enemy::getAttackDice(){
    return attackDice;
}

void Enemy::setAttackDice(int attackDice_){
    attackDice = attackDice_;
}

int Enemy::getAttackMultiplier(){
    return attackMultiplier;
}

void Enemy::setAttackMultiplier(int attackMultiplier_){
    attackMultiplier = attackMultiplier_;
}

int Enemy::getAttackBonus(){
    return attackBonus;
}

void Enemy::setAttackBonus(int attackBonus_){
    attackBonus = attackBonus_;
}

bool Enemy::isIntelligent(){
    return intelligent;
}

void Enemy::setIntelligent(bool intelligent_){
    intelligent = intelligent_;
}

int Enemy::dealDamage(){
    //srand(time(NULL));
    return (attackMultiplier * ((rand() % attackDice) + 1)) + attackBonus; 
}

// Returns true if hit is successful
bool Enemy::takeDamage(int damage, int precisionBonus){
    //srand(time(NULL));
    if(((rand() % 10) + 1) + precisionBonus > defense){
        health -= damage;
        health = std::max(health, 0); // We never go to negative HP
        return true;
    }
    return false;
}

void Enemy::addStatusEffect(std::string effect){
    statusEffects.push_back(effect);
}

bool Enemy::hasStatusEffect(std::string effect){
    for(auto x : statusEffects){
        if(x == effect) return true;
    }
    return false;
}
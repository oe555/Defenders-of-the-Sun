#include "Quest.h"
#include <string>

Quest::Quest(std::string title_, std::string description_, int type_, int id_){
    title = title_;
    description = description_;
    type = type_;
    id = id_;
    complete = false;
}

std::string Quest::getTitle(){
    return title;
}

void Quest::setTitle(std::string title_){
    title = title_;
}

std::string Quest::getDescription(){
    return description;
}

void Quest::setDescription(std::string description_){
    description = description_;
}

int Quest::getType(){
    return type;
}

void Quest::setType(int type_){
    type = type_;
}

int Quest::getId(){
    return id;
}

void Quest::setId(int id_){
    id = id_;
}

bool Quest::isComplete(){
    return complete;
}

void Quest::finish(){
    complete = true;
}
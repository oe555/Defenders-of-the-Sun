#include <string>
#include <vector>
#include "Journal.h"
#include "Quest.h"
#include <iostream>

Journal::Journal(){
    quests = {};
}

void Journal::addQuest(std::string title, std::string description, int type, int id){
    Quest newQuest = Quest(title, description, type, id);
    quests.push_back(newQuest);
}

bool Journal::advanceQuest(int id, int newId, std::string newDescription, bool completeQuest){
    for(Quest &q : quests){
        if(q.getId() == id && !q.isComplete()){
            q.setId(newId);
            q.setDescription(newDescription);
            if(completeQuest) q.finish();
            return true;
        }
    }
    return false;
}

void Journal::listQuests(bool completedQuests){
    int currCount = 1;
    if(!completedQuests){
        std::cout << "The following quests are written in your journal:\n";
        std::cout << "\nSection 1: Main Quests\n\n";
        for(Quest q : quests){
            if(q.getType() == 0 && !q.isComplete()){
                std::cout << currCount << ") " << q.getTitle() << "\n";
                std::cout << "-- " << q.getDescription() << "\n";
                currCount++;
            }
        }
        std::cout << "\nSection 2: Personal Quests\n\n";
        for(Quest q : quests){
            if(q.getType() == 1 && !q.isComplete()){
                std::cout << currCount << ") " << q.getTitle() << "\n";
                std::cout << "-- " << q.getDescription() << "\n";
                currCount++;
            }
        }
        std::cout << "\nSection 3: Companion Quests\n\n";
        for(Quest q : quests){
            if(q.getType() == 2 && !q.isComplete()){
                std::cout << currCount << ") " << q.getTitle() << "\n";
                std::cout << "-- " << q.getDescription() << "\n";
                currCount++;
            }
        }
        std::cout << "\nSection 4: Side Quests\n\n";
        for(Quest q : quests){
            if(q.getType() == 3 && !q.isComplete()){
                std::cout << currCount << ") " << q.getTitle() << "\n";
                std::cout << "-- " << q.getDescription() << "\n";
                currCount++;
            }
        }
    }
    else{
        std::cout << "You take a moment to look through what you have accomplished so far:\n";
        std::cout << "\nSection 1: Main Quests\n\n";
        for(Quest q : quests){
            if(q.getType() == 0 && q.isComplete()){
                std::cout << currCount << ") " << q.getTitle() << "\n";
                std::cout << "-- " << q.getDescription() << "\n";
                currCount++;
            }
        }
        std::cout << "\nSection 2: Personal Quests\n\n";
        for(Quest q : quests){
            if(q.getType() == 1 && q.isComplete()){
                std::cout << currCount << ") " << q.getTitle() << "\n";
                std::cout << "-- " << q.getDescription() << "\n";
                currCount++;
            }
        }
        std::cout << "\nSection 3: Compainion Quests\n\n";
        for(Quest q : quests){
            if(q.getType() == 2 && q.isComplete()){
                std::cout << currCount << ") " << q.getTitle() << "\n";
                std::cout << "-- " << q.getDescription() << "\n";
                currCount++;
            }
        }
        std::cout << "\nSection 4: Side Quests\n\n";
        for(Quest q : quests){
            if(q.getType() == 3 && q.isComplete()){
                std::cout << currCount << ") " << q.getTitle() << "\n";
                std::cout << "-- " << q.getDescription() << "\n";
                currCount++;
            }
        }
    }
}

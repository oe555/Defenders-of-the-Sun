#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include <vector>
#include "Quest.h"

class Journal{
private:
    std::vector<Quest> quests;
public:
    Journal();
    
    void addQuest(std::string title, std::string description, int type, int id);
    // Searches for a quest with given id and updates if exists (returns true on success)
    bool advanceQuest(int id, int newId, std::string newDescription, bool completeQuest); 
    void listQuests(bool completedQuests);
};

#endif
#ifndef QUEST_H
#define QUEST_H

#include <string>

class Quest{
private:
    std::string title;
    std::string description;
    int type; // 0 = main, 1 = personal, 2 = companion, 3 = side
    int id;
    bool complete;
public:
    Quest(std::string title_, std::string description_, int type_, int id_);

    std::string getTitle();
    void setTitle(std::string title_);

    std::string getDescription();
    void setDescription(std::string description_);

    int getType();
    void setType(int type_);

    int getId();
    void setId(int id_);

    bool isComplete();
    void finish();
};

#endif
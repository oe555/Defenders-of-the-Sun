#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <string>
#include <vector>
#include "Companion.h"
#include "Meta.h"

class Dialogue{
private:
    // Is this a standard line or does the player pick a choice here?
    bool playerChoice;
    // This is the line given as output.
    std::string line;
    // Player will roll perception for this line. Set to a large negative number to always show.
    int perceptionRequirement; 
    // If a player choice, this is the charisma check. A failed check returns -1. It only applies to the first choice.
    int charismaRequirement;
    // Use "None" if this line is shown to everyone. 
    // If playerChoice is true, this determines whether the first string in "choices" is shown.
    // The other requirements are the same idea
    std::string classRequirement;
    std::string deityRequirement;
    std::string companionRequirement;
    int storyVariableRequirement;
    // List of choices that will be shown if this is a player choice.
    std::vector<std::string> choices;

    // Pairs of name, approval value
    std::vector<std::pair<std::pair<std::string, int>, int>> approval;
public:
    Dialogue(bool playerChoice_, std::string line_, int storyVariableRequirement_, int perceptionRequirement_, int charismaRequirement_, std::string classRequirement_, std::string companionRequirement_, std::string deityRequirement_, std::vector<std::string> choices_);

    // If it's a player choice, then this will return the index of what the player chooses. Returns -1 on any fail. Returns 0 otherwise.
    int runDialogue(Meta meta);

    bool isPlayerChoice();

    void addApproval(std::string companion, int value, int index);
};

#endif
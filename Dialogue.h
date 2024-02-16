#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <string>
#include <vector>

class Dialogue{
private:
    // Is this a standard line or does the player pick a choice here?
    bool playerChoice;
    // If not a player choice, this is the line given as output.
    std::string line;
    // Player will roll perception for this line. Set to a large negative number to always show.
    int perceptionRequirement; 
    // Use "None" if this line is shown to everyone. 
    // If playerChoice is true, this determines whether the last string in "choices" is shown.
    std::string classRequirement; 
    // List of choices that will be shown if this is a player choice.
    std::vector<std::string> choices;
public:
    Dialogue(bool playerChoice_, std::string line_, int perceptionRequirement_, std::string classRequirement_, std::vector<std::string> choices_);

    // If it's a player choice, then this will return the index of what the player chooses.
    int runDialogue();
};

#endif
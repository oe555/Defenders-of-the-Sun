#include "Enemy.h"
#include "Quest.h"
#include "Journal.h"
#include "Weapon.h"
#include "Armor.h"
#include "Companion.h"
#include "Meta.h"
#include "Location.h"
#include "Interaction.h"
#include "Region.h"
#include "Dialogue.h"
#include "MapGen.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

Region GenRegionA(Meta meta){
    /*
        A0
    */
    Dialogue d0 = Dialogue(true, "You wake up in a cold, dark prison cell patrolled by skeleton guards. You try hard to remember how you got here, but it seems like something is preventing you from remembering your past.",
                        -99, -99, "None", "None", "None",
                        {"Check your body for injuries.", "Look for prisoners in the cell across the hall."});
    Dialogue d1 = Dialogue(false, "You glance over your body, trying to find scars. Everything seems fine, but who knows how much luck was involved?",
                        -99, -99, "None", "None", "None", {});
    Dialogue d2 = Dialogue(false, "You closely examine the only cell within your line of sight. You see a young, unconscious, female half elf with black hair and a large raven tattooed to her neck. Looking at her gives you a feeling of danger and uncertainty. It's unclear whether allying with her is a good idea...",
                        -99, -99, "None", "None", "None", {});
    Dialogue d3 = Dialogue(false, "Before you get a chance to check anything else, a massive beam moonlight shoots through the hallway. A radiant energy, one that you realize is fueled by the power of your goddess, burns the skeletons to a crisp. The energy shakes the ground, causing your cell door to open slightly. Strangely, it seems like none the cell doors were locked in the first place.\n\nAfter listening carefully, you're able to hear noises that sound like fighting in the distance. Perhaps this is the source of the energy that freed you...\n\nYou slowly step outside of your cell, thinking about what to do next.",
                        -99, -99, "None", "None", "Selunara", {});
    Dialogue d4 = Dialogue(false, "Before you get a chance to check anything else, a massive beam of light shoots through the hallway. A mysterious radiant energy burns the skeletons to a crisp. The energy shakes the ground, causing your cell door to open slightly. Strangely, it seems like none the cell doors were locked in the first place. \n\nAfter listening carefully, you're able to hear noises that sound like fighting in the distance. Perhaps this is the source of the energy that freed you...\n\nYou slowly step outside of your cell, thinking about what to do next.",
                        -99, -99, "None", "None", "None", {});
    Interaction interaction = Interaction({d0, d1, d2, d3, d4});
    interaction.addNav(0, 1, 1);
    interaction.addNav(0, 2, 2);
    interaction.addNav(1, 0, 3);
    interaction.addNav(2, 0, 3);
    interaction.addNav(3, -1, 4);
    interaction.addNav(3, 0, -7);
    interaction.addNav(4, 0, -7);
    interaction.addQuestUpdate(-1, 0, 0, "Break out of Prison", "Leaving this prison seems to be in our best interest.");
    interaction.addQuestUpdate(-1, 1, 0, "Find Allies", "Whatever lies ahead will be easier with friends.");
    interaction.addQuestUpdate(-1, 2, 1, "Discover Your Past", "The prison is causing your memory to be surpressed. Leaving the prison may help recover some memories.");

    Location A0 = Location("Your cell");
    A0.setPrimaryInteraction(interaction);

    /*
        A1
    */
    d0 = Dialogue(false, "As you step towards the cell, your vision blurs as you experience a painful headache. You start to lose control of your body, causing you to stand lifelessly in front of the cell door. The young woman who was once trapped in that cell suddenly yet slowly walks towards you.",
                -99, -99, "None", "None", "None", {});
    d1 = Dialogue(false, "[Perception] Despite the pain her magic is inflicting on you, you realize that she is as confused and vulnerable as you are. She speaks and acts with extreme caution out of fear that you intend to harm her.",
                3, -99, "None", "None", "None", {});
    d2 = Dialogue(true, "Raven: \"Speak.\"", -99, -99, "None", "None", "None",
                {"\"I am a prisoner just like you. The cell doors are unlocked for some reason.\"", "\"Threatening me will end very badly for you...\"", "Attack"});
    d3 = Dialogue(true, "Your headache swiftly clears and your vision returns to normal.\n\nRaven: \"I apologize for the poor introduction. I\'m Raven. I have no idea why we're here or how we got here, but together we may be able to figure this out. Are you in?\"",
                -99, -99, "None", "None", "None", {"\"I\'m " + meta.getCharName() + ". Come with me, let's deal with this together.\""});
    d4 = Dialogue(false, "Raven: \"Good luck kid.\"\n\nShe runs off, leaving you to deal with this mystery without her.",
                -99, -99, "None", "None", "None", {});
    interaction = Interaction({d0, d1, d2, d3, d4});
    interaction.addNav(0, 0, 1);
    interaction.addNav(1, -1, 2);
    interaction.addNav(1, 0, 2);
    interaction.addNav(2, 1, 3);
    interaction.addNav(2, 2, 3);
    interaction.addNav(2, 3, -2);
    interaction.addNav(3, 1, -3);
    interaction.addNav(3, 2, 4);
    interaction.addNav(4, 0, -1);
    interaction.addCompanion("Raven", "None");
    interaction.addQuestUpdate(-1, 3, 2, "Raven", "Raven's powers are strange and unfamiliar. We should continue traveling with her to learn more.");
    
    Location A1 = Location("Nearby cell");
    Enemy ravenEnemy = Enemy("Raven", 7, 3, 4, 1, 0, true);
    A1.addEnemy(ravenEnemy);
    A1.setPrimaryInteraction(interaction);

    /*
        A2
    */
    d0 = Dialogue(false, "You run down the hallway towards the noise, but you're too late. Dead warriors of Selunara and piles of bones are scattered across the floor. There are three severely weakened skeletons that are still intact. They turn towards you, ready to fight.",
                -99, -99, "None", "None", "None", {});
    d1 = Dialogue(false, "Raven: \"Shit. Stay close, we can take them.\"", -99, 
                -99, "None", "Raven", "None", {});
    interaction = Interaction({d0, d1});
    interaction.addNav(0, 0, 1);
    interaction.addNav(1, -1, -2);
    interaction.addNav(1, 0, -2);
    
    Location A2 = Location("First Hallway");
    Enemy skeletonWarrior1 = Enemy("Skeleton Warrior 1", 3, 2, 6, 1, 0, false);
    Enemy skeletonWarrior2 = Enemy("Skeleton Warrior 2", 3, 2, 6, 1, 0, false);
    Enemy skeletonWarrior3 = Enemy("Skeleton Warrior 3", 3, 2, 6, 1, 0, false);
    A2.addEnemy(skeletonWarrior1); A2.addEnemy(skeletonWarrior2); A2.addEnemy(skeletonWarrior3);
    A2.setPrimaryInteraction(interaction);
    // TODO: POST ENCOUNTER INTERACTION WITH VIVIAN

    /*
        Region A
    */

    Region res = Region();
    res.addLocation(A0);
    res.addLocation(A1);
    res.addLocation(A2);
    res.addConnection(0, 1);
    res.addConnection(0, 2);
    res.addConnection(1, 2);
    
    return res;
}
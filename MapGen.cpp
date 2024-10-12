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

std::string pullName(std::vector<std::string> &names){
    int res = rand() % ((int)names.size());
    std::string ret = names[res];
    names.erase(names.begin() + res);
    return ret;
}

Region GenRegionA(Meta meta){
    std::vector<std::string> nameBank = {"Steve", "John", "Jake", "Richard", "Owen", "Mike", "Terry", "Jeff", "Suyash", "Raphael", "Nick", "Brad", "Sarah", "Susan", "Mary", "Estelle", "Rachael", "Jullian", "Theo", "Lisa", "Jenny", "Olivia", "Gina", "Tracy", "Abby", "Jill"};

    /*
        A0
    */
    Dialogue d0 = Dialogue(true, "You wake up in a cold, dark prison cell patrolled by skeleton guards. You try hard to remember how you got here, but it seems like something is preventing you from remembering your past.",
                        -1, -99, -99, "None", "None", "None",
                        {"Check your body for injuries.", "Look for prisoners in the cell across the hall."});
    Dialogue d1 = Dialogue(false, "You glance over your body, trying to find scars. Everything seems fine, but who knows how much luck was involved?",
                        -1, -99, -99, "None", "None", "None", {});
    Dialogue d2 = Dialogue(false, "You closely examine the only cell within your line of sight. You see an unconscious female half-elf with pale skin, black hair, and a large raven tattooed to her neck. Looking at her gives you a feeling of danger and uncertainty. It's unclear whether allying with her is a good idea...",
                        -1, -99, -99, "None", "None", "None", {});
    Dialogue d3 = Dialogue(false, "Before you get a chance to check anything else, a massive beam moonlight shoots through the hallway. A radiant energy, one that you realize is fueled by the power of your goddess, burns the skeletons to a crisp. The energy shakes the ground, causing your cell door to open slightly. Strangely, it seems like none the cell doors were locked in the first place.\n\nAfter listening carefully, you're able to hear noises that sound like fighting in the distance. Perhaps this is the source of the energy that freed you...\n\nYou slowly step outside of your cell, thinking about what to do next.",
                        -1, -99, -99, "None", "None", "Selunara", {});
    Dialogue d4 = Dialogue(false, "Before you get a chance to check anything else, a massive beam of light shoots through the hallway. A mysterious radiant energy burns the skeletons to a crisp. The energy shakes the ground, causing your cell door to open slightly. Strangely, it seems like none of the cell doors were locked in the first place. \n\nAfter listening carefully, you're able to hear noises that sound like fighting in the distance. Perhaps this is the source of the energy that freed you...\n\nYou slowly step outside of your cell, thinking about what to do next.",
                        -1, -99, -99, "None", "None", "None", {});
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
    d0 = Dialogue(false, "As you step towards the cell, your vision blurs as you experience a painful headache. You start to lose control of your body, causing you to stand lifelessly in front of the cell door. The pale half-elf woman who was once trapped in that cell suddenly yet slowly walks towards you.",
                -1, -99, -99, "None", "None", "None", {});
    d1 = Dialogue(false, "[Perception] Despite the pain her magic is inflicting on you, you realize that she is as confused and vulnerable as you are. She speaks and acts with extreme caution out of fear that you intend to harm her.",
                -1, 3, -99, "None", "None", "None", {});
    d2 = Dialogue(true, "Raven: \"Speak.\"", -1, -99, -99, "None", "None", "None",
                {"\"I am a prisoner just like you. The cell doors are unlocked for some reason.\"", "\"Threatening me will end very badly for you...\"", "Attack."});
    d3 = Dialogue(true, "Your headache swiftly clears and your vision returns to normal.\n\nRaven: \"I\'m Raven. I have no idea why we're here or how we got here, but together we may be able to figure this out. Are you in?\"",
                -1, -99, -99, "None", "None", "None", {"\"I\'m " + meta.getCharName() + ". Come with me, let's deal with this together.\"", "\"I'm not interested in your company.\""});
    d4 = Dialogue(false, "Raven: \"Good luck kid.\"\n\nShe runs off, leaving you to deal with this mystery without her.",
                -1, -99, -99, "None", "None", "None", {});
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
    Enemy ravenEnemy = Enemy("Raven", 16, 3, 6, 1, 0, true);
    A1.addEnemy(ravenEnemy);
    A1.setPrimaryInteraction(interaction);

    /*
        A2
    */
    d0 = Dialogue(false, "You run down the hallway towards the noise, but you're too late. Dead warriors of Selunara and piles of bones are scattered across the floor. There are three severely weakened skeletons that are still intact. They turn towards you, ready to fight.",
                -1, -99, -99, "None", "None", "None", {});
    d1 = Dialogue(false, "Raven: \"Shit. Stay close, we can take them.\"", -99, 
                -1, -99, "None", "Raven", "None", {});
    interaction = Interaction({d0, d1});
    interaction.addNav(0, 0, 1);
    interaction.addNav(1, -1, -2);
    interaction.addNav(1, 0, -2);
    
    Location A2 = Location("First Hallway");
    Enemy skeletonWarrior1 = Enemy("Skeleton Warrior " + pullName(nameBank), 3, 2, 4, 1, 0, false);
    Enemy skeletonWarrior2 = Enemy("Skeleton Warrior " + pullName(nameBank), 3, 2, 4, 1, 0, false);
    Enemy skeletonWarrior3 = Enemy("Skeleton Warrior " + pullName(nameBank), 3, 2, 4, 1, 0, false);
    A2.addEnemy(skeletonWarrior1); A2.addEnemy(skeletonWarrior2); A2.addEnemy(skeletonWarrior3);
    A2.setPrimaryInteraction(interaction);

    /*
        A3
    */
    d0 = Dialogue(false, "You move into the central room and spot more dead warriors. You notice a wolf examining one of the corpses, but you know all too well that this isn't an ordinary wolf. She turns towards you, recognizing you as a fellow druid.",
                -1, -99, -99, "Druid", "None", "None", {});
    d1 = Dialogue(true, "You move into the central room and spot more dead warriors. You notice a strange wolf examining one of the corpses. It's not clear whether who's side this wolf is on, but it doesn't notice you yet...",
                -1, -99, -99, "None", "None", "None", {"Slowly and peacefully approach the wolf.", "Attack."});
    d2 = Dialogue(false, "The wolf gets scared and runs away.", -1, -99, -99, "None", "None", "None", {});
    d3 = Dialogue(false, "The wolf's body starts glowing and changing shape. In its place, a half-elf woman with a long bright white pony tail and piercing dark blue eyes appears.",
                -1, -99, -99, "None", "None", "None", {});
    d4 = Dialogue(false, "Raven: \"Another half-elf? It's been a while since I've seen another of my kind...\"",
                -1, -99, -99, "None", "Raven", "None", {});
    Dialogue d5 = Dialogue(true, "Vivian: \"I\'m glad to see that I'm not the only one in this situation. Let us work together. I believe my fellow Selunarans were looking to break me out and keep me alive, but unfortunately I wasn't able to return the favor...\"",
                -1, -99, -99, "None", "None", "None", {"Let's travel together then. I\'m " + meta.getCharName() + ".", "Why were they looking for you?", "I would rather handle this without you. Good luck."});
    Dialogue d6 = Dialogue(false, "Vivian: \"Fair enough. Good luck my friend.\"", -1, -99, -99, "None", "None", "None", {});
    Dialogue d7 = Dialogue(true, "Vivian: \"Unfortunately I'll have to discuss this another time. We have more urgent things to deal with.\"",
                -1, -99, -99, "None", "None", "None", {"Let's travel together then. I\'m " + meta.getCharName() + ".", "I would rather handle this without you. Good luck."});
    Dialogue d8 = Dialogue(false, "Vivian: \"Vivian. Let's keep an eye out for more prisoners on the way.\"", -1, -99, -99, "None", "None", "None", {});
    Dialogue d9 = Dialogue(false, "[Perception] She seems very skeptical of you. Perhaps she knows that you're a follower of Leer. Either way, she's certainly more worried about the current situation.",
                -1, 4, -99, "None", "None", "Leer", {});
    d5.addApproval("Raven", 2, 1);
    d7.addApproval("Raven", 2, 1);
    interaction = Interaction({d0, d1, d2, d3, d4, d5, d6, d7, d8, d9});
    interaction.addNav(0, -1, 1);
    interaction.addNav(0, 0, 3);
    interaction.addNav(1, 1, 3);
    interaction.addNav(1, 2, 2);
    interaction.addNav(2, 0, -1);
    interaction.addNav(3, 0, 4);
    interaction.addNav(4, -1, 5);
    interaction.addNav(4, 0, 5);
    interaction.addNav(5, 1, 8);
    interaction.addNav(5, 2, 7);
    interaction.addNav(5, 3, 6);
    interaction.addNav(6, 0, -1);
    interaction.addNav(7, 1, 8);
    interaction.addNav(7, 2, 6);
    interaction.addNav(8, 0, 9);
    interaction.addNav(9, -1, -3);
    interaction.addNav(9, 0, -3);
    interaction.addCompanion("Vivian", "Selunara");
    interaction.addQuestUpdate(-1, 4, 2, "Vivian", "Vivian mentioned that the Selunarans raiding the prison were there to find her. Traveling with Vivian may give us more insight into what is happening.");

    Location A3 = Location("Central Room");
    A3.setPrimaryInteraction(interaction);

    /*
        A4
    */
    Location A4 = Location("East Hallway");
    /*
        A5
    */
    d0 = Dialogue(false, "[Perception] You manage to find some silver under one of the tables.", -1, 3, -99, "None", "None", "None", {});
    interaction = Interaction({d0});
    interaction.addNav(0, -1, -1);
    interaction.addNav(0, 0, -6);
    interaction.setSilver(5);

    Location A5 = Location("Cafeteria");
    A5.setPrimaryInteraction(interaction);

    /*
        A6
    */
    d0 = Dialogue("As you peak your head into the storage closet, something immediately grabs you and pulls you in. The skin of whatever is holding you feels hot to the touch, contrasting with the cold blade that is being held to your neck.");
    d1 = Dialogue(false, "Although Raven is hesitant to step near the closet, she begins moving her hands and getting ready to use her magic against the strange creature. \n\nRaven: \"Whatever you are, if you hurt my friend, it will be the last thing you do.\"",
                -1, -99, -99, "None", "Raven", "None", {});
    d2 = Dialogue(true, "The mysterious creature does not speak. As its skin begins to get hotter, you realize that it is waiting for you to say something. Surprisingly, you also have an opportunity to reach for your dagger and end its life once and for all.",
                -1, -99, -99, "Rogue", "None", "None", {"[Rogue] \"You're not gripping my arm properly. If you don't let me go right now, it won't end nicely for you.\"", "Stab the creature and attempt to kill it.", "\"Please let me go. I'm not looking for conflict.\""});
    d2.addApproval("Vivian", 2, 1);
    d2.addApproval("Vivian", -1, 2);
    d2.addApproval("Vivian", 2, 3);
    d3 = Dialogue("You grab your dagger and drive it into the creature with as much force as possible. It immediately releases you, and burns itself into an unrecognizable human-like corpse. Maybe it's best to avoid stepping into random dark storage closets.");
    d4 = Dialogue("The creature pushes you out of the closet and steps out into the light. An adorable, young, female half-human half-devil with freckles and devil horns shaped like cat ears. Not quite what you were expecting...\n\nShrugmini: \"Who the hell are you?\"",
                {"\"I should be asking you the same question. Do you have a name?\"", "\"I'm assuming you also woke up here with little to no memory?\"", "\"I don't owe you anything after that. I think it's time for you to leave.\""});
    d5 = Dialogue("Without saying anything else she backs away and leaves. Maybe it's best to avoid dark storage closets in the future...");
    d6 = Dialogue("Shrugmini: \"My name is Shrugmini. I don't remember a fucking thing about how I got here but these dead things don't know how to make a proper lock. Listen, I'm sorry I attacked you. Sometimes it's hard for me to trust people when I first meet them.\"",
                {"\"Don't worry about it, we can still work together. I think your skills may be quite useful.\"", "\"Shrugmini? Awww that's an adorable name.\"", "\"I think it's best if we part ways. I don't think I trust you any more than you trust me.\""});
    d7 = Dialogue("Shrugmini seems embarrased by your remark, but in an innocent way. Maybe her devil side isn't quite as strong as it first seemed.\n\nShrugmini: \"Not as adorable as the exit to this damn prison. Let's get out of here. Also, maybe you should stop peeking into dark storage closets.\"");
    d8 = Dialogue("Shrugmini: \"Alright then. Let's get out of here. Also, maybe you should stop peeking into dark storage closets.\"");

    interaction = Interaction({d0, d1, d2, d3, d4, d5, d6, d7, d8});
    interaction.addNav(0, 0, 1);
    interaction.addNav(1, -1, 2);
    interaction.addNav(1, 0, 2);
    interaction.addNav(2, 1, 4);
    interaction.addNav(2, 2, 3);
    interaction.addNav(2, 3, 4);
    interaction.addNav(3, 0, -1);
    interaction.addNav(4, 1, 6);
    interaction.addNav(4, 2, 6);
    interaction.addNav(4, 3, 5);
    interaction.addNav(5, 0, -1);
    interaction.addNav(6, 1, 8);
    interaction.addNav(6, 2, 7);
    interaction.addNav(6, 3, 5);
    interaction.addNav(7, 0, -3);
    interaction.addNav(8, 0, -3);
    interaction.addCompanion("Shrugmini", "None");
    interaction.addQuestUpdate(-1, 5, 2, "Shrugmini", "Shrugmini is certainly a strange character. Traveling with her more may give more insight into her background.");

    Location A6 = Location("Unsuspicious Dark Storage Closet");
    A6.setPrimaryInteraction(interaction);

    /*
        A7
    */

    d0 = Dialogue("You notice more skeletons guarding this hallway, one of which has a longbow. Perhaps they are guarding another pair of cells...");
    interaction = Interaction({d0});
    interaction.addNav(0, 0, -2);
    Location A7 = Location("West Hallway");
    Enemy skeletonArcher = Enemy("Skeleton Archer " + pullName(nameBank), 1, 2, 8, 1, 0, false);
    Enemy skeletonWarrior4 = Enemy("Skeleton Warrior " + pullName(nameBank), 3, 2, 4, 1, 0, false);
    Enemy skeletonWarrior5 = Enemy("Skeleton Warrior " + pullName(nameBank), 3, 2, 4, 1, 0, false);
    A7.addEnemy(skeletonWarrior4);
    A7.addEnemy(skeletonWarrior5);
    A7.addEnemy(skeletonArcher);
    A7.setPrimaryInteraction(interaction);
    
    /*
        A8
    */
    Location A8 = Location("Empty Cell");

    /*
        A9
    */
    d0 = Dialogue("In this cell, you spot a man with bagpipes strapped to his back examining the lock on his cell door. For some reason, his cell is still locked.\n\nHubert: \"Hello! Over here! My cell is still locked somehow.\"",
                {"\"That's not my problem. I'm sure you can figure it out on your own.\"", "\"Don't worry. I'll help you escape.\""});
    d0.addApproval("Raven", -2, 1);
    d0.addApproval("Raven", 2, 2);
    d0.addApproval("Iris", -2, 1);
    d0.addApproval("Iris", 2, 2);
    d1 = Dialogue("He looks dissapointed as he shifts his focus back to the lock.");
    d2 = Dialogue("Hubert: \"Thank the gods. Feel free to try to open the lock. If you can't open it easily from the outside, maybe there's a key nearby or some other tool to break it open...\"");
    interaction = Interaction({d0, d1, d2});
    interaction.addNav(0, 1, 1);
    interaction.addNav(0, 2, 2);
    interaction.addNav(1, 0, -1);
    interaction.addNav(2, 0, -7);
    interaction.addQuestUpdate(-1, 9, 3, "Free the Musician", "We found a man with bagpipes locked in one of the cells. We should try to find a way to free him.");
    Location A9 = Location("Locked Cell");
    A9.setPrimaryInteraction(interaction);
    // Create optional interaction (interacting with the lock)
    d0 = Dialogue("In hopes of opening the cell door, you approach the lock and brainstorm a solution.");
    d1 = Dialogue(false, "Shrugmini: \"Step aside.\"\n\nShrumini wraps her hair tie awkwardly around the lock. With one simple tug, Shrugmini splits the lock in two. It seems like she has a lot of experience with things like this.",
                -1, -99, -99, "None", "Shrugmini", "None", {});
    d2 = Dialogue(false, "[Explorer] Using your experience with picking locks, you manage to open the cell door.", -1, -99, -99, "Explorer", "None", "None", {});
    d3 = Dialogue(false, "[Rogue] Using your experience with picking locks, you manage to open the cell door.", -1, -99, -99, "Rogue", "None", "None", {});
    d4 = Dialogue(false, "The key you found in the closet upstairs fits the lock perfectly.", 0, -99, -99, "None", "None", "None", {});
    d5 = Dialogue("Unfortunately, no solution comes to mind. You'll need to keep looking...");
    d6 = Dialogue("Hubert: \"You're a legend. Please, let me come with you. I owe you my life.\"", {"\"Of course. Stay close and we'll find our way out of here.\"", "\"I think it's best if we travel seperately. I wish you the best of luck.\""});
    interaction = Interaction({d0, d1, d2, d3, d4, d5, d6});
    interaction.addNav(0, 0, 1);
    interaction.addNav(1, -1, 2);
    interaction.addNav(1, 0, 6);
    interaction.addNav(2, -1, 3);
    interaction.addNav(2, 0, 6);
    interaction.addNav(3, -1, 4);
    interaction.addNav(3, 0, 6);
    interaction.addNav(4, -1, 5);
    interaction.addNav(4, 0, 6);
    interaction.addNav(5, 0, -1);
    interaction.addNav(6, 1, -3);
    interaction.addNav(6, 2, -9);
    interaction.addQuestUpdate(-1, 7, 2, "Hubert", "We should travel more with Hubert to learn more about him.");
    interaction.addQuestUpdate(9, -1, 3, "Free the Musician", "We freed the musician.");
    interaction.addAltQuestUpdate(9, -1, 3, "Free the Musician", "We freed the musician.");
    interaction.addCompanion("Hubert", "None");
    A9.addOptionalInteraction({"Examine the lock", interaction});

    /*
        A10*/

    d0 = Dialogue(false, "[Perception] This staircase seems to lead to a long hallway with many open cells. It's likely to be heavily guarded.",
                -1, 3, -99, "None", "None", "None", {});
    interaction = Interaction({d0});
    interaction.addNav(0, 0, -1);
    interaction.addNav(0, -1, -1);
    Location A10 = Location("First Staircase");
    A10.setPrimaryInteraction(interaction);
    
    /*
        A11
    */
    d0 = Dialogue("Once you get to the top of the staircase and enter the hallway, a small army of skeleton guards turn towards you.");
    interaction = Interaction({d0});
    interaction.addNav(0, 0, -2);
    Location A11 = Location("Upper Hallway");
    Enemy skeletonWarrior6 = Enemy("Skeleton Warrior " + pullName(nameBank), 3, 2, 4, 1, 0, false);
    Enemy skeletonWarrior7 = Enemy("Skeleton Warrior " + pullName(nameBank), 3, 2, 4, 1, 0, false);
    Enemy skeletonWarrior8 = Enemy("Skeleton Warrior " + pullName(nameBank), 3, 2, 4, 1, 0, false);
    A11.addEnemy(skeletonWarrior6);
    A11.addEnemy(skeletonWarrior7);
    A11.addEnemy(skeletonWarrior8);
    Enemy skeletonArcher1 = Enemy("Skeleton Archer " + pullName(nameBank), 1, 2, 8, 1, 0, false);
    Enemy skeletonArcher2 = Enemy("Skeleton Archer " + pullName(nameBank), 1, 2, 8, 1, 0, false);
    Enemy skeletonArcher3 = Enemy("Skeleton Archer " + pullName(nameBank), 1, 2, 8, 1, 0, false);
    Enemy skeletonArcher4 = Enemy("Skeleton Archer " + pullName(nameBank), 1, 2, 8, 1, 0, false);
    A11.addEnemy(skeletonArcher1);
    A11.addEnemy(skeletonArcher2);
    A11.addEnemy(skeletonArcher3);
    A11.addEnemy(skeletonArcher4);
    A11.setPrimaryInteraction(interaction);

    /*
        A12
    */
    d0 = Dialogue("You find a key on one of the shelves.");
    interaction = Interaction({d0});
    interaction.addQuestUpdate(9, 9, 3, "Free the Musician", "We found a key in a storage closet. This key might unlock the cell door...");
    interaction.addNav(0, 0, -8);
    interaction.setStoryVariableUpdate(0);
    Location A12 = Location("Suspicious Dark Storage Closet");
    A12.setPrimaryInteraction(interaction);

    /*
        A13
    */
    d0 = Dialogue("You find some silver on the ground.");
    interaction = Interaction({d0});
    interaction.addNav(0, 0, -6);
    interaction.setSilver(3);
    Location A13 = Location("Upper Cell A");
    A13.setPrimaryInteraction(interaction);

    /*
        A14
    */
    d0 = Dialogue("Whoever broke out of this cell left a bloody note on the ground.\n\n\"Beware the giant warden guarding the exit! If you think the guards are aggressive, you're not prepared for this. I don't even think a cute devil reciting a sexually explicit poem about kittens would calm it down!\"");
    interaction = Interaction({d0});
    interaction.addNav(0, 0, -8);
    interaction.setStoryVariableUpdate(1);
    interaction.addQuestUpdate(0, 0, 0, "Break out of Prison", "We found a note that warns us of a \"giant warden\" by the exit. We should be prepared for a big fight.");
    Location A14 = Location("Upper Cell B");
    A14.setPrimaryInteraction(interaction);

    /*
        A15
    */
    d0 = Dialogue("As you climb up the staircase, you notice a knight wearing Solarian armor sneaking near the top of the stairs. She turns around and walks slowly towards you.\n\n\"Iris: Someone is in trouble up there. Come look.\"");
    d1 = Dialogue("You climb to the top of the stairs and peek into the armory. You see three armored guards surrounding a small gnome. They seem to be harassing him.");
    d2 = Dialogue(true, "Iris: \"Together, we can take them out. I can take on the ones around the corner while you deal with the three surrounding the innocent. Are you in?\"",
                -1, -99, -99, "Paladin", "None", "None", {"\"[Paladin] Of course. Together our blades can make a difference.\"", "Nod in agreement.", "\"I'm not interested in dealing with this.\""});
    d3 = Dialogue("Iris: \"Perfect.\"\n\nWithout hesitating, she charges into the armory and starts fighting a group of skeletons around the corner. She's giving you the opportunity to take on the three bullies and help the gnome.");
    d4 = Dialogue("Iris: \"You don't have a choice kid. This is our way out. Go help him.\"\n\nWithout hesitating, she charges into the armory and starts fighting a group of skeletons around the corner. She's giving you the opportunity to take on the three bullies and help the gnome.");
    interaction = Interaction({d0, d1, d2, d3, d4});
    interaction.addNav(0, 0, 1);
    interaction.addNav(1, 0, 2);
    interaction.addNav(2, 1, 3);
    interaction.addNav(2, 2, 3);
    interaction.addNav(2, 3, 4);
    interaction.addNav(3, 0, -1);
    interaction.addNav(4, 0, -1);
    Location A15 = Location("Second Starcase");
    A15.setPrimaryInteraction(interaction);

    /*
        A16
    */
    // INITIAL INTERACTION: CHOOSE WHETHER OR NOT TO SAVE NOAM
    d0 = Dialogue("You quickly approach the three bullies surrounding the gnome. They look very tough, but you notice that you're able to sneak up on them and kill them easily. Unfortunately, doing this will result in the gnome's death.",
                {"Allow the gnome to die and kill the bullies easily.", "Charge in and take on the bullies before they do anything else."});
    d0.addApproval("Hubert", 3, 2);
    d0.addApproval("Raven", 2, 2);
    d0.addApproval("Shrugmini", -1, 2);
    d0.addApproval("Shrugmini", 3, 1);
    d0.addApproval("Hubert", -3, 1);
    d0.addApproval("Raven", -2, 1);
    d1 = Dialogue("You sneak up to the bullies as you watch the gnome die to their abuse. You're able to surprise the bullies and disable them completely by striking their legs. At the same time, the paladin you met earlier finishes her fight and starts leaning against the wall to catch her breath.");
    d2 = Dialogue("The bullies turn your attention towards you as you prepare to fight.");
    interaction = Interaction({d0, d1, d2});
    interaction.addNav(0, 1, 1);
    interaction.addNav(0, 2, 2);
    interaction.addNav(1, 0, -1);
    interaction.addNav(2, 0, -2);
    // Make the location
    Location A16 = Location("Armory");
    A16.setPrimaryInteraction(interaction);
    Enemy armoredSkeletonBully1 = Enemy("Armored Skeleton Bully " + pullName(nameBank), 12, 5, 8, 1, 0, false);
    Enemy armoredSkeletonBully2 = Enemy("Armored Skeleton Bully " + pullName(nameBank), 12, 5, 8, 1, 0, false);
    Enemy armoredSkeletonBully3 = Enemy("Armored Skeleton Bully " + pullName(nameBank), 12, 5, 8, 1, 0, false);
    A16.addEnemy(armoredSkeletonBully1);
    A16.addEnemy(armoredSkeletonBully2);
    A16.addEnemy(armoredSkeletonBully3);
    // POST ENCOUNTER INTERACTION
    d0 = Dialogue(true, "Just as you finish defeating the bullies, the paladin you met earlier finishes her fight and starts leaning against the wall to catch her breath. The gnome you saved approaches you with gratitude.\n\nNoam: \"You saved me. I can't believe it. I really thought I was going to die back there. How could I possibly repay you?\"",
                -1, -99, 4, "Rogue", "None", "None", {"[Rogue] [Intimidation] If I were you I'd be handing over all the silver in my pocket.", "Do you think you could come with us and help us escape?", "You owe me nothing. You're free to leave. Good luck!"});
    d0.addApproval("Shrugmini", 2, 1);
    d1 = Dialogue("The gnome runs off happily. Hopefully he's able to find his way out of here.");
    d2 = Dialogue(true, "Noam: \"I'd love to join you! I've learned quite a bit from magic school that could come in handy. Trust me, you won't regret having another brain on your team.\"",
                -1, -99, -99, "Wizard", "None", "None", {"[Wizard] \"Magic school? Traveling with a fellow wizard would certainly be useful! Come with me.\"", "\"Come with me. Let's figure this out together.\"", "\"On second thought, I think we should part ways.\""});
    d3 = Dialogue("The gnome gets scared and runs away.");
    d4 = Dialogue("Noam: \"Fine, but you better leave me alone after I pay.\"\n\nThe gnome runs away after throwing all the silver he had on the floor in front of you.");
    d5 = Dialogue("Noam: \"I don't think that's the intellegent decision but you do you.\"");
    interaction = Interaction({d0, d1, d2, d3, d4, d5});
    interaction.addNav(0, -1, 3);
    interaction.addNav(0, 1, 4);
    interaction.addNav(0, 2, 2);
    interaction.addNav(0, 3, 1);
    interaction.addNav(1, 0, -1);
    interaction.addNav(2, 1, -3);
    interaction.addNav(2, 2, -3);
    interaction.addNav(2, 3, 5);
    interaction.addNav(3, 0, -1);
    interaction.setSilver(17); // Rogue's who convince him to pay get 17
    interaction.addNav(4, 0, -6);
    interaction.addNav(5, 0, -1);
    interaction.addCompanion("Noam", "None");
    interaction.addQuestUpdate(-1, 8, 2, "Noam", "Gnomes aren't very common in this part of the world, much less a gnome wizard. We should travel with Noam and learn more about him.");
    A16.setPostEncounterInteraction(interaction);
    // OPTIONAL INTERACTION WITH IRIS
    d0 = Dialogue(true, "Iris: \"I'm assuming you also woke up here. I believe the exit is up ahead. If we had time to chat, I would, but I don't think we have that luxury right now.\"",
                -1, -99, -99, "None", "None", "Solari", {"[Solari] \"I noticed our god's symbol on your armor. I think we'd make great allies.\"", "\"Traveling together will improve our odds.\"", "\"Let's split up and travel seperately. Good luck!\""});
    d1 = Dialogue("She runs towards the exit, never to be seen again.");
    d2 = Dialogue("Iris: \"I agree. Lead the way!\"");
    interaction = Interaction({d0, d1, d2});
    interaction.addNav(0, 1, 2);
    interaction.addNav(0, 2, 2);
    interaction.addNav(0, 3, 1);
    interaction.addNav(1, 0, -10);
    interaction.addNav(2, 0, -3);
    interaction.addCompanion("Iris", "Solari");
    interaction.addQuestUpdate(-1, 6, 2, "Iris", "Iris seems to be a brave and loyal ally. Traveling with her more may reveal more about her background.");
    A16.addOptionalInteraction({"Introduce yourself to the paladin", interaction});

    /*
        A17
    */
    Location A17 = Location("South Hallway");

    /*
        A18
    */
    Location A18 = Location("Indoor Garden");
    d0 = Dialogue("As you enter the garden, you encounter an angry undead gardener getting ready to throw vegitables at you.");
    // Initial interaction
    interaction = Interaction({d0});
    Enemy gardener = Enemy("The Gardener", 40, 3, 10, 2, 0, false);
    A18.addEnemy(gardener);
    interaction.addNav(0, 0, -2);
    A18.setPrimaryInteraction(interaction);
    // Post encounter
    d0 = Dialogue("You find some silver on the dead gardener's body.");
    interaction = Interaction({d0});
    interaction.addNav(0, 0, -6);
    interaction.setSilver(10);
    A18.setPostEncounterInteraction(interaction);

    /*
        A19
    */
    Location A19 = Location("Library");
    d0 = Dialogue("You walk into the library but make a little too much noise. This causes an undead librarian to get a little upset. Your only option is to fight back.");
    // Initial interaction
    interaction = Interaction({d0});
    Enemy librarian = Enemy("The Librarian", 40, 3, 10, 2, 0, false);
    A19.addEnemy(librarian);
    interaction.addNav(0, 0, -2);
    A19.setPrimaryInteraction(interaction);
    // Optional encounter
    d0 = Dialogue(false, "You search through the literature and come across a poem called \"Kissy Kissy Meow Meow\". You recall what you read about in the cell upstairs. Maybe this is genuinely a good idea? You turn to Shrugmini to see what she thinks.\n\nShrugmini: \"Ugh fine. As long as you cover your ears.\"\n\nYou hand the poem over to Shrugmini.",
                1, -99, -99, "None", "Shrugmini", "None", {});
    d1 = Dialogue("You look through the literature but can't find anything that would be useful.");
    interaction = Interaction({d0, d1});
    interaction.addNav(0, 0, -8);
    interaction.setStoryVariableUpdate(2);
    interaction.addQuestUpdate(0, 0, 0, "Break out of Prison", "We found a piece of literature that oddly matches a specific description given in a note on the floor. It could give us a way to bypass fighting the grand warden...");
    interaction.addNav(0, -1, 1);
    interaction.addNav(1, 0, -1);
    A19.addOptionalInteraction({"Search the library", interaction});

    /*
        A20
    */
    Location A20 = Location("Prison Exit");
    d0 = Dialogue(true, "You approach the exit and spot a giant skeleton warden that has no intention to let you leave.",
                2, -99, -99, "None", "Shrugmini", "None", {"Tell Shrugmini to read the poem.", "Attack."});
    d0.addApproval("Vivian", 3, 1);
    d0.addApproval("Noam", 2, 1);
    d1 = Dialogue("Shrugmini swallows her pride and begins to recite the sexually explicit kitten poem. The warden begins waddling back and fourth, eventually slamming onto the ground into an eternal slumber.\n\nShrugmini: \"Let's just pretend this didn't happen\"");
    interaction = Interaction({d0, d1});
    interaction.addNav(0, 1, 1);
    interaction.addNav(0, 2, -2);
    interaction.addNav(1, 0, -7);
    interaction.addQuestUpdate(0, -1, 0, "Break out of Prison", "Shrugmini read a sexually explicit poem about kittens in front of the Grand Warden. This caused it to fall asleep, allowing us to bypass the fight entirely.");
    Enemy warden = Enemy("Grand Warden", 50, 4, 10, 2, 0, false);
    A20.addEnemy(warden);
    A20.setPrimaryInteraction(interaction);
    d0 = Dialogue("The Grand Warden falls to the ground. The taste of freedom fills the air as the gate opens up in front of you.");
    interaction = Interaction({d0});
    interaction.addQuestUpdate(0, -1, 0, "Break out of Prison", "We defeated the Grand Warden.");
    interaction.addNav(0, 0, -7);
    A20.setPostEncounterInteraction(interaction);

    /*
        A21
    */
    Location A21 = Location("Drawbridge");
    d0 = Dialogue("As you step outside, your memories rush back to you. Images of your young self roaming city streets fills you with comfort and gives you a sense of familiarity. Unfortunately, it looks like this prison was in the middle of a large wilderness. You look around and desperately try to find civilization, but the only thing close to it is the group of elf druids approaching you from the other side of the bridge.");
    d1 = Dialogue(false, "Magnus: \"Vivian! Thank goodness you're alive. We sent some of our best warriors to come find you. Are you hurt?\"",
                -1, -99, -99, "None", "Vivian", "None", {});
    d2 = Dialogue("Vivian: \"I'm alright. Do you have an explanation for all of this?\"");
    d3 = Dialogue("Magnus: \"While you aren't the prisoner I was looking for, I'm glad to see some of you survived.\"");
    d4 = Dialogue("Magnus: \"I know you're probably not interested in further drama given your situation, but please listen carefully. A group of cultists, followers of Leer and Necrotar to be specific, have discovered a way to manipulate the brightness of the sun. The prison you found yourself in was built by servants of Necrotar ages ago. It's surrounded by a magic force that temporarily blocks out the memory of those who are imprisoned.\n\nThey captured each of you for a reason, but those reasons aren't exactly clear. We're hoping that your party has the ability to put a stop to the cultists. Fortunately, something is wrong on their end and they haven't been able to execute their plans of bringing permanent darkness to the world, but we fear that whatever is holding them back won't last very long.\n\nThere's a lot of detail to this but I don't want to overwhelm you. I need you to find our cave in the east wilderness. There, I will discuss all of the specifics. I'm in a hurry to get back to report to the others and I won't be able to escort your party as a result. Please, be careful. There is a campsite up ahead with some basic supplies and bedrolls for those who need them. It's getting dark and you should rest as much as you can before finding us. My name is Magnus. Tell them you're looking for me when you get there. Good luck.\"");
    d5 = Dialogue(false, "He turns to Vivian with a fearful look in his eyes.\n\nMagnus: \"I have some unfortunate news I'll need to share with you as well. Please keep yourself safe. We have a lot to talk about.\"",
                -1, -99, -99, "None", "Vivian", "None", {});
    d6 = Dialogue("The druids transform themselves into wolfs and run away towards their home. Your memory loss is simply replaced by stress. Nothing from your life before the prison has prepared you for a conflict like this, yet with the reassurance of your party behind you, you look towards the campsite ready to get some well deserved sleep.");
    interaction = Interaction({d0, d1, d2, d3, d4, d5, d6});
    interaction.addNav(0, 0, 1);
    interaction.addNav(1, -1, 3);
    interaction.addNav(1, 0, 2);
    interaction.addNav(2, 0, 4);
    interaction.addNav(3, 0, 4);
    interaction.addNav(4, 0, 5);
    interaction.addNav(5, -1, 6);
    interaction.addNav(5, 0, 6);
    interaction.addNav(6, 0, -7);
    interaction.addQuestUpdate(1, -1, 0, "Find Allies", "There's something special about the people that were trapped in the prison. It's unlikely that we'll find more allies in the future.");
    interaction.addQuestUpdate(2, -1, 1, "Discover Your Past", "Escaping the prison resulted in our memories coming back.");
    interaction.addQuestUpdate(4, 4, 2, "Vivian", "One of the leaders of Vivian's pack has something to say to her. We should go to their cave in the east wilderness to learn more.");
    interaction.addQuestUpdate(-1, 10, 0, "Talk to Magnus", "We were told that cultists are trying to control the brightness of the sun. The pack of druids in the east wilderness knows more about this.");
    A21.setPrimaryInteraction(interaction);

    /*
        A22
    */
    Location A22 = Location("Campsite A");

    /*
        Region A
    */

    Region res = Region();
    res.addLocation(A0);
    res.addLocation(A1);
    res.addLocation(A2);
    res.addLocation(A3);
    res.addLocation(A4);
    res.addLocation(A5);
    res.addLocation(A6);
    res.addLocation(A7);
    res.addLocation(A8);
    res.addLocation(A9);
    res.addLocation(A10);
    res.addLocation(A11);
    res.addLocation(A12);
    res.addLocation(A13);
    res.addLocation(A14);
    res.addLocation(A15);
    res.addLocation(A16);
    res.addLocation(A17);
    res.addLocation(A18);
    res.addLocation(A19);
    res.addLocation(A20);
    res.addLocation(A21);
    res.addLocation(A22);
    res.addConnection(0, 1);
    res.addConnection(0, 2);
    res.addConnection(1, 2);
    res.addConnection(2, 3);
    res.addConnection(3, 4);
    res.addConnection(4, 5);
    res.addConnection(4, 6);
    res.addConnection(3, 7);
    res.addConnection(7, 8);
    res.addConnection(7, 9);
    res.addConnection(8, 9);
    res.addConnection(3, 10);
    res.addConnection(10, 11);
    res.addConnection(11, 12);
    res.addConnection(11, 13);
    res.addConnection(11, 14);
    res.addConnection(13, 14);
    res.addConnection(11, 15);
    res.addConnection(15, 16);
    res.addConnection(16, 17);
    res.addConnection(17, 18);
    res.addConnection(17, 19);
    res.addConnection(17, 20);
    res.addConnection(20, 21);
    res.addConnection(21, 22);

    /*
        Making the rest interactions
    */
    // VIVIAN REST A
    d0 = Dialogue("You spot Vivian praying on her knees by the river nearby. Squirrels, birds, and various other animals gather around her. As you approach, she begins to speak, somehow knowing you're nearby.");
    d1 = Dialogue(false, "Vivian: \"I know you probably don't think highly of me because of my faith, but I assure you what we're dealing with is far more threatening than our differences.\"",
                -1, -99, -99, "None", "None", "Leer", {});
    d2 = Dialogue(true, "Vivian: \"We need to find my people and talk to Magnus. I'm worried, " + meta.getCharName() + ".\"",
                -1, -99, -99, "None", "None", "Selunara", {"[Selunara] \"With Her guidance, we can accomplish anything.\"", "\"I'm sure we can figure this out, especially with your help.\"", "\"Don't be so weak. What are a bunch of cultists going to do?\""});
    d2.addApproval("Vivian", 3, 1);
    d2.addApproval("Vivian", 2, 2);
    d2.addApproval("Vivian", -2, 3);
    d3 = Dialogue(true, "Vivian: \"I appreciate your optimism, but we must not be impatient. I'm relying on you and our friends to stand up for what is right and maintain our composure.\n\nI was impressed by you in the prison. Thank you, for approaching me peacefully. In what is likely one of your most vulnerable moments you didn't seem to be bothered by the potential threat of a wolf. Why?\"",
                -1, -99, -99, "Druid", "None", "None", {"[Druid] \"I knew you weren't an ordinary wolf.\"", "\"It's just a wolf. There was no reason for violence.\"", "\"I could easily beat a wolf in a fight.\""});
    d3.addApproval("Vivian", 3, 1);
    d3.addApproval("Vivian", 2, 2);
    d3.addApproval("Vivian", -1, 3);
    d4 = Dialogue("Vivian: \"I'm glad to be by your side. Get some rest, we'll need it.\"\n\nVivian stands up and walks towards the camp.");
    d5 = Dialogue("Vivian laughs, but it seems like she's laughing at you rather than with you.\n\nVivian: \"Don't make me test that. Sleep well.\"\n\nVivian stands up and walks towards the camp.");
    Interaction vivianInteraction = Interaction({d0, d1, d2, d3, d4, d5, d6});
    vivianInteraction.addNav(0, 0, 1);
    vivianInteraction.addNav(1, 0, 2);
    vivianInteraction.addNav(1, -1, 2);
    vivianInteraction.addNav(2, 1, 3);
    vivianInteraction.addNav(2, 2, 3);
    vivianInteraction.addNav(2, 3, 3);
    vivianInteraction.addNav(3, 1, 4);
    vivianInteraction.addNav(3, 2, 4);
    vivianInteraction.addNav(3, 3, 5);
    vivianInteraction.addNav(4, 0, -1);
    vivianInteraction.addNav(5, 0, -1);
    res.endingRest.setVivianInteraction(vivianInteraction);

    // RAVEN REST A
    d0 = Dialogue(true, "You notice that Raven is still a little unsettled by the encounter your party had with the devil. She signals you to come over while she sets up a place for her to sleep by one of the large trees nearby.\n\nRaven: \"So, what do you think about Jasper?\"",
                -1, -99, -99, "None", "None", "Necrotar", {"[Necrotar] \"Seems like a friendly fiend. It's nice having good connections in the underworld.\"", "\"I don't trust him. He's a devil, why would he be helping us?\"", "\"He seems to be on our side. We should give him a chance.\""});
    d0.addApproval("Raven", -1, 1);
    d0.addApproval("Raven", 2, 2);
    d0.addApproval("Raven", -2, 3);
    d1 = Dialogue("Raven: \"There is no winning with devils. I don't want to play his game. I've already done it before and it's one of my biggest regrets. We should keep an eye on him in the future, trust me.\"\n\nBefore you get a chance to ask follow up questions, Raven turns her back and starts organizing again. It seems best to leave her alone for now.");
    d2 = Dialogue("Raven: \"You're a smart kid. I have a really bad feeling about him being here. In the future, let's keep an eye on him, yeah? I have a bad history with this one in particular, but I'll spare you the details for now. Rest well.\"\n\nBefore you get a chance to ask follow up questions, Raven turns her back and starts organizing again. It seems best to leave her alone for now.");
    Interaction ravenInteraction = Interaction({d0, d1, d2});
    ravenInteraction.addNav(0, 1, 1);
    ravenInteraction.addNav(0, 2, 2);
    ravenInteraction.addNav(0, 3, 1);
    ravenInteraction.addNav(1, 0, -7);
    ravenInteraction.addNav(2, 0, -7);
    ravenInteraction.addQuestUpdate(3, 3, 2, "Raven", "Raven indicated that she has a bad history with Jasper but didn't want to share details. We should keep this in mind and continue to learn more about him from Raven.");
    res.endingRest.setRavenInteraction(ravenInteraction);

    // SHRUGMINI REST A
    d0 = Dialogue("You notice Shrugmini playing with squirrels near her bedroll. Given her half-devil appearance, she might know a thing or two about your party's encounter with Jasper. On the other hand, she's clearly much younger than the rest of your party and may not have any experiences. You watch as she plays, but she doesn't seem to notice you.",
                {"\"Hey Shrugmini, what do you know about devils like Jasper?\"", "\"Shrugmini, I noticed that you're half-devil half-human. How does that work? Do you have a devil parent and human parent?\"", "Leave Shrugmini to play with the squirrels."});
    d1 = Dialogue("Shrugmini: \"They're exactly as you expect. Evil in every way and always fighting for themselves. I don't like playing games with devils, and even though I look like one, I can promise you I'm nowhere close to those damn creatures.\"");
    d2 = Dialogue("Shrugmini: \"I was a slave in the underworld once. I served devils as they saught to take over the surface and abuse innocent mortals for their own personal gain. I was born a human just like you, but was taken and slowly transformed during my time in the underworld. When I finally escaped, I was discriminated against in the city and became an outcast. It's been rough, but having devil skin isn't so bad once you get used to it.\"",
                {"\"I'm sorry you had to go through that.\"", "\"You're tough. I bet it wasn't so bad for you down there.\""});
    d2.addApproval("Shrugmini", 2, 2);
    d3 = Dialogue("Shrugmini: \"It's in the past now. There's no point in dwelling on how bad it was or what could've been different. What matters is that I'm here and ready to kick some cultist ass. Go get some rest. I don't want to be doing all the heavy lifting.\"\n\nShrugmini goes back to playing with squirrels.");
    Interaction shrugminiInteraction = Interaction({d0, d1, d2, d3});
    shrugminiInteraction.addNav(0, 1, 1);
    shrugminiInteraction.addNav(0, 2, 2);
    shrugminiInteraction.addNav(1, 0, 2);
    shrugminiInteraction.addNav(2, 1, 3);
    shrugminiInteraction.addNav(2, 2, 3);
    shrugminiInteraction.addNav(3, 0, -1);

    // IRIS REST A
    d0 = Dialogue(true, "The sun is setting, and Iris seems... sad?\n\nIris: \"Isn't it beautiful? Can you feel it?\"\n\nThe sun warms your skin but slowly the feeling starts to go away as it approaches the horizon. This seems important to Iris, almost as if her life is dedicated to protecting it.",
                -1, -99, -99, "None", "None", "Solari", {"[Solari] \"I understand your dedication. The sun is the source of everything in this world.\"", "\"Beautiful is an understatement.\"", "\"You seem upset about all of this. Are you alright?\"", "\"It will come back tomorrow morning.\""});
    d0.addApproval("Iris", 3, 1);
    d0.addApproval("Iris", 2, 2);
    d0.addApproval("Iris", 2, 3);
    d0.addApproval("Iris", -1, 4);
    d1 = Dialogue("Iris: \"I'm not so sure about that. I hope the others take this situation as seriously as I do, and I can only pray that you will as well. Stay focused, my friend.\"\n\nThe sun has set, and Iris seems to be ready to sleep. As she begins to rest, you notice her whisper prayers in hopes that the sun will greet her in the morning.");
    d2 = Dialogue("Iris: \"You're right. As long as Solari keeps that ball in the sky with all of his power and dedication, everything in this world remains beyond beautiful. I can't let anyone take that away from him, and I certainly can't let anyone take that away from us.\"");
    d3 = Dialogue("Iris: \"Don't worry about me kid. I'm not usually feeling down at dusk, but this is the first night in which I worry I will never see his creation again. As long as the sun rises the next morning, I'll be ready. Until then, sleep well.\"\n\nThe sun has set, and Iris seems to be ready to sleep. As she begins to rest, you notice her whisper prayers in hopes that the sun will greet her in the morning.");
    Interaction irisInteraction = Interaction({d0, d1, d2, d3});
    irisInteraction.addNav(0, 1, 2);
    irisInteraction.addNav(0, 2, 2);
    irisInteraction.addNav(0, 3, 3);
    irisInteraction.addNav(0, 4, 1);
    irisInteraction.addNav(1, 0, -1);
    irisInteraction.addNav(2, 0, 3);
    irisInteraction.addNav(3, 0, -1);

    // HUBURT REST A
    d0 = Dialogue("Hubert seems to be very tired compared to your other allies. \n\nHubert: \"Beautiful night, isn't it buddy? It's refreshing to see nature again after being stuck in there. What do you make of all this?\"",
                {"\"I'm not sure what to think.\"", "\"Seems like people really need our help. I'm worried I won't be able to live up to expectations.\"", "\"I honestly don't want to deal with this.\""});
    d0.addApproval("Hubert", 2, 2);
    d0.addApproval("Hubert", -1, 3);
    d1 = Dialogue("Hubert: \"You're not the only one. It's a lot of responsibility. It isn't just me and you at stake... it's the entire world.\"");
    d2 = Dialogue("Hubert: \"We don't have a choice unfortunately. The sun isn't just good for beaches. People's lives are at stake. Children, leaders, traders, farmers, everyone.\"");
    d3 = Dialogue(true, "Hubert: \"No matter what, don't forget that we're a team. No matter how bad this situation gets, I hope we struggle together if we struggle at all.\"",
                -1, -1, -1, "Paladin", "None", "None", {"[Paladin] \"It's an honor to be by your side Hubert.\"", "\"You seem quick to consider me an ally...\"", "\"I hope so too.\"", "\"Let's not worry too much. We should get some sleep.\""});
    d3.addApproval("Hubert", 2, 3);
    d3.addApproval("Hubert", 2, 1);
    d4 = Dialogue("Hubert: \"You're a good friend. Let's get some rest.\"");
    d5 = Dialogue("Hubert: \"I know a good friend when I see one. Let's get some rest.");
    d6 = Dialogue("Hubert: \"Right. Sleep well buddy.\"");
    Interaction hubertInteraction = Interaction({d0, d1, d2, d3, d4, d5, d6});
    hubertInteraction.addNav(0, 1, 1);
    hubertInteraction.addNav(0, 2, 1);
    hubertInteraction.addNav(0, 3, 2);
    hubertInteraction.addNav(1, 0, 3);
    hubertInteraction.addNav(2, 0, 3);
    hubertInteraction.addNav(3, 1, 4);
    hubertInteraction.addNav(3, 2, 5);
    hubertInteraction.addNav(3, 3, 4);
    hubertInteraction.addNav(3, 4, 6);
    hubertInteraction.addNav(4, 0, -1);
    hubertInteraction.addNav(5, 0, -1);
    hubertInteraction.addNav(6, 0, -1);

    // NOAM REST A
    d0 = Dialogue(true, "As everyone begins to settle for the night, Noam remains awake reading a small book titled \"Spell Gnomenclature\". He doesn't seem very tired and notices you watching.\n\nNoam: \"You were brave for saving me back there. I'm not sure if I'd be strong enough to do the same.\"",
                -1, -1, -1, "Barbarian", "None", "None", {"[Barbarian] \"You'd be strong enough after a few push-ups.\"", "\"I bet you're a lot stronger than you look.\"", "\"No need to be strong if you're smart.\""});
    d0.addApproval("Noam", 2, 3);
    d1 = Dialogue("Noam: \"You're the optimistic type it seems. You remind me of my father. His confidence was unmatched, but unfortunately I feel like I didn't inherit much of that from him. Maybe I'll tell you some stories about him in the future, but for now we should sleep a little bit.\"\n\nNoam closes his book and starts to prepare his bed.");
    Interaction noamInteraction = Interaction({d0, d1});
    noamInteraction.addNav(0, 1, 1);
    noamInteraction.addNav(0, 2, 1);
    noamInteraction.addNav(0, 3, 1);

    // JASPER REST A
    d0 = Dialogue("As you approach the campsite looking for places to set up your bedding, a loud roar from the hells shakes the ground and alerts your entire party. A small inferno appears in the distance as a tall, well-dressed man with red skin and devil horns politely approaches.\n\nJasper: \"Hello friends. My name is Jasper. It's an absolute pleasure to finally introduce myself. May I?\"");
    d1 = Dialogue(false, "Raven: \"Ugh, anyone but you...\"", -1, -1, -1, "None", "Raven", "None", {});
    d2 = Dialogue(false, "You notice Shrugmini slowly back up and hide behind a tree. She seems very startled by this.", -1, -1, -1, "None", "Shrugmini", "None", {});
    d3 = Dialogue(false, "Noam: \"Well that's not something you see every day...\"", -1, -1, -1, "None", "Noam", "None", {});
    d4 = Dialogue(false, "Iris grips the handle of her sword.\n\nIris: \"I already don't like this guy...\"", -1, -1, -1, "None", "Iris", "None", {});
    d5 = Dialogue("Jasper: \"Don't let me appearance decieve you. I am your friend. If it weren't for me, the sun would already be gone. Indeed, I know about your predicament, and I am on your side.\"",
                {"\"That's a relief!\"", "\"You need to leave. Right now.\"", "Slowly reach for your dagger."});
    d5.addApproval("Shrugmini", 2, 2);
    d5.addApproval("Shrugmini", -2, 1);
    d5.addApproval("Raven", 3, 3);
    d5.addApproval("Raven", 3, 2);
    d5.addApproval("Raven", -3, 1);
    d5.addApproval("Iris", 2, 2);
    d5.addApproval("Vivian", -1, 3);
    d6 = Dialogue("Jasper: \"Relax my friend. Let me reiterate, I'm not here to fight you. I am your ally.\"");
    d7 = Dialogue("Jasper: \"When you meet Magnus, he will tell you that the cultists are missing an artifact necessary for their spell. I have it. All I need you to do is listen to Magnus and play your part.\"");
    d8 = Dialogue("Before you even get a chance to respond, Jasper engulfs himself in fire and disappears back into the hells.");
    Interaction jasperInteraction = Interaction({d0, d1, d2, d3, d4, d5, d6, d7, d8});
    jasperInteraction.addNav(0, 0, 1);
    jasperInteraction.addNav(1, 0, 2);
    jasperInteraction.addNav(1, -1, 2);
    jasperInteraction.addNav(2, 0, 3);
    jasperInteraction.addNav(2, -1, 3);
    jasperInteraction.addNav(3, 0, 4);
    jasperInteraction.addNav(3, -1, 4);
    jasperInteraction.addNav(4, 0, 5);
    jasperInteraction.addNav(4, -1, 5);
    jasperInteraction.addNav(5, 1, 7);
    jasperInteraction.addNav(5, 2, 6);
    jasperInteraction.addNav(5, 3, 6);
    jasperInteraction.addNav(6, 0, 7);
    jasperInteraction.addNav(7, 0, 8);
    jasperInteraction.addNav(8, 0, -7);
    jasperInteraction.addQuestUpdate(-1, 11, 0, "Deal with the Devil", "A devil named Jasper appeared at our campsite and claimed to be our friend. We should keep an eye on him.");


    Rest restA = Rest();
    restA.setVivianInteraction(vivianInteraction);
    restA.setIrisInteraction(irisInteraction);
    restA.setNoamInteraction(noamInteraction);
    restA.setRavenInteraction(ravenInteraction);
    restA.setShrugminiInteraction(shrugminiInteraction);
    restA.setHubertInteraction(hubertInteraction);
    restA.setJasperInteraction(jasperInteraction);

    res.endingRest = restA;

    return res;
}
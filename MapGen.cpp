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
    Dialogue d2 = Dialogue(false, "You closely examine the only cell within your line of sight. You see a young, unconscious, female half-elf with black hair and a large raven tattooed to her neck. Looking at her gives you a feeling of danger and uncertainty. It's unclear whether allying with her is a good idea...",
                        -1, -99, -99, "None", "None", "None", {});
    Dialogue d3 = Dialogue(false, "Before you get a chance to check anything else, a massive beam moonlight shoots through the hallway. A radiant energy, one that you realize is fueled by the power of your goddess, burns the skeletons to a crisp. The energy shakes the ground, causing your cell door to open slightly. Strangely, it seems like none the cell doors were locked in the first place.\n\nAfter listening carefully, you're able to hear noises that sound like fighting in the distance. Perhaps this is the source of the energy that freed you...\n\nYou slowly step outside of your cell, thinking about what to do next.",
                        -1, -99, -99, "None", "None", "Selunara", {});
    Dialogue d4 = Dialogue(false, "Before you get a chance to check anything else, a massive beam of light shoots through the hallway. A mysterious radiant energy burns the skeletons to a crisp. The energy shakes the ground, causing your cell door to open slightly. Strangely, it seems like none the cell doors were locked in the first place. \n\nAfter listening carefully, you're able to hear noises that sound like fighting in the distance. Perhaps this is the source of the energy that freed you...\n\nYou slowly step outside of your cell, thinking about what to do next.",
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
    d0 = Dialogue(false, "As you step towards the cell, your vision blurs as you experience a painful headache. You start to lose control of your body, causing you to stand lifelessly in front of the cell door. The half-elf woman who was once trapped in that cell suddenly yet slowly walks towards you.",
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
    d3 = Dialogue(false, "The wolf's body starts glowing and changing shape. In its place, a young, half-elf woman with long bright white hair and baby blue eyes appears.",
                -1, -99, -99, "None", "None", "None", {});
    d4 = Dialogue(false, "Raven: \"We should see what this druid has to say. I'm not confident that she'll be useful in a fight but I trust that my kind will be helpful allies in situations like this.\"",
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
    interaction.addNav(0, 0, 1);
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
    interaction.addQuestUpdate(-1, 4, 2, "Vivian", "Vivian mentioned that the Selunarans raiding the temple were there to find her. Traveling with Vivian may give us more insight into what is happening.");

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
    d1 = Dialogue(false, "Although Raven is hesitant to step near the closet, she begins moving her hands and getting ready to use her magic against the strange creature. \n\nRaven: \"Whatever you are, if you hurt my friend I'll incinerate you.\"",
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
    d0 = Dialogue("You quickly approach the three goblin bullies surrounding the gnome. They look very tough, but you notice that you're able to sneak up on them and kill them easily. Unfortunately, doing this will result in the gnome's death.",
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
                -1, -99, 4, "Rogue", "None", "None", {"[Rogue] [Persuasion] If I were you I'd be handing over all the silver in my pocket.", "Do you think you could come with us and help us escape?", "You owe me nothing. You're free to leave. Good luck!"});
    d0.addApproval("Shrugmini", 2, 1);
    d1 = Dialogue("The gnome runs off happily. Hopefully he's able to find his way out of here.");
    d2 = Dialogue(true, "Noam: \"I'd love to join you! I've learned quite a bit from magic school that could come in handy. Trust me, you won't regret having another brain on your team.\"",
                -1, -99, -99, "Wizard", "None", "None", {"[Wizard] \"Magic school? Traveling with a fellow wizard would certainly come in handy! Come with me.\"", "\"Come with me. Let's figure this out together.\"", "\"On second thought, I think we should part ways.\""});
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
    interaction.addNav(1, 0, -1);
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
    
    return res;
}
#ifndef REST_H
#define REST_H

#include <string>
#include <vector>
#include "Meta.h"
#include "Interaction.h"

class Rest{
private:
    Interaction jasperInteraction;
    Interaction vivianInteraction;
    Interaction ravenInteraction;
    Interaction hubertInteraction;
    Interaction shrugminiInteraction;
    Interaction irisInteraction;
    Interaction noamInteraction;
public:
    Rest();

    void setJasperInteraction(Interaction interaction);
    void setVivianInteraction(Interaction interaction);
    void setRavenInteraction(Interaction interaction);
    void setHubertInteraction(Interaction interaction);
    void setShrugminiInteraction(Interaction interaction);
    void setIrisInteraction(Interaction interaction);
    void setNoamInteraction(Interaction interaction);

    void executeRest(Meta &meta);
};

#endif
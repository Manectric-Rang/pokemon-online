#ifndef BATTLERBY_H
#define BATTLERBY_H

#include "battlebase.h"

class BattleRBY : public BattleBase
{
public:
    BattleRBY(Player &p1, Player &p2, const ChallengeInfo &additionnalData, int id, int nteam1, int nteam2, PluginManager *p);
    ~BattleRBY();

    typedef void (*MechanicsFunction) (int source, int target, BattleRBY &b);

    void inflictDamage(int player, int damage, int source, bool straightattack=false, bool goForSub=false);
    void losePP(int player, int move, int loss=1);
    int calculateDamage(int player, int target);
    bool hadSubstitute(int player);
    void useAttack(int player, int attack, bool specialOccurence=false, bool notify=true);
    void changeTempMove(int player, int slot, int move);
protected:
    void endTurn();
    void initializeEndTurnFunctions();
    void changeStatus(int player, int status, bool tell=false, int turns=0);
    int getStat(int poke, int stat);
    void sendPoke(int player, int poke, bool silent);
    BattleChoice &choice (int p);
    BattleChoices createChoice(int slot);
    void analyzeChoices();
    bool testAccuracy(int player, int target, bool silent=false);
    void inflictRecoil(int x, int target);

    void personalEndTurn(int player);
    void setupMove(int i, int move);
private:
    BattleChoice choices[2];

    BasicPokeInfo pokes[2];

    struct SlotMemory {
        SlotMemory() {
            switchCount = 0;
        }

        quint16 switchCount;
    };

    SlotMemory slotzones[2];

    TurnMemory turnzones[2];

    BasicMoveInfo moves[2];

    context pokeMems[2];
    context turnMems[2];

    BasicPokeInfo &fpoke(int i) {return pokes[i];}
    const BasicPokeInfo &fpoke(int i) const {return pokes[i];}
    SlotMemory &slotMemory(int i) {return slotzones[i];}
    TurnMemory &turnMem(int i) {return turnzones[i];}
    const TurnMemory &turnMem(int i) const {return turnzones[i];}
    BasicMoveInfo &tmove(int slot) { return moves[slot];}
    const BasicMoveInfo &tmove(int slot) const {return moves[slot];}
    context &pokeMemory(int slot) { return pokeMems[slot];}
    const context & pokeMemory(int slot) const {return pokeMems[slot];}
    context &turnMemory(int slot) { return turnMems[slot];}
    const context & turnMemory(int slot) const {return turnMems[slot];}
public:
    /* Calls the effects of source reacting to name */
    void calleffects(int source, int target, const QString &name);
    /* This time the pokelong effects */
    void callpeffects(int source, int target, const QString &name);
};

Q_DECLARE_METATYPE(BattleRBY::MechanicsFunction)

#endif // BATTLERBY_H
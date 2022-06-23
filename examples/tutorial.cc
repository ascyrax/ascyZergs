// ascyrax

#include <sc2api/sc2_api.h>
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"
#include <iostream>
#include <vector>

#include "sc2api/sc2_unit_filters.h"

#define endl std::endl
#define cout std::cout
#define vector std::vector
#define string std::string
#define pair std::pair
#define make_pair std::make_pair

using namespace sc2;



class Bot : public Agent
{
public:
    vector<Point3D> expansions;
    Point3D base1;
    Point3D base2;
    Point3D opBase1;// opponents starting base
    Point3D opBase2;// opponents natural
    vector<Point3D>bases;

    //  vibe's silver macro build for zerg
    const Unit* overlord1;
    const Unit* overlord2;
    Units overlords, drones;

    vector<const Unit*> idleLarvas, idleDrones, idleOverlords, idleHatcheries, idleQueens, idleOverseers, idleZergs;
    int gameLoop = 0; // Observation()->GetGameLoop();
    int minerals = 0; // Observation()->GetMinerals();
    int vespene = 0;  // Observation()->GetVespene();
    int foodCap = 0;     // Observation()->GetFoodCap();
    int foodUsed = 0;    // Observation()->GetFoodUsed();
    int foodArmy = 0;    // Observation()->GetFoodArmy();
    int foodWorkers = 0; // Observation()->GetFoodWorkers();
    int idleWorkerCnt = 0; // Observation()->GetIdleWorkerCount();
    int armyCnt = 0;       // Observation()->GetArmyCount();
    // bug. GetLarvaCnt always returns 0.
    // int larvaCnt =0;// Observation()->GetLarvaCount();
    int larvaCnt = 0; // idleLarvas.size();


    // variables till first 2 bases reach the saturation and safety roaches are built
    bool vibeSilverOpeningFinished = false;
    int hatcheryCnt = 1;
    bool flagOverlord14 = true; // build an overlord at 14 supply
    bool firstOverlordScoutSent = false;
    bool overlord2Sent = false;
    const Unit* naturalDrone;// drone used to build natural
    
    void getBases() {
        base1 = Observation()->GetStartLocation();
        vector<pair<double, int>>v;
        for (int i = 0; i < expansions.size();i++) {
            double dist = Distance2D(base1, expansions[i]);
            v.push_back(make_pair(dist, i));
        }

        sort(v.begin(), v.end());
        base2 = expansions[v[1].second];
        opBase1 = expansions[v.back().second];
        opBase2 = expansions[v[v.size() - 2].second];
        for (auto el : v) 
            bases.push_back(expansions[el.second]); 
    }
    virtual void OnGameStart() final
    {
        cout << endl << endl << "HELLO ASCYRAX. GAME STARTED." << endl << endl;

        cout << "checking and caching the possible expansions." << endl;
        expansions = search::CalculateExpansionLocations(Observation(), Query());

        // getting all the bases
        cout << "getting all the bases." << endl;
        getBases();
    }
    

    virtual void OnUnitIdle(const Unit *unit)
    {
        if (unit->unit_type == UNIT_TYPEID::ZERG_LARVA)
            idleLarvas.push_back(unit);
        else if (unit->unit_type == UNIT_TYPEID::ZERG_DRONE)
            idleDrones.push_back(unit);
        else if (unit->unit_type == UNIT_TYPEID::ZERG_OVERLORD)
            idleOverlords.push_back(unit);
        else if (unit->unit_type == UNIT_TYPEID::ZERG_HATCHERY)
            idleHatcheries.push_back(unit);
        else if (unit->unit_type == UNIT_TYPEID::ZERG_QUEEN)
            idleQueens.push_back(unit);
        else if (unit->unit_type == UNIT_TYPEID::ZERG_OVERSEER)
            idleOverseers.push_back(unit);
    }

    virtual void OnUnitCreated(const Unit *unit)
    {
        cout << "A " << UnitTypeToName(unit->unit_type) << " was created during gameLoop: "<<gameLoop<<"." << endl;
    }

    virtual void OnGameEnd()
    {
        cout << endl << endl<< "BYE ASCYRAX. GAME ENDED." << endl << endl;
    }

    // coordinator.update() forwards the game by a certain amount of game steps
    // after a step is completed, an observation is received => client events are run
    // Our OnStep function is run after the client events.

    void trainDrone()
    {
        const Unit *larva = Observation()->GetUnit(idleLarvas.back()->tag);
        Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_DRONE);
        idleLarvas.erase(idleLarvas.end()-1);
        larvaCnt = idleLarvas.size();
        return;
    }
    void trainOverlord()
    {
        const Unit *larva = Observation()->GetUnit(idleLarvas.back()->tag);
        Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_OVERLORD);
        idleLarvas.erase(idleLarvas.end()-1);
        return;
    }

    void getValues() {
        gameLoop = Observation()->GetGameLoop();

        minerals = Observation()->GetMinerals();
        vespene = Observation()->GetVespene();

        foodCap = Observation()->GetFoodCap();
        foodUsed = Observation()->GetFoodUsed();
        foodArmy = Observation()->GetFoodArmy();
        foodWorkers = Observation()->GetFoodWorkers();

        idleWorkerCnt = Observation()->GetIdleWorkerCount();
        armyCnt = Observation()->GetArmyCount();
        // bug. GetLarvaCnt always returns 0.
        // larvaCnt = Observation()->GetLarvaCount();
        larvaCnt = idleLarvas.size();
    }


    // scouting functions
    void scoutOpponentsNatural(const Unit* scoutingUnit) {
        // assuming opponent's natural is the second farthest expansion from my starting expansion
        Actions()->UnitCommand(scoutingUnit, ABILITY_ID::SMART,bases[bases.size()-1]);
        firstOverlordScoutSent = true;
    }
    void scoutMyNatural(const Unit* scoutingUnit) {
        Actions()->UnitCommand(scoutingUnit, ABILITY_ID::SMART, bases[1]);
        // base2= bases[1].
        overlord2Sent = true;
    }
    // building
    void buildMyNatural(const Unit* buildingUnit) {
        if (Query()->Placement(ABILITY_ID::BUILD_HATCHERY, bases[1], buildingUnit)) {
            Actions()->UnitCommand(buildingUnit, ABILITY_ID::BUILD_HATCHERY, bases[1]);
            hatcheryCnt++;
        }
    }

    void vibeSilverOpening() {

       overlords = Observation()->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::ZERG_OVERLORD));

        // send scouting to natural
        if (!firstOverlordScoutSent && overlords.size()>=1)
        {
            overlord1 = overlords[0];
            scoutOpponentsNatural(overlord1);
        }
        if (!overlord2Sent && overlords.size()>=2) {
            overlord2 = overlords[1];
            scoutMyNatural(overlord2);
        }

        if (foodCap == 14 && foodUsed == 12)
        {
            // get a larva
            if (larvaCnt && minerals >= 50)
                trainDrone();
        }
        if (foodCap == 14 && foodUsed == 13)
        {
            // get a larva
            if (larvaCnt && flagOverlord14 && minerals >= 100)
            {
                trainOverlord();
                flagOverlord14 = false;
            }
            if (flagOverlord14 == false && minerals >= 50)
                trainDrone();
        }
        if (foodCap == 22 && foodUsed == 14)
        {
            // get two larvas
            if (larvaCnt >= 2 && minerals >= 100)
            {
                trainDrone();
                trainDrone();
            }
        }
        // move towards to the natural at 200 mineral mark
        if (minerals >= 200 && hatcheryCnt==1)
        {
            // get a drone to build the hatchery at natural
            drones = Observation()->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::ZERG_DRONE));
            naturalDrone = drones[0];
            scoutMyNatural(naturalDrone);
        }
        // build the natural at 300 mineral mark
        if (minerals >= 300 && hatcheryCnt == 1) {
            buildMyNatural(naturalDrone);
            vibeSilverOpeningFinished = true;
        }
        
    }

    virtual void OnStep() final
    {
        getValues();
        if (!vibeSilverOpeningFinished)
            vibeSilverOpening();
    }

};

int main(int argc, char *argv[])
{
    Coordinator coordinator;
    coordinator.SetStepSize(1);
    // coordinator.LoadSettings(argc, argv);
    if (!coordinator.LoadSettings(argc, argv))
    {
        return 1;
    }
    // coordinator.SetRealtime(true);

    Bot bot;
    coordinator.SetParticipants({CreateParticipant(Race::Zerg, &bot),
                                 CreateComputer(Race::Random, Difficulty::CheatInsane, AIBuild::Rush)});

    coordinator.LaunchStarcraft();
    coordinator.StartGame(sc2::kMapBelShirVestigeLE);


    while (coordinator.Update())
    {
        SleepFor(20);
    }
    return 0;
}

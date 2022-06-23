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

using namespace sc2;

// global variables
vector<const Unit *> idleLarvas, idleDrones, idleOverlords, idleHatcheries, idleQueens, idleOverseers, idleZergs;
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

bool flagOverlord14 = true; // build an overlord at 14 supply

int nActions = 0;

class Bot : public Agent
{
public:
    vector<Point3D> expansions;
    Point3D startLocation;


    virtual void OnGameStart() final
    {
        cout << "Hello ascyrax. Game started." << endl;
        cout << "checking and caching the possible expansions." << endl;
        expansions = search::CalculateExpansionLocations(Observation(), Query());
        cout << "storing the startLocation too." << endl;
        startLocation = Observation()->GetStartLocation();
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
        cout << "A " << UnitTypeToName(unit->unit_type) << " was created." << endl;
    }

    virtual void OnGameEnd()
    {
        cout << "Bye ascyrax. Game ended." << endl;
    }

    // coordinator.update() forwards the game by a certain amount of game steps
    // after a step is completed, an observation is received => client events are run
    // Our OnStep function is run after the client events.

    void trainDrone()
    {
        const Unit *larva = Observation()->GetUnit(idleLarvas[0]->tag);
        Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_DRONE);
        idleLarvas.erase(idleLarvas.begin());
        larvaCnt = idleLarvas.size();
        nActions++;
        return;
    }
    void trainOverlord()
    {
        const Unit *larva = Observation()->GetUnit(idleLarvas[0]->tag);
        Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_OVERLORD);
        idleLarvas.erase(idleLarvas.begin());
        nActions++;
        return;
    }

    virtual void OnStep() final
    {
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

        // get the natural
        if (minerals >= 200)
        {
            // get a drone to build the hatchery at natural
            Units drones = Observation()->GetUnits(Unit::Alliance::Self,IsUnit(UNIT_TYPEID::ZERG_DRONE));
            Point3D natural;
            double minDist = 1e9;
            for (auto el : expansions) {
                if (Query()->Placement(ABILITY_ID::BUILD_HATCHERY, el, drones[0])) {
                    float dist = Distance2D(startLocation, el);
                    if (dist < minDist) {
                        minDist = dist;
                        natural = el;
                    }
                }
            }
            Actions()->UnitCommand(drones[0], ABILITY_ID::BUILD_HATCHERY, natural);
        }
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

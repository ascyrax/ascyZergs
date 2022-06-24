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

    // GAME VARIABLES

    // LOCATION AND BASES
    vector<Point3D> expansions;
    vector<Point3D>bases;
    int nBases = 0;
    Point3D base1, base2, base3, base4, base5, base6;
    Point3D opBase1, opBase2, opBase3, opBase4, opBase5, opBase6;// opponents starting base
    Point3D stagingLocation; // unused for now

    // UNITS AND BUILDINGS AND RESOURCES
    Units overlords, drones, hatcheries, larvas, eggs, lairs, hives, evoChambers
        , spawningPools, roachWarrens, hydraliskDens, extractors;
    int gameLoop = 0;
    int minerals = 0, vespene = 0;
    int maxSupply = 0, currentSupply = 0, armySupply = 0, armyCnt = 0;
    int extractorCnt = 0, spawningPoolCnt = 0, hatcheryCnt = 0, lairCnt = 0, hiveCnt = 0,
        roachWarrenCnt=0, hydraliskDenCnt=0,evoChamberCnt=0;
    int overlordCnt = 0, droneCnt = 0, larvaCnt = 0, eggCnt = 0;

    // MISCELLANEOUS
    vector<UpgradeID> upgrades;

    // EARLY_A
    bool overlord14Trained = false; // build an overlord at 14 supply
    bool firstOverlordScoutSent = false;
    bool overlord2Sent = false;
    const Unit* naturalDrone;// drone used to build natural
    bool naturalDroneSent = false; // whether natural drone is sent towards the natural at 200 mineral mark or not.
    int roachCnt = 0;
    const Unit* overlord1;
    const Unit* overlord2;

    // EARLY_B

    // EARLY_C



    virtual void OnGameStart() final
    {
        cout << endl << endl << "HELLO ASCYRAX." << endl << endl;

        //cout << "checking and caching the possible expansions." << endl;
        expansions = search::CalculateExpansionLocations(Observation(), Query());

        // getting all the bases
        //cout << "getting all the bases." << endl;
        getBases();
        getValues();
    }

    virtual void OnUnitIdle(const Unit *unit)
    {
        ;// do nothing for now
    }

    virtual void OnUnitCreated(const Unit *unit)
    {
        //cout << "A " << UnitTypeToName(unit->unit_type) << " was created during gameLoop: "<<gameLoop<<"." << endl;
    }


    // coordinator.update() forwards the game by a certain amount of game steps
    // after a step is completed, an observation is received => client events are run
    // Our OnStep function is run after the client events.


    void getBases() {
        base1 = Observation()->GetStartLocation();

        vector<pair<double, int>>v;
        for (int i = 0; i < expansions.size(); i++) {
            if (expansions[i].x == 0 && expansions[i].y == 0)continue;
            double dist = Distance2D(base1, expansions[i]);
            v.push_back(make_pair(dist, i));
        }

        sort(v.begin(), v.end());

        for (auto el : v)
            bases.push_back(expansions[el.second]);
        nBases = bases.size();
        base2 = bases[0];
        base3 = bases[1];
        base4 = bases[2];
        base5 = bases[3];
        base6 = bases[4];
        opBase1 = bases[nBases - 1];
        opBase2 = bases[nBases - 2];
        opBase3 = bases[nBases - 3];
        opBase4 = bases[nBases - 4];
        opBase5 = bases[nBases - 5];
        opBase6 = bases[nBases - 6];
    }

    void getValues() {
        gameLoop = Observation()->GetGameLoop();

        minerals = Observation()->GetMinerals();
        vespene = Observation()->GetVespene();

        maxSupply = Observation()->GetFoodCap();
        currentSupply = Observation()->GetFoodUsed();
        armySupply = Observation()->GetFoodArmy();
        armyCnt = Observation()->GetArmyCount();



        overlords = getUnits(UNIT_TYPEID::ZERG_OVERLORD);
        drones = getUnits(UNIT_TYPEID::ZERG_DRONE);
        hatcheries = getUnits(UNIT_TYPEID::ZERG_HATCHERY);
        larvas = getUnits(UNIT_TYPEID::ZERG_LARVA);
        eggs = getUnits(UNIT_TYPEID::ZERG_EGG);

        droneCnt = drones.size();
        overlordCnt = overlords.size();
        hatcheryCnt = hatcheries.size();
        larvaCnt = larvas.size();
        eggCnt = eggs.size();

        // conting the drones which are still egg
        for (auto el : eggs) {
            if (!el->orders.empty()) {
                if (el->orders.front().ability_id == ABILITY_ID::TRAIN_DRONE)
                    droneCnt++;
            }
        }

        // counting the overlords which are still egg
        for (auto el : eggs) {
            if (!el->orders.empty()) {
                if (el->orders.front().ability_id == ABILITY_ID::TRAIN_OVERLORD)
                    overlordCnt++;
            }
        }

        upgrades = Observation()->GetUpgrades();
        spawningPools = getUnits(UNIT_TYPEID::ZERG_SPAWNINGPOOL);
        spawningPoolCnt = spawningPools.size();
        roachWarrens = getUnits(UNIT_TYPEID::ZERG_ROACHWARREN);
        roachWarrenCnt = roachWarrens.size();
        evoChambers = getUnits(UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER);
        evoChamberCnt = evoChambers.size();
        hydraliskDens = getUnits(UNIT_TYPEID::ZERG_HYDRALISKDEN);
        hydraliskDenCnt = hydraliskDens.size();
        extractors = getUnits(UNIT_TYPEID::ZERG_EXTRACTOR);
        extractorCnt = extractors.size();

    }

    Units getUnits(UNIT_TYPEID unitType) {
        return Observation()->GetUnits(Unit::Alliance::Self, IsUnit(unitType));
    }


    bool trainDrone()
    {
        if (larvaCnt == 0)return false;
        const Unit* larva = larvas.back();
        Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_DRONE);
        larvas.erase(larvas.end() - 1);
        larvaCnt = larvas.size();
        return true;
    }

    bool trainOverlord()
    {
        if (larvaCnt == 0)return false;
        const Unit* larva = larvas.back();
        Actions()->UnitCommand(larva, ABILITY_ID::TRAIN_OVERLORD);
        larvas.erase(larvas.end() - 1);
        return true;
    }

    bool TryBuildStructure(AbilityID ability_type_for_structure, UnitTypeID unit_type, Point2D location, bool isExpansion = false) {
        const ObservationInterface* observation = Observation();
        Units workers = observation->GetUnits(Unit::Alliance::Self, IsUnit(unit_type));

        //if we have no workers Don't build
        if (workers.empty()) {
            return false;
        }

        // Check to see if there is already a worker heading out to build it
        for (const auto& worker : workers) {
            for (const auto& order : worker->orders) {
                if (order.ability_id == ability_type_for_structure) {
                    return false;
                }
            }
        }

        // If no worker is already building one, get a random worker to build one
        const Unit* unit = GetRandomEntry(workers);

        // Check to see if unit can make it there
        if (Query()->PathingDistance(unit, location) < 0.1f) {
            return false;
        }
        if (!isExpansion) {
            for (const auto& expansion : bases) {
                if (Distance2D(location, Point2D(expansion.x, expansion.y)) < 7) {
                    return false;
                }
            }
        }
        // Check to see if unit can build there
        if (Query()->Placement(ability_type_for_structure, location)) {
            Actions()->UnitCommand(unit, ability_type_for_structure, location);
            return true;
        }
        return false;

    }

    bool TryBuildOnCreep(AbilityID ability_type_for_structure, UnitTypeID unit_type) {
        float rx = GetRandomScalar();
        float ry = GetRandomScalar();
        Point2D build_location = Point2D(base1.x + rx * 15, base1.y + ry * 15);

        if (Observation()->HasCreep(build_location)) {
            return TryBuildStructure(ability_type_for_structure, unit_type, build_location, false);// false => this is not an expansion
        }
        return false;
    }



    // EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....
    // SCOUTING
    void scoutOpponentsNatural(const Unit* scoutingUnit) {
        // assuming opponent's natural is the second farthest expansion from my starting expansion
        cout << "1st overlord sent to opponent's natural: " << opBase2.x << " " << opBase2.y << " " << opBase2.z << endl;
        Actions()->UnitCommand(scoutingUnit, ABILITY_ID::SMART,opBase2);
    }

    void scoutMyNatural(const Unit* scoutingUnit) {
        Actions()->UnitCommand(scoutingUnit, ABILITY_ID::SMART, bases[0]);
    }

    // BUILDING
    
    bool buildMyNatural(const Unit* buildingUnit) {
        if (Query()->Placement(ABILITY_ID::BUILD_HATCHERY, bases[1], buildingUnit)) {
            Actions()->UnitCommand(buildingUnit, ABILITY_ID::BUILD_HATCHERY, bases[0]);
            return true;
        }
        return false;
    }

    bool buildSpawningPool(const Unit* buildingUnit, Point3D hatcheryLocation) {
        return TryBuildOnCreep(ABILITY_ID::BUILD_SPAWNINGPOOL, UNIT_TYPEID::ZERG_DRONE);
    }

    bool buildVespeneGeyser(Point3D targetHatcheryLocation) {
        if (drones.size() == 0)return false;
        // return back if a drone has already been given the order
        for (auto drone : drones) {
            if (!drone->orders.empty()) {
                for (auto order : drone->orders) {
                    if (order.ability_id == ABILITY_ID::BUILD_EXTRACTOR) {
                        return false; // since order already given.
                    }
                }
            }
        }
        const Unit* buildingUnit = GetRandomEntry(drones);
        // find the closest geyser(neutral unit) to the target base and build on it.
        Units geysers = Observation()->GetUnits(Unit::Alliance::Neutral, IsGeyser());

        if (geysers.size() == 0)return false;

        double minDist = 1e9;
        const Unit* closestVespeneGeyser;
        for (const Unit* el : geysers) {
            if (Query()->Placement(ABILITY_ID::BUILD_EXTRACTOR, el->pos, buildingUnit)) {
                double dist = Distance2D(el->pos, targetHatcheryLocation);
                if (dist < minDist) {
                    closestVespeneGeyser = el;
                }
            }
        }
        if (Query()->Placement(ABILITY_ID::BUILD_EXTRACTOR, closestVespeneGeyser->pos,buildingUnit)) {
            Actions()->UnitCommand(buildingUnit, ABILITY_ID::BUILD_EXTRACTOR, closestVespeneGeyser);
            return true;
        }
        return false;
    }

    // EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....EARLY_A.....

    void earlyA() {
        
        //cout << "droneCnt:  " << droneCnt << endl;
        // send 1st overlord as scout to opponent's natural
        if (!firstOverlordScoutSent && overlords.size()>=1)
        {
            overlord1 = overlords[0];
            scoutOpponentsNatural(overlord1);
            firstOverlordScoutSent = true;
        }
        // send 2nd overlord to my natural
        if (!overlord2Sent && overlords.size()==2) {
            for (auto el : overlords) {
                if (el == overlord1)continue;
                else { overlord2 = el; break; }
            }
            scoutMyNatural(overlord2);
            overlord2Sent = true;
        }


        if (hatcheryCnt == 1) {
            // build drone as soon as the game starts
            if (droneCnt < 13)
            {
                if (minerals >= 50)
                    trainDrone();
                return;
            }

            // build an overlord next
            if (overlordCnt == 1)
            {
                // get a larva
                if (minerals >= 100)
                    trainOverlord();
                return;
            }
            if (overlordCnt == 2 && maxSupply == 14 && droneCnt==13) {
                if (minerals >= 50)
                    trainDrone();
            }

            // draw drones till 16
            if (overlordCnt == 2  && maxSupply==22 && droneCnt < 16) {
                if (minerals >= 50)
                    trainDrone();
                return;
            }

            // expansion time

            // move towards to the natural at 200 mineral mark
            if (droneCnt==16 && minerals >= 160 && !naturalDroneSent)
            {
                // get a drone to build the hatchery at natural
                naturalDrone = drones[0];
                scoutMyNatural(naturalDrone);
                naturalDroneSent = true;
                return;
            }
            // build the natural at 300 mineral mark
            if (minerals >= 300) {
                buildMyNatural(naturalDrone);
                return;
            }
        }
        else if (hatcheryCnt == 2) {
            if (droneCnt < 18) {
                if (minerals >= 50)
                    trainDrone();
                return;
            }

            // hatchery==2 && droneCnt==18
            if (spawningPoolCnt == 0) {
                if (minerals >= 150 && buildSpawningPool(drones[0], base1));
                return;
            }

            if (spawningPoolCnt == 1 && droneCnt < 20) {
                if (minerals >= 50)
                    trainDrone();
                return;
            }

            if (extractorCnt == 0) {
                if (minerals >= 30 && buildVespeneGeyser(base1));
                return;
            }
        }
        

        // EARLY_A PHASE OF VIBE'S ZERG BUILD ENDS.
    }

    void earlyB() {

    }

    void earlyC() {

    }
    
    virtual void OnStep() final
    {
        getValues();

        if (extractorCnt < 1) {
            earlyA();
        }
        else if(hatcheryCnt<3 && roachCnt<6){
            earlyB();
        }
        else if (hatcheryCnt < 4 && maxSupply < 120 && droneCnt < 120) {
            earlyC();
        }
        
    }

    virtual void OnGameEnd()
    {
        cout << endl << endl << "BYE ASCYRAX." << endl << endl;
    }

};

int main(int argc, char *argv[])
{
    Coordinator coordinator;
    coordinator.SetStepSize(1);
    if (!coordinator.LoadSettings(argc, argv))
        return 1;
    Bot bot;
    coordinator.SetParticipants({CreateParticipant(Race::Zerg, &bot),
                                 CreateComputer(Race::Random, Difficulty::CheatInsane, AIBuild::Rush)});
    coordinator.LaunchStarcraft();
    coordinator.StartGame(sc2::kMapBelShirVestigeLE);



    while (coordinator.Update())
        SleepFor(5);
    return 0;
}



// CONCEPTS
// droneCnt = dronesPresent + eggs(which are morphing into drones)
// hatcheryCnt = already built + currently building hatcheries
// GetUnits(Unit::Alliance::Self,IsUnit(UNIT_TYPEID::ZERG_DRONES)) -> will not give the eggs which are morphing into drones. It returns only the already built drones.

// BUGS
//  //// bug. GetLarvaCnt always returns 0.
        // larvaCnt = Observation()->GetLarvaCount();

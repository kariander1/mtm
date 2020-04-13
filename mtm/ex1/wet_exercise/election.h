//
// Created by Ortal on 3/12/2020.
//

#ifndef MTM_ELECTION_H
#define MTM_ELECTION_H

#include "mtm_map/map.h"

typedef struct election_t* Election;

typedef enum ElectionResult_t {
    ELECTION_OUT_OF_MEMORY,
    ELECTION_NULL_ARGUMENT,
    ELECTION_SUCCESS,
    ELECTION_INVALID_ID,
    ELECTION_TRIBE_ALREADY_EXIST,
    ELECTION_INVALID_NAME,
    ELECTION_AREA_ALREADY_EXIST,
    ELECTION_TRIBE_NOT_EXIST,
    ELECTION_AREA_NOT_EXIST,
    ELECTION_INVALID_VOTES
} ElectionResult;

typedef bool (*AreaConditionFunction) (int);

Election electionCreate(); // Shelly

void electionDestroy(Election election); // Shai

ElectionResult electionAddTribe (Election election, int tribe_id, const char* tribe_name); // Shelly

ElectionResult electionAddArea(Election election, int area_id, const char* area_name); // Shai

const char* electionGetTribeName (Election election, int tribe_id); // Shelly

ElectionResult electionAddVote (Election election, int area_id, int tribe_id, int num_of_votes); // Shai

ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes); // Shelly

ElectionResult electionSetTribeName (Election election, int tribe_id, const char* tribe_name); // Shai

ElectionResult electionRemoveTribe (Election election, int tribe_id); // Shai

ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area); //Shelly

Map electionComputeAreasToTribesMapping (Election election); // UNITED!

#endif //MTM_ELECTION_H
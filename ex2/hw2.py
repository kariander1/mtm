def printCompetitor(competitor):
    '''
    Given the data of a competitor, the function prints it in a specific format.
    Arguments:
        competitor: {'competition name': competition_name, 'competition type': competition_type,
                        'competitor id': competitor_id, 'competitor country': competitor_country, 
                        'result': result}
    '''
    competition_name = competitor['competition name']
    competition_type = competitor['competition type']
    competitor_id = competitor['competitor id']
    competitor_country = competitor['competitor country']
    result = competitor['result']
    
    print(f'Competitor {competitor_id} from {competitor_country} participated in {competition_name} ({competition_type}) and scored {result}')


def printCompetitionResults(competition_name, winning_gold_country, winning_silver_country, winning_bronze_country):
    '''
    Given a competition name and its champs countries, the function prints the winning countries 
        in that competition in a specific format.
    Arguments:
        competition_name: the competition name
        winning_gold_country, winning_silver_country, winning_bronze_country: the champs countries
    '''
    undef_country = 'undef_country'
    countries = [country for country in [winning_gold_country, winning_silver_country, winning_bronze_country] if country != undef_country]
    print(f'The winning competitors in {competition_name} are from: {countries}')


def key_sort_competitor(competitor):
    '''
    A helper function that creates a special key for sorting competitors.
    Arguments:
        competitor: a dictionary contains the data of a competitor in the following format: 
                    {'competition name': competition_name, 'competition type': competition_type,
                        'competitor id': competitor_id, 'competitor country': competitor_country, 
                        'result': result}
    '''
    competition_name = competitor['competition name']
    result = competitor['result']
    return (competition_name, result)


def readParseData(file_name):
    '''
    Given a file name, the function returns a list of competitors.
    Arguments: 
        file_name: the input file name. Assume that the input file is in the directory of this script.
    Return value:
        A list of competitors, such that every record is a dictionary, in the following format:
            {'competition name': competition_name, 'competition type': competition_type,
                'competitor id': competitor_id, 'competitor country': competitor_country, 
                'result': result}
    '''
    competitors_in_competitions = []
    competitors = {}  # ID -> Country
    competitor_keyword = "competitor"
    competitor_mapping={
        1 : "competitor id",
        2 : "competitor country"
    }

    competitions = [] # List of dicts of competitions
    competition_keyword = "competition"
    competition_mapping = {
        1: "competition name",
        2: "competitor id",
        3: "competition type",
        4: "result"
    }
    keys_types ={ # For parsing correct type of values. Will call the int() or str() function
        "competition name" : str,
        "competition type" : str,
        "competitor id" : int,
        "competitor country" : str,
        "result" : int
    }
    keyword_to_mapping = {

        competitor_keyword : {  "mapping" : competitor_mapping,
                                "collection" : competitors,
                                "method" : addCompetitor},

        competition_keyword : { "mapping" : competition_mapping,
                                "collection" : competitions,
                                "method" : addCompetition},
    }
    field_delimiter = ' '
    new_line_char = '\n'
    file = open(file_name, 'r')
    file_text = file.read()
    lines = file_text.split(new_line_char)
    for line in lines:
        if(line ==''): #Empty line (like in EOF)
            continue
        segements = line.split(field_delimiter)
        # Assuming we have no empty lines
        keyword = segements[0]
        mapping = keyword_to_mapping[keyword]["mapping"]
        collection = keyword_to_mapping[keyword]["collection"]
        add_method = keyword_to_mapping[keyword]["method"]

        current_dict ={}
        for index in mapping:
            current_key = mapping[index]
            current_dict[current_key] = keys_types[current_key](segements[index])
        add_method(current_dict,collection)
    file.close()
    competitors_in_competitions_keys = ["competition name","competition type","competitor id","competitor country","result"]
    return mergeCompetitions(competitors,competitions,competitors_in_competitions_keys)

def mergeCompetitions(competitors,competitions,competitors_in_competitions_keys):
    '''
    Given competitors and competitions, this method merges them to the desired 
    competitors_in_competitions list. Instructions to fields of each dictionary
    in the list are depicted in the competitors_in_competitions_keys arguement
    Arguments:
        competitions: a list of dictionaries that defines the competitions
        competitors: dictionary of competitors
        competitors_in_competitions_keys: keys for the new dictionary
    Retuen value:
        competitors_in_competitions list of dictionaries
    '''

    competitors_in_competitions=[]
    for competition in competitions:
        new_dict = {}
        for i in range(len(competitors_in_competitions_keys)):
            key = competitors_in_competitions_keys[i]
            if(key == "competitor country"):
                value = competitors[competition["competitor id"]]
            else:
                value = competition[key]
            new_dict[key]=value
        competitors_in_competitions.append(new_dict)
    return competitors_in_competitions
def addCompetitor(competitor_dict,competitors):
    '''
    Given competitor dictionary and competioners collection, this method handles adding it to
    the new competitiors dictionary.
    This method creates the dictionary such that the key is the ID and value the country name
    Arguments:
        competitor_dict: a dictionary that defines the competitor
        competitors: collections to add the competitor to
    Retuen value:
        NONE
    '''
    #Assumes competitor will always have 2 fields, while first is ID
    i=0
    for key in competitor_dict:
        if(i == 0) :
            id = competitor_dict[key]
        else:
            country = competitor_dict[key]
        i+=1
    competitors[id]=country

def addCompetition(competition_dict,competitions):
    '''
    Given competition dictionary and competitions collection, this method handles adding it to
    the new competitions list.
    Arguments:
        competition_dict: a dictionary that defines the competition
        competitions: collections to add the competition to
    Retuen value:
        NONE
    '''
    competitions.append(competition_dict)

def calcCompetitionsResults(competitors_in_competitions):
    '''
    Given the data of the competitors, the function returns the champs countries for each competition.
    Arguments:
        competitors_in_competitions: A list that contains the data of the competitors
                                    (see readParseData return value for more info)
    Retuen value:
        A list of competitions and their champs (list of lists). 
        Every record in the list contains the competition name and the champs, in the following format:
        [competition_name, winning_gold_country, winning_silver_country, winning_bronze_country]
    '''
    competition_list = [] # list of all competition names
    # competition_dictionary =  {competition_name:{
    #                               type : "",
    #                               participants : [list of participants], 
    #                               countries : [list of countries by participants],
    #                               results: [list of results by participants] }, 
    #                            next_competition .....
    # }
    competition_dictionary = {} 
    forbidden_participants = {} # competition -> [ids]
    competitors_keys = ['competition name', 'competition type','competitor id','competitor country', 'result']
    competition_dictionary_keys = ['type','participants', 'countries', 'results' ]
    # for dictionary in the competitors_in_competitions list
    for parameters in competitors_in_competitions:
        parameter_name = parameters[competitors_keys[0]]
        parameter_id = parameters[competitors_keys[2]]
        parameter_country = parameters[competitors_keys[3]]
        parameter_result = parameters[competitors_keys[4]]
        
        if (parameter_name not in  competition_list): # check if the competition exsists
            competition_list.append(parameter_name)
            initializeParametersOfCompetition (competition_dictionary, parameters, competitors_keys,competition_dictionary_keys )
            initializeForbiddenParticipants(forbidden_participants, parameter_name)
        
        current_dictionary = competition_dictionary[parameter_name]

        if (parameter_id in current_dictionary[competition_dictionary_keys[1]]): #if the participant is already in the competition
            removeParticipant(current_dictionary, parameter_id, competition_dictionary_keys )
            # add id to forbidden lists of this competition
            forbidden_participants[parameter_name].append(parameter_id)
            continue

        if (parameter_id in forbidden_participants[parameter_name]):
            continue

        appendCompetitorToCompetition(current_dictionary, parameter_id, parameter_country, parameter_result, competition_dictionary_keys )
        
    return getListOfWinners(competition_dictionary, competition_list, competition_dictionary_keys)


def initializeParametersOfCompetition(current_competition_dictionary, parameters , competitors_keys, dictionary_keys):
    '''
    Given the data of the competitors and the competitions, the function initialize the competition dictionary.
    Arguments:
        current_competition_dictionary: A empty dictionary for the current competition
        parameters: The current dictionary in the list of competitors_in_competitions
        competitors_keys: The keys of the dictionaries in competitors_in_competitions
        dictionary_keys: The keys of the new current_competition_dictionary
    Retuen value:
        NONE
    '''
    competition_name = parameters[competitors_keys[0]] 
    competition_type = parameters[competitors_keys[1]]
    current_competition_dictionary[competition_name] = {} 
    current_competition_dictionary[competition_name][dictionary_keys[0]] = competition_type

    for x in range(1,len(dictionary_keys)): #create a list of participants, countries, results
        current_competition_dictionary[competition_name][dictionary_keys[x]] = []

def initializeForbiddenParticipants(forbidden_list, competition_name):
    '''
    Given the forbidden competitors list, the function adds the new competition to the dictionary with an empty list.
    Arguments:
        forbidden_list: A  dictionary containing the forbidden compatitors for each competition
        competition_name: The name of the current competition
    Retuen value:
        NONE
    '''
    forbidden_list[competition_name] = []


def removeParticipant(current_competition_dictionary, competitor_id , dictionary_keys):
    '''
    Given the data of the current competition and the competitor id, the function removes the competitor id from the competition.
    Arguments:
        current_competition_dictionary: A  dictionary containing data about the current competition
                                       (lists of compatitors, their counrty and results)
        competitor_id: The compatitor id to remove from competition
        dictionary_keys: The keys of the current_competition_dictionary
    Retuen value:
        NONE
    '''
    participant_index = current_competition_dictionary[dictionary_keys[1]].index(competitor_id)
    for x in range(1,len(dictionary_keys)):
        list_to_delete_value = current_competition_dictionary[dictionary_keys[x]]
        del list_to_delete_value[participant_index]

def appendCompetitorToCompetition(current_competition_dictionary, id, country, result, dictionary_keys ):
    '''
    Given the data of the current competition, the competitor id, country and result, 
    the function appends the competitor to the competition.
    Arguments:
        current_competition_dictionary: A  dictionary containing data about the current competition
                                       (lists of compatitors, their counrty and results)
        competitor_id: The compatitor id to remove from competition
        dictionary_keys: The keys of the current_competition_dictionary
    Retuen value:
        NONE
    '''
    current_competition_dictionary[dictionary_keys[1]].append(id)
    current_competition_dictionary[dictionary_keys[2]].append(country)
    current_competition_dictionary[dictionary_keys[3]].append(result)

def getListOfWinners(competition_dictionary, competition_list, dictionary_keys):
    '''
    Given the data of all competitions and the competition list id,
    the function returns the list of competitions_champs.
    Arguments:
        competition_dictionary: A  dictionary containing data about all competitions
                                       (lists of compatitors, their counrty and results)
        competition_list: A list of all competitions names
        dictionary_keys: The keys of the competition_dictionary
    Retuen value:
        A list of competitions and their champs (for mor information see calcCompetitionsResults).
    '''
    competitions_champs = []
    calculate_winner = {"untimed": getIndexOfMax, "timed": getIndexOfMin, "knockout": getIndexOfMin}

    for competition in competition_list:
        competition_winners_list = []
        competition_winners_list.append(competition)
        current_dictionary = competition_dictionary[competition]
        participants_list = current_dictionary[dictionary_keys[1]]
        results_list = current_dictionary[dictionary_keys[3]]

        if (len(participants_list) == 0):
            continue

        for x in range(3):
            if (len(participants_list) > 0):
                winner_index = calculate_winner[current_dictionary[dictionary_keys[0]]](results_list) 
                competition_winners_list.append(current_dictionary[dictionary_keys[2]][winner_index])
                removeParticipant(current_dictionary, participants_list[winner_index], dictionary_keys ) #remove the winner index
            else: 
                competition_winners_list.append("undef_country")
        competitions_champs.append(competition_winners_list)  
    print(competitions_champs)  
    return competitions_champs

def getIndexOfMax(results_list):
    '''
    Given the results list of the competition returns the index of the maximal result.
    Arguments:
        results_list: A list with all the results of the compatitors in the current competition
    Retuen value:
        The index of the maximal result
    '''
    return results_list.index(max(results_list))

def getIndexOfMin(results_list): # assuming the knockout results are by rank
    '''
    Given the results list of the competition returns the index of the minimal result.
    Arguments:
        results_list: A list with all the results of the compatitors in the current competition
    Retuen value:
        The index of the minimal result
    '''
    return results_list.index(min(results_list))

def partA(file_name = 'input.txt', allow_prints = True):
    # read and parse the input file
    competitors_in_competitions = readParseData(file_name)
    if allow_prints:
        for competitor in sorted(competitors_in_competitions, key=key_sort_competitor):
            printCompetitor(competitor)
    
    # calculate competition results
    competitions_results = calcCompetitionsResults(competitors_in_competitions)
    if allow_prints:
        for competition_result_single in sorted(competitions_results):
            printCompetitionResults(*competition_result_single)
    
    return competitions_results


def partB(file_name = 'input.txt'):
    competitions_results = partA(file_name, allow_prints = False)
    # TODO Part B


if __name__ == "__main__":
    '''
    The main part of the script.
    __main__ is the name of the scope in which top-level code executes.
    
    To run only a single part, comment the line below which correspondes to the part you don't want to run.
    '''    
    file_name = 'input.txt'

    partA(file_name)
    #partB(file_name)
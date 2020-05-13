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
    # TODO Part A, Task 3.4
    

    competitors ={}  # ID -> Country
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
    keys_types ={ # For parsing correct values
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
    new_line_char ='\n'
    file_text = open(file_name, 'r').read()
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
    id= None
    country=None
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
    competitions_champs = []
    # TODO Part A, Task 3.5
    
    return competitions_champs


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
    partB(file_name)
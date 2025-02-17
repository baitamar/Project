extern void input_arrays_initializing(char array[], int len);
extern reserved* addingReservedObjectToList(reserved *head, short type, char *name, short operands);
/*extern int lineParsing(char **input[],char line[], int lineCount, int *numSpaceSegments, int *numCSVsegments);
extern int lineParsingSpaceDeliminated(char *spaceInput[], char line[], char shortLine[],int *numSpaceSegments);
extern int lineParsingCommaDeliminated(char *CSVinput[],char shortLine[], int CSVinputSegment, int *numCSVsegments);
extern void shortenStrings(char line[], char shortLine[], int starting_point);*/
static void initiating_reserved_fixed_words_list(reserved *headFixed);
static void initiating_input_array(char **input[], char *CSVinput[], char *spaceInput[], char firstSpaceSegment[], char secondSpaceSegment[], char thirdSpaceSegment[], char forthSpaceSegment[], char firstCSVSegment[], char secondCSVSegment[], char thirdCSVSegment[], char forthCSVSegment[]);
static void initiating_reserved_non_fixed_words_list(reserved *headNonFixed);
static void powerOfTwoArray(int powerOfTwo[]);

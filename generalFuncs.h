/* in generalfuncs.c */
int lineParsing(char **input[],char line[], int lineCount, int *numSpaceSegments, int *numCSVsegments);
int lineParsingSpaceDeliminated(char *spaceInput[], char line[], char shortLine[],int *numSpaceSegments);
int lineParsingCommaDeliminated(char *CSVinput[],char shortLine[], int CSVinputSegment, int *numCSVsegments);
void input_arrays_initializing(char array[], int len);
void shortenStrings(char line[], char shortLine[], int starting_point);
reserved* addingReservedObjectToList(reserved *head, short type, char *name, short operands);
void translatingNumToBinary(int num, int powerOfTwo[]);
/* in initiating.c */
void initiating(int *filesNum, int argc, reserved *headNonFixed, reserved *headFixed, char **input[], char *CSVinput[], char *spaceInput[], char firstSpaceSegment[], char secondSpaceSegment[], char thirdSpaceSegment[], char forthSpaceSegment[], char firstCSVSegment[], char secondCSVSegment[], char thirdCSVSegment[], char forthCSVSegment[], int poerOfTwo[], codeLine data[], codeLine code[]);
/* in preprocess.c */
int preprocess(char fileBase[], FILE *fPtrOrig, char suffix[], char **input[], reserved *headNonFixed, reserved *headFixed);

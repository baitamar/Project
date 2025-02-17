#include "general.h"

/*
extern void input_arrays_initializing(char array[], int len);
extern int lineParsing(char **input[],char line[], int lineCount, int *numSpaceSegments, int *numCSVsegments);
extern int lineParsingSpaceDeliminated(char *spaceInput[], char line[], char shortLine[],int *numSpaceSegments);
extern int lineParsingCommaDeliminated(char *CSVinput[],char shortLine[], int CSVinputSegment, int *numCSVsegments);
extern void shortenStrings(char line[], char shortLine[], int starting_point);
extern reserved* addingReservedObjectToList(reserved *head, short type, char *name, short operands);
*/

static void lineParsingSpaceInputAndCSVInputEquilibrating(char *spaceInput[], char *CSVinput[], int spaceInputCounter);


/* a function which initializing char arrays with '\0' (NULL char) all along */
void input_arrays_initializing(char array[], int len)
{
int i;
for (i = 0; i<len; i++)
	array[i] = ASCII_VALUE_OF_NULL_CHAR;
}


/* A function which copies the end of a string char based on a given point to another char */
void shortenStrings(char line[], char shortLine[], int starting_point)
{
int i = starting_point;
while (line[i] != ASCII_VALUE_OF_NULL_CHAR && line[i] != ASCII_VALUE_OF_NEW_LINE)
	{
	shortLine[i-starting_point]=line[i];
	i++;
	}
}


int lineParsingSpaceDeliminated(char *spaceInput[], char line[], char shortLine[],int *numSpaceSegments)
{
int spaceInputCounter = 0, segmentCounter = -1, lineCharCounter = 0, deliminatorFlag = FALSE;
char c = line[lineCharCounter];

while((c != ASCII_VALUE_OF_NULL_CHAR) && (c != ASCII_VALUE_OF_COMMA))
	{
	if ((deliminatorFlag == FALSE) && (isspace(c) != 0))	/* new space deliminator encountered */
		{
		deliminatorFlag = TRUE;
		lineCharCounter++;
		c = line[lineCharCounter];
		}
	else if((deliminatorFlag == TRUE) && (isspace(c) != 0)) 	/* space deliminator area continues */
		{
		lineCharCounter++;
		c = line[lineCharCounter];
		}
	else if(deliminatorFlag == TRUE)	/*first non-deliminator char encountered. Char to be copied to appropriate SpaceInput[spaceInputCounter] */
		{
		deliminatorFlag = FALSE;
		spaceInputCounter++;
		segmentCounter = 0;
		spaceInput[spaceInputCounter][segmentCounter] = c;
		lineCharCounter++;
		c = line[lineCharCounter];
		}
	else if(deliminatorFlag == FALSE)	/* string to copy continues */
		{
		segmentCounter++;
		spaceInput[spaceInputCounter][segmentCounter] = c;
		lineCharCounter++;
		c = line[lineCharCounter];
		}
	}
input_arrays_initializing(shortLine, MAXLINE);
shortenStrings(line, shortLine, lineCharCounter);
*numSpaceSegments = spaceInputCounter;/*- 1  */
return spaceInputCounter;
}


/* A function which equilibrates between spaceInput and CSVinput, by taking the last cell in spaceInput and move it to CSVinput. The rational is that technically, spaceInput stops when it hits the first comma. However, essentially, this first comma is already seperating between the first pair of comma seperated segments */
static void lineParsingSpaceInputAndCSVInputEquilibrating(char *spaceInput[], char *CSVinput[], int spaceInputCounter)
{
int CSVinputCounter = FIRST_SEGMENT;
strcpy(CSVinput[CSVinputCounter],spaceInput[spaceInputCounter]);
input_arrays_initializing(spaceInput[spaceInputCounter], SEGMENT_LEN);
}


int lineParsingCommaDeliminated(char *CSVinput[],char shortLine[], int CSVinputSegment, int *numCSVsegments)
{
int lineCharCounter = 0, segmentCounter = -1, deliminatorFlag = FALSE, consecutiveCommasFlag = FALSE;
char c  = shortLine[lineCharCounter];
CSVinputSegment--;
while((c != ASCII_VALUE_OF_NULL_CHAR))
	{
	if ((deliminatorFlag == FALSE) && (c == ASCII_VALUE_OF_COMMA))	/* new space deliminator encountered  */
		{
		deliminatorFlag = TRUE;
		lineCharCounter++;
		c = shortLine[lineCharCounter];
		}
	else if((deliminatorFlag == TRUE) && (c == ASCII_VALUE_OF_COMMA)) 	/* deliminator area continues, which means two consecutive commas*/
		{
		lineCharCounter++;
		c = shortLine[lineCharCounter];
		consecutiveCommasFlag = TRUE;
		}
	else if((deliminatorFlag == TRUE) && (isspace(c) != 0)) 	/* deliminator area continues with space(s)*/
		{
		lineCharCounter++;
		c = shortLine[lineCharCounter];
		}
	else if(deliminatorFlag == TRUE)	/*first non-deliminator char encountered. Char to be copied to appropriate SpaceInput[spaceInputCounter] */
		{
		deliminatorFlag = FALSE;
		CSVinputSegment++;
		segmentCounter = 0;
		CSVinput[CSVinputSegment][segmentCounter] = c;
		lineCharCounter++;
		c = shortLine[lineCharCounter];
		}
	else if(deliminatorFlag == FALSE)	/* string to copy continues */
		{
		segmentCounter++;
		CSVinput[CSVinputSegment][segmentCounter] = c;
		lineCharCounter++;
		c = shortLine[lineCharCounter];
		}
	}
*numCSVsegments = CSVinputSegment ;
return consecutiveCommasFlag;
}


int lineParsing(char **input[],char line[], int lineCount, int *numSpaceSegments, int *numCSVsegments)
{
char shortLine[MAXLINE];
int spaceInputCounter, errorFlag = FALSE;
spaceInputCounter = lineParsingSpaceDeliminated(input[FIRST_SEGMENT], line, shortLine, numSpaceSegments);
/*printf("numSpaceSegments: %d\n",*numSpaceSegments);temp*/
if(strpbrk(line, DELIMINATOR_COMMA) != NULL)	/* Only when there is an occurrence of a comma in line, run the function to equilibrate Space and CSV input arrays */
	lineParsingSpaceInputAndCSVInputEquilibrating(input[FIRST_SEGMENT], input[SECOND_SEGMENT], spaceInputCounter);
errorFlag = lineParsingCommaDeliminated(input[SECOND_SEGMENT], shortLine, SECOND_SEGMENT, numCSVsegments);
if (errorFlag == TRUE)
	printf(ERROR_3,lineCount);
return errorFlag;
}


reserved* addingReservedObjectToList(reserved *head, short type, char *name, short operands)
{
int len = strlen(name), i;
char c;
reserved *temp1, *temp2;
temp2 = (reserved *) malloc(sizeof(reserved));
temp1 = head;
while(temp1->next != NULL)
	temp1 = temp1->next;
temp1->next = temp2;
temp2->next = NULL;
temp2->previous = temp1;
temp2->name = (char *) calloc(SEGMENT_LEN,sizeof(char));
for(i=0; i<len; i++)
	{
	c = name[i];
	temp2->name[i] = c;
	}
temp2->operands = operands;
temp2->type = type;
temp1 = temp2;
return temp2;
}

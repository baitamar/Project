#include "general.h"

/*
extern void input_arrays_initializing(char array[], int len);
extern int lineParsing(char **input[],char line[], int lineCount, int *numSpaceSegments, int *numCSVsegments);
extern int lineParsingSpaceDeliminated(char *spaceInput[], char line[], char shortLine[],int *numSpaceSegments);
extern int lineParsingCommaDeliminated(char *CSVinput[],char shortLine[], int CSVinputSegment, int *numCSVsegments);
extern void shortenStrings(char line[], char shortLine[], int starting_point);
extern reserved* addingReservedObjectToList(reserved *head, short type, char *name, short operands);
extern void translatingNumToBinary(int num, int powerOfTwo[]);
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


void translatingNumToBinary(int num, int powerOfTwo[])
{
int twentyThirdBitMSB = FALSE, twentySecondBit = FALSE, twentyOneBit = FALSE, twentiethBit = FALSE, nineteenthBit = FALSE, eighteenthBit = FALSE, seventeenthBit = FALSE, sixteenthBit = FALSE, fifthteenthBit = FALSE, fourteenthBit = FALSE, thirteenthBit = FALSE, twelvethBit = FALSE, eleventhBit = FALSE, tenthBit = FALSE, ninethBit = FALSE, eighthBit = FALSE, seventhBit = FALSE, sixthBit = FALSE, FifthBit = FALSE, fourthBit = FALSE, thirdBit = FALSE, secondBit = FALSE, firstBit = FALSE, zerothBitLSB = FALSE, binaryTranslation[WORD_LEN], i = 0;

binaryTranslation[0] = twentyThirdBitMSB;
binaryTranslation[1] = twentySecondBit;
binaryTranslation[2] = twentyOneBit;
binaryTranslation[3] = twentiethBit;
binaryTranslation[4] = nineteenthBit;
binaryTranslation[5] = eighteenthBit;
binaryTranslation[6] = seventeenthBit;
binaryTranslation[7] = sixteenthBit;
binaryTranslation[8] = fifthteenthBit;
binaryTranslation[9] = fourteenthBit;
binaryTranslation[10] = thirteenthBit;
binaryTranslation[11] = twelvethBit;
binaryTranslation[12] = eleventhBit;
binaryTranslation[13] = tenthBit;
binaryTranslation[14] = ninethBit;
binaryTranslation[15] = eighthBit;
binaryTranslation[16] = seventhBit;
binaryTranslation[17] = sixthBit;
binaryTranslation[18] = FifthBit;
binaryTranslation[19] = fourthBit;
binaryTranslation[20] = thirdBit;
binaryTranslation[21] = secondBit;
binaryTranslation[22] = firstBit;
binaryTranslation[23] = zerothBitLSB;
while(num > 0)
	{
	for(; i < WORD_LEN; i++) 
		{
		if(num >= powerOfTwo[i])
			{
			binaryTranslation[i] = TRUE;
			num -= powerOfTwo[i];
			}
		}
	}
printf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",binaryTranslation[0], binaryTranslation[1], binaryTranslation[2], binaryTranslation[3], binaryTranslation[4], binaryTranslation[5], binaryTranslation[6], binaryTranslation[7], binaryTranslation[8], binaryTranslation[9], binaryTranslation[10], binaryTranslation[11], binaryTranslation[12], binaryTranslation[13], binaryTranslation[14], binaryTranslation[15], binaryTranslation[16], binaryTranslation[17], binaryTranslation[18], binaryTranslation[19], binaryTranslation[20], binaryTranslation[21], binaryTranslation[22], binaryTranslation[23]);
}

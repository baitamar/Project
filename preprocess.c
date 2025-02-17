#include "general.h"
#include "preprocess.h"

int preprocess(char fileBase[], FILE *fPtrOrig, char suffix[], char **input[], reserved *headNonFixed,  reserved *headFixed)
{
char AmFileName[FILE_NAME_LEN], line[MAXLINE], accomulatingReplacement[MAXLINE * 3], c;
FILE *fPtrAm;
int lineCount = 0, lineParsingError = FALSE, firstMcroCommandError = FALSE, secondMcroCommandError = FALSE, nameError = FALSE, mcroFlag = FALSE, relevantSegment, numSpaceSegments, numCSVsegments, accomulatingReplacementLen = 0, i;
reserved *temp = NULL;
strcpy(AmFileName, fileBase);
strcat(AmFileName, DOT_AM);
fPtrAm = fopen(AmFileName,APPEND_MODE);
input_arrays_initializing(accomulatingReplacement, MAXLINE * 3);
while (fgets(line,MAXLINE,fPtrOrig) != NULL)
	{
	lineCount++;
	lineParsingError = lineParsing(input, line, lineCount, &numSpaceSegments, &numCSVsegments);
	/* temp*/
	/*printf("lineCount: %d\n",lineCount);
	for(i=0; i<4; i++)
		printf("space[i]: %s\n",input[0][i]);
	for(i=0; i<4; i++)
		printf("CSV[i]: %s\n",input[1][i]);	
	 temp*/
	if(isFirstSpaceDeliminatedSegmentALabel(input) == FALSE)	/* if first segment is a label, examine the second segment */
		relevantSegment = FIRST_SEGMENT;
	else
		relevantSegment = SECOND_SEGMENT;
	/* temp*/
	/*if(temp !=NULL)
		printf("2. temp: %s relevantSegment: %d\n",temp->name, relevantSegment);
	else
		printf("2. temp: NULL relevantSegment: %d\n", relevantSegment);
	 temp*/
	if (mcroFlag == FALSE && isRelevantSpaceSegmentReserved(input[FIRST_SEGMENT][relevantSegment], headFixed) != NULL)	/* segment to be examine shows in 																	reservedFixed list. Copy line 																	to .AM file */		
		fputs(line, fPtrAm);
	else if (mcroFlag == FALSE && isRelevantSegmentMcroOperand(input[FIRST_SEGMENT][relevantSegment]) == TRUE)	/* hitting mcro command. If no error shows, 																turn on mcro flag and start process the 															mcro */
		{
		mcroFlag = TRUE;
		if((input[FIRST_SEGMENT][relevantSegment + 2][FIRST_SEGMENT] != ASCII_VALUE_OF_NULL_CHAR) || (input[SECOND_SEGMENT][FIRST_SEGMENT][FIRST_SEGMENT] 			!= ASCII_VALUE_OF_NULL_CHAR))	/* if the first char in	SpcaeInput 2 segments after mcro command or the first char in first segment of CSVinput are 							anything but null char, then there are junk chars alongwith the mcro command. Flag it as an error, but keep 							procesing the line as normal. Otherwise, the program will fail later on when running a full set of commands */
			{			
			printf(ERROR_4,lineCount);
			firstMcroCommandError = TRUE;
			temp = addingReservedObjectToList(headNonFixed, MCRO, input[FIRST_SEGMENT][relevantSegment + 1], -1);
			}
		else if (isRelevantSpaceSegmentReserved(input[FIRST_SEGMENT][relevantSegment + 1], headNonFixed) != NULL && (isRelevantSpaceSegmentReserved(input[FIRST_SEGMENT][relevantSegment + 1], headNonFixed)->type == MCRO))	/*name already exist in NonFixed list, which is not allowed Flag it as an error, but keep 							procesing the line as normal. Otherwise, the program will fail later on when running a full set of commands */
			{
			printf(ERROR_5,lineCount);
			nameError = TRUE;
			temp = addingReservedObjectToList(headNonFixed, MCRO, input[FIRST_SEGMENT][relevantSegment + 1], -1);
			}
		else	/* start process the mcro by creating a NonFixed object for the mcro*/
			temp = addingReservedObjectToList(headNonFixed, MCRO, input[FIRST_SEGMENT][relevantSegment + 1], -1);	
		}
	else if(mcroFlag == TRUE && isEndOfMcro(input[FIRST_SEGMENT][relevantSegment]) == FALSE)	/* in mcro recording, but before the end of it. Record 														line to accomulatingReplacement */
		{
		for(i=0; i<strlen(line); i++)
			{
			c = line[i];
			accomulatingReplacement[accomulatingReplacementLen] = c;
			accomulatingReplacementLen++;
			}	
		} 
	else if(mcroFlag == TRUE && isEndOfMcro(input[FIRST_SEGMENT][relevantSegment]) == TRUE)	/* hitting end of mcro. Stop recording and turn off mcro flag 													again */
		{
		mcroFlag = FALSE;
		accomulatingReplacementLen = 0;
		if((input[FIRST_SEGMENT][relevantSegment + 1][FIRST_SEGMENT] != ASCII_VALUE_OF_NULL_CHAR) || (input[SECOND_SEGMENT][FIRST_SEGMENT][FIRST_SEGMENT] 			!= ASCII_VALUE_OF_NULL_CHAR))	/* if the first char in SpcaeInput one segment after mcro command or the first char in first segment of CSVinput 							are anything but null char, then there are junk chars alongwith the mcro command */
			{			
			printf(ERROR_4,lineCount);
			secondMcroCommandError = TRUE;
			}
		else
			{
			temp->replacement = (char *) calloc(strlen(accomulatingReplacement), sizeof(char));
			strcpy(temp->replacement, accomulatingReplacement);
			}
		} 
	else if(mcroFlag == FALSE && isRelevantSpaceSegmentReserved(input[FIRST_SEGMENT][relevantSegment], headNonFixed) != NULL)	/* Hitting mcro name, which 																		needs to be deployed, 																		unless an earlier error was 																		detacted */	
		{
		temp = isRelevantSpaceSegmentReserved(input[FIRST_SEGMENT][relevantSegment], headNonFixed);
			/* temp*/
			/*if(temp !=NULL)
				printf("14. temp: %s\n",temp->name);
			else
				printf("14. temp: NULL\n");
			 temp*/
		if(temp->type == MCRO)	 /*segment to be examine shows in reservedNonFixed list AND of type mcro. Therefore, it needs to be deployed */
			{
			if(firstMcroCommandError == TRUE || secondMcroCommandError == TRUE || nameError == TRUE)
				continue;
			else
				fputs(temp->replacement, fPtrAm);
			}
		else	 /*at preprocess there aren't suppose to be any other types of objects in NonFixed list (other than a dummy), but as a precaution, if there is such do to a mistake, it should be handled the same as other segments which shows in reservedFixed list, that is to copy line to .AM file */
			{
			fputs(line, fPtrAm);
			/* temp*/
			if(temp !=NULL)
				printf("15. temp: %s\n",temp->name);
			else
				printf("15. temp: NULL\n");
			 /*temp*/
			}
		}
	else if(input[FIRST_SEGMENT][FIRST_SEGMENT][FIRST_SEGMENT] == ASCII_VALUE_OF_NULL_CHAR)	/* empty line, do nothing */
		continue;
	else /* temp comment should errors here invoke the preprocess error, and therefore to delete the .AM file? as a residual category, nothing is supposed to get here. However, one thing that does get here is wrong commands. It is possible that when the project will be tested, false commands will be put in, and possibly, as it ain't supposed to be detected at that stage, it will be expected that a .AM will still be produced */
		printf(ERROR_6,lineCount);
		/* temp comment numCSVsegments & numCSVsegments are not working properly. it it possible here not to use it, and judt iterate through all 4 segmenets of space/CSV arrays. The question is what are numCSVsegments & numCSVsegments good for in the first place and if they can be removed? on the otherhand, keeping and fixing it will make the code slighly more eficient. for now, the 2 variables will not be removed but will be replaced here. In the future, one of the two option should be selected */
	for(i = 0; i<SPACE_SEPERETED_SEGMENTS_NUM; i++)
		input_arrays_initializing(input[FIRST_SEGMENT][i],SEGMENT_LEN);
	for(i = 0; i<CSV_SEGMENTS_NUM; i++)
		input_arrays_initializing(input[SECOND_SEGMENT][i],SEGMENT_LEN);
	}
fclose(fPtrAm);
if (lineParsingError == TRUE || firstMcroCommandError == TRUE || secondMcroCommandError == TRUE || nameError == TRUE)	/* if at least one of the possible errors 																is TRUE, delete the .AM file created and 																return TRUE, which signals an error*/
	{
	/*printf("removing .AM file"); temp */
	remove(AmFileName);
	return TRUE;
	}
return FALSE;
}

static int isFirstSpaceDeliminatedSegmentALabel(char **input[])
{
int labelFlag = FALSE, firstSpaceDeliminatedSegmentLen;
char c;
firstSpaceDeliminatedSegmentLen = strlen(input[FIRST_SEGMENT][FIRST_SEGMENT]);
c = input[FIRST_SEGMENT][FIRST_SEGMENT][firstSpaceDeliminatedSegmentLen];	/* jump to the end of word in input[0][0] */
while(c == ASCII_VALUE_OF_NEW_LINE || (isspace(c) != 0) || c == ASCII_VALUE_OF_NULL_CHAR)	/* if last char is a whitespace, go back one char */
	{
	firstSpaceDeliminatedSegmentLen--;
	c = input[FIRST_SEGMENT][FIRST_SEGMENT][firstSpaceDeliminatedSegmentLen];
	}
if(c ==	ASCII_VALUE_OF_COLON)	/* if the last non-whitespace char is colon, mark as label */
	labelFlag = TRUE;
return labelFlag;
}


static reserved * isRelevantSpaceSegmentReserved(char relevantSegment[], reserved *head)
{
int breakFlag = FALSE, endOfListFlag = FALSE;
reserved *temp;
temp = head;
while(breakFlag == FALSE && endOfListFlag == FALSE && temp != NULL)
	{
	if(strcmp(temp->name, relevantSegment) == 0)
		breakFlag = TRUE;
	if(temp->next != NULL)
		temp = temp->next;
	else
		endOfListFlag = TRUE;
	}
if (breakFlag == FALSE)
	return NULL;
return temp;
}


static int isRelevantSegmentMcroOperand(char relevantSegment[])
{
int mcroFlag = FALSE;
if(strcmp(relevantSegment,MACRO) == 0)
	mcroFlag = TRUE;
return mcroFlag;
}


static int isEndOfMcro(char segment[])
{
int mcroEndFlag = FALSE;
if(strcmp(segment,MCRO_END) == 0)
	mcroEndFlag = TRUE;
return mcroEndFlag;
}

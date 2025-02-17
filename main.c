#include "general.h"
#include "generalFuncs.h"

int main(int argc, char *argv[])
{
int filesNum, errorFlag, completingFlag, powerOfTwo[WORD_LEN], i;
/* file/s name/s*/
char fileBase[FILE_NAME_LEN], currentFile[FILE_NAME_LEN];
/* input line segments holders*/
char **input[NUM_SEGMENTS_TYPES], *CSVinput[CSV_SEGMENTS_NUM], *spaceInput[SPACE_SEPERETED_SEGMENTS_NUM], firstSpaceSegment[SEGMENT_LEN], secondSpaceSegment[SEGMENT_LEN], thirdSpaceSegment[SEGMENT_LEN], forthSpaceSegment[SEGMENT_LEN],firstCSVSegment[SEGMENT_LEN], secondCSVSegment[SEGMENT_LEN], thirdCSVSegment[SEGMENT_LEN], forthCSVSegment[SEGMENT_LEN];
FILE *fPtr;
reserved *headFixed = NULL, *headNonFixed = NULL;
codeLine data[CODLINE_SIZE_JUMPS], code[CODLINE_SIZE_JUMPS];
headNonFixed = (reserved *) malloc(sizeof(reserved));
headFixed = (reserved *) malloc(sizeof(reserved));
if(argc == 1)
	{
	printf(ERROR_1);
	return 0;	/* dummy, to end the program */
	}
initiating(&filesNum, argc, headNonFixed, headFixed, input, CSVinput, spaceInput, firstSpaceSegment, secondSpaceSegment, thirdSpaceSegment, forthSpaceSegment, firstCSVSegment, secondCSVSegment, thirdCSVSegment, forthCSVSegment,powerOfTwo, code, data);
for (i=0; i<filesNum; i++)
	{
	strcpy(fileBase, argv[i+1]);
	strcpy(currentFile, argv[i+1]);
	strcat(currentFile,DOT_AS);
	if(fopen(currentFile,READ_MODE) == NULL)
		printf(ERROR_2,argv[i + 1]);
	else
		{
		errorFlag = FALSE;
		completingFlag = FALSE;
		while (errorFlag == FALSE && completingFlag == FALSE)
			{		
			fPtr = fopen(currentFile,READ_MODE);
			errorFlag = preprocess(fileBase, fPtr, DOT_AM, input, headNonFixed, headFixed);
			fclose(fPtr);
			completingFlag = TRUE; /* temp */
			}
		}
	/* temp comment delete NonFixed list upon finishing up with each file processed*/
	}
return 0; /* dummy */
}

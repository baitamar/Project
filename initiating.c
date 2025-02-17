#include "general.h"
#include "initiating.h"


void initiating(int *filesNum, int argc, reserved *headNonFixed, reserved *headFixed, char **input[], char *CSVinput[], char *spaceInput[], char firstSpaceSegment[], char secondSpaceSegment[], char thirdSpaceSegment[], char forthSpaceSegment[], char firstCSVSegment[], char secondCSVSegment[], char thirdCSVSegment[], char forthCSVSegment[], int powerOfTwo[], codeLine data[], codeLine code[])
{
*filesNum = argc - 1;
initiating_input_array(input, CSVinput, spaceInput, firstSpaceSegment, secondSpaceSegment, thirdSpaceSegment, forthSpaceSegment, firstCSVSegment, secondCSVSegment, thirdCSVSegment, forthCSVSegment);
initiating_reserved_fixed_words_list(headFixed);
initiating_reserved_non_fixed_words_list(headNonFixed);
powerOfTwoArray(powerOfTwo);
initiatingCodeLineArrays(data, code);
return;
}


static void initiating_reserved_fixed_words_list(reserved *headFixed)	 /* temp comment 1: list is not orgenized. in leftover.txt there is a failed attempt to sort it alphabetically 
temp comment 2: it is not very efficient function. attempts to use a smaller function, each time to build one more object came at expense of being unable to keep a tail. instead, every time the smaller function in called, it need to iterate through all the list
*/
{
char *reservedWords[] = {"add","cmp","lea","mov","sub","bne","clr","dec","inc","jmp","jsr","not","prn","red","rts","stop",".data",".string",".entry",".extern","r0","r1","r2","r3","r4","r5","r6","r7"};
int i = 0;
/* populating headFixed with content: */
headFixed->next = NULL;
headFixed->previous = NULL;
headFixed->name = reservedWords[i];
headFixed->operands = 2;
headFixed-> type = COMMAND;
i++;
/* go over commands with two operands */
for (; i<TWO_OPERANDS_COMMANDS_NUM; i++)	 
	addingReservedObjectToList(headFixed, COMMAND, reservedWords[i], 2);
/* go over commands with one operand */
for (; i<TWO_OPERANDS_COMMANDS_NUM + ONE_OPERAND_COMMANDS_NUM; i++)	
	addingReservedObjectToList(headFixed, COMMAND, reservedWords[i], 1);
/* go over commands with zero operands */
for (; i<COMMANDS_NUM; i++)	
	addingReservedObjectToList(headFixed, COMMAND, reservedWords[i], 0);
/* go over guidances */
for(;i<COMMANDS_NUM + GUIDANCES_NUM; i++)	
	addingReservedObjectToList(headFixed, GUIDANCE, reservedWords[i], -1);
/* go over registers */
for(;i<COMMANDS_NUM + GUIDANCES_NUM + REGISTERS_NUM; i++)	  
	addingReservedObjectToList(headFixed, REGISTER, reservedWords[i], -1);
}


static void initiating_reserved_non_fixed_words_list(reserved *headNonFixed)	 /* temp comment same comments as for initiating_reserved_fixed_words_list */
{
/* populating dummy headNonFixed with content: */
headNonFixed->next = NULL;
headNonFixed->previous = NULL;
headNonFixed->name = "__dummy";
headNonFixed->operands = -1;
headNonFixed-> type = DUMMY;
}


static void initiating_input_array(char **input[], char *CSVinput[], char *spaceInput[], char firstSpaceSegment[], char secondSpaceSegment[], char thirdSpaceSegment[], char forthSpaceSegment[], char firstCSVSegment[], char secondCSVSegment[], char thirdCSVSegment[], char forthCSVSegment[])
{
input[0] = spaceInput;
input[1] = CSVinput;
input_arrays_initializing(firstSpaceSegment,SEGMENT_LEN);
input_arrays_initializing(secondSpaceSegment,SEGMENT_LEN);
input_arrays_initializing(thirdSpaceSegment,SEGMENT_LEN);
input_arrays_initializing(forthSpaceSegment,SEGMENT_LEN);		
input_arrays_initializing(firstCSVSegment,SEGMENT_LEN);
input_arrays_initializing(secondCSVSegment,SEGMENT_LEN);
input_arrays_initializing(thirdCSVSegment,SEGMENT_LEN);
input_arrays_initializing(forthCSVSegment,SEGMENT_LEN);
spaceInput[0] = firstSpaceSegment;
spaceInput[1] = secondSpaceSegment;
spaceInput[2] = thirdSpaceSegment;
spaceInput[3] = forthSpaceSegment;
CSVinput[0] = firstCSVSegment;
CSVinput[1] = secondCSVSegment;
CSVinput[2] = thirdCSVSegment;
CSVinput[3] = forthCSVSegment;
}

/* populating the array powerOfTwo with powerOfTwo from 0-23. This will later be used in another function, translatingNumToBinary, to transform an integer to a printed binary representation of it */
static void powerOfTwoArray(int *powerOfTwo)
{
int i = WORD_LEN - 1;
powerOfTwo[i] = 1;
i--;
for (;i >= 0; i--)
	{
	powerOfTwo[i] = 2 * powerOfTwo[i + 1];
	}
}


static void initiatingCodeLineArrays(codeLine data[], codeLine code[])
{
int i;
for(i = 0; i < CODLINE_SIZE_JUMPS; i++)
	{
	data[i].intToBeTranslatedToBinary = 0;
	code[i].intToBeTranslatedToBinary = 0;
	data[i].isCompletedOnFirstPass = FALSE;
	code[i].isCompletedOnFirstPass = FALSE;
	data[i].line = (char *) malloc(MAXLINE * sizeof(char));
	code[i].line = (char *) malloc(MAXLINE * sizeof(char));
	}
}


extern void input_arrays_initializing(char array[], int len);
extern int lineParsing(char **input[],char line[], int lineCount, int *numSpaceSegments, int *numCSVsegments);
extern reserved* addingReservedObjectToList(reserved *head, short type, char *name, short operands);

static int isFirstSpaceDeliminatedSegmentALabel(char **input[]);
static int isRelevantSegmentMcroOperand(char relevantSegment[]);
static reserved * isRelevantSpaceSegmentReserved(char relevantSegment[], reserved *head);
static int isEndOfMcro(char segment[]);

#define MACRO "mcro"
#define MCRO_END "mcroend"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct reserevedList
{
struct reserevedList *next;
struct reserevedList *previous;
short type;
char *name;
short operands;
char *replacement;
};

typedef struct reserevedList reserved;

/* *** ERRORS LIST *** */
#define ERROR_1 "No command line argument was passed\n"
#define ERROR_2 "An error occourd with the specified file: %s. It either not a file name, or the file doesn't exist\n"
#define ERROR_3 "An error occourd: two consecutive commas in line %d\n"
#define ERROR_4 "An error occourd: junk chars alongwith mcro command in line %d\n"
#define ERROR_5 "An error occourd: mcro being recorded has a name already in use in line %d\n"
#define ERROR_6 "An unexpected error occourd while processing mcros in line %d\n"
/*#define ERROR_7 "An error occourd: unrecognized command passed in line %d\n"*/

/* *** FILES SUFFIXES LIST *** */
#define DOT_AS ".as"
#define DOT_AM ".am"
#define DOT_OB ".ob"
#define DOT_ENT ".ent"
#define DOT_EXT ".ext"

/* *** FILES' ACCESS MODES LIST *** */
#define READ_MODE "r"
#define WRITE_MODE "w" /*temp does it really needed? */
#define APPEND_MODE "a"

/* *** ASCII VALUES LIST  *** */
#define ASCII_VALUE_OF_COLON 58
#define ASCII_VALUE_OF_SPACE 32
#define ASCII_VALUE_OF_COMMA 44
#define ASCII_VALUE_OF_POINT 46 /* temp does it really needed?  */
#define ASCII_VALUE_OF_MINUS 45 /* temp does it really needed?  */
#define ASCII_VALUE_OF_NEW_LINE 10
#define ASCII_VALUE_OF_NULL_CHAR 0

/* *** INPUT LINE SEGMENTS HOLDERS  *** */
#define NUM_SEGMENTS_TYPES 2 /* space spereted segments, and comma sepereted segments*/
#define SEGMENT_LEN 20
#define SPACE_SEPERETED_SEGMENTS_NUM 4
#define CSV_SEGMENTS_NUM 4
#define FIRST_SEGMENT 0
#define SECOND_SEGMENT 1

/* *** POWER OF TWO *** */
#define POWER_OF_TWO_0 1
#define POWER_OF_TWO_1 2
#define POWER_OF_TWO_2 4
#define POWER_OF_TWO_3 8
#define POWER_OF_TWO_4 16
#define POWER_OF_TWO_5 32
#define POWER_OF_TWO_6 64
#define POWER_OF_TWO_7 128
#define POWER_OF_TWO_8 256
#define POWER_OF_TWO_9 512
#define POWER_OF_TWO_10 1024
#define POWER_OF_TWO_11 2048
#define POWER_OF_TWO_12 4096
#define POWER_OF_TWO_13 8192
#define POWER_OF_TWO_14 1
#define POWER_OF_TWO_15 1
#define POWER_OF_TWO_16 1
#define POWER_OF_TWO_17 1
#define POWER_OF_TWO_18 1
#define POWER_OF_TWO_19 1
#define POWER_OF_TWO_20 1
#define POWER_OF_TWO_21 1
#define POWER_OF_TWO_22 1
#define POWER_OF_TWO_23 1

/* *** GENERAL *** */

enum {FALSE,TRUE};
enum {COMMAND,LABEL,MCRO,REGISTER,GUIDANCE,DUMMY};
#define FILE_NAME_LEN 30
#define COMMANDS_NUM 16
#define TWO_OPERANDS_COMMANDS_NUM 5
#define ONE_OPERAND_COMMANDS_NUM 9
#define ZERO_OPERANDS_COMMANDS_NUM 2
#define REGISTERS_NUM 8
#define GUIDANCES_NUM 4
#define MAXLINE 81
#define DELIMINATOR_SPACE " "
#define DELIMINATOR_COMMA ","
#define WORD_LEN 24


/*#define Multiplicative_inverse -1	temp does it really needed?*/




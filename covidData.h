
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>


#ifndef GENERAL
#define GENERAL

//VARIABLE DATA STRUCT
typedef struct new_var{
    char *indicator, *year_week;
    int weekly_count, cumulative_count;
    float rate_14_days;
    struct new_var *next;
}VAR;


//MAIN LIST STRUCT
typedef struct new_fix{
    //FIX DATA
    char *name,*code, *continent;
    int population;
    //VAR DATA
    struct new_var *var;
    struct new_fix *next;
}FIX;

/* Description: Goes throught the whole list of lists, printing out all nodes to the console.*/
void printList(FIX *);

/* Description: Prints out an help message to explain how the inputs work.It exits the program and
its used whenever the program goes through an error.*/
void help();

/*This function belongs to the GNU library and was implemented in this code due to errors when
compiling the program*/
char *strseparate (char **, const char *);

/*This function belongs to the GNU library and was implemented in this code due to errors when
compiling the program and not being able to use the one on the library.*/
char *strdup (const char*);

#endif // GENERAL

#ifndef CHECK_INPUT
#define CHECK_INPUT

/*Description: Checks all the possible continents the user can choose, if the input doesnt
match with the continent list, it will return an error.*/
void check_input_L(char* );


/*Description: Checks all the possible sorts modes the user can choose,if the input doesnt
match with the sorting list, it will return an error.*/
void check_input_S(char*);


/* Description: Checks all the possible selection modes the user can choose,if the input doesnt
match with the selection list, it will return an error.*/
void check_input_D(char*);


/* Description: Checks all the possible restriction modes the user can choose,if the input doesnt
match with the restriction list, it will return an error.*/
void check_input_P(char*);


/* Description: Checks if the user wants to read/write a Binary file or a CSV file,if the input doesnt
match with the extensions list, it will return an error.*/
int check_RorW_type(char*);


/* Description: Checks if "data" string is correspondent to the format "yyyy-ww"
and if it is a possible date aswell.*/
void checkDate(char*);


/* Description: The function goes through the principal list to check if there is a node with the same
name as the argument.*/
int check_name(FIX *, char*);


/* Description: This function checks if "token" is 3 characters long.If not, exits the program.*/
void check_code_len(char*);


/* Description: This function checks if "token" corresponds to "cases" or "deaths". If not, exit the program.*/
void check_indicator(char*);


/* Description: This function checks if a string is empty, if so exits with help function.
Its used to check if rows from csv file are empty while reading it.*/
void check_emptyrows(char*);


#endif

#ifndef READ_WRITE
#define READ_WRITE

/* Description: Allocates and saves the information of the arguments onto nodes of the secondary list.*/
VAR *create_var(struct new_var*,char*,int, char*, double, int);


/* Description: Allocates and saves the information of the arguments onto nodes of the main list.*/
FIX *create_fix(FIX *, char*, char*, char*,int, char*,int, char*, double, int);


/* Description: This function creates principal list nodes and secondary list nodes, given certain situations.*/
FIX* createNodes(FIX*,char*, char*, char*,int,char*,int, char*, double, int);


/* Description: Goes through the principal list incrementing for each cycle.*/
int numCountries(FIX *);


/* Description: The function goes through the secondary list, printing out to a binary file (.dat) all the nodes on the list.*/
int numVar(VAR*);


/* Description: Given a text file, this function will read it, line by line, while creating nodes for each country (in the main list) and each variable information
of that country (secondary list).*/
FIX *read(char*, char*);


/* Description: The function goes through the whole list, printing out to a text file (.csv) all the nodes on the list.*/
void write(FIX*, char*);


/* Description: Given a binary file, this function will read it, while saving the info into variables and then, creating nodes for each
 country (in the main list) and each variable information.
of that country (secondary list).*/
FIX* readBinary(char*);


/* Description: The function goes through the whole list, printing out to a binary file (.dat) all the nodes on the list.*/
void writeBinary(FIX*, char*);


#endif // READ_WRITE

#ifndef FREE
#define FREE

/* Description: Frees all the information inside a principal list node and itself.*/
void free_fix(FIX*);


/* Description: Frees all the information inside a secondary list node and itself.*/
void free_var(VAR*);


/* Description: Goes through the whole list of lists, freeing everything there is inside the nodes and the nodes themselves, ending up freeing all the nodes.*/
void free_list(FIX*);


#endif // FREE

#ifndef SORT
#define SORT

/* Description: Swaps the position of 2 nodes of the principal list.*/
FIX *swapF(FIX *, FIX *);


/* Description: Bubble sort algorithm to organize all the list by alphabetical order (A-Z).*/
FIX *alfa(FIX *);


/* Description: Bubble sort algorithm to organize all the list by population. (Highest to lowest)*/
FIX *pop(FIX *);


/* Description: Bubble sort algorithm to organize all the list by weekly_count of infected cases for the specified
date ("data").*/
FIX* inf_yyyy_ww(FIX*,char*);


/*Description: Bubble sort algorithm to organize all the list by weekly_count of death cases for the specified
date ("data").*/
FIX *dea_yyyy_ww(FIX *, char*);


#endif // SORT

#ifndef SELECTION
#define SELECTION

/* Description: This function goes through the whole secondary list, saving on x the highest weekly count
for infected cases for a country. If there are 2 weeks with the same value o x, it chooses the earliest week.*/
char* inf_aux(VAR**, int*, char*);


/* Description: This function goes through the whole secondary list, freeing all the nodes except the one with highest weekly count
for infected cases and the earliest week.*/
VAR* inf_del(VAR*, int, char*);


/* Description: This function goes through the whole primary list,assigning data the function(inf_aux) and the variable
list head, the function "inf_del".*/
FIX* inf(FIX*);


/* Description: This function goes through the whole secondary list, saving on x the highest weekly count
for death cases for a country. If there are 2 weeks with the same value o x, it chooses the earliest week.*/
char* dea_aux(VAR**, int*,char*);


/* Description: This function goes through the whole secondary list, freeing all the nodes except the one with highest weekly count
for death cases and the earliest week.*/
VAR* dea_del(VAR*, int, char*);


/* Description: This function goes through the whole primary list,assigning data the function(dea_aux) and the variable
list head, the function "dea_del".*/
FIX* dea(FIX*);


/* Description: This function goes through the whole secondary list, saving on x the highest rate_14_days
for infected case for a country. If there are 2 weeks with the same value o x, it chooses the earliest week.*/
char* racinf_aux(VAR**, double*, char*);


/* Description: This function goes through the whole secondary list, freeing all the nodes except the one with rate_14_days
for infected cases and the earliest week.*/
VAR* racinf_del(VAR*, double, char*);


/* Description: This function goes through the whole primary list,assigning data the function(racinf_aux) and the variable
list head, the function "racinf_del".*/
FIX* racinf(FIX*);


/* Description: This function goes through the whole secondary list, saving on x the highest rate_14_days
for death case for a country. If there are 2 weeks with the same value o x, it chooses the earliest week.*/
char* racdea_aux(VAR**, double*, char*);


/* Description: This function goes through the whole secondary list, freeing all the nodes except the one with rate_14_days
for death cases and the earliest week.*/
VAR* racdea_del(VAR*, double, char*);


/* Description: This function goes through the whole primary list,assigning data the function(racdea_aux) and the variable
list head, the function "racdea_del".*/
FIX* racdea(FIX*);


#endif // SELECTION

#ifndef RESTRICTION
#define RESTRICTION

/* Description: This function goes through the whole list, freeing all the principal list nodes with
a lower number of population than x.*/
FIX* min(FIX*, int);


/* Description: This function goes through the whole list, freeing all the principal list nodes with
a higher number of population than x.*/
FIX* max(FIX*, int);


/* Description: This function goes through the whole secondary list, freeing all the secondary list nodes with
a "year_week" different of the argument "data".*/
VAR* date_aux(VAR *, char*);


/* Description: Function relative to the restriction mode "date yyyy-ww". Goes through the principal list assigning all the secondary lists head's,
the function "date_aux".*/
FIX* date_only(FIX*, char*);


/* Description: This function goes through the whole secondary list, freeing all the secondary list nodes that dont
belong to the interval set beetween "date1" and "date2"*/
VAR* date_interval_aux(VAR *, char*, char*);


/* Description: Function relative to the restriction mode "dates yyyy-ww yyyy-ww".Initially checks which date is smaller, and assign it to "date 1".
After that, goes through the principal list, assigning every secondary list head the function "date_interval_aux".*/
FIX* date_interval(FIX*, char* , char*);


#endif //RESTRICTIONS

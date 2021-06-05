
#include "covidData.h"

/*******************************************************************************
* Function name: help
*
* Arguments:
    None.
*
* Return: Nothing.
*
*
* Description: Prints out an help message to explain how the inputs work.It exits the program and
its used whenever the program goes through an error.
*
*******************************************************************************/
void help(){

    printf(
"\n=================================================================================================================================================\n\
       Help Menu:\n\
    Read File Instructions (-i argument) \n\
-> filename.csv - Reads the selected name csv file\n\
-> filename.dat - Reads the selected name binary file\n\n\
    Read Data Instructions (-L argument)\n\
-> all - Reads all the data on the selected file\n\
-> continent name (Africa,Asia,Europe,America,Oceania) - Reads the data related to the chosen country\n\n\
    Sort Instructions (-S argument)\n\
-> alfa - The data list will be sorted by alphabetical order (A-Z)\n\
-> pop - The data list will be sorted by population number (Highest-Lowest\n\
-> inf year-week - The data list will be sorted by the cumulative count of infected cases related to the chosen date\n\
-> inf year-week - The data list will be sorted by the cumulative count of death cases related to the chosen date\n\n\
    Selection Instructions (-D argument)\n\
-> inf - Selects for each country the week with the most infected cases\n\
-> dea - Selects for each country the week with the most death cases\n\
-> racioinf - Selects for each country the week with the highest rate of infected cases per 100k population, last 14 days.\n\
-> raciodea - Selects for each country the week with the highest rate of death cases per 1M population, last 14 days.\n\n\
    Restriction Instructions (-P argument)\n\
-> min n - Restrains the data to show only countrys with a population above n*1000\n\
-> max n - Restrains the data to show only countrys with a population under n*1000\n\
-> date year-week - Restrains the data to show only the selected week\n\
-> dates year-week year-week - Restrains the data to show only the weeks between the interval of the selected ones.(Including themselves)\n\n\
    Write File Instruction (-o argument)\n\
-> filename.csv - Writes the list into a csv file with the selected name\n\
-> filename.dat - Writes the list into a binary file with the selected name\n\
\n\
\n\
    Reading csv file\n\
-> All columns except the eighth one, should have data in it otherwise the program will close.\n\
-> In the eighth one, only the earliest date of a country should be empty.\n\
-> Antartida is not an available continent for analysis.\n\
\n\
    Reading dat file\n\
-> If you are reading a binary file, you cant use -L;-S;-D;-P as options.\n\
=================================================================================================================================================\n");

exit(EXIT_FAILURE);
}

/*******************************************************************************
* Function name: printList
*
* Arguments:
    Listhead -> Initial node of the secondary list.
*
* Return:
    Nothing.
*
*
* Description: Goes throught the whole list of lists, printing out all nodes to the console.
*
*******************************************************************************/
void printList(FIX *head){

    FIX *aux = head;
    VAR* ax = head -> var;

    if(aux==NULL){
        printf("There is no data for that specification.\n");
    }

    while(aux != NULL){
        ax = aux-> var;
        while(aux->var != NULL){
            printf("%s - ", aux -> name);
            printf("%s - ", aux -> code);
            printf("%s - ", aux -> continent);
            printf("%d - ", aux -> population);
            printf("%s - ", ax ->indicator);
            printf("%d - ", ax -> weekly_count);
            printf("%s - ", ax ->year_week);
            printf("%lf - ", ax ->rate_14_days);
            printf("%d \n", ax -> cumulative_count);
            ax = ax -> next;
        }
        aux = aux -> next;
    }

    free_list(head);

}

/*******************************************************************************
* Function name: strseparate
*
* This function belongs to the GNU library and was implemented in this code due to errors when
compiling the program and not being able to use the one on the library.
*******************************************************************************/
char *strseparate (char **stringp, const char *delim){
  char *begin, *end;
  begin = *stringp;
  if (begin == NULL)
    return NULL;
  /* Find the end of the token.  */
  end = begin + strcspn (begin, delim);
  if (*end)
    {
      /* Terminate the token and set *STRINGP past NUL character.  */
      *end++ = '\0';
      *stringp = end;
    }
  else
    /* No more delimiters; this is the last token.  */
    *stringp = NULL;
  return begin;
}

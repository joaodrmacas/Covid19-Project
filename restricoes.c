
#include "covidData.h"

/*******************************************************************************
* Function name: min
*
* Arguments:
    FIX* Listhead -> Initial node of the principal list.
    int x -> Number in thousands relative to the minimum population of a country.
*
* Return:
    Listhead -> Initial node of the principal list.
*
*
* Description: This function goes through the whole list, freeing all the principal list nodes with
a lower number of population than x.
*
*******************************************************************************/
FIX* min(FIX *Listhead, int x){
    x = x*1000;
    FIX *head = Listhead,*before = NULL;
    while (head){
        FIX *next = head->next;
        if (head->population < x){
            free_fix(head);
            if (before){
                before->next = next;
            }
            else{
                Listhead = next;
            }
        }
        else{
         before = head;
        }
      head = next;
   }
   return Listhead;
}

/*******************************************************************************
* Function name: max
*
* Arguments:
    FIX* Listhead -> Initial node of the principal list.
    int x -> Number in thousands relative to the maximum population of a country.
*
* Return:
    Listhead -> Initial node of the principal list.
*
*
* Description: This function goes through the whole list, freeing all the principal list nodes with
a higher number of population than x.
*
*******************************************************************************/
FIX* max(FIX *Listhead, int x){
    x = x*1000;
    FIX *head = Listhead,
    *before = NULL;
    while (head){
        FIX *next = head->next;
        if (head->population > x){
            free_fix(head);
            if (before){
                before->next = next;
            }
            else{
                Listhead = next;
            }
        }
        else{
         before = head;
        }
      head = next;
   }

   return Listhead;
}

/*******************************************************************************
* Function name: date_aux
*
* Arguments:
    VAR* Listhead -> Initial node of the secondary list.
    char* data -> String relative to a certain date.
*
* Return:
    Listhead -> Initial node of the secondary list.
*
*
* Description: This function goes through the whole secondary list, freeing all the secondary list nodes with
a "year_week" different of the argument "data".
*
*******************************************************************************/
VAR* date_aux(VAR *Listhead, char* date){

    VAR* head = Listhead, *before = NULL;

    while(head){
        VAR *next = head -> next;
        if((strcmp(head -> year_week, date) != 0)){
            free_var(head);
            if(before){
                before -> next = next;
            }
            else{
                Listhead = next;
            }
        }
        else{
            before = head;
        }
        head = next;
    }

    return Listhead;
}

/*******************************************************************************
* Function name: date_only
*
* Arguments:
    VAR* Listhead -> Initial node of the principal list.
    char* data -> String relative to a certain date.
*
* Return:
    Listhead -> Initial node of the principal list.
*
*
* Description: Function relative to the restriction mode "date yyyy-ww". Goes through the principal list assigning all the secondary lists head's,
the function "date_aux".
*
*******************************************************************************/
FIX* date_only(FIX*Listhead, char* date){
    FIX* aux = Listhead;

    while(aux != NULL){

        aux->var = date_aux(aux->var, date);

        aux = aux -> next;
    }

    return Listhead;
}

/*******************************************************************************
* Function name: date_interval_aux
*
* Arguments:
    VAR* Listhead -> Initial node of the secondary list.
    char* data1 -> String relative to the first input date
    char* date2 -> String relative to the second input date
*
* Return:
    VAR* Listhead -> Initial node of the secondary list.
*
*
* Description: This function goes through the whole secondary list, freeing all the secondary list nodes that dont
belong to the interval set beetween "date1" and "date2"
*
*******************************************************************************/
VAR* date_interval_aux(VAR *Listhead, char* date1, char* date2){

    VAR* head = Listhead, *before = NULL;

    while(head){
        VAR *next = head -> next;
        if( ((strcmp(head->year_week,date1)) < 0) || ((strcmp(head->year_week, date2)) > 0 ) ){ //Condition
            free_var(head);
            if(before){
                before -> next = next;
            }
            else{
                Listhead = next;
            }
        }
        else{
            before = head;
        }
        head = next;
    }

    return Listhead;
}

/*******************************************************************************
* Function name: date_interval
*
* Arguments:
    FIX* Listhead -> Initial node of the principal list.
    char* data1 -> String relative to the first input date
    char* date2 -> String relative to the second input date
*
* Return:
    Listhead -> Initial node of the principal list.
*
*
* Description: Function relative to the restriction mode "dates yyyy-ww yyyy-ww".Initially checks which date is smaller, and assign it to "date 1".
After that, goes through the principal list, assigning every secondary list head the function "date_interval_aux".
*
*******************************************************************************/
FIX* date_interval(FIX*Listhead, char* date1 , char* date2){
    FIX* aux = Listhead;
    char* date_copy;
    int flag=0;

    if( (strcmp(date1,date2)) > 0 ){
        date_copy = strdup(date1);
        date1 = strdup(date2);
        date2 = strdup(date_copy);
        flag =1;
    }

    while(aux != NULL){

        aux->var = date_interval_aux(aux->var,date1,date2);

        aux = aux -> next;
    }

    if(flag==1){
        free(date_copy);
        free(date1);
        free(date2);
    }

    return Listhead;
}

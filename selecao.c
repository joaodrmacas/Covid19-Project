#include "covidData.h"

/** The next 3 functions are used for selection mode "inf"*/

/*******************************************************************************
* Function name: inf_aux
*
* Arguments:
    VAR **Listhead -> Initial node of the secondary list, passed by reference.
    int *x -> Number of infected people, passed by reference.
    char* data -> String relative to a certain date (yyyy-ww)
*
* Return:
    data -> String relative to the most recent date with the highest weekly_count for infected cases.
*
*
* Description: This function goes through the whole secondary list, saving on x the highest weekly count
for infected cases for a country. If there are 2 weeks with the same value o x, it chooses the earliest week.
*
*******************************************************************************/
char* inf_aux(VAR** Listhead, int *x,char* data){
    VAR* aux = *Listhead;

    while(aux != NULL){

        if( ( aux -> weekly_count >= *x ) && (strcmp(aux->indicator, "cases")==0) ){//Search for infected cases, and if they are higher than the current x, it will be the new value of x.
            *x = aux -> weekly_count;
            if ( (strcmp(aux -> year_week,data)) > 0){//Compares the date if 2 weeks have the highest weekly count for cases.Saves the earliest week
                free(data);
                data = strdup(aux->year_week);
            }
        }
        aux = aux -> next;
    }

    return data;
}

/*******************************************************************************
* Function name: inf_del
*
* Arguments:
    VAR *Listhead -> Initial node of the secondary list.
    int x -> Number of infected people.
    char* data -> String relative to a certain date (yyyy-ww)
*
* Return:
    Listhead -> Initial node of the secondary list.
*
*
* Description: This function goes through the whole secondary list, freeing all the nodes except the one with highest weekly count
for infected cases and the earliest week.
*
*******************************************************************************/
VAR* inf_del(VAR* Listhead, int x,char* data){
    VAR* head = Listhead, *before = NULL;
    while(head){
        VAR* next = head -> next;
        if( ( (head -> weekly_count < x) && (strcmp(head->indicator,"cases")==0) ) || ((strcmp(head->indicator, "deaths")) == 0) || ( (head -> weekly_count>=x) && ((strcmp(head->indicator,"cases")) ==0 ) && ((strcmp(data,head->year_week)) > 0) ) ){
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
* Function name: inf
*
* Arguments:
    FIX* Listhead -> Initial node of the primary list.
*
* Return:
    Listhead -> Initial node of the primary list.
*
*
* Description: This function goes through the whole primary list,assigning data the function(inf_aux) and the variable
list head, the function "inf_del".
*
*******************************************************************************/
FIX* inf(FIX* Listhead){
    int x= 0;
    char* data = strdup("0-0");
    FIX* aux = Listhead;

    while(aux != NULL){
        data = inf_aux(&aux->var, &x, data);
        aux -> var = inf_del(aux -> var, x, data);
        aux = aux -> next;
        x = 0;//Resets the value of weekly count for the next primary list node.
        free(data);
        data = strdup("0-0");//Resets the date for the next primary list node.
    }

    free(data);
    return Listhead;
}



/** The next 3 functions are used for selection mode "dea"*/


/*******************************************************************************
* Function name: dea_aux
*
* Arguments:
    VAR **Listhead -> Initial node of the secondary list, passed by reference.
    int *x -> Number of deaths of that week, passed by reference.
    char* data -> String relative to a certain date (yyyy-ww)
*
* Return:
    data -> String relative to the most recent date with the highest weekly_count for death cases.
*
*
* Description: This function goes through the whole secondary list, saving on x the highest weekly count
for death cases for a country. If there are 2 weeks with the same value o x, it chooses the earliest week.
*
*******************************************************************************/
char* dea_aux(VAR** Listhead, int *x, char* data){
    VAR* aux = *Listhead;

    while(aux != NULL){

        if( ( ( aux -> weekly_count >= *x ) && (strcmp(aux->indicator, "deaths")==0) ) ){//Search for death cases, and if they are higher than the current x, it will be the new value of x.
            *x = aux -> weekly_count;
            if ( (strcmp(aux -> year_week,data)) > 0){//Compares the date if 2 weeks have the highest weekly count for deaths.Saves the earliest week
                free(data);
                data = strdup(aux->year_week);
            }
        }
        aux = aux -> next;
    }

    return data;
}

/*******************************************************************************
* Function name: dea_del
*
* Arguments:
    VAR *Listhead -> Initial node of the secondary list.
    int x -> Number of deaths of that week.
    char* data -> String relative to a certain date (yyyy-ww)
*
* Return:
    Listhead -> Initial node of the secondary list.
*
*
* Description: This function goes through the whole secondary list, freeing all the nodes except the one with highest weekly count
for death cases and the earliest week.
*
*******************************************************************************/
VAR* dea_del(VAR* Listhead, int x, char* data){
    VAR* head = Listhead, *before = NULL;
    while(head){
        VAR* next = head -> next;
        if( ( (head -> weekly_count < x) && (strcmp(head->indicator,"deaths")==0) ) || ((strcmp(head->indicator, "cases")) == 0) || /* meter a semana mais recente */ ( (head -> weekly_count>=x) && ((strcmp(head->indicator,"deaths")) ==0 ) && ((strcmp(data,head->year_week)) > 0) ) ){
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
* Function name: dea
*
* Arguments:
    FIX* Listhead -> Initial node of the primary list.
*
* Return:
    Listhead -> Initial node of the primary list.
*
*
* Description: This function goes through the whole primary list,assigning data the function(dea_aux) and the variable
list head, the function "dea_del".
*
*******************************************************************************/
FIX* dea(FIX* Listhead){
    int x= 0;
    char* data = strdup("0-0");
    FIX* aux = Listhead;

    while(aux != NULL){

        data = dea_aux(&aux->var, &x, data);
        aux -> var = dea_del(aux -> var, x, data);
        aux = aux -> next;
        x = 0;//Resets the value of weekly count for the next primary list node.
        free(data);
        data = strdup("0-0");//Resets the date for the next primary list node.
    }

    free(data);
    return Listhead;
}



/** The next 3 functions are used for selection mode "racioinf"*/



/*******************************************************************************
* Function name: racinf_aux
*
* Arguments:
    VAR **Listhead -> Initial node of the secondary list, passed by reference.
    int *x -> Rate of the last 14 days for infected cases, passed by reference.
    char* data -> String relative to a certain date (yyyy-ww)
*
* Return:
    data -> String relative to the most recent date with the highest rate in the last 14 days for infected cases.
*
*
* Description: This function goes through the whole secondary list, saving on x the highest rate_14_days
for infected case for a country. If there are 2 weeks with the same value o x, it chooses the earliest week.
*
*******************************************************************************/
char* racinf_aux(VAR** Listhead, double *x, char* data){
    VAR* aux = *Listhead;


    while(aux != NULL){

        if( ( aux -> rate_14_days >= *x ) && (strcmp(aux->indicator, "cases")==0) ){//Search for rate in the last 14 days for infected cases, and if they are higher than the current x, it will be the new value of x.
            *x = aux -> rate_14_days;
            if ( (strcmp(aux -> year_week,data)) > 0){//Compares the date if 2 weeks have the highest rate for infected cases. Saves the earliest week
                free(data);
                data = strdup(aux->year_week);
            }
        }
        aux = aux -> next;
    }

    return data;
}

/*******************************************************************************
* Function name: racinf_del
*
* Arguments:
    VAR *Listhead -> Initial node of the secondary list.
    int x -> Rate of the last 14 days for infected cases
    char* data -> String relative to a certain date (yyyy-ww)
*
* Return:
    Listhead -> Initial node of the secondary list.
*
*
* Description: This function goes through the whole secondary list, freeing all the nodes except the one with rate_14_days
for infected cases and the earliest week.
*
*******************************************************************************/
VAR* racinf_del(VAR* Listhead, double x, char* data){
    VAR* head = Listhead, *before = NULL;
    while(head){
        VAR* next = head -> next;
        if( ( (head -> rate_14_days < x) && (strcmp(head->indicator,"cases")==0) ) || ((strcmp(head->indicator, "deaths")) == 0) || ( (head -> rate_14_days>=x) && ((strcmp(head->indicator,"cases")) ==0 ) && ((strcmp(data,head->year_week)) > 0) ) ){
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
* Function name: racinf
*
* Arguments:
    FIX* Listhead -> Initial node of the primary list.
*
* Return:
    Listhead -> Initial node of the primary list.
*
*
* Description: This function goes through the whole primary list,assigning data the function(racinf_aux) and the variable
list head, the function "racinf_del".
*
*******************************************************************************/
FIX* racinf(FIX* Listhead){
    double x= 0.0;
    char* data = strdup("0-0");
    FIX* aux = Listhead;

    while(aux != NULL){

        data =racinf_aux(&aux->var, &x, data);
        aux -> var = racinf_del(aux -> var, x, data);
        aux = aux -> next;
        x = 0.0;//Resets the value of rate_14_days for the next primary list node.
        free(data);
        data = strdup("0-0");//Resets the date for the next primary list node.
    }
    free(data);
    return Listhead;
}


/** The next 3 functions are used for selection mode "raciodea"*/

/*******************************************************************************
* Function name: racdea_aux
*
* Arguments:
    VAR **Listhead -> Initial node of the secondary list, passed by reference.
    int *x -> Rate of the last 14 days for death cases, passed by reference.
    char* data -> String relative to a certain date (yyyy-ww)
*
* Return:
    data -> String relative to the most recent date with the highest rate in the last 14 days for death cases.
*
*
* Description: This function goes through the whole secondary list, saving on x the highest rate_14_days
for death case for a country. If there are 2 weeks with the same value o x, it chooses the earliest week.
*
*******************************************************************************/
char* racdea_aux(VAR** Listhead, double *x, char* data){
    VAR* aux = *Listhead;

    while(aux != NULL){

        if( ( aux -> rate_14_days >= *x ) && (strcmp(aux->indicator, "deaths")==0) ){//Search for rate in the last 14 days for death cases, and if they are higher than the current x, it will be the new value of x.
            *x = aux -> rate_14_days;
            if ( (strcmp(aux -> year_week,data)) > 0){//Compares the date if 2 weeks have the highest rate for death cases. Saves the earliest week
                free(data);
                data = strdup(aux->year_week);
            }
        }
        aux = aux -> next;
    }

    return data;
}


/*******************************************************************************
* Function name: racdea_del
*
* Arguments:
    VAR *Listhead -> Initial node of the secondary list.
    int x -> Rate of the last 14 days for death cases
    char* data -> String relative to a certain date (yyyy-ww)
*
* Return:
    Listhead -> Initial node of the secondary list.
*
*
* Description: This function goes through the whole secondary list, freeing all the nodes except the one with rate_14_days
for death cases and the earliest week.
*
*******************************************************************************/
VAR* racdea_del(VAR* Listhead, double x, char* data){
    VAR* head = Listhead, *before = NULL;
    while(head){
        VAR* next = head -> next;
        if( ( (head -> rate_14_days < x) && (strcmp(head->indicator,"deaths")==0) ) || ((strcmp(head->indicator, "cases")) == 0) ||( (head -> rate_14_days>=x) && ((strcmp(head->indicator,"deaths")) ==0 ) && ((strcmp(data,head->year_week)) > 0) ) ){
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
* Function name: racdea
*
* Arguments:
    FIX* Listhead -> Initial node of the primary list.
*
* Return:
    Listhead -> Initial node of the primary list.
*
*
* Description: This function goes through the whole primary list,assigning data the function(racdea_aux) and the variable
list head, the function "racdea_del".
*
*******************************************************************************/
FIX* racdea(FIX* Listhead){
    double x= 0.0;
    char* data = strdup("0-0");
    FIX* aux = Listhead;

    while(aux != NULL){

        data = racdea_aux(&aux->var, &x, data);
        aux -> var = racdea_del(aux -> var, x, data);
        aux = aux -> next;
        x = 0.0;//Resets the value of rate_14_days for the next primary list node.
        free(data);
        data = strdup("0-0");//Resets the date for the next primary list node.
    }
    free(data);
    return Listhead;
}


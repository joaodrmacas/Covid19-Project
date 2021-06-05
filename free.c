#include "covidData.h"

/*******************************************************************************
* Function name: free_fix
*
* Arguments:
    head -> Initial node of the secondary list.
*
* Return:
    Nothing.
*
*
* Description: Frees all the information inside a principal list node and itself.
*
*******************************************************************************/
void free_fix(FIX* head){
    FIX *aux_fix = head;
    VAR *aux_var = head->var, *aux_var2;

    while(aux_var!=NULL){
        free(aux_var->indicator);
        free(aux_var->year_week);
        aux_var2 = aux_var->next;
        free(aux_var);
        aux_var = aux_var2;
    }
    free(aux_fix->name);
    free(aux_fix->code);
    free(aux_fix->continent);
    free(aux_fix);
}

/*******************************************************************************
* Function name: free_var
*
* Arguments:
    head -> Initial node of the secondary list.
*
* Return:
    Nothing.
*
*
* Description: Frees all the information inside a secondary list node and itself.
*
*******************************************************************************/
void free_var(VAR* head){
    VAR* aux = head;

    free(aux->indicator);
    free(aux->year_week);
    free(aux);
}

/*******************************************************************************
* Function name: free_list
*
* Arguments:
    Listhead -> Initial node of the secondary list.
*
* Return:
    Nothing.
*
*
* Description: Goes through the whole list of lists, freeing everything there is inside the nodes and the nodes themselves, ending up freeing all the nodes.
*
*******************************************************************************/
void free_list(FIX* Listhead){

    FIX* aux = Listhead;

    while(Listhead != NULL){
        VAR* auxi = Listhead -> var;
        while(Listhead -> var != NULL){

            auxi = Listhead -> var;
            Listhead -> var = Listhead -> var -> next;
            free(auxi->indicator);
            free(auxi->year_week);
            free(auxi);

        }
        aux = Listhead;
        Listhead = Listhead -> next;
        free(aux->name);
        free(aux->code);
        free(aux->continent);
        free(aux -> var);
        free(aux);
    }
}



#include "covidData.h"

/*******************************************************************************
* Function name: swapF
*
* Arguments:
    FIX* left -> Pointer to the node before
    FIX* right -> Pointer to the actual node
*
* Return:
    right -> Pointer to the actual node
*
*
* Description: Swaps the position of 2 nodes of the principal list.
*
*******************************************************************************/
FIX *swapF(FIX *left, FIX *right){
    left -> next = right -> next;
    right -> next = left;
    return right;
}

/*******************************************************************************
* Function name: alfa
*
* Arguments:
    Listhead -> Initial node of the principal list.
*
* Return:
    Listhead -> Initial node of the principal list.
*
*
* Description: Bubble sort algorithm to organize all the list by alphabetical order (A-Z).
*
*******************************************************************************/
FIX *alfa(FIX *Listhead){ //SE OS PAISES FOREM DESORDENADOS POR SEMANAS, TEMOS DE FAZER ESTE ALGORITMO PARA DADOS VARIAVEIS
    int trocas = 1;
    FIX *left, *right, *head, aux_struct;

    head= &aux_struct;
    head-> next = Listhead;

    if((Listhead!= NULL) && ((Listhead-> next != NULL))){
        while(trocas){
            trocas = 0;
            left = head;
            right = head-> next;
            while(right -> next != NULL){
                if( (strcmp(right->name,right->next->name))>0){
                    left -> next = swapF(right,right->next);
                    trocas = 1;
                }
                left = right;
                if(right->next != NULL) right = right->next;
            }
        }
    }
    Listhead= head-> next;
    return Listhead;
}

/*******************************************************************************
* Function name: pop
*
* Arguments:
    Listhead -> Initial node of the principal list.
*
* Return:
    Listhead -> Initial node of the principal list.
*
*
* Description: Bubble sort algorithm to organize all the list by population. (Highest to lowest)
*
*******************************************************************************/
FIX *pop(FIX *Listhead){
    int trocas = 1;
    FIX *left, *right, *head, aux_struct;

    head= &aux_struct;
    head-> next = Listhead;

    if((Listhead!= NULL) && ((Listhead-> next != NULL))){
        while(trocas){
            trocas = 0;
            left = head;
            right = head-> next;
            while(right -> next != NULL){
                if(right -> population < right->next-> population){
                    left -> next = swapF(right,right->next);
                    trocas = 1;
                }
                else if((right -> population == right -> next -> population) && (strcmp(right -> name, right -> next -> name) > 0)){
                    left -> next = swapF(right,right->next);
                    trocas = 1;
                }
                left = right;
                if(right->next != NULL) right = right->next;
            }
        }
    }
    Listhead= head-> next;
    return Listhead;
}


/*******************************************************************************
* Function name: inf_yyyy_ww
*
* Arguments:
    FIX* Listhead -> Initial node of the principal list.
    char* data -> String relative to a certain date.
*
* Return:
    Listhead -> Initial node of the principal list.
*
*
* Description: Bubble sort algorithm to organize all the list by weekly_count of infected cases for the specified
date ("data").
*
*******************************************************************************/
FIX *inf_yyyy_ww(FIX *Listhead, char* data){
    int trocas = 1;
    FIX *left, *right, *head, aux_struct;
    VAR *head1, *head2;

    int weeklyc1 = 0;
    int weeklyc2 = 0;

    head= &aux_struct;
    head-> next = Listhead;

    if((Listhead!= NULL) && ((Listhead-> next != NULL))){
        while(trocas){
            trocas = 0;
            left = head;
            right = head-> next;
            while(right -> next != NULL){
                head1 = right -> var;
                head2 = right -> next -> var;
                        weeklyc1 = 0;
                        weeklyc2 = 0;
                    while(head1!= NULL){
                        if((strcmp(head1->indicator,"cases") == 0) && (strcmp(head1->year_week,data) == 0)){//The first VAR pointer, points to the before node. And saves on "weeklyc1" the weekly count for the date "data".
                            weeklyc1 = head1->weekly_count;
                        }
                        head1 = head1 -> next;
                    }
                    while(head2!= NULL){
                        if( (strcmp(head2->indicator,"cases") == 0) && (strcmp(head2->year_week,data) == 0) ){//The second VAR pointer, points to the before->next node. And saves on "weeklyc2" the weekly count for the date "data".
                            weeklyc2 = head2->weekly_count;
                        }
                        head2 = head2 -> next;
                    }
                    if( weeklyc2 > weeklyc1 ){ //Compares both values and if the 2nd is higher than the first, they swap.
                            left -> next = swapF(right,right->next);
                            trocas = 1;
                        }
                    else if((weeklyc2 == weeklyc1) && (strcmp(right -> name, right -> next -> name) > 0)){
                            left -> next = swapF(right,right->next);
                            trocas = 1;
                    }
                    left = right;
                    if(right->next != NULL) right = right->next;
                    }
            }
    }
    Listhead = head-> next;
    return Listhead;
}

/*******************************************************************************
* Function name: dea_yyyy_ww
*
* Arguments:
    FIX* Listhead -> Initial node of the principal list.
    char* data -> String relative to a certain date.
*
* Return:
    Listhead -> Initial node of the principal list.
*
*
* Description: Bubble sort algorithm to organize all the list by weekly_count of death cases for the specified
date ("data").
*
*******************************************************************************/
FIX *dea_yyyy_ww(FIX *Listhead, char* data){
    int trocas = 1;
    FIX *left, *right, *head, aux_struct;
    VAR *head1, *head2;

    int weeklyc1 = 0;
    int weeklyc2 = 0;

    head= &aux_struct;
    head-> next = Listhead;

    if((Listhead!= NULL) && ((Listhead-> next != NULL))){
        while(trocas){
            trocas = 0;
            left = head;
            right = head-> next;
            while(right -> next != NULL){
                head1 = right -> var;
                head2 = right -> next -> var;
                        weeklyc1 = 0;
                        weeklyc2 = 0;
                    while(head1!= NULL){
                        if((strcmp(head1->indicator,"deaths") == 0) && (strcmp(head1->year_week,data) == 0)){//The first VAR pointer, points to the before node. And saves on "weeklyc1" the weekly count for the date "data".
                            weeklyc1 = head1->weekly_count;
                        }
                        head1 = head1 -> next;
                    }
                    while(head2!= NULL){
                        if( (strcmp(head2->indicator,"deaths") == 0) && (strcmp(head2->year_week,data) == 0) ){//The second VAR pointer, points to the before->next node. And saves on "weeklyc2" the weekly count for the date "data".
                            weeklyc2 = head2->weekly_count;
                        }
                        head2 = head2 -> next;
                    }
                    if( weeklyc2 > weeklyc1 ){//Compares both values and if the 2nd is higher than the first, they swap.
                            left -> next = swapF(right,right->next);
                            trocas = 1;
                        }
                    else if((weeklyc2 == weeklyc1) && (strcmp(right -> name, right -> next -> name) > 0)){
                            left -> next = swapF(right,right->next);
                            trocas = 1;
                    }
                    left = right;
                    if(right->next != NULL) right = right->next;
                    }
            }
    }
    Listhead = head-> next;
    return Listhead;
}

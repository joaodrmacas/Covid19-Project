
#include "covidData.h"


/*******************************************************************************
* Function name: check_input_L
*
* Arguments:
    input -> Continent chosen on console arguments by the user.
*
* Return: Nothing.
*
*
* Description: Checks all the possible continents the user can choose, if the input doesnt
match with the continent list, it will return an error.
*
*******************************************************************************/
void check_input_L(char* input){

    char available_countries[6][10] = {"Oceania", "Asia", "Europe", "America", "Africa", "all"};
    int i;

    for(i=0; i<6; i++){
        if( (strcmp(input,available_countries[i])) == 0 ){
            return;
        }
    }

    fprintf (stderr, "-1 Invalid Continent\n");
    help();
}

/*******************************************************************************
* Function name: check_input_S
*
* Arguments:
    input -> Sort mode chosen on the console arguments by the user.
*
* Return: Nothing.
*
*
* Description: Checks all the possible sorts modes the user can choose,if the input doesnt
match with the sorting list, it will return an error.
*
*******************************************************************************/
void check_input_S(char* input){

    char available_sorts[4][5] = {"pop","inf","dea","alfa"};
    int i=0;

    for(i=0; i<=4; i++){
        if( (strcmp(input,available_sorts[i])) == 0 ){
            return;
        }
    }

    fprintf (stderr, "-1 Invalid sort option\n");
    help();

}

/*******************************************************************************
* Function name: check_input_D
*
* Arguments:
    input -> Selection mode chosen on the console arguments by the user.
*
* Return: Nothing.
*
*
* Description: Checks all the possible selection modes the user can choose,if the input doesnt
match with the selection list, it will return an error.
*
*******************************************************************************/
void check_input_D(char* input){

    char available_selec[5][10] = {"inf", "dea", "racioinf", "raciodea",""};
    int i=0;

    for(i=0; i<=4; i++){
        if( (strcmp(input,available_selec[i])) == 0 ){
            return;
        }
    }

    fprintf (stderr, "-1 Invalid selection option\n");
    help();

}

/*******************************************************************************
* Function name: check_input_P
*
* Arguments:
    input -> Restriction mode chosen on the console arguments by the user.
*
* Return: Nothing.
*
*
* Description: Checks all the possible restriction modes the user can choose,if the input doesnt
match with the restriction list, it will return an error.
*
*******************************************************************************/
void check_input_P(char* input){
    char available_rest[5][10] = {"min", "max", "date", "dates",""};
    int i=0;

    for(i=0; i<=5; i++){
        if( (strcmp(input,available_rest[i])) == 0 ){
            return;
        }
    }

    fprintf (stderr, "-1 Invalid restriction option\n");
    help();
}

/*******************************************************************************
* Function name: check_RorW_type
*
* Arguments:
    input -> Filename chosen on the console arguments by the user to be read / written.
*
* Return:
    1 -> When the input is a binary file (.dat)
    0 -> When the input is a text file (.csv)
*
*
* Description: Checks if the user wants to read/write a Binary file or a CSV file,if the input doesnt
match with the extensions list, it will return an error.
*
*******************************************************************************/
int check_RorW_type(char* input){

    char* extension;

    extension = strrchr(input, '.');

    if(!extension || extension == input){
        fprintf (stderr, "-1 Filetype not recognized\n");
        help();
    }

    if( (strcmp(extension,".csv")) == 0 ) return 0;
    else if( (strcmp(extension, ".dat")) == 0) return 1;

    else{
        fprintf (stderr, "-1 Filetype not recognized\n");
        help();
    }

    return -1;
}

/*******************************************************************************
* Function name: checkDate
*
* Arguments:
    char* data -> String of the date.
*
* Return: Nothing.
*
*
* Description: Checks if "data" string is correspondent to the format "yyyy-ww"
and if its a possible date aswell.
*
*******************************************************************************/
void checkDate(char* data){
    int i;
    int ano;
    int mes;

    if(strlen(data) != 7){
        fprintf(stderr, "-1 Invalid date");
        help();
    }

    if(data[4] != '-'){
        fprintf(stderr, "-1 Invalid date");
        help();
    }

    for(i=1; i<=7; i++){
        if(i!=5){
            if(isalpha(data[i])){
            fprintf(stderr, "-1 Invalid date");
            help();
            }
        }
    }

    sscanf(data, "%d-%d", &ano, &mes);

    if(ano<2019 || ano>2021 || mes<0 || mes>53){
        fprintf(stderr,"-1 Invalid Date");
        help();
    }
}

/*******************************************************************************
* Function name: check_name
*
* Arguments:
    head -> Initial node of the principal list.
    nome -> Name of the country.
*
* Return:
    0 -> There isnt a node with the name of the argument "nome"
    1 -> There is already a node with the name.
*
*
* Description: The function goes through the principal list to check if there is a node with the same name as the argument.
*
*******************************************************************************/
int check_name(FIX *head, char* nome){

    FIX* aux = NULL;

    aux = head;

    while(aux != NULL){

        if((strcmp(nome, aux->name)) == 0){
            return 1;
        }
        aux = aux -> next;
    }
        return 0;
}

/*******************************************************************************
* Function name: check_code_len
*
* Arguments:
    char* token -> string to analyze
*
* Return:
    Nothing
*
*
* Description: This function checks if "token" is 3 characters long.If not, exits the program.
*
*******************************************************************************/
void check_code_len(char* token){
    if(strlen(token) != 3){
        fprintf(stderr,"-1 Error while reading code length.\n");
        help();
    }
}

/*******************************************************************************
* Function name: check_indicator
*
* Arguments:
    char* token -> string to analyze
*
* Return:
    Nothing
*
*
* Description: This function checks if "token" corresponds to "cases" or "deaths". If not, exit the program.
*
*******************************************************************************/
void check_indicator(char* token){

    if( ((strcmp(token, "cases"))!=0) || ((strcmp(token, "deaths"))!=0) ){
        fprintf(stderr, "-1 Error while reading indicator.\n");
        help();
    }
}

/*******************************************************************************
* Function name: check_emptyrows
*
* Arguments:
    char* token -> string to analyze
*
* Return:
    Nothing
*
*
* Description: This function checks if a string is empty, if so exits with help function.
Its used to check if rows from csv file are empty while reading it.
*
*******************************************************************************/
void check_emptyrows(char* token){
    if ( (token != NULL)) {
        if( (token[0] == '\0') || (token[0] == '\n') || (token[0]== '\r') ){
            fprintf(stderr, "-1 Error: Empty line detected.\n");
            help();
        }
    }
}

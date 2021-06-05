
#include "covidData.h"

/*******************************************************************************
* Function name: create_var
*
* Arguments:
    head -> Initial node of the secondary list.
    indicator -> Indicator of the variables node
    weekly_count -> Weekly count of the variables node
    year_week -> Year and week of the variables node
    rate_14_days -> Rate on the last 14 days of the variables node
    cumulative_count -> Cumulative count of the variables node
*
* Return:
    VAR* head: Pointer for the first element of the secondary list
*
*
* Description: Allocates and saves the information of the arguments onto nodes of the secondary list.
*
*******************************************************************************/
VAR *create_var(VAR* head,char* indicator,int weekly_count, char* year_week, double rate_14_days, int cumulative_count){

    if(head == NULL){
        head = (VAR*) calloc (1,(sizeof(VAR)));
        head ->  indicator = (char*)calloc(1,(strlen(indicator)+1)*sizeof(char));
        strcpy(head->indicator, indicator);
        head->weekly_count= weekly_count;
        head -> year_week = (char*)calloc(1,(strlen(year_week)+1)*sizeof(char));
        strcpy(head->year_week,year_week);
        head->rate_14_days = rate_14_days;
        head-> cumulative_count = cumulative_count;
        head -> next = NULL;
    }
    else{
        VAR* aux = head;
        while(aux -> next != NULL){
            aux = aux -> next;
        }
            aux->next = (VAR*) calloc(1,(sizeof(VAR)));
            aux = aux -> next;
            aux->indicator = (char*)calloc(1,(strlen(indicator)+1)*sizeof(char));
            strcpy(aux->indicator, indicator);
            aux -> weekly_count = weekly_count;
            aux -> year_week = calloc(1,(strlen(year_week)+1)*sizeof(char));
            strcpy(aux->year_week,year_week);
            aux -> rate_14_days = rate_14_days;
            aux-> cumulative_count = cumulative_count;
            aux -> next = NULL;
    }
    return head;
}

/*******************************************************************************
* Function name: create_fix
*
* Arguments:
    head -> Initial node of the principal list.
    nome -> Name of the country
    code -> Code of the country
    continent -> Continent of the country
    population -> Population number of the country
    indicator -> Indicator of the variables node
    weekly_count -> Weekly count of the variables node
    year_week -> Year and week of the variables node
    rate_14_days -> Rate on the last 14 days of the variables node
    cumulative_count -> Cumulative count of the variables node
*
* Return:
    FIX* head: Pointer for the first element of the principal list
*
*
* Description: Allocates and saves the information of the arguments onto nodes of the main list.
*
*******************************************************************************/
FIX *create_fix(FIX *head, char* nome, char* code, char* continent,int population,char* indicator,int weekly_count, char* year_week, double rate_14_days, int cumulative_count){

    if(head == NULL){
        head = (FIX*) calloc(1,sizeof(FIX));
        head->name = (char*)calloc(1,(strlen(nome)+1)*sizeof(char));
        strcpy(head->name, nome);
        head-> code = (char*)calloc(1,(strlen(code)+1)*sizeof(char));
        strcpy(head->code, code);
        head-> continent = (char*)calloc(1,(strlen(continent)+1)*sizeof(char));
        strcpy(head->continent, continent);
        head -> population = population;
        head -> var = create_var(head -> var, indicator, weekly_count, year_week ,rate_14_days,cumulative_count);
        head -> next = NULL;
    }
    else{
        FIX *aux = head;

        while(aux -> next != NULL){
            aux = aux -> next;
        }
        aux->next =(FIX*) calloc(1,sizeof(FIX));
        aux = aux -> next;
        aux->name = (char*)calloc(1,(strlen(nome)+1)*sizeof(char));
        strcpy(aux->name, nome);
        aux-> code = (char*)calloc(1,(strlen(code)+1)*sizeof(char));
        strcpy(aux->code, code);
        aux-> continent = (char*)calloc(1,(strlen(continent)+1)*sizeof(char));
        strcpy(aux->continent, continent);
        aux -> population = population;
        aux -> var = create_var(aux -> var, indicator, weekly_count, year_week ,rate_14_days,cumulative_count);
        aux -> next = NULL;
    }

    return head;
}

/*******************************************************************************
* Function name: createNodes
*
* Arguments:
    head -> Initial node of the principal list.
    name -> Name of the country
    code -> Code of the country
    continent -> Continent of the country
    population -> Population number of the country
    indicator -> Indicator of the variables node
    weekly_count -> Weekly count of the variables node
    year_week -> Year and week of the variables node
    rate_14_days -> Rate on the last 14 days of the variables node
    cumulative_count -> Cumulative count of the variables node
*
* Return:
    FIX* head: Pointer for the first element of the principal list
*
*
* Description: This function creates principal list nodes and secondary list nodes, given certain situations.
*
*******************************************************************************/
FIX* createNodes(FIX* head,char* name, char* code, char* continent,int population,char* indicator,int weekly_count, char* year_week, double rate_14_days, int cumulative_count){
    int checkName;
            if((checkName=check_name(head,name)) == 0){ //Creates a new principal list node if there isnt a country with that name already.
                head = create_fix(head, name, code,continent, population,indicator,weekly_count,year_week,rate_14_days,cumulative_count);
            }
            else if((check_name(head,name)) == 1){ //Creates a new secondary list node.
                FIX* aux = head;
                while(aux -> next != NULL){
                    if( (strcmp(aux->name,name)) == 0){
                    break;
                }
                    aux = aux->next;
                }
                aux -> var = create_var(aux->var,indicator,weekly_count,year_week,rate_14_days,cumulative_count);
            }
            return head;
}

/*******************************************************************************
* Function name: numCountries
*
* Arguments:
    head -> Initial node of the principal list.
*
* Return:
    n -> Number of nodes of the given list.
*
*
* Description: Goes through the principal list incrementing for each cycle.
*
*******************************************************************************/
int numCountries(FIX* head){

    FIX* aux = head;
    int n=0;

    while(aux!=NULL){
        n++;
        aux = aux -> next;
    }

    return n;
}

/*******************************************************************************
* Function name: numVar
*
* Arguments:
    head -> Initial node of the principal list.
*
* Return:
    n -> Number of nodes of the given list.
*
*
* Description: The function goes through the secondary list, printing out to a binary file (.dat) all the nodes on the list.
*
*******************************************************************************/
int numVar(VAR* head){
    VAR* aux=head;
    int n=0;

    while(aux!= NULL){
        n++;
        aux = aux->next;
    }

    return n;
}


/*******************************************************************************
* Function name: read
*
* Arguments:
    filename -> File name the information is read from.
    continente -> Name of the continent the user wants to read the information of.
*
* Return:
    FIX* head: Pointer to the initial node of the principal list after the list of lists is fully created.
*
*
* Description: Given a text file, this function will read it, line by line, while creating nodes for each country (in the main list) and each variable information
of that country (secondary list).
*
*******************************************************************************/

FIX *read(char* filename, char* continente){
    FILE *pFile = NULL;
    FIX *head = NULL;

    char buffer[150] = "";
    char* token = "";
    int count_token = 1;
    char* pBuffer = buffer;
    char name[30]="", code[25]="", continent[25]="";
    char year_week[20]="";
    int population=0;
    //variaveis
    char indicator[25]="";
    int weekly_count=0,cumulative_count=0;
    double rate_14_days=0;
    int i;

    pFile = fopen(filename, "r");
    if(pFile == NULL){
        printf("An error has ocurred while reading the file. \n");
        exit(EXIT_FAILURE);
    }

    fgets(buffer, sizeof(buffer), pFile); //Skip the first line of the text file.

    while(fgets(buffer, sizeof(buffer), pFile) != NULL){

        pBuffer = buffer;
        count_token = 1;

        /*parse each individually line with a buffer, saving all the information on the respective variable*/

        while((token = strseparate(&pBuffer, ","))!=NULL){ // verificar se as listas tao vazias? a excessao da 8ª

                switch(count_token){
                    case 1:
                        check_emptyrows(token);
                        for(i=0; i<(strlen(token)); i++){
                            if(isdigit(token[i])){
                                fprintf(stderr,"-1 Error while reading country name.\n");
                                help();
                            }
                        }
                        strcpy(name,token);
                        break;
                    case 2:
                        check_emptyrows(token);
                        for(i=0; i<(strlen(token)); i++){
                            check_code_len(token);
                            if(isdigit(token[i])){
                                fprintf(stderr,"-1 Error while reading code.\n");
                                help();
                            }
                        }
                        strcpy(code,token);
                        break;
                    case 3:
                        check_emptyrows(token);
                        check_input_L(token);
                        strcpy(continent,token);
                        break;
                    case 4:
                        check_emptyrows(token);
                        for(i=0; i<(strlen(token)); i++){
                            if(isalpha(token[i])){
                                fprintf(stderr,"-1 Error while reading population.\n");
                                help();
                            }
                        }
                        population = atoi(token);
                        break;
                    case 5:
                        check_emptyrows(token);
                        for(i=0; i<(strlen(token)); i++){
                            if(isdigit(token[i])){
                                fprintf(stderr,"-1 Error while reading indicator.\n");
                                help();
                            }
                        }
                        //check_indicator(token); We tried to use this function but it wasnt working.
                        strcpy(indicator,token);
                        break;
                    case 6:
                        check_emptyrows(token);
                        for(i=0; i<(strlen(token)); i++){
                            if(isalpha(token[i])){
                                fprintf(stderr,"-1 Error while reading weekly count.\n");
                                help();
                            }
                        }
                        weekly_count = atoi(token);
                        break;
                    case 7:
                        check_emptyrows(token);
                        checkDate(token);
                        strcpy(year_week, token);
                        break;
                    case 8:
                        for(i=0; i<(strlen(token)); i++){
                            if(isalpha(token[i])){
                                fprintf(stderr,"-1 Error while reading rate for the last 2 weeks.\n");
                                help();
                            }
                        }
                        rate_14_days = atof(token);
                        break;
                    case 9:
                        check_emptyrows(token);
                        for(i=0; i<(strlen(token)); i++){
                            if(isalpha(token[i])){
                                fprintf(stderr,"-1 Error while reading cumulative count.\n");
                                help();
                            }
                        }
                        cumulative_count = atoi(token);
                        break;
                }
                count_token++;
            }

        if(strcmp(continente,"all") == 0){ //Creates nodes for all the data on the file
            head = createNodes(head,name,code,continent,population,indicator,weekly_count,year_week,rate_14_days,cumulative_count);
        }
        if((strcmp(continente,continent))==0){ //Creates nodes for the continent specified.
            head = createNodes(head,name,code,continent,population,indicator,weekly_count,year_week,rate_14_days,cumulative_count);
        }
    }

    fclose(pFile);

    return head;
}

/*******************************************************************************
* Function name: write
*
* Arguments:
    Listhead -> Initial node of the principal list.
    filename -> File name the information is written to.
*
* Return: Nothing.
*
*
* Description: The function goes through the whole list, printing out to a text file (.csv) all the nodes on the list.
*
*******************************************************************************/
void write(FIX* Listhead, char* filename){
    FILE * pFile = NULL;
    FIX *aux = Listhead;
    VAR *ax = Listhead -> var;

    pFile = fopen(filename, "w");

    if(pFile == NULL){
        printf("That file couldn't be opened");
        exit(EXIT_FAILURE);
    }

    if(aux == NULL){
        printf("No data to be displayed.");
    }

    else{

        fprintf(pFile,"country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");

        while(aux != NULL){ //Goes through the whole list of lists printing out the information.
            ax = aux -> var;
            while(ax != NULL){
                fprintf(pFile,"%s,", aux -> name);
                fprintf(pFile,"%s,", aux -> code);
                fprintf(pFile,"%s,", aux -> continent);
                fprintf(pFile,"%d,", aux -> population);
                fprintf(pFile,"%s,", ax ->indicator);
                fprintf(pFile,"%d,", ax-> weekly_count);
                fprintf(pFile,"%s,", ax ->year_week);
                fprintf(pFile,"%lf,", ax ->rate_14_days);
                fprintf(pFile,"%d\n", ax -> cumulative_count);
                ax = ax -> next;
            }
            aux = aux -> next;
        }
    }

    free_list(Listhead);

    printf("Your file -%s- was printed sucessfully\n", filename);

    fclose(pFile);
}

/*******************************************************************************
* Function name: readBinary
*
* Arguments:
    filename -> File name the information is read from.
*
* Return:
    FIX* head: Pointer to the initial node of the principal list after the list of lists is fully created.
*
*
* Description: Given a binary file, this function will read it, while saving the info into variables and then, creating nodes for each
 country (in the main list) and each variable information.
of that country (secondary list).
*
*******************************************************************************/
FIX *readBinary(char* filename){
    FIX* head=NULL;
    FILE *fp;
    int num_fix;
    int num_var;
    char *name=NULL;
    char *continent=NULL;
    char *code =NULL;
    char *indicator=NULL;
    char *year_week=NULL;
    int population,weekly_count,cumulative_count;
    float rate_14_days;

    int i=0, j=0;
    int name_len=0, code_len = 0, continent_len = 0;
    int indicator_len=0, yearweek_len = 0;


    fp = fopen(filename, "rb");

    if (fp == NULL){
        printf("Erro ao ler o ficheiro");
        exit(EXIT_FAILURE);
    }

    fread(&num_fix, sizeof(int),1,fp); //Reads the number of country nodes on the list;

    for(i=0; i != num_fix; i++){
        fread(&num_var, sizeof(int),1,fp); //Reads the number of lines of variable data for each country.

        fread(&name_len,sizeof(int),1,fp); //Reads the lenght of the name
        fread(&code_len,sizeof(int),1,fp); //Reads the lenght of the code
        fread(&continent_len,sizeof(int),1,fp); //Reads the lenght of the continent

        name = (char*)malloc(name_len);
        fread(&(*name),name_len,1,fp);
        code = (char*)malloc(code_len);
        fread(&(*code),code_len,1,fp);
        continent = (char*)malloc(continent_len);
        fread(&(*continent),continent_len,1,fp);
        fread(&(population),sizeof(int),1,fp);

        for(j=0; j!=num_var; j++){

            fread(&indicator_len, sizeof(int), 1, fp); //Reads the lenght of the indicator
            fread(&yearweek_len, sizeof(int), 1, fp); //Reads the lenght of the year_week

            indicator = (char*)malloc(indicator_len);
            fread(&(*indicator), indicator_len,1,fp);
            fread(&weekly_count, sizeof(int),1,fp);
            year_week = (char*)malloc(yearweek_len);
            fread(&(*year_week),yearweek_len,1,fp);
            fread(&rate_14_days, sizeof(float),1,fp);
            fread(&cumulative_count, sizeof(int),1,fp);

            head = createNodes(head,name,code,continent,population,indicator,weekly_count,year_week,rate_14_days,cumulative_count);

            free(indicator);
            free(year_week);
        }

        free(name);
        free(code);
        free(continent);
    }


    fclose(fp);

    return head;
}

/*******************************************************************************
* Function name: writeBinary
*
* Arguments:
    head -> Initial node of the principal list.
    filename -> File name the information is written to.
*
* Return: Nothing.
*
*
* Description: The function goes through the whole list, printing out to a binary file (.dat) all the nodes on the list.
*
*******************************************************************************/
void writeBinary(FIX* head, char* filename){

    FILE *pFile = NULL;
    FIX* aux_fix = head;
    VAR* aux_var = head -> var;
    int num_fix = numCountries(head);
    int num_var;
    int name_len = 0,code_len = 0,continent_len = 0, indicator_len=0, yearweek_len=0;

    pFile = fopen(filename,"wb");

    if(pFile==NULL){
        printf("Error reading the file.\n");
        exit(EXIT_FAILURE);
    }

    if(head == NULL){
        printf("No data to be displayed.");
    }

    fwrite(&num_fix, sizeof(int), 1, pFile); //Writes the number of country nodes on the list.

    while(aux_fix != NULL){
        aux_var = aux_fix -> var;
        name_len = strlen(aux_fix -> name)+1;
        code_len = strlen(aux_fix -> code)+1;
        continent_len = strlen(aux_fix -> continent)+1;

        num_var = numVar(aux_fix->var);

        fwrite(&num_var, sizeof(int), 1, pFile); //Writes the number of variable data nodes for each country.

        fwrite(&name_len, sizeof(int), 1, pFile); //Writes the name lenght
        fwrite(&code_len, sizeof(int), 1, pFile); //Writes the code lenght
        fwrite(&continent_len, sizeof(int), 1, pFile); //Writes the continent lenght

        fwrite(aux_fix -> name, name_len, 1, pFile);
        fwrite(aux_fix -> code, code_len, 1, pFile);
        fwrite(aux_fix -> continent, continent_len, 1, pFile);
        fwrite(&aux_fix -> population, sizeof(int), 1, pFile);

        while(aux_var != NULL){

            indicator_len = strlen(aux_var -> indicator)+1; //Writes the indicator lenght
            yearweek_len = strlen(aux_var -> year_week)+1; //Writes the year_week lenght
            fwrite(&indicator_len, sizeof(int),1,pFile);
            fwrite(&yearweek_len, sizeof(int),1,pFile);

            fwrite(aux_var -> indicator, indicator_len, 1,pFile);
            fwrite(&aux_var -> weekly_count, sizeof(int), 1,pFile);
            fwrite(aux_var -> year_week, yearweek_len, 1,pFile);
            fwrite(&aux_var -> rate_14_days, sizeof(int), 1,pFile);
            fwrite(&aux_var -> cumulative_count, sizeof(int), 1,pFile);

            aux_var = aux_var -> next;
        }

        aux_fix = aux_fix -> next;
    }

    printf("Your file -%s- was printed sucessfully\n", filename);

    free_list(head);

    fclose(pFile);

}

#include "covidData.h"


int main(int argc, char* argv[]){

    FIX* head = NULL;

    int selection_flag = 0, restriction_flag = 0, binary_flag = 0, continent_flag = 0, sort_flag = 0;
    char* filename="";
    char* output="";
    char* continente = "all";
    char* sort = "alfa";
    char* date_sort ="";
    char* selection = "";
    char* restriction = "";
    char* reading = "";
    char* writing="";
    int rest_min=0;
    int rest_max=0;
    char* rest_data_only="";
    char* rest_data_interval_1="";
    char* rest_data_interval_2="";
    int option_val, checkInput_i =2, checkInput_o = 2;

    while((option_val = getopt(argc, argv, ":i:L:S:D:P:o:")) != -1){
        switch(option_val){
            case 'o':
                writing = optarg;
                break;
            case 'L':
                continent_flag = 1;
                continente = optarg;
                break;
            case 'S':
                sort_flag = 1;
                optind--;
                if( ((strcmp(argv[optind],"alfa")) == 0) || ((strcmp(argv[optind],"pop"))==0) ){
                    sort = argv[optind];
                }
                else if( ((strcmp(argv[optind],"inf"))==0) || ((strcmp(argv[optind],"dea"))==0) ){
                    sort = argv[optind];
                    date_sort = argv[optind+1];
                    checkDate(date_sort);
                }
                break;
            case 'D':
                selection_flag = 1;
                selection = optarg;
                break;
            case 'P':
                restriction_flag = 1;
                optind--;
                restriction = argv[optind];
                if((strcmp(restriction, "min")) == 0){
                    rest_min = atoi(argv[optind+1]);
                }
                else if((strcmp(restriction, "max")) == 0){
                    rest_max = atoi(argv[optind+1]);
                }
                else if(((strcmp(restriction, "date")) == 0)){
                    rest_data_only = argv[optind+1];
                    checkDate(rest_data_only);
                }
                else if(((strcmp(restriction, "dates")) == 0)){
                    rest_data_interval_1 = argv[optind+1];
                    checkDate(rest_data_interval_1);
                    rest_data_interval_2 = argv[optind+2];
                    checkDate(rest_data_interval_2);
                }
                break;
            case 'i':
                reading = optarg;
                break;
            case '?':
                if (isprint (optopt))
                  fprintf (stderr, "-1 Unknown option `-%c'.\n", optopt);
                exit(EXIT_FAILURE);
            case ':':
                if (optopt == 'i')
                  fprintf (stderr, "-1 The option -%c needs an argument.\n", optopt);
                exit(EXIT_FAILURE);
            }
    }

    filename = reading;
    output = writing;

    printf("Program call: i-> %s, L-> %s, S-> %s, D-> %s, P-> %s, o-> %s\n\n\n", reading, continente, sort, selection, restriction, writing);

//-------------Checkar Input----------------

    check_input_L(continente);

    check_input_S(sort);

    check_input_D(selection);

    check_input_P(restriction);

    checkInput_i = check_RorW_type(reading);

    checkInput_o = check_RorW_type(writing);


//----------------Ler-------------------

    if(continent_flag == 1 && binary_flag == 1){
        fprintf(stderr, "-1 Error: Cant use -L when reading from a binary file");
        help();
    }

    if (checkInput_i == 0) head = read(filename, continente);
    else if(checkInput_i == 1){
        head = readBinary(filename);
        binary_flag = 1;
    }

//-------------selecionar---------------

    if(selection_flag == 1){
        if(binary_flag == 0){
            if((strcmp(selection,"inf")) == 0) head = inf(head);
            else if((strcmp(selection,"dea")) == 0) head = dea(head);
            else if((strcmp(selection,"racioinf")) == 0) head = racinf(head);
            else if((strcmp(selection,"raciodea")) == 0) head = racdea(head);
        }
        else if(binary_flag ==1){
            fprintf(stderr, "-1 Error: Cant use -D when reading from a binary file");
            help();
        }
    }

//-------------restringir---------------

    if(restriction_flag == 1){
        if(binary_flag == 0){
            if((strcmp(restriction,"min")) == 0) head = min(head, rest_min);
            else if((strcmp(restriction,"max")) == 0) head = max(head, rest_max);
            else if((strcmp(restriction,"date")) == 0) head = date_only(head, rest_data_only);
            else if((strcmp(restriction,"dates")) == 0) head = date_interval(head,rest_data_interval_1,rest_data_interval_2);
        }
        else if(binary_flag ==1){
            fprintf(stderr, "-1 Error: Cant use -P when reading from a binary file");
            help();
        }
    }

//----------------Sort------------------

    if(binary_flag == 0){
        if((strcmp(sort,"pop")) == 0) head = pop(head);
        else if((strcmp(sort,"alfa")) == 0) head = alfa(head);
        else if((strcmp(sort,"inf")) == 0) head = inf_yyyy_ww(head,date_sort);
        else if((strcmp(sort,"dea")) == 0) head = dea_yyyy_ww(head,date_sort);
    }
    else if(binary_flag ==1 && sort_flag == 1){
        fprintf(stderr, "-1 Error: Cant use -S when reading from a binary file");
        help();
    }

//--------------Escrever----------------

    if(checkInput_o == 0)write(head,output);
    else if(checkInput_o == 1)writeBinary(head,output);


    return 0;
}



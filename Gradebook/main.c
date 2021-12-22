//
//  main.c
//  Gradebook
//
//  Created by Rizwan Syed on 10/30/21.
//

#include <stdio.h>
#include <string.h>

// TODO: ask user for list of classes and store it, so you are making an array of character arrays
// TODO: state the number of classes, and ask them to enter the corresponding number in order to enter that class
// TODO: when in a class menu, have a button that allows the user to go back, and another button which calculates the weight of
typedef struct{
    char name[50];
    int numWords;
} class;

void classWriter(FILE *pointer){
    
    pointer = fopen("gradebook.txt", "w");
    printf("Please enter the names of your classes, pressing enter after each class(< 50 characters). When you are finished enterring your classes, press the ` key, and then press enter.\n");
    char input[50];
    //scanf("%[^\n]s", input);
    fgets(input, sizeof(input), stdin);
    
    /*
    int i = 0;
    while(input[i] != '\0'){
        if(input[i] == ' '){
            input[i] = '_';
        }
        i++;
    }
    */
    /*
    printf("\n");
    printf("%s", input);
    printf("\n");
    printf("%d", strcmp(input, "`"));
    printf("\n");
     */
    int i = 0;
    while(input[i] != '\0'){
        if(input[i] == '\n'){
            input[i] = '\0';
        }
        i++;
    }
    
    while(strcmp(input, "`") != 0){
        
        fprintf(pointer, "%s\n", input);
        
        
        //scanf("%[^\n]s", input);
        fgets(input, sizeof(input), stdin);
        
        /*
        printf("\n");
        printf("%s", input);
        printf("\n");
        printf("%d", strcmp(input, "`"));
        printf("\n");
         */
        
        /*
        int i = 0;
        while(input[i] != '\0'){
            if(input[i] == ' '){
                input[i] = '_';
                printf("space found\n");
            }
            i++;
        }
         */
        int i = 0;
        while(input[i] != '\0'){
            if(input[i] == '\n'){
                input[i] = '\0';
            }
            i++;
        }
        
    }
    
}


int main(){
    //remove("gradebook.txt");
    FILE *fptr;
    fptr = fopen("gradebook.txt", "r");
    if(fptr == NULL){
        printf("Welcome to the gradebook program! Please enter the names of the classes you have taken this quarter!\n\n");
        //function which writes classes to files
        classWriter(fptr);
    }
    
    else{
        //give the user the option to either view one of their classes, or edit the list of classes which they currently have
        printf("It seems you have used this program before! Here are the classes you currently have enterred in the gradebook: \n\n");
        fptr = fopen("gradebook.txt", "r");
        char line[256];
        
        while( fgets(line, sizeof(line), fptr) ){
            //int i = 0;
            /*
            while(line[i] != '\0'){
                if(line[i] == '_'){
                    line[i] = ' ';
                }
                i++;
            }
             */
            printf("%s" , line);
        }
        printf("\n");
        
    }
    
    fclose(fptr);

    //remove("gradebook.txt");
    return 0;
    
}


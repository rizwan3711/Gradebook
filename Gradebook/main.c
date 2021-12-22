//
//  main.c
//  Gradebook
//
//  Created by Rizwan Syed on 10/30/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO: ask user for list of classes and store it, so you are making an array of character arrays
// TODO: state the number of classes, and ask them to enter the corresponding number in order to enter that class
// TODO: when in a class menu, have a button that allows the user to go back, and another button which calculates the weight of
typedef struct{
    char name[50];
    int pos;
} class;

void classWriter(FILE *pointer){
    
    pointer = fopen("gradebook.txt", "w");
    printf("Please enter the names of your classes, pressing enter after each class(< 50 characters). When you are finished enterring your classes, press the ` key, and then press enter.\n");
    char input[50];
    
    fgets(input, sizeof(input), stdin);
    
    
    int i = 0;
    while(input[i] != '\0'){
        if(input[i] == '\n'){
            input[i] = '\0';
        }
        i++;
    }
    
    while(strcmp(input, "`") != 0){
        
        fprintf(pointer, "%s\n", input);
        
        fgets(input, sizeof(input), stdin);
        
        int i = 0;
        while(input[i] != '\0'){
            if(input[i] == '\n'){
                input[i] = '\0';
            }
            i++;
        }
        
    }
    
}

void classEditor(int pos, class classes[]){
    //first, check if they have ever enterred any grades for this class before
    //pointer = fopen("gradebook.txt", "r");
    FILE *pointer;
    
    char fileName[54];
    int i = 0;
    while(classes[pos - 1].name[i] != '\0'){
        if(classes[pos - 1].name[i] == ' '){
            classes[pos - 1].name[i] = '_';
        }
        i++;
    }
    i = 0;
    while(classes[pos - 1].name[i] != '\n'){
        fileName[i] = classes[pos - 1].name[i];
        i++;
    }
    char extension[5] = ".txt";
    int i2 = 0;
    while(extension[i2] != '\0'){
        fileName[i] = extension[i2];
        i++;
        i2++;
    }
    fileName[i] = '\0';
    i = 0;
    while(classes[pos - 1].name[i] != '\0'){
        if(classes[pos - 1].name[i] == '_'){
            classes[pos - 1].name[i] = ' ';
        }
        i++;
    }
    
    //printf("%s\n", classes[pos-1].name);
    //printf("%s\n", fileName);
    
    pointer = fopen(fileName, "r");
    if(pointer == NULL){
        pointer = fopen(fileName, "w");
        
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
        int classNum = 0;
        //give the user the option to either view one of their classes, or edit the list of classes which they currently have
        printf("It seems you have used this program before! Here are the classes you currently have enterred in the gradebook: \n\n");
        fptr = fopen("gradebook.txt", "r");
        char line[256];
        
        while( fgets(line, sizeof(line), fptr) ){
            printf("%s" , line);
            classNum++;
            
        }
        printf("\n");
        
        fclose(fptr);
        fptr = fopen("gradebook.txt", "r");
        
        class classes[classNum];
        classNum = 0;
        while( fgets(line, sizeof(line), fptr) ){
            classNum++;
            strcpy(classes[classNum-1].name, line);
            classes[classNum-1].pos = classNum;
        }
        
        
        //MARK: giving options on what they want to do with their class list.
        int input;
        printf("press 1 to view/edit your grades for a class, 2 to edit your list of classes, and 3 to exit the program\n\n");
        scanf("%d", &input);
        if(input == 1){
            //call view/edit function
            printf("You currently have %d classes in the gradebook. To view your grades for the first class displayed, press 1, to view your grades for the second class displayed above, press 2, etc. \n\n", classNum);
            scanf("%d", &input);
            
            int flag = 0;
            for(int i = 0; i < classNum; i++){
                if(classes[i].pos == input){
                    flag = 1;
                    classEditor(input, classes, fptr);
                    break;
                }
            }
            if(!flag){
                printf("Enter a valid number!\n");
            }
            
        }
        else if(input == 2){
            //call edit list of classes function
            //make sure that, lets say you have a file containing the grades of Math20D with a lot of data on there. when you remove math20d from the gradebook, make sure you are also removing the math20d text file with all the data for that class
        }
        else if(input == 3){
            exit(0);
        }
        else{
            printf("Please enter a valid input \n\n");
        }
    }
    
    fclose(fptr);

    //remove("gradebook.txt");
    return 0;
    
}


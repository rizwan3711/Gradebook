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
void classWriter(FILE *pointer){
    pointer = fopen("gradebook.txt", "w");
    printf("Please enter the names of your classes, pressing enter after each class. When you are finished enterring your classes, press the ` key, and then press enter.\n");
    char input[50];
    scanf("%s", &input);
    printf("\n");
    while(strcmp(input, "`") != 0){
        //write to the text file
        fprintf(pointer, "%s\n", input);
        scanf("%s", &input);
        printf("\n");
    }
}

int main(){
    FILE *fptr;
    fptr = fopen("gradebook.txt", "r");
    if(fptr == NULL){
        printf("Welcome to the gradebook program! Please enter the names of the classes you have taken this quarter!\n\n");
        //function which writes classes to files
        classWriter(fptr);
    }
    else{
        //give the user the option to either view one of their classes, or edit the list of classes which they currently have
        printf("It seems you have used this program before! Here are the classes you currently have enterred in the gradebook: \n");
        fptr = fopen("gradebook.txt", "r");
        char line[256];
        while( fgets(line, sizeof(line), fptr) ){
            printf("%s\n" , line);
        }
    }
    fclose(fptr);
   
        return 0;
}

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
int main(){
    FILE *fptr;
    if(fopen("gradebook.txt", "w") == NULL){
        printf("Welcome to the gradebook program! Please enter the names of the classes you have taken this quarter!");
        //function which accepts multiple grades
    }
    else{
        //give the user the option to either view one of their classes, or edit the list of classes which they currently have
    }
}

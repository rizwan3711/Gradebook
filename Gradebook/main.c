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
    double weight;
} cat;

typedef struct{
    char name[50];
    int pos;
    cat cats[10];
} class;

void spaceReplacer(char *string){
    int i = 0;
    while(string[i] != '\0'){
        if(string[i] == ' '){
            string[i] = '_';
        }
        i++;
    }
}

int catCounter(FILE *pointer, char *fileName){
    int answer = 0;
    fclose(pointer);
    pointer = fopen(fileName, "r");
    char line[256];
    /*
    fscanf(pointer, "%[^\n]", line);
    printf("%s\n", line);
    */
    int pog = 0;
    while( fgets(line, sizeof(line), pointer) ){
        if(pog == 1){
            break;
        }
        pog++;
    }
    int i = 0;
    while(line[i] != '\0'){
        if(line[i] == '\t'){
            answer++;
        }
        i++;
    }
    //printf("%d", answer);
    return answer;
}

void assignmentWriter(FILE * pointer, char * cat, char * fileName){
    printf("\nPlease enter a numerical decimal value for the grade which you received on this assignment, out of 100. If you received a 93 on you assignment, enter, 93.0\n");
    double ans;
    scanf("%lf", &ans);
    char line[50];
    int counter = 0;
    //int c = 0;
    while( fscanf(pointer, "%s", line) == 1 ){
        if(strcmp(line, cat) == 0){
            break;
        }
        counter++;
    }
    //printf("\n%d\n", c);
    //before appending to the file, figure out which category(column), you are adding a value to. To do this, read from the beginning
    //of the file, so you shoudl use a+ when calling fopen with your file pointer. 
    fclose(pointer);
    pointer = fopen(fileName, "a+");

    fprintf(pointer, "\n");
    int c = 0;
    int c2 = 0;

    //printf("%f %f \n", ans, -1.000);
    //printf("%d\n", catCounter(pointer, fileName));

    while(c2 < catCounter(pointer, fileName)){
        fclose(pointer);
        pointer = fopen(fileName, "a+");

        if(counter == c){
            //printf("%d\n", catCounter(pointer, fileName));
            fprintf(pointer, "%f\t", ans);
            //break;
        }
        else{
            //printf("%d", c);
            fprintf(pointer, "%f\t", -1.000);
        }
        c++;
        c2++;
    }
    //catCounter(pointer, fileName);
}

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
    
    fclose(pointer);
}

void classMenu(int pos, class classes[]){
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
        //MARK: POGGIES
        pointer = fopen(fileName, "w");
        printf("It seems you have never enterred information for this class before! Please enter the categories which your grade is broken down into(homework, finals, etc), pressing enter after each entry. Press ` when you are done enterring categories. You may enter up to 10 categories, each one being 50 characters or less.\n\n");
        char catName[50];
        int catNum = -1;
        fgets(catName, sizeof(catName), stdin);
        int i = 0;
        
        while(catName[i] != '\0'){
            if(catName[i] == '\n'){
                catName[i] = '\0';
            }
            i++;
        }
        
        //MARK: poggies
        while(strcmp(catName, "`") != 0){
            
            strcpy(classes[pos-1].cats[catNum].name, catName);
            
            catNum++; 
            //HERHERHERHERHERHERHERHERHER
            if(strcmp(catName, "\0") != 0){
                spaceReplacer(catName);
                fprintf(pointer, "%s\t", catName);
            }
            fgets(catName, sizeof(catName), stdin);
            int i = 0;
            while(catName[i] != '\0'){
                if(catName[i] == '\n'){
                    catName[i] = '\0';
                } 
                i++;
            }
        }
        fprintf(pointer, "\n");
        //printf("%d", catNum);
       
        printf("\nFor each of the categories printed above, enter a number for how much of your grade this category counts for. For example, if you have a final category which accounts for 50%% of your final grade, enter the number 50 for this category\n");
        double dinput = 0.0;
        for(i = 0; i < catNum; i++){
            printf("%s: \n", classes[pos - 1].cats[i].name);
            scanf("%lf", &dinput);
    
            fprintf(pointer, "%lf\t", dinput);
            //printf("\n%lf\n", dinput);
        }
        
        /*
        for(i = 0; i < catNum; i++){
            //printf("%f\n", classes[pos - 1].cats[i].weight);
            //printf("AT LEAST YOU GOT IN HERE DOE POGGGGG\n");
            //printf("%f\n", classes[pos - 1].cats[i].weight);
            //fprintf(pointer, "%f\t", classes[pos - 1].cats[i].weight);
            //printf("iteration %d worked\n", i);
            //break;
        }
        //printf("POGGGGGGGG");
        */
        
    }
    else{
        //function which prints your current grade in this class
        printf("Press 1 to add any assignments, or press 2 to go back to the class selection menu\n\n");
        int input = 0;
        scanf("%d", &input);
        if(input == 1){
            char line[256];
            /*
            while(fgets(line, sizeof(line), pointer)){
                printf("%s", line);
            }
            */
            fscanf(pointer, "%[^\n]", line);
            printf("%s", line);
            //fclose(fptr);

            printf("\n\nThe categories which you have for this class are displayed above. Enter the category which you would like to enter an assignment for, exactly as it is displayed above.\n");
            char catEntry[50];
            //scanf("%s", catEntry);
            char c = getchar();
            fgets(catEntry, sizeof(catEntry), stdin);
            
            //printf("\n%s\n", catEntry);
            
            char catEntry2[50];
            //printf("\n%s\n", catEntry);
            sscanf(catEntry, "%[^\t\n]", catEntry2);
            //printf("\n%s\n", catEntry2);
            
            fclose(pointer);
            pointer = fopen(fileName, "r");
            while( fscanf(pointer, "%s", line) == 1 ){
                //printf("%s: ", line);
                //printf("%d\n", strcmp(catEntry2, line));
                /*
                printf("%d\n" , strcmp(line, catEntry));
                printf("%s %d\n", catEntry , catEntry);
                printf("%s %d\n\n", line,  line);
                printf("%d\n" , strcmp(line, catEntry));
                */
               if(strcmp(catEntry2, line) == 0){
                   fclose(pointer);
                   pointer = fopen(fileName, "r");
                   // CALL ASSIGNMENT ADDING FUNCTION
                   assignmentWriter(pointer, line, fileName);
                   break;
               }
            }
            
        }
        else if(input == 2){
            //call main menu function
        }
    }
    //printf("asdf\n");
    fclose(pointer);
    //printf("full stack this shit is not working");
}


int main(){
    //remove("gradebook.txt");
    //remove("math_18.txt");
    //remove("phys_2a.txt");
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
        //fptr = fopen("gradebook.txt", "r");
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
           // printf("You currently have the following %d classes in the gradebook. To view your grades for the first class displayed, press 1, to view your grades for the second class displayed above, press 2, etc. \n\n", classNum);
            printf("You currently have the following %d classes enterred in the gradebook.\n\n", classNum);
            fclose(fptr);
            fptr = fopen("gradebook.txt", "r");
            while( fgets(line, sizeof(line), fptr) ){
                printf("%s" , line);
            }
            printf("\nTo view your grades for the first class displayed, press 1, to view your grades for the second class displayed above, press 2, etc. \n\n");
            
            
            int flag = 0;
            while(!flag){
                scanf("%d", &input);
                for(int i = 0; i < classNum; i++){
                    if(classes[i].pos == input && !flag){
                        flag = 1;
                        //fclose(fptr);
                        classMenu(input, classes);
                        break;
                    }
                }
                if(!flag){
                    printf("Enter a valid number!\n");
                    //scanf("%d", &input);
                }
            }
            //printf("here2");
            
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
    //printf("here1\n");
    return 0;
    
}

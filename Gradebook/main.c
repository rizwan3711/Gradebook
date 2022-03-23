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
    return answer;
}

void classAdder(FILE *pointer){
    pointer = fopen("gradebook.txt", "a");
    char input[50];
    
    printf("\nPlease enter the name of the class you want to add below, using less than 50 characters for the class name\n");
    
    fgets(input, sizeof(input), stdin);
    
    fgets(input, sizeof(input), stdin);

    int i = 0;
    while(input[i] != '\0'){
        if(input[i] == '\n'){
            input[i] = '\0';
        }
        i++;
    }

    fprintf(pointer, "%s\n", input);

    fclose(pointer);
}

void classDeleter(FILE * pointer){
    pointer = fopen("gradebook.txt", "r");
    FILE * temp = fopen("temp.txt", "w");

    printf("\nTo delete your grades for the first class displayed, press 1, to delete your grades for the second class displayed, press 2, etc. Enter -1 to go back to the class selection menu.\n\n");

    int input;
    char curr;
    int flag = 0;
    int line_number;
    char fileName[54];
    int i = 0;
    scanf("%d", &input);
    while(!flag){
            
        curr = getc(pointer);
        if(curr != EOF){
            line_number = 1;
        }
        while(1){
            if(input != line_number){
                putc(curr, temp);
            }
            else{
                if(curr != '\n'){
                    fileName[i] = curr;
                    i++;
                }
            }
            curr = getc(pointer);
            if(curr == '\n'){
                line_number++;
            }
            if(curr == EOF){
                flag = 1;
                break;
            }
        }
        
        if(!flag){
            printf("Enter a valid number!\n");
            scanf("%d", &input);
            break;
        }
    }

    fclose(pointer);
    fclose(temp);

    pointer = fopen("gradebook.txt", "w");
    temp = fopen("temp.txt", "r");
    curr = getc(temp);
    while(1){
        putc(curr, pointer);
        curr = getc(temp);
        if(curr == EOF){
            flag = 1;
            break;
        }
    }

    fclose(pointer);
    fclose(temp);

    remove("temp.txt");

    //i++;
    //printf("%s", fileName);
    char extension[4] = ".txt";
    for(int j = 0; j < 4; j++){
        fileName[i] = extension[j];
        i++;
    }
    fileName[i] = '\0';
    spaceReplacer(fileName);
    remove(fileName);
}

void classEditor(FILE * pointer){
    pointer = fopen("gradebook.txt", "r");
    char line[256];
    char * classes[10];

    printf("\n\nYou currently have the following classes enterred in the gradebook\n\n");
        
    int counter = 0;
    while( fgets(line, sizeof(line), pointer) ){
        printf("%s" , line);
        classes[counter] = line;
        counter++;
    }
    printf("\n");
        
    fclose(pointer);

    int input;
    printf("Press 1 to add any classes to the gradebook, press 2 to delete any classes, or press 3 to return to the class selection menu\n\n");
    scanf("%d", &input);

    int flag = 0;
    while(!flag){
        if(input == 1){
            classAdder(pointer);
            flag = 1;
        }
        else if(input == 2){
            classDeleter(pointer);
            flag = 1;
        }
        else if(input == 3){
            break;
        }
        if(!flag){
            printf("Please enter a valid input!");
            scanf("%d", &input);
        }
    }

}

double gradeCalculator(FILE * pointer, char * fileName){
    //read each column, and multiply the average of every row except for the first 2 by .1 times the value in the 
    //second row for that column

    fclose(pointer);
    pointer = fopen(fileName, "r");
    char line[256];
    
    //CHECK IF ANY ASSIGNMENTS HAVE BEEN ADDED AND RETURN -1 IF THERE ARE NO ASSIGNMENTS YET   
    int counter = 0;
    while( fgets(line, sizeof(line), pointer) ){
        counter++;
    }
    if(counter < 3){
        return -1.0;
    }

    int cN = catCounter(pointer, fileName);
    fclose(pointer);
    pointer = fopen(fileName, "r");

    //calculating grades by making an array of weights, calculating total points in each cat, and multiplying total by weight
    int ogcounter = counter;
    counter = 0;
    double weights[cN];
    double totals[cN];
    double temp;
    double aN[cN];
    double answer = 0.0;

    for(int i = 0; i < cN; i++){
        totals[i] = 0;
    }
    
    //printf("%d\n\n", ogcounter);
    while( fgets(line, sizeof(line), pointer) && counter < ogcounter-1){
        counter++;
        if(counter == 1){
            for(int i = 0; i < cN; i++){
                fscanf(pointer, "%lf, ", &weights[i]);
            }
        }
        if(counter >= 2){
            for(int i = 0; i < cN; i++){
                fscanf(pointer, "%lf, ", &temp);
                if(temp != -1.000000){
                    //printf("%d: %lf\t%d\n", i, temp, counter);
                    totals[i] += temp;
                    aN[i] += 1.0;
                }
            }
        }
    }
    
    printf("\n");
    for(int i = 0; i < cN; i++){
        if(totals[i] != 0.0){
            answer += (totals[i]/aN[i])*(weights[i]);
            //printf("%d: %lf\n", i, totals[i]);
        }
    }
    
    double grand = 0;
    for(int i = 0; i < cN; i++){
        if(totals[i] != 0.0){
            grand += weights[i];
        }
    }
    answer /= grand;
    
    return answer;

}

void assignmentWriter(FILE * pointer, char * cat, char * fileName){
    printf("\nPlease enter a numerical decimal value for the grade which you received on this assignment, out of 100. If you received a 93 on you assignment, enter, 93.0\n");
    double ans;
    scanf("%lf", &ans);
    char line[50];
    int counter = 0;
    while( fscanf(pointer, "%s", line) == 1 ){
        if(strcmp(line, cat) == 0){
            break;
        }
        counter++;
    }
    //before appending to the file, figure out which category(column), you are adding a value to. To do this, read from the beginning
    //of the file, so you shoudl use a+ when calling fopen with your file pointer. 
    fclose(pointer);
    pointer = fopen(fileName, "a+");

    fprintf(pointer, "\n");
    int c = 0;
    int c2 = 0;

    while(c2 < catCounter(pointer, fileName)){
        fclose(pointer);
        pointer = fopen(fileName, "a+");

        if(counter == c){
            fprintf(pointer, "%f\t", ans);
        }
        else{
            fprintf(pointer, "%f\t", -1.000);
        }
        c++;
        c2++;
    }
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
    
    pointer = fopen(fileName, "r");
    if(pointer == NULL){
        pointer = fopen(fileName, "w");
        printf("\nIt seems you have never enterred information for this class before! Please enter the categories which your grade is broken down into(homework, finals, etc), pressing enter after each entry. Press ` when you are done enterring categories. You may enter up to 10 categories, each one being 50 characters or less.\n\n");
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
        
        while(strcmp(catName, "`") != 0){
            
            strcpy(classes[pos-1].cats[catNum].name, catName);
            
            catNum++; 
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
       
        printf("\nFor each of the categories printed above, enter a number for how much of your grade this category counts for. For example, if you have a final category which accounts for 50%% of your final grade, enter the number 50 for this category\n");
        double dinput = 0.0;
        for(i = 0; i < catNum; i++){
            printf("\n%s: \n\n", classes[pos - 1].cats[i].name);
            scanf("%lf", &dinput);
    
            fprintf(pointer, "%lf\t", dinput);
        }
        
    }
    else{
        printf("\nPress 1 to add any assignments, press 2 to calculate your grade in the class, or press 3 to go back to the class selection menu\n\n");
        int input = 0;
        while(1){
        scanf("%d", &input);
        if(input == 1){
            char line[256];
            fscanf(pointer, "%[^\n]", line);
            printf("\n%s", line);

            printf("\n\nThe categories which you have for this class are displayed above. Enter the category which you would like to enter an assignment for, exactly as it is displayed above.\n");
            char catEntry[50];
            char c = getchar();
            fgets(catEntry, sizeof(catEntry), stdin);
            
            char catEntry2[50];
            sscanf(catEntry, "%[^\t\n]", catEntry2);
            
            fclose(pointer);
            pointer = fopen(fileName, "r");
            while( fscanf(pointer, "%s", line) == 1 ){
               if(strcmp(catEntry2, line) == 0){
                   fclose(pointer);
                   pointer = fopen(fileName, "r");
                   assignmentWriter(pointer, line, fileName);
                   break;
               }
            }
            break;
        }
        else if(input == 2){
            //call main menu function
            double grade = gradeCalculator(pointer, fileName);
            if(grade == -1.0){
                printf("It seems you have never enterred any assignments for this class before! Enter assignments before calculating your grade.");
                printf("\n");
            }
            else{
                printf("Your grade in this class is %0.2lf%c", grade, 37);
                printf("\n");
            }
            break;
        }
        else if(input == 3){
            break;
        }
        else{
            printf("\nPlease enter a valid input!\n\n");
        }

    }

    }
    fclose(pointer);
}


int main(){
    //remove("gradebook.txt");
    //remove("math_18.txt");
    //remove("phys_2a.txt");
    FILE *fptr;
    fptr = fopen("gradebook.txt", "r");
    char line[256];
    int classNum = 0;
    
    if(fptr == NULL){
        printf("Welcome to the gradebook program! Please enter the names of the classes you have taken this quarter!\n\n");
        classWriter(fptr);
    }
    else{
        //give the user the option to either view one of their classes, or edit the list of classes which they currently have
        //printf("It seems you have used this program before! Here are the classes you currently have enterred in the gradebook: \n\n");
        
        int input;

        int validInput = 1;

        
        while(1){

        fptr = fopen("gradebook.txt", "r");
        printf("\nHere are the classes you currently have enterred in the gradebook: \n\n");
        
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

        fclose(fptr);

        printf("Press 1 to view/edit your grades for a class, 2 to edit your list of classes, and 3 to exit the program\n\n");
        scanf("%d", &input);
        if(input == 1){
            validInput = 1;
           // printf("You currently have the following %d classes in the gradebook. To view your grades for the first class displayed, press 1, to view your grades for the second class displayed above, press 2, etc. \n\n", classNum);
            printf("\n\nYou currently have the following %d classes enterred in the gradebook.\n\n", classNum);
            
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
                        classMenu(input, classes);
                        break;
                    }
                }
                if(!flag){
                    printf("Enter a valid number!\n");
                }
            }
            
        }
        else if(input == 2){
            validInput = 1;
            //make sure that, lets say you have a file containing the grades of Math20D with a lot of data on there. when you remove math20d from the gradebook, make sure you are also removing the math20d text file with all the data for that class
            classEditor(fptr);
        }
        else if(input == 3){
            validInput = 1;
            exit(0);
        }
        else{
            printf("Please enter a valid input \n\n");
            validInput = 0;
        }
        
        }

    }
    
    fclose(fptr);
    return 0;
    
}

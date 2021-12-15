//
//  main.c
//  Gradebook
//
//  Created by Rizwan Syed on 10/30/21.
//

#include <stdio.h>
#include <string.h>

// first, we need to accept that 
char** inputCategories(){
    const char *cats[10];
    int i = 0;
    char input[50];
    printf("Enter the categories of your class, pressing enter each category. Press ` when you are done.\n");
    while(input != "`"){
        scanf("%s", &input);
        cats[i] = input;
        i++;
    }
    return *cats;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    char *catgories[10];
    categories = inputCategories();
    return 0;
}

/*
  Spencer Johnson : May 11, 2021
  
  This is the program that corresponds to project 2.2
  This program begins by accepting 3 files from the user and storing them using the new knowledge of pointers 
  Two of the files are related through the pointers used to store the information. The third file is for the. venues. With the information that is obtained from the files we can display the various names for all of a category. Using other elements within our structure we can do a calculation if requested by the user. 
  The program terminates upon user entering 4 at main menu 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  the following structures were given in the instructions 
  We will call each respective structure when we scan the file entered 
  by the user in the first 3 inputs from the user 
*/
typedef struct {
  char name[50];
  int age;
} Musician;

typedef struct {
  char name[50];
  int fame;
  int num_musicians;
  Musician *musicians;
} Band;

typedef struct {
  char name[50];
  int capacity;
} Venue;

/*
  this is where i analyze the band file given by the user
    I noticed early that reading the total bands as the first variable
    was interesting. But thinking i quickly realized that i could
    utilize this to allocate the memory for the main pointer band. This
    will also be found in the for loop that scans just the right amount
    of bands in the file 
      i initially had problems when I was obtaining my information 
      because i was using the  while(!feof) but critical thinking 
      assisted me in obtaining the correct information
    i use an initial malloc to prepare my initial pointer for the inputs
    i malloc for the number of musicians here as well
*/
int analyzebands (Band** band){

  int totbands = 0; 
  char userinputbands[20];
  FILE* filebands = NULL; 
  char trash;

  printf("\t- Bands: ");
  scanf("%s", userinputbands);
  filebands = fopen(userinputbands, "r");
      
  if(NULL == filebands){
    printf("ERROR: Can't open file '%s'\n", userinputbands);
  }else{
    fscanf(filebands, "%d", &totbands);
    //scan the \n
    fscanf(filebands, "%c", &trash);
    
    *band = (Band*)malloc(totbands * sizeof(Band));
    
    for(int j = 0; j < totbands; j++){
      //name 
      fgets(((*band)+j)->name, 50, filebands);
      ((*band)+j)->name[strlen(((*band)+j)->name)-1] = '\0';
      //fame
      fscanf(filebands, "%d", &((*band)+j)->fame);
      //number musicians
      fscanf(filebands, "%d", &((*band)+j)->num_musicians);

      fscanf(filebands, "%c", &trash);

      ((*band)+j)->musicians = (Musician*)malloc(((*band)+j)->num_musicians * sizeof(Musician)); 
    }
    fclose(filebands);
  }
  return totbands;
}

/*
  To analyze this file was interesting at first
  as I was not sure how to alloc the memory 
  
  I utilize a temporary variable that Will obtain a set of information from the file and will continue to do this for the whole file witha for loop from the first scanned musicians 
  With this information from the file I will determine what band I am in and input information 
*/


int analyzemusicians (Band** band, int totbands){
  int checker = 0; 
  int totmusicians = 0; 
  char userinputmusicians[20];
  FILE* filemusicians = NULL; 
  char bandcheck[50];
  char tmpname[50];
  char trash;
  int bandcounter[totbands];
  
  /*
  bro i forgot what exactly i did in the estudy 
  
  for(int k = 0; k < ; k++){
    bandcounter[k] = 0; 
  }
  */

  do{
    printf("\t- Musicians: ");
    scanf("%s", userinputmusicians);
    filemusicians = fopen(userinputmusicians, "r");
    
    if(NULL == filemusicians){
      printf("ERROR: Can't open file '%s'\n", userinputmusicians);
      checker = 0; 
    }
    else{
      checker = 1;
      fscanf(filemusicians, "%d", &totmusicians);
      //scan the \n
      fscanf(filemusicians, "%c", &trash);
      for(int i = 0; i < totmusicians; i++){
        
        //this is where i extract the information from the file 
        //temporary variable 
        Musician tmpmusician;
        //name
        fgets(tmpname, 50, filemusicians);
        //format
        tmpname[strlen(tmpname)-1] = '\0';
        
        //printf("\n-%s-why not work?\n", tmpname);
        //tmpmusician = malloc(strlen(tmpname)*sizeof(char));
        
        strcpy(tmpmusician.name,tmpname);
        //name band 
        fgets(bandcheck, 50, filemusicians);
        //format
        (bandcheck[strlen(bandcheck)-1])= '\0';
        fscanf(filemusicians, "%d", &(tmpmusician.age));
        fscanf(filemusicians, "%c", &trash);
        for(int j = 0; j < totbands; j++){
          if(0 == strcmp(bandcheck, ((*band)+j)->name)){
            //((*band)+j)->musicians[]
            strcpy(((*band)+j)->musicians[bandcounter[j]].name,tmpname);
            ((*band)+j)->musicians[bandcounter[j]].age = tmpmusician.age;
            //printf("%s plz work%d", ((*band)+j)->musicians[bandcounter[j]].name, ((*band)+j)->musicians[bandcounter[j]].age);
            bandcounter[j]++;
          }
        }
      }
      fclose(filemusicians);
    }
  }while(!checker);
  return totmusicians;
}

/*
  To analyze the venues was quite easy and seemed to be a repeat of the 
  bands for the most part
    1. I return the total venues in the file for use in later aspects
    2. Memory is allocate\d for the venues 
*/

int analyzevenues (Venue** venue){

  int totvenues = 0; 
  char userinputvenues[20];
  FILE* filevenues = NULL; 
  char trash;
  
  printf("\t- Venues: ");
  scanf("%s", userinputvenues);
  filevenues = fopen(userinputvenues, "r");
  if(NULL == filevenues){
    printf("ERROR: Can't open file '%s'\n", userinputvenues);
  }
  else{
    fscanf(filevenues, "%d", &totvenues);
    //scan the \n
    fscanf(filevenues, "%c", &trash);
    *venue = (Venue*)malloc(totvenues * sizeof(Venue));
    for(int j = 0; j < totvenues; j++){
      //name 
      fgets(((*venue)+j)->name, 50 ,filevenues);
      ((*venue)+j)->name[strlen(((*venue)+j)->name)-1] = '\0';
      fscanf(filevenues, "%d", &((*venue)+j)->capacity);
      fscanf(filevenues, "%c", &trash);
     }
    fclose(filevenues);
    }
    return totvenues;
}


/*
  This is for the first option for the user. we will print the bands or venues depending on what the user wants. 
      1. since i have used the file scans and runctions that return the total amount of venues and bands in the files I use them here to print the name in the respected for loops 

      2. then use them as the value to stay beneath and print what user wants 
*/
void showbandsvenues(int totbands, int totvenues, Band** band, Venue** venue){
  int userpick;
  int i = 0; 
  int flag = 0;
  
  do{
    printf("\n1. Show bands | 2. Show venues\n");
    printf("Select option: ");
    scanf("%d", &userpick);
    if(userpick == 1){
      flag = 1;
      printf("\nBands:\n");
      for(i = 0; i < totbands; i++){
        printf("\t%d - ", i+1);
        printf("%s\n", ((*band)+i)->name);
      }
    }else{
      if(userpick == 2){
        flag = 1;
        printf("\nVenues:\n");
        for(i = 0; i < totvenues; i++){
          printf("\t%d - ", i+1);
          printf("%s\n", ((*venue)+i)->name);
        }
      }else{
        printf("ERROR: Wrong option number\n");
      }
    }
  }while(!flag);
}

/*
  The second option for the user was to calculate ticket price 
    Scan a band number (check parameters)
    Scan a venue number (^)
      I then access these values and calc
    This value was then used to print the price at that specific venue 
*/

void tixprice (int totbands, int totvenues, Venue** venue, Band** band){
  
  int userbandnum = 0; 
  int uservennum = 0;
  float mintix = 0; 
  int flagband = 0; 
  int flagven = 0;
  
  do{
    printf("\nSelect band number: ");
    scanf("%d", &userbandnum);
    if(userbandnum < 1 || userbandnum > totbands){
      printf("ERROR: Invalid band number\n");
      flagband = 0; 
    }else{
      flagband = 1; 
      do{
        printf("\nSelect venue number: ");
        scanf("%d", &uservennum);
        if(uservennum < 1 || uservennum > totvenues){
          printf("ERROR: Invalid venue number\n");
          flagven = 0; 
        }else{
          flagven = 1;
          //this is where i do my equation to solve for the ticket 
          mintix = ((float)((*band)+(userbandnum - 1))->fame) / ((float)((*venue)+(uservennum - 1))->capacity);
          printf("\nThe minimum ticket price is %0.2f euros\n", mintix);
          
        }
      }while(!flagven);
    }
  }while(!flagband);
}

/*
  Option 3: Show band members 
  
  
*/
void showmemb(int totbands, int totmusicians, Band ** band){
  
  int userbandnum = 0; 
  int flag; 
  int i;
  
  do{
    flag = 0;
    userbandnum = 0;
    printf("\nSelect band number: ");
    scanf("%d", &userbandnum);
    
    if(userbandnum > 0 && userbandnum <= totbands){
      printf("\nMembers:\n");
      
      for(i = 0; i < (((*band)+userbandnum-1)->num_musicians); i++){
        printf("\t- %s\n", ((*band)+(userbandnum-1))->musicians[i].name);
        flag = 1;
      }
    }else{
      printf("ERROR: Invalid band number\n");
      flag = 0;
    }
    
  }while(!flag);
}

void mainmenu(){
  printf("\n1. Show bands or venues | ");
  printf("2. Calculate ticket price | ");
  printf("3. Show band members | 4. Exit\n");
  printf("Select option: ");
}

/*
  Here is where i will release all the memory that has been 
  allocated for my pointers 
    I will have to cycle through all of my bands i have created 
      to do this i use a for loop 
    the if statement is to make sure that memory has actually be allocated and file already been read
    
    and my original one that was created for the initial pointer *band
    by ensuring i have read the venue file i also free the pointer i used there; 
*/

void releasepokemon(int totbands, int totmusicians, int totvenues, Band** band, Venue** venue){
  
  
 // if(totbands != 0 && totmusicians != 0){
    for(int j = 0; j < totbands; j++){
      free(((*band)+j)->musicians);
    }
    free(*band);
  //}
  //if(totvenues != 0){
    free(*venue);
  //}
}

int main() {
  
  int totbands;
  int totvenues;
  int totmusicians;
  int menuopt = 0; 
  Band* band;
  Venue* venue;
  
  printf("Welcome!\n\n");
  printf("Introduce the file names:\n");
  
  do{
    totbands = analyzebands(&band); 
  }while(totbands == 0);
  
 do{
    //totmusicians = analyzemusicians(&band, musician, totbands);
    totmusicians = analyzemusicians(&band, totbands); 
  }while(totmusicians == 0);
  
  do{
    totvenues = analyzevenues(&venue); 
  }while(totvenues == 0);
  
  do{
    mainmenu();
    scanf("%d", &menuopt);
    
    if(menuopt > 4 || menuopt < 1){
      printf("ERROR: Wrong option number\n");
    }
    
    switch(menuopt){
      case 1:
        showbandsvenues(totbands, totvenues, &band, &venue);
        break; 
        
      case 2:
        tixprice(totbands, totvenues, &venue, &band);
        break;
        
      case 3:
        showmemb(totbands, totmusicians, &band);
        break;
    }
  }while(menuopt != 4);
  printf("\nBye!");
  
  releasepokemon(totbands, totmusicians, totvenues, &band, &venue);

  
    return 0;
}
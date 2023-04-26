/*
  Spencer Johnson : May 9, 2021
  Project 2.3 Programming M and T 

    The purpose of this program is to take the information from 3 different files. From the first two files i store the information with pointers. The last file, for the venues  I store using queues. 
      With this information i have stored above i call to a main menu for the user and the user can do different tasks with the information i have stored in the three files. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
//#include "queue.c"
//#include "mine.h"
//#include "mine.c"

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
  
  for(int k = 0; k < totbands; k++){
      bandcounter[k] = 0; 
  }

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
        
        strcpy(tmpmusician.name,tmpname);
        //name band 
        fgets(bandcheck, 50, filemusicians);
        //format
        (bandcheck[strlen(bandcheck)-1])= '\0';
        fscanf(filemusicians, "%d", &(tmpmusician.age));
        fscanf(filemusicians, "%c", &trash);
        for(int j = 0; j < totbands; j++){
          if(0 == strcmp(bandcheck, ((*band)+j)->name)){
            strcpy(((*band)+j)->musicians[bandcounter[j]].name,tmpname);
            ((*band)+j)->musicians[bandcounter[j]].age = tmpmusician.age;
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
  In this function  
    I will add my obtained info to the queue 
    1. I return the total venues in the file for use in later aspects
    2. to extract the information from the file was quite routine and the same thing from other projects 

*/

int analyzevenues (Queue *venueq){

  int totvenues = 0; 
  char userinputvenues[20];
  FILE* filevenues = NULL; 
  char trash;
  Element element; 
  
  printf("\t- Venues: ");
  scanf("%s", userinputvenues);
  filevenues = fopen(userinputvenues, "r");
  if(NULL == filevenues){
    printf("ERROR: Can't open file '%s'\n", userinputvenues);
  }
  else{
    
    //name and pre reading 
    fgets(element.name, 50 ,filevenues);
    //format
    (element.name[strlen(element.name)-1]) = '\0';
 
    while(!feof(filevenues)){
      //scan the capacity and then the \n 
      fscanf(filevenues, "%d", &element.capacity);
      //printf("%d", element.capacity);
      fscanf(filevenues, "%c", &trash);
      
      QUEUE_add(venueq,element);

      //to know how many venues we have scanned
      totvenues++; 

      //name again 
      fgets(element.name, 50 ,filevenues);
      //format
      (element.name[strlen(element.name)-1]) = '\0';
    }
    
    fclose(filevenues);
  }
  return totvenues;
}


/*
  i create a temp element and set the first value of my queue to my new temp Element
  i use a for loop to cycle through all the venes 
  then i print the element i have grabbed 
  then i add the element already printed to the bottom of the queue 
  because i have the tot number of venues when i am done printing the queue will be normal cause i go through ALL of them 
  
*/

void showVen(Queue * venueq, int totvenues){
  Element el;
  //print the info 
  for(int i = 0; i < totvenues; i++){
    
    el = QUEUE_getFirst(venueq);
    QUEUE_remove(venueq);
    printf("\t%d - %s\n", i+1, el.name);
    QUEUE_add(venueq, el);
  }
}



/*
  This is for the first option for the user. we will print the bands or venues depending on what the user wants. 
      1. since i have used the file scans and runctions that return the total amount of venues and bands in the files I use them here to print the name in the respected for loops 

      2. then use them as the value to stay beneath and print what user wants 
      
      the updated method to print the venues is found in the abouve procedure 
*/
void showbandsvenues(int totbands, int totvenues, Band** band, Queue venueq){
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
        showVen(&venueq, totvenues); 
      }else{
        printf("ERROR: Wrong option number\n");
      }
    }
  }while(!flag);
}


/*
  1. here i create a variable for a tmp Element and use the function below to return the capacity for the user entered or desired venue 
  2. using a for loop i cycle through the venues and i see if the number of venues i have gone through matches the desired
  3. set me Element equal to the top of the queue 
  4. if it is the venue we want i get the capacity and return it
  
*/
int venQtix(int uservennum, Queue * venueq, int totvenues){
  
  Element el;
  int cap = 0;
  int i = 0; 
  el.capacity = 0;
  for(i = 0; i < totvenues; i++){
    el = QUEUE_getFirst(venueq);
    if((uservennum-1) == i){
      cap = el.capacity;
    }
    QUEUE_add(venueq, el);
    QUEUE_remove(venueq);
  }
  return cap;
}


/*
  The second option for the user was to calculate ticket price 
    Scan a band number (check parameters)
    Scan a venue number (^)
      I then access these values and calc
    This value was then used to print the price at that specific venue 
*/

void tixprice (int totbands, int totvenues, Queue * venueq, Band** band){
  
  int userbandnum = 0; 
  int uservennum = 0;
  float mintix = 0; 
  int flagband = 0; 
  int flagven = 0;
  int cap = 0; 

  
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
          cap = venQtix(uservennum, venueq, totvenues); 
          //printf("%d", cap);
          mintix = ((float)((*band)+(userbandnum - 1))->fame) / ((float)(cap));
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

void releasepokemon(int totbands, int totmusicians, Band** band){
  
  for(int j = 0; j < totbands; j++){
    free(((*band)+j)->musicians);
  }
  free(*band);

  //removed the free for the venues pointer 
}

/*
  we know the the destroy function from the queue.c file cycles through all the queue and frees the mem and eliminates all the nodes and elements so we utilize that here 
*/
void releaseQueue(Queue * venueq){
  
  QUEUE_destroy(venueq); 
}



int main() {
  
  int totbands;
  int totvenues;
  int totmusicians;
  int menuopt = 0; 
  Band* band;
  Queue venueq;
  
  // i will create my queue here
    venueq = QUEUE_create ();
  
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
    totvenues = analyzevenues(&venueq); 
  }while(totvenues == 0);
  
  do{
    mainmenu();
    scanf("%d", &menuopt);
    
    if(menuopt > 4 || menuopt < 1){
      printf("ERROR: Wrong option number\n");
    }
    
    switch(menuopt){
      case 1:
        showbandsvenues(totbands, totvenues, &band, venueq);
        break; 
        
      case 2:
        tixprice(totbands, totvenues, &venueq, &band);
        break;
        
      case 3:
        showmemb(totbands, totmusicians, &band);
        break;
    }
  }while(menuopt != 4);
  printf("\nBye!");
  
  releasepokemon(totbands, totmusicians, &band);
  //releaseQueue(&venueq); 
  QUEUE_destroy(&venueq);

  
    return 0;
}
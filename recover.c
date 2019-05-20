/**  
   recover.c
   
   Computer Science 50
   Problem Set 4
   
   Recovers JPEGs from a forensic image.
**/
 
// By Oladosu Ayobami
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
// pre definition of functions
int filecheck(FILE* filepointer);
 
// output file pointer
FILE * outptr;
 
int main(void)
{
    // Opening of card image file
    FILE* filepointer = fopen("card.raw", "r");
    filecheck(filepointer);    
     
    // initializing some useful variables and space
    int count = 0;
    unsigned char buffer[512];
    int times = 0;
     
    // forever loop that only stops when card end is reached 
    while (times == 0 && !feof(filepointer))
    {
        fread(buffer, 512, 1, filepointer);
        if ((buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255) && 
        (buffer[3] == 225 || buffer[3] == 224))
        {
            break;
        }       
    }  
    while (times == 0)                
    {    
        // array to store title  
        char title[8];
        // creates a filename    
        sprintf(title, "%.3d.jpg", count);
         
        // opens a new jpeg
        outptr = fopen(title, "w");
        filecheck(outptr);
         
        // Yet another forever loop
        do
        {
            // the writing and reading starts
            fwrite(buffer, 512, 1, outptr);
            fread(buffer, 512, 1, filepointer);
             
            // checks for a new jpeg
            if ((feof(filepointer)) || ((buffer[0] == 255 && buffer[1] == 216
            && buffer[2] == 255) && (buffer[3] == 225 || buffer[3] == 224)))
            {
                break;
            }        
        }    
        while (times == 0); 
         
        // keeps count
        count++;
        // closes currently opened jpeg
        fclose(outptr);
         
        // checks for end of file
        if (feof(filepointer))
        {
            break;            
        }
    }
    // closes card
    fclose(filepointer);
    return 0;
    // That's all folks!
}
 
// definition of function
int filecheck(FILE* filepointer)
{
    // checks if file pointer is NULL
    if (filepointer == NULL)
    {
        printf("could not open file\n");
        return 2;
    }
    else
    {
        return 0;
    }
}

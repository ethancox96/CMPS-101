//Ethan Cox
//etecox
//pa2
//Lex.c
//Lexicographically sorts the input file

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){

   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];

   //check command line for correct number of arguments
   if (argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   //open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if (in == NULL){
      printf("Unable to open file %s for reading]n", argv[1]);
      exit(1);
   }
   if (out == NULL){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   char list[60][60];
   while( fgets(line, MAX_LEN, in) != NULL){
      strcpy(list[count++], line);
   }
   
   List A = newList();
   for (int i = 0; i < count; i++){
      append(A, i);
   }

   List B = newList();
   for (moveFront(A); index(A) >= 0; moveNext(A)){
      int key = get(A);
      if (length(B) == 0)
	 prepend(B, key);
      else{
	 moveFront(B);
	 char* s1 = list[key];
	 char* s2 = list[get(B)];
	 while(strcmp(s1, s2) >= 0 && index(B) >= 0){
	    moveNext(B);
	    if (index(B) != -1){
	       s2 = list[get(B)];
	    }
	 }
	 if (index(B) == -1)
	    append(B, key);
	 else
	    insertBefore(B, key);
      }
   }

   printList(out, B);
   fclose(in);
   fclose(out);
   return(0);
}








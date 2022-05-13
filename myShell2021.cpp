#include <iostream>
#include <cstring>   // prototype for strtok
#include <unistd.h>
#include <string>
#include <sys/wait.h>
using namespace std;

int main() {
while (true){
   char command[100];
   
   std::cin.getline (command, 100);
   int tok_count = 0;
   if (command[0] == 'e' && command[1] == 'x' && command[2] == 'i' && command[3] == 't'){ break;}
   
   
   if (fork() == 0){
      char* curr_token;
      int filedesc[2];
      filedesc[0] = 0;
      int first = 0;

      while (true){
         
         if (first == 0){
            curr_token = strtok(command, "|"); first = 1;
         }
         else{ 
            curr_token = strtok(NULL, "|");
         } 
         close (filedesc[1]);
         int pipeinput = filedesc[0];
         pipe(filedesc);
         
         if (curr_token == NULL){
            dup2(pipeinput, 0);
            char fin [4] = "cat";
            char* fin1[] = {fin, nullptr};
            execvp (fin1[0], fin1);
            close (filedesc[1]);
            close (pipeinput);
            close (filedesc[0]);
            exit(0);
         }

         int child_pid = fork();
         if (child_pid > 0){
            char* temp1[50];
            for (int i = 0; i < 50; i++){temp1[i] = nullptr;}
            int tok_count1 = 0;
            temp1[tok_count1] = strtok(curr_token, " ");
            while (temp1[tok_count1] != NULL) {

               tok_count1++;
               temp1[tok_count1] = strtok(NULL, " ");
               
            }
            
            dup2(filedesc[1], 1);
            dup2(pipeinput, 0);
            execvp (temp1[0], temp1);
            close (filedesc[1]);
            close (pipeinput);
            close (filedesc[0]);
            wait (&child_pid);
            exit(0);
         }
      } 
   } 
}
}

            
      
      

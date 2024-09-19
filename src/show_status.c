#include<stdio.h>
#include<stdlib.h>
#include"show_status.h"
void show_status() { 
 FILE *index_file = fopen(".git/index", "r"); 
 if (!index_file) { 
 printf("No files in the staging area.\n");  return; 
 } 
 
 char buffer[256]; 
 printf("Staged files:\n"); 
 while (fgets(buffer, sizeof(buffer), index_file)) { 
 printf("%s", buffer); 
 } 
 
 fclose(index_file); 
} 
void show_log(){ 
 FILE *log_file = fopen(".git/logs", "r"); 
 if (!log_file) { 
 printf("No commits found.\n"); 
 return; 
 } 
 
 char line[256];
    while (fgets(line, sizeof(line), log_file)) {
        printf("%s", line);
    }
 
 fclose(log_file); 
} 

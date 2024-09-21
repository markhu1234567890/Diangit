#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include"branch.h"
#include"commit.h"

void create_branch(const char *branch_name, const char *commit_hash) { 
 char check_path[256]; 
 sprintf(check_path, ".git/objects/%c%c/%s", commit_hash[0], commit_hash[1], commit_hash + 2); 
 FILE *check_file = fopen(check_path, "rb");
 if (!check_file) {
        printf("Cannot find commit file: %s\n", check_path);
        return ;
  }
  fclose(check_file); 
 char path[256]; 
 sprintf(path, ".git/refs/heads/%s", branch_name); 
 
 FILE *file = fopen(path, "w"); 
 if (!file) { 
 printf("Failed to create branch: %s\n", branch_name); 
 return; 
 } 
 
 fprintf(file, "%s\n", commit_hash);  
 fclose(file); 
 char up_message[256];
 sprintf(up_message,"Branch '%s' created pointing to commit %s.", branch_name, commit_hash); 
 printf("%s\n",up_message);
 update(1,(unsigned char*)commit_hash,up_message);//1表示commit
    
} 
void list_branches(){
    DIR* dir = opendir(".git/refs/heads");
    if (!dir) {
        perror("Error opening branches directory");
        return;
    }
    struct dirent* entry;
    printf("Branches:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("  %s\n", entry->d_name);
        }
    }
    closedir(dir);
}

void delete_branch(const char *branch_name) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", ".git/refs/heads", branch_name);
    if (remove(path) == 0) {
        printf("Branch '%s' deleted.\n", branch_name);
    }else{
         printf("Failed to delete branch");
    }
    
}


void rename_branch(const char *old_name, const char *new_name) {
    char old_path[256], new_path[256];
    snprintf(old_path, sizeof(old_path), "%s/%s", ".git/refs/heads", old_name);
    snprintf(new_path, sizeof(new_path), "%s/%s", ".git/refs/heads", new_name);
    
    if (rename(old_path, new_path) != 0) {
        perror("Error renaming branch");
        return;
    }
    printf("Branch '%s' renamed to '%s'.\n", old_name, new_name);
}

void update_branch(const char *branch_name, const char *new_commit_hash) {
    char check_path[256];
    snprintf(check_path, sizeof(check_path), "%s/%c%c/%s", ".git/objects", new_commit_hash[0], new_commit_hash[1], new_commit_hash + 2);

    FILE *check_file = fopen(check_path, "rb");
    if (!check_file) {
        printf("Cannot find commit file: %s\n", check_path);
        return;
    }
    fclose(check_file);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", ".git/refs/heads", branch_name);

    FILE *file = fopen(path, "w");
    if (!file) {
        perror("Failed to update branch");
        return;
    }

    fprintf(file, "%s\n", new_commit_hash);
    fclose(file);

    printf("Branch '%s' updated to commit %s.\n", branch_name, new_commit_hash);
}


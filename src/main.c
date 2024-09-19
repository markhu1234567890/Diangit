#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"init_repository.h"
#include"commit.h"
#include"checkout.h"
#include"create_branch.h"
#include"create_tag.h"
#include"add_file.h"
#include"show_status.h"

#define HASH_LENGTH 32
#define CHUNK_SIZE 1024
#define PATH_SIZE 512


/*

int main(int argc, char *argv[]) {
printf("%d\n",argc);
for(int i=0;i<argc;i++){
printf("%s ",argv[i]);
}


 if (argc < 2) { 
 printf("Usage: diangit <command> [options]\n"); 
 return 1; 
 } 
 if (strcmp(argv[1], "init") == 0) { 
 init_repository(argc > 2 ? argv[2] : "."); 
 } 
 
 else if (strcmp(argv[1], "hash-object") == 0) {

 unsigned char hash[HASH_LENGTH];
 if (hash_object(argv[2], hash)) {
 printf("Hash: ");
 for (int i = 0; i < HASH_LENGTH; ++i) {
 printf("%02x", hash[i]);
 }
 printf("\n");

 
 } else {
 fprintf(stderr, "Failed to hash object\n");
 }
 } else if (strcmp(argv[1], "cat-file") == 0) {

  cat_file(argv[2]);
}

  else if (strcmp(argv[1], "add") == 0) { 
 add_file(argv[2]); 
 } 

 else if (strcmp(argv[1], "commit") == 0) { 
 commit(argv[2]); 
 } 
 //------------------------------------------------------
 else if (strcmp(argv[1], "checkout") == 0) { 
 checkout(argv[2]); 
 } 
 else if (strcmp(argv[1], "ls-tree") == 0) { 
 print_tree(argv[2]); 
 } 
 
 else if (strcmp(argv[1], "branch") == 0) { 
 create_branch(argv[2], argv[3]); 
 } 
 
 else if (strcmp(argv[1], "tag") == 0) { 
 create_tag(argv[2], argv[3]); 
 } 
 else if (strcmp(argv[1], "show-branches") == 0) { 
 list_branches();
 } 
 else if (strcmp(argv[1], "show-tags") == 0) { 
 list_tags();
 } 
 else if (strcmp(argv[1], "delete-branch") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s delete-branch <branch_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        delete_branch(argv[2]);
    } else if (strcmp(argv[1], "delete-tag") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s delete-tag <tag_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        delete_tag(argv[2]);
    } else if (strcmp(argv[1], "rename-branch") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s rename-branch <old_name> <new_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        rename_branch(argv[2], argv[3]);
    } else if (strcmp(argv[1], "rename-tag") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s rename-tag <old_name> <new_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        rename_tag(argv[2], argv[3]);
    } else if (strcmp(argv[1], "update-branch") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s update-branch <branch_name> <new_commit_hash>\n", argv[0]);
            return EXIT_FAILURE;
        }
        update_branch(argv[2], argv[3]);
    } else if (strcmp(argv[1], "update-tag") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s update-tag <tag_name> <new_commit_hash>\n", argv[0]);
            return EXIT_FAILURE;
        }
        update_tag(argv[2], argv[3]);
    } 
 //-----------------------------------------------------
 else if (strcmp(argv[1], "status") == 0) { 
 show_status(); 
 } 
 
 else if (strcmp(argv[1], "log") == 0) { 
 show_log();  
 } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
 
 return 0; 
} */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: diangit <command> [options]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) {
        init_repository(argc > 2 ? argv[2] : ".");
    } else if (strcmp(argv[1], "hash-object") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s hash-object <file>\n", argv[0]);
            return 1;
        }
        unsigned char hash[HASH_LENGTH];
        if (hash_object(argv[2], hash)) {
            printf("Hash: ");
            for (int i = 0; i < HASH_LENGTH; ++i) {
                printf("%02x", hash[i]);
            }
            printf("\n");
        } else {
            fprintf(stderr, "Failed to hash object\n");
        }
    } else if (strcmp(argv[1], "cat-file") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s cat-file <file>\n", argv[0]);
            return 1;
        }
        cat_file(argv[2]);
    } else if (strcmp(argv[1], "add") == 0) { 
 add_file(argv[2]); 
 } 

 else if (strcmp(argv[1], "commit") == 0) { 
 commit(argv[2]); 
 } 
 //------------------------------------------------------
   else if (strcmp(argv[1], "checkout") == 0) {
      if (argc != 3) {
	  fprintf(stderr, "Usage: %s checkout <commit_hash>\n", argv[0]);
	  return EXIT_FAILURE;
      }
      checkout(argv[2]);
  } 
  else if (strcmp(argv[1], "ls-tree") == 0) {
      if (argc != 3) {
	  fprintf(stderr, "Usage: %s ls-tree <tree_hash>\n", argv[0]);
	  return EXIT_FAILURE;
      }
      print_tree(argv[2]);
  } 
  else if (strcmp(argv[1], "branch") == 0) {
      if (argc != 4) {
	  fprintf(stderr, "Usage: %s branch <branch_name> <commit_hash>\n", argv[0]);
	  return EXIT_FAILURE;
      }
      create_branch(argv[2], argv[3]);
  }
   else if (strcmp(argv[1], "tag") == 0) {
     if (argc != 4) {
	  fprintf(stderr, "Usage: %s tag <tag_name> <commit_hash>\n", argv[0]);
	  return EXIT_FAILURE;
      }
      create_tag(argv[2], argv[3]);
  }
   else if (strcmp(argv[1], "show-branches") == 0) {
      if (argc != 2) {
	  fprintf(stderr, "Usage: %s show-branches\n", argv[0]);
	  return EXIT_FAILURE;
      }
      list_branches();
  } else if (strcmp(argv[1], "show-tags") == 0) {
      if (argc != 2) {
	  fprintf(stderr, "Usage: %s show-tags\n", argv[0]);
	  return EXIT_FAILURE;
       }
       list_tags();
   }
   else if (strcmp(argv[1], "delete-branch") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s delete-branch <branch_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        delete_branch(argv[2]);
    } 
    else if (strcmp(argv[1], "delete-tag") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s delete-tag <tag_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        delete_tag(argv[2]);
    }
     else if (strcmp(argv[1], "rename-branch") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s rename-branch <old_name> <new_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        rename_branch(argv[2], argv[3]);
    } 
    else if (strcmp(argv[1], "rename-tag") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s rename-tag <old_name> <new_name>\n", argv[0]);
            return EXIT_FAILURE;
        }
        rename_tag(argv[2], argv[3]);
    } 
    else if (strcmp(argv[1], "update-branch") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s update-branch <branch_name> <new_commit_hash>\n", argv[0]);
            return EXIT_FAILURE;
        }
        update_branch(argv[2], argv[3]);
    } 
    else if (strcmp(argv[1], "update-tag") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s update-tag <tag_name> <new_commit_hash>\n", argv[0]);
            return EXIT_FAILURE;
        }
        update_tag(argv[2], argv[3]);
    } 
 //-----------------------------------------------------
 else if (strcmp(argv[1], "status") == 0) { 
 show_status(); 
 } 
 
 else if (strcmp(argv[1], "log") == 0) { 
 show_log();  
 }
    

    else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}



















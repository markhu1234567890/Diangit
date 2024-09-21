#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"init_repository.h"
#include"commit.h"
#include"checkout.h"
#include"branch.h"
#include"tag.h"
#include"add_file.h"
#include"show_status.h"
#include"ignore.h"

#define HASH_LENGTH 32
#define O 0



int main(int argc, char *argv[]) {
    if (argc < 2+O) {
        fprintf(stderr, "Usage: diangit <command> [options]\n");
        return 1;
    }
    
    int f=(argc <2+O ? 0 : (strcmp(argv[1+O], "init") == 0) ? 1 :
                     (strcmp(argv[1+O], "hash-object") == 0) ? 2 :
                     (strcmp(argv[1+O], "cat-file") == 0) ? 3 :
                     (strcmp(argv[1+O], "add") == 0) ? 4 :
                     (strcmp(argv[1+O], "commit") == 0) ? 5 :
                     (strcmp(argv[1+O], "checkout") == 0) ? 6 :
                     (strcmp(argv[1+O], "ls-tree") == 0) ? 7 :
                     (strcmp(argv[1+O], "branch") == 0) ? 8 :
                     (strcmp(argv[1+O], "tag") == 0) ? 9 :
                     (strcmp(argv[1+O], "show-branches") == 0) ? 10 :
                     (strcmp(argv[1+O], "show-tags") == 0) ? 11 :
                     (strcmp(argv[1+O], "delete-branch") == 0) ? 12 :
                     (strcmp(argv[1+O], "delete-tag") == 0) ? 13 :
                     (strcmp(argv[1+O], "rename-branch") == 0) ? 14 :
                     (strcmp(argv[1+O], "rename-tag") == 0) ? 15 :
                     (strcmp(argv[1+O], "update-branch") == 0) ? 16 :
                     (strcmp(argv[1+O], "update-tag") == 0) ? 17 :
                     (strcmp(argv[1+O], "status") == 0) ? 18 :
                     (strcmp(argv[1+O], "log") == 0) ? 19 :
                     (strcmp(argv[1+O], "clear-log") == 0) ? 20 :
                     (strcmp(argv[1+O], "rm") == 0) ? 21 :
                     (strcmp(argv[1+O], "ignore") == 0) ? 22 :
                     (strcmp(argv[1+O], "check-ignore") == 0) ? 23 :
                     24);
     printf("-------%d------\n",f);
     int i;
    switch (f) {
        case 1:
            init_repository(argc > 2+O ? argv[2+O] : ".");
            break;
        case 2:
            if (argc < 3+O) {
                fprintf(stderr, "Usage: %s hash-object <file>\n", argv[0]);
                return 1;
            }
            {
                unsigned char hash[HASH_LENGTH];
                if (hash_object(0, argv[2+O], hash)) { // 1表示不生成obj对象 其他表示生成
                    printf("Hash: ");
                    for (int i = 0; i < HASH_LENGTH; ++i) {
                        printf("%02x", hash[i]);
                    }
                    printf("\n");
                } else {
                    fprintf(stderr, "Failed to hash object\n");
                }
            }
            break;
        case 3:
            if (argc < 3+O) {
                fprintf(stderr, "Usage: %s cat-file <file>\n", argv[0]);
                return 1;
            }
            cat_file(argv[2+O]);
            break;
        case 4:
            i=2+O;
            while(argv[i]!=NULL){
                    printf("%s",argv[i]);
		    if(check_ignore(argv[i])==1){
		    printf("%s is been ignored\n",argv[i]);
		    }else{
		    add_file(argv[i]);
		    }
		    i++;
		    
            }
            break;
        case 5:
            i=2+O;
            while(argv[i]!=NULL){
		if(check_ignore(argv[i])==1){
            	printf("%s is been ignored",argv[i]);
           	}else{
            	commit(argv[i]);
           	}
           	i++;
            }
            break;
        case 6:
            if (argc != 3+O) {
                fprintf(stderr, "Usage: %s checkout <commit_hash>\n", argv[0]);
                return EXIT_FAILURE;
            }
            checkout(argv[2+O]);
            break;
        case 7:
            if (argc != 3+O) {
                fprintf(stderr, "Usage: %s ls-tree <tree_hash>\n", argv[0]);
                return EXIT_FAILURE;
            }
            print_tree(argv[2+O]);
            break;
        case 8:
            if (argc != 4+O) {
                fprintf(stderr, "Usage: %s branch <branch_name> <commit_hash>\n", argv[0]);
                return EXIT_FAILURE;
            }
            create_branch(argv[2], argv[3]);
            break;
        case 9:
            if (argc != 4+O) {
                fprintf(stderr, "Usage: %s tag <tag_name> <commit_hash>\n", argv[0]);
                return EXIT_FAILURE;
            }
            create_tag(argv[2+O], argv[3+O]);
            break;
        case 10:
            if (argc != 2+O) {
                fprintf(stderr, "Usage: %s show-branches\n", argv[0]);
                return EXIT_FAILURE;
            }
            list_branches();
            break;
        case 11:
            if (argc != 2+O) {
                fprintf(stderr, "Usage: %s show-tags\n", argv[0]);
                return EXIT_FAILURE;
            }
            list_tags();
            break;
        case 12:
            if (argc != 3+O) {
                fprintf(stderr, "Usage: %s delete-branch <branch_name>\n", argv[0]);
                return EXIT_FAILURE;
            }
            delete_branch(argv[2+O]);
            break;
        case 13:
            if (argc != 3+O) {
                fprintf(stderr, "Usage: %s delete-tag <tag_name>\n", argv[0]);
                return EXIT_FAILURE;
            }
            delete_tag(argv[2+O]);
            break;
        case 14:
            if (argc != 4+O) {
                fprintf(stderr, "Usage: %s rename-branch <old_name> <new_name>\n", argv[0]);
                return EXIT_FAILURE;
            }
            rename_branch(argv[2+O], argv[3+O]);
            break;
        case 15:
            if (argc != 4+O) {
                fprintf(stderr, "Usage: %s rename-tag <old_name> <new_name>\n", argv[0]);
                return EXIT_FAILURE;
            }
            rename_tag(argv[2+O], argv[3+O]);
            break;
        case 16:
            if (argc != 4+O) {
                fprintf(stderr, "Usage: %s update-branch <branch_name> <new_commit_hash>\n", argv[0]);
                return EXIT_FAILURE;
            }
            update_branch(argv[2+O], argv[3+O]);
            break;
        case 17:
            if (argc != 4+O) {
                fprintf(stderr, "Usage: %s update-tag <tag_name> <new_commit_hash>\n", argv[0]);
                return EXIT_FAILURE;
            }
            update_tag(argv[2+O], argv[3+O]);
            break;
        case 18:
            show_status();
            break;
        case 19:
            show_log();
            break;
        case 20:
            clear_log();
            break;
        case 21:
            rm(argv[2+O]);
            break;
        case 22:
            add_to_gitignore(argv[2+O]);
            break;
        case 23:
            if(check_ignore(argv[2+O])==1){
            printf("%s is been ignored",argv[2+O]);
            }else{
            printf("%s is not been ignored",argv[2+O]);
            }
            break;
        default:
            fprintf(stderr, "Unknown command: %s\n", argv[1+O]);
            return 1;
    }

    return 0;
}



















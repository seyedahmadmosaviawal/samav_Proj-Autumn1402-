// In The Name Of God
// samav Project
// Autumn_Winter 1402

// Seyed_Ahmad_Mousavi_Awal
// 402106648

// Address Of Global Thing:
// C:\Users\user\Desktop\c programs\tamrin\project_1402_autumn\global

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define global_thing "C:\\Users\\user\\Desktop\\c programs\\tamrin\\project_1402_autumn\\global"
#define wildcard_path "C:\\Users\\user\\Desktop\\c programs\\tamrin\\project_1402_autumn\\global\\wildcard.txt"

// Check Samav Exists?:
char* samav_exist(int argc, char* argv[]){

    char tmp_cwd[1024];
    char* tmp_cpy = (char*) malloc(1024 * sizeof(char));
    getcwd(tmp_cwd, sizeof(tmp_cwd));
    strcpy(tmp_cpy, tmp_cwd);
    struct dirent *entry;
    do {
        // find samav:
        DIR *dir = opendir(".");
        if (dir == NULL) {
            fprintf(stdout, "SAMAV : An Error Was Founded While Opening The Current Directory");
            free(tmp_cpy);
            return NULL;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".samav") == 0){
                return tmp_cpy;
            }
        }
        closedir(dir);

        // change cwd to parent
        if (strcmp(tmp_cwd, "C:\\") != 0) {
            if (chdir("..") != 0) {fprintf(stdout, "SAMAV : Unknown Error");free(tmp_cpy); return NULL;}
        }

        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) {fprintf(stdout, "SAMAV : Unknown Error"); free(tmp_cpy); return NULL;}
        strcpy(tmp_cpy, tmp_cwd);

    } while (strcmp(tmp_cwd, "C:\\") != 0);
    free(tmp_cpy);
    return NULL;
}

// Write In Global Files:
int global_writter(int argc, char* argv[], int line, char* global, int choose){
    char tmp_cwd[1024];
    getcwd(tmp_cwd, sizeof(tmp_cwd));
    chdir(global_thing);
    FILE* file;
    FILE* file_cpy;
    if(choose == 1){
        file = fopen("config_global.txt", "r");
        file_cpy = fopen("config_global_cpy.txt", "w");  
    }
    else{
        file = fopen("config_local.txt", "r");
        file_cpy = fopen("config_local_cpy.txt", "w");
    }
    char line_reader[1000];
    // Copy File In File:
    while(fgets(line_reader, 1000, file)){
        line--;
        if(line == 0){
            fprintf(file_cpy, global);
            fprintf(file_cpy, "\n");
        }
        else{
            fprintf(file_cpy, line_reader);
        }
    }
    rewind(file);
    rewind(file_cpy);
    fclose(file);
    fclose(file_cpy);
    if(choose == 1){
        file = fopen("config_global.txt", "w");
        file_cpy = fopen("config_global_cpy.txt", "r");
    }
    else{
        file = fopen("config_local.txt", "w");
        file_cpy = fopen("config_local_cpy.txt", "r");
    }
    while(fgets(line_reader, 1000, file_cpy)){
        fprintf(file, line_reader);
    }
    rewind(file);
    rewind(file_cpy);
    fclose(file);
    fclose(file_cpy);

    chdir(tmp_cwd);
    return 0;
}

int Add_to_stage_file_mod(int argc, char* argv[], char * filepath){
    char wildcard[1000] = "dir /b ";
    strcat(wildcard, filepath);
    strcat(wildcard, " >>");
    strcat(wildcard, " wildcard.txt");
    system(wildcard);
    FILE* file_read = fopen("wildcard.txt", "r");
    FILE* file_find = fopen("stage.txt", "r");
    char line_reader[1024];
    char line_wild[1024];
    // MAIN LOOP:
    int exist = 2;
    while(fgets(line_wild, 1024, file_read)){
        line_wild[strlen(line_wild) - 1] = '\0';
        exist = 0;
        if(strcmp(line_wild, "File Not Found") == 0){
            fprintf(stdout, "SAMAV : There Is No File With Specified Address! Please Try Again!");
            fclose(file_find);
            fclose(file_read);
            system("del wildcard.txt");  
            return 1;
        }
        while(fgets(line_reader, 1024, file_find)){
            line_reader[strlen(line_reader) - 1] = '\0';
            if(strcmp(line_reader, line_wild) == 0){
                fprintf(stdout , "SAMAV : File With Address: \'%s\' Exists! Please Use Commit Operation!\n", line_wild);
                exist = 1;
                break;
            }
        }
        if(!exist){
            fclose(file_find);
            file_find = fopen("stage.txt", "a");
            fprintf(file_find,"%s\n" ,line_wild);
            fclose(file_find);
            file_find = fopen("stage.txt", "r");
            fprintf(stdout, "SAMAV : A File With Address: \'%s\' Has Been Added!\n", line_wild);
        }
        rewind(file_find);
    }
    fclose(file_find);
    fclose(file_read);
    system("del wildcard.txt");
    return 0;
}




int main(int argc, char* argv[]){
    // Less Than 2 Inputs:
    if (argc < 2){
        fprintf(stdout, "SAMAV : Please Enter A Valid Command!");
        return 1;
    }

    char Current[1024];
    if(getcwd(Current, sizeof(Current)) == NULL) {fprintf(stdout, "SAMAV : There Is An Unknown Error Please Try Again!"); return 1;}
    char* Samav_Root;
    Samav_Root = samav_exist(argc, argv);
    ///////////////////// Menu: /////////////////////

    // All The samav init:
    if(strcmp(argv[1], "init") == 0){
        if(Samav_Root != NULL){
            fprintf(stdout, "SAMAV : There Is Exists An Initialized Repository At Address:\n%s\\.samav", Samav_Root);
            return 1;
        }
        else{
            chdir(global_thing);
            FILE* file_1 = fopen("config_local.txt", "r");
            FILE* file_2 = fopen("config_global.txt", "r");
            char name_local[100];
            char name_global[100];
            char email_local[100];
            char email_global[100];
            fgets(name_local, 100, file_1);
            fgets(email_local, 100, file_1);
            fgets(name_global, 100, file_2);
            fgets(email_global, 100, file_2);
            fclose(file_1); 
            fclose(file_2);
            if (strncmp(name_local, "name:", 5) == 0 || strncmp(email_local, "email:", 6) == 0){
                if(strncmp(name_global, "name:", 5) == 0 || strncmp(email_global, "email:", 6) == 0){
                    fprintf(stdout, "SAMAV : There Is No Local or Global Completed Configuration.\nPlease Complete Both Configuration(Email & Name) First, Then Try Again!");
                    return 1;
                }
                else{
                    chdir(Current);
                    system("mkdir .samav");
                    system("attrib +h .samav");
                    fprintf(stdout, "SAMAV : Initialization Was Successful Now You Have A Repository At Address:\n%s\\.samav\n", Current);
                    fprintf(stdout, "NOTE: Your Global Configuration Has Been Used For This Project!");
                    chdir(".samav");
                    file_1 = fopen("config.txt", "w");
                    fprintf(file_1, "%s%s", name_global, email_global);
                    fprintf(file_1, "branch = master\n");
                    fprintf(file_1, "last_commit_id: %d\n", 999999);
                    fprintf(file_1, "current_commit_id: %d\n", 999999);
                    fclose(file_1);
                    file_1 = fopen("stage.txt", "w");
                    fclose(file_1);
                    file_1 = fopen("track.txt", "w");
                    fclose(file_1);
                    mkdir("commits");
                    mkdir("files");
                    chdir(global_thing);
                    file_1 = fopen("config_local.txt", "w");
                    fprintf(file_1, "name:\nemail:\n");
                    fclose(file_1);
                    chdir(Current);
                    return 0;
                }
            }
            else{
                chdir(Current);
                system("mkdir .samav");
                system("attrib +h .samav");
                fprintf(stdout, "SAMAV : Initialization Was Successful Now You Have A Repository At Address:\n%s\\.samav\n", Current);
                fprintf(stdout, "NOTE: Your Local Configuration Has Been Used For This Project!");
                chdir(".samav");
                file_1 = fopen("config.txt", "w");
                fprintf(file_1, "%s%s", name_local, email_local);
                fprintf(file_1, "branch = master\n");
                fprintf(file_1, "last_commit_id: %d\n", 999999);
                fprintf(file_1, "current_commit_id: %d\n", 999999);
                fclose(file_1);
                file_1 = fopen("stage.txt", "w");
                fclose(file_1);
                file_1 = fopen("track.txt", "w");
                fclose(file_1);
                mkdir("commits");
                mkdir("files");
                chdir(global_thing);
                file_1 = fopen("config_local.txt", "w");
                fprintf(file_1, "name:\nemail:\n");
                fclose(file_1);
                chdir(Current);
                return 0;
            }
        }
    }

    // All The samav config:
    else if(strcmp(argv[1], "config") == 0){
        // Global:
        if(strcmp(argv[2], "-global") == 0){
            // User.Name:
            if(strcmp(argv[3], "user.name") == 0){
                if(!global_writter(argc, argv, 1, argv[4], 1))
                fprintf(stdout, "SAMAV : A Global Name: \"%s\" Has Been Saved Successfully!", argv[4]);
                return 0;
            }
            // User.Email:
            if(strcmp(argv[3], "user.email") == 0){
                if(!global_writter(argc, argv, 2, argv[4], 1))
                fprintf(stdout, "SAMAV : A Global Email: \"%s\" Has Been Saved Successfully!", argv[4]);
                return 0;
            }
            // Alias:
            if(strncmp(argv[3], "alias.", 6) == 0){
                // LATER//
            }
        
        }
        // Just This Project:
        else{
            // User.Name:
            if(strcmp(argv[2], "user.name") == 0){
                if(!global_writter(argc, argv, 1, argv[3], 0))
                fprintf(stdout, "SAMAV : A Local Name: \"%s\" Has Been Saved Successfully!", argv[3]);
                return 0;
            }
            // User.Email:
            if(strcmp(argv[2], "user.email") == 0){
                if(!global_writter(argc, argv, 2, argv[3], 0))
                fprintf(stdout, "SAMAV : A Local Email: \"%s\" Has Been Saved Successfully!", argv[3]);
                return 0;
            }
            // Alias:
            if(strncmp(argv[2], "alias.", 6) == 0){
                // LATER//
            }
        }
    }

    else if(strcmp(argv[1], "add") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc < 3){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
        strcat(Samav_Root, "\\.samav");
        chdir(Samav_Root);
        if(strcmp(argv[2], "-f") == 0){
            return 0;
        }
        if(strcmp(argv[2], "-n") == 0){
            return 0;
        }
        if(strcmp(argv[2], "-redo") == 0){
            return 0;
        }
        else{
            return Add_to_stage_file_mod(argc, argv, argv[2]);
        }
    }






    return 0;
}
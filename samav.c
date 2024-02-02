// In The Name Of God
// samav Project
// Autumn_Winter 1402

// Seyed_Ahmad_Mousavi_Awal
// 402106648

// Address Of Global Thing:
// C:\Users\user\Desktop\c programs\tamrin\project_1402_autumn\global

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>
#include <conio.h>

#define global_thing "C:\\Users\\user\\Desktop\\c programs\\tamrin\\project_1402_autumn\\global"
#define wildcard_path "C:\\Users\\user\\Desktop\\c programs\\tamrin\\project_1402_autumn\\global\\wildcard.txt"

// Error: {fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
// Don't Have: {fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}


// Proto_Types:
int line_counter(char* path);
int is_wild(char* line);
char* end(int argc, char* argv[], char* address);
int check_difference(char* path1, char* path2);
char* samav_exist(int argc, char* argv[]);
int global_writter(int argc, char* argv[], int line, char* global, int choose);
int Add_to_stage_file_mod(int argc, char* argv[], char * filepath);
int Add_to_stage_file_mod_2(int argc, char* argv[], char * filepath);
int Is_Directory(char* path);
int Add_to_stage_folder_mod(int argc, char* argv[], char* pathfile);
int Add_with_depth(int argc, char* argv[], int depth, char* pathfile, char* rootpath);
char** config_reader(char* rootpath);
int run_commit(int argc, char* argv[], char* root_path);
int inc_last_commit_ID(char* root_path);
bool check_file_directory_exists(char *filepath, char* root_path);
int commit_staged_file(int commit_ID, char* filepath, char* rootpath, char* filepath2);
int track_file(char *filepath, char* rootpath);
bool is_tracked(char *filepath, char* rootpath);
int create_commit_file(int commit_ID, char *message, char* rootpath, int q);
int find_file_last_commit(char* filepath, char* rootpath);
int Add_to_stage_folder_mod_simple(int argc, char* argv[], char* pathfile, char* rootpath);
int Add_to_stage_file_mod_2_simple(int argc, char* argv[], char * filepath, char* rootpath);
int Add_to_stage_file_mod_simple(int argc, char* argv[], char * filepath, char* rootpath);
int directory_reader(char* name, char* rootpath);
void write_name_commit(char* file, char* rootpath);
int status(int argc, char* argv[], int state, char* path);
int reset_folder_mod_simple(int argc, char* argv[], char* pathfile, char* rootpath);
void delete_reset(char* path, char* root_path);
int reset_file_mod_simple(int argc, char* argv[], char * filepath, char* rootpath);
int undo_reset(int argc, char* argv[], char* rootpath);
int reset_undo_last_a(int argc, char* argv[], char* rootpath);
int reset_file_mod_2_simple(int argc, char* argv[], char * filepath, char* rootpath);
int folder_reader(int argc, char* argv[], char* pathfile, char* rootpath);
void status_file(int argc, char* argv[], char* path, char* rootpath);




// How Many Lines?
int line_counter(char* path){
    FILE* file = fopen(path, "r");
    if(file == NULL){return -1;}
    int i = 0;
    char* line = (char*) malloc(1000 * sizeof(char));  
    while(fgets(line, 1000, file)){
        i++;
    }
    free(line);
    rewind(file);
    fclose(file);
    return i;
}

// Is Wild Card?
int is_wild(char* line){
    for(int i = 0; i < strlen(line); i++){
        if(*(line + i) == '*'){
            return 1;
        }
    }
    return 0;
}


// Find The End Of A String in Address:
char* end(int argc, char* argv[], char* address){
    char* nothing = (char*) malloc(sizeof(char) * 1000);
    char nothing2[100];
    int j = 0;
    int i = strlen(address) - 1;
    while(address[i] != '\\'){
        nothing2[j] = address[i];
        i--;
        j++;
    }
    nothing2[j] = '\0';
    for(int i = 0; i < j; i++){
        nothing[i] = nothing2[j - i - 1];
    }
    nothing[j] = '\0';
    return nothing;
}

// Check Two File Are Different Or No?
int check_difference(char* path1, char* path2){
    FILE* file1 = fopen(path1, "r");
    FILE* file2 = fopen(path2, "r");
    char ch1;
    char ch2;
    rewind(file1);
    rewind(file2);
    while(((ch1 = fgetc(file1)) != EOF) && ((ch2 = fgetc(file2)) != EOF)){
        if(ch1 != ch2){
            fclose(file1);
            fclose(file2);
            return 0;
        }
    }
    ch1 = fgetc(file1);
    ch2 = fgetc(file2);
    if(ch1 != ch2){
        fclose(file1);
        fclose(file2);
        return 0;
    }
    fclose(file1);
    fclose(file2);
    return 1;
}

// Check Samav Exists?:
char* samav_exist(int argc, char* argv[]) {

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

// Add A File Or Folder To Project:
int Add_to_stage_file_mod(int argc, char* argv[], char * filepath){
    char wildcard[1000] = "dir /s /b ";
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

        if(Is_Directory(line_wild) == 1){
            Add_to_stage_folder_mod(argc, argv, line_wild);
            continue;
        }
        while(fgets(line_reader, 1024, file_find)){
            line_reader[strlen(line_reader) - 1] = '\0';
            if(strcmp(line_reader, line_wild) == 0){
                char path_nothing[1000] = "adds\\";
                int i = strlen(line_wild) - 1;
                int j = 0;
                char nothing[100];
                while(line_wild[i] != '\\'){
                    nothing[j] = line_wild[i];
                    i--;
                    j++;
                }
                char nothing2[100];
                for(int i = 0; i < j; i++){
                    nothing2[i] = nothing[j - i - 1];
                }
                nothing2[j] = '\0';
                strcat(path_nothing, nothing2);
                if(check_difference(line_wild, path_nothing) == 1){
                    fprintf(stdout , "SAMAV : File With Address: \'%s\' Exists! Please Use Commit Operation!\n", line_wild);
                    exist = 1;
                    break;
                }
                else{
                    // Delete:
                    chdir("adds");
                    char operation[1000] = "del ";
                    int i = strlen(line_wild) - 1;
                    int j = 0;
                    char nothing[100];
                    while(line_wild[i] != '\\'){
                        nothing[j] = line_wild[i];
                        i--;
                        j++;
                    }
                    char nothing2[100];
                    for(int i = 0; i < j; i++){
                        nothing2[i] = nothing[j - i - 1];
                    }
                    nothing2[j] = '\0';
                    strcat(operation, nothing2);
                    system(operation);
                    chdir("..");
                    // copy:
                    strcpy(operation, "copy ");
                    strcat(operation, line_wild);
                    strcat(operation, " adds");
                    system(operation);
                    exist = 1;
                    fprintf(stdout, "SAMAV : File With Address: \'%s\' Has Already Been Changed Before! And Now Has Been Added!\n", line_wild);
                    break;
                }
            }
        }
        if(!exist){
            fclose(file_find);
            file_find = fopen("stage.txt", "a");
            fprintf(file_find,"%s\n" ,line_wild);
            fclose(file_find);
            file_find = fopen("stage.txt", "r");
            char operation[1000] = "copy ";
            strcat(operation, line_wild);
            strcat(operation, " adds");
            system(operation);
            fprintf(stdout, "SAMAV : A File With Address: \'%s\' Has Been Added!\n", line_wild);
        }
        rewind(file_find);
    }
    fclose(file_find);
    fclose(file_read);
    system("del wildcard.txt");
    return 0;
}

// version2:
int Add_to_stage_file_mod_2(int argc, char* argv[], char * filepath){
    FILE* file_find = fopen("stage.txt", "r");
    char line_reader[1024];
    int exist = 0;
    while(fgets(line_reader, 1024, file_find)){
        line_reader[strlen(line_reader) - 1] = '\0';
        if(strcmp(line_reader, filepath) == 0){
            char path_nothing[1000] = "adds\\";
            int i = strlen(filepath) - 1;
            int j = 0;
            char nothing[100];
            while(filepath[i] != '\\'){
                nothing[j] = filepath[i];
                i--;
                j++;
            }
            char nothing2[100];
            for(int i = 0; i < j; i++){
                nothing2[i] = nothing[j - i - 1];
            }
            nothing2[j] = '\0';
            strcat(path_nothing, nothing2);
            if(check_difference(filepath, path_nothing) == 1){
                fprintf(stdout , "SAMAV : File With Address: \'%s\' Exists! Please Use Commit Operation!\n", filepath);
                exist = 1;
                break;
            }
            else{
                // Delete:
                chdir("adds");
                char operation[1000] = "del ";
                strcat(operation, filepath);
                system(operation);
                chdir("..");
                // copy:
                strcpy(operation, "copy ");
                strcat(operation, filepath);
                strcat(operation, " adds");
                system(operation);
                exist = 1;
                fprintf(stdout, "SAMAV : File With Address: \'%s\' Has Already Been Changed Before! And Now Has Been Added!\n", filepath);
                break;
            }
        }
    }
    if(!exist){
        fclose(file_find);
        file_find = fopen("stage.txt", "a");
        fprintf(file_find,"%s\n" ,filepath);
        fclose(file_find);
        file_find = fopen("stage.txt", "r");
        char operation[1000] = "copy ";
        strcat(operation, filepath);
        strcat(operation, " adds");
        system(operation);
        fprintf(stdout, "SAMAV : A File With Address: \'%s\' Has Been Added!\n", filepath);
    }
    fclose(file_find);
    return 0;
}

// Is Staged?
int is_staged(char* path, char* rootpath){
    char alak[1000];
    strcpy(alak, rootpath);
    strcat(alak, "\\stage_copy.txt");
    FILE* file = fopen(alak ,"r");
    char line[1000];
    while(fgets(line, 1000, file)){
        if(strstr(line, path) != NULL){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}


// A Path Address Is A directory Or No?
int Is_Directory(char* path){
    struct stat path_stat;

    if (stat(path, &path_stat) == 0) {
        if (S_ISREG(path_stat.st_mode)) {
            return 0;
        } 
        else if (S_ISDIR(path_stat.st_mode)) {
            return 1;
        }
    }
    return 2;
}

// Add A Folder To Project:
int Add_to_stage_folder_mod(int argc, char* argv[], char* pathfile){
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(pathfile);

    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return 1;
    }

    int is_come = 0;
    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            is_come = 1;
            char address[1000];
            strcpy(address, pathfile);
            strcat(address, "\\");
            strcat(address, entry->d_name);
            if(Is_Directory(address) == 1){
                Add_to_stage_folder_mod(argc, argv, address);
            }
            else{
                Add_to_stage_file_mod_2(argc, argv, address);    
            }
        }
    }
    if(!is_come){
        fprintf(stdout, "SAMAV : Folder With Address: \'%s\' Is Empty!\n", pathfile);
    }

    closedir(dir);
    return 0;
}

/////// A Simple Version://////
int Add_to_stage_file_mod_simple(int argc, char* argv[], char * filepath, char* rootpath){
    if(is_wild(filepath) == 0 && Is_Directory(filepath) == 1){
        return Add_to_stage_folder_mod_simple(argc, argv, filepath, rootpath);
    }
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

        if(Is_Directory(line_wild) == 1){
            Add_to_stage_folder_mod_simple(argc, argv, line_wild, rootpath);
            continue;
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
            char op[1000] = "dir /s /a:-d /b ";
            strcat(op, line_wild);
            strcat(op, " >> stage_copy.txt");
            system(op);
            fprintf(file_find,"%s\n" ,line_wild);
            fclose(file_find);
            file_find = fopen("stage.txt", "r");
            char operation[1000] = "copy ";
            strcat(operation, line_wild);
            strcat(operation, " adds > NUL");
            system(operation);
            fprintf(stdout, "SAMAV : A File With Address: \'%s\' Has Been Added!\n", line_wild);
        }
        rewind(file_find);
    }
    fclose(file_find);
    fclose(file_read);
    system("del wildcard.txt");
    return 0;
}

// version2:
int Add_to_stage_file_mod_2_simple(int argc, char* argv[], char * filepath, char* rootpath){
    FILE* file_find = fopen("stage.txt", "r");
    int exist = 0;
    char* fileName = end(argc, argv, filepath);
    char line_read[1000];
    while(fgets(line_read, 1000, file_find)){
        line_read[strlen(line_read) - 1] = '\0';
        if(strcmp(line_read, fileName) == 0){
            fprintf(stdout , "SAMAV : File With Address: \'%s\' Exists! Please Use Commit Operation!\n", filepath);
            exist = 1;
            break;
            // int i = strlen(fileName) - 1;
            // int j = 0;
            // char nothing[100];
            // while(fileName[i] != '\\'){
            //     nothing[j] = fileName[i];
            //     i--;
            //     j++;
            // }
            // char nothing2[100];
            // for(int i = 0; i < j; i++){
            //     nothing2[i] = nothing[j - i - 1];
            // }
            // nothing2[j] = '\0';


            // char path_nothing[1000] = "adds\\";
            // strcat(path_nothing, fileName);
            // if(check_difference(filepath, path_nothing) == 1){
            //     fprintf(stdout , "SAMAV : File With Address: \'%s\' Exists! Please Use Commit Operation!\n", filepath);
            //     exist = 1;
            //     break;
            // }
            // else{
            //     // Delete:
            //     chdir("adds");
            //     char operation[1000] = "del ";
            //     strcat(operation, fileName);
            //     system(operation);
            //     chdir("..");
            //     // copy:
            //     strcpy(operation, "copy ");
            //     strcat(operation, filepath);
            //     strcat(operation, " adds > NUL");
            //     system(operation);
            //     exist = 1;
            //     fprintf(stdout, "SAMAV : File With Address: \'%s\' Has Already Been Changed Before! And Now Has Been Added!\n", filepath);
            //     break;
            // }
        }
    }
    if(!exist){
        fclose(file_find);
        file_find = fopen("stage.txt", "a");
        char op[1000] = "dir /s /a:-d /b ";
        strcat(op, fileName);
        strcat(op, " >> stage_copy.txt");
        system(op);
        fprintf(file_find,"%s\n" ,fileName);
        fclose(file_find);
        file_find = fopen("stage.txt", "r");
        char operation[1000] = "copy ";
        strcat(operation, filepath);
        strcat(operation, " adds > NUL");
        system(operation);
        fprintf(stdout, "SAMAV : A File With Address: \'%s\' Has Been Added!\n", filepath);
    }
    fclose(file_find);
    return 0;
}

int Add_to_stage_folder_mod_simple(int argc, char* argv[], char* pathfile, char* rootpath){
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(pathfile);

    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return 1;
    }

    int is_come = 0;
    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            is_come = 1;
            char address[1000];
            strcpy(address, pathfile);
            strcat(address, "\\");
            strcat(address, entry->d_name);
            if(Is_Directory(address) == 1){
                Add_to_stage_folder_mod_simple(argc, argv, address, rootpath);
            }
            else{
                Add_to_stage_file_mod_2_simple(argc, argv, address, rootpath);    
            }
        }
    }
    if(!is_come){
        fprintf(stdout, "SAMAV : Folder With Address: \'%s\' Is Empty!\n", pathfile);
    }

    closedir(dir);
    return 0;
}
/////// A Simple Version!//////

// redo_add:
void redo_in_add(int argc, char* argv[], char* rootpath){
    char salam[1000];
    strcpy(salam, rootpath);
    strcat(salam, "\\stage_copy.txt");
    FILE* file = fopen(salam, "r");
    char line[1000];
    int is_come = 0;
    while(fgets(line, 1000, file)){
        if(strcmp(line, "a\n") == 0){
            continue;
        }
        line[strlen(line) - 1] = '\0';
        char* alaki = end(argc, argv, line);
        char salam_2[1000];
        strcpy(salam_2, rootpath);
        strcat(salam_2, "\\adds\\");
        strcat(salam_2, alaki);
        // Different:
        if(!check_difference(line, salam_2)){
            printf("%s\n%s\n", line, salam_2);
            is_come = 1;
            FILE* fd = fopen(line, "w");
            FILE* fc = fopen(salam_2, "r");
            char copy[1000]; 
            while(fgets(copy, 1000, fc)){
                fprintf(fd, copy);
            }
            fclose(fd);
            fclose(fc);
            fprintf(stdout, "SAMAV : File With Address: \'%s\' Had Changed Before And Now Is In Staging Area With Previous Text!\n", line);
        }
    }
    if(!is_come){
        fprintf(stdout, "SAMAV : There Is No File(s) With Changes In Your Repository!\n");
    }
    return;
}

// Add with Depth:
int Add_with_depth(int argc, char* argv[], int depth, char* folderpath, char* rootpath){
    if(depth == 0){
        return 0;
    }
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(folderpath);


    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return 1;
    }

    int is_come = 0;
    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_DIR){
            if(strcmp(entry->d_name, "adds") != 0 && strcmp(entry->d_name, "branches") != 0 && strcmp(entry->d_name, "commits") != 0 && strcmp(entry->d_name, "files") != 0 && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                is_come = 1;
                char salam[1000];
                strcpy(salam, folderpath);
                strcat(salam, "\\");
                strcat(salam, entry->d_name);
                depth--;
                Add_with_depth(argc, argv,depth, salam, rootpath);
            }
        }
        else{
            if(strcmp(entry->d_name, "stage.txt") != 0 && strcmp(entry->d_name, "stage_copy.txt") != 0 && strcmp(entry->d_name, "track.txt") != 0 && strcmp(entry->d_name, "config.txt") != 0){
                is_come = 1;
                char salam[1000];
                strcpy(salam, folderpath);
                strcat(salam, "\\");
                strcat(salam, entry->d_name);
                if(is_staged(salam, rootpath) == 1){
                    fprintf(stdout, "File With Address: \'%s\' Is In Staging Area!\n", salam);
                }
                else{
                    fprintf(stdout, "File With Address: \'%s\' Is Not In Staging Area!\n", salam);
                }
            }
        }
    }
    if(!is_come){
        fprintf(stdout, "Folder With Address: \'%s\' Is Empty!\n", folderpath);
    }


    closedir(dir);
    return 0;
}

///////////// ADD IS DONE! ////////////


//// Reset Functions: ///////
int reset_undo_last_a(int argc, char* argv[], char* rootpath){
    char path[1000];
    strcpy(path, rootpath);
    strcat(path, "\\stage.txt");
    int a = line_counter(path);
    FILE* file = fopen(path, "r");
    char line[1000];
    int where = 1;
    for(int i = 1; i < a ; i++){
        fgets(line, 1000, file);
        if(strcmp(line, "a\n") == 0){
            fgets(line, 1000, file);
            i++;
            if(strcmp(line, "a\n") != 0){
                where = i - 1;
            }
        }
    }
    rewind(file);
    fclose(file);
    return where;
}


int undo_reset(int argc, char* argv[], char* rootpath){
    int where = reset_undo_last_a(argc, argv, rootpath);
    char line[1000];
    char path[1000];
    strcpy(path, rootpath);
    strcat(path, "\\stage.txt");
    FILE* file = fopen(path, "r");
    for(int i = 1; i < where; i++){
        fgets(line, 1000, file);
    }

    FILE* file3 = fopen("alaki.txt", "w");
    while(fgets(line, 1000, file)){
        if(strcmp(line, "a\n") != 0){
            fprintf(file3, line);
        }
    }
    fclose(file);
    fclose(file3);
    file3 = fopen("alaki.txt", "r");
    int is = 0;
    while(fgets(line, 1000, file3)){
        is = 1;
        line[strlen(line) - 1] = '\0';
        reset_file_mod_2_simple(argc, argv, line, rootpath);
    }
    fclose(file3);
    system("del alaki.txt");
    if(!is){
        fprintf(stdout, "SAMAV : There Is No File(s) In Staging Area Please Try Again!");
    }
    return 0;
}

void delete_reset(char* path, char* root_path){
    char first[1000];
    strcpy(first, root_path);
    strcat(first, "\\stage.txt");
    char second[1000];
    strcpy(second, root_path);
    strcat(second, "\\stage_1.txt");
    FILE* file_1 = fopen(first, "r");
    FILE* file_2 = fopen(second, "w");
    char line[1000];
    while(fgets(line, 1000, file_1)){
        line[strlen(line) - 1] = '\0';
        if(strstr(path, line) == NULL){
            fprintf(file_2, line);
            fprintf(file_2, "\n");
        }
    }
    fclose(file_1);
    fclose(file_2);
    char op[1000] = "del \"";
    strcat(op, first);
    strcat(op, "\"");
    system(op);
    strcpy(op, "rename \"");
    strcat(op, second);
    strcat(op, "\" stage.txt");
    system(op);
    //second:
    strcpy(first, root_path);
    strcat(first, "\\stage_copy.txt");
    strcpy(second, root_path);
    strcat(second, "\\stage_copy_1.txt");
    file_1 = fopen(first, "r");
    file_2 = fopen(second, "w");
    while(fgets(line, 1000, file_1)){
        if(strstr(line, path) == NULL){
            fprintf(file_2, line);
        }
    }
    fclose(file_1);
    fclose(file_2);
    char oper[1000] = "del \"";
    strcat(oper, first);
    strcat(oper, "\"");
    system(oper);
    strcpy(oper, "rename \"");
    strcat(oper, second);
    strcat(oper, "\" stage_copy.txt");
    system(oper);
    return;
}

int reset_file_mod_simple(int argc, char* argv[], char * filepath, char* rootpath){
    if(is_wild(filepath) == 0 && Is_Directory(filepath) == 1){
        return reset_folder_mod_simple(argc, argv, filepath, rootpath);
    }
    char wildcard[1000] = "dir /b ";
    strcat(wildcard, filepath);
    strcat(wildcard, " >>");
    strcat(wildcard, " wildcard.txt");
    system(wildcard);
    FILE* file_read = fopen("wildcard.txt", "r");
    char line_wild[1024];
    // MAIN LOOP:
    while(fgets(line_wild, 1024, file_read)){
        line_wild[strlen(line_wild) - 1] = '\0';

        if(Is_Directory(line_wild) == 1){
            reset_folder_mod_simple(argc, argv, line_wild, rootpath);
            continue;
        }
        if(!is_staged(line_wild, rootpath)){
            fprintf(stdout, "SAMAV : File With Address: \'%s\' Is Not Staged Yet! You Can't Use Reset Operation For This File!\n", line_wild);
            continue;
        }
        else{
            delete_reset(line_wild, rootpath);
            char alaki[1000] = "del \"";
            strcat(alaki, rootpath);
            strcat(alaki, "\\adds\\");
            strcat(alaki, line_wild);
            strcat(alaki, "\"");
            system(alaki);
            fprintf(stdout, "SAMAV : File With Address: \'%s\' Has Been Deleted From Staging Area!\n", line_wild);
        }
    }
    fclose(file_read);
    system("del wildcard.txt");
    return 0;
}

// version2:
int reset_file_mod_2_simple(int argc, char* argv[], char * filepath, char* rootpath){
        if(!is_staged(filepath, rootpath)){
            fprintf(stdout, "SAMAV : File With Address: \'%s\' Is Not Staged Yet! You Can't Use Reset Operation For This File!\n", filepath);
        }
        else{
            delete_reset(filepath, rootpath);
            char alaki[1000] = "del \"";
            strcat(alaki, rootpath);
            strcat(alaki, "\\adds\\");
            strcat(alaki, filepath);
            strcat(alaki, "\"");
            system(alaki);
            fprintf(stdout, "SAMAV : File With Address: \'%s\' Has Been Deleted From Staging Area!\n", filepath);
        }
    return 0;
}

int reset_folder_mod_simple(int argc, char* argv[], char* pathfile, char* rootpath){
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(pathfile);

    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return 1;
    }

    int is_come = 0;
    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            is_come = 1;
            char address[1000];
            strcpy(address, pathfile);
            strcat(address, "\\");
            strcat(address, entry->d_name);
            if(Is_Directory(address) == 1){
                reset_folder_mod_simple(argc, argv, address, rootpath);
            }
            else{
                char* alaki = end(argc, argv, address);
                reset_file_mod_2_simple(argc, argv, alaki, rootpath);    
            }
        }
    }
    if(!is_come){
        fprintf(stdout, "SAMAV : Folder With Address: \'%s\' Is Empty!\n", pathfile);
    }

    closedir(dir);
    return 0;
}
///// RESET functions DONE! ////////

//// Status Functions: ///////
void status_file(int argc, char* argv[], char* path, char* rootpath){
    char* alaki = end(argc, argv, path);
    int state = is_staged(alaki, rootpath);
    int max = directory_reader(alaki, rootpath); // -2: add, else: M?
    
    if(max == -2){
        if(state == 1){
            fprintf(stdout, "SAMAV : File: \'%s\', +A\n", path);
            return;
        }
        else{
            fprintf(stdout, "SAMAV : File: \'%s\', -A\n", path);
            return;
        }
    }
    char way[1000];
    strcpy(way, rootpath);
    strcat(way, "\\.samav\\files\\");
    char tmp[100];
    sprintf(tmp, "\\%d.txt", max);
    strcat(way, alaki);
    strcat(way, tmp);
    int mod = check_difference(path, way); // 1: m-, 0: m+
    int last = config_commit(rootpath);
    char commit[1000];
    strcpy(commit, rootpath);
    strcat(commit, "\\.samav\\commits\\");
    char tmpp[100];
    sprintf(tmpp, "%d.txt", last);
    strcat(commit, tmpp);
    FILE* file = fopen(commit, "r");
    char line[1000];
    while(fgets(line, 1000, file)){
        if(strncmp(line, "files:", 6) == 0){
            break;
        }
    }
    char get[1000];
    strcpy(get, global_thing);
    strcat(get, "\\time.txt");
    FILE* file_2 = fopen(get, "a");
    int q = 1;
    while(fgets(line, 1000, file)){
        int com;
        char name[1000];
        sscanf(line, "%s%d\n", &name, &com);
        name[strlen(name) - 1] = '\0';
        if(strstr(path, name) != NULL){
            if(state == 1){
                fprintf(file_2, "%d\n", q);
                break;
            }
            else{
                fprintf(file_2, "%d\n", q);
                break;
            }
        }
        q++;
    }
    fclose(file);
    fclose(file_2);
    if(state == 1){
        if(mod == 0){
            fprintf(stdout, "SAMAV : File: \'%s\', +M\n", path);
            return;
        }
    }
    else{
        if(mod == 0){
            fprintf(stdout, "SAMAV : File: \'%s\', -M\n", path);
            return;
        }
    }
}

int folder_reader(int argc, char* argv[], char* pathfile, char* rootpath){
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(pathfile);

    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return 1;
    }

    int is_come = 0;
    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, "adds") != 0 && strcmp(entry->d_name, "config.txt") != 0 && strcmp(entry->d_name, "stage.txt") != 0 && strcmp(entry->d_name, "stage_copy.txt") != 0 && strcmp(entry->d_name, "branches") != 0 && strcmp(entry->d_name, "commits") != 0 && strcmp(entry->d_name, "files") != 0 && strcmp(entry->d_name, "track.txt") != 0 && strcmp(entry->d_name, "tags") != 0){
            is_come = 1;
            char address[1000];
            strcpy(address, pathfile);
            strcat(address, "\\");
            strcat(address, entry->d_name);
            if(Is_Directory(address) == 1){
                folder_reader(argc, argv, address, rootpath);
            }
            else{
                status_file(argc, argv, address,  rootpath);    
            }
        }
    }
    if(!is_come){
        fprintf(stdout, "SAMAV : Folder With Address: \'%s\' Is Empty!\n", pathfile);
    }

    closedir(dir);
    return 0;
}

void line_commit(int line, char* commit_path, char* rootpath){
    FILE* file = fopen(commit_path, "r");
    char sal[1000];
    for(int i = 0; i < line + 8; i++){
        fgets(sal, 1000, file);
    }
    fclose(file);
    char name[100];
    int com;
    sscanf(sal, "%s%d\n", &name, &com);
    name[strlen(name) - 1] = '\0';
    int how = is_staged(name, rootpath);
    if(how){
        fprintf(stdout, "SAMAV : File: \'%s\', +D\n", name);
        return;
    }
    fprintf(stdout, "SAMAV : File: \'%s\', -D\n", name);
    return;
}

void Delete_commit(int argc, char* argv[], int num, char* rootpath, char* commit_path){
    char alaki[1000];
    strcpy(alaki, global_thing);
    strcat(alaki, "\\time.txt");
    FILE* file = fopen(alaki, "r");
    char line[1000];
    int car[num + 1];
    for(int i = 1; i <= num; i++){
        car[i - 1] = i; 
    }
    char get[1000];
    for(int i = 1; i <= num; i++){
        while(fgets(get, 1000, file)){
            int a;
            sscanf(get, "%d\n", &a);
            if(a == i){
                car[i - 1] = 0;
            }
        }
        rewind(file);
    }
    fclose(file);
    file = fopen(alaki, "w");
    fclose(file);
    for(int i = 0; i < num; i++){
        if(car[i] != 0){
            line_commit(car[i], commit_path, rootpath);
        }
    }
    return;
}
////// Status functions DONE! ////////


// MAKE BRANCH:
int branch_maker(int argc, char* argv[], char* root_path){
    char path[1000];
    strcpy(path, root_path);
    strcat(path, "\\.samav\\branches");
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(path);

    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, argv[2]) == 0){
            fprintf(stdout, "SAMAV : A Branch With Name: \'%s\' is Already Exists! Please Choose A Different Name!\n", argv[2]);
            return 1;
        }
    }
    // we have to make a branch here:
    char op2[1000] = "mkdir \"";
    strcat(op2, path);
    strcat(op2, "\\");
    strcat(op2, argv[2]);
    strcat(op2, "\"");
    system(op2);
    char** which_branch = config_reader(root_path);
    closedir(dir);
    strcat(path, "\\");
    strcat(path, which_branch[2]);

    struct dirent *de;
    DIR *dr = opendir(path);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        fprintf( stdout, "Could not open current directory\n");
        return 0;
    }

    // for readdir()
    long long int tmp; 
    long long int max = -1;
    while ((de = readdir(dr)) != NULL){
        if(strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0){
            char alaki[1000];
            strcpy(alaki, de->d_name);
            sscanf(alaki, "%lld.txt", &tmp);
            if(tmp > max){
                max = tmp;
            }
        }
    }
    closedir(dr);     // close directory
    strcat(path, "\\");
    char alak[1000];
    sprintf(alak, "%lld.txt", max);
    strcat(path, alak);
    char where[1000] = " \"";
    strcat(where, root_path);
    strcat(where, "\\.samav\\branches\\");
    strcat(where, argv[2]);
    strcat(where, "\"");


    char operation[2000] = "copy \"";
    strcat(operation, path);
    strcat(operation, "\"");
    strcat(operation, where);
    strcat(operation, " > NUL");
    system(operation);
    char but[1000];
    strcpy(but, root_path);
    strcat(but, "\\.samav\\config.txt");
    FILE* opn = fopen(but, "r");
    FILE* good = fopen("alaki.txt", "w");
    char fread[1000];
    while(fgets(fread, 1000, opn)){
        if(strncmp(fread, "branch =", 8) == 0){
            fprintf(good, "branch = %s\n", argv[2]);
        }
        else{
            fprintf(good, fread);
        }
    }
    fclose(opn);
    fclose(good);
    char sd[1000] = "del \"";
    strcat(sd, but);
    strcat(sd, "\"");
    system(sd);

    char alaki[1000] = "move /Y \"alaki.txt\" \"";
    strcat(alaki, but);
    strcat(alaki, "\" > NUL");
    system(alaki);

    fprintf(stdout, "SAMAV : A Branch With Name: \'%s\' Is Now In Your Repository!\nYour Now In Branch: \'%s\'.    (%s->%s)\n", argv[2], argv[2], which_branch[2], argv[2]);
    return 0;
}

// Showing The Branches:
int branch_show(int argc, char* argv[], char* root_path){
    char path[1000];
    strcpy(path, root_path);
    strcat(path, "\\.samav\\branches");
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(path);

    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return 1;
    }

    char** which = config_reader(root_path);

    fprintf(stdout, "SAMAV : You Have This(These) Branch(es) In Your Repository:\n");
    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0){
            if(strcmp(entry->d_name, which[2]) == 0){
                fprintf(stdout ,"* %s\n", entry->d_name);
            }
            else{
                printf("%s\n", entry->d_name);
            }
        }
    }
    closedir(dir);
    return 0;
}

// String To Number:
long long str_num(char* str){
    long long int num = 0;
    for(int i = 0; i < strlen(str); i++){
        num *= 10;
        num += ((int)str[i] - '0');
    }
    return num;
}

// Read commit:
char** commits_reader(char* rootpath, long long int name){
    char** res = (char**) malloc(sizeof(char*) * 5);
    for(int i = 0; i < 5; i++){
        *(res + i) = (char*) malloc(sizeof(char) * 1000);
    }
    char salam[1000];
    strcpy(salam, rootpath);
    strcat(salam, "\\.samav\\commits\\");
    char tmp[100];
    sprintf(tmp, "%lld.txt", name);
    strcat(salam, tmp);
    FILE* file = fopen(salam, "r");
    char line[1000];
    fgets(line, 1000, file);
    fgets(line, 1000, file);

    for(int i = 9; i < strlen(line) - 1; i++){
        *(*(res + 0) + (i - 9)) = line[i];
    }
    *(*(res + 0) + (strlen(line) - 10)) = '\0';
    // printf("%s\n", *(res + 0));
    fgets(line, 1000, file);
    fgets(line, 1000, file);
    fgets(line, 1000, file);
    line[strlen(line) - 1] = '\0';
    strcpy(*(res + 1), line); // branch
    fgets(line, 1000, file);
    line[strlen(line) - 1] = '\0';
    strcpy(*(res + 2), line); // name
    fclose(file);
    return res;
}

// read config:
char** config_reader(char* rootpath){
    char** res = (char**) malloc(sizeof(char*) * 10);
    for(int i = 0; i < 10; i++){
        *(res + i) = (char*) malloc(sizeof(char) * 1000);
    }
    char salam[1000];
    strcpy(salam, rootpath);
    strcat(salam, "\\.samav\\config.txt");
    FILE* file = fopen(salam, "r");
    char line[1000];
    fgets(line, 1000, file);
    int a = strlen(line);
    line[a - 1] = '\0';
    strcpy(*(res + 0), line); //name
    res[0][a - 1] = '\0';
    fgets(line, 1000, file);
    a = strlen(line);
    line[a - 1] = '\0';
    strcpy(*(res + 1), line); //email
    res[1][a - 1] = '\0';
    while(fgets(line, 1000, file)){
        if(strncmp(line, "branch =", 8) == 0){
            sscanf(line, "branch = %s", *(res + 2)); // branch
            fclose(file);
            return res;
        }
    }
}

// Last Commit_Id:
int config_commit(char* rootpath){
    char salam[1000];
    strcpy(salam, rootpath);
    strcat(salam, "\\.samav\\config.txt");
    FILE* file = fopen(salam, "r");
    int last_commit_ID;
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_id:", 15) == 0) {
            sscanf(line, "last_commit_id: %d\n", &last_commit_ID);
            break;
        }
    }
    fclose(file);
    return last_commit_ID;
}

// Read Time From Commits:
int read_time(char* rootpath, int name){
    char salam[1000];
    strcpy(salam, rootpath);
    strcat(salam, "\\.samav\\commits\\");
    char tmp[100];
    sprintf(tmp, "%d.txt", name);
    strcat(salam, tmp);
    FILE* file = fopen(salam, "r");
    char line[1000];
    fgets(line, 1000, file);
    fgets(line, 1000, file);
    fgets(line, 1000, file);
    line[strlen(line) - 1] = '\0';
    int h, m;
    sscanf(line, "%d:%d", &h, &m);
    rewind(file);
    fclose(file);
    int alaki = h * 100 + m;
    return alaki;
}

////////////////////// ALL THE WORK WE SHOULD DO IN COMMIT : ///////////////////
int max_in_commit(char* rootpath, char* name){
    char path[1000];
    strcpy(path, rootpath);
    strcat(path, "\\.samav\\branches\\");
    strcat(path, name);
    struct dirent *de;
    DIR *dr = opendir(path);
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("nista!\n");
        return -2;
    }

    // for readdir()
    int tmp; 
    int max = -1;
    while ((de = readdir(dr)) != NULL){
        if(strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0){
            char alak[1000];
            strcpy(alak, de->d_name);
            sscanf(alak, "%d.txt", &tmp);
            if(tmp > max){
                max = tmp;
            }
        }
    }
    closedir(dr);     // close directory

    return max;
}

int is_head(char* rootpath, int where){
    char path[1000];
    strcpy(path, rootpath);
    strcat(path, "\\.samav\\branches");
    struct dirent *de;
    DIR *dr = opendir(path);
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("nista!\n");
        return -2;
    }

    // for readdir()
    int tmp; 
    int max = -1;
    while ((de = readdir(dr)) != NULL){
        if(strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0){
            if(where == max_in_commit(rootpath, de->d_name)){
                closedir(dr);
                return 1;
            }
        }
    }
    closedir(dr); 
    return 0;
}

int run_commit(int argc, char* argv[], char* root_path) {

    char message[73];
    strcpy(message, argv[3]);
    char path[1000];
    char path2[1000];
    strcpy(path, root_path);
    strcpy(path2, root_path);
    strcat(path2, "\\.samav\\stage_copy.txt");
    strcat(path, "\\.samav\\stage.txt");
    if(line_counter(path) == 0 || line_counter(path) == 1){
        fprintf(stdout, "SAMAV : There Is No File In Staging Area To Commit!\nPlease Use \'samav add (Address)\' Operation First!\n");
        return 1;
    } 
    

    int commit_ID = inc_last_commit_ID(root_path);
    if (commit_ID == -1) return 1;
    if (commit_ID == -2){
        fprintf(stdout, "SAMAV : You Are Not In HEAD! And Because Of This You Can't Use Commit Operation Here!\n");
        return 1;
    }
    FILE *file = fopen(path, "r");
    FILE * file_copy = fopen(path2, "r");
    if (file == NULL) return 1;
    char line[1024];
    char line2[1024];
    int q = 1;
    while (fgets(line, sizeof(line), file) && fgets(line2, sizeof(line2), file_copy)) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        line2[strlen(line2) - 1] = '\0';
        if(strcmp(line, "a") == 0){continue;}
        
        if (!check_file_directory_exists(line, root_path)) {
            char dir_path[1024];
            strcpy(dir_path, root_path);
            strcat(dir_path, "\\.samav\\files\\");
            strcat(dir_path, line);
            if (mkdir(dir_path) != 0) return 1;
        }
        fprintf(stdout, "SAMAV : %d) Committed A File With Address: %s\n", q ,line);
        q++;
        commit_staged_file(commit_ID, line, root_path, line2);
        track_file(line, root_path);
    }
    fclose(file);
    fclose(file_copy);
    
    // free staging
    file = fopen(path, "w");
    if (file == NULL) return 1;
    fclose(file);
    file_copy = fopen(path2, "w");
    if (file == NULL) return 1;
    fclose(file_copy);

    system("rmdir /s /q adds");
    system("mkdir adds");

    create_commit_file(commit_ID, message, root_path, q - 1);
    fprintf(stdout, "Commit Was Successfully Done With Commit ID: %d, Message: \'%s\'\n%d File(s) Has Been Tracked!\n", commit_ID, message, q - 1);
    return 0;
}

// returns new commit_ID
int inc_last_commit_ID(char* root_path) {
    char copy[1000];
    char copy2[1000];
    strcpy(copy, root_path);
    strcpy(copy2, root_path);
    strcat(copy2, "\\.samav\\config.txt");
    strcat(copy, "\\.samav\\tmp_config.txt");
    FILE *file = fopen(copy2, "r");
    if (file == NULL) return -1;
    
    FILE *tmp_file = fopen(copy, "w");
    if (tmp_file == NULL) return -1;

    int last_commit_ID;
    int current_commit_id;
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_id:", 15) == 0) {
            sscanf(line, "last_commit_id: %d\n", &last_commit_ID);
            last_commit_ID++;
            fprintf(tmp_file, "last_commit_id: %d\n", last_commit_ID);
        }
        else if(strncmp(line, "current_commit_id:", 18) == 0){
            sscanf(line, "current_commit_id: %d\n", &current_commit_id);
            current_commit_id++;
            fprintf(tmp_file, "current_commit_id: %d\n", last_commit_ID);
            if(!is_head(root_path, current_commit_id - 1)){
                fclose(file);
                fclose(tmp_file);
                char sd[1000] = "del \"";
                strcat(sd, copy);
                strcat(sd, "\"");
                system(sd);
                return -2;
            }
        }
        else fprintf(tmp_file, "%s", line);
    }
    fclose(file);
    fclose(tmp_file);
    // remove(copy2);
    char sd[1000] = "del \"";
    strcat(sd, copy2);
    strcat(sd, "\"");
    system(sd);
    strcat(copy, "\"");
    char alaki[1000] = "rename \"";
    strcat(alaki, copy);
    strcat(alaki, " config.txt");
    system(alaki);
    return last_commit_ID;
}

bool check_file_directory_exists(char *filepath, char* root_path) {
    char alaki[1000];
    strcpy(alaki, root_path);
    strcat(alaki, "\\.samav\\files");
    char a[1024];
    strcpy(a, root_path);
    strcat(a, "\\.samav");
    DIR *dir = opendir(alaki);
    struct dirent *entry;
    if (dir == NULL) {
        fprintf(stdout, "SAMAV : There is An Unknown Problem While Opening Directory!");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, filepath) == 0){
            closedir(dir);
            chdir(a);
            return true;
        }

    }
    closedir(dir);

    chdir(a);

    return false;
}

int commit_staged_file(int commit_ID, char* filepath, char* rootpath, char* filepath2) {
    FILE *read_file, *write_file;
    char read_path[1024];
    strcpy(read_path, filepath2);
    char write_path[1024];
    strcpy(write_path, rootpath);
    strcat(write_path, "\\.samav\\files\\");
    strcat(write_path, filepath);
    strcat(write_path, "\\");
    char tmp[100];
    sprintf(tmp, "%d", commit_ID);
    strcat(write_path, tmp);
    strcat(write_path, ".txt");
    read_file = fopen(read_path, "r");
    if (read_file == NULL) return 1;
    write_file = fopen(write_path, "w");
    if (write_file == NULL) return 1;

    char buffer;
    buffer = fgetc(read_file);
    while(buffer != EOF) {
        fputc(buffer, write_file);
        buffer = fgetc(read_file);
    }
    fclose(read_file);
    fclose(write_file);
    char ax[1000];
    strcpy(ax, rootpath);
    strcat(ax, "\\.samav");
    chdir(ax);

    return 0;
}

int track_file(char *filepath, char* rootpath) {
    if (is_tracked(filepath, rootpath)) return 0;
    char alaki[1000];
    strcpy(alaki, rootpath);
    strcat(alaki, "\\.samav\\track.txt");
    FILE *file = fopen(alaki, "a");
    if (file == NULL) return 1;
    fprintf(file, "%s\n", filepath);
    fclose(file);
    return 0;
}

bool is_tracked(char *filepath, char* rootpath) {
    char alaki[1000];
    strcpy(alaki, rootpath);
    strcat(alaki, "\\.samav\\track.txt"); 
    FILE *file = fopen(alaki, "r");
    if (file == NULL) return false;
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);

        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        
        if (strcmp(line, filepath) == 0) {fclose(file); return true;}

    }
    fclose(file); 
    return false;
}

int create_commit_file(int commit_ID, char *message, char* rootpath, int q) {
    char commit_filepath[1024];
    strcpy(commit_filepath, rootpath);
    strcat(commit_filepath, "\\.samav\\commits\\");
    char tmp[100];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp);
    strcat(commit_filepath, ".txt");

    FILE *file = fopen(commit_filepath, "w");
    if (file == NULL) return 1; 
    char alaki[1000];
    strcpy(alaki, "time /t >> \"");
    strcat(alaki, global_thing);
    strcat(alaki, "\\time.txt\"");
    system(alaki);
    char alak[1000] = "echo %date% >> \"";
    strcat(alak, global_thing);
    strcat(alak, "\\time.txt\"");
    system(alak);
    char op[1000];
    strcpy(op, global_thing);
    strcat(op, "\\time.txt");
    FILE* time = fopen(op, "r");
    int hour, minute;
    fscanf(time, "%d:%d", &hour, &minute);
    rewind(time);
    char li[1000];
    fgets(li, 1000, time);
    fgets(li, 1000, time);
    fclose(time);
    fprintf(file, "%d\n", q);
    fprintf(file, "message: %s\n", message);
    fprintf(file, "%d:%d, %d\n", hour , minute, (60 * hour) + minute);
    fprintf(file, li);
    char** res = (char**) malloc(10 * sizeof(char*));
    for(int i = 0; i < 10; i++){
        *(res + i) = (char*) malloc(sizeof(char) * 100);
    }
    res = config_reader(rootpath);
    fprintf(file, "%s\n", res[2]);
    fprintf(file, "%s\n", res[0]);
    fprintf(file, "%s\n", res[1]);
    fprintf(file, "files:\n");
    fclose(file);
    char ax[1000];
    strcpy(ax, rootpath);
    strcat(ax, "\\.samav");
    chdir(ax);
    write_name_commit(commit_filepath, rootpath);
    char where[1000] = " \"";
    strcat(where, rootpath);
    strcat(where, "\\.samav\\branches\\");
    strcat(where, res[2]);
    strcat(where, "\"");
    char copy[2000] = "copy \"";
    strcat(copy, commit_filepath);
    strcat(copy, "\"");
    strcat(copy, where);
    strcat(copy, " > NUL");
    system(copy);
    time = fopen(op, "r");
    char read[100];
    fgets(read, 100, time);
    read[strlen(read) - 1] = '\0';
    fprintf(stdout, "SAMAV : Time: \'%s\', Commit ID: \'%d\'\n", read, commit_ID);
    fclose(time);
    time = fopen(op, "w");
    fclose(time);
    return 0;
}

// Write in commit:
void write_name_commit(char* file, char* rootpath){
    FILE* fptr = fopen(file, "a");
    struct dirent *entry;
    struct stat st;
    char path[1000];
    strcpy(path, rootpath);
    strcat(path, "\\.samav\\files");
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0){
            stat(entry->d_name, &st);
            fprintf(fptr,"%s: %d\n", entry->d_name, directory_reader(entry->d_name, rootpath));
        }
    }
    closedir(dir); 
    fclose(fptr);
    return;
}

// Max Of A Directory Files:
int directory_reader(char* name, char* rootpath){
    struct dirent *de;  // Pointer for directory entry
    char alaki[1000];
    strcpy(alaki, rootpath);
    strcat(alaki, "\\.samav\\files\\");
    strcat(alaki, name);
    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(alaki);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        closedir(dr);
        return -2;
    }

    // for readdir()
    int tmp; 
    int max = -1;
    while ((de = readdir(dr)) != NULL){
        if(strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0){
            char alak[1000];
            strcpy(alak, de->d_name);
            sscanf(alak, "%d.txt", &tmp);
            if(tmp > max){
                max = tmp;
            }
        }
    }
    closedir(dr);     // close directory

    return max;
}

////////////////////// ALL THE WORK WE SHOULD DO IN COMMIT : ///////////////////

// Log Functions:
void run_log(int argc, char* argv[], char* rootpath, int current, int counter){
    if(current - counter < 999999){
        counter = current - 999999;
    }
    fprintf(stdout, "SAMAV : You Can See Information of Last %d commit(s):\n", counter);
    fprintf(stdout ,"------------------------------------------------------------\n");
    while(counter != 0){
        char commit[1000];
        strcpy(commit, rootpath);
        strcat(commit, "\\.samav\\commits\\");
        char tmp[100];
        sprintf(tmp, "%d.txt", current);
        strcat(commit, tmp);
        FILE* file = fopen(commit, "r"); 
        fprintf(stdout, "%dth Commit:\n", counter);
        fprintf(stdout, "ID: %d\n", current);

        // Reading File:
        char line[1000];
        fgets(line, 1000, file);
        fgets(line, 1000, file);
        fprintf(stdout, line);
        int h, min;
        fscanf(file, "%d:%d", &h,&min);
        fprintf(stdout, "Time: %2d:%2d\n", h, min);
        rewind(file);
        char number[100];
        fgets(line, 1000, file);
        strcpy(number, line);
        number[strlen(number) - 1] = '\0';
        fgets(line, 1000, file);
        fgets(line, 1000, file);
        fgets(line, 1000, file);
        fprintf(stdout, line);
        fgets(line, 1000, file);
        fprintf(stdout, "Branch: %s", line);
        fgets(line, 1000, file);
        fprintf(stdout, "Author: %s", line);
        fgets(line, 1000, file);
        fprintf(stdout, "Email: %s", line);
        fprintf(stdout, "In This Commit You Have Commited %s file(s)\n", number);
        fprintf(stdout ,"____________________________________________________________\n");
        fclose(file);
        counter--;
        current--;
    }
    return;
}

void commit_in_branch(int argc, char* argv[] ,char* name, char* root_path){
    char path[1000];
    strcpy(path, root_path);
    strcat(path, "\\.samav\\branches\\");
    strcat(path, name);

    struct dirent *de;
    DIR *dr = opendir(path);
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        fprintf(stdout, "SAMAV : There Is No Branch With Name: \'%s\'! Please Try Again!\n", name);
        return;
    }
    fprintf(stdout, "SAMAV : You Have Committed These Commits In Branch: \'%s\'\n", argv[3]);
    int q = 1;
    while ((de = readdir(dr)) != NULL){
        long long int id;
        if(strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0){
            char name[100];
            strcpy(name, path);
            strcat(name, "\\");
            strcat(name, de->d_name);
            sscanf(de->d_name, "%lld.txt", &id);
            fprintf(stdout, "%2dth) ID: %lld, ", q ,id);
            q++;
            FILE* file = fopen(name, "r");
            char line[1000];
            fgets(line, 1000, file);
            fgets(line, 1000, file);
            fprintf(stdout, line);
            fclose(file);
        }
    }
    closedir(dr);
    return;
}

void author_in_log(int argc, char* argv[], char* name, char* root_path, int current){
    // char** not = config_reader(root_path);
    
    int q = 1;
    int is_come = 0;
    for(long long i = current; i >= 1000000; i--){
        char** commit = commits_reader(root_path, i);
        if(strcmp(*(commit + 2), name) == 0){
            is_come = 1;
            fprintf(stdout, "%2dth) ID: %lld, Message: %s\n", q, i, *(commit + 0));
            q++;
        }
    }
    if(!is_come){
        fprintf(stdout, "SAMAV : Person With Name: \'%s\' Has Never Committed!\n",name);
        return;
    }
    if(q == 2){
        fprintf(stdout, "SAMAV : Person With Name: \'%s\' Committed Just This Commit!\n", name);
        return;
    }
    fprintf(stdout, "SAMAV : Person With Name: \'%s\' Committed These %d Commits!\n", name, q - 1);
    return;



}

void time_in_log(int argc, char* argv[], int time, char* root_path, int current, int state, int h, int m){
    int is_come;
    for(int i = current; i >= 1000000; i--){
        int sum = read_time(root_path, i);
        int hour = sum / 100;
        int min = sum % 100;
        if(time > ((60 * hour) + min)){
            is_come = i;
            break;
        }
    }
    // Since:
    if(state == 1){
        int q = 1;
        for(int j = current; j > is_come; j--){
            int sum = read_time(root_path, j);
            int min = sum % 100;
            int hour = sum / 100;
            fprintf(stdout, "%2dth) ID: %d, Time: %2d:%2d\n", q, j, hour, min);
            q++;
        }
        if(q == 1){
            fprintf(stdout, "SAMAV : You Haven't Committed Since: %d:%d !\n", h, m);
            return;
        }
        fprintf(stdout, "SAMAV : You Have Committed This(These) Commit(s) Since: %d:%d\n", h, m);
        return;
    }
    // Before:
    else{
        int q = 1; 
        for(int j = is_come; j > 1000000; j--){
            int sum = read_time(root_path, j);
            int min = sum % 100;
            int hour = sum / 100;
            fprintf(stdout, "%2dth) ID: %d, Time: %2d:%2d\n", q, j, hour, min);
            q++;
        }
        if(q == 1){
            fprintf(stdout, "SAMAV : You Haven't Committed Before: %2d:%2d !\n", h, m);
            return;
        }
        fprintf(stdout, "SAMAV : You Have Committed This(These) Commit(s) Before: %2d:%2d\n", h, m);
        return;
    }
}

void search_message(int argc, char* argv[], int current, char* root_path){
    int q = 1;
    int is = 0;
    for(int i = current;  i >= 1000000; i--){
        char path[1000];
        strcpy(path, root_path);
        strcat(path, "\\.samav\\commits\\");
        char tmp[100];
        sprintf(tmp, "%d.txt", i);
        strcat(path, tmp);
        char** alk = commits_reader(root_path, i);
        for(int j = 3; j < argc; j++){
            char* salam = strstr(*(alk + 0) ,argv[j]);
            if(salam != NULL){
                is = 1;
                fprintf(stdout, "%2dth) ID: %d, Message: ", q, i);
                q++;
                for(int w = 0; w < ((int)(salam - *(alk + 0))); w++){
                    fprintf(stdout, "%c", *(*(alk + 0) + w));
                }
                fprintf(stdout, "<<");
                for(int w = 0; w < strlen(argv[j]); w++){
                    fprintf(stdout, "%c", argv[j][w]);
                }
                fprintf(stdout, ">>");
                for(int w = strlen(argv[j]); w < strlen(salam); w++){
                    fprintf(stdout, "%c", *(salam + w));
                }
                fprintf(stdout, "\n");
                break;
            }
        }
    }
    if(!is){
        fprintf(stdout, "SAMAV : This(These) Word(s) Were Not Found In The Message Of Any Of The Commit(s)!\n");
        return;
    }
    fprintf(stdout, "SAMAV : This(These) Word(s) Were Found In Message Of %d Commit(s)!\n", q - 1);
    return;
}
// Log Functions:


// Checkout Functions: ////
void cop_check(int which, char* what, char* rootpath){
    char first[1000];
    strcpy(first, rootpath);
    strcat(first, "\\.samav\\files\\");
    strcat(first, what);
    strcat(first, "\\");
    char tmp[100];
    sprintf(tmp, "%d.txt", which);
    strcat(first, tmp);
    FILE* awal = fopen(first, "r");
    // Done!
    char oper[1000] = "dir /s /a:-d /b ";
    strcat(oper, what);
    strcat(oper, " >> alaki.txt");
    system(oper);
    FILE* f = fopen("alaki.txt", "r");
    char second[1000];
    fgets(second, 1000, f);
    second[strlen(second) - 1] = '\0';
    fclose(f);
    system("del alaki.txt");
    FILE* dowom = fopen(second, "w");
    // Done!
    char buffer;
    buffer = fgetc(awal);
    while(buffer != EOF) {
        fputc(buffer, dowom);
        buffer = fgetc(awal);
    }
    fclose(awal);
    fclose(dowom);
    fprintf(stdout, "SAMAV : File With Address: \'%s\' Has Been Updated! With Commit: \'%d\'\n", second, which);
    return;
}

void run_check(int argc, char* argv[], char* rootpath, int che){
    char alaki[1000];
    strcpy(alaki, rootpath);
    strcat(alaki, "\\.samav\\commits\\");
    char tmp[100];
    sprintf(tmp, "%d.txt", che);
    strcat(alaki, tmp);
    FILE* file = fopen(alaki, "r");
    char red[1000];
    for(int i = 0; i < 5; i++){
        fgets(red, 1000, file);
    }
    char where[100]; // branch
    strcpy(where, red);
    where[strlen(where) - 1] = '\0';


    // Making Config Ok!:
    char br[1000];
    strcpy(br, rootpath);
    strcat(br, "\\.samav\\config.txt");
    FILE* bran = fopen(br, "r");
    char k[1000];
    strcpy(k, rootpath);
    strcat(k, "\\.samav\\1.txt");
    FILE* bran_cop = fopen(k, "w");
    char line[1000];
    while(fgets(line, 1000, bran)){
        if(strncmp(line, "branch =", 8) == 0){
            fprintf(bran_cop, "branch = %s", red);
        }
        else if(strncmp(line, "current_commit_id:", 18) == 0){
            fprintf(bran_cop, "current_commit_id: %d\n", che);
        }
        else{
            fprintf(bran_cop, line); 
        }
    }
    fclose(bran);
    fclose(bran_cop);
    char sd[1000] = "del \"";
    strcat(sd, br);
    strcat(sd, "\"");
    system(sd);
    char al[1000] = "move /Y \"";
    strcat(al, k);
    strcat(al, "\" \"");
    strcat(al, br);
    strcat(al, "\" > NUL");
    system(al);
    // OK!////
    for(int i = 0; i < 3; i++){
        fgets(red, 1000, file);
    }

    // READING THE FILES:
    while(fgets(red, 1000, file)){
        red[strlen(red) - 1] = '\0';
        char what[100];
        int which;
        sscanf(red, "%s %d", &what, &which);
        what[strlen(what) - 1] = '\0';
        cop_check(which, what, rootpath);
    }
    fclose(file);
    fprintf(stdout ,"____________________________________________________________\n");
    fprintf(stdout, "SAMAV : Checkout Was Succesful! Now You Are In Commit:\'%d\', Branch:\'%s\'\n", che, where);
    return;
}
// CHECKout Functions! /////////


// Tag functions: ///////
char** config_tag_read(char* rootpath){
    char** res = (char**) malloc(sizeof(char*) * 10);
    for(int i = 0; i < 10; i++){
        *(res + i) = (char*) malloc(sizeof(char) * 1000);
    }
    char salam[1000];
    strcpy(salam, rootpath);
    strcat(salam, "\\.samav\\config.txt");
    FILE* file = fopen(salam, "r");
    char line[1000];
    fgets(line, 1000, file);
    int a = strlen(line);
    line[a - 1] = '\0';
    strcpy(*(res + 0), line); //name
    res[0][a - 1] = '\0';
    fgets(line, 1000, file);
    a = strlen(line);
    line[a - 1] = '\0';
    strcpy(*(res + 1), line); //email
    res[1][a - 1] = '\0';
    while(fgets(line, 1000, file)){
        if(strncmp(line, "current_commit_id:", 18) == 0){
            sscanf(line, "current_commit_id: %s", *(res + 2)); // current
            fclose(file);
            return res;
        }
    }
}

void tag_maker(int argc, char* argv[], int state, char** tag, char* message, char* rootpath){
    char whe[1000];
    strcpy(whe, rootpath);
    strcat(whe, "\\.samav\\tags");
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(whe);

    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return;
    }

    int is = 0;
    while ((entry = readdir(dir)) != NULL) {
        if(strncmp(entry->d_name, argv[3], strlen(argv[3])) == 0){
            if(!state){
                fprintf(stdout, "SAMAV : A Tag With Name: \'%s\' is Already Exists! Please Choose A Different Name!\n", argv[3]);
                return 1;
            }
            else{
                is = 1;
                break;
            }
        }
    }
    closedir(dir);
    strcat(whe, "\\");
    strcat(whe, argv[3]);
    strcat(whe, ".txt");
    FILE* file = fopen(whe, "w");
    fprintf(file, "Commit: %s\n", *(tag + 2));
    fprintf(file, "Author: %s <%s>\n", *(tag + 0), *(tag + 1));
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);
    fprintf(file, "Date: %s", asctime(localTime));
    fprintf(file, "Message: %s\n", message);
    fclose(file);
    if(is){
        fprintf(stdout, "SAMAV : A Tag With Name: \'%s\' Has Been Overwrited!\n", argv[3]);
    }
    else{
        fprintf(stdout, "SAMAV : A Tag With Name: \'%s\' Has Been Saved!\n", argv[3]);
    }
    return;
}

int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void tag_name(int argc, char* argv[], char* rootpath){
    char whe[1000];
    strcpy(whe, rootpath);
    strcat(whe, "\\.samav\\tags");
    DIR *dir;
    struct dirent *entry;

    // Replace "directory_path" with the actual directory path you want to read
    dir = opendir(whe);

    if (dir == NULL) {
        perror("SAMAV : Error Opening Directory!");
        return;
    }

    int is = 0;
    char** name = (char**) malloc(sizeof(char*) * 20);
    for(int i = 0; i < 100; i++){
        *(name + i) = (char*) malloc(sizeof(char) * 100);
    }
    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0){
            char alaki[1000];
            strcpy(alaki, entry->d_name);
            strncpy(*(name + i), alaki, strlen(alaki) - 4);
            name[i][strlen(alaki) - 4] = '\0';
            i++;
        }
    }
    qsort(name, i, sizeof(char *), compareStrings);
    for(int j = 0; j < i; j++){
        fprintf(stdout, "%2dth) %s\n", j + 1,  name[j]);
    }
    fprintf(stdout ,"____________________________________________________________\n");
    fprintf(stdout, "SAMAV : You Have This(These) %d Tag(s) In Your Repository!\n", i);
    return;
}

void tag_show(int argc, char* argv[], char* rootpath){
    char alaki[1000];
    strcpy(alaki, rootpath);
    strcat(alaki, "\\.samav\\tags\\");
    strcat(alaki, argv[3]);
    strcat(alaki, ".txt");
    FILE* file = fopen(alaki, "r");
    char line[1000];
    fprintf(stdout, "SAMAV : Here Is A Tag With The Following Specifications:\n");
    fprintf(stdout ,"Tag_Name: %s\n", argv[3]);
    while(fgets(line, 1000, file)){
        fprintf(stdout, line);
    }
    return;
}
// Tag Functions: /////


// DIFF Functions: /////
int which_line(char* path, char* line){
    FILE* file = fopen(path, "r");
    char li[1000];
    int k = 0;
    while(fgets(li, 1000, file)){
        k++;
        li[strlen(li) - 1] = '\0';
        if(strcmp(li, line) == 0){
            return k;
        }
    }
    return -1;
}

void diff_files(char* path1, char* path2, int bg1, int en1, int bg2, int en2){
    FILE* file1 = fopen(path1, "r");
    FILE* file2 = fopen(path2, "r");
    char* f1 = (char*) malloc(sizeof(char) * 30000);
    char* f2 = (char*) malloc(sizeof(char) * 30000);
    char line[1000];
    for(int i = 1; i < bg1; i++){
        fgets(line, 1000, file1);
    }
    fgets(line, 1000, file1);
    strcpy(f1, line);
    for(int i = 1; i < bg2; i++){
        fgets(line, 1000, file2);
    }
    fgets(line, 1000, file2);
    strcpy(f2, line);
    for(int i = bg1; i < en1; i++){
        if(fgets(line, 1000, file1)){
            strcat(f1, line);
        }
    }
    for(int i = bg2; i < en2; i++){
        if(fgets(line, 1000, file2)){
            strcat(f2, line);
        }
    }
    fclose(file1);
    fclose(file2);


    char f1n[20][1000];
    char f2n[20][1000];
    int index11 = 0;
    int index21 = 0;
    for(int i = 0; i < strlen(f1); i++){
        if(*(f1 + i) == '\n'){
            f1n[index11][index21] = '\0';
            index21 = 0;
            index11++;
            while(*(f1 + i) == '\n' || *(f1 + i) == ' ' || *(f1 + i) == '\t'){
                i++;
            }
        }
        f1n[index11][index21] = *(f1 + i);
        index21++;
    }
    f1n[index11][index21 + 1] = '\0';

    int index12 = 0;
    int index22 = 0;
    for(int i = 0; i < strlen(f2); i++){
        if(*(f2 + i) == '\n'){
            f2n[index12][index22] = '\0';
            index22 = 0;
            index12++;
            while(*(f2 + i) == '\n' || *(f2 + i) == ' ' || *(f2 + i) == '\t'){
                i++;
            }
        }
        f2n[index12][index22] = *(f2 + i);
        index22++;
    }
    f2n[index12][index22 + 1] = '\0';
    // f2n , f2n Saved correctly

    int k = 0;
    if(index11 > index12){
        for(int i = 0; i < index11; i++){
            if(strcmp(f1n[i], f2n[i]) != 0){
                k = 1;
                fprintf(stdout, "<<<<<<<<\n");
                fprintf(stdout, "<%s>-<%d>\n", path1, which_line(path1, f1n[i]));
                fprintf(stdout, "%s\n", f1n[i]);
                fprintf(stdout, "<%s>-<%d>\n", path2, which_line(path2, f2n[i]));
                fprintf(stdout, "%s\n", f2n[i]);
                fprintf(stdout, ">>>>>>>>\n");
                fprintf(stdout ,"____________________________________________________________\n");
            }
        }
    }
    else{
        for(int i = 0; i < index12; i++){
            if(strcmp(f1n[i], f2n[i]) != 0){
                k = 1;
                fprintf(stdout, "<<<<<<<<\n");
                fprintf(stdout, "<%s>-<%d>\n", path1, which_line(path1, f1n[i]));
                fprintf(stdout, "%s\n", f1n[i]);
                fprintf(stdout, "<%s>-<%d>\n", path2 ,which_line(path2, f2n[i]));
                fprintf(stdout, "%s\n", f2n[i]);
                fprintf(stdout, ">>>>>>>>\n");
                fprintf(stdout ,"____________________________________________________________\n");
            }
        }
    }
    if(!k){
        fprintf(stdout, "SAMAV : File: \'%s\'And\nFile: \'%s\' Are Similar!\n", path1, path2);
        fprintf(stdout ,"____________________________________________________________\n");

    }
    return;
}

void com_diff(char* com1, char* com2, char* rootpath){
    char first[1000];
    strcpy(first, rootpath);
    strcat(first, "\\.samav\\commits\\");
    strcat(first, com1);
    strcat(first, ".txt");
    char second[1000];
    strcpy(second, rootpath);
    strcat(second, "\\.samav\\commits\\");
    strcat(second, com2);
    strcat(second, ".txt");
    FILE* file1 = fopen(first, "r");
    FILE* file2 = fopen(second, "r");
    char lin1[1000];
    char lin2[1000];
    for(int i = 0; i < 8; i++){
        fgets(lin1, 1000, file1);
        fgets(lin2, 1000, file2);
    }
    // NOw OK!
    int is = 0;
    while(fgets(lin1, 1000, file1)){
        is = 0;
        lin1[strlen(lin1) - 1] = '\0';
        char name1[100];
        char commit1[100];
        sscanf(lin1, "%s %s", &name1, &commit1);
        name1[strlen(name1) - 1] = '\0';
        while(fgets(lin2, 1000, file2)){
            lin2[strlen(lin2) - 1] = '\0';
            char name2[100];
            char commit2[100];
            sscanf(lin2, "%s %s", &name2, &commit2);
            name2[strlen(name2) - 1] = '\0';
            if(strcmp(name1, name2) == 0){
                char awal[1000];
                strcpy(awal, rootpath);
                strcat(awal, "\\.samav\\files\\");
                strcat(awal, name1);
                strcat(awal, ".txt\\");
                strcat(awal, commit1);
                strcat(awal, ".txt");
                char dowom[1000];
                strcpy(dowom, rootpath);
                strcat(dowom, "\\.samav\\files\\");
                strcat(dowom, name2);
                strcat(dowom, ".txt\\");
                strcat(dowom, commit2);
                strcat(dowom, ".txt");
                diff_files(awal, dowom, 1, line_counter(awal), 2, line_counter(dowom));
                rewind(file2);
                for(int i = 0; i < 8; i++){
                    fgets(lin2, 1000, file2);
                }
                is = 1;
                break;
            }
        }
        if(!is){
            fprintf(stdout, "SAMAV : File With Name: \'%s\' Is In Commit: \'%s\' But It's Not In Commit: \'%s\' !\n",name1, com1, com2);
            fprintf(stdout ,"____________________________________________________________\n");
        }
        rewind(file2);
        for(int i = 0; i < 8; i++){
            fgets(lin2, 1000, file2);
        }
    }
    rewind(file1);
    for(int i = 0; i < 8; i++){
        fgets(lin1, 1000, file1);
    }
    
    while(fgets(lin2, 1000, file2)){
        is = 0;
        lin2[strlen(lin2) - 1] = '\0';
        char name1[100];
        char commit1[100];
        sscanf(lin2, "%s %s", &name1, &commit1);
        name1[strlen(name1) - 1] = '\0';
        while(fgets(lin1, 1000, file1)){
            lin1[strlen(lin1) - 1] = '\0';
            char name2[100];
            char commit2[100];
            sscanf(lin1, "%s %s", &name2, &commit2);
            name2[strlen(name2) - 1] = '\0';
            if(strcmp(name1, name2) == 0){
                rewind(file1);
                for(int i = 0; i < 8; i++){
                    fgets(lin1, 1000, file1);
                }
                is = 1;
                break;
            }
        }
        if(!is){
            fprintf(stdout, "SAMAV : File With Name: \'%s\' Is In Commit: \'%s\' But It's Not In Commit: \'%s\' !\n",name1, com2, com1);
            fprintf(stdout ,"____________________________________________________________\n");
        }
        rewind(file1);
        for(int i = 0; i < 8; i++){
            fgets(lin1, 1000, file1);
        }
    }
    return;
}
// Diff Functions! /////







int main(int argc, char* argv[]){
    // Less Than 2 Inputs:
    if (argc < 2){
        fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!\n");
        return 1;
    }

    char Current[1024];
    if(getcwd(Current, sizeof(Current)) == NULL) {fprintf(stdout, "SAMAV : There Is An Unknown Error Please Try Again!\n"); return 1;}
    char* Samav_Root;
    Samav_Root = samav_exist(argc, argv);
    char** config = config_reader(Samav_Root);
    int last_commit = config_commit(Samav_Root);

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
                    file_1 = fopen("stage_copy.txt", "w");
                    fclose(file_1);
                    mkdir("adds");
                    mkdir("commits");
                    mkdir("files");
                    mkdir("tags");
                    mkdir("branches");
                    chdir("branches");
                    mkdir("master");
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
                file_1 = fopen("stage_copy.txt", "w");
                fclose(file_1);
                mkdir("commits");
                mkdir("adds");
                mkdir("files");
                mkdir("tags");
                mkdir("branches");
                chdir("branches");
                mkdir("master");
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
        if(argc < 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
        if(strcmp(argv[2], "-global") == 0){
            if(argc < 5){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            // User.Name:
            if(strcmp(argv[3], "user.name") == 0){
                if(!global_writter(argc, argv, 1, argv[4], 1))
                fprintf(stdout, "SAMAV : A Global Name: \"%s\" Has Been Saved Successfully!", argv[4]);
                if(Samav_Root != NULL){
                    char ds[1000];
                    char ds_cpy[1000];
                    strcpy(ds, Samav_Root);
                    strcpy(ds_cpy, Samav_Root);
                    strcat(ds_cpy, "\\.samav\\config_cpy.txt");
                    strcat(ds, "\\.samav\\config.txt");
                    FILE* file = fopen(ds, "r");
                    FILE* file_cpy = fopen(ds_cpy, "w");
                    char line[1000];
                    fgets(line, 1000, file);
                    fprintf(file_cpy, argv[4]);
                    fprintf(file_cpy, "\n");
                    while(fgets(line, 1000, file)){
                        fprintf(file_cpy, line);
                    }
                    fclose(file);
                    fclose(file_cpy);
                    strcpy(line, "del ");
                    strcat(line, ds);
                    system(line);
                    strcpy(line, "rename ");
                    strcat(line, ds_cpy);
                    strcat(line, " config.txt");
                    system(line);
                }
                return 0;
            }
            // User.Email:
            if(strcmp(argv[3], "user.email") == 0){
                if(!global_writter(argc, argv, 2, argv[4], 1))
                fprintf(stdout, "SAMAV : A Global Email: \"%s\" Has Been Saved Successfully!", argv[4]);
                if(Samav_Root != NULL){
                    char ds[1000];
                    char ds_cpy[1000];
                    strcpy(ds, Samav_Root);
                    strcpy(ds_cpy, Samav_Root);
                    strcat(ds_cpy, "\\.samav\\config_cpy.txt");
                    strcat(ds, "\\.samav\\config.txt");
                    FILE* file = fopen(ds, "r");
                    FILE* file_cpy = fopen(ds_cpy, "w");
                    char line[1000];
                    fgets(line, 1000, file);
                    fprintf(file_cpy, line);
                    fgets(line, 1000, file);
                    fprintf(file_cpy, argv[4]);
                    fprintf(file_cpy, "\n");
                    while(fgets(line, 1000, file)){
                        fprintf(file_cpy, line);
                    }
                    fclose(file);
                    fclose(file_cpy);
                    strcpy(line, "del ");
                    strcat(line, ds);
                    system(line);
                    strcpy(line, "rename ");
                    strcat(line, ds_cpy);
                    strcat(line, " config.txt");
                    system(line);
                }
                return 0;
            }
            // Alias:
            if(strncmp(argv[3], "alias.", 6) == 0){
                // LATER//
                return 0;
            }
        
        }
        // Just This Project:
        else{
            // User.Name:
            if(strcmp(argv[2], "user.name") == 0){
                if(!global_writter(argc, argv, 1, argv[3], 0))
                fprintf(stdout, "SAMAV : A Local Name: \"%s\" Has Been Saved Successfully!", argv[3]);
                if(Samav_Root != NULL){
                    char ds[1000];
                    char ds_cpy[1000];
                    strcpy(ds, Samav_Root);
                    strcpy(ds_cpy, Samav_Root);
                    strcat(ds_cpy, "\\.samav\\config_cpy.txt");
                    strcat(ds, "\\.samav\\config.txt");
                    FILE* file = fopen(ds, "r");
                    FILE* file_cpy = fopen(ds_cpy, "w");
                    char line[1000];
                    fgets(line, 1000, file);
                    fprintf(file_cpy, argv[3]);
                    fprintf(file_cpy, "\n");
                    while(fgets(line, 1000, file)){
                        fprintf(file_cpy, line);
                    }
                    fclose(file);
                    fclose(file_cpy);
                    strcpy(line, "del ");
                    strcat(line, ds);
                    system(line);
                    strcpy(line, "rename ");
                    strcat(line, ds_cpy);
                    strcat(line, " config.txt");
                    system(line);
                }
                return 0;
            }
            // User.Email:
            if(strcmp(argv[2], "user.email") == 0){
                if(!global_writter(argc, argv, 2, argv[3], 0))
                fprintf(stdout, "SAMAV : A Local Email: \"%s\" Has Been Saved Successfully!", argv[3]);
                if(Samav_Root != NULL){
                    char ds[1000];
                    char ds_cpy[1000];
                    strcpy(ds, Samav_Root);
                    strcpy(ds_cpy, Samav_Root);
                    strcat(ds_cpy, "\\.samav\\config_cpy.txt");
                    strcat(ds, "\\.samav\\config.txt");
                    FILE* file = fopen(ds, "r");
                    FILE* file_cpy = fopen(ds_cpy, "w");
                    char line[1000];
                    fgets(line, 1000, file);
                    fprintf(file_cpy, line);
                    fgets(line, 1000, file);
                    fprintf(file_cpy, argv[3]);
                    fprintf(file_cpy, "\n");
                    while(fgets(line, 1000, file)){
                        fprintf(file_cpy, line);
                    }
                    fclose(file);
                    fclose(file_cpy);
                    strcpy(line, "del ");
                    strcat(line, ds);
                    system(line);
                    strcpy(line, "rename ");
                    strcat(line, ds_cpy);
                    strcat(line, " config.txt");
                    system(line);
                }
                return 0;
            }
            // Alias:
            if(strncmp(argv[2], "alias.", 6) == 0){
                // LATER//
                return 0;
            }
        }
    }

    // All The samav add:
    else if(strcmp(argv[1], "add") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc < 3){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
        strcat(Samav_Root, "\\.samav");
        chdir(Samav_Root);
        if(strcmp(argv[2], "-f") == 0){
            for(int i = 3; i < argc; i++){
                Add_to_stage_file_mod_simple(argc, argv, argv[i], Samav_Root);
            }
            FILE* file = fopen("stage.txt", "r");
            char alaki[1000];
            while(fgets(alaki, 1000, file)){continue;}
            fclose(file);
            if(strcmp(alaki, "a\n") != 0){
                file = fopen("stage.txt", "a");
                fprintf(file, "a\n");
                fclose(file);
                file = fopen("stage_copy.txt", "a");
                fprintf(file, "a\n");
                fclose(file);
            }
            return 0;
        }
        if(strcmp(argv[2], "-n") == 0){
            int num = str_num(argv[3]);
            Add_with_depth(argc, argv, num, Samav_Root, Samav_Root);
            return 0;
        }
        if(strcmp(argv[2], "-redo") == 0){
            redo_in_add(argc, argv, Samav_Root);
            return 0;
        }
        else{
            Add_to_stage_file_mod_simple(argc, argv, argv[2], Samav_Root);
            FILE* file = fopen("stage.txt", "r");
            char alaki[1000];
            while(fgets(alaki, 1000, file)){continue;}
            fclose(file);
            if(strcmp(alaki, "a\n") != 0){
                file = fopen("stage.txt", "a");
                fprintf(file, "a\n");
                fclose(file);
                file = fopen("stage_copy.txt", "a");
                fprintf(file, "a\n");
                fclose(file);
            }
            return 0;
        }
    }
    
    // All The samav reset:
    else if(strcmp(argv[1], "reset") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc < 3){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
        strcat(Samav_Root, "\\.samav");
        chdir(Samav_Root);
        if(strcmp(argv[2], "-undo") == 0){
            undo_reset(argc, argv, Samav_Root);
            return 0;
        }
        else if(strcmp(argv[2], "-f") == 0){
            for(int i = 3; i < argc; i++){
                reset_file_mod_simple(argc, argv, argv[i], Samav_Root);
            }
            return 0;
        }
        else{
            reset_file_mod_simple(argc, argv, argv[2], Samav_Root);
            return 0;
        }
    }
    
    // All The samav status:
    else if(strcmp(argv[1], "status") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        char alaki[1000];
        strcpy(alaki, Samav_Root);
        strcat(alaki, "\\.samav");
        folder_reader(argc, argv, alaki, Samav_Root);
        strcat(alaki, "\\commits\\");
        char tmp[100];
        sprintf(tmp, "%d.txt", last_commit);
        strcat(alaki, tmp);
        int a = line_counter(alaki);
        Delete_commit(argc, argv, a - 8, Samav_Root, alaki);
        return 0;
    }
 
    // All The samav commit:
    else if(strcmp(argv[1], "commit") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc < 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
        if(strlen(argv[3]) > 72){fprintf(stdout, "SAMAV : Your Message Has %d Character And It's Over Limit (72)!\nPlease Choose A Shorter Message!", strlen(argv[3])); return 1;}
        char alaki[1000];
        strcpy(alaki, Samav_Root);
        strcat(alaki, "\\.samav");
        chdir(alaki);
        run_commit(argc, argv, Samav_Root);
    }
    
    // All the samav log:
    else if(strcmp(argv[1], "log") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc == 2){
            run_log(argc, argv, Samav_Root, last_commit, last_commit - 999999);
            return 0;
        }
        if(strcmp(argv[2], "-n") == 0){
            int num = str_num(argv[3]);
            run_log(argc, argv, Samav_Root, last_commit, num);
            return 0;
        }
        if(strcmp(argv[2], "-branch") == 0){
            if(argc != 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            commit_in_branch(argc, argv, argv[3], Samav_Root);
            return 0;
        }
        if(strcmp(argv[2], "-author") == 0){
            if(argc != 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            author_in_log(argc, argv, argv[3], Samav_Root, last_commit);
            return 0;
        }
        if(strcmp(argv[2], "-since") == 0){
            if(argc != 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            int h, m;
            sscanf(argv[3], "%d:%d", &h, &m);
            int sum = (60 * h) + m;
            time_in_log(argc, argv, sum, Samav_Root, last_commit, 1, h, m);
            return 0;
        }
        if(strcmp(argv[2], "-before") == 0){
            if(argc != 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            int h, m;
            sscanf(argv[3], "%d:%d", &h, &m);
            int sum = (60 * h) + m;
            time_in_log(argc, argv, sum, Samav_Root, last_commit, 2, h, m);
            return 0;
        }
        if(strcmp(argv[2], "-search") == 0){
            if(argc < 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            search_message(argc, argv, last_commit, Samav_Root);
            return 0;
        }

        
    }
    
    // All The samav branch:
    else if(strcmp(argv[1], "branch") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc == 3){
            return branch_maker(argc, argv, Samav_Root);
        }
        if(argc == 2){
            return branch_show(argc, argv, Samav_Root);
        }
        else{fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
    }

    // All The samav checkout:
    else if(strcmp(argv[1], "checkout") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc < 3){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
        char where[1000];
        strcpy(where, Samav_Root);
        strcat(where, "\\.samav\\stage.txt");
        if(line_counter(where) != 0 && line_counter(where) != 1){
            fprintf(stdout, "SAMAV : You Can't Checkout to \'%s\' ! Because You Have File(s) That Are Not Committed Yet!\nPlease Use Commit Operation First!\n", argv[2]);
            return 1;
        }
        if(strcmp(argv[2], "HEAD") == 0){
            if(argc > 3){
                if(strcmp(argv[3], "-n") == 0){
                    int a = str_num(argv[4]);
                    if(a > last_commit - 1000000){
                        fprintf(stdout, "SAMAV : You Can't Checkout To Commit Id: %d ! This Id Doesn't Exist!\n", last_commit - a);
                        return 1;
                    }
                    run_check(argc, argv, Samav_Root, last_commit - a);
                    return 0;
                }
            }
            int che = last_commit;
            run_check(argc, argv, Samav_Root, che);
            return 0;
        }
        if(argv[2][0] == '1'){
            int che = str_num(argv[2]);
            run_check(argc, argv, Samav_Root, che);
            return 0;
        }
        else{
            int che = max_in_commit(Samav_Root, argv[2]);
            run_check(argc, argv, Samav_Root, che);
            return 0;
        }
    }
    
    // All The samav tag:
    else if(strcmp(argv[1], "tag") == 0){
        if(argc == 2){
            tag_name(argc, argv, Samav_Root);
            return 0;
        }
        if(strcmp(argv[2], "show") == 0){
            if(argc != 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            tag_show(argc, argv, Samav_Root);
            return 0;
        } 
        if(argc >= 4){
            int state = 0; // -f
            char** tag = config_tag_read(Samav_Root);
            char mess[100] = "No Message!";
            for(int i = 4; i < argc; i++){
                if(strcmp(argv[i], "-m") == 0){
                    if(i == argc - 1){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
                    strcpy(mess, argv[i + 1]);
                }
                else if(strcmp(argv[i], "-c") == 0){
                    if(i == argc - 1){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
                    strcpy(*(tag + 2), argv[i + 1]);
                }
                else if(strcmp(argv[i], "-f") == 0){
                    state = 1;
                }
            }
            tag_maker(argc, argv, state, tag, mess, Samav_Root);
            return 0;
        }
        fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!");
        return 1;
    }

    // All The samav diff:
    else if(strcmp(argv[1], "diff") == 0){
        if(strcmp(argv[2], "-f") == 0){
            if(argc < 5){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            if(argc == 5){
                strcat(Samav_Root, "\\.samav");
                chdir(Samav_Root);
                diff_files(argv[3], argv[4], 1, line_counter(argv[3]) , 1, line_counter(argv[4]));
                return 0;
            }
            int bg1, en1, bg2, en2;
            sscanf(argv[6], "%d-%d", &bg1, &en1);
            sscanf(argv[8], "%d-%d", &bg2, &en2);
            diff_files(argv[3], argv[4], bg1, en1 , bg2, en2);
            return 0;
        }
        if(strcmp(argv[2], "-c") == 0){
            if(argc != 5){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
            com_diff(argv[3], argv[4], Samav_Root);
            return 0;
        }
    }



    return 0;
}
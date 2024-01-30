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
int Add_with_depth(int argc, char* argv[], int depth, char* pathfile);
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
long long directory_reader(char* name, char* rootpath);
void write_name_commit(char* file, char* rootpath);
int status(int argc, char* argv[], int state, char* path);


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
    // alaki\slaki.txt 14 
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
                char path_nothing[1000] = "adds\\";
                // int i = strlen(line_wild) - 1;
                // int j = 0;
                // char nothing[100];
                // while(line_wild[i] != '\\'){
                //     nothing[j] = line_wild[i];
                //     i--;
                //     j++;
                // }
                // char nothing2[100];
                // for(int i = 0; i < j; i++){
                //     nothing2[i] = nothing[j - i - 1];
                // }
                // nothing2[j] = '\0';
                strcat(path_nothing, line_wild);
                if(check_difference(line_wild, path_nothing) == 1){
                    fprintf(stdout , "SAMAV : File With Address: \'%s\' Exists! Please Use Commit Operation!\n", line_wild);
                    exist = 1;
                    break;
                }
                else{
                    // Delete:
                    chdir("adds");
                    char operation[1000] = "del ";
                    // int i = strlen(line_wild) - 1;
                    // int j = 0;
                    // char nothing[100];
                    // while(line_wild[i] != '\\'){
                    //     nothing[j] = line_wild[i];
                    //     i--;
                    //     j++;
                    // }
                    // char nothing2[100];
                    // for(int i = 0; i < j; i++){
                    //     nothing2[i] = nothing[j - i - 1];
                    // }
                    // nothing2[j] = '\0';
                    strcat(operation, wildcard);
                    system(operation);
                    chdir("..");
                    // copy:
                    strcpy(operation, "copy ");
                    strcat(operation, line_wild);
                    strcat(operation, " adds > NUL");
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
    // char line_reader[1024];
    // strcpy(line_reader, rootpath);
    // strcat(line_reader, "\\.samav\\stage.txt");
    FILE* file_find = fopen("stage.txt", "r");
    int exist = 0;
    char* fileName = end(argc, argv, filepath);
    char line_read[1000];
    while(fgets(line_read, 1000, file_find)){
        line_read[strlen(line_read) - 1] = '\0';
        if(strcmp(line_read, fileName) == 0){
            char path_nothing[1000] = "adds\\";
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
            strcat(path_nothing, fileName);
            if(check_difference(filepath, path_nothing) == 1){
                fprintf(stdout , "SAMAV : File With Address: \'%s\' Exists! Please Use Commit Operation!\n", filepath);
                exist = 1;
                break;
            }
            else{
                // Delete:
                chdir("adds");
                char operation[1000] = "del ";
                strcat(operation, fileName);
                system(operation);
                chdir("..");
                // copy:
                strcpy(operation, "copy ");
                strcat(operation, filepath);
                strcat(operation, " adds > NUL");
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








// Add with Depth:
int Add_with_depth(int argc, char* argv[], int depth, char* pathfile){
    if(depth == 0){return 0;}
    // Later:
}

// Status:
int status(int argc, char* argv[], int state, char* path){
    if(Is_Directory(path) == 1){

    }
}

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
    printf("%s\n", operation);
    system(operation);

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


////////////////////// ALL THE WORK WE SHOULD DO IN COMMIT : ///////////////////

int run_commit(int argc, char* argv[], char* root_path) {

    char message[73];
    strcpy(message, argv[3]);
    char path[1000];
    char path2[1000];
    strcpy(path, root_path);
    strcpy(path2, root_path);
    strcat(path2, "\\.samav\\stage_copy.txt");
    strcat(path, "\\.samav\\stage.txt");
    if(line_counter(path) == 0){
        fprintf(stdout, "SAMAV : There Is No File In Staging Area To Commit!\nPlease Use \'samav add (Address)\' Operation First!\n");
        return 1;
    } 
    

    int commit_ID = inc_last_commit_ID(root_path);
    printf("salam\n");
    if (commit_ID == -1) return 1;
    FILE *file = fopen(path, "r");
    FILE * file_copy = fopen(path2, "r");
    if (file == NULL) return 1;
    char line[1024];
    char line2[1024];
    int q = 1;
    while (fgets(line, sizeof(line), file) && fgets(line2, sizeof(line2), file_copy)) {
        int length = strlen(line);
        line2[strlen(line2) - 1] = '\0';

        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        
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
    fprintf(stdout, "SAMAV : Commit Was Successfully Done With Commit ID: %d\n%d File(s) Has Been Tracked!\n", commit_ID, q - 1);
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
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "last_commit_id:", 15) == 0) {
            sscanf(line, "last_commit_id: %d\n", &last_commit_ID);
            last_commit_ID++;
            fprintf(tmp_file, "last_commit_id: %d\n", last_commit_ID);

        } else fprintf(tmp_file, "%s", line);
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
    time = fopen(op, "w");
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
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0){
            stat(entry->d_name, &st);
            fprintf(fptr,"%s: %d\n", entry->d_name, directory_reader(entry->d_name, rootpath));
        }
    }
    closedir(dir); 
    fclose(fptr);
    return 0;
}

// Max Of A Directory Files:
long long directory_reader(char* name, char* rootpath){
    struct dirent *de;  // Pointer for directory entry
    char alaki[1000];
    strcpy(alaki, rootpath);
    strcat(alaki, "\\.samav\\files\\");
    strcat(alaki, name);
    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(alaki);

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
            char alak[1000];
            strcpy(alak, de->d_name);
            sscanf(alak, "%lld.txt", &tmp);
            if(tmp > max){
                max = tmp;
            }
        }
    }
    closedir(dr);     // close directory

    return max;
}

////////////////////// ALL THE WORK WE SHOULD DO IN COMMIT : ///////////////////

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



int main(int argc, char* argv[]){
    // Less Than 2 Inputs:
    if (argc < 2){
        fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!");
        return 1;
    }

    char Current[1024];
    if(getcwd(Current, sizeof(Current)) == NULL) {fprintf(stdout, "SAMAV : There Is An Unknown Error Please Try Again!"); return 1;}
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
                    mkdir("adds");
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
                mkdir("adds");
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
        if(argc < 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
        if(strcmp(argv[2], "-global") == 0){
            if(argc < 5){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
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
                return 0;
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
            return 0;
        }
        if(strcmp(argv[2], "-n") == 0){
            //Later:
            return 0;
        }
        if(strcmp(argv[2], "-redo") == 0){
            // Later:
            return 0;
        }
        else{
            return Add_to_stage_file_mod_simple(argc, argv, argv[2], Samav_Root);
        }
    }
    
    // else if(strcmp(argv[1], "reset") == 0){
    //     if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
    //     if(argc < 3){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
    //     if(strcmp(argv[2], "-undo") == 0){
    //         return 0;
    //     }
    // }
    else if(strcmp(argv[1], "commit") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc < 4){fprintf(stdout , "SAMAV : Please Insert A Complete Operation!\nNOTE: Use \"samav help\" To Know All The Operations!"); return 1;}
        if(strlen(argv[3]) > 72){fprintf(stdout, "SAMAV : Your Message Has %d Character And It's Over Limit (72)!\nPlease Choose A Shorter Message!", strlen(argv[3])); return 1;}
        char alaki[1000];
        strcpy(alaki, Samav_Root);
        strcat(alaki, "\\.samav");
        chdir(alaki);
        return run_commit(argc, argv, Samav_Root);
    }
    else  if(strcmp(argv[1], "log") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc == 2){
            run_log(argc, argv, Samav_Root, last_commit, last_commit - 999999);
            return 0;
        }
        if(strcmp(argv[2], "-n") == 0){
            run_log(argc, argv, Samav_Root, last_commit, (int)argv[3]);
            return 0;
        }
        if(strcmp(argv[2], "-branch") == 0){

            return 0;
        }
        
        
    }
    else  if(strcmp(argv[1], "branch") == 0){
        if(Samav_Root == NULL){fprintf(stdout ,"SAMAV : You Don't Have Any Initilized Repository. Please Use This Operation First:\nsamav init\nThen Try Again Later!"); return 1;}
        if(argc == 3){
            return branch_maker(argc, argv, Samav_Root);
        }
        if(argc == 2){
            return branch_show(argc, argv, Samav_Root);
        }
    }

    
    return 0;
}






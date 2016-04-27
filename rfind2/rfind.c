//
//  rfind.c
//  rfind
//
//    Unix程序设计第二次作业 rfind
//    国际软件学院
//    2015302580244
//    陈俊达
//
//    Stay hungry, stay foolish.

//

#include "rfind.h"

int rfind(int argc, const char * argv[]) {

    THROWPERROR(argc != 4 && argc != 6, USAGE);
    const char * fname = NULL, *content = NULL , * path = NULL;
    
    for (int i = 0; i < argc-1; i++) {
        strcmp(argv[i], "-name")    == 0  &&  ( fname   = argv[i+1] )   ;
        strcmp(argv[i], "-content") == 0  &&  ( content = argv[i+1] )   ;
    }
    path = (fname && content) ? argv[5] : argv[3] ;
    
    if (fname && content) {
        readFileContent(path, content);
    }
    
    if (fname) { readDir(path, fname);   return 0; }
    
    if (content) { readFileContent(path, content); return 0; }
    
    THROWPERROR((!fname && !content), USAGE);
    
    return 0;
}

#pragma Read File in Name Specified
int readFileInNameSpecified ( const char * path, const char * fname, const char * content )
{
    DIR  * dirc = opendir(path);
    struct dirent   * dir;
    char * newpath = malloc(256 * sizeof(char));
    
    while ( (dir = readdir(dirc)) ) {
        
        if (fnmatch(fname, dir->d_name, FNM_PATHNAME|FNM_PERIOD) == 0) {
            const char * npath = malloc(strlen(fname)*sizeof(char));
            formPath(npath, fname, dir->d_name);
            if ( fileCheck(npath, content) ) {dump_entry(dir, path);}
        }
        if (NOT_PARENT_OR_SELF(dir->d_name) && (dir->d_type & DT_DIR)) {
            formPath(newpath, path, dir->d_name);
            readDir(newpath, fname);
        }
        
    }
    
    return 0 ;
}


#pragma Read Directory

int readDir(const char * path,  const char * fname)
{
    DIR  * dirc = opendir(path);
    struct dirent   * dir;
    char * newpath = malloc(256 * sizeof(char));
    
    while ( (dir = readdir(dirc)) ) {
        
        if (fnmatch(fname, dir->d_name, FNM_PATHNAME|FNM_PERIOD) == 0) {
            dump_entry(dir, path);
        }
        if (NOT_PARENT_OR_SELF(dir->d_name) && (dir->d_type & DT_DIR)) {
            formPath(newpath, path, dir->d_name);
            readDir(newpath, fname);
        }
        
    }
    
    return 0 ;
};

#pragma Read Content In File

int readFileContent(const char * path ,const char * content)
{
    DIR * dirc = opendir(path);
    struct dirent * dir;
    char * newpath = malloc(256 * sizeof(char));
    
    while ( (dir = readdir(dirc)) ) {
        if ( ! (NOT_PARENT_OR_SELF(dir->d_name)) ) {continue;}
        if( (dir->d_type & DT_DIR)) {
            formPath(newpath, path, dir->d_name);
            readFileContent(newpath, content);
            continue;
        }
        formPath(newpath, path, dir->d_name);
        int result = fileCheck(newpath, content);
        if(result == 0) { dump_entry(dir, path); }
    }
    return 0;
}


int fileCheck(const char * fpath, const char * content)
{
    FILE * fd = fopen(fpath, "r");  THROWPERROR(!fd, "");
    struct stat * status;   stat(fpath, status);
    char * buff = malloc(sizeof(char) * status->st_size);
    
    fread (buff, sizeof(char), status->st_size, fd);
    
    if (regex_match(buff, content) == 0 ) {
        THROWPERROR(fclose(fd), "");
        return 0;
    }

    THROWPERROR(fclose(fd), "");
    return 1;
}


#pragma Utility

const char * formPath(char * dest, char * old, const char * move)
{
    char * cpold = malloc( 256 * sizeof(old) ) ; strcpy(cpold, old);
    strcpy(dest, strcat(strcat(cpold, "/"), move));
    return dest;
}

void dump_entry(struct dirent *entry, const char * path)
{
    int type = entry->d_type;
    char *text = "???";
    
    if (type == DT_BLK)
        text = "block device";
    
    if (type == DT_CHR)
        text = "character device";
    
    if (type ==  DT_DIR)
        text = "directory";
    
    if (type == DT_FIFO)
        text = "named pipe";
    
    if (type == DT_LNK)
        text = "symbolic link";
    
    if (type == DT_REG)
        text = "regular file";
    
    if (type == DT_SOCK)
        text = "unix domain socket";
    
    if (type == DT_UNKNOWN)
        text = "unknown";
    
    printf("%-15s%s/%s\n", text ,path, entry->d_name);
}


int regex_match(const char * target, const char * pattern)
{
    int    status;
    regex_t    re;
    
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0){ return 1; }
    
    status = regexec(&re, target, (size_t) 0, NULL, 0);
    regfree(&re);
    
    if (status != 0) {
        return 1;
    }
    return 0;
}



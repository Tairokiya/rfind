//
//  rfind.h
//  rfind2
//
//  Created by Mike on 16/4/28.
//  Copyright © 2016年 陈俊达. All rights reserved.
//

#ifndef rfind_h
#define rfind_h

#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <dirent.h>
#include <fnmatch.h>



int rfind(int argc, const char * argv[]) ;



//  Macro function:
//  NOT_PARENT_OR_SELF(name) :  Ignore "." , ".." , ".DS_Store"(in Mac OS)
#define NOT_PARENT_OR_SELF(name)                \
(   (   strcmp(name,".")            ) &&        \
(   strcmp(name,"..")           ) &&        \
(   strcmp(name,".DS_Store" )   )           \
)

#define THROWPERROR(condition,str) {if(condition) {perror(str); return 1;}}
#define USAGE "Usage : rfind [-name] [filename] [-content] [regular expr] \nPlacement of options are ignored \n"

// Match regular expresion
int         regex_match     (const char * target, const char * pattern);
// Match filetype and print out
void        dump_entry      (struct dirent *entry, const char * path);
// Generate path in case accident happen
const char* formPath        (char * dest, char * old, const char * move);
// Check whether file has the pattern string as shown in content
int         fileCheck       (const char * fpath, const char * content);

// Main methods
int                 readDir (const char * path,  const char * fname); //[-name]
int         readFileContent (const char * path , const char * content);//[-content]
int readFileInNameSpecified (const char * path , const char * fname, const char * content );//[both]



#endif /* rfind_h */

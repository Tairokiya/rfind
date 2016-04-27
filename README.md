Unix程序设计作业 `rfind` 
===

**NAME**  `rfind`  —trivially find a file with a specific name or content  

**SYNOPSIS**   
`rfind [-name] filename [-content] startingdir ` 

**DESCRIPTION**  
The `rfind` utility finds the targeted files according to the **[name-mode]** or **[content-mode]** recursively.
The starting point is a specified directory. If the meta-character * is used, all the matched files must be located.  


**EXAMPLES**  
The following examples show common usage:  
`rfind -name test.txt .  
`
`rfind -content stdio.h /  
`
`rfind -name *.txt /dev  
`
`rfind -content put*() /home/chenzuolin `
`rfind -content "Hello World" /home/chenzuolin  `
`rfind -content get*() -name *.c /home/chenzuolin  `  

**EXIT STATUS**  
rfind exits 0 on success, and >0 if an error occurred.  

**SEE ALSO**  
opendir(3), readdir(2), read(2), strcmp(3)
NOTES

The code for the rfind utility is, of course, well-formatted and can be compiled using the -Wall flags without any errors or warnings.

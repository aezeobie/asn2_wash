//This is my code
//Andrea Ezeobiejesi
//CS366
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
int copyDir();
int copyFile();
int rename();
int delete();
int zeroLength();
int appendFile();
int display100(); //tail command ... tail -n  4 commmand;; fseek(fin, -2, SEEK_CUR)
int changePermisson();
int changeTime();
int goToNext();
int quit();
void printFile(char []);
/* purpose: Command Line Interface - Reads files from the
 * command line and parses user commands. Based on input
 * from the user, call the appropriate function. 
 * input: command line arguments
 * returns: output corresponding to the command issued
 */
int main(int argc, char *argv[])
{
// FILE *f;
// copyDir();
//Skip over the first arg, a.out
// for i< argc; i++
// printf("%s",argv[i]);
  printFile(argv[1]);
  return 0;
}

//Print file read in from command line
//WORKS!! :)
void printFile(char* file)
{
  printf("The file you entered is %s\n", file);
}


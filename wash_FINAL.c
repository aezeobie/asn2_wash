//This is my code
//Andrea Ezeobiejesi
//CS366
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
int catFile();
int copyFile();
int renameFile();
int delete();
int zeroLength();
int appendFile();
int displayTail(); 
int changePermission();
int changeTime(); 
void printFile();
/**
 * purpose: Run file IO functions that correspond to user input
 * commands the result array for correctness 
 * input: argument count, char array of arguments read from command
 * line
 */
int main(int argc, char *argv[])
{
  char file[50];
  char command = ' ';
  char fileArray[100][50];
  int numFiles = argc;
  
  for(int i = 1; i < argc; i++)
  { 
    strcpy(fileArray[i], argv[i]);
  }   
  
  for(int j = 1; j < numFiles; j++)
  {
    strcpy(file, fileArray[j]);
    do   
    {
      printf("File %s: command: ", fileArray[j]);
      scanf(" %c", &command);   
      if(command == 'c')
      {
        catFile(file); 
      }
      else if(command == 'd')
      {
        copyFile(file);
      }
      else if(command =='r')
      {
        renameFile(file);
      }
      else if(command =='u')
      {
        delete(file);
      }
      else if(command =='t')
      {
        zeroLength(file);
      }
      else if(command == 'a')
      {
        appendFile(file);
      }
      else if(command =='l')
      {
        displayTail(file);
      }
      else if(command =='m')
      {
        changePermission(file);
      }
      else if(command =='x')
      {
        changeTime(file);
      }
      else if(command =='q')
      {
        exit (0);  
      }    
    }while(command != 'n');
  }
   return 0; 
}   

/**
 * purpose: List the current file to /dev/tty
 * input: file name 
 * output: nothing(prints current file to the terminal)
 */
int catFile(char* file)
{
  FILE *commandLine = fopen("/dev/tty", "w");
  fprintf(commandLine, "The current file is: %s\n", file);
  return 0;
}

/**
 * purpose: Make a copy of the current file
 * input: file name
 * output: duplicated file
 */
int copyFile(char* file)
{
  char fileStream;
  char destination[50] = " ";
  FILE *sourceFile;
  FILE *copiedFile;
  sourceFile = fopen(file, "r"); //Open file to copy
  
  printf("Enter destination name: ");
  scanf("%s", destination);
  printf("Destination file: %s\n", destination);
  copiedFile = fopen(destination, "w+"); 

  while(1)
  {
    if((fileStream = fgetc(sourceFile)) == EOF) 
    {
      break;
    }
    else
    {
      fputc(fileStream, copiedFile);
    }
  } 
  printf("Your file was successfully copied!\n");   
   
  fclose(sourceFile);
  fclose(copiedFile);
    
  return 0;
} 

/**
 * purpose: Rename the curent file
 * input: file name
 * output: nothing(changes the name of the current file)
 */
int renameFile(char* oldFile)
{
  int success;
  char newFile [50]; 
  printf("Current filename: %s\n", oldFile);
  
  printf("Enter new filename: ");
  scanf("%s", newFile);
  printf("New file name: %s\n", newFile);
  success = rename(oldFile, newFile);
  if(success == 0) 
  {
    printf("File renamed successfully!\n");
  }
  else 
  {
    perror("rename");
    printf("Error: unable to rename the file\n");
  }
  return 0;
}

/**
 * purpose: Delete the current file
 * input: file name
 * output: nothing(unlinks the current file)
 */
int delete(char* file)
{
  int DELETED = 0;
 
  printf("Name of file to delete: %s\n", file);
  DELETED = remove(file);
  if(DELETED == 0)
  {
    printf("The file %s was successfully deleted!! :)\n", file);
  }
  else
  {
    perror("remove");
    fprintf(stderr, "There was an error deleting the file %s.\n", file);
  }
}

/**
 * purpose: Zero the current file
 * input: file name
 * output: nothing(clears the contents of the file)
 */
int zeroLength(char* file)
{
  int ZEROED = 0;
  ZEROED = truncate(file, 0);
  if(ZEROED == 0)
  {
    printf("Your file %s was cleared! :)\n", file);
  }
  else
  {
    perror("truncate");
    printf("There was an error while clearing the file %s\n", file);
  }
}

/**
 * purpose: Append the current file to another file
 * input: file name
 * output: nothing(appends contents of current file to another)
 */
int appendFile(char* file)
{
  char fileStream;
  char destination[50] = " ";
  FILE *sourceFile;
  FILE *appendFile;
  sourceFile = fopen(file, "r"); //Open file to read
  
  printf("Enter file to append: ");
  scanf("%s", destination);
  printf("Destination file: %s\n", destination);
  appendFile = fopen(destination, "a");  

  while(1)
  {
    if((fileStream = fgetc(sourceFile)) == EOF) 
    {
      break;
    }
    else
    {
      fputc(fileStream, appendFile);
    }
  } 
  printf("Your file was successfully appended!\n");   
   
  fclose(sourceFile);
  fclose(appendFile);
    
  return 0;
}

/**
 * purpose: Display the last 100 bytes of the curent file 
 * to the user through the terminal
 * input: file name
 * output: the last 100 bytes of the current file
 */
int displayTail(char* file)
{
  FILE *pointer;
  pointer = fopen(file, "r");
  char inputStream[1000];
  const long int offset = -100;
  int read_byte;
  if(pointer == NULL)
  {
    perror("fopen");
    printf("The file could not be read!!");
  }
  else
  {
    fseek(pointer, offset, SEEK_END);
    fread(inputStream, 1, 100, pointer);
    inputStream[(sizeof inputStream)-1] = 0;
    printf("%s\n", inputStream);    
   }
 
  fclose(pointer);
  return 0;
}

/**
 * purpose: Change the access permissions of the current 
 * file
 * input: file name
 * output: nothing(changes current file's permissions)
 */
int changePermission(char* file)
{
  printf("Enter a 4-digit permission code: ");
  int permission;
  scanf("%i", &permission);
  chmod(file, permission);
}

/**
 * purpose: Change the current file's access time to
 * the current time 
 * input: file name
 * output: nothing(change access time of file)
 */
int changeTime(char* file)
{
  utime(file, NULL);
  return 0;
}


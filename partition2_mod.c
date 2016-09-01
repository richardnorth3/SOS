#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **environ;
#define MAXSTRING 128
#define BASESTR "SMA_SYMMETRIC_PARTITION"
#define BASESTR2 "SHMEM_SYMMETRIC_PARTITION"

struct HBM{
    unsigned int part_id;
    unsigned int kind;
    unsigned int pgsize;
    unsigned int policy;
    unsigned int size;
};


int main(int argc, const char * argv[]){

    char **env;
    size_t nbase,nrhs,nbase2;
    char *firsteq;
    char num[4];
    char rhs[MAXSTRING];
    size_t nn;
    char *token1, *token2;
    char *st1 = NULL, *st2 = NULL;
    int i = 1;
    int max = 7;
    struct HBM partition[max];



     env = environ;
     nbase = strlen(BASESTR);
     nbase2 = strlen(BASESTR2);

     while(*env != NULL){

         if (strncmp(*env, BASESTR, nbase) == 0 || strncmp(*env, BASESTR2, nbase2) == 0){

             firsteq = strchr(*env,'=');

             nn = firsteq - *env - nbase;

             strncpy(num, *env+nbase, nn);

             num[nn] = '\0';

             nrhs = strlen(firsteq+1);
             strncpy(rhs,firsteq+1,nrhs);
             rhs[nrhs] = '\0';

             partition[i].part_id = atoi(num);
             printf("PartID%d: %d\n",i,partition[i].part_id);

             token1 = strtok_r(rhs,":",&st1);

             while(token1 != NULL){

                 token2 = strtok_r(token1,"=",&st2);

                 if (strstr(token1,"size") != NULL){

                     token2 = strtok_r(NULL, "=", &st2);
                     partition[i].size = atoi(token2);
                     printf("Size%d: %d\n",i,partition[i].size);

                     //printf("Size Token %s\n",token1);
                     //printf("Token 2 = %s\n\n", token2);

                 }

                 else if (strstr(token1,"kind") != NULL){
                     //Do something with token

                     token2 = strtok_r(NULL, "=", &st2);

                     if(strncmp(token2,"F",1) == 0){

                         partition[i].kind = 1;
                     }
                     else if(strncmp(token2,"D",1) == 0){

                         partition[i].kind = 0;
                     }
                     else{
                         printf("Error, wrong input for kind value\n");
                     }

                     printf("Kind%d: %d\n",i,partition[i].kind);

                     //printf("Kind Token %s\n",token1);
                     //printf("Token 2 = %s\n\n", token2);
                 }

                 else if (strstr(token1,"policy") != NULL){
                     //Do something with token

                     token2 = strtok_r(NULL, "=", &st2);
                     partition[i].policy = atoi(token2);
                     printf("Policy%d: %d\n",i,partition[i].policy);

                     //printf("Policy Token %s\n",token1);
                     //printf("Token 2 = %s\n\n", token2);

                 }

                 else if (strstr(token1,"pgsz") != NULL){
                     //Do something with token

                     token2 = strtok_r(NULL, "=",&st2);

                     partition[i].pgsize = atoi(token2);
                     printf("Pgsize%d: %d\n",i,partition[i].pgsize);

                     //printf("Pgsize Token %s\n",token1);
                     //printf("Token 2 = %s\n\n", token2);
                 }

                 else {

                     printf("Error\n");
                 }



                 token1 = strtok_r(NULL, ":", &st1);
             }
                 i++;
                 printf("\n\n");
         }


         env++;
         if (i>max){
             printf("Max partitions reached\n");
             break;
         }
    }
}


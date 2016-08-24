#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSTRING 65

struct HBM{

    unsigned int part_id;
    unsigned int kind;
    unsigned int pgsize;
    unsigned int policy;
    unsigned int size;
};

int main(int argc, const char * argv[]){

    /* Process environment variable
     *
     * char* symmetric_partition;
     * symmetric_partition = (shmem_util_getenv_str("SYMMETRIC_PARTITION"));
     *
     */

    char *token1, *token2;
    char *st1 = NULL, *st2 = NULL;
    char myenv[MAXSTRING];
    int i = 0;
    // char SMA_SYMMETRIC_PARTITION[] = "size=4:kind=something:policy=mypolicy:pgsize=4K";
    int max = 7;
    struct HBM partition[max];

    setenv("SMA_SYMMETRIC_PARTITION","size=4:kind=F:policy=mypolicy:pgsz=4K",0);

    strcpy(myenv,getenv("SMA_SYMMETRIC_PARTITION"));

    //Partition 0 example
    token1 = strtok_r(myenv,":",&st1);

    while(token1 != NULL){

        token2 = strtok_r(token1,"=",&st2);

         if (strstr(token1,"size") != NULL){

            token2 = strtok_r(NULL, "=", &st2);
            partition[i].size = atoi(token2);
             printf("Size: %d\n",partition[i].size);

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

            printf("Kind: %d\n",partition[i].kind);

            //printf("Kind Token %s\n",token1);
            //printf("Token 2 = %s\n\n", token2);
                   }

        else if (strstr(token1,"policy") != NULL){
            //Do something with token

            token2 = strtok_r(NULL, "=", &st2);
            partition[i].policy = atoi(token2);
            printf("Policy: %d\n",partition[i].policy);

            //printf("Policy Token %s\n",token1);
            //printf("Token 2 = %s\n\n", token2);

        }

        else if (strstr(token1,"pgsz") != NULL){
            //Do something with token

            token2 = strtok_r(NULL, "=",&st2);

            partition[i].pgsize = atoi(token2);
            printf("Pgsize: %d\n",partition[i].pgsize);

            //printf("Pgsize Token %s\n",token1);
            //printf("Token 2 = %s\n\n", token2);
                    }

        else {

            printf("Error\n");
        }


        i++;
        token1 = strtok_r(NULL, ":", &st1);
    }

}


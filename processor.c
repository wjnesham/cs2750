/*
 * processor.c
 *
 *  Created on: Apr 24, 2018
 *      Author: william nesham
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <memory.h>
#include <ctype.h>




#include <memory.h>
#include <ctype.h>
#include <regex.h>

#ifndef NULL
#define NULL ((void *) 0)
#endif


typedef struct
{
char name[40];
int number;
float balance;
} acct_info_t;

void getBalance(FILE * file, int, acct_info_t*) ;

/*
 * Debug function to dump all records, be sure file ptr is at first record
 */
void dumpRecords(FILE * file, unsigned int num_rec) {

    int errorNumber=0;
    acct_info_t *record = (acct_info_t *) malloc(sizeof(acct_info_t)); //

    for(int i=0; i < num_rec; i++) {
//        fread(record, sizeof(acct_info_t *), i, file);
//        printf("Name: %s, Number: %d, Balance: %f\n", record->name, record->number, record->balance);
//        errorNumber = fseek(file, sizeof(acct_info_t), SEEK_CUR);
//        if(errorNumber != 0) return;
    	getBalance(file, 0, record);

    }

}


void getBalance(FILE * file, int record_num, acct_info_t *record) {
    int errorNumber=0;
    errorNumber = fseek(file, record_num * sizeof(acct_info_t), SEEK_CUR);
    if(errorNumber != 0) {
        printf("Invalid record number. Please check the file\n");
        exit(2);
    }
    fread(record, sizeof(acct_info_t), 1, file);
    printf("Name: %s, Number: %d, Balance: %f\n", record->name, record->number, record->balance);
}


/*
 * Takes in file, pattern, and record num.
 * Prints
 */
void findRecordUsingRegexec(FILE * file, char * regxPattern, int num_rec) {
    char *pattern = regxPattern;
    regex_t preg;
    int rc;
    int errorNumber=0;
    size_t nmatch = 2;
    regmatch_t pmatch[2];

    acct_info_t *record = (acct_info_t *) malloc(sizeof(acct_info_t));

    for(int i=0; i < num_rec; i++) {

        if ((rc = regcomp(&preg, pattern, REG_EXTENDED)) != 0) {
               printf("regcomp() failed, returning nonzero (%d)\n", rc);
               exit(1);
            }

        fread(record, sizeof(acct_info_t), 1, file);
        if(errorNumber != 0) return;

        if ((rc = regexec(&preg, record->name, nmatch, pmatch, 0)) != 0) {
           //printf("failed to match '%s' with '%s',returning %d.\n", record->name, pattern, rc);
        } else {
            printf("Match found -> Name: %s, Number: %d, Balance: %f\n", record->name, record->number, record->balance);
        }

        regfree(&preg);
    }
}

void findAccountWRegex(char * regexPattern) {

    unsigned int magic_num;
    unsigned int num_rec;

    int headerLen = sizeof(magic_num) + sizeof(num_rec);

    FILE * file = fopen("./acct_info", "rb");
    if (file==NULL) {
        printf("no file found.\n");
        exit(1);
    }

    rewind(file); //go to start of file
    fread(&magic_num, sizeof(magic_num), 1, file);

    fseek(file, sizeof(unsigned int), SEEK_SET);
    fread(&num_rec, sizeof(num_rec), 1, file);

    fseek(file, headerLen, SEEK_SET); //position to start of first record

    printf("magic=%d, numRec=%d\n",magic_num, num_rec);

    findRecordUsingRegexec(file, regexPattern, num_rec);
    fclose(file);
}



void findAccount(int rec_num) {
	rec_num-=1; // To convert to index.

    acct_info_t *record = (acct_info_t *) malloc(sizeof(acct_info_t));

    unsigned int magic_num;
    unsigned int num_rec;

    int headerLen = sizeof(magic_num) + sizeof(num_rec);

    FILE * file = fopen("./acct_info", "rb");
    if (file==NULL) {
        printf("no file found.");
        exit(1);
    }

    rewind(file); //go to start of file
    fread(&magic_num, sizeof(magic_num), 1, file);

    fseek(file, sizeof(unsigned int), SEEK_SET);
    fread(&num_rec, sizeof(num_rec), 1, file);

    if(rec_num > num_rec || rec_num < 0) {
        printf("Usage: ./process [record_number]  to find record. 0 < 'record_number' <= 1000.\n");
        exit(0);
    }
    fseek(file, headerLen, SEEK_SET); //position to start of first record

    printf("magic=%d, numRec=%d\n",magic_num, num_rec);

    getBalance(file, rec_num, record);
    //dumpRecords(file, num_rec);
    fclose(file);
}

typedef enum { false, true } bool;
bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-') {
        i = 1;
    }
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}


int main(int argc, char ** argv) {
    //printf("param '%s' was passed.\n", argv[1]);
    if(argc < 1 ) {
        printf("Usage: ./process [regex_pattern] [record_number_to_find].\n");
        exit(0);
    }
    int dec = 0, len;
    len = strlen(argv[1]);
    for(int i=0; i<len; i++){
        dec = dec * 10 + ( argv[1][i] - '0' );
    }
    //printf("'%d' passed string converted to int.\n", dec);

    if (isNumber(argv[1]) == false)
    	findAccountWRegex(argv[1]);
    else
    	findAccount(dec);

}

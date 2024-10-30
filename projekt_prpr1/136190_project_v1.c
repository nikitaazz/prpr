#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int CountStrings(FILE **file){
    char ch,z;
    int L = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            L++;
        }
        z=ch;
    }
    if (z!='\n')
    {
        L++;
    }
    return L;
}


void v1(FILE **DataPointer1,FILE **ParsePointer1,FILE **StringPointer1) {
    char *StringValues, *CombainedValues;
    char *token, buffer[256];
    int WhileCounter = 0;

    StringValues = (char*) calloc(256, sizeof(char));
    CombainedValues = (char*) calloc(256, sizeof(char));
    if (*DataPointer1==NULL)
    {
        *DataPointer1=fopen("data.txt","r");
        if (*DataPointer1==NULL)
        {
            printf("V1: Neotvorene txt subory.\n");
            return;
        }
    }
    if (*ParsePointer1==NULL)
    {
        *ParsePointer1=fopen("parse.txt","r");
        if (*ParsePointer1==NULL)
        {
            printf("V1: Neotvorene txt subory.\n");
            return;
        }
    }
    if (*StringPointer1==NULL)
    {
        *StringPointer1=fopen("string.txt","r");
        if (*StringPointer1==NULL)
        {
            printf("V1: Neotvorene txt subory.\n");
            return;
        }
    }    
    fseek(*StringPointer1, 0, SEEK_SET);
    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
    while (fgets(buffer, sizeof(buffer),*DataPointer1)!=NULL)
    {
        WhileCounter=0;
        token=strtok(buffer," ");
        printf("ID. mer. modulu: %s",fgets(StringValues, 256, *StringPointer1));
        while (token!=NULL)
        {
            WhileCounter++;
            if (WhileCounter==3)
            {
                printf("Hodnota 1: %d\n",atoi(token));
            }
            if (WhileCounter==4)
            {
                printf("Hodnota 2: %g\n",atof(token));
            }   
            token = strtok(NULL, " ");
        }
        printf("Poznámka: %s\n",fgets(CombainedValues, 256, *ParsePointer1));
    }
    free(StringValues);
    free(CombainedValues);
}



void v2(FILE **DataPointer1,FILE **ParsePointer1,FILE **StringPointer1) { 
}



void n(FILE **DataPointer1, FILE **ParsePointer1, FILE **StringPointer1) {
    int CountStringsDataPointer = CountStrings(DataPointer1);
    int CountStringsParsePointer = CountStrings(ParsePointer1);
    int CountStringsStringPointer = CountStrings(StringPointer1);
    char *DataTxtLions = (char *)malloc(CountStringsDataPointer * sizeof(char));
    char *ParseTxtLions = (char *)malloc(CountStringsParsePointer * sizeof(char));
    char *StringTxtLions = (char *)malloc(CountStringsStringPointer * sizeof(char));
    while (fgets(buffer, sizeof(buffer),*DataPointer1)!=NULL)
    {
        WhileCounter=0;
        token=strtok(buffer," ");
        printf("ID. mer. modulu: %s",fgets(StringValues, 256, *StringPointer1));
        while (token!=NULL)
        {
            WhileCounter++;
            if (WhileCounter==3)
            {
                printf("Hodnota 1: %d\n",atoi(token));
            }
            if (WhileCounter==4)
            {
                printf("Hodnota 2: %g\n",atof(token));
            }   
            token = strtok(NULL, " ");
        }
    }
    free(DataTxtLions);
    free(ParseTxtLions);
    free(StringTxtLions);
}





void h(FILE **StringPointer1){
    char Symbol;
    int LetterCountLowerCase[26]={0},LetterCountUpperCase[26]={0},NumberCounter[10]={0},i = 0;
    if (*StringPointer1==NULL)
    {
        printf("H: Neotvoreny subor.\n");
        return;
    }
    fseek(*StringPointer1, 0, SEEK_SET);
    while ((Symbol = fgetc(*StringPointer1)) != EOF)
    {
        if (Symbol >= '0' && Symbol <= '9')
        {
            NumberCounter[Symbol - '0']++;
        }
        else if (Symbol >= 'A' && Symbol <= 'Z')
        {
            LetterCountUpperCase[Symbol - 'A']++;
        }
        else if (Symbol >= 'a' && Symbol <= 'z')
        {
            LetterCountLowerCase[Symbol - 'a']++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (LetterCountUpperCase[i] > 0) {
            printf("%c : %d\n", i + 'A', LetterCountUpperCase[i]);
        }
    }
    for (i = 0; i < 26; i++) {
        if (LetterCountLowerCase[i] > 0) {
            printf("%c : %d\n", i + 'a', LetterCountLowerCase[i]);
        }
    }
    for (i = 0; i < 10; i++) {
        if (NumberCounter[i] > 0) {
            printf("%d : %d\n", i, NumberCounter[i]);
        }
    }

}



void v(FILE **DataPointer1,FILE **ParsePointer1,FILE **StringPointer1) {
    int NumberOfFunction;
    scanf("%d",&NumberOfFunction);
    if (NumberOfFunction==1)
    {
        v1(DataPointer1,ParsePointer1,StringPointer1);
    }else if (NumberOfFunction==2)
    {
        v2(DataPointer1,ParsePointer1,StringPointer1);
    }else{
        printf("V: Nespravne volba vypisu.\n");
    }
}



int main(void)
{
    FILE *DataPointer = NULL;
    FILE *ParsePointer = NULL;
    FILE *StringPointer = NULL;
    FILE **DataPointer1 = &DataPointer;
    FILE **ParsePointer1 = &ParsePointer;
    FILE **StringPointer1 = &StringPointer;
    char CalledFunction;
    while (1)
    {
        scanf("%c",&CalledFunction);
        if (CalledFunction=='v')
        {
            v(DataPointer1,ParsePointer1,StringPointer1);
        } else if (CalledFunction=='h')
        {
            h(StringPointer1);
        } else if (CalledFunction == 'k') { 
            if (DataPointer != NULL) fclose(DataPointer); 
            if (StringPointer != NULL) fclose(StringPointer); 
            if (ParsePointer != NULL) fclose(ParsePointer); 
            break; 
        } else if (CalledFunction=='n')
        {
            n(DataPointer1,ParsePointer1,StringPointer1);
        }
    }
    return 0;
}
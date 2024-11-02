#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char *my_strdup(const char *str) {
    char *dup = malloc(strlen(str) + 1);
    if (dup) {
        strcpy(dup, str);
    }
    return dup;
}



int FindLargestElement(char **array, int size) {
    int i = 1;
    int maxIndex = 0;
    int maxLength = strlen(array[0]);

    for (i = 1; i < size; i++) {
        int currentLength = strlen(array[i]);
        if (currentLength > maxLength) {
            maxLength = currentLength;
            maxIndex = i;
        }
    }

    return maxIndex;
}


void PrintArray(char **array, int size) {
    int i=0;
    for (i = 0; i < size; i++) {
        if (array[i] != NULL) {
            printf("%s\n", array[i]);
        }
    }
}



int CountStrings(FILE *file) {
    int count = 0;
    char ch;
    int is_new_line = 1;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
            is_new_line = 1;
        } else {
            is_new_line = 0;
        }
    }

    if (is_new_line==0) {
        count++;
    }
    return count;
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
    fseek(*StringPointer1, 0, SEEK_SET);
    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
}



void v2(FILE **DataPointer1,FILE **ParsePointer1,FILE **StringPointer1) {
    fseek(*StringPointer1, 0, SEEK_SET);
    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
}



void n(FILE **DataPointer1, FILE **ParsePointer1, FILE **StringPointer1,int *largestDataIndex,int *largestParseIndex,int *largestStringIndex,char ***DataTxtLions,char ***ParseTxtLions,char ***StringTxtLions) {

    int i = 0;
    char buffer[256];
    int DataCounter = 0, StringCounter = 0, ParseCounter = 0;

    int CountStringsDataPointer = CountStrings(*DataPointer1);
    int CountStringsParsePointer = CountStrings(*ParsePointer1);
    int CountStringsStringPointer = CountStrings(*StringPointer1);

    if (*DataTxtLions) {
        for (i = 0; i < CountStringsDataPointer; i++) {
            free((*DataTxtLions)[i]);
        }
        free(*DataTxtLions);
    }

    if (*ParseTxtLions) {
        for (i = 0; i < CountStringsParsePointer; i++) {
            free((*ParseTxtLions)[i]);
        }
        free(*ParseTxtLions);
    }

    if (*StringTxtLions) {
        for (i = 0; i < CountStringsStringPointer; i++) {
            free((*StringTxtLions)[i]);
        }
        free(*StringTxtLions);
    }

    if (*DataPointer1 == NULL || *ParsePointer1 == NULL || *StringPointer1 == NULL) {
        printf("N: Neotvoreny subor.\n");
        return;
    }

    *DataTxtLions = malloc(CountStringsDataPointer * sizeof(char *));
    *ParseTxtLions = malloc(CountStringsParsePointer * sizeof(char *));
    *StringTxtLions = malloc(CountStringsStringPointer * sizeof(char *));

    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
    fseek(*StringPointer1, 0, SEEK_SET);

    while (fgets(buffer, sizeof(buffer), *DataPointer1) != NULL && DataCounter < CountStringsDataPointer) {
        buffer[strcspn(buffer, "\n")] = '\0';
        (*DataTxtLions)[DataCounter] = my_strdup(buffer);
        DataCounter++;
    }

    while (fgets(buffer, sizeof(buffer), *ParsePointer1) != NULL && ParseCounter < CountStringsParsePointer) {
        buffer[strcspn(buffer, "\n")] = '\0';
        (*ParseTxtLions)[ParseCounter] = my_strdup(buffer);
        ParseCounter++;
    }

    while (fgets(buffer, sizeof(buffer), *StringPointer1) != NULL && StringCounter < CountStringsStringPointer) {
        buffer[strcspn(buffer, "\n")] = '\0';
        (*StringTxtLions)[StringCounter] = my_strdup(buffer);
        StringCounter++;
    }

    *largestDataIndex = FindLargestElement(*DataTxtLions, CountStringsDataPointer);
    *largestParseIndex = FindLargestElement(*ParseTxtLions, CountStringsParsePointer);
    *largestStringIndex = FindLargestElement(*StringTxtLions, CountStringsStringPointer);

    printf("Data Array:\n");
    PrintArray(*DataTxtLions, CountStringsDataPointer);
    
    printf("\nParse Array:\n");
    PrintArray(*ParseTxtLions, CountStringsParsePointer);
    
    printf("\nString Array:\n");
    PrintArray(*StringTxtLions, CountStringsStringPointer);

    printf("\nLargest Data Index: %d\n", *largestDataIndex);
    printf("Largest Parse Index: %d\n", *largestParseIndex);
    printf("Largest String Index: %d\n", *largestStringIndex);

    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
    fseek(*StringPointer1, 0, SEEK_SET);
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
    fseek(*StringPointer1, 0, SEEK_SET);
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
    int largestDataIndex = 0, largestParseIndex = 0,largestStringIndex = 0;
    int *pLargestDataIndex = &largestDataIndex, *pLargestParseIndex = &largestParseIndex, *pLargestStringIndex = &largestStringIndex;
    char **DataTxtLions = NULL;
    char **ParseTxtLions = NULL;
    char **StringTxtLions = NULL;
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
            n(DataPointer1, ParsePointer1, StringPointer1, pLargestDataIndex, pLargestParseIndex, pLargestStringIndex, &DataTxtLions, &ParseTxtLions, &StringTxtLions);
        }
    }
    return 0;
}
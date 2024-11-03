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
    int currentLength;
    int maxLength = strlen(array[0]);

    for (i = 1; i < size; i++) {
        currentLength = strlen(array[i]);
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

int countElements(char **array) {
    int count = 0;
    while (array[count] != NULL) {
        count++;
    }
    return count;
}


void v1(FILE **DataPointer1,FILE **ParsePointer1,FILE **StringPointer1, int *p_numElements) {
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
    *p_numElements=CountStrings(*DataPointer1);
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


void v2(int numElements, char **DataTxtLions, char **ParseTxtLions, char **StringTxtLions) {
    int Counter = 0;
    char *token;
    double hodnota1 = 0.0, hodnota2 = 0.0;
    int i = 0;

    if (DataTxtLions == NULL || ParseTxtLions == NULL || StringTxtLions == NULL) {
        printf("V2: Nenaplnene polia.\n");
        return;
    }

    while (Counter < numElements) {
        char *dataLineCopy = (char *)malloc(strlen(DataTxtLions[Counter]) + 1);
        if (dataLineCopy == NULL) {
            printf("Memory allocation error\n");
            return;
        }
        strcpy(dataLineCopy, DataTxtLions[Counter]);

        token = strtok(dataLineCopy, " ");
        i = 0;
        hodnota1 = 0.0;
        hodnota2 = 0.0;

        while (token != NULL) {
            if (i == 2) {
                hodnota1 = atoi(token);
            } else if (i == 3) {
                hodnota2 = atof(token);
            }
            i++;
            token = strtok(NULL, " ");
        }

        printf("ID. mer. modulu: %s\n", StringTxtLions[Counter]);
        printf("Hodnota 1: %d\n", (int)hodnota1);
        printf("Hodnota 2: %g\n", hodnota2);
        printf("Poznámka: %s\n", ParseTxtLions[Counter]);
        printf("\n");

        free(dataLineCopy);
        Counter++;
    }
}


void n(FILE **DataPointer1, FILE **ParsePointer1, FILE **StringPointer1,int *largestDataIndex,int *largestParseIndex,int *largestStringIndex,char ***DataTxtLions,char ***ParseTxtLions,char ***StringTxtLions) {

    int i = 0;
    char buffer[256];
    int DataCounter = 0, StringCounter = 0, ParseCounter = 0;

    int CountStringsDataPointer = 0;
    int CountStringsParsePointer = 0;
    int CountStringsStringPointer = 0;

    if (*DataPointer1 == NULL || *ParsePointer1 == NULL || *StringPointer1 == NULL) {
        printf("N: Neotvoreny subor.\n");
        return;
    }

    CountStringsDataPointer = CountStrings(*DataPointer1);
    CountStringsParsePointer = CountStrings(*ParsePointer1);
    CountStringsStringPointer = CountStrings(*StringPointer1);

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

    *DataTxtLions = malloc(CountStringsDataPointer * sizeof(char *));
    *ParseTxtLions = malloc(CountStringsParsePointer * sizeof(char *));
    *StringTxtLions = malloc(CountStringsStringPointer * sizeof(char *));

    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
    fseek(*StringPointer1, 0, SEEK_SET);

    while (fgets(buffer, sizeof(buffer), *DataPointer1) != NULL && DataCounter < CountStringsDataPointer) {
        for (i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
        }
        (*DataTxtLions)[DataCounter] = my_strdup(buffer);
        DataCounter++;
    }

    while (fgets(buffer, sizeof(buffer), *ParsePointer1) != NULL && ParseCounter < CountStringsParsePointer) {
        for (i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
        }
        (*ParseTxtLions)[ParseCounter] = my_strdup(buffer);
        ParseCounter++;
    }

    while (fgets(buffer, sizeof(buffer), *StringPointer1) != NULL && StringCounter < CountStringsStringPointer) {
        for (i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
        }
        (*StringTxtLions)[StringCounter] = my_strdup(buffer);
        StringCounter++;
    }

    *largestDataIndex = FindLargestElement(*DataTxtLions, CountStringsDataPointer);
    *largestParseIndex = FindLargestElement(*ParseTxtLions, CountStringsParsePointer);
    *largestStringIndex = FindLargestElement(*StringTxtLions, CountStringsStringPointer);

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


void q(int *numElements, char ***DataTxtLions, char ***ParseTxtLions, char ***StringTxtLions) {
    int YMain = 0, WhileCounter = 0, i = 0;

    char **DataNewArray = malloc(*numElements+1 * sizeof(char *));
    char **ParseNewArray = malloc(*numElements+1 * sizeof(char *));
    char **StringNewArray = malloc(*numElements+1 * sizeof(char *));

    if (*DataTxtLions == NULL || *ParseTxtLions == NULL || *StringTxtLions == NULL) {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }

    for (i = 0; i < *numElements+1; i++) {
        DataNewArray[i] = malloc(256 * sizeof(char));
        ParseNewArray[i] = malloc(256 * sizeof(char));
        StringNewArray[i] = malloc(256 * sizeof(char));
    }

    scanf("%d", &YMain);
    YMain--;
    if (YMain>*numElements)
    {
        YMain=*numElements-1;
    }
    

    WhileCounter = 0;
    while (WhileCounter < *numElements + 1) {
        if (WhileCounter < YMain) {
            strcpy(DataNewArray[WhileCounter], (*DataTxtLions)[WhileCounter]);
            strcpy(ParseNewArray[WhileCounter], (*ParseTxtLions)[WhileCounter]);
            strcpy(StringNewArray[WhileCounter], (*StringTxtLions)[WhileCounter]);
        } else if (WhileCounter == YMain) {
            scanf(" %[^\n]", StringNewArray[WhileCounter]);
            scanf(" %[^\n]", DataNewArray[WhileCounter]);
            scanf(" %[^\n]", ParseNewArray[WhileCounter]);
        } else {
            strcpy(DataNewArray[WhileCounter], (*DataTxtLions)[WhileCounter - 1]);
            strcpy(ParseNewArray[WhileCounter], (*ParseTxtLions)[WhileCounter - 1]);
            strcpy(StringNewArray[WhileCounter], (*StringTxtLions)[WhileCounter - 1]);
        }
        WhileCounter++;
    }
    for (i = 0; i < *numElements; i++) {
        free((*DataTxtLions)[i]);
        free((*ParseTxtLions)[i]);
        free((*StringTxtLions)[i]);
    }

    free(*DataTxtLions);
    free(*ParseTxtLions);
    free(*StringTxtLions);

    *DataTxtLions = DataNewArray;
    *ParseTxtLions = ParseNewArray;
    *StringTxtLions = StringNewArray;

    (*numElements)++;
}


void w(int *numElements, char ***DataTxtLions, char ***ParseTxtLions, char ***StringTxtLions) {
    int i=0;
    int deletedCount = 0;
    int newArrayIndex = 0;
    char idToDelete[256];



    char **DataNewArray = malloc((*numElements) * sizeof(char *));
    char **ParseNewArray = malloc((*numElements) * sizeof(char *));
    char **StringNewArray = malloc((*numElements) * sizeof(char *));

    if (*DataTxtLions == NULL || *StringTxtLions == NULL || *ParseTxtLions == NULL) {
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    
    scanf(" %s", idToDelete);
    
    
    for (i = 0; i < *numElements; i++) {
        if (strcmp((*StringTxtLions)[i], idToDelete) == 0) {
            deletedCount++;
            free((*DataTxtLions)[i]);
            free((*ParseTxtLions)[i]);
            free((*StringTxtLions)[i]);
        } else {
            DataNewArray[newArrayIndex] = (*DataTxtLions)[i];
            ParseNewArray[newArrayIndex] = (*ParseTxtLions)[i];
            StringNewArray[newArrayIndex] = (*StringTxtLions)[i];
            newArrayIndex++;
        }
    }

    free(*DataTxtLions);
    free(*ParseTxtLions);
    free(*StringTxtLions);

    *DataTxtLions = DataNewArray;
    *ParseTxtLions = ParseNewArray;
    *StringTxtLions = StringNewArray;

    *numElements -= deletedCount;

    printf("W: Vymazalo sa : %d zaznamov !\n", deletedCount);
}


void v(FILE **DataPointer1,FILE **ParsePointer1,FILE **StringPointer1,  char ***DataTxtLions,char ***ParseTxtLions,char ***StringTxtLions, int numElements, int *p_numElements) {
    int NumberOfFunction;
    scanf("%d",&NumberOfFunction);
    if (NumberOfFunction==1)
    {
        v1(DataPointer1,ParsePointer1,StringPointer1,p_numElements);
    }else if (NumberOfFunction==2)
    {
        v2(numElements, *DataTxtLions, *ParseTxtLions, *StringTxtLions);
    }else{
        printf("V: Nespravne volba vypisu.\n");
    }
}


void e(char ***ParseTxtLions, int numElements) {
    int i = 0;
    char ExploreString[256];

    if (*ParseTxtLions == NULL) {
        printf("E: Polia nie su vytvorene.\n");
        return;
    }
    
    scanf("%s", ExploreString);
    
    for (i = 0; i < numElements; i++) {
        if (strstr((*ParseTxtLions)[i], ExploreString) != NULL) {
            printf("%s\n", (*ParseTxtLions)[i]);
        }
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
    int numElements=0;
    int *p_numElements = &numElements;
    while (1)
    {
        scanf("%c",&CalledFunction);
        if (CalledFunction=='v')
        {
            v(DataPointer1, ParsePointer1, StringPointer1, &DataTxtLions, &ParseTxtLions, &StringTxtLions,numElements,p_numElements);
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
        }else if (CalledFunction=='q')
        {
            q(&numElements, &DataTxtLions, &ParseTxtLions, &StringTxtLions);
        }else if (CalledFunction=='w')
        {
            w(&numElements, &DataTxtLions, &ParseTxtLions, &StringTxtLions);
        }else if (CalledFunction=='e')
        {
            e(&ParseTxtLions,numElements);
        }
        
    }
    return 0;
}
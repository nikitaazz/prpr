#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct DataStructure
{
    int DataFirstValue;
    int DataSecondValue;
    int DataThirdValue;
    double DataFourthValue;
    struct DataStructure *next;
};


struct ParseStructure
{
    char ID[1024];
    double FirstValue;
    int Hours;
    int Minutes;
    char Comment[1024];
    struct ParseStructure *next;
};


struct StringStructure
{
    char ID[1024];
    struct StringStructure *next;
};



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


void v1(FILE **DataPointer1,FILE **ParsePointer1,FILE **StringPointer1, int *p_numElements, int *numElements_PZ) {
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
    char *token, *buffer;
    double hodnota2 = 0.0;
    int hodnota1 = 0;
    int i = 0;

    if (DataTxtLions == NULL || ParseTxtLions == NULL || StringTxtLions == NULL) {
        printf("V2: Nenaplnene polia.\n");
        return;
    }

    buffer=(char*)malloc(512*sizeof(char));

    while (Counter < numElements) {
        strcpy(buffer,DataTxtLions[Counter]);
        token = strtok(buffer, " ");
        i = 0;
        hodnota1 = 0;
        hodnota2 = 0.0;

        while (token != NULL) {
            if (i == 2) {
                hodnota1 = atoi(token);
            } else if (i == 3) {
                hodnota2 = atof(token);
                break;
            }
            i++;
            token = strtok(NULL, " ");
        }
        
        printf("ID. mer. modulu: %s",StringTxtLions[Counter]);
        printf("Hodnota 1: %d\n", hodnota1);
        printf("Hodnota 2: %g\n", hodnota2);
        printf("Poznámka: %s",ParseTxtLions[Counter]);
        printf("\n");
        Counter++;
    }
    free(buffer);
}


void v3(struct DataStructure *DataStructurePointer,struct ParseStructure *ParseStructurePointer,struct StringStructure *StringStructurePointer,int *numElements){ 
    int i=0;
    if (DataStructurePointer->next==NULL || ParseStructurePointer->next==NULL || StringStructurePointer->next==NULL)
    {
        printf("V3: Nenaplnený spajany zoznam.\n");
        return;
    }
    while (i<*numElements)
    {
        printf("ID. mer. modulu: %s",StringStructurePointer->ID);
        printf("Hodnota 1: %d\n",DataStructurePointer->DataThirdValue);
        printf("Hodnota 2: %g\n",DataStructurePointer->DataFourthValue);
        printf("Poznámka ID: %s\n",ParseStructurePointer->ID);   
        printf("Poznámka C: %d : %d => %g\n",ParseStructurePointer->Hours,ParseStructurePointer->Minutes,ParseStructurePointer->FirstValue);
        printf("Poznámka T: %s\n\n", ParseStructurePointer->Comment[0] == '\0' ? "NAN" : ParseStructurePointer->Comment);
        ParseStructurePointer=ParseStructurePointer->next;
        DataStructurePointer=DataStructurePointer->next;
        StringStructurePointer=StringStructurePointer->next;
        i++;
    }
}


void n(FILE **DataPointer1, FILE **ParsePointer1, FILE **StringPointer1,int *largestDataIndex,int *largestParseIndex,int *largestStringIndex,char ***DataTxtLions,char ***ParseTxtLions,char ***StringTxtLions,int *numElements) {

    int i = 0;
    char buffer[256];

    int CountStringsDataPointer = 0;
    int CountStringsParsePointer = 0;
    int CountStringsStringPointer = 0;

    if (*DataPointer1 == NULL || *ParsePointer1 == NULL || *StringPointer1 == NULL) {
        printf("N: Neotvoreny subor.\n");
        return;
    }

    if (*DataTxtLions!=NULL) {
        for (i = 0; i < *numElements; i++) {
            free((*DataTxtLions)[i]);
        }
        free(*DataTxtLions);
    }

    if (*ParseTxtLions!=NULL) {
        for (i = 0; i < *numElements; i++) {
            free((*ParseTxtLions)[i]);
        }
        free(*ParseTxtLions);
    }


    if (*StringTxtLions!=NULL) {
        for (i = 0; i < *numElements; i++) {
            free((*StringTxtLions)[i]);
        }
        free(*StringTxtLions);
    }

    CountStringsDataPointer = CountStrings(*DataPointer1);
    CountStringsParsePointer = CountStrings(*ParsePointer1);
    CountStringsStringPointer = CountStrings(*StringPointer1);
    *numElements=CountStringsDataPointer;

    *DataTxtLions = malloc(CountStringsDataPointer * sizeof(char *));
    *ParseTxtLions = malloc(CountStringsParsePointer * sizeof(char *));
    *StringTxtLions = malloc(CountStringsStringPointer * sizeof(char *));

    i=0;
    while (i<CountStringsDataPointer)
    {
        (*DataTxtLions)[i] = malloc(256 * sizeof(char));
        i++;
    }

    i=0;
    while (i<CountStringsParsePointer)
    {
        (*ParseTxtLions)[i] = malloc(256 * sizeof(char));
        i++;
    }

    i=0;
    while (i<CountStringsStringPointer)
    {
        (*StringTxtLions)[i] = malloc(256 * sizeof(char));
        i++;
    }
    

    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
    fseek(*StringPointer1, 0, SEEK_SET);

    i=0;
    while (fgets(buffer, sizeof(buffer), *DataPointer1) != NULL && i < CountStringsDataPointer) {
        strcpy((*DataTxtLions)[i],buffer);
        i++;
    }

    i=0;
    while (fgets(buffer, sizeof(buffer), *ParsePointer1) != NULL && i < CountStringsParsePointer) {
        strcpy((*ParseTxtLions)[i],buffer);
        i++;
    }

    i=0;
    while (fgets(buffer, sizeof(buffer), *StringPointer1) != NULL && i < CountStringsStringPointer) {
        strcpy((*StringTxtLions)[i],buffer);
        i++;
    }

    *largestDataIndex = FindLargestElement(*DataTxtLions, CountStringsDataPointer);
    *largestParseIndex = FindLargestElement(*ParseTxtLions, CountStringsParsePointer);
    *largestStringIndex = FindLargestElement(*StringTxtLions, CountStringsStringPointer);

    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
    fseek(*StringPointer1, 0, SEEK_SET);
}


void m(FILE **DataPointer1, FILE **ParsePointer1, FILE **StringPointer1, int *numElements, struct DataStructure *DataStructurePointer,struct ParseStructure *ParseStructurePointer,struct StringStructure *StringStructurePointer){
    struct ParseStructure *ParseStructure1 = ParseStructurePointer;
    struct DataStructure *DataStructure1 = DataStructurePointer;
    struct StringStructure *StringStructure1 = StringStructurePointer;
    struct DataStructure *p1 = NULL;
    struct ParseStructure *p2 = NULL;
    struct StringStructure *p3 = NULL;
  
    int i = 0, whileCounter = 0,a=0,b=0;
    char buffer[1024], *token;

    if (*DataPointer1==NULL || *ParsePointer1 == NULL || *StringPointer1 == NULL)
    {
        printf("M: Neotvoreny subor.\n");
        return;
    }

    while (DataStructurePointer->next != NULL) {
        p1 = DataStructurePointer->next->next;
        free(DataStructurePointer->next);
        DataStructurePointer->next = p1;
    }
    while (ParseStructurePointer->next != NULL) {
        p2 = ParseStructurePointer->next->next;
        free(ParseStructurePointer->next);
        ParseStructurePointer->next = p2;
    }
    while (StringStructurePointer->next != NULL) {
        p3 = StringStructurePointer->next->next;
        free(StringStructurePointer->next);
        StringStructurePointer->next = p3;
    }

    *numElements=CountStrings(*DataPointer1);

    fseek(*DataPointer1, 0, SEEK_SET);
    fseek(*ParsePointer1, 0, SEEK_SET);
    fseek(*StringPointer1, 0, SEEK_SET);

    i=0;
    while (fgets(buffer, sizeof(buffer), *DataPointer1) != NULL && i < *numElements)
    {
       
        whileCounter=0;
        token = strtok(buffer," ");
        
        while (token!=NULL)
        {
            whileCounter++;
            if (whileCounter==1)
            {
                DataStructure1->DataFirstValue=atoi(token);
            }else if (whileCounter==2)
            {
                DataStructure1->DataSecondValue=atoi(token);
            }else if (whileCounter==3)
            {
                DataStructure1->DataThirdValue=atoi(token);
            }else if (whileCounter==4)
            {
                DataStructure1->DataFourthValue=atof(token);
            }
            
            token = strtok(NULL," ");
        }
        if (i < *numElements - 1) {
            DataStructure1->next = (struct DataStructure*)malloc(sizeof(struct DataStructure));
            DataStructure1 = DataStructure1->next;
        }
        i++;
    }
    DataStructure1->next = NULL;

    i=0;
    while (fgets(buffer, sizeof(buffer), *ParsePointer1) != NULL && i < *numElements)
    {
      
        token=strtok(buffer,"#");
        if (token[0] == '\n') {
            strcpy(ParseStructure1->ID, "NaN");
            token = strtok(NULL,"#");
        } else {
            strcpy(ParseStructure1->ID, token);
            token = strtok(NULL,"#");
        }
        if (token == NULL) {
            ParseStructure1->FirstValue=-1;
            token = strtok(NULL,"#");
        } else {
            ParseStructure1->FirstValue=atof(token);
            token = strtok(NULL,"#");
        }
        if (token == NULL){
            ParseStructure1->Hours = -1;
            ParseStructure1->Minutes = -1;
            token = strtok(NULL,"#");
        }else{
            sscanf(token, "%2d%2d", &a, &b);
            ParseStructure1->Hours = a;
            ParseStructure1->Minutes = b;
            token = strtok(NULL,"#");
        }
        if (token == NULL) {
            strcpy(ParseStructure1->Comment, "NaN");
            token = strtok(NULL,"#");
        } else {
            strcpy(ParseStructure1->Comment, token);
            token = strtok(NULL,"#");
        }
 
        ParseStructure1->next = (struct ParseStructure*)malloc(sizeof(struct ParseStructure));
        ParseStructure1 = ParseStructure1->next;
        i++;
    }
    ParseStructure1->next=NULL;
    

    i=0;
    while (fgets(buffer, sizeof(buffer), *StringPointer1) != NULL && i < *numElements)
    {
        strcpy(StringStructure1->ID, buffer);
        if (i < *numElements - 1) {
            StringStructure1->next=(struct StringStructure*)malloc(sizeof(struct StringStructure));
            StringStructure1=StringStructure1->next;
        }
        i++;
    }
    *numElements=i;
    StringStructure1->next=NULL;
    printf("M: Nacitalo sa %d zaznamov.\n", i);
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


void d(int *numElements, struct DataStructure *DataStructurePointer, struct ParseStructure *ParseStructurePointer, struct StringStructure *StringStructurePointer, struct DataStructure **DataStartPointer, struct ParseStructure **ParseStartPointer, struct StringStructure **StringStartPointer) {
    int FirstIndex, SecondIndex;
    int WhileCounter;
    struct DataStructure *DataPreviousElem1, *DataPreviousElem2, *DataCurrentElem1, *DataCurrentElem2, *DataIterator;
    struct ParseStructure *ParsePreviousElem1, *ParsePreviousElem2, *ParseCurrentElem1, *ParseCurrentElem2, *ParseIterator;
    struct StringStructure *StringPreviousElem1, *StringPreviousElem2, *StringCurrentElem1, *StringCurrentElem2, *StringIterator;
    struct DataStructure *DataTempNext;
    struct ParseStructure *ParseTempNext;
    struct StringStructure *StringTempNext;

    DataPreviousElem1 = DataPreviousElem2 = DataCurrentElem1 = DataCurrentElem2 = NULL;
    ParsePreviousElem1 = ParsePreviousElem2 = ParseCurrentElem1 = ParseCurrentElem2 = NULL;
    StringPreviousElem1 = StringPreviousElem2 = StringCurrentElem1 = StringCurrentElem2 = NULL;
    DataIterator = DataStructurePointer;
    ParseIterator = ParseStructurePointer;
    StringIterator = StringStructurePointer;
    WhileCounter = 1;

    scanf("%d", &FirstIndex);
    scanf("%d", &SecondIndex);

    if (FirstIndex < 1 || FirstIndex > *numElements || SecondIndex < 1 || SecondIndex > *numElements || FirstIndex == SecondIndex) {
        return;
    } else {
        if (FirstIndex > SecondIndex) {
            int TemporaryIndex = FirstIndex;
            FirstIndex = SecondIndex;
            SecondIndex = TemporaryIndex;
        }

        while (WhileCounter <= SecondIndex) {
            if (WhileCounter == FirstIndex - 1) {
                DataPreviousElem1 = DataIterator;
                ParsePreviousElem1 = ParseIterator;
                StringPreviousElem1 = StringIterator;
            }
            if (WhileCounter == FirstIndex) {
                DataCurrentElem1 = DataIterator;
                ParseCurrentElem1 = ParseIterator;
                StringCurrentElem1 = StringIterator;
            }
            if (WhileCounter == SecondIndex - 1) {
                DataPreviousElem2 = DataIterator;
                ParsePreviousElem2 = ParseIterator;
                StringPreviousElem2 = StringIterator;
            }
            if (WhileCounter == SecondIndex) {
                DataCurrentElem2 = DataIterator;
                ParseCurrentElem2 = ParseIterator;
                StringCurrentElem2 = StringIterator;
            }
            DataIterator = DataIterator->next;
            ParseIterator = ParseIterator->next;
            StringIterator = StringIterator->next;
            WhileCounter++;
        }

        if (DataCurrentElem1->next == DataCurrentElem2) {
            if (DataPreviousElem1 != NULL) {
                DataPreviousElem1->next = DataCurrentElem2;
            } else {
                *DataStartPointer = DataCurrentElem2;
            }

            DataCurrentElem1->next = DataCurrentElem2->next;
            DataCurrentElem2->next = DataCurrentElem1;

            if (ParsePreviousElem1 != NULL) {
                ParsePreviousElem1->next = ParseCurrentElem2;
            } else {
                *ParseStartPointer = ParseCurrentElem2;
            }

            ParseCurrentElem1->next = ParseCurrentElem2->next;
            ParseCurrentElem2->next = ParseCurrentElem1;

            if (StringPreviousElem1 != NULL) {
                StringPreviousElem1->next = StringCurrentElem2;
            } else {
                *StringStartPointer = StringCurrentElem2;
            }

            StringCurrentElem1->next = StringCurrentElem2->next;
            StringCurrentElem2->next = StringCurrentElem1;
        } else {
            if (DataPreviousElem1 != NULL) {
                DataPreviousElem1->next = DataCurrentElem2;
            } else {
                *DataStartPointer = DataCurrentElem2;
            }
            if (DataPreviousElem2 != NULL) {
                DataPreviousElem2->next = DataCurrentElem1;
            } else {
                *DataStartPointer = DataCurrentElem1;
            }

            DataTempNext = DataCurrentElem2->next;
            DataCurrentElem2->next = DataCurrentElem1->next;
            DataCurrentElem1->next = DataTempNext;

            if (ParsePreviousElem1 != NULL) {
                ParsePreviousElem1->next = ParseCurrentElem2;
            } else {
                *ParseStartPointer = ParseCurrentElem2;
            }

            if (ParsePreviousElem2 != NULL) {
                ParsePreviousElem2->next = ParseCurrentElem1;
            } else {
                *ParseStartPointer = ParseCurrentElem1;
            }

            ParseTempNext = ParseCurrentElem2->next;
            ParseCurrentElem2->next = ParseCurrentElem1->next;
            ParseCurrentElem1->next = ParseTempNext;

            if (StringPreviousElem1 != NULL) {
                StringPreviousElem1->next = StringCurrentElem2;
            } else {
                *StringStartPointer = StringCurrentElem2;
            }

            if (StringPreviousElem2 != NULL) {
                StringPreviousElem2->next = StringCurrentElem1;
            } else {
                *StringStartPointer = StringCurrentElem1;
            }

            StringTempNext = StringCurrentElem2->next;
            StringCurrentElem2->next = StringCurrentElem1->next;
            StringCurrentElem1->next = StringTempNext;
        }
    }
}


void a(int *numElements, struct DataStructure *DataStructurePointer, struct ParseStructure *ParseStructurePointer, struct StringStructure *StringStructurePointer, struct DataStructure **p1, struct ParseStructure **p2, struct StringStructure **p3) {
    struct DataStructure *DataNewStruct;
    struct ParseStructure *ParseNewStruct;
    struct StringStructure *StringNewStruct;
    struct DataStructure *currentData;
    struct ParseStructure *currentParse;
    struct StringStructure *currentString;
    char a[512], b[512], c[512], *token;
    int Hours = 0, Minutes = 0, YMain = 0, index;

    DataNewStruct = (struct DataStructure *)malloc(sizeof(struct DataStructure));
    ParseNewStruct = (struct ParseStructure *)malloc(sizeof(struct ParseStructure));
    StringNewStruct = (struct StringStructure *)malloc(sizeof(struct StringStructure));

    if (!DataNewStruct || !ParseNewStruct || !StringNewStruct) {
        printf("Memory allocation failed\n");
        return;
    }

    scanf("%d", &YMain);
    if (YMain < 1) YMain = 1;
    if (YMain > *numElements + 1) YMain = *numElements + 1;

    scanf(" %[^\n]", a);
    strcat(a, "\n");
    scanf(" %[^\n]", b);
    strcat(b, "\n");
    scanf(" %[^\n]", c);

    strcpy(StringNewStruct->ID, a);

    token = strtok(b, " ");
    index = 0;
    while (token != NULL) {
        index++;
        if (index == 1) DataNewStruct->DataFirstValue = atoi(token);
        else if (index == 2) DataNewStruct->DataSecondValue = atoi(token);
        else if (index == 3) DataNewStruct->DataThirdValue = atoi(token);
        else if (index == 4) DataNewStruct->DataFourthValue = atof(token);
        token = strtok(NULL, " ");
    }
    token = strtok(c, "#");
    strcpy(ParseNewStruct->ID, token ? token : "NaN");
    token = strtok(NULL, "#");
    ParseNewStruct->FirstValue = token ? atof(token) : -1;
    token = strtok(NULL, "#");
    if (token) {
        sscanf(token, "%2d%2d", &Hours, &Minutes);
        ParseNewStruct->Hours = Hours;
        ParseNewStruct->Minutes = Minutes;
    } else {
        ParseNewStruct->Hours = -1;
        ParseNewStruct->Minutes = -1;
    }
    token = strtok(NULL, "#");
    strcpy(ParseNewStruct->Comment, token ? token : "NaN");

   

    (*numElements)++;

    if (YMain == 1) {
        DataNewStruct->next = DataStructurePointer;
        ParseNewStruct->next = ParseStructurePointer;
        StringNewStruct->next = StringStructurePointer;

        *p1 = DataNewStruct;
        *p2 = ParseNewStruct;
        *p3 = StringNewStruct;
        return;
    }

    currentData = DataStructurePointer;
    currentParse = ParseStructurePointer;
    currentString = StringStructurePointer;

    for (index = 1; index < YMain - 1; index++) {
        currentData = currentData->next;
        currentParse = currentParse->next;
        currentString = currentString->next;
    }

    DataNewStruct->next = currentData->next;
    currentData->next = DataNewStruct;

    ParseNewStruct->next = currentParse->next;
    currentParse->next = ParseNewStruct;

    StringNewStruct->next = currentString->next;
    currentString->next = StringNewStruct;

}


void q(int *numElements, char ***DataTxtLions, char ***ParseTxtLions, char ***StringTxtLions) {
    int YMain = 0, WhileCounter = 0, i = 0;
    char **DataNewArray = NULL;
    char **ParseNewArray = NULL;
    char **StringNewArray = NULL;
    char a[512],b[512],c[512];

    if (*DataTxtLions == NULL || *ParseTxtLions == NULL || *StringTxtLions == NULL) {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }

    DataNewArray = malloc((*numElements+1) * sizeof(char *));
    ParseNewArray = malloc((*numElements+1) * sizeof(char *));
    StringNewArray = malloc((*numElements+1) * sizeof(char *));

    for (i = 0; i < *numElements + 1; i++) {
        DataNewArray[i] = malloc(256 * sizeof(char));
        ParseNewArray[i] = malloc(256 * sizeof(char));
        StringNewArray[i] = malloc(256 * sizeof(char));
    }

    scanf("%d", &YMain);
    YMain--;
    if (YMain>*numElements)
    {
        YMain=*numElements;
    }

    WhileCounter = 0;
    while (WhileCounter < *numElements + 1) {
        if (WhileCounter < YMain) {
            strcpy(DataNewArray[WhileCounter], (*DataTxtLions)[WhileCounter]);
            strcpy(ParseNewArray[WhileCounter], (*ParseTxtLions)[WhileCounter]);
            strcpy(StringNewArray[WhileCounter], (*StringTxtLions)[WhileCounter]);
        } else if (WhileCounter == YMain) {
            scanf(" %[^\n]", a);
            strcpy(StringNewArray[WhileCounter],strcat(a, "\n"));
            scanf(" %[^\n]", b);
            strcpy(DataNewArray[WhileCounter],strcat(b, "\n"));
            scanf(" %[^\n]", c);
            strcpy(ParseNewArray[WhileCounter],strcat(c, "\n"));
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
    strcat(idToDelete, "\n");
    
    
    for (i = 0; i < *numElements; i++) {
        if (strcmp((*StringTxtLions)[i], idToDelete) == 0) {
            deletedCount++;
            free((*DataTxtLions)[i]);
            free((*ParseTxtLions)[i]);
            free((*StringTxtLions)[i]);
            (*DataTxtLions)[i]=NULL;
            (*ParseTxtLions)[i]=NULL;
            (*StringTxtLions)[i]=NULL;

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


void s(int *numElements, struct DataStructure *DataStructurePointer, struct ParseStructure *ParseStructurePointer, struct StringStructure *StringStructurePointer,struct DataStructure **p1D, struct ParseStructure **p2P, struct StringStructure **p3S) {
    struct DataStructure *p1 = NULL;
    struct ParseStructure *p2 = NULL;
    struct StringStructure *p3 = NULL;

    char String[512];
    int deletedCount = 0;

    if (DataStructurePointer->next == NULL || ParseStructurePointer->next == NULL || StringStructurePointer->next == NULL) {
        printf("S: Spajany zoznam nie je vytvorený.\n");
        return;
    }

    scanf("%s", String);
    strcat(String, "\n");

    while (StringStructurePointer != NULL) {
        if (strcmp(String,StringStructurePointer->ID)==0)
        {
            p1 = DataStructurePointer;
            p2 = ParseStructurePointer;
            p3 = StringStructurePointer;

            DataStructurePointer = DataStructurePointer->next;
            ParseStructurePointer = ParseStructurePointer->next;
            StringStructurePointer = StringStructurePointer->next;

            *p1D = DataStructurePointer;
            *p2P = ParseStructurePointer;
            *p3S = StringStructurePointer;

            free(p1);
            free(p2);
            free(p3);

            deletedCount++;
        }else if (StringStructurePointer->next != NULL && strcmp(StringStructurePointer->next->ID, String) == 0) {

            p1 = DataStructurePointer->next;
            p2 = ParseStructurePointer->next;
            p3 = StringStructurePointer->next;

            DataStructurePointer->next = p1->next;
            ParseStructurePointer->next = p2->next;
            StringStructurePointer->next = p3->next;

            free(p1);
            free(p2);
            free(p3);

            deletedCount++;
        } else {
            DataStructurePointer = DataStructurePointer->next;
            ParseStructurePointer = ParseStructurePointer->next;
            StringStructurePointer = StringStructurePointer->next;
        }
    }

    *numElements -= deletedCount;

    printf("S: Vymazalo sa : %d zaznamov !\n", deletedCount);
}


void v(FILE **DataPointer1,FILE **ParsePointer1,FILE **StringPointer1,  char ***DataTxtLions,char ***ParseTxtLions,char ***StringTxtLions, int numElements, int *p_numElements,struct DataStructure *DataStructurePointer,struct ParseStructure *ParseStructurePointer,struct StringStructure *StringStructurePointer,int *numElements_PZ) {
    int NumberOfFunction;
    scanf("%d",&NumberOfFunction);
    if (NumberOfFunction==1)
    {
        v1(DataPointer1,ParsePointer1,StringPointer1,p_numElements,numElements_PZ);
    }else if (NumberOfFunction==2)
    {
        v2(numElements, *DataTxtLions, *ParseTxtLions, *StringTxtLions);
    }else if (NumberOfFunction==3)
    {
        v3(DataStructurePointer,ParseStructurePointer,StringStructurePointer,numElements_PZ);
    }else{
        printf("V: Nespravne volba vypisu.\n");
    }
}


void e(char ***ParseTxtLions, int numElements) {
    int i = 0;
    char ExploreString[512];
    int length;

    if (*ParseTxtLions == NULL) {
        printf("E: Polia nie su vytvorene.\n");
        return;
    }
    getchar();
    fgets(ExploreString,512,stdin);

    length = (int)strlen(ExploreString);
    if (length > 0 && ExploreString[length - 1] == '\n') {
        ExploreString[length - 1] = '\0';
    }
    
    for (i = 0; i < numElements; i++) {
        if (strstr((*ParseTxtLions)[i], ExploreString) != NULL) {
            printf("%s", (*ParseTxtLions)[i]);
        }
    }
}


int main(void)
{
    int i=0;
    FILE *DataPointer = NULL;
    FILE *ParsePointer = NULL;
    FILE *StringPointer = NULL;
    FILE **DataPointer1 = &DataPointer;
    FILE **ParsePointer1 = &ParsePointer;
    FILE **StringPointer1 = &StringPointer;
    struct DataStructure *DataStructurePointer = NULL;
    struct DataStructure *p1 = NULL;
    struct DataStructure **p1D = &DataStructurePointer;
    struct ParseStructure *ParseStructurePointer = NULL;
    struct ParseStructure *p2 = NULL;
    struct ParseStructure **p2P = &ParseStructurePointer;
    struct StringStructure *StringStructurePointer = NULL;
    struct StringStructure *p3 = NULL;
    struct StringStructure **p3S = &StringStructurePointer;
    char CalledFunction = 'p';
    int largestDataIndex = 0, largestParseIndex = 0,largestStringIndex = 0;
    int *pLargestDataIndex = &largestDataIndex, *pLargestParseIndex = &largestParseIndex, *pLargestStringIndex = &largestStringIndex;
    char **DataTxtLions = NULL;
    char **ParseTxtLions = NULL;
    char **StringTxtLions = NULL;
    int numElements=0,numElementsP=0;
    int *p_numElements = &numElements;
    int *numElements_PZ = &numElementsP;
    DataStructurePointer = (struct DataStructure*)malloc(sizeof(struct DataStructure));
    ParseStructurePointer = (struct ParseStructure*)malloc(sizeof(struct ParseStructure));
    StringStructurePointer = (struct StringStructure*)malloc(sizeof(struct StringStructure));
    DataStructurePointer->next = NULL;
    StringStructurePointer->next = NULL;
    ParseStructurePointer->next = NULL;
    while (1)
    {
        scanf("%c",&CalledFunction);
        if (CalledFunction=='v')
        {
            v(DataPointer1, ParsePointer1, StringPointer1, &DataTxtLions, &ParseTxtLions, &StringTxtLions,numElements,p_numElements,DataStructurePointer,ParseStructurePointer,StringStructurePointer,numElements_PZ);
        } else if (CalledFunction=='h')
        {
            h(StringPointer1);
        } else if (CalledFunction == 'k') {
            if (DataPointer != NULL){
                fclose(DataPointer); 
            } 
            if (StringPointer != NULL){
                fclose(StringPointer); 
            }
            if (ParsePointer != NULL){
                fclose(ParsePointer); 
            }

            if (DataTxtLions != NULL) {
                for (i = 0; i < numElements; i++) {
                    if (DataTxtLions[i] != NULL) {
                        free(DataTxtLions[i]);
                        DataTxtLions[i] = NULL;
                    }
                }
                free(DataTxtLions);
                DataTxtLions = NULL;
            }

            if (ParseTxtLions != NULL) {
                for (i = 0; i < numElements; i++) {
                    if (ParseTxtLions[i] != NULL) {
                        free(ParseTxtLions[i]);
                        ParseTxtLions[i] = NULL;
                    }
                }
                free(ParseTxtLions);
                ParseTxtLions = NULL;
            }

            if (StringTxtLions != NULL) {
                for (i = 0; i < numElements; i++) {
                    if (StringTxtLions[i] != NULL) {
                        free(StringTxtLions[i]);
                        StringTxtLions[i] = NULL;
                    }
                }
                free(StringTxtLions);
                StringTxtLions = NULL;
            }

            while (DataStructurePointer != NULL) {
                p1 = DataStructurePointer->next;
                free(DataStructurePointer);
                DataStructurePointer = p1;
            }
            while (ParseStructurePointer != NULL) {
                p2 = ParseStructurePointer->next;
                free(ParseStructurePointer);
                ParseStructurePointer = p2;
            }
            while (StringStructurePointer != NULL) {
                p3 = StringStructurePointer->next;
                free(StringStructurePointer);
                StringStructurePointer = p3;
            }
            break; 
        } else if (CalledFunction=='n')
        {
            n(DataPointer1, ParsePointer1, StringPointer1, pLargestDataIndex, pLargestParseIndex, pLargestStringIndex, &DataTxtLions, &ParseTxtLions, &StringTxtLions,&numElements);
        }else if (CalledFunction=='q')
        {
            q(&numElements, &DataTxtLions, &ParseTxtLions, &StringTxtLions);
        }else if (CalledFunction=='w')
        {
            w(&numElements, &DataTxtLions, &ParseTxtLions, &StringTxtLions);
        }else if (CalledFunction=='e')
        {
            e(&ParseTxtLions,numElements);
        }else if (CalledFunction=='m')
        {
            m(DataPointer1, ParsePointer1, StringPointer1,&numElementsP,DataStructurePointer,ParseStructurePointer,StringStructurePointer);
        }else if (CalledFunction=='a')
        {
            a(&numElementsP,DataStructurePointer,ParseStructurePointer,StringStructurePointer,p1D,p2P,p3S);
        }else if (CalledFunction=='s')
        {
            s(&numElementsP,DataStructurePointer,ParseStructurePointer,StringStructurePointer,p1D,p2P,p3S);
        }else if (CalledFunction=='d')
        {
            d(&numElementsP,DataStructurePointer,ParseStructurePointer,StringStructurePointer,p1D,p2P,p3S);
        }
    }
    return 0;
}
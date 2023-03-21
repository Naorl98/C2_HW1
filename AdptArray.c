#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int ArrSize;
    PElement *pElemArr;
    DEL_FUNC del;
    COPY_FUNC copy;
    PRINT_FUNC print;
} AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyy, DEL_FUNC dell, PRINT_FUNC printt)
{
    PAdptArray a = (PAdptArray)malloc(sizeof(AdptArray)); 
    if (a == NULL) 
        return NULL;
    a->del = dell;
    a->copy = copyy;
    a->print = printt;
    a->ArrSize = 0;
    a->pElemArr = NULL;
    return a;
}

void DeleteAdptArray(PAdptArray a){
	if (a == NULL)
		return;
	if(a->ArrSize > 0)
	{
		    a->del(a->pElemArr);
	}
	free(a);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
    int changed = 0;
    PElement *newpElemArr;
    if (pArr == NULL || idx < 0)
        return FAIL;
    if (idx >= pArr->ArrSize)
    {
        if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) ==
            NULL)
            return FAIL;
		for (int i = 0; i < pArr->ArrSize; i++)
        {
            newpElemArr[i] = (pArr->pElemArr)[i];
        }
        newpElemArr[idx] = pArr->copy(pNewElem);
        free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
        changed = 1;
    }
    else{
        pArr->del((pArr->pElemArr)[idx]);
        (pArr->pElemArr)[idx] = pArr->copy(pNewElem);
    }
    if( changed == 1)
        pArr->ArrSize = idx + 1;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray a, int idx){
    if( a == NULL)
        return NULL;
    if(idx < 0 || idx > (a->ArrSize))
        return NULL;
    return ((a->pElemArr)[idx]);
}
int GetAdptArraySize(PAdptArray a){
    if(a == NULL)
        return -1;
    return (a->ArrSize);
}
void PrintDB(PAdptArray a){

    if (a == NULL)
        return;
    for (int i = 0; i < a->ArrSize; i++)
    {
        if((a->pElemArr)[i])
            a->print((a->pElemArr)[i]);
    }
}   




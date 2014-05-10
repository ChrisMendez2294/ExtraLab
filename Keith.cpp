//**************************************************************************************************************
// FILE: Keith.cpp 
//**************************************************************************************************************
#include <iostream>
#include <cmath>
#include "Main.hpp"
#include "Keith.hpp"
#include "Thread.hpp"

using std::cout;
using std::endl;

//==============================================================================================================
// Static Function Declarations
//==============================================================================================================
static bool IsKeith(ulong const pNum);

//==============================================================================================================
// Function Definitions
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// FindKeiths()
//
// Finds all Keith numbers from 10 to pLimit. We do nothing with the numbers we find.
//--------------------------------------------------------------------------------------------------------------
void FindKeiths
    (
    ulong pLimit
    )
{
    if (GetVerbose()) cout << "FindKeiths() Begin" << endl;
    for (ulong n = 10L; n <= pLimit; n++) {
        if (IsKeith(n))
            ;
    }
    if (GetVerbose()) cout << "FindKeith() End" << endl;
}

//--------------------------------------------------------------------------------------------------------------
// FindKeithsThread()
//
// A thread which finds all Keith numbers from 10 to pState->mLimit.
//--------------------------------------------------------------------------------------------------------------
void *FindKeithsThread
    (
    void *pState
    )
{
    if (GetVerbose()) cout << "FindKeithsThread() Begin" << endl;
    ThreadState *state = static_cast<ThreadState *>(pState);
    FindKeiths(state->mLimit);
    state->mExitCode = 0;
    if (GetVerbose()) cout << "FindKeithsThread() End" << endl;
    pthread_exit(pState);
}

//--------------------------------------------------------------------------------------------------------------
// IsKeith()
//
// Returns true if pNum is a Keith number.
//--------------------------------------------------------------------------------------------------------------
static bool IsKeith(ulong const pNum){
	int n, size;
	if(pNum < 10) return false; //This should never happen!

	// The greatest an unsigned long can be is 10 digits, but there are no 10 digit Keith numbers
	if(pNum <= 99L) size = 2;
	else if(pNum <= 999L) size = 3;
	else if(pNum <= 9999L) size = 4;
	else if(pNum <= 99999L) size = 5;
	else if(pNum <= 999999L) size = 6;
	else if(pNum <= 9999999L) size = 7;
	else if(pNum <= 99999999L) size = 8;
	else if(pNum <= 999999999L) size = 9;
	else return false;

	n = size - 1;
	ulong k_array[size];

	//Store the digits of our original number into the array
	for(int i = n; i >= 0; i--){
		int tmpNum = pNum / (10*i);
		k_array[i] = tmpNum % 10;
	}

	/*******************************************************************
	* Compute until original value is found, or current value is greater
	* than the original value, at which point we are sure that pNum is
	* not a Keith number.
	*******************************************************************/
	do {
		int sum = 0;
		for(int i = 0; i <= n; i++) sum = sum + k_array[i];
		for(int i = 0; i < n; i++) k_array[i] = k_array[i+1];
		k_array[n] = sum;

		if(k_array[n] == pNum) return true;
	} while(k_array[n] < pNum);
	return false;
}

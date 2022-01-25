#include <stdio.h>
#include <assert.h>
#include "misaligned.h"

// Decomposed below function part that can be tested
ColorPair provideColorMap(int i, int j) {
    ColorPair myColorPair;
	myColorPair.myNumberPair = i * 5 + j;
	myColorPair.myMajorColor = majorColor[i];
    // Intention of the test is to fail and get detected.
    // Hence set the index below as 'i' instead of 'j' as given in original problem.
	myColorPair.myMinorColor = minorColor[i]; 

    return myColorPair;
}

// Let's dont care and print whatever we receive. Could be a null string or any invalid characters!!
void FormatAndPrintColorMapToDisplay(ColorPair ColorPairReceived) {
	printf("%d | %s | %s\n", ColorPairReceived.myNumberPair, ColorPairReceived.myMajorColor, ColorPairReceived.myMinorColor);
}

// Loop through, extract and send ColorMap to formatter function for printing
int printColorMap() {
	int i = 0, j = 0;
	for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
			FormatAndPrintColorMapToDisplay(provideColorMap(i,j));
		}
	}
    return i * 5 + j;
}

void unitTestColorMapforRandomPairNumber(int expectedNumberPair) {
	if((expectedNumberPair > 0) && expectedNumberPair < 26)	{
		int loopCount_i = (expectedNumberPair-1)/5;
		int loopCount_j = (expectedNumberPair-1)%5;
		ColorPair testColorpair = provideColorMap(loopCount_i,loopCount_j);
 		assert(testColorpair.myNumberPair == expectedNumberPair);
 		assert(testColorpair.myMajorColor == majorColor[loopCount_i]);
 		assert(testColorpair.myMinorColor == minorColor[loopCount_j]);
	}
	else
		printf("Sorry, that's not a valid PairNumber. Use 1 to 25 please!!\n");
}

int main() {
    int result = printColorMap();
    assert(result == 25);
    unitTestColorMapforRandomPairNumber(5);
    unitTestColorMapforRandomPairNumber(23);
    unitTestColorMapforRandomPairNumber(-4);
    unitTestColorMapforRandomPairNumber(72);

    printf("All is well (maybe!)\n");
    return 0;
}

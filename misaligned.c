#include <stdio.h>
#include <assert.h>
#include "misaligned.h"

// Decomposed below function part that can be tested
ColorPair provideColorMap(int i, int j) {
    ColorPair myColorPair;
	myColorPair.myNumberPair = (i * 5) + j + 1;
	myColorPair.myMajorColor = majorColor[i];
    // Bug on below line is now fixed with correct loopControl variable]
	myColorPair.myMinorColor = minorColor[j]; 

    return myColorPair;
}

// Let's dont care and print whatever we receive. Could be a null string or any invalid characters!!
void FormatAndPrintColorMapToDisplay(ColorPair ColorPairReceived) {
	printf("%d | %s | %s\n", ColorPairReceived.myNumberPair, ColorPairReceived.myMajorColor, ColorPairReceived.myMinorColor);
}

// Loop through, extract and send ColorMap to formatter function for printing
int printColorMap(void (*pointsToFormatAndPrintColorMapToDisplay)(ColorPair)) {
	int i = 0, j = 0;
	for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
			pointsToFormatAndPrintColorMapToDisplay(provideColorMap(i,j));
		}
	}
    return i * 5 + j;
}

void unitTestColorMapforRandomPairNumber(int expectedNumberPair) {
    int loopCount_i = (expectedNumberPair-1)/5;
	int loopCount_j = (expectedNumberPair-1)%5;
	ColorPair testColorpair = provideColorMap(loopCount_i,loopCount_j);
 	assert(testColorpair.myNumberPair == expectedNumberPair);
 	assert(testColorpair.myMajorColor == majorColor[loopCount_i]);
 	assert(testColorpair.myMinorColor == minorColor[loopCount_j]);
}

int main() {
    int result = printColorMap(&FormatAndPrintColorMapToDisplay);
    assert(result == 30);
    
    for(int i=1; i<=25; i++)
        unitTestColorMapforRandomPairNumber(i);

    printf("All is well\n");
    return 0;
}

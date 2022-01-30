#include <stdio.h>
#include <assert.h>

char provideTShirtSizeInCharacter(int inputSizeInCms) {
    char returnSizeName = '\0';

    if(inputSizeInCms < 36)
        returnSizeName = '!'; // may not be a valid size, e.g: Negative Values.

    else if((inputSizeInCms >= 36) && (inputSizeInCms <= 38))
        returnSizeName = 'S';

    else if((inputSizeInCms >= 39) && (inputSizeInCms <= 41)) 
        returnSizeName = 'M';

    else if((inputSizeInCms >= 42) && (inputSizeInCms <= 44))
        returnSizeName = 'L';
        
    else 
        returnSizeName = '!'; // May not be a valid size. Reject!
    
    return returnSizeName;
}

void unitTest_provideTShirtSizeInCharacter(int expectedSizeNumber, char expectedSizeCharacter) {
    assert(provideTShirtSizeInCharacter(expectedSizeNumber) == expectedSizeCharacter);
}

int main() {
    unitTest_provideTShirtSizeInCharacter(-250,'!');
    unitTest_provideTShirtSizeInCharacter(0,'!');
    unitTest_provideTShirtSizeInCharacter(24,'!');

    unitTest_provideTShirtSizeInCharacter(36,'S');
    unitTest_provideTShirtSizeInCharacter(37,'S');
    unitTest_provideTShirtSizeInCharacter(38,'S');
    
    unitTest_provideTShirtSizeInCharacter(39,'M');
    unitTest_provideTShirtSizeInCharacter(40,'M');
    unitTest_provideTShirtSizeInCharacter(41,'M');
    
    unitTest_provideTShirtSizeInCharacter(42,'L');
    unitTest_provideTShirtSizeInCharacter(43,'L');
    unitTest_provideTShirtSizeInCharacter(44,'L');
    
    unitTest_provideTShirtSizeInCharacter(45,'!');
    unitTest_provideTShirtSizeInCharacter(10000,'!');
    
    printf("All is well..!\n");
    return 0;
}

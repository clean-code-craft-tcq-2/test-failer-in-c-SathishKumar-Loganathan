#include <stdio.h>
#include <assert.h>

#define THRESHOLD_TEMP_IN_CELSIUS 200.0F

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    if(celcius > THRESHOLD_TEMP_IN_CELSIUS) {
        printf("ALERT: Temperature is %.1f celcius.\n", celcius);
        return 500;     // Return 500 for not-ok
    }
    else
        return 200;    // Return 200 for ok
}

float getCelsiusFromFarenheit(float farenheit)  {
	return (farenheit - 32) * 5 / 9;
}

void alertInCelcius(float farenheit, float (*getCelsiusFromFarenheit)(float), int (*pointsToNetworkAlertStub)(float))
{
    float celcius = getCelsiusFromFarenheit(farenheit);
    int returnCode = pointsToNetworkAlertStub(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        alertFailureCount += 1;
    }
}

void unitTest_alertInCelcius(float inputfarenheit, int expectedFailCount) {
    alertInCelcius(inputfarenheit, &getCelsiusFromFarenheit, &networkAlertStub);
    assert(alertFailureCount == expectedFailCount);
}

void unitTest_getCelsiusFromFarenheit(float inputfarenheit, float expectedCelsius) {
    assert(getCelsiusFromFarenheit(inputfarenheit) == expectedCelsius);
}

int main() {

    // Test the conversion function with entire range of input
    unitTest_getCelsiusFromFarenheit(-720.5, -418.055556f);
    unitTest_getCelsiusFromFarenheit(0, -17.777778f);
    unitTest_getCelsiusFromFarenheit(400.5, 204.722222f);
    unitTest_getCelsiusFromFarenheit(303.6, 150.888889f);
    unitTest_getCelsiusFromFarenheit(1234.567, 668.092778f);

    // Test the alerter function 
    assert(alertFailureCount == 0);     // Check whether the failureCount is always zero, before the start of Test
    unitTest_alertInCelcius(-720.5, 0);
    unitTest_alertInCelcius(0, 0);
    unitTest_alertInCelcius(400.5, 1);
    unitTest_alertInCelcius(303.6, 1);
    unitTest_alertInCelcius(1234.567, 2);
    
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well \n");
    return 0;
}

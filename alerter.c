#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    if(celcius > 200.0f) {
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

int main() {
    // Test above threshold
	assert(getCelsiusFromFarenheit(400.5) == 204.722222f);
    alertInCelcius(400.5, &getCelsiusFromFarenheit, &networkAlertStub);
    assert(alertFailureCount == 1);
    
    //Test below threshold
	assert(getCelsiusFromFarenheit(303.6) == 150.888889f);
    alertInCelcius(303.6, &getCelsiusFromFarenheit, &networkAlertStub);
    assert(alertFailureCount == 1);
    
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well \n");
    return 0;
}

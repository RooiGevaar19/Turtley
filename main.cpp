#include <cstdio>
#include "modules/ApplicationTest.h"
#include "modules/ApplicationTest2.h"

int main(int argc, char* args[]) {
    int x;
    printf("1 - Test 1\n2 - Test 2\n");
    scanf("%i", &x);
    if (x == 1) {
        ApplicationTest app;
        app.run();    
    } else if (x == 2) {
        ApplicationTest2 app;
        app.run();    
    }
    return 0;
}

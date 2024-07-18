#include <stdio.h>
#include <stdlib.h>

int main() {
    // Retrieve the value of the PATH environment variable
    const char *path = getenv("USER");
    
    if (path != NULL) {
        printf("PATH: %s\n", path);
    } else {
        printf("PATH environment variable not found.\n");
    }
    
    return 0;
}

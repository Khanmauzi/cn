
#include <string>
#include <iostream>
#include <stdio.h>

/**
 * This is not tested in windows.
 * Windows users should use _popen and _pclose.
 * http://msdn.microsoft.com/en-us/library/aa298534(v=vs.60).aspx
 */

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe){
        return "ERROR";
    }
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

int main ()
{
    std::string retval = exec("ls -l");
    std::cout << "Return: " << retval << std::endl;
    return 0;
}

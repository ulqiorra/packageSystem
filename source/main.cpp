#include "PackageController.h"

// main function with PackageController test object
int main(int argc, char *argv[])
{
    PackageController tst;

    while(tst.getStatus())
    {
        tst.getInput(std::cin);
        tst.executeCommand();
    }

    return 0;
}
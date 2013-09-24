#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    fileApp obj(argv[1],argv[2],argv[3]);

    if(!obj.SetupApp()) return -1;      //if fail to initial ,return -1 for error

    obj.BeginApp();

    return 0;
}

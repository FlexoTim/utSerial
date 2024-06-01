#include "utSerial.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    utPetoi::commandline = vector<string>(argv, argv + argc);

    return RUN_ALL_TESTS();
}
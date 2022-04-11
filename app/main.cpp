//
// Created by user on 2022/4/11 0011.
//
#include <iostream>
#include <functional>
#include <memory>
#include "opus_fec.h"

int main(int argc, char * argv[])
{
    OpusFec* opusFec = new OpusFec();
    opusFec->test();

    return 0;
}


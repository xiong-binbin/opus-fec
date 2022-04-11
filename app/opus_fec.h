//
// Created by user on 2022/4/11 0011.
//

#ifndef OPUS_FEC_OPUS_FEC_H
#define OPUS_FEC_OPUS_FEC_H

#include <iostream>
#include <functional>
#include <memory>
#include "opus/opus.h"

class OpusFec
{
public:
    OpusFec();
    ~OpusFec();

    void test();

private:
    OpusDecoder*  opusDecode{ nullptr };
    OpusEncoder*  opusEncode{ nullptr };
};


#endif //OPUS_FEC_OPUS_FEC_H

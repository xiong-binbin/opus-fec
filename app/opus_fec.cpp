//
// Created by user on 2022/4/11 0011.
//

#include "opus_fec.h"
#include <assert.h>
#include <fstream>
#include <memory>
#include <string.h>

#define  OPUS_DEFAULT_SAMPLE_RATE  (48000)
#define  OPUS_DEFAULT_CHANNELS     (2)


OpusFec::OpusFec()
{
    int rt = 0;

    //创建OPUS编码器
    opusEncode = opus_encoder_create(OPUS_DEFAULT_SAMPLE_RATE, OPUS_DEFAULT_CHANNELS, OPUS_APPLICATION_VOIP, &rt);
    assert(OPUS_OK == rt);

    opus_encoder_ctl(opusEncode, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
    opus_encoder_ctl(opusEncode, OPUS_SET_BITRATE(OPUS_AUTO));
    opus_encoder_ctl(opusEncode, OPUS_SET_INBAND_FEC(1));

    //创建opus音频解码器
    opusDecode = opus_decoder_create(OPUS_DEFAULT_SAMPLE_RATE, OPUS_DEFAULT_CHANNELS, &rt);
    assert(OPUS_OK == rt);
}

OpusFec::~OpusFec()
{

}

void OpusFec::test()
{
    uint32_t   pcmDataSize = (OPUS_DEFAULT_SAMPLE_RATE/50)*OPUS_DEFAULT_CHANNELS*2;
    uint32_t   opusDataSize = 0;
    opus_int16 pcmData[4*1024] = {0};
    uint8_t    opusData[4*1024] = {0};

    int rt = 0;
    int i = 0;
    std::ifstream inFile;
    inFile.open("../test.pcm", std::ios::binary);
    inFile.seekg(0, std::ifstream::end);
    int fileLength = inFile.tellg();
    inFile.seekg(0, std::ifstream::beg);

    std::ofstream outFile;
    outFile.open("out.pcm", std::ios::binary);

    std::ofstream tmpFile;
    tmpFile.open("tmp.pcm", std::ios::binary);

    while (!inFile.eof() || fileLength < pcmDataSize)
    {
        memset((void*)pcmData, 0, sizeof(pcmData));
        memset((void*)opusData, 0, sizeof(opusData));
        inFile.read((char*)pcmData, pcmDataSize);
        fileLength -= pcmDataSize;
        i++;

        //opus编码
        opusDataSize = opus_encode(this->opusEncode, (opus_int16*)pcmData, OPUS_DEFAULT_SAMPLE_RATE/50, opusData, sizeof(opusData));

        //记录开始丢包时的音频
        if(i >= 60 && i <= 200) {
            tmpFile.write((const char*)pcmData, pcmDataSize);
        }

        //模拟丢包
        if(60 <= i && i <= 198 && (i%2 == 0)) {
            continue;
        }

        if(61 <= i && i <= 199 && (i%2 == 1)) {
            //opus向前纠错
            rt = opus_decode(this->opusDecode, (const unsigned char*)opusData, opusDataSize, (opus_int16*)pcmData, OPUS_DEFAULT_SAMPLE_RATE/50, 1);
            assert(rt >= 0);
            outFile.write((const char*)pcmData, rt*OPUS_DEFAULT_CHANNELS*2);
        }

        //opus解码
        rt = opus_decode(this->opusDecode, (const unsigned char*)opusData, opusDataSize, (opus_int16*)pcmData, OPUS_DEFAULT_SAMPLE_RATE/50, 0);
        assert(rt >= 0);
        outFile.write((const char*)pcmData, rt*OPUS_DEFAULT_CHANNELS*2);
    }

    inFile.close();
    outFile.close();
    tmpFile.close();

    std::cout << "run end! max i=" << i << std::endl;
}


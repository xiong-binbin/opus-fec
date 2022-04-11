//
// Created by user on 2022/4/11 0011.
//

#include "opus_fec.h"
#include <assert.h>

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

}


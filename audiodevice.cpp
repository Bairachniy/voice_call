#include "audiodevice.h"

AudioDevice::AudioDevice(QObject *parent) : QObject(parent)
{
    m_input.reset(new QAudioInput(getAudioFormat()));
    m_output.reset(new QAudioOutput(getAudioFormat()));
    m_device.reset(m_output->start());
}

AudioDevice::~AudioDevice(){}

void AudioDevice::stop()
{
    m_input->stop();
}

void AudioDevice::play(QByteArray data)
{
    m_device->write(data.data(), data.size());
}

void AudioDevice::read(QUdpSocket *socket)
{
    m_input->start(socket);
}

QAudioFormat AudioDevice::getAudioFormat(int sampleRate, int chanelCount, int sampleSize, QString codec)
{
    QAudioFormat format;

    format.setSampleRate(sampleRate);
    format.setChannelCount(chanelCount);
    format.setSampleSize(sampleSize);
    format.setCodec(codec);

    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(format))
        format = info.nearestFormat(format);

    return format;
}

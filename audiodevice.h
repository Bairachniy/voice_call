#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <QObject>
#include <QUdpSocket>
#include<QtMultimedia/QAudioInput>
#include<QtMultimedia/QAudioOutput>

class AudioDevice : public QObject
{
    Q_OBJECT
public:
    explicit AudioDevice(QObject *parent = nullptr);
    ~AudioDevice();
    void stop();

public slots:
    void play(QByteArray data);
    void read(QUdpSocket* socket);

private:
    std::unique_ptr<QAudioInput> m_input;
    std::unique_ptr<QAudioOutput> m_output;

    std::unique_ptr<QIODevice> m_device;
    QAudioFormat getAudioFormat(int sampleRate = 128000, int chanelCount = 1, int sampleSize = 32, QString codec = "audio/pcm");

};

#endif // AUDIODEVICE_H

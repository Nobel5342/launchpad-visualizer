#include "MidiManager.h"
#include <QDebug>

MidiManager::MidiManager(QObject *parent)
    : QObject(parent)
    , m_isInitialized(false)
{
    try {
        // RtMidiインスタンス作成
        m_midiIn = std::make_unique<RtMidiIn>();
        m_isInitialized = true;
    } catch (RtMidiError &error) {
        qCritical() << "RtMidi初期化エラー:" << QString::fromStdString(error.getMessage());
        m_isInitialized = false;
    }
}

MidiManager::~MidiManager()
{
    closeInputDevice();
}

QStringList MidiManager::getAvailableInputDevices() const
{
    QStringList devices;
    
    if (!m_isInitialized) {
        return devices;
    }
    
    try {
        // 利用可能なMIDI入力ポートを取得
        unsigned int portCount = m_midiIn->getPortCount();
        
        for (unsigned int i = 0; i < portCount; i++) {
            QString deviceName = QString::fromStdString(m_midiIn->getPortName(i));
            devices.append(deviceName);
        }
    } catch (RtMidiError &error) {
        qWarning() << "MIDIデバイス列挙エラー:" << QString::fromStdString(error.getMessage());
    }
    
    return devices;
}

bool MidiManager::openInputDevice(int deviceIndex)
{
    if (!m_isInitialized) {
        qWarning() << "MIDIマネージャが初期化されていません";
        return false;
    }
    
    closeInputDevice();  // 既に開いている場合は閉じる
    
    try {
        // MIDI入力ポートを開く
        unsigned int portCount = m_midiIn->getPortCount();
        
        if (deviceIndex < 0 || static_cast<unsigned int>(deviceIndex) >= portCount) {
            qWarning() << "無効なデバイスインデックス:" << deviceIndex;
            return false;
        }
        
        m_midiIn->openPort(deviceIndex);
        
        // コールバック関数を設定
        m_midiIn->setCallback(&MidiManager::midiCallback, this);
        
        // すべてのタイプのMIDIメッセージを受信
        m_midiIn->ignoreTypes(false, false, false);
        
        QString deviceName = QString::fromStdString(m_midiIn->getPortName(deviceIndex));
        qInfo() << "MIDI入力デバイスを開きました:" << deviceName;
        return true;
    } catch (RtMidiError &error) {
        qWarning() << "MIDIデバイス接続エラー:" << QString::fromStdString(error.getMessage());
        return false;
    }
}

void MidiManager::closeInputDevice()
{
    if (m_isInitialized && m_midiIn->isPortOpen()) {
        try {
            m_midiIn->closePort();
            qInfo() << "MIDI入力デバイスを閉じました";
        } catch (RtMidiError &error) {
            qWarning() << "MIDIデバイス切断エラー:" << QString::fromStdString(error.getMessage());
        }
    }
}

bool MidiManager::isInputDeviceOpen() const
{
    return m_isInitialized && m_midiIn->isPortOpen();
}

void MidiManager::midiCallback(double /*timeStamp*/, std::vector<unsigned char>* message, void* userData)
{
    // static関数からインスタンスメソッドを呼び出す
    if (userData && message) {
        MidiManager* midiManager = static_cast<MidiManager*>(userData);
        midiManager->processMidiMessage(*message);
    }
}

void MidiManager::processMidiMessage(const std::vector<unsigned char>& message)
{
    if (message.empty()) {
        return;
    }
    
    // メッセージの種類に基づいて処理
    unsigned char status = message[0];
    
    // SysExメッセージ (F0で始まるメッセージ)
    if (status == 0xF0) {
        emit sysExReceived(message);
        return;
    }
    
    // チャンネルメッセージの種類を取得 (ステータスバイトの上位4ビット)
    unsigned char messageType = status & 0xF0;
    
    // Note Onメッセージ (ステータス 0x9n)
    if (messageType == 0x90 && message.size() >= 3) {
        unsigned char note = message[1];
        unsigned char velocity = message[2];
        
        // ベロシティ0のNote Onはチャンネル・モードでのNote Offとして扱う
        if (velocity > 0) {
            emit noteOnReceived(note, velocity);
        } else {
            emit noteOffReceived(note);
        }
    }
    // Note Offメッセージ (ステータス 0x8n)
    else if (messageType == 0x80 && message.size() >= 3) {
        unsigned char note = message[1];
        emit noteOffReceived(note);
    }
}
#include "LaunchpadVisualizer.h"
#include <QDebug>
#include <QColor>

LaunchpadVisualizer::LaunchpadVisualizer(QObject *parent)
    : QObject(parent)
    , m_midiManager(std::make_unique<MidiManager>())
    , m_isRunning(false)
{
    // MIDIマネージャーからのシグナルを接続
    connect(m_midiManager.get(), &MidiManager::noteOnReceived, 
            this, &LaunchpadVisualizer::onNoteOn);
    connect(m_midiManager.get(), &MidiManager::noteOffReceived, 
            this, &LaunchpadVisualizer::onNoteOff);
    connect(m_midiManager.get(), &MidiManager::sysExReceived, 
            this, &LaunchpadVisualizer::onSysEx);
}

LaunchpadVisualizer::~LaunchpadVisualizer()
{
    stopVisualization();
}

QStringList LaunchpadVisualizer::getAvailableMidiDevices() const
{
    return m_midiManager->getAvailableInputDevices();
}

bool LaunchpadVisualizer::connectToDevice(int deviceIndex)
{
    if (m_isRunning) {
        stopVisualization();
    }
    
    return m_midiManager->openInputDevice(deviceIndex);
}

void LaunchpadVisualizer::disconnectDevice()
{
    stopVisualization();
    m_midiManager->closeInputDevice();
}

bool LaunchpadVisualizer::startVisualization()
{
    if (m_isRunning) {
        return true; // 既に実行中
    }
    
    if (!m_midiManager->isInputDeviceOpen()) {
        qWarning() << "MIDIデバイスが接続されていません。";
        return false;
    }
    
    m_isRunning = true;
    qInfo() << "可視化を開始しました。";
    return true;
}

void LaunchpadVisualizer::stopVisualization()
{
    m_isRunning = false;
    qInfo() << "可視化を停止しました。";
}

bool LaunchpadVisualizer::isRunning() const
{
    return m_isRunning;
}

void LaunchpadVisualizer::onNoteOn(unsigned char note, unsigned char velocity)
{
    if (!m_isRunning) {
        return;
    }
    
    int x, y;
    if (noteToCoordinates(note, x, y)) {
        emit padPressed(x, y, velocity);
        
        // ベロシティ値から色を決定（仮実装）
        // 後でLaunchpadProtocolによる適切な色変換に置き換える
        QColor color = QColor::fromHsv(velocity * 2, 255, 255);
        emit padColorChanged(x, y, color);
    }
}

void LaunchpadVisualizer::onNoteOff(unsigned char note)
{
    if (!m_isRunning) {
        return;
    }
    
    int x, y;
    if (noteToCoordinates(note, x, y)) {
        emit padReleased(x, y);
    }
}

void LaunchpadVisualizer::onSysEx(const std::vector<unsigned char>& data)
{
    if (!m_isRunning) {
        return;
    }
    
    // SysExメッセージの処理（将来的にLaunchpadProtocolクラスで実装）
    qDebug() << "SysEx message received, length: " << data.size();
    
    // TODO: SysExメッセージから色情報を抽出し、padColorChangedシグナルを発行する
}

bool LaunchpadVisualizer::noteToCoordinates(unsigned char note, int& x, int& y) const
{
    // Launchpad Xのノート番号からグリッド座標へのマッピング
    // 詳細なマッピングはLaunchpad Xのプログラマーリファレンスに基づいて実装する必要がある
    // 以下は仮実装
    
    // 11 12 13 14 15 16 17 18
    // 21 22 23 24 25 26 27 28
    // ...
    // 81 82 83 84 85 86 87 88
    
    if (note < 11 || note > 88) {
        return false; // 有効な範囲外
    }
    
    int row = (note / 10) - 1;
    int col = (note % 10) - 1;
    
    if (row < 0 || row > 7 || col < 0 || col > 7) {
        return false; // 8x8グリッド外
    }
    
    x = col;
    y = row;
    return true;
}
#ifndef MIDI_MANAGER_H
#define MIDI_MANAGER_H

#include <QObject>
#include <QStringList>
#include <memory>
#include <vector>
#include <RtMidi.h>

/**
 * @brief MIDIデバイスとの通信を管理するクラス
 */
class MidiManager : public QObject {
    Q_OBJECT

public:
    explicit MidiManager(QObject *parent = nullptr);
    ~MidiManager();

    /**
     * @brief 利用可能なMIDI入力デバイスのリストを取得
     * @return デバイス名のリスト
     */
    QStringList getAvailableInputDevices() const;

    /**
     * @brief MIDI入力デバイスを開く
     * @param deviceIndex デバイスインデックス
     * @return 接続成功の場合true
     */
    bool openInputDevice(int deviceIndex);

    /**
     * @brief MIDI入力デバイスを閉じる
     */
    void closeInputDevice();

    /**
     * @brief MIDI入力デバイスが開いているかチェック
     * @return 開いている場合true
     */
    bool isInputDeviceOpen() const;

signals:
    /**
     * @brief MIDI Note Onメッセージを受信したときのシグナル
     * @param note ノート番号
     * @param velocity ベロシティ値
     */
    void noteOnReceived(unsigned char note, unsigned char velocity);

    /**
     * @brief MIDI Note Offメッセージを受信したときのシグナル
     * @param note ノート番号
     */
    void noteOffReceived(unsigned char note);

    /**
     * @brief MIDI SysExメッセージを受信したときのシグナル
     * @param data SysExデータ
     */
    void sysExReceived(const std::vector<unsigned char>& data);

private:
    /**
     * @brief RtMidiからのコールバック関数（静的）
     */
    static void midiCallback(double timeStamp, std::vector<unsigned char>* message, void* userData);

    /**
     * @brief MIDI入力データ処理メソッド
     */
    void processMidiMessage(const std::vector<unsigned char>& message);

private:
    std::unique_ptr<RtMidiIn> m_midiIn;  // MIDI入力デバイス
    bool m_isInitialized;  // 初期化フラグ
};

#endif // MIDI_MANAGER_H
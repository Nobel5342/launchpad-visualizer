#ifndef LAUNCHPAD_VISUALIZER_H
#define LAUNCHPAD_VISUALIZER_H

#include <QObject>
#include <QColor>  // QColorクラスをインクルード
#include <memory>
#include "midi/MidiManager.h"

/**
 * @brief Launchpad X の操作と色情報を可視化するメインアプリケーションクラス
 */
class LaunchpadVisualizer : public QObject {
    Q_OBJECT

public:
    explicit LaunchpadVisualizer(QObject *parent = nullptr);
    ~LaunchpadVisualizer();

    /**
     * @brief 利用可能なMIDIデバイスのリストを取得
     * @return デバイス名のリスト
     */
    QStringList getAvailableMidiDevices() const;

    /**
     * @brief MIDIデバイスを選択して接続
     * @param deviceIndex デバイスインデックス
     * @return 接続が成功したかどうか
     */
    bool connectToDevice(int deviceIndex);

    /**
     * @brief 現在接続中のデバイスを切断
     */
    void disconnectDevice();

    /**
     * @brief 可視化の開始
     * @return 開始が成功したかどうか
     */
    bool startVisualization();

    /**
     * @brief 可視化の停止
     */
    void stopVisualization();

    /**
     * @brief 可視化が実行中かどうかを取得
     * @return 実行中の場合true
     */
    bool isRunning() const;

public slots:
    /**
     * @brief MIDIノートオンイベントを受信したときに呼ばれる
     * @param note ノート番号
     * @param velocity ベロシティ値
     */
    void onNoteOn(unsigned char note, unsigned char velocity);
    
    /**
     * @brief MIDIノートオフイベントを受信したときに呼ばれる
     * @param note ノート番号
     */
    void onNoteOff(unsigned char note);
    
    /**
     * @brief SysExメッセージを受信したときに呼ばれる
     * @param data SysExデータバイト
     */
    void onSysEx(const std::vector<unsigned char>& data);

signals:
    /**
     * @brief パッドが押されたときに発生するシグナル
     * @param x X座標 (0-7)
     * @param y Y座標 (0-7)
     * @param velocity ベロシティ値
     */
    void padPressed(int x, int y, int velocity);
    
    /**
     * @brief パッドが離されたときに発生するシグナル
     * @param x X座標 (0-7)
     * @param y Y座標 (0-7)
     */
    void padReleased(int x, int y);
    
    /**
     * @brief パッドの色が変更されたときに発生するシグナル
     * @param x X座標 (0-7)
     * @param y Y座標 (0-7)
     * @param color 色 (RGB値)
     */
    void padColorChanged(int x, int y, QColor color);

private:
    /**
     * @brief ノート番号からX,Y座標に変換
     * @param note ノート番号
     * @param x 出力X座標
     * @param y 出力Y座標
     * @return 変換が成功したかどうか
     */
    bool noteToCoordinates(unsigned char note, int& x, int& y) const;

    std::unique_ptr<MidiManager> m_midiManager;  // MIDIマネージャー
    bool m_isRunning;  // 可視化実行中フラグ
};

#endif // LAUNCHPAD_VISUALIZER_H
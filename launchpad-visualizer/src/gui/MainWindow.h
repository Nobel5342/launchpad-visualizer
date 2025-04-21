#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "../LaunchpadVisualizer.h"
#include "LaunchpadGrid.h"

/**
 * @brief アプリケーションのメインウィンドウクラス
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(LaunchpadVisualizer* visualizer, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief デバイス選択コンボボックスの内容を更新
     */
    void updateDeviceList();

    /**
     * @brief MIDIデバイスに接続
     */
    void connectToDevice();

    /**
     * @brief MIDIデバイスとの接続を切断
     */
    void disconnectDevice();

    /**
     * @brief 可視化の開始/停止を切り替え
     */
    void toggleVisualization();

    /**
     * @brief パッド押下イベントのハンドラー
     */
    void onPadPressed(int x, int y, int velocity);

    /**
     * @brief パッド離上イベントのハンドラー
     */
    void onPadReleased(int x, int y);

    /**
     * @brief パッド色変更イベントのハンドラー
     */
    void onPadColorChanged(int x, int y, QColor color);

private:
    /**
     * @brief UIコンポーネントの初期化
     */
    void initializeUI();

    /**
     * @brief UI状態の更新
     */
    void updateUIState();

private:
    LaunchpadVisualizer* m_visualizer;  // 可視化エンジン

    // UIコンポーネント
    QComboBox* m_deviceComboBox;     // デバイス選択コンボボックス
    QPushButton* m_connectButton;    // 接続ボタン
    QPushButton* m_disconnectButton; // 切断ボタン
    QPushButton* m_startStopButton;  // 開始/停止ボタン
    QLabel* m_statusLabel;           // ステータス表示
    LaunchpadGrid* m_launchpadGrid;  // Launchpad可視化グリッド
};

#endif // MAIN_WINDOW_H
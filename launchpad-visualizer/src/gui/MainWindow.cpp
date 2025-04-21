#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(LaunchpadVisualizer* visualizer, QWidget *parent)
    : QMainWindow(parent)
    , m_visualizer(visualizer)
{
    // ウィンドウタイトルの設定
    setWindowTitle("Launchpad X Visualizer");
    
    // UIの初期化
    initializeUI();
    
    // シグナル/スロット接続
    connect(m_visualizer, &LaunchpadVisualizer::padPressed, 
            this, &MainWindow::onPadPressed);
    connect(m_visualizer, &LaunchpadVisualizer::padReleased, 
            this, &MainWindow::onPadReleased);
    connect(m_visualizer, &LaunchpadVisualizer::padColorChanged, 
            this, &MainWindow::onPadColorChanged);
    
    // デバイスリストの更新
    updateDeviceList();
    
    // UI状態の更新
    updateUIState();
    
    // ウィンドウサイズの初期設定
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    // 切断処理
    m_visualizer->disconnectDevice();
}

void MainWindow::initializeUI()
{
    // 中央ウィジェット
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // メインレイアウト
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    // コントロールグループ
    QGroupBox* controlGroup = new QGroupBox("デバイス制御", this);
    QHBoxLayout* controlLayout = new QHBoxLayout(controlGroup);
    
    // デバイス選択コンボボックス
    m_deviceComboBox = new QComboBox(this);
    controlLayout->addWidget(new QLabel("MIDIデバイス:", this));
    controlLayout->addWidget(m_deviceComboBox, 1);
    
    // 更新ボタン
    QPushButton* refreshButton = new QPushButton("更新", this);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::updateDeviceList);
    controlLayout->addWidget(refreshButton);
    
    // 接続/切断ボタン
    m_connectButton = new QPushButton("接続", this);
    connect(m_connectButton, &QPushButton::clicked, this, &MainWindow::connectToDevice);
    controlLayout->addWidget(m_connectButton);
    
    m_disconnectButton = new QPushButton("切断", this);
    connect(m_disconnectButton, &QPushButton::clicked, this, &MainWindow::disconnectDevice);
    controlLayout->addWidget(m_disconnectButton);
    
    // 開始/停止ボタン
    m_startStopButton = new QPushButton("開始", this);
    connect(m_startStopButton, &QPushButton::clicked, this, &MainWindow::toggleVisualization);
    controlLayout->addWidget(m_startStopButton);
    
    mainLayout->addWidget(controlGroup);
    
    // ステータスラベル
    m_statusLabel = new QLabel("準備完了", this);
    m_statusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_statusLabel);
    
    // Launchpadグリッド
    m_launchpadGrid = new LaunchpadGrid(this);
    mainLayout->addWidget(m_launchpadGrid, 1);
    
    // レイアウトのスペースを調整
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);
}

void MainWindow::updateDeviceList()
{
    m_deviceComboBox->clear();
    
    QStringList devices = m_visualizer->getAvailableMidiDevices();
    m_deviceComboBox->addItems(devices);
    
    if (devices.isEmpty()) {
        m_statusLabel->setText("MIDIデバイスが見つかりません");
    } else {
        m_statusLabel->setText("MIDIデバイスを選択して「接続」をクリックしてください");
    }
    
    updateUIState();
}

void MainWindow::connectToDevice()
{
    int deviceIndex = m_deviceComboBox->currentIndex();
    if (deviceIndex < 0) {
        QMessageBox::warning(this, "接続エラー", "MIDIデバイスが選択されていません。");
        return;
    }
    
    if (m_visualizer->connectToDevice(deviceIndex)) {
        m_statusLabel->setText("デバイスに接続しました: " + m_deviceComboBox->currentText());
        updateUIState();
    } else {
        QMessageBox::warning(this, "接続エラー", "MIDIデバイスへの接続に失敗しました。");
    }
}

void MainWindow::disconnectDevice()
{
    m_visualizer->disconnectDevice();
    m_statusLabel->setText("デバイスから切断しました");
    updateUIState();
}

void MainWindow::toggleVisualization()
{
    if (m_visualizer->isRunning()) {
        m_visualizer->stopVisualization();
        m_statusLabel->setText("可視化を停止しました");
    } else {
        if (m_visualizer->startVisualization()) {
            m_statusLabel->setText("可視化を開始しました");
        } else {
            QMessageBox::warning(this, "エラー", "可視化の開始に失敗しました。デバイスが接続されているか確認してください。");
            return;
        }
    }
    
    updateUIState();
}

void MainWindow::onPadPressed(int x, int y, int velocity)
{
    // パッドが押されたときの処理
    m_launchpadGrid->setPadActive(x, y, true);
    
    // ステータス更新（デバッグ用）
    m_statusLabel->setText(QString("パッド押下: (%1, %2) ベロシティ: %3").arg(x).arg(y).arg(velocity));
}

void MainWindow::onPadReleased(int x, int y)
{
    // パッドが離されたときの処理
    m_launchpadGrid->setPadActive(x, y, false);
    
    // ステータス更新（デバッグ用）
    m_statusLabel->setText(QString("パッド離上: (%1, %2)").arg(x).arg(y));
}

void MainWindow::onPadColorChanged(int x, int y, QColor color)
{
    // パッドの色が変更されたときの処理
    m_launchpadGrid->setPadColor(x, y, color);
}

void MainWindow::updateUIState()
{
    bool isConnected = m_visualizer && m_visualizer->isRunning();
    bool isDeviceConnected = m_visualizer && m_visualizer->isRunning();
    
    // デバイスリスト
    m_deviceComboBox->setEnabled(!isDeviceConnected);
    
    // 接続/切断ボタン
    m_connectButton->setEnabled(!isDeviceConnected && m_deviceComboBox->count() > 0);
    m_disconnectButton->setEnabled(isDeviceConnected);
    
    // 開始/停止ボタン
    m_startStopButton->setEnabled(isDeviceConnected);
    m_startStopButton->setText(isConnected ? "停止" : "開始");
}
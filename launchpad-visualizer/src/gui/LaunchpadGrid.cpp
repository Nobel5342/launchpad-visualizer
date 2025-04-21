#include "LaunchpadGrid.h"
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QDebug>

LaunchpadGrid::LaunchpadGrid(QWidget *parent)
    : QWidget(parent)
    , m_padSize(0)
{
    // 背景色を黒に設定
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    
    // パレットを設定
    QPalette palette = this->palette();
    palette.setColor(QPalette::Base, Qt::black);
    setPalette(palette);
    
    // 最小サイズを設定
    setMinimumSize(200, 200);
    
    // 色とアクティブ状態の初期化
    m_padColors = QVector<QVector<QColor>>(GRID_SIZE, QVector<QColor>(GRID_SIZE, Qt::black));
    m_padActiveState = QVector<QVector<bool>>(GRID_SIZE, QVector<bool>(GRID_SIZE, false));
}

LaunchpadGrid::~LaunchpadGrid()
{
    // 特に何もしない
}

void LaunchpadGrid::setPadColor(int x, int y, const QColor& color)
{
    if (!isValidCoordinate(x, y)) {
        return;
    }
    
    m_padColors[y][x] = color;
    update(calculatePadRect(x, y)); // 該当パッドのみ再描画
}

void LaunchpadGrid::setPadActive(int x, int y, bool active)
{
    if (!isValidCoordinate(x, y)) {
        return;
    }
    
    m_padActiveState[y][x] = active;
    update(calculatePadRect(x, y)); // 該当パッドのみ再描画
}

void LaunchpadGrid::resetGrid()
{
    // すべてのパッドの色とアクティブ状態をリセット
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            m_padColors[y][x] = Qt::black;
            m_padActiveState[y][x] = false;
        }
    }
    
    // 全体を再描画
    update();
}

void LaunchpadGrid::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 再描画する矩形を取得
    QRect updateRect = event->rect();
    
    // 描画範囲内のパッドのみ描画
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            QRect padRect = calculatePadRect(x, y);
            
            // 更新矩形と交差する場合のみ描画
            if (padRect.intersects(updateRect)) {
                // パッドの色を取得
                QColor padColor = m_padColors[y][x];
                
                // パッドの描画
                if (m_padActiveState[y][x]) {
                    // アクティブ状態: 中心に小さめの四角を描画
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(padColor);
                    painter.drawRoundedRect(padRect, 5, 5);
                    
                    // さらに押された状態を表現するために、中央に明るい色で小さな四角を描画
                    QColor brighterColor = padColor.lighter(150);
                    QRect innerRect = padRect;
                    innerRect.adjust(
                        padRect.width() * (1.0f - ACTIVE_SCALE) / 2,
                        padRect.height() * (1.0f - ACTIVE_SCALE) / 2,
                        -padRect.width() * (1.0f - ACTIVE_SCALE) / 2,
                        -padRect.height() * (1.0f - ACTIVE_SCALE) / 2
                    );
                    painter.setBrush(brighterColor);
                    painter.drawRoundedRect(innerRect, 5, 5);
                } else {
                    // 非アクティブ状態: 通常の四角を描画
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(padColor);
                    painter.drawRoundedRect(padRect, 5, 5);
                }
                
                // パッド境界線
                painter.setPen(Qt::gray);
                painter.setBrush(Qt::NoBrush);
                painter.drawRoundedRect(padRect, 5, 5);
            }
        }
    }
}

void LaunchpadGrid::resizeEvent(QResizeEvent *event)
{
    // ウィジェットのサイズが変更されたときにパッドサイズを再計算
    QSize newSize = event->size();
    int width = newSize.width();
    int height = newSize.height();
    
    // グリッド全体を正方形に収める
    int minDim = qMin(width, height);
    
    // パッドのサイズを計算 (ギャップを考慮)
    m_padSize = (minDim - PAD_GAP * (GRID_SIZE + 1)) / GRID_SIZE;
    
    QWidget::resizeEvent(event);
}

QRect LaunchpadGrid::calculatePadRect(int x, int y) const
{
    if (!isValidCoordinate(x, y)) {
        return QRect();
    }
    
    int padX = PAD_GAP + x * (m_padSize + PAD_GAP);
    int padY = PAD_GAP + y * (m_padSize + PAD_GAP);
    
    return QRect(padX, padY, m_padSize, m_padSize);
}

bool LaunchpadGrid::isValidCoordinate(int x, int y) const
{
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}
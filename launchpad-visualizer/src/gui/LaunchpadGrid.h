#ifndef LAUNCHPAD_GRID_H
#define LAUNCHPAD_GRID_H

#include <QWidget>
#include <QColor>
#include <QVector>

/**
 * @brief Launchpad X のパッドグリッドを表示するウィジェット
 */
class LaunchpadGrid : public QWidget {
    Q_OBJECT

public:
    explicit LaunchpadGrid(QWidget *parent = nullptr);
    ~LaunchpadGrid();

    /**
     * @brief パッドの色を設定
     * @param x X座標 (0-7)
     * @param y Y座標 (0-7)
     * @param color 色
     */
    void setPadColor(int x, int y, const QColor& color);

    /**
     * @brief パッドのアクティブ状態を設定
     * @param x X座標 (0-7)
     * @param y Y座標 (0-7)
     * @param active アクティブならtrue
     */
    void setPadActive(int x, int y, bool active);

    /**
     * @brief グリッド全体をリセット
     */
    void resetGrid();

protected:
    /**
     * @brief ペイントイベント
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief リサイズイベント
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    /**
     * @brief 特定のパッドの矩形を計算
     * @param x X座標 (0-7)
     * @param y Y座標 (0-7)
     * @return パッドの矩形
     */
    QRect calculatePadRect(int x, int y) const;

    /**
     * @brief 座標が有効かチェック
     * @param x X座標
     * @param y Y座標
     * @return 有効ならtrue
     */
    bool isValidCoordinate(int x, int y) const;

private:
    static constexpr int GRID_SIZE = 8;      // グリッドサイズ (8x8)
    static constexpr int PAD_GAP = 5;        // パッド間のギャップ (ピクセル)
    static constexpr float ACTIVE_SCALE = 0.9f; // アクティブ時のサイズ比率

    QVector<QVector<QColor>> m_padColors;    // パッドの色
    QVector<QVector<bool>> m_padActiveState; // パッドのアクティブ状態
    int m_padSize;                          // パッドのサイズ (ピクセル)
};

#endif // LAUNCHPAD_GRID_H
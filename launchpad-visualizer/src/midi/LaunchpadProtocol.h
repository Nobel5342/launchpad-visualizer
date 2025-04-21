#ifndef LAUNCHPAD_PROTOCOL_H
#define LAUNCHPAD_PROTOCOL_H

#include <QColor>
#include <vector>
#include <map>

/**
 * @brief Launchpad X の通信プロトコルを扱うクラス
 * Novation Launchpad X のMIDI通信プロトコルに関する処理を担当
 */
class LaunchpadProtocol {
public:
    LaunchpadProtocol();
    ~LaunchpadProtocol();

    /**
     * @brief パッドのベロシティ値からRGB色を取得
     * @param velocity ベロシティ値 (0-127)
     * @return 対応するRGB色
     */
    QColor velocityToColor(unsigned char velocity) const;

    /**
     * @brief RGB色からベロシティ値に近似変換
     * @param color RGB色
     * @return 最も近いLaunchpadの色に対応するベロシティ値
     */
    unsigned char colorToVelocity(const QColor& color) const;

    /**
     * @brief SysExメッセージから色情報を解析
     * @param sysExData SysExメッセージデータ
     * @param x 出力X座標
     * @param y 出力Y座標
     * @param color 出力色
     * @return 解析成功の場合true
     */
    bool parseSysExColorMessage(const std::vector<unsigned char>& sysExData, 
                                int& x, int& y, QColor& color) const;

    /**
     * @brief RGB値で指定されたパッドの色を設定するためのSysExメッセージを生成
     * @param x X座標 (0-7)
     * @param y Y座標 (0-7)
     * @param r 赤成分 (0-127)
     * @param g 緑成分 (0-127)
     * @param b 青成分 (0-127)
     * @return SysExメッセージ
     */
    std::vector<unsigned char> createRgbColorMessage(int x, int y, 
                                                    unsigned char r,
                                                    unsigned char g, 
                                                    unsigned char b) const;

    /**
     * @brief ノート番号からXY座標への変換
     * @param note ノート番号
     * @param x 出力X座標
     * @param y 出力Y座標
     * @return 変換成功の場合true
     */
    bool noteToXY(unsigned char note, int& x, int& y) const;

    /**
     * @brief XY座標からノート番号への変換
     * @param x X座標 (0-7)
     * @param y Y座標 (0-7)
     * @return ノート番号、変換失敗時は255
     */
    unsigned char xyToNote(int x, int y) const;

private:
    // Launchpad X の定数
    static constexpr int GRID_SIZE = 8;      // グリッドサイズ (8x8)
    static constexpr int MAX_BRIGHTNESS = 63; // 最大輝度
    
    // 色マッピング用の内部テーブル
    std::map<unsigned char, QColor> m_velocityColorMap; // ベロシティ→色マップ
};

#endif // LAUNCHPAD_PROTOCOL_H
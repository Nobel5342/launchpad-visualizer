#include "LaunchpadProtocol.h"
#include <QDebug>

LaunchpadProtocol::LaunchpadProtocol()
{
    // ベロシティ値と色のマッピングを初期化
    // 注: これは仮のマッピングです。実際のLaunchpad Xの色マップは公式プログラマーリファレンスに基づいて実装する必要があります
    
    // 0: オフ
    m_velocityColorMap[0] = QColor(0, 0, 0);
    
    // 1-15: 低輝度の赤シェード
    for (int i = 1; i <= 15; i++) {
        int intensity = (i * 16) - 1;
        m_velocityColorMap[i] = QColor(intensity, 0, 0);
    }
    
    // 16-31: 低輝度の黄シェード
    for (int i = 16; i <= 31; i++) {
        int intensity = ((i - 16) * 16) - 1;
        m_velocityColorMap[i] = QColor(intensity, intensity, 0);
    }
    
    // 32-47: 低輝度の緑シェード
    for (int i = 32; i <= 47; i++) {
        int intensity = ((i - 32) * 16) - 1;
        m_velocityColorMap[i] = QColor(0, intensity, 0);
    }
    
    // 48-63: 低輝度の水色シェード
    for (int i = 48; i <= 63; i++) {
        int intensity = ((i - 48) * 16) - 1;
        m_velocityColorMap[i] = QColor(0, intensity, intensity);
    }
    
    // 64-79: 低輝度の青シェード
    for (int i = 64; i <= 79; i++) {
        int intensity = ((i - 64) * 16) - 1;
        m_velocityColorMap[i] = QColor(0, 0, intensity);
    }
    
    // 80-95: 低輝度の紫シェード
    for (int i = 80; i <= 95; i++) {
        int intensity = ((i - 80) * 16) - 1;
        m_velocityColorMap[i] = QColor(intensity, 0, intensity);
    }
    
    // 96-111: 高輝度の赤シェード
    for (int i = 96; i <= 111; i++) {
        int intensity = ((i - 96) * 16) + 127;
        m_velocityColorMap[i] = QColor(intensity, 0, 0);
    }
    
    // 112-127: 高輝度の白シェード
    for (int i = 112; i <= 127; i++) {
        int intensity = ((i - 112) * 16) + 127;
        m_velocityColorMap[i] = QColor(intensity, intensity, intensity);
    }
}

LaunchpadProtocol::~LaunchpadProtocol()
{
    // 特に何もしない
}

QColor LaunchpadProtocol::velocityToColor(unsigned char velocity) const
{
    // ベロシティから色へのマッピングを検索
    auto it = m_velocityColorMap.find(velocity);
    if (it != m_velocityColorMap.end()) {
        return it->second;
    }
    
    // マップにない場合は既定の色を返す
    return QColor(0, 0, 0);
}

unsigned char LaunchpadProtocol::colorToVelocity(const QColor& color) const
{
    // 色から最も近いベロシティ値を検索
    unsigned char bestMatch = 0;
    int minDistance = 255 * 255 * 3; // 最大可能距離（R、G、B各成分の距離の二乗の和）
    
    for (const auto& entry : m_velocityColorMap) {
        QColor mapColor = entry.second;
        
        // RGB空間での距離を計算
        int dr = mapColor.red() - color.red();
        int dg = mapColor.green() - color.green();
        int db = mapColor.blue() - color.blue();
        int distance = dr*dr + dg*dg + db*db;
        
        if (distance < minDistance) {
            minDistance = distance;
            bestMatch = entry.first;
        }
    }
    
    return bestMatch;
}

bool LaunchpadProtocol::parseSysExColorMessage(const std::vector<unsigned char>& sysExData, 
                                              int& x, int& y, QColor& color) const
{
    // Launchpad X SysExカラーメッセージのフォーマット解析
    // 注: この実装は仮のもので、実際のLaunchpad XのSysEx仕様に基づいて実装する必要があります
    
    // 基本的なバリデーション
    if (sysExData.size() < 10) {
        return false;  // メッセージが短すぎる
    }
    
    // SysExヘッダーチェック
    if (sysExData[0] != 0xF0 || sysExData[sysExData.size() - 1] != 0xF7) {
        return false;  // 有効なSysExではない
    }
    
    // Novation ID (後で実際のIDに置き換える)
    if (sysExData[1] != 0x00 || sysExData[2] != 0x20 || sysExData[3] != 0x29) {
        return false;  // Novation IDではない
    }
    
    // このセクションは実際のLaunchpad Xのプログラマーリファレンスに基づいて実装する必要があります
    // 仮の実装として、単純なフォーマットを想定
    
    // 仮の座標と色情報の抽出
    x = sysExData[5] & 0x0F;
    y = (sysExData[5] & 0xF0) >> 4;
    
    // RGB値の抽出
    unsigned char r = sysExData[6] & 0x7F;  // 0-127に制限
    unsigned char g = sysExData[7] & 0x7F;
    unsigned char b = sysExData[8] & 0x7F;
    
    // RGB値を0-255に正規化
    r = (r * 255) / 127;
    g = (g * 255) / 127;
    b = (b * 255) / 127;
    
    color = QColor(r, g, b);
    
    return true;
}

std::vector<unsigned char> LaunchpadProtocol::createRgbColorMessage(int x, int y, 
                                                                  unsigned char r,
                                                                  unsigned char g, 
                                                                  unsigned char b) const
{
    // Launchpad X のRGB色設定SysExメッセージを生成
    // 注: 実際のLaunchpad XのSysEx仕様に基づいて実装する必要があります
    
    std::vector<unsigned char> message;
    
    // F0 00 20 29 02 0A [LED index] [R] [G] [B] F7
    // 上記は仮のフォーマットで、実際のLaunchpad XのSysEx仕様に置き換える必要があります
    
    message.push_back(0xF0);   // SysExスタート
    message.push_back(0x00);   // Novation ID (仮)
    message.push_back(0x20);
    message.push_back(0x29);
    message.push_back(0x02);   // Launchpad X ID (仮)
    message.push_back(0x0A);   // RGB色設定コマンド (仮)
    
    // LED位置 (x, yから計算)
    unsigned char ledIndex = (y << 4) | x;
    message.push_back(ledIndex);
    
    // RGB値 (0-127に制限)
    message.push_back(r & 0x7F);
    message.push_back(g & 0x7F);
    message.push_back(b & 0x7F);
    
    message.push_back(0xF7);   // SysEx終了
    
    return message;
}

bool LaunchpadProtocol::noteToXY(unsigned char note, int& x, int& y) const
{
    // Launchpad X のノート番号からXY座標への変換
    // 注: 実際のLaunchpad Xのマッピングに基づいて実装する必要があります
    
    // 仮のマッピング (10の位が行、1の位が列)
    if (note < 11 || note > 88) {
        return false;  // 無効なノート番号
    }
    
    y = (note / 10) - 1;  // 行番号 (0-7)
    x = (note % 10) - 1;  // 列番号 (0-7)
    
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
        return false;  // グリッド範囲外
    }
    
    return true;
}

unsigned char LaunchpadProtocol::xyToNote(int x, int y) const
{
    // XY座標からLaunchpad X のノート番号への変換
    // 注: 実際のLaunchpad Xのマッピングに基づいて実装する必要があります
    
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
        return 255;  // 無効な値
    }
    
    // 仮のマッピング (10の位が行、1の位が列)
    return static_cast<unsigned char>((y + 1) * 10 + (x + 1));
}
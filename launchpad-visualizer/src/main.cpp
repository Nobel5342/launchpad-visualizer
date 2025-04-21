#include <QApplication>
#include "gui/MainWindow.h"
#include "LaunchpadVisualizer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // アプリケーション情報の設定
    QCoreApplication::setApplicationName("Launchpad Visualizer");
    QCoreApplication::setOrganizationName("LaunchpadTools");
    QCoreApplication::setApplicationVersion("0.1.0");
    
    // メインアプリケーションクラスの初期化
    LaunchpadVisualizer visualizer;
    
    // メインウィンドウの作成と表示
    MainWindow mainWindow(&visualizer);
    mainWindow.show();
    
    // イベントループ開始
    return app.exec();
}
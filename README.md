# Launchpad X Visualizer

Novation Launchpad X のパッド操作と色情報をリアルタイムで可視化するアプリケーションです。

## 概要

このアプリケーションは、Novation Launchpad X を使用したパフォーマンス中に、ユーザーが行ったパッド操作（押下、離上）およびパッドの点灯色を、PC画面上にリアルタイムで視覚的に表示することができます。

## 主な機能

- Launchpad X デバイスの接続・認識
- パッド押下/離上イベントのリアルタイム可視化
- パッドの色情報のリアルタイム表示
- 可視化の開始/停止機能

## 対応プラットフォーム

- Windows
- Linux

## 必要なもの

- Novation Launchpad X
- CMake 3.10以上
- Qt 5.15.x
- RtMidi ライブラリ

## ビルド方法

### Linuxの場合

```bash
# 必要なパッケージのインストール
sudo apt install cmake qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools libasound2-dev librtmidi-dev

# ビルド
mkdir build && cd build
cmake ..
make
```

### Windowsの場合

Visual Studio、Qt、CMakeを使用してビルドします。詳細な手順は以下の通りです：

1. 必要なソフトウェアのインストール
   - Visual Studio（C++デスクトップ開発ワークロード）
   - Qt 5.15.x
   - CMake
   - RtMidi

2. ビルドの実行

```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:/Qt/5.15.x/msvc2019_64
cmake --build . --config Release
```

※ パスは環境に合わせて調整してください

## 使い方

1. アプリケーションを起動
2. Launchpad X をUSBで接続
3. デバイスリストからLaunchpad Xを選択
4. 「開始」ボタンをクリック
5. パッド操作が画面上のグリッドに反映される

## ライセンス

[MIT License](LICENSE)

## 作者

Nobel5342
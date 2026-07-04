import processing.serial.*;

Serial myPort;

int distance = 1000; // 距離センサで取得したデータを格納するための変数

void setup() {

  size(1000, 700); // キャンバスサイズを1000x700pxに指定

  printArray(Serial.list()); // シリアルポートのリストをコンソールに表示

  // 使用するシリアルポートを選択
  // [0]の部分を自分のポート番号に変更する
  myPort = new Serial(this, Serial.list()[3], 115200);

  background(255); // キャンバスの背景色を白にする

  noStroke(); // 図形描画の際に枠線をなしにする
}

void draw() {

  // シリアルポートからデータを受信したら変数distanceに格納する
  while (myPort.available() > 0) {
    String s = myPort.readStringUntil('\n');

    if (s != null) {
      s = trim(s);
      distance = int(s);
    }
  }

  // センサとの距離が500mm以内なら円を追加
  if (distance < 500) {
    float x = random(width); // 円のx座標をランダムに
    float y = random(height); // 円のy座標をランダムに
    float d = random(20,150); // 円の大きさを20〜150pxの範囲でランダムに

    fill(0); // 円の色を黒に
    ellipse(x,y,d,d); // 円を描画
  }
  fill(255); // 文字の色を白に
  textSize(100); // 文字サイズを100に
  text("Welcome Home!", 100, 350); // (100, 350)の座標に文字を表示

}

//enshu02
//左バイナリ法を作ってみよう。

void serialEvent() {
  char input;
  long b = 2, e = 100; //2進数表現1000100
  long N = 707;
  int i = 0;
  long n = 1;
  long final_ans;
  long ans = 1, X = 65536;
  while (Serial.available()) {
    input = (char)Serial.read();

    if (input == '1') {
      while (X > 0) {
        ans = ans * ans;   // 2乗算する
        ans = ans % N;    // その都度、modを取ることを忘れずに

        if ((e & X) != 0) {//1が立つ
          ans *= b;         // 基数をかける
          ans = ans % N;  // modを取ることを忘れずに
        }

        X = X >> 1;
        Serial.println(ans);
      }
      Serial.println(ans);

      while (i < 6) {
        final_ans = n*ans;
        final_ans = n % N;
        i++;
      }
      Serial.print("final_ans");
      Serial.println(final_ans);
    }
  }
}

void setup() {
  Serial.begin(9600);
  serialEvent();
}

void loop() {

}

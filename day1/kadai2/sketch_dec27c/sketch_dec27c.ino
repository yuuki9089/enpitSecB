//enshu02
//左バイナリ法を作ってみよう。

void serialEvent() {
  char input;
  long b = 2, e = 100; //2進数表現1000100
  long N = 707;
  int i = 0;
  long n = 1;
  long final_ans;
  long ans1 = 1, ans2 = 0, X = 65536;
  while (Serial.available()) {
    input = (char)Serial.read();
    ans2 = b;

    if (input == '1') {
      while (X > 0) {

        if ((e & X) != 0) {//1が立つ

          ans1 = ans1 * ans2;
          ans1 = ans1 % N;

          ans2 = ans2 * ans2;   // 2乗算する
          ans2 = ans2 % N;    // その都度、modを取ることを忘れずに
        }

        else {

          ans2 = ans2 * ans1;   // 2乗算する
          ans2 = ans2 % N;    // その都度、modを取ることを忘れずに

          ans1 = ans1 * ans1;
          ans1 = ans1 % N;
        }

        X = X >> 1;
        Serial.print("ans1= ");
        Serial.println(ans1);
        Serial.println();
        Serial.print("ans2= ");
        Serial.println(ans2);
        Serial.println();

      }
      Serial.println(ans1);

      while (i < 6) {
        final_ans = n * ans1;
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

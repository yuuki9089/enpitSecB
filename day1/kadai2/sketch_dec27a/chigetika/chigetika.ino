void binaryMethod()
{
  long b = 2, e = 100, N = 707;
  long ans = 1, X = 65536;
  long veri = 1;
  int bi = 0;
  int i = 0;
  while (X > 0) {
    ans = ans * ans; // 2乗算する
    ans = ans % N;  // その都度、modを取ることを忘れずに

    if ((e & X) != 0) {
      ans *= b;         // 基数をかける
      ans = ans % N; // modを取ることを忘れずに
    }
    X = X >> 1;
    Serial.println(ans);
  }
  Serial.println(ans);

  Serial.println("");
  for (i = 0; i < 6; i++)
  {
    veri = (veri * ans) % N;
  }

  Serial.print("Verification: ");
  Serial.println(veri);
}

void setup()
{
  Serial.begin(9600);
  binaryMethod();
}

void loop()
{

}

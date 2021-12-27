//enshu03
//ArduinoでRSAを実装してみよう。

#define prime 250 //prime size
#define M 120 //message size
#define SIZE 10 //loop size

long gcd(long a, long b) {
  long c;
  if (a < b) {
    a = a + b;
    b = a - b;
    a = a - b;
  }

  while (b != 0) {
    c = a % b;
    a = b;
    b = c;
  }

  return a;
}

long Check_Prime(long p) {
  long i;
  if (p == 1) return 0;
  for (i = 1; i < p; i++) {
    if (gcd(i, p) != 1) return 0;
  } //non prime

  return 1; //prime
}

long Inv_Mod(long a, long m) {
  long b, x, u, q, tmp;

  b = m; x = 1; u = 0;
  while ( b > 0 ) {
    q = a / b;
    tmp = u; u = x - q * u; x = tmp;
    tmp = b; b = a - q * b; a = tmp;
  }

  return ( x < 0 ) ? x + m : x;
}

////////////////////////////////
//左バイナリ法でべき乗剰余計算を行う
long Power_Mod(long base, long expo, long mod) {
  char input;
  long  //2進数表現1000100
  int i = 0;
  long n = 1;
  long final_ans;
  long ans = 1, X = 65536;
  long N ;
  long b ;
  long e ;
  while (Serial.available()) {
    input = (char)Serial.read();
    N = mod;
    e = expo;
    b = base;
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

      /*   while (i < 6) {
           final_ans = n*ans;
           final_ans = n % N;
           i++;
         }
         Serial.print("final_ans");
         Serial.println(final_ans);*/
    }
  }
  return ans;
}
/////////////////////////////////

void serialEvent() {
  char input;
  long p, q;
  long N, euler;
  long e, d;
  long msg, e_msg, d_msg;
  long gcd_return;
  int i;
  int hit = 0;

  while (Serial.available()) {
    input = (char)Serial.read();

    if (input == '1') {

      for (i = 0; i < SIZE; i++) {
        do {
          p = random() % prime + 1;
        } while (Check_Prime(p) != 1);
        do {
          q = random() % prime + 1;
        } while (Check_Prime(q) != 1 || q == p);

        Serial.print("-----------"); Serial.print(i + 1); Serial.println(" set-----------");
        Serial.print("prime p : "); Serial.println(p);
        Serial.print("prime q : "); Serial.println(q);

        N = p * q;
        Serial.print("N = p * q : "); Serial.println(N);
        euler = (p - 1) * (q - 1);
        Serial.print("euler = (p - 1) * (q - 1) : "); Serial.println(euler);

        /////////////////////////////////
        //eulerと互いに素なeを求める
        while (1) {
          e = random();
          if (e > euler) break;
          gcd_return = gcd(e, euler);

          if (gcd_return == 1) break;
        }

        /////////////////////////////////

        Serial.print("PublicKey (e, N) : ("); Serial.print(e); Serial.print(", "); Serial.print(N); Serial.println(")");

        /////////////////////////////////
        //e * d ≡ 1 mod euler を満たすdを求める

        d = Inv_Mod(e, euler);

        /////////////////////////////////

        Serial.print("PrivateKey (d, p, q) : ("); Serial.print(d); Serial.print(", "); Serial.print(p); Serial.print(", "); Serial.print(q); Serial.println(")");

        do {
          msg = random() % M + 1;
        } while (msg >= N || gcd(msg, N) != 1);

        /////////////////////////////////
        //左バイナリ法を用いて、msgをe_msgに暗号化し、e_msgをd_msgに復号する
        e_msg = Power_Mod(msg, e, N);
        d_msg = Power_Mod(e_msg, d, N);

        /////////////////////////////////

        Serial.print("Msg : "); Serial.println(msg);
        Serial.print("Encrypted Msg : "); Serial.println(e_msg);
        Serial.print("Decrypted Msg : "); Serial.println(d_msg);

        if (msg == d_msg) {
          Serial.println("OK.");
          hit = hit + 1;
        } else {
          Serial.println("MISS.");
          delay(1000);
        }

        Serial.println("");
      }

      Serial.print("Hit : "); Serial.println(hit);
      Serial.println("");
    }
  }

}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void loop() {
  serialEvent();

}

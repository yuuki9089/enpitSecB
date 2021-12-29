//enshu04
//多倍長システムを使ってみよう。

#include "enshu.h"

void serialEvent() {
  char input;
  unsigned long x[4], y[4]; //x * y 上位ビットx,y[3]-x,y[2]-x,y[1]-x,y[0]下位ビット
  unsigned long z[8]; //= z 上位ビットz[7]-z[6]-z[5]-z[4]-z[3]-z[2]-z[1]-z[0]下位ビット
  unsigned long z_mod[4]; //= z mod 2^64 - 1 上位ビットz_mod[3]-z_mod[2]-z_mod[1]-z_mod[0]下位ビット
  unsigned long T1[8], T1_mod[4];
  unsigned long T2[8], T2_mod[4];
  while (Serial.available()) {
    input = (char)Serial.read();
    long X = 65536;
    long e = 2017;
    if (input == '1') {
      ///////////////////////////////////////////////////////////
      //Multiple64()を用いて、x[] * y[] = z[]の乗算を行う
      //配列の出力にはArray_print()を用いる


      Serial.println("x * y = z");
      Serial.println("------------------------");
      Multiple64(x, y, z);
      Serial.print("z=");
      Array_print(x, 3);
      Array_print(y, 3);



      ///////////////////////////////////////////////////////////
    }

    if (input == '2') {
      ///////////////////////////////////////////////////////////
      //乗算結果z[]に対してModulo64()を用いて、z[] mod 2^64 - 1 = z_mod[]の剰余演算を行う
      Multiple64(x, y, z);





      Serial.println("x * y = z mod 2^64 - 1");
      Serial.println("------------------------");




      ///////////////////////////////////////////////////////////
    }

    if (input == '3') {
      ///////////////////////////////////////////////////////////
      //左バイナリ法とMultiple64()、Modulo64()を用いて、べき乗剰余演算を行う
      x[3] = 0xfbc7;
      x[2] = 0xa9ce;
      x[1] = 0x382c;
      x[0] = 0xe051;
      z_mod[3] = 0x0;
      z_mod[2] = 0x0;
      z_mod[1] = 0x0;
      z_mod[0] = 0x1;//1に初期化

      while (X > 0) {
        Multiple64(z_mod, z_mod, z);
        Modulo64(z, z_mod);
        if (e & X) {
          Multiple64(z_mod, x, z);
          Modulo64(z, z_mod);
        }
        X = X >> 1;
        Array_print(z_mod, 4);
      }
      Array_print(z_mod, 4);
    }

    ///////////////////////////////////////////////////////////
    if (input == '4') {
      T1_mod[3] = 0xfbc7;
      T1_mod[2] = 0xa9ce;
      T1_mod[1] = 0x382c;
      T1_mod[0] = 0xe051;
      T2_mod[3] = 0x0;
      T2_mod[2] = 0x0;
      T2_mod[1] = 0x0;
      T2_mod[0] = 0x1;

      while (X > 0)
      {
        if ((e & X) != 0) {
          Multiple64(T1_mod, T2_mod, T1);
          Modulo64(T1, T1_mod);
          Multiple64(T2_mod, T2_mod, T2);
          Modulo64(T2, T2_mod);
        }
        else {
          Multiple64(T1_mod, T2_mod, T2);
          Modulo64(T2, T2_mod);
          Multiple64(T1_mod, T1_mod, T1);
          Modulo64(T1, T1_mod);
        }
        X = X >> 1;
        Serial.print("T1= ");
        Array_print(T1_mod, 4);
        Serial.print("T2= ");
        Array_print(T2_mod, 4);
      }
      Array_print(T1_mod, 4);
    }
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  serialEvent();

}

#include "enshu.h"
#define PINNUM 5

void serialEvent() {
  char input;
  unsigned long x[4], y[4];
  unsigned long z[8];
  unsigned long z_mod[4];

  int bin[100], i;
  long d;
  unsigned long mul[4];

  while (Serial.available()) {
    input = (char)Serial.read();

    if (input == '1') {

      d = 0b1001100010110100;
      //d = random(0b1000000000000000, 0b1111111111111111);

      ///////////////通常攻撃用//////////////////////
      x[3] = 0xfdfc;
      x[2] = 0x98ee;
      x[1] = 0x34da;
      x[0] = 0xaa01;
      mul[3] = 0x0000;
      mul[2] = 0x0000;
      mul[1] = 0x0000;
      mul[0] = 0x0001;
      ///////////////通常攻撃用//////////////////////

      Serial.println("C ^ d = M mod 2^64 - 1");
      Serial.println("------------------------");
      Serial.print("C : ");
      Array_print(x, 4);
      Serial.print("d : "); Serial.println(d, BIN);

      for (i = 0; d > 0; i++) {
        bin[i] = d % 2;
        d = d / 2;
      }

      ///////////////////波形観測ポイント///////////////////
      digitalWrite(PINNUM, HIGH);
      for (i = i - 1; i >= 0; i--) {
        Multiple64(mul, mul, z);
        Modulo64(z, z_mod);
        mul[3] = z_mod[3];
        mul[2] = z_mod[2];
        mul[1] = z_mod[1];
        mul[0] = z_mod[0];

        if (bin[i] == 1) {
          Multiple64(mul, x, z);
          Modulo64(z, z_mod);
          mul[3] = z_mod[3];
          mul[2] = z_mod[2];
          mul[1] = z_mod[1];
          mul[0] = z_mod[0];
        }
      }
      digitalWrite(PINNUM, LOW);
      /////////////////// 波形観測ポイント///////////////////

      Serial.print("M : ");
      Array_print(mul, 4);
      Serial.println();
    }

    if (input == '2') {

      d = 0b1001100010110100;
      //d = random(0b1000000000000000, 0b1111111111111111);

      ///////////////選択暗号文攻撃用//////////////////////
      x[3] = 0xffff;
      x[2] = 0xffff;
      x[1] = 0xffff;
      x[0] = 0xfffe;
      mul[3] = 0x0000;
      mul[2] = 0x0000;
      mul[1] = 0x0000;
      mul[0] = 0x0001;
      ///////////////選択暗号文攻撃用//////////////////////

      Serial.println("(N - 1) ^ d = M mod 2^64 - 1");
      Serial.println("------------------------");
      Serial.print("N - 1 : ");
      Array_print(x, 4);
      Serial.print("d : "); Serial.println(d, BIN);

      for (i = 0; d > 0; i++) {
        bin[i] = d % 2;
        d = d / 2;
      }

      ///////////////////波形観測ポイント///////////////////
      digitalWrite(PINNUM, HIGH);
      for (i = i - 1; i >= 0; i--) {
        Multiple64(mul, mul, z);
        Modulo64(z, z_mod);
        mul[3] = z_mod[3];
        mul[2] = z_mod[2];
        mul[1] = z_mod[1];
        mul[0] = z_mod[0];

        if (bin[i] == 1) {
          Multiple64(mul, x, z);
          Modulo64(z, z_mod);
          mul[3] = z_mod[3];
          mul[2] = z_mod[2];
          mul[1] = z_mod[1];
          mul[0] = z_mod[0];
        }
      }
      digitalWrite(PINNUM, LOW);
      /////////////////// 波形観測ポイント///////////////////

      Serial.print("M : ");
      Array_print(mul, 4);
      Serial.println();
    }

  }
}

void setup() {
  Serial.begin(9600);

}

void loop() {
  serialEvent();

}

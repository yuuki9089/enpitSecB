//enshu01
//簡単なプログラムを作成してみよう。

void serialEvent() {
  char input;
  //while (Serial.available()) {
    //input = (char)Serial.read();

    if (Serial.available()) {

      ///////////////////////////
Serial.println("enter your favorite number");

Serial.println((char)Serial.read());



      ///////////////////////////

    }
  }
//}

void setup() {
  Serial.begin(9600);

}

void loop() {
  ///////////////////////////




  ///////////////////////////
  serialEvent();

}

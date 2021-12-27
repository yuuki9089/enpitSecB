int r1,r2,r3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  r1 = random(0,10);
  r2 = random(0,10);
  Serial.print("r1 = ");
  Serial.println(r1);
  Serial.print("r2 = ");
  Serial.println(r2);
  r3 = r1 + r2;
  Serial.print("r1 + r2 = ");
  Serial.println(r3);
  r3 = r1 - r2;
  Serial.print("r1 - r2 = ");
  Serial.println(r3);
  r3 = r1 * r2;
  Serial.print("r1 * r2 = ");
  Serial.println(r3);
  r3 = r1 / r2;
  Serial.print("r1 / r2 = ");
  Serial.println(r3);
  r3 = r1 % r2;
  Serial.print("r1 % r2 = ");
  Serial.println(r3);
  Serial.println();
  delay(10000);
}

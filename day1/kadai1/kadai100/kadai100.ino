void setup(){
  Serial.begin(9600);
  Event();
  }

void Event() {
  // put your setup code here, to run once:
int a;
int b = 100;
int i;
int sum=0;
for(i=0;i<b;i++){
  sum = sum + i;
  }
Serial.print("sum= ");
Serial.println(sum);

}

void loop() {
  // put your main code here, to run repeatedly:

}

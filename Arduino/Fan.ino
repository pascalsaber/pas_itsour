#define MOTOR_A D6
#define MOTOR_B D7

void fan_setup() {
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
  digital_setFanOn(0);// המאוורר במצב כבוי בנתיים
}
// פונקציה שמקבלת מתח מהחיישןומעדכנת את עוצמת המתח של המאוורר
void digital_setFanOn(int ldrSensor) {
  Serial.printf("send on motor: $d", ldrSensor);
  //שליטה על עוצמת המתח של המאוורר דרך אנלוגרייט
  analogWrite(MOTOR_A, ldrSensor);//D6  
  digitalWrite(MOTOR_B, LOW);//D7
}
// פונקציית כבוי המאוורר 
void digital_setFanOff() {
  Serial.println("send off motor");
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
}

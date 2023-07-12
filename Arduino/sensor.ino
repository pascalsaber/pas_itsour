//פין הקלט האנלוגי
#define LDR A0

//משתנה שבו שמרתי את זמן ביצוע הפעולה האחרונה
int sensorLastTime;
//משתנה שמחזיק את הזמן ההייה הרצוי עד שהחיישן יוכל לחזור לעבוד
int sensorLastTimeDelay = 2000;
// משתנה ממוצע של המספרים הנקלטים מהאנלוג
double avgLDR;
// משתנה המספרים הנקלטים מהאנלוג
int numbers;
// משתנה ספירת כמות הפעמים שנקלטו מספרים אנלוגים
int counter;
//פונקציה שמתבצעת בתחילת התהליך של החיישן
// להגדיר תפין,לשמור תזמן הנוכחי על מנת לדעת מתי התחיל זמן ההשהיה של החיישן למשך שניה אחת

void sensor_setup() {
  pinMode(LDR, INPUT);
  sensorLastTime = 0;
  avgLDR = 0;
  numbers= 0;
  counter = 1;
}
//פונקציה ראשית של החיישן
//מטרת הבדיקה היא השהיית החיישן למשך שניה אחת אם זה קורה מבצעים תפעולות הבאות
//אם זמן ההשהיה נגמר לאפס לזמן חדש את מדידת זמן ההשהיה,
//משתנה לדיר סנסור מטרתו לשמור את את המספר האנלוגי ששלחתי דרך קליטת האנלוג לדר
//אם המספר האלוגי שנשמר בלדר סנסור גדול מ170 כלומר גדול מ3.3 ולט להפחית למתח של 3.3לא יותר
//שליחת מתח למאורר לשם הפעלתו דרך הפונקציה הפעלת המאוורר שיש בקובץ המאורר
void sensor_loop() 
{
  if(millis() - sensorLastTime > sensorLastTimeDelay)
  {
    sensorLastTime = millis();
    int ldrSensor = analogRead(LDR);
    Serial.printf("LDR: %d", ldrSensor);
    Serial.println();
  
    if(ldrSensor > 170)
      ldrSensor = 170; //3.33v MAX
     //הפעלת מאוורר עם ערך חיישן LDR 
    digital_setFanOn(ldrSensor); 
    
    Serial.printf("ldrSensor: %d", ldrSensor);
    Serial.println();
    //AVG
    numbers+=ldrSensor;
    Serial.printf("numbers: %d", numbers);
    Serial.println();
    avgLDR = numbers /counter;
    Serial.printf("counter: %d", counter);
    Serial.println();
    Serial.printf("avgLDR: %f", avgLDR);
    Serial.println();
    counter++;
    Serial.printf("counter ++: %d", counter);
    Serial.println();

  }
}

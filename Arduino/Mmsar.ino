// (in)משתנה לשליטה על הממסר
#define PinRelay D4
//משתנה שבו שמרתי את זמן ביצוע הפעולה האחרונה
int memsarLastTime;
//משתנה שמחזיק את הזמן ההייה הרצוי עד שהממסר יוכל לחזור לפעילות
int memsarLastTimeDelay = 2000;
//מצב הממסר
bool status_memsar;

//פונקציה שמתבצעת בתחילת התהליך של הממסר
// להגדיר תפין,לשמור תזמן הנוכחי על מנת לדעת מתי התחיל זמן ההשהיה של הממסר ולספור 2 שניות
//קריאה לפונקציה שמאפסת את מצב הממסר למצב כבוי כערך התחלתי
void memsar_setup() {
  pinMode(PinRelay, OUTPUT);
  memsarLastTime = 0;
  stop_memsar();
}
// פונקצית הפעלת ממסר ושינוי מצב הסטטוס לטרו פעיל
void start_memsar(){
  digitalWrite(PinRelay, LOW);// מצב פעיל
  status_memsar = true;
  Serial.println("start memsar");
}
// פונקציה לכיבוי ממסר ושינוי הסטטוס לפאלז לא פעיל
void stop_memsar(){
  digitalWrite(PinRelay,HIGH);//מצב כבוי
  status_memsar = false;
  Serial.println("stop memsar");
}
// פונקציה ראשית של הממסר
//בדיקה עם הזמן הנוכחי פחות הזמן שעבר מרגע מדידת הזמן גדול מ2שניות
//מטרת הבדיקה היא השהיית הממסר כלומר להרדים אותו למשך 2 שניותת
//ואם זמן ההשהיה נגמר לאפס לזמן חדש את מדידת זמן ההשהיה,
//ואם הסטטוב הממסר "לא פעיל"לקרוא לפונקציית הפעלת הממסר
//אחרת אם הסטטוס "פעיל"אז לכבות את הממסר
void memsar_loop()
{
  if(millis() - memsarLastTime > memsarLastTimeDelay)
  {
    memsarLastTime = millis();
    if(status_memsar == false)
     start_memsar();
    else if(status_memsar == true)
      stop_memsar();
  }
}

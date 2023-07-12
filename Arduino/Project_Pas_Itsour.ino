//אי-אפשר לגשת למשתנים במסמכים אחרים ללא הקצעה מיוחד לכן השתמשתי באקסטרן
//על מנת להצליח להשתמש במשתנים האילו

extern int memsarLastTimeDelay;
extern int sensorLastTimeDelay;

//משתנה שמחזיק את הזמן ההשהיה של שליפת המידע
int updateTimers_LastTimeDelay = 2000;
//משתנה שבו שמרתי את זמן ביצוע הפעולה האחרונה
int updateTimers_LastTime = 0;

// פונקציה לעדכון זמני ההשהייה של הממסר,החיישן, ושל זמן שליפת המידע מהדפדפן
// הזמנים מגיעים מהשרת

void update_timers()
{
  if(millis() - updateTimers_LastTime > updateTimers_LastTimeDelay)
  {
    updateTimers_LastTime = millis();
    memsarLastTimeDelay = GetData("memsar");
    sensorLastTimeDelay = GetData("ldr");
    updateTimers_LastTimeDelay = GetData("updateTimers");
  }
}
// פונקצית מערכת לשם הפעלת הפעולות פעם אחת בתחילת עבודת הארדואינו
void setup()
{
  Serial.begin(9600);
  wifi_Setup();
  memsar_setup();
  sensor_setup();
  fan_setup();
}

// פונקצייית מערכת ראשית לשם הפעלת הפעולותת ללא ההפסקה כל פעם מחדש
void loop() 
{
  update_timers();
  memsar_loop();
  sensor_loop();
  
}

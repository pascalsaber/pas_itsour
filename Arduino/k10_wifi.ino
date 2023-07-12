// ספריות עבור החומרה של כרטיס wifi
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* wifiUser = "Redmi Note 11S";
const char* wifiPassword = "amfw4093";

WiFiClient client;
//int server_port = 80;//http

void wifi_Setup() {
  Serial.println("WiFi Connecting.");
  WiFi.begin(wifiUser, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    //כל עוד לא הצליח להתחבר
    Serial.println("Waiting...");
    delay(100);
  }
  //הצליח להתחבר
  Serial.println("WiFi Connected.");
}

int GetData(String val_delay) {
  // כדי לזהות בעיה בתוצאה
    int ret = -1; 
    // הגדרת משנה כדי לפנות דרכו לאתר האינטרנט
    HTTPClient http;
    // כדי לפנות לאתר ולמשוך נתונים 
    //פונים לכתובת ip של המחשב המארח (שרת EXPRESS)
    //כתובת הIP מתקבלת על ידי רשת ה-WIFI אליה מחובר
    // כדי למצוא את הכתובת רשת אפשר להשתמש בפקודת ipconfig
    // ביגין זה הפעולה לפניה לאתר
    http.begin(client, "http://192.168.244.88:5858/TIMER/Get/" + val_delay);
    // מצב הבקשה
    int httpCode = http.GET();
    Serial.printf("httpCode :%d",httpCode);
    Serial.println();
    if (httpCode == HTTP_CODE_OK) {
        Serial.print("HTTP response code ");
        Serial.println();
        
        String Res = http.getString();// resolt=תוצאה שמוצגת באתר 
        Serial.printf("Res: %s",Res);
        Serial.println();
        ret = Res.toInt();// המרת התוצאה שמוצגת באתר למספר
    }
    http.end();
    return ret;
}

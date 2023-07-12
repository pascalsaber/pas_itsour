
const express = require('express');

const mongoose = require('mongoose');
// פורט שהשרת שלי יאזין לו
const port = 5858;
//יצירת אפלקציה שרת דפדפן
const app = express();
// ככה אני אומרת לאפלקציה שלי לקרוא קבצי גיסון
app.use(express.json());
//הגדרת סוג קבצי תצוגה ללקוח
// כדי להציג מיד מהקוד על גבי המסך של הלקוח
//ejs-שילוב של קוד עם html
app.set("view engine", "ejs");
//הגדרה שמאפשרת לקרוא מידע שמגיע מהטופס לפוסת
var bodyParser = require('body-parser');
// הגדרה להעברת מידע בצורה מסודרת כאובייקט 
// זה מאפשר להעביר מידע בצורת מבנה של עצם במקום מחרוזת אחת
app.use(bodyParser.urlencoded({extended: false}));
//ספריית מיקום 
const path = require('path');
//להגדיר ספריה ספציפית שאליה הקוד יפנה גם אם הקובץ הנדרש אינו נמצא באותו מיקום נוכחי
app.use(express.static(path.join(__dirname, "css")));

// 127.0.0.1 כתובת המחשב / כתובת השרת
// פורט 27017 - תוכנת מונגו-דב - בסיס נתונים  
//ושם ספריה שאליה אני רוצה להתחבר
const address_MongoDB = 'mongodb://127.0.0.1:27017/pascalProject';
// שליחת כתובת כדי להתחבר למונגו
mongoose.connect(address_MongoDB);

// בודק אם החיבור לא תקין יחזיר שגיה  
mongoose.connection.on('error', error => {
    console.log(error);
   
});

//בודק אם החיבור תקין יחזיר התחברתי לבסיס נתונים
mongoose.connection.once('connected', () => {
    console.log('- Database Connected');
});

//--- חיבור ניתובים ------------------------
//יבוא קובץ ניתובים מספריית רוטס
const timers_rtr = require('./routes/timers_R');
// המטרה להגדיר בשרות האקספר ניתוב בהתאם לכתובת
// פרמטר 1: שם ניתוב 
// פרמטר 2: זה הקובץ ניתובים
// לדוגמה: http://localhost:5858/TIMER
app.use('/TIMER', timers_rtr);

//השרת מתחיל להאזין לכל ניסיונות מלקוח להתחבר לפורט
app.listen(port, () => {          
    console.log(`- Listening on port: ${port}`);
});

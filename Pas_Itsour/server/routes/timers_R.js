const express = require('express');
const router = express.Router()
module.exports = router;

const timerModel = require("../models/timer_M");
//יצירת עצם 
async function createEtsem()
{
    const data = await timerModel.findOne({timer_id:0});
    if(data == null)
    {
        //
        const modelData = new timerModel({
            timer_id:0,
            memsar_delay:2000,
            ldr_delay:2000,
            updateTimers:2000
        });
        modelData.save();
        console.log("Created new Etsem.");
       
    }
}

// בקשה רגילה מהמשתמש
router.get('/Update', async (req, res) => {
    //קריאה לפונקציה להוספת עצם במידה ואינה קיימת
    await createEtsem();
    // שליפת נתונים של העצם
    // שמירת נתונים במשתנה כאובייקט
    const data = await timerModel.findOne({timer_id:0});
    // הצגת עמוד מעוצב 
    // העברת מידע מהקוד לעמוד מעוצב כדי להציג בפני המשתמש
    // רנדר - פונקציה שמציגה למשתמש עמוד מעוצב 
    res.render("updateTimer.ejs", 
    {
        pageTitle:"עדכון זמנים",
        item:data
    }); 
});

// req=הבקשה של הלקוח 
// res=מה אני מציגה ללקוח
// ברגע שרושמים את הערכים בטופס ולוחצים עדכן
//המידע נשלח בצורת פוסט הוא מגיע לפונקצעה הבאה 
router.post('/Update',async (req, res) => {
    if(req.body.memsar_delay < 2000)
        req.body.memsar_delay = 2000;
    if(req.body.ldr_delay < 2000)
        req.body.ldr_delay = 2000;
    if(req.body.updateTimers < 2000)
        req.body.updateTimers = 2000;

    if(req.body.memsar_delay > 10000)
        req.body.memsar_delay = 10000;
    if(req.body.ldr_delay > 10000)
        req.body.ldr_delay = 10000;
    if(req.body.updateTimers > 10000)
        req.body.updateTimers = 10000;

    const modelData = {
        memsar_delay:req.body.memsar_delay,
        ldr_delay:req.body.ldr_delay,
        updateTimers:req.body.updateTimers
    };
    // מעדכן את העצם הקיימת בבסיס נתונים במידע שהתקבל
    await timerModel.findOneAndUpdate({timer_id:0}, modelData);
    
    // שליפת העצם מבסיס הנתונים לאחר העדכון שבוצע בפקודה הקודמת
    let newData = await timerModel.findOne({timer_id:0});

    //Print new Details in Page
    //מציג עמוד אינטרנט לאחר שהעברנו אליו ערכים להצגה 
    //עמוד אינטרנט שמציג לי את הנתונים החדשים ששלפתי מבסיס הנתונים
    res.render("displayTimers.ejs", 
    {
        pageTitle:"זמנים לאחר ששלפתי מבסיס הנתונים שלי",
        item:newData
    });
});

//מציג את המספר של הפרמטר המבוקש יכול להיות ממסר חיישן 
router.get('/Get/:timer', async (req, res) => {
    await createEtsem();
    let data = await timerModel.findOne({timer_id:0});
    console.log(data);
    if(req.params.timer == "memsar")
        res.send(data.memsar_delay.toString());
    else if(req.params.timer == "ldr")
        res.send(data.ldr_delay.toString());
    else if(req.params.timer == "updateTimers")
        res.send(data.updateTimers.toString());  
    else
        res.send("פרמטר אינו קיים");
});


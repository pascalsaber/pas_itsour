const mongoose = require('mongoose');

const dataSchema = new mongoose.Schema({
    timer_id: {
        required: true,
        type: Number
    },
    memsar_delay: {
        required: true,
        type: Number
    },
    ldr_delay: {
        required: true,
        type: Number
    },
    updateTimers: {
        required: true,
        type: Number
    }
});
// הוספת טבלה בשם טיימר שהמבנה שלה הוא דאטא סכימה
// זאת הדרך שבה מאפשרים לסכימה להיות נגישה לקבצים אחרים בבפרוייקט
module.exports = mongoose.model('timer', dataSchema)
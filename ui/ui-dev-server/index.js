const express = require("express");
const app = express();
app.use(express.static('public'));

let c1 = 120;
let c2 = 220;
let isWorking = 0;

app.get("/", (req, res) => {
    res.sendFile(__dirname + "/public/index.html");
});

app.get("/getContainer", (req, res) => {
    res.json({
        container1: c1,
        container2: c2,
        isWorking: isWorking
    });
});

app.get("/setContainer", (req, res) => {
    c1 = req.query.container1;
    c2 = req.query.container2;

    isWorking = 1; // başlat
    res.json({ state: '1' }); // hemen yanıt ver

    setTimeout(() => {
        isWorking = 0; // 5 saniye sonra durdur
    }, 5000);
});

console.log("mixer");
app.listen(8080);

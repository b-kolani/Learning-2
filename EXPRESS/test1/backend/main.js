const express = require('express');
const cors = require('cors');

const port = 3000;
const app = express();

// Use cors middleware
// Adds headers: Access-Control-Allow-Origin: *
app.use(cors());

// To serve static files as images, CSS files, and JS files,
// use the express.static built-in middleware function in Express.
app.use('/static', express.static('files'));
app.use('/static', express.static('public'));

app.get('/', (req, res) => {
    res.end("Hello World!");
});

app.listen(port, () => {
    console.log("App Running");
});
import http from 'http';
import connectdb from './src/db.js';

function start() {
    connectdb();
    const server = http.createServer((req, res) => {
        return res.end("Hello!");
    })

    server.listen(3000, () => {
        console.log("App Running...!");
    });
}

start();

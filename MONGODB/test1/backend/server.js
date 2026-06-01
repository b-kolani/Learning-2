import http from "http";
import connectDB from "./src/dbConnection.js"

const server = http.createServer((req, res) => {
    res.end("Welcome");
});

connectDB().catch(console.dir);

server.listen(3000, () => {
    console.log("Server running...!");
});
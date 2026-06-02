import http from "http";
import connectDB from "./src/dbConnection.js"

connectDB().catch(console.dir);

const server = http.createServer((req, res) => {
    res.end("Welcome");
});


server.listen(3000, () => {
    console.log("Server running...!");
});
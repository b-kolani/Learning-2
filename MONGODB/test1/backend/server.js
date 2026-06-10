import http from "http";
import connectDB from "./src/dbConnection.js"

// Make sure to connect to the db before 
// the server starts listening
connectDB()
    .then(server.listen(3000, () => {
        console.log("Server running...!");
    }))
    .catch (console.dir);

const server = http.createServer((req, res) => {
    res.end("Welcome");
});



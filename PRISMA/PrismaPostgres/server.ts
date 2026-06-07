import http from 'http';
import { prisma } from "./lib/prisma"

const server = http.createServer(async (req, res) => {
    if (req.url === '/') {
        res.writeHead(200, {
            "access-control-allow-origin": '*',
            "content-type": 'application/json'
        });
        return res.end(JSON.stringify({ message: 'Hello!' }));
    } else if (req.url === '/posts') {
        res.writeHead(200, {
            "access-control-allow-origin": '*',
            "content-type": "application/json"
        });
        const allPosts = await prisma.post.findMany({
            include: {
                author: true
            }
        });
        return res.end(JSON.stringify({ allPosts }));
    }
});

server.listen(3000, () => {
    console.log('App is running...!')
});


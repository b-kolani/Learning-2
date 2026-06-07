import http from 'http';
import { prisma } from "./lib/prisma"

const server = http.createServer(async (req, res) => {
    if (req.method === 'OPTIONS') {
        res.writeHead(204, {
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'OPTIONS, GET, POST',
            'Access-Control-Allow-Headers': 'Content-Type'
        });
        return res.end();
    }
    if (req.url === '/' && req.method === 'GET') {

        res.writeHead(200, {
            "Access-Control-Allow-Origin": '*',
            "Content-Type": 'application/json'
        });
        return res.end(JSON.stringify({ message: 'Hello!' }));
    } else if (req.url === '/posts') {
        res.writeHead(200, {
            "Access-Control-Allow-Origin": '*',
            "Content-Type": "application/json"
        });
        const allPosts = await prisma.post.findMany({
            include: {
                author: true
            }
        });
        return res.end(JSON.stringify({ allPosts }));
    } else if (req.url === '/post' && req.method === 'POST') {
        let body = '';
        req.on('data', (chunk) => {
            // console.log(chunk);
            body += chunk;
        });
        req.on('end', async () => {
            const data = JSON.parse(body);
            const user = await prisma.user.create({
                data,
                include: {
                    posts: true
                }
            });
            res.writeHead(200, {
                'Access-Control-Allow-Origin': '*',
                'Content-Type': 'application/json'
            });
            res.end(JSON.stringify({ message: 'Post created!' }));
        })
    }
});

server.listen(3000, () => {
    console.log('App is running...!')
});


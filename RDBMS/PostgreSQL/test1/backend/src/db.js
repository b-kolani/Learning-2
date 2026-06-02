import { Client } from 'pg';
import { config } from 'dotenv';

config();

// Here we have two ways to connect 
// to the DB 
// --- 1st create a client 
// by supplying an object as argument to the 
// Client class.
const client = new Client({
    host: "aws-0-eu-west-1.pooler.supabase.com",
    port: 5432,
    database: "postgres",
    user: "postgres.pbshpjhdyymahxldayzd",
    password: process.env.DATABASE_PASSWORD
});

async function connectdb() {
    await client.connect();
    console.log("Connected to the database !");

    // Query the DB
    const result = await client.query("SELECT NOW()");
    console.log(result.rows);

    // Close the connection
    await client.end();
}

export default connectdb;
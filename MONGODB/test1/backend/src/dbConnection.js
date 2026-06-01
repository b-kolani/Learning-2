import { MongoClient } from 'mongodb';
import { config } from "dotenv";

config();

async function connectDB() {
    // String connection URI to the DB
    const uri = process.env.DATABASE_URI;
    const client = new MongoClient(uri);
    try {
        const database = client.db('sample_mflix');
        const movies = database.collection('movies');
        // movies.find().toArray().then(console.log);
        // Query for a movie
        const query = { title: 'The Great Train Robbery' };
        // console.log("Start searching movie!");
        const movie = await movies.findOne(query);
        // console.log("Movie found!");
        console.log(movie);
    } finally {
        await client.close();
    }
}

export default connectDB;
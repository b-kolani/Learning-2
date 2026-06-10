// ESM
// our-db-connector.js

import fastifyPlugin from "fastify-plugin";
import fastifyMongodb from "@fastify/mongodb";
import 'dotenv/config';

/**
 * @param {FastifyInstance} fastify
 * @param {Object} options
 */

async function dbConnector(fastify, options) {
    await fastify.register(fastifyMongodb, {
        url: process.env.DATABASE_URI
    });
}

export default fastifyPlugin(dbConnector);

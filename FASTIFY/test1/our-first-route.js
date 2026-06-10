// ESM
// our-first-route.js 

/**
 * @param {FastifyInstance} fastify
 * @param {Object} options 
 */

async function routes(fastify, options) {
    console.log(fastify.mongo);
    const db = fastify.mongo.client.db('test');
    const collection = db.collection('animals');
    
    fastify.get('/', async (request, reply) => {
        return { hello: "World" };
    });

    fastify.get('/animals', async (request, reply) => {
        const result = await collection
            .find()
            .toArray();
        if (result.length === 0) {
            throw new Error('No documents found');
        }
        return result;
    });

    fastify.get('/animals/:animal', async (request, reply) => {
        const result = await collection.findOne({ animal: request.params.animal });
        if (!result) {
            throw new Error('Invalid value');
        }
        return result;
    });

    const animalBodyJsonSchema = {
        type: 'object',
        required: ['animal'],
        properties: {
            animal: { type: 'string' },
        }
    }

    const schema = {
        body: animalBodyJsonSchema,
    }

    fastify.post('/animals', { schema }, async (request, reply) => {
        const result = await collection.insertOne({ animal: request.body.animal });
        return result;
    });
}

export default routes;
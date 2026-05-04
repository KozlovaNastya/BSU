const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');

const rest = require('./rest');
const store = require('./store');

const app = express();
const PORT = 3000;

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(express.static(path.join(__dirname, 'dist')));

app.get('/items', rest.getAllItems);
app.get('/items/:id', rest.getItemById);
app.post('/items', rest.createItem);
app.put('/items/:id', rest.updateItem);
app.delete('/items/:id', rest.deleteItem);

app.listen(PORT, () => {
    console.log(`Сервер запущен: http://localhost:${PORT}`);
});

const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');

const rest = require('./rest');
const store = require('./store');

const app = express();
const PORT = 3000;

app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (req, res) => {
    try {
        const recipes = store.getAll();
        res.render('index', { recipes: recipes });
    } catch (err) {
        res.status(500).send("Ошибка при загрузке данных: " + err.message);
    }
});

app.get('/items', rest.getAllItems);
app.get('/items/:id', rest.getItemById);
app.post('/items', rest.createItem);
app.put('/items/:id', rest.updateItem);
app.delete('/items/:id', rest.deleteItem);

// Запуск сервера
app.listen(PORT, () => {
    console.log(`Сервер запущен!`);
    console.log(`Адрес: http://localhost:${PORT}`);
});

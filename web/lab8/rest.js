const store = require('./store');

exports.getAllItems = (req, res) => {
    res.json(store.getAll());
};

exports.getItemById = (req, res) => {
    const item = store.getById(req.params.id);
    item ? res.json(item) : res.status(404).send('Рецепт не найден');
};

exports.createItem = (req, res) => {
    const newItem = store.add(req.body);
    res.status(201).json(newItem);
};

exports.updateItem = (req, res) => {
    const updated = store.update(req.params.id, req.body);
    if (updated) {
        res.json(updated);
    } else {
        res.status(404).send('Рецепт не найден');
    }
};

exports.deleteItem = (req, res) => {
    const success = store.remove(req.params.id);
    success ? res.status(204).send() : res.status(404).send('Рецепт не найден');
};

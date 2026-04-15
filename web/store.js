const fs = require('fs');
const path = require('path');

const dbPath = path.join(__dirname, 'db.json');

const readData = () => {
    if (!fs.existsSync(dbPath)) {
        fs.writeFileSync(dbPath, '[]');
    }
    const data = fs.readFileSync(dbPath, 'utf8');
    return JSON.parse(data);
};

const writeData = (data) => {
    fs.writeFileSync(dbPath, JSON.stringify(data, null, 2));
};

module.exports = {
    getAll: () => readData(),
    getById: (id) => readData().find(item => item.id === parseInt(id)),
    add: (newItem) => {
        const data = readData();
        newItem.id = Date.now(); 
        data.push(newItem);
        writeData(data);
        return newItem;
    },
    update: (id, updatedItem) => {
    let data = readData();
    const index = data.findIndex(item => item.id === parseInt(id));
    if (index !== -1) {
        data[index] = { ...data[index], ...updatedItem, id: parseInt(id) };
        writeData(data);
        return data[index];
    }
    return null;
    },
    remove: (id) => {
        let data = readData();
        const filteredData = data.filter(item => item.id !== parseInt(id));
        if (data.length !== filteredData.length) {
            writeData(filteredData);
            return true;
        }
        return false;
    }
};

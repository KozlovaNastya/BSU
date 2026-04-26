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
    // *** Изменено ***
    getAll: (params = {}) => {
        let data = readData();
        const { search, sort, page = 1, limit = 5 } = params;

        if (search) {
            data = data.filter(item => 
                item.name.toLowerCase().includes(search.toLowerCase())
            );
        }

        if (sort === 'asc') {
            data.sort((a, b) => a.name.localeCompare(b.name));
        } else if (sort === 'desc') {
            data.sort((a, b) => b.name.localeCompare(a.name));
        }

        const totalItems = data.length;
        const startIndex = (page - 1) * limit;
        const paginatedData = data.slice(startIndex, startIndex + parseInt(limit));

        return {
            items: paginatedData,
            totalItems,
            totalPages: Math.ceil(totalItems / limit),
            currentPage: parseInt(page)
        };
    },
    // ***

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

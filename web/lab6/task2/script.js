class TLocalStorage {
    #lsKey;

    constructor(storageKey) {
        this.#lsKey = storageKey;
    }

    save(data) {
        localStorage.setItem(this.#lsKey, JSON.stringify(data));
    }

    load() {
        const data = localStorage.getItem(this.#lsKey);
        return data ? JSON.parse(data) : {};
    }
}

class THashStorage {
    #dishesStorage = {};
    #lsProvider;

    constructor(name) {
        this.#lsProvider = new TLocalStorage(name);
        this.#dishesStorage = this.#lsProvider.load();
    }

    AddValue(key, value) {
        this.#dishesStorage[key] = value;
        this.#lsProvider.save(this.#dishesStorage);
    }

    DeleteValue(key) {
        if (key in this.#dishesStorage) {
            delete this.#dishesStorage[key];
            this.#lsProvider.save(this.#dishesStorage);
            return true;
        }
        return false;
    }

    GetValue(key) {
        if (key in this.#dishesStorage) {
            return "Блюдо: " + key + "\nВремя приготовления: " + this.#dishesStorage[key];
        }
        return "Нет информации";
    }

    ListValues() {
        let res = "";
        for (let key in this.#dishesStorage) {
            res += "Блюдо: " + key + " | Время: " + this.#dishesStorage[key] + "\n";
        }
        return res || "Список пуст";
    }
}

const dishStorage = new THashStorage('dishes_data');

function addValue() {
    const name = prompt("Введите название блюда:");
    if (!name) return;
    const info = prompt("Введите время приготовления:");
    if (!info) return;

    dishStorage.AddValue(name, info);
    alert("Блюдо '" + name + "' сохранено в LocalStorage");
}

function deleteValue() {
    const name = prompt("Введите название для удаления:");
    if (!name) return;

    if (dishStorage.DeleteValue(name))
        alert("Блюдо удалено");
    else 
        alert("Блюда нет в списке");
}

function getValueInfo() {
    const name = prompt("Какое блюдо найти?");
    if (!name) return;
    alert(dishStorage.GetValue(name));
}

function listValues() {
    alert("Список всех блюд:\n" + dishStorage.ListValues());
}

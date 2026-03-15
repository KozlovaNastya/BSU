class THashStorage{
    #dishesStorage = {};

        Reset() {
        this.#dishesStorage = {};
    }

AddValue(key, value){
    this.#dishesStorage[key] = value;
}

DeleteValue(key){
    if(key in this.#dishesStorage){
        delete this.#dishesStorage[key];
        return true;
    }
    return false;
}

GetValue(key){
    if(key in this.#dishesStorage){
        return "Блюдо: " + key + "\nВремя приготовления: " + this.#dishesStorage[key];
    }
    return "нет информации";
}

ListValues(){
    let res = "";
    for(let key in this.#dishesStorage){
        res += "Блюдо: " + key + "\nВремя приготовления: " + this.#dishesStorage[key] + "\n";
    }
    return res || "Список пуст";
}

    GetKeys() {
        return Object.keys(this.#dishesStorage);
    }

}

//=====================================

const dishStorage = new THashStorage();

function addValue(){
    const name = prompt("Введите блюдо")
    if(!name) return;
    const info = prompt("Введите время приготовления");
    if(!info) return;

    dishStorage.AddValue(name, info);
    alert("Блюдо " + name + " успешно добавлено");
}

function deleteValue(){
    const name = prompt("Введите блюдо")
    if(!name) return;

    if(dishStorage.DeleteValue(name))
        alert("Блюдо " + name + " успешно удалено");
    else alert("Блюда нет в списке");
}

function getValueInfo(){
    const name = prompt("Введите блюдо")
    if(!name) return;

    alert(dishStorage.GetValue(name));
}

function listValues(){
    console.log("Список всех блюд:\n" + dishStorage.ListValues());
}
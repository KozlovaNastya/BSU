let dishesStorage = {};

function AddValue(key, value){
    dishesStorage[key] = value;
}

function DeleteValue(key){
    if(key in dishesStorage){
        delete dishesStorage[key];
        return true;
    }
    return false;
}

function GetValueInfo(key){
    if(key in dishesStorage){
        return "Блюдо: " + key + "\nВремя приготовления: " + dishesStorage[key];
    }
    return "нет информации";
}

function ListValues(){
    let res = "";
    for(let key in dishesStorage){
        res += "Блюдо: " + key + "\nВремя приготовления: " + dishesStorage[key] + "\n";
    }
    return res || "Список пуст";
}

//=====================================

function addValue(key, value){
    const name = prompt("Введите блюдо")
    if(!name) return;
    const info = prompt("Введите время приготовления");
    if(!info) return;

    AddValue(name, info);
    alert("Блюдо " + name + " успешно добавлено");
}

function deleteValue(key){
    const name = prompt("Введите блюдо")
    if(!name) return;

    if(DeleteValue(name))
        alert("Блюдо " + name + " успешно удалено");
    else alert("Блюда нет в списке");
}

function getValueInfo(key){
    const name = prompt("Введите блюдо")
    if(!name) return;

    alert(GetValueInfo(name));
}

function listValues(){
    alert("Список всех блюд:\n" + ListValues());
}
var FormConfig = [
  { label: 'Название рецепта:', elemtype: 'text', name: 'recipe_name', width: 300, required: true },
  { label: 'Автор:', elemtype: 'text', name: 'author', width: 200, required: true },
  { label: 'Сложность (1-5):', elemtype: 'number', name: 'difficulty', width: 50, required: true },
  { label: 'Разрешить отзывы:', elemtype: 'checkbox', name: 'enable_comments' },
  { label: 'Опубликовать:', elemtype: 'submit', value: 'Отправить рецепт' }
];

function buildForm(config, formName) {
    const form = document.forms[formName];
    
    config.forEach(item => {
        const row = document.createElement('div');
        row.style.marginBottom = '15px';

        if (item.label && item.elemtype !== 'submit') {
            const label = document.createElement('label');
            label.textContent = item.label;
            label.style.display = 'inline-block';
            label.style.width = '160px';
            row.appendChild(label);
        }

        let element;
        if (item.elemtype === 'submit') {
            element = document.createElement('input');
            element.type = 'submit';
            element.value = item.value;
        } else {
            element = document.createElement('input');
            element.type = item.elemtype;
            element.name = item.name;
            if (item.width) element.style.width = item.width + 'px';
        }
        
        row.appendChild(element);

        const errorSpan = document.createElement('span');
        errorSpan.className = 'error-msg';
        errorSpan.style.color = 'red';
        errorSpan.style.marginLeft = '10px';
        errorSpan.id = 'err_' + item.name;
        row.appendChild(errorSpan);

        if (item.elemtype !== 'submit' && item.elemtype !== 'checkbox') {
            element.addEventListener('blur', () => validateField(element, item));
        }

        form.appendChild(row);
    });

    form.onsubmit = function(e) {
        let isValid = true;
        config.forEach(item => {
            const el = form.elements[item.name];
            if (el && !validateField(el, item)) {
                isValid = false;
            }
        });

        if (!isValid) {
            e.preventDefault();
            alert('Пожалуйста, исправьте ошибки в форме');
        }
    };
}

function validateField(element, configItem) {
    const errorSpan = document.getElementById('err_' + configItem.name);
    let message = "";

    if (configItem.required && !element.value.trim()) {
        message = "Это поле обязательно для заполнения";
    } else if (configItem.name === 'difficulty' && (element.value < 1 || element.value > 5)) {
        message = "Введите число от 1 до 5";
    }

    if (errorSpan) {
        errorSpan.textContent = message;
    }
    
    return message === "";
}

window.onload = () => buildForm(FormConfig, 'RECP_FORM');

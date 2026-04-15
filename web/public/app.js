function showAddForm() {
    const name = prompt("Введите название рецепта:");
    if (name) {
        fetch('/items', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ name: name })
        }).then(() => location.reload());
    }
}

async function deleteItem(id) {
    if (confirm('Вы точно хотите удалить этот рецепт?')) {
        const response = await fetch(`/items/${id}`, {
            method: 'DELETE'
        });

        if (response.ok) {
            const element = document.getElementById(`item-${id}`);
            if (element) element.remove();
        } else {
            alert('Ошибка при удалении');
        }
    }
}

async function editItem(id) {
    const newName = prompt("Введите новое название рецепта:");
    
    if (newName === null || newName.trim() === "") return;

    const response = await fetch(`/items/${id}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ name: newName })
    });

    if (response.ok) {
        const card = document.getElementById(`item-${id}`);
        const content = card.querySelector('.card-content');
        content.textContent = newName;
    } else {
        alert('Ошибка при обновлении рецепта');
    }
}

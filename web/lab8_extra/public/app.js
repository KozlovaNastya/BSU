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


// *** Изменено ***
let currentPage = 1;

async function applyFilters(page = 1) {
    currentPage = page;
    const search = document.getElementById('searchInput').value;
    const sort = document.getElementById('sortSelect').value;

    const response = await fetch(`/items?search=${search}&sort=${sort}&page=${page}&limit=3`);
    const data = await response.json();

    renderList(data.items);
    renderPagination(data.totalPages, data.currentPage);
}

function renderList(items) {
    const list = document.getElementById('recipe-list');
    list.innerHTML = items.map(recipe => `
        <div class="card" id="item-${recipe.id}">
            <div class="card-actions">
                <span class="edit-icon" onclick="editItem('${recipe.id}')">✏️</span>
                <span class="delete-icon" onclick="deleteItem('${recipe.id}')">❌</span>
            </div>
            <div class="card-content">${recipe.name}</div>
        </div>
    `).join('');
}

function renderPagination(totalPages, current) {
    const container = document.getElementById('pagination');
    let html = '';
    for (let i = 1; i <= totalPages; i++) {
        html += `<button class="${i === current ? 'active' : ''}" onclick="applyFilters(${i})">${i}</button>`;
    }
    container.innerHTML = html;
}

applyFilters();

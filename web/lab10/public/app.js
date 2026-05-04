import './style.css';
import { fromEvent, combineLatest, BehaviorSubject } from 'rxjs';
import { ajax } from 'rxjs/ajax';
import { map, switchMap, startWith, debounceTime } from 'rxjs/operators';

const searchInput = document.getElementById('searchInput');
const search$ = fromEvent(searchInput, 'input').pipe(
    map(e => e.target.value),
    startWith(''),
    debounceTime(300)
);

const sortSelect = document.getElementById('sortSelect');
const sort$ = fromEvent(sortSelect, 'change').pipe(
    map(e => e.target.value),
    startWith('name')
);

const page$ = new BehaviorSubject(1);

const refresh$ = new BehaviorSubject(null);

combineLatest([search$, sort$, page$, refresh$]).pipe(
    switchMap(([search, sort, page]) => 
        ajax.getJSON(`/items?search=${search}&sort=${sort}&page=${page}&limit=3`)
    )
).subscribe(data => {
    renderList(data.items);
    renderPagination(data.totalPages, data.currentPage);
});

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
        html += `<button class="${i === current ? 'active' : ''}" onclick="changePage(${i})">${i}</button>`;
    }
    container.innerHTML = html;
}

window.showAddForm = () => {
    const name = prompt("Введите название рецепта:");
    if (name) {
        ajax.post('/items', { name }, { 'Content-Type': 'application/json' })
            .subscribe(() => refresh$.next(null));
    }
};

window.deleteItem = (id) => {
    if (confirm('Вы точно хотите удалить этот рецепт?')) {
        ajax.delete(`/items/${id}`)
            .subscribe(() => refresh$.next(null));
    }
};

window.editItem = (id) => {
    const newName = prompt("Введите новое название рецепта:");
    if (newName && newName.trim() !== "") {
        ajax.put(`/items/${id}`, { name: newName }, { 'Content-Type': 'application/json' })
            .subscribe(() => refresh$.next(null));
    }
};

window.changePage = (page) => {
    page$.next(page);
};

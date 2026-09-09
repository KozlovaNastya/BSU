import React, { useState } from "react";
import "./styles.css";

import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';

const MySearch = () => {
  const allAnimals = window.lab1models?.animalsModel?.() || [];
  const [searchTerm, setSearchTerm] = useState("");

  const filteredAnimals = searchTerm.trim() === "" 
    ? [...allAnimals].sort((a, b) => a.localeCompare(b, 'ru'))
    : allAnimals
        .filter(animal => animal.toLowerCase().includes(searchTerm.toLowerCase()))
        .sort((a, b) => a.localeCompare(b, 'ru'));

  return (
    <div style={{ padding: '20px' }}>
      <h2>Поиск животных</h2>
      
      <div>
        <label>Введите подстроку для поиска:</label>
        <input
          type="text"
          value={searchTerm}
          onChange={(e) => setSearchTerm(e.target.value)}
          placeholder="Например: лев, кот..."
          style={{ padding: '8px', width: '300px', fontSize: '16px', marginLeft: '10px' }}
        />
      </div>

      <p>Искомая подстрока: {searchTerm || '(не введена)'}</p>

      <h3>Результаты поиска:</h3>
      
      {filteredAnimals.length > 0 ? (
        <List>
          {filteredAnimals.map((animal, index) => (
            <ListItem key={index}>{animal}</ListItem>
          ))}
        </List>
      ) : (
        <p style={{ color: '#999', fontStyle: 'italic' }}>
          {searchTerm ? 'Совпадений не найдено' : 'Введите текст для поиска'}
        </p>
      )}
    </div>
  );
};

export default MySearch;
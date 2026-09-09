import React, { useState } from "react"; 
import "./styles.css";

const Regions = () => {
  const allRegions = window.lab1models.regionsModel();
  const [substr, setSubstr] = useState("");

  const getFilteredRegions = () => {
    const searchTerm = substr.trim();
    
    if (!allRegions || allRegions.length === 0) {
      return [];
    }
    
    if (searchTerm === "") {
      return [...allRegions].sort((a, b) => a.localeCompare(b, 'ru'));
    }
    
    const filtered = allRegions.filter(region =>
      region.toLowerCase().includes(searchTerm.toLowerCase())
    );
    
    return filtered.sort((a, b) => a.localeCompare(b, 'ru'));
  };

  const filteredRegions = getFilteredRegions();

  return (
    <div>
      <div className="state-search">
        {substr}
      </div>
      <div className="lab1-example-output">
        <span id='IInfo'>
          {substr && (
            <span>Результаты поиска для "{substr}":</span>
          )}
        </span>
      </div>
      <label htmlFor="substrId">Enter substring to search:</label>
      <input
        id="substrId"
        type="text"
        value={substr}
        onChange={(e) => setSubstr(e.target.value)}
      />
      
      <ul style={{ listStyleType: 'none', padding: '10px 0' }}>
        {filteredRegions.length > 0 ? (
          filteredRegions.map((region, index) => (
            <li key={index} style={{ padding: '5px 0' }}>
              {region}
            </li>
          ))
        ) : (
          <li style={{ color: '#666', fontStyle: 'italic' }}>
            {substr ? 'Нет областей, соответствующих запросу' : 'Введите текст для поиска'}
          </li>
        )}
      </ul>
    </div>
  );
};

export default Regions;
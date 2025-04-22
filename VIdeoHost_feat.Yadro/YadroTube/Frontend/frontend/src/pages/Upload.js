import React, { useState } from 'react';
import axios from 'axios';

const Upload = () => {
  const [file, setFile] = useState(null);

  const handleUpload = async (e) => {
    e.preventDefault();
    const formData = new FormData();
    formData.append('file', file);

    try {
      await axios.post('http://localhost:8000/api/videos/', formData, {
        headers: {
          'Authorization': `Bearer ${localStorage.getItem('access_token')}`,
          'Content-Type': 'multipart/form-data',
        },
      });
      alert('Видео загружено!');
    } catch (err) {
      alert('Ошибка загрузки!');
    }
  };

  return (
    <form onSubmit={handleUpload}>
      <input type="file" onChange={(e) => setFile(e.target.files[0])} />
      <button type="submit">Загрузить</button>
    </form>
  );
};
export default Upload;
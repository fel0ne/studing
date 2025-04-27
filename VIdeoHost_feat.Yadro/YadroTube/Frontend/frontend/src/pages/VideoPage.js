// src/pages/VideoPage.js
import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import ReactPlayer from 'react-player';
import axios from 'axios';
import Header from '../components/Header';
// --- ДОБАВЛЕНО: Импорт компонента комментариев ---
import VideoComments from '../components/VideoComments';
// --- Конец добавленного импорта ---


const VideoPage = () => {
  const { id } = useParams();
  const [video, setVideo] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState('');
  // --- ДОБАВЛЕНО: Проверка статуса авторизации для передачи в компонент комментариев ---
  const isLoggedIn = !!localStorage.getItem('access_token'); // Проверяем наличие токена
  // --- Конец добавленной проверки ---


  useEffect(() => {
    const fetchVideo = async () => {
      try {
        const response = await axios.get(`http://localhost:8000/api/videos/${id}/`, {
          headers: {
            'Authorization': `Bearer ${localStorage.getItem('access_token')}`
          }
        });  
        setVideo(response.data);
      } catch (err) {
        setError('Ошибка загрузки видео');
        // Если видео не найдено (например, 404), можно установить video в null явно,
        // хотя ваше начальное состояние handleit already.
        if (err.response && err.response.status === 404) {
            setVideo(null);
        }
      } finally {
        setLoading(false);
      }
    };

    fetchVideo();
  }, [id]); // Перезагружаем видео при изменении ID в URL

  if (loading) return <div>Загрузка...</div>;
  if (error && !video) return <div>{error}</div>; // Показываем ошибку, только если видео не загружено
  if (!video && !loading) return <div>Видео не найдено</div>; // Показываем, если видео нет и загрузка завершена


  return (
    <div>
      <Header />
      {/* --- ИЗМЕНЕНО: Основной контейнер теперь использует Flexbox --- */}
      <div className="content-layout" style={{
        display: 'flex', // Включаем Flexbox
        maxWidth: '1600px', // Увеличиваем максимальную ширину, чтобы вместить видео + комментарии
        margin: '80px auto 20px auto', // Отступ сверху, чтобы контент не скрывался за фиксированной шапкой
        padding: '0 20px', // Отступы по бокам
        gap: '30px', // Промежуток между блоком видео и блоком комментариев
        flexWrap: 'wrap', // Разрешаем элементам переноситься на новую строку на узких экранах
        alignItems: 'flex-start' // Выравниваем элементы по верху
      }}>

        {/* --- Блок слева: Видео плеер и информация о видео --- */}
        <div className="video-and-info" style={{
          flex: '2 1 700px', // grow (растет в 2 раза быстрее), shrink (сжимается), basis (базовая ширина 700px)
          minWidth: 0 // Важно для адаптивности во Flexbox
        }}>
          <div className="player-wrapper" style={{ position: 'relative', paddingTop: '56.25%' }}>
            <ReactPlayer
              className="react-player"
              url={video.file_url} // Используем file_url из сериализатора
              controls
              width="100%"
              height="100%"
              style={{ position: 'absolute', top: 0, left: 0 }}
              config={{
                file: {
                  attributes: {
                    controlsList: 'nodownload' // Отключить скачивание
                  }
                }
              }}
          />
        </div>

        <div className="video-info" style={{ marginTop: '20px' }}>
          <h1>{video.title}</h1>
          <p style={{ color: '#666', margin: '10px 0' }}>
            Автор: {video.author_username} • {new Date(video.uploaded_at).toLocaleDateString()}
          </p>
          <p style={{ lineHeight: '1.6' }}>{video.description}</p>
        </div>
        </div> {/* Конец блока video-and-info */}

        {/* --- Блок справа: Комментарии --- */}
        <div className="comments-sidebar" style={{
          flex: '1 1 400px', // grow (растет), shrink (сжимается), basis (базовая ширина 400px)
          minWidth: 300, // Минимальная ширина блока комментариев
          display: 'flex', // Комментарии внутри тоже Flexbox для расположения списка и формы
          flexDirection: 'column' // Элементы внутри располагаются вертикально
        }}>
          {/* Используем компонент VideoComments */}
          <VideoComments videoId={id} isLoggedIn={isLoggedIn} />
        </div> {/* Конец блока comments-sidebar */}

      </div> {/* Конец основного контейнера content-layout */}
    </div>
  );
};

export default VideoPage;
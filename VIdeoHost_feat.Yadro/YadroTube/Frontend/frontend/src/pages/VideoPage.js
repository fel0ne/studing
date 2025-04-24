import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import ReactPlayer from 'react-player';
import axios from 'axios';
import Header from '../components/Header';

const VideoPage = () => {
  const { id } = useParams();
  const [video, setVideo] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState('');

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
      } finally {
        setLoading(false);
      }
    };
    
    fetchVideo();
  }, [id]);

  if (loading) return <div>Загрузка...</div>;
  if (error) return <div>{error}</div>;
  if (!video) return <div>Видео не найдено</div>;

  return (
    <div>
      <Header />
      <div className="video-container" style={{ maxWidth: '1200px', margin: '0 auto', padding: '20px' }}>
        <div className="player-wrapper" style={{ position: 'relative', paddingTop: '56.25%' }}>
          <ReactPlayer
            className="react-player"
            url={video.file_url}
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
      </div>
    </div>
  );
};

export default VideoPage;
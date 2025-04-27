// src/components/VideoComments.js
import React, { useEffect, useState } from 'react';
import axios from 'axios';
// Если нужен переход на страницу входа при ошибке 401, импортируйте useNavigate или Link
// import { useNavigate, Link } from 'react-router-dom';
// --- ДОБАВЛЕНО: Импортируем файл стилей ---
import './VideoComments.css';


// Этот компонент обрабатывает загрузку, отображение и отправку комментариев для видео
const VideoComments = ({ videoId, isLoggedIn }) => {
    const [comments, setComments] = useState([]);
    const [newCommentText, setNewCommentText] = useState('');
    const [loading, setLoading] = useState(true); // Состояние загрузки комментариев
    const [error, setError] = useState(''); // Состояние ошибки (для загрузки и отправки)
    const [posting, setPosting] = useState(false); // Состояние отправки нового комментария

    // Если нужен useNavigate для перенаправления при 401 ошибке
    // const navigate = useNavigate();

    // Эффект для загрузки комментариев при монтировании компонента или изменении ID видео
    useEffect(() => {
        const fetchComments = async () => {
            try {
                // GET запрос для получения комментариев. Доступен всем.
                const response = await axios.get(`http://localhost:8000/api/videos/${videoId}/comments/`); // <-- URL вашего API для комментариев
                // Предполагается, что бэкенд возвращает комментарии, отсортированные по дате (от старых к новым по умолчанию модели Comment)
                // Если нужна сортировка от новых к старым на фронтенде:
                // setComments(response.data.sort((a, b) => new Date(b.created_at) - new Date(a.created_at)));
                 setComments(response.data); // Используем сортировку с бэкенда
            } catch (err) {
                console.error("Ошибка загрузки комментариев:", err.response || err);
                setError('Не удалось загрузить комментарии.');
            } finally {
                setLoading(false);
            }
        };

        fetchComments();

        // TODO (Опционально): Реализовать WebSockets здесь для обновлений в реальном времени
        // Подключиться к WebSocket для получения новых комментариев по videoId

        // TODO (Опционально): Функция очистки для отключения WebSocket при размонтировании компонента
        // return () => {
        //   Отключить WebSocket
        // };

    }, [videoId]); // Зависимости хука: перезагружаем комментарии при смене videoId
    // Если используете navigate в useEffect, добавьте его в зависимости: [videoId, navigate]


    // Обработчик отправки нового комментария
    const handlePostComment = async (e) => {
        e.preventDefault();
        // Проверяем, что поле ввода не пустое после удаления пробелов
        const trimmedComment = newCommentText.trim();
        if (!trimmedComment) {
             setError('Комментарий не может быть пустым.'); // Установим сообщение об ошибке
             setTimeout(() => setError(''), 3000); // Сбросим ошибку через 3 секунды
             return; // Прерываем функцию
        }
        
        // Проверяем, авторизован ли пользователь перед отправкой (фронтенд-проверка)
        if (!isLoggedIn) {
            setError('Вы не авторизованы. Пожалуйста, войдите, чтобы оставить комментарий.');
            // Опционально: перенаправить на страницу входа
            // if (navigate) navigate('/login');
            return; // Останавливаем выполнение, если не авторизован
        }

        setPosting(true); // Устанавливаем состояние отправки (для кнопки)
        setError(''); // Сбрасываем предыдущие ошибки перед новой попыткой

        try {
            // POST запрос для создания нового комментария. Требуется аутентификация.
            const response = await axios.post(`http://localhost:8000/api/videos/${videoId}/comments/`, { // <-- Тот же URL, но метод POST
                text: trimmedComment // Отправляем текст комментария (обрезаем пробелы)
                // Бэкенд автоматически свяжет комментарий с видео и текущим авторизованным пользователем
            }, {
                headers: {
                    'Authorization': `Bearer ${localStorage.getItem('access_token')}` // <-- Включаем JWT токен
                }
            });

            // При успехе: добавляем новый комментарий в список и очищаем поле ввода
            // Предполагается, что бэкенд возвращает созданный объект комментария (включая id, автора и т.д.)
            // Добавляем новый комментарий в начало списка для лучшего UX
            setComments([response.data, ...comments]); // Добавляем в начало массива комментариев
            setNewCommentText(''); // Очищаем поле ввода

        } catch (err) {
            console.error("Ошибка отправки комментария:", err.response || err);
            let errorMessage = 'Не удалось отправить комментарий.';
            // Обработка специфических ошибок с бэкенда (например, валидация или 401)
            if (err.response) {
                 if (err.response.status === 401 || err.response.status === 403) {
                     errorMessage = 'Вы не авторизованы или ваш токен истек. Пожалуйста, войдите снова.';
                     // Опционально: удалить токены и перенаправить на логин
                     // localStorage.removeItem('access_token');
                     // localStorage.removeItem('refresh_token');
                     // if (navigate) navigate('/login');
                 } else if (err.response.data && err.response.data.text) {
                     // Ошибки валидации по полю 'text' от бэкенда
                     errorMessage = `Ошибка: ${err.response.data.text.join(', ')}`;
                 } else if (err.response.data) {
                      errorMessage = `Ошибка сервера: ${JSON.stringify(err.response.data)}`;
                 } else {
                      errorMessage = `Ошибка HTTP: ${err.response.status}`;
                 }
            }
            setError(errorMessage); // Устанавливаем сообщение об ошибке
            // Ошибка не сбрасывается автоматически, чтобы пользователь мог ее прочитать
        } finally {
            setPosting(false); // Завершаем состояние отправки
        }
    };

    // Если комментарии еще загружаются, показываем индикатор
    if (loading) {
        return <div className="comments-loading">Загрузка комментариев...</div>;
    }

    // Основная разметка компонента комментариев
    return (
        // Контейнер для всего блока комментариев (гибкий столбец)
        <div className="video-comments-container"> {/* Применяем CSS класс */}

            {/* Заголовок с количеством комментариев */}
            <h3 className="comments-title">Комментарии ({comments.length})</h3> {/* Применяем CSS класс */}

            {/* Блок для отображения списка комментариев (с прокруткой) */}
            <div className="comments-list"> {/* Применяем CSS класс */}
                
                {/* Сообщение, если комментариев нет */}
                {comments.length === 0 && !loading && !error && (
                    <p className="no-comments">Комментариев пока нет.</p> // Применяем CSS класс
                )}

                {/* Отображение каждого комментария */}
                {comments.map(comment => (
                    <div key={comment.id} className="comment-item"> {/* Применяем CSS класс */}
                        {/* Используем comment.author напрямую для отображения имени пользователя */}
                        <strong className="comment-author">{comment.author || 'Аноним'}:</strong> {comment.text} {/* Применяем CSS класс */}
                        {/* Дата и время комментария */}
                        <div className="comment-timestamp"> {/* Применяем CSS класс */}
                            {new Date(comment.created_at).toLocaleString()} {/* Предполагается поле 'created_at' */}
                        </div>
                    </div>
                ))}

                 {/* Отображаем ошибку загрузки списка, если она была и комментариев нет */}
                 {error && !comments.length && <div className="comments-error-list">{error}</div>} {/* Применяем CSS класс */}
            </div>

            {/* Форма для добавления нового комментария (отображается только если пользователь авторизован) */}
            {isLoggedIn ? (
                <form onSubmit={handlePostComment} className="comment-form"> {/* Применяем CSS класс */}
                    {/* Отображаем ошибку отправки комментария прямо над формой */}
                    {error && !posting && <div className="comment-post-error">{error}</div>} {/* Применяем CSS класс */}

                    {/* Поле ввода текста комментария */}
                    <textarea
                        className="comment-textarea" // Применяем CSS класс
                        placeholder="Оставьте комментарий..."
                        value={newCommentText}
                        onChange={(e) => setNewCommentText(e.target.value)}
                        required
                        rows="3" // Высота поля ввода
                        disabled={posting} // Отключаем поле во время отправки
                    />
                    {/* Кнопка отправки */}
                    <button
                        type="submit"
                        className="comment-button" // Применяем CSS класс
                        disabled={posting || !newCommentText.trim()} // Отключаем кнопку, если идет отправка или поле пустое
                    >
                        {posting ? 'Отправка...' : 'Отправить'}
                    </button>
                </form>
            ) : (
                //{/* Сообщение для неавторизованных пользователей */}
                <div className="login-prompt"> {/* Применяем CSS класс */}
                    <p>Войдите, чтобы оставить комментарий.</p>
                    {/* Опционально: Ссылка на страницу входа */}
                    {/* Если используете Link из react-router-dom */}
                    {/* <Link to="/login" className="login-link">Войти</Link> */} {/* Применяем CSS класс */}
                </div>
            )}
        </div>
    );
};

export default VideoComments;
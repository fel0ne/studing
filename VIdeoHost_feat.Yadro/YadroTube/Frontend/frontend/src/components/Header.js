// src/components/Header.js
import React from 'react';
import { Link, useNavigate } from 'react-router-dom'; // <-- Импортируем useNavigate
import logo from './logo.png'; // <-- Импортируем файл логотипа (убедитесь, что имя файла правильное)

const Header = () => {
  const navigate = useNavigate(); // <-- Инициализируем хук useNavigate

  // Функция для обработки выхода из аккаунта
  const handleLogout = () => {
    // Удаляем access_token и refresh_token из localStorage
    localStorage.removeItem('access_token');
    localStorage.removeItem('refresh_token'); // Если вы используете refresh token

    // Перенаправляем пользователя на главную страницу (или на страницу входа)
    navigate('/'); // Можно также navigate('/login');
    // Важно: Простое удаление токенов и перенаправление - это стандартный
    // способ выхода для JWT. Если ваш бэкенд требует отправки запроса для
    // аннулирования токена на сервере, вам нужно добавить сюда axios.post('/api/logout/', ...).
  };

  // Проверяем, авторизован ли пользователь (наличие access_token в localStorage)
  const isLoggedIn = localStorage.getItem('access_token');

  return (
    <header
      style={{
        backgroundColor: '#343a40', // Темно-серый фон
        padding: '15px 20px',      // Отступы сверху/снизу и по бокам
        color: 'white',            // Цвет текста по умолчанию
        position: 'fixed',         // Фиксируем шапку в верхней части экрана
        width: '100%',             // Растягиваем на всю ширину
        top: '0',                  // Прижимаем к верху
        zIndex: '1000',            // Устанавливаем высокий z-index
        boxShadow: '0 2px 4px rgba(0,0,0,0.2)', // Тень
        display: 'flex', // Используем flexbox для расположения логотипа и навигации
        justifyContent: 'space-between', // Распределяем пространство между логотипом и навигацией
        alignItems: 'center', // Выравниваем по центру по вертикали
      }}
    >
        {/* --- Блок с логотипом (слева) --- */}
        <div style={{ display: 'flex', alignItems: 'center' }}>
            {/* Логотип как ссылка на главную */}
            <Link to="/" style={{ textDecoration: 'none' }}>
                <img
                    src={logo} // Источник изображения - импортированный файл
                    alt="Логотип" // Альтернативный текст для доступности
                    style={{ height: '30px', marginRight: '15px' }} // Размер и отступ справа от логотипа
                />
            </Link>
            {/* Можно добавить название сайта рядом с логотипом, если нужно */}
            {/* <span style={{ color: 'white', fontSize: '1.2rem', fontWeight: 'bold' }}>Название Сайта</span> */}
        </div>
        {/* --- Конец блока с логотипом --- */}

      {/* --- Блок навигации (справа) --- */}
      <nav
        style={{
          display: 'flex',
          alignItems: 'center',
          gap: '25px',             // Расстояние между элементами навигации
            // Убрали maxWidth и margin: '0 auto' из nav, так как header теперь flex-контейнер
        }}
      >
        {/* Ссылка на главную (теперь может быть продублирована, если логотип тоже ссылка) */}
        {/* Если логотип является ссылкой на главную, эту текстовую ссылку можно убрать */}
        <Link
          to="/"
          style={linkStyle} // Используем общий стиль для ссылок
          onMouseOver={(e) => e.target.style.color = '#007bff'} // Эффект наведения
          onMouseOut={(e) => e.target.style.color = 'white'}
        >
          Главная
        </Link>

        {/* Условный рендеринг: показываем разные ссылки в зависимости от авторизации */}
        {isLoggedIn ? (
          // --- Если пользователь авторизован (токен найден) ---
          <> {/* Используем Fragment для группировки нескольких элементов без добавления лишнего div */}
            {/* Ссылка на Мой аккаунт */}
            <Link
              to="/account"
              style={linkStyle}
              onMouseOver={(e) => e.target.style.color = '#007bff'}
              onMouseOut={(e) => e.target.style.color = 'white'}
            >
              Мой аккаунт
            </Link>
            {/* Кнопка Выход */}
            {/* Используем button с onClick для выполнения действия, стилизуем как ссылку */}
            <button
              onClick={handleLogout} // При клике вызываем функцию handleLogout
              style={logoutButtonStyle} // Используем стиль, который делает кнопку похожей на ссылку
              onMouseOver={(e) => e.target.style.color = '#dc3545'} // Эффект наведения (можно сделать другим цветом)
              onMouseOut={(e) => e.target.style.color = 'white'}
            >
              Выход
            </button>
          </>
        ) : (
          // --- Если пользователь не авторизован (токен не найден) ---
          <> {/* Также используем Fragment, хотя здесь всего один элемент */}
             {/* Ссылка на Вход */}
            <Link
              to="/login"
              style={linkStyle}
              onMouseOver={(e) => e.target.style.color = '#007bff'}
              onMouseOut={(e) => e.target.style.color = 'white'}
            >
              Вход
            </Link>
             {/* Опционально: Ссылка на Регистрацию, если она отдельным маршрутом */}
             {/* <Link to="/register" style={linkStyle}>Регистрация</Link> */}
          </>
        )}
      </nav>
        {/* --- Конец блока навигации --- */}
    </header>
  );
};

// --- Стили для ссылок и кнопки выхода (делаем кнопку похожей на ссылку) ---
const linkStyle = {
  color: 'white',            // Белый цвет текста
  textDecoration: 'none',    // Убираем подчеркивание
  fontSize: '16px',
  fontWeight: '600',
  transition: 'color 0.3s ease', // Плавный переход цвета при наведении
  // Примечание: Прямые псевдоклассы :hover в inline стилях не работают.
  // Используем onMouseOver/onMouseOut как простой пример.
};

const logoutButtonStyle = {
    ...linkStyle, // Наследуем стили ссылки
    backgroundColor: 'transparent', // Прозрачный фон кнопки
    border: 'none', // Убираем рамку кнопки
    cursor: 'pointer', // Курсор в виде руки при наведении
    padding: 0, // Убираем стандартные отступы кнопки
    font: 'inherit', // Наследуем настройки шрифта от родителя
    // Здесь можно добавить специфичные стили для кнопки "Выход",
    // например, другой цвет при наведении.
};
// --- Конец стилей ---


export default Header;

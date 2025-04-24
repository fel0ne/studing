import axios from 'axios';
import { useNavigate } from 'react-router-dom';
import React, { useState, useEffect } from 'react'; // <-- Добавили useEffect
import Header from '../components/Header'; // Если Header нужен на этой странице

const Login = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [username, setUsername] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');
  const [isRegistering, setIsRegistering] = useState(false);
  const [error, setError] = useState('');
  const navigate = useNavigate();

  // --- БЛОК useEffect для перенаправления авторизованных пользователей ---
  // Этот хук срабатывает при монтировании компонента
  useEffect(() => {
    // Проверяем, есть ли токен в localStorage
    if (localStorage.getItem('access_token')) {
      // Если токен есть (пользователь уже авторизован), перенаправляем его на главную страницу
      navigate('/');
    }
  }, [navigate]); // Зависимость от navigate

  // --- Улучшенная обработка ошибок от бэкенда ---
  const handleError = (err) => {
    let errorMessage = 'Произошла ошибка';
    if (err.response && err.response.data) {
        if (err.response.data.detail) {
            errorMessage = err.response.data.detail;
        } else if (typeof err.response.data === 'object') {
             // Попробуем обработать ошибки валидации DRF (например, {"username": ["..."]})
             errorMessage = Object.entries(err.response.data)
                 .map(([key, value]) => {
                     // Опционально: перевести стандартные имена полей из DRF
                     const fieldName = {
                         username: 'Имя пользователя',
                         email: 'Email',
                         password: 'Пароль',
                         password2: 'Подтверждение пароля',
                         non_field_errors: 'Ошибка' // Для ошибок, не связанных с конкретным полем
                     }[key] || key; // Если имя поля не найдено в словаре, используем его как есть
                     return `${fieldName}: ${Array.isArray(value) ? value.join(', ') : value}`;
                 })
                 .join('; '); // Соединяем несколько ошибок точкой с запятой
        } else {
            errorMessage = JSON.stringify(err.response.data); // На всякий случай, если формат ошибки неизвестен
        }
    }
    setError(errorMessage);
    setTimeout(() => setError(''), 7000); // Показываем ошибку 7 секунд
  };
  // --- Конец обработки ошибок ---


  const handleRegister = async (e) => {
    e.preventDefault();
    setError(''); // Сбросить предыдущие ошибки перед новым действием

    if (password !== confirmPassword) {
      setError('Пароли не совпадают');
      setTimeout(() => setError(''), 7000); // Показываем ошибку 7 секунд
      return;
    }

    // Проверка email не нужна вручную, т.к. input type="email" с required и бэкенд выполнят валидацию

    try {
      // Отправляем запрос на регистрацию с необходимыми полями
      await axios.post('http://localhost:8000/api/auth/register/', {
        username,
        email,
        password,
        password2: confirmPassword // Передаем confirmPassword как password2
      });

      alert('Регистрация успешна! Теперь вы можете войти.');
      setIsRegistering(false); // Переключаем на форму входа после успешной регистрации
      // Сбрасываем поля после успешной регистрации для чистоты или для удобства входа
      setError(''); // Убираем ошибку
      setEmail(''); // Очищаем email
      setConfirmPassword(''); // Очищаем подтверждение пароля
      // username и password можно оставить заполненными для удобства автоматического входа
    } catch (err) {
      // Обрабатываем ошибки, полученные от бэкенда
      handleError(err);
    }
  };


  const handleLogin = async (e) => {
    e.preventDefault();
    setError(''); // Сбросить предыдущие ошибки перед новым действием

    try {
      // Отправляем запрос на получение токена
      // Убедитесь, что ваш бэкенд принимает 'username' (или 'email') и 'password'
      const res = await axios.post('http://localhost:8000/api/token/', { username, password }); // Обычно для токена используется username
      localStorage.setItem('access_token', res.data.access); // Сохраняем access токен
      if (res.data.refresh) {
          localStorage.setItem('refresh_token', res.data.refresh); // Опционально: сохраняем refresh токен, если бэкенд его выдает
      }
      navigate('/'); // Перенаправляем на главную после успешного входа
    } catch (err) {
      // Обрабатываем ошибки, полученные от бэкенда (например, неверные учетные данные)
      handleError(err);
    }
  };

  return (
    // --- ОБЩИЙ КОНТЕЙНЕР ДЛЯ СТРАНИЦЫ (Центрирование) ---
    <div style={{
        display: 'flex', // Используем flexbox
        flexDirection: 'column', // Элементы внутри располагаются по вертикали
        alignItems: 'center', // Выравниваем элементы по центру по горизонтали
        justifyContent: 'center', // Выравниваем элементы по центру по вертикали
        minHeight: '100vh', // Занимаем всю высоту окна браузера
        backgroundColor: '#e9ecef', // Легкий серый фон для всей страницы
        padding: '20px', // Небольшие отступы по краям
        boxSizing: 'border-box' // Включаем padding в размер элемента
    }}>
        {/* Header здесь, возможно, не нужен, если это отдельная страница /login без общей навигации */}
         <Header /> 

        {/* --- БЛОК ФОРМЫ (Стилизованный контейнер) --- */}
        <div style={{
            backgroundColor: '#ffffff', // Белый фон для самого блока формы
            padding: '40px', // Внутренние отступы блока
            borderRadius: '8px', // Скругленные углы
            boxShadow: '0 4px 15px rgba(0,0,0,0.1)', // Красивая тень
            maxWidth: '400px', // Максимальная ширина блока
            width: '100%', // Блок занимает 100% доступной ширины до maxWidth
            textAlign: 'center', // Центрируем текст внутри (например, заголовки)
            marginTop: '20px', // Отступ сверху (может быть нужен, если есть шапка)
            marginBottom: '20px' // Отступ снизу
        }}>
            {/* Заголовок формы */}
            <h2 style={{ marginBottom: '30px', color: '#333' }}>
                {isRegistering ? 'Регистрация' : 'Вход'}
            </h2>

            {/* Сообщение об ошибке */}
            {error && (
                <div
                   className="error-message" // Оставляем класс, если он используется в других стилях
                   style={{ // Добавляем inline стили
                     padding: '12px',
                     backgroundColor: '#f8d7da', // Светло-красный фон
                     color: '#721c24', // Темно-красный текст
                     border: '1px solid #f5c6cb', // Красная рамка
                     borderRadius: '5px',
                     marginBottom: '20px', // Отступ снизу от формы
                     fontSize: '15px',
                     textAlign: 'left', // Выравнивание текста ошибки по левому краю
                     wordBreak: 'break-word' // Перенос длинных слов
                   }}
                >
                  {error}
                </div>
            )}

            {/* --- САМА ФОРМА --- */}
            <form
               onSubmit={isRegistering ? handleRegister : handleLogin}
               style={{ // Стилизация формы как flex-контейнера
                 display: 'flex',
                 flexDirection: 'column', // Поля располагаются вертикально
                 gap: '15px' // Расстояние между полями и кнопками внутри формы
               }}
            >
                {/* Поле Имя пользователя (username) */}
                {/* Показываем username всегда, т.к. он нужен для входа */}
                <input
                    type="text"
                    placeholder="Имя пользователя"
                    value={username}
                    onChange={(e) => setUsername(e.target.value)}
                    required // Поле обязательное
                    style={{ // Стилизация поля ввода
                       padding: '12px', // Внутренние отступы
                       borderRadius: '5px', // Скругленные углы
                       border: '1px solid #ced4da', // Цвет рамки
                       fontSize: '16px', // Размер шрифта
                       width: '100%', // Растягиваем на всю ширину контейнера
                       boxSizing: 'border-box', // Учитываем padding и border в ширине
                    }}
                />

                {/* Поле Email (только для регистрации) */}
                {isRegistering && (
                   <input
                     type="email"
                     placeholder="Email"
                     value={email}
                     onChange={(e) => setEmail(e.target.value)}
                     required={isRegistering} // required только когда форма - регистрация
                     style={{
                        padding: '12px',
                        borderRadius: '5px',
                        border: '1px solid #ced4da',
                        fontSize: '16px',
                        width: '100%',
                        boxSizing: 'border-box',
                     }}
                   />
                )}

                {/* Поле Пароль (всегда нужно) */}
                <input
                    type="password"
                    placeholder="Пароль"
                    value={password}
                    onChange={(e) => setPassword(e.target.value)}
                    required // Поле обязательное
                    style={{
                       padding: '12px',
                       borderRadius: '5px',
                       border: '1px solid #ced4da',
                       fontSize: '16px',
                       width: '100%',
                       boxSizing: 'border-box',
                    }}
                />

                {/* Поле Повторите пароль (только для регистрации) */}
                {isRegistering && (
                    <input
                        type="password"
                        placeholder="Повторите пароль"
                        value={confirmPassword}
                        onChange={(e) => setConfirmPassword(e.target.value)}
                        required={isRegistering} // required только когда форма - регистрация
                        style={{
                           padding: '12px',
                           borderRadius: '5px',
                           border: '1px solid #ced4da',
                           fontSize: '16px',
                           width: '100%',
                           boxSizing: 'border-box',
                        }}
                    />
                )}

                {/* Кнопка отправки формы */}
                <button
                   type="submit"
                   style={{
                      padding: '12px 20px', // Внутренние отступы
                      backgroundColor: '#007bff', // Синий фон
                      color: 'white', // Белый текст
                      border: 'none', // Убираем рамку
                      borderRadius: '5px', // Скругленные углы
                      cursor: 'pointer', // Курсор в виде руки при наведении
                      fontSize: '18px', // Размер шрифта
                      fontWeight: 'bold', // Жирный текст
                      marginTop: '20px', // Отступ сверху от последнего поля/кнопки
                      transition: 'background-color 0.2s ease', // Плавное изменение цвета фона
                   }}
                   // Простой hover эффект для примера с inline стилями
                   onMouseOver={(e) => e.target.style.backgroundColor = '#0056b3'}
                   onMouseOut={(e) => e.target.style.backgroundColor = '#007bff'}
                >
                    {isRegistering ? 'Зарегистрироваться' : 'Войти'}
                </button>
            </form>

            {/* Кнопка переключения между формами */}
            <button
                className="toggle-button" // Оставляем класс
                onClick={() => {
                    setIsRegistering(!isRegistering);
                    // Сбрасываем ошибки и поля при переключении для чистоты
                    setError('');
                    setEmail('');
                    setPassword('');
                    setUsername('');
                    setConfirmPassword('');
                }}
                style={{ // Стилизация кнопки как ссылки
                    marginTop: '25px', // Отступ сверху
                    backgroundColor: 'transparent', // Прозрачный фон
                    color: '#007bff', // Синий цвет текста
                    border: 'none', // Убираем рамку
                    cursor: 'pointer', // Курсор в виде руки
                    fontSize: '15px',
                    textDecoration: 'underline', // Подчеркивание
                }}
            >
                {isRegistering ? 'Уже есть аккаунт? Войти' : 'Нет аккаунта? Зарегистрироваться'}
            </button>
        </div>
     </div>
  );
}

export default Login;
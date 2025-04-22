import axios from 'axios';
import { useNavigate } from 'react-router-dom';
import React, { useState } from 'react';

const Login = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [username, setUsername] = useState(''); 
  const [confirmPassword, setConfirmPassword] = useState('');
  const [isRegistering, setIsRegistering] = useState(false);
  const [error, setError] = useState('');
  const navigate = useNavigate();

  const handleError = (err) => {
    setError(err.response?.data?.detail || 'Произошла ошибка');
    setTimeout(() => setError(''), 3000);
  };

  const handleRegister = async (e) => {
    e.preventDefault();

    if (password !== confirmPassword) {
      setError('Пароли не совпадают');
      setTimeout(() => setError(''), 3000);
      return;
    }

    // Проверка email остается
    if (!email && isRegistering) { // Добавим проверку isRegistering на всякий случай
        setError('Email обязателен для регистрации');
        setTimeout(() => setError(''), 3000);
        return;
    }

    try {
      // --- ИЗМЕНЕНИЕ ЗДЕСЬ ---
      // Добавляем поле password2 и передаем в него значение из confirmPassword
      await axios.post('http://localhost:8000/api/auth/register/', {
        username,
        email,
        password,
        password2: confirmPassword // <--- Вот это изменение
      });
      // --- КОНЕЦ ИЗМЕНЕНИЯ ---

      alert('Регистрация успешна! Теперь вы можете войти.');
      setIsRegistering(false); // Переключить на форму входа
       // Сбросить поля после успешной регистрации
       setError('');
       setEmail('');
       setPassword('');
       setUsername('');
       setConfirmPassword('');
    } catch (err) {
      // handleError теперь сможет показать и другие ошибки валидации от DRF,
      // например, если username уже занят
      handleError(err);
    }
  };

  const handleLogin = async (e) => {
    e.preventDefault();
    try {
      const res = await axios.post('http://localhost:8000/api/token/', { username, password }); // Используйте username вместо email
      localStorage.setItem('access_token', res.data.access);
      navigate('/');
    } catch (err) {
      handleError(err);
    }
  };

  return (
    <div className="auth-form">
      <h2>{isRegistering ? 'Регистрация' : 'Вход'}</h2>

      {error && <div className="error-message">{error}</div>}

      <form onSubmit={isRegistering ? handleRegister : handleLogin}>
        {/* Поле username теперь есть и для регистрации */}
        {(isRegistering || !isRegistering) && ( // Показываем всегда ИЛИ только для входа, в зависимости от вашей логики бэкенда при входе
            <input
              type="text"
              placeholder="Имя пользователя"
              value={username}
              onChange={(e) => setUsername(e.target.value)}
              required // Имя пользователя обычно требуется и при регистрации
            />
        )}

        {/* Email всегда нужен */}
        <input
          type="email"
          placeholder="Email"
          value={email}
          onChange={(e) => setEmail(e.target.value)}
          required
        />

        {/* Пароль всегда нужен */}
        <input
          type="password"
          placeholder="Пароль"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          required
        />

        {/* Подтверждение пароля только для регистрации */}
        {isRegistering && (
          <input
            type="password"
            placeholder="Повторите пароль"
            value={confirmPassword}
            onChange={(e) => setConfirmPassword(e.target.value)}
            required
          />
        )}

        <button type="submit">
          {isRegistering ? 'Зарегистрироваться' : 'Войти'}
        </button>
      </form>

      <button
        className="toggle-button"
        onClick={() => {
            setIsRegistering(!isRegistering);
            // Сбросить ошибки и поля при переключении для лучшего UX
            setError('');
            setEmail('');
            setPassword('');
            setUsername('');
            setConfirmPassword('');
        }}
      >
        {isRegistering ? 'Уже есть аккаунт? Войти' : 'Нет аккаунта? Зарегистрироваться'}
      </button>
    </div>
  );
}

export default Login;
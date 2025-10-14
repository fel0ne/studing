from http.server import HTTPServer, BaseHTTPRequestHandler
from datetime import datetime
import urllib.parse

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    
    def do_GET(self):
        """Обработка GET-запросов"""
        current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        print(f"{current_time} - GET-запрос: {self.path} от {self.client_address[0]}")
        
        # Маршрутизация
        if self.path == '/':
            self.send_main_page()
        elif self.path == '/about':
            self.send_about_page()
        elif self.path == '/services':
            self.send_services_page()
        elif self.path == '/contact':
            self.send_contact_page()
        elif self.path == '/form':
            self.send_form_page()
        else:
            self.send_error_page()
    
    def do_POST(self):
        """Обработка POST-запросов"""
        print(f"{datetime.now().strftime('%Y-%m-%d %H:%M:%S')} - POST-запрос: {self.path} от {self.client_address[0]}")
        
        if self.path == '/submit-form':
            self.handle_form_submission()
        else:
            self.send_error(404, "Страница не найдена")

    def handle_form_submission(self):
        """Обрабатывает отправку формы"""
        try:
            # Получаем длину данных
            content_length = int(self.headers['Content-Length'])
            
            # Читаем данные формы
            post_data = self.rfile.read(content_length).decode('utf-8')
            
            # Парсим данные формы (они приходят в формате: name=John&email=test@mail.ru)
            parsed_data = urllib.parse.parse_qs(post_data)
            
            # Валидация обязательных полей
            errors = []
            
            name = parsed_data.get('name', [''])[0].strip()
            email = parsed_data.get('email', [''])[0].strip()
            subject = parsed_data.get('subject', [''])[0].strip()
            message = parsed_data.get('message', [''])[0].strip()
            
            if not name:
                errors.append("Имя является обязательным полем")
            if not email:
                errors.append("Email является обязательным полем")
            elif '@' not in email:
                errors.append("Email должен содержать символ @")
            
            # Если есть ошибки, показываем их
            if errors:
                self.show_form_errors(errors)
            else:
                # Все хорошо, показываем страницу успеха
                self.show_success_page(name, email, subject, message)
                
        except Exception as e:
            print(f"Ошибка при обработке формы: {e}")
            self.send_error(500, "Внутренняя ошибка сервера")

    def show_form_errors(self, errors):
        """Показывает страницу с ошибками валидации"""
        errors_html = "<br>".join([f"• {error}" for error in errors])
        
        html = f"""
        <!DOCTYPE html>
        <html lang="ru">
        <head>
            <meta charset="UTF-8">
            <title>Ошибки в форме</title>
            <style>
                body {{ font-family: Arial, sans-serif; margin: 40px; }}
                nav {{ background: #f0f0f0; padding: 10px; margin-bottom: 20px; }}
                nav a {{ margin: 0 10px; text-decoration: none; color: #333; }}
                nav a:hover {{ color: #007bff; }}
                .error {{ color: red; background: #ffe6e6; padding: 15px; margin: 20px 0; border-radius: 5px; }}
                .form-group {{ margin-bottom: 15px; }}
                label {{ display: block; margin-bottom: 5px; font-weight: bold; }}
                input, textarea {{ 
                    width: 100%; 
                    max-width: 500px;
                    padding: 8px; 
                    border: 1px solid #ddd; 
                    border-radius: 4px; 
                    box-sizing: border-box;
                }}
                .required {{ color: red; }}
                button {{ 
                    background: #007bff; 
                    color: white; 
                    padding: 10px 20px; 
                    border: none; 
                    border-radius: 4px; 
                    cursor: pointer; 
                }}
                button:hover {{ background: #0056b3; }}
            </style>
        </head>
        <body>
            <nav>
                <a href="/">Главная</a> | 
                <a href="/about">О нас</a> | 
                <a href="/services">Услуги</a> | 
                <a href="/contact">Контакты</a> |
                <a href="/form">Обратная связь</a>
            </nav>
            
            <h1>Ошибки при заполнении формы</h1>
            <div class="error">
                <strong>Исправьте следующие ошибки:</strong><br>
                {errors_html}
            </div>
            
            <h2>Заполните форму еще раз:</h2>
            <form method="POST" action="/submit-form">
                <div class="form-group">
                    <label for="name">Имя <span class="required">*</span></label>
                    <input type="text" id="name" name="name" required placeholder="Введите ваше имя">
                </div>
                
                <div class="form-group">
                    <label for="email">Email <span class="required">*</span></label>
                    <input type="email" id="email" name="email" required placeholder="Введите ваш email">
                </div>
                
                <div class="form-group">
                    <label for="subject">Тема сообщения</label>
                    <input type="text" id="subject" name="subject" placeholder="Тема вашего сообщения">
                </div>
                
                <div class="form-group">
                    <label for="message">Текст сообщения</label>
                    <textarea id="message" name="message" rows="5" placeholder="Введите ваше сообщение..."></textarea>
                </div>
                
                <button type="submit">Отправить сообщение</button>
            </form>
            
            <p><a href="/">Вернуться на главную</a></p>
        </body>
        </html>
        """
        self.send_response(200)
        self.send_header('Content-type', 'text/html; charset=utf-8')
        self.end_headers()
        self.wfile.write(html.encode('utf-8'))

    def show_success_page(self, name, email, subject, message):
        """Показывает страницу успешной отправки формы"""
        html = f"""
        <!DOCTYPE html>
        <html lang="ru">
        <head>
            <meta charset="UTF-8">
            <title>Сообщение отправлено</title>
            
        </head>
        <body>
            <nav>
                <a href="/">Главная</a> | 
                <a href="/about">О нас</a> | 
                <a href="/services">Услуги</a> | 
                <a href="/contact">Контакты</a> |
                <a href="/form">Обратная связь</a>
            </nav>
            
            <h1>Сообщение успешно отправлено!</h1>
            
            <div class="success">
                <strong>Спасибо, {name}!</strong><br>
                Ваше сообщение было успешно отправлено. Мы свяжемся с вами в ближайшее время.
            </div>
            
            <div class="message-info">
                <h3>Информация о вашем сообщении:</h3>
                <p><strong>Имя:</strong> {name}</p>
                <p><strong>Email:</strong> {email}</p>
                <p><strong>Тема:</strong> {subject if subject else 'Не указана'}</p>
                <p><strong>Сообщение:</strong> {message if message else 'Не указано'}</p>
            </div>
            
            <p>
                <a href="/form">Отправить еще одно сообщение</a> | 
                <a href="/">Вернуться на главную</a>
            </p>
        </body>
        </html>
        """
        self.send_response(200)
        self.send_header('Content-type', 'text/html; charset=utf-8')
        self.end_headers()
        self.wfile.write(html.encode('utf-8'))
    
    def send_main_page(self):
        """Главная страница"""
        html = """
        <!DOCTYPE html>
        <html lang="ru">
        <head><meta charset="UTF-8"><title>Главная</title></head>
        <body>
            <nav>
                <a href="/">Главная</a> | 
                <a href="/about">О нас</a> | 
                <a href="/services">Услуги</a> | 
                <a href="/contact">Контакты</a> |
                <a href="/form">Обратная связь</a>
            </nav>
            <h1>Главная страница</h1>
            <p>Добро пожаловать на наш сайт!</p>
        </body>
        </html>
        """
        self.send_html(html)
    
    def send_about_page(self):
        """Страница О нас"""
        html = """
        <!DOCTYPE html>
        <html lang="ru">
        <head><meta charset="UTF-8"><title>О нас</title></head>
        <body>
            <nav>
                <a href="/">Главная</a> | 
                <a href="/about">О нас</a> | 
                <a href="/services">Услуги</a> | 
                <a href="/contact">Контакты</a> |
                <a href="/form">Обратная связь</a>
            </nav>
            <h1>О нашем проекте</h1>
            <p>Это учебный проект по созданию HTTP-сервера на Python.</p>
        </body>
        </html>
        """
        self.send_html(html)
    
    def send_services_page(self):
        """Страница Услуги"""
        html = """
        <!DOCTYPE html>
        <html lang="ru">
        <head><meta charset="UTF-8"><title>Услуги</title></head>
        <body>
            <nav>
                <a href="/">Главная</a> | 
                <a href="/about">О нас</a> | 
                <a href="/services">Услуги</a> | 
                <a href="/contact">Контакты</a> |
                <a href="/form">Обратная связь</a>
            </nav>
            <h1>Наши услуги</h1>
            <ul>
                <li>Веб-разработка</li>
                <li>Программирование на Python</li>
                <li>Создание API</li>
            </ul>
        </body>
        </html>
        """
        self.send_html(html)
    
    def send_contact_page(self):
        """Контактная страница"""
        html = """
        <!DOCTYPE html>
        <html lang="ru">
        <head><meta charset="UTF-8"><title>Контакты</title></head>
        <body>
            <nav>
                <a href="/">Главная</a> | 
                <a href="/about">О нас</a> | 
                <a href="/services">Услуги</a> | 
                <a href="/contact">Контакты</a> |
                <a href="/form">Обратная связь</a>
            </nav>
            <h1>Контакты</h1>
            <p>Email: example@mail.ru</p>
            <p>Телефон: +7 (123) 456-78-90</p>
        </body>
        </html>
        """
        self.send_html(html)
    
    def send_form_page(self):
        """Страница с формой"""
        html = """
        <!DOCTYPE html>
        <html lang="ru">
        <head><meta charset="UTF-8"><title>Обратная связь</title></head>
        <body>
            <nav>
                <a href="/">Главная</a> | 
                <a href="/about">О нас</a> | 
                <a href="/services">Услуги</a> | 
                <a href="/contact">Контакты</a> |
                <a href="/form">Обратная связь</a>
            </nav>
            <h1>Форма обратной связи</h1>
            <form method="POST" action="/submit-form">
                <p>Имя: <input type="text" name="name" required></p>
                <p>Email: <input type="email" name="email" required></p>
                <p>Тема: <input type="text" name="subject"></p>
                <p>Сообщение: <textarea name="message"></textarea></p>
                <button type="submit">Отправить</button>
            </form>
        </body>
        </html>
        """
        self.send_html(html)
    
    def send_error_page(self):
        """Страница 404"""
        html = """
        <!DOCTYPE html>
        <html lang="ru">
        <head><meta charset="UTF-8"><title>404</title></head>
        <body>
            <nav>
                <a href="/">Главная</a> | 
                <a href="/about">О нас</a> | 
                <a href="/services">Услуги</a> | 
                <a href="/contact">Контакты</a> |
                <a href="/form">Обратная связь</a>
            </nav>
            <h1>404 - Страница не найдена</h1>
            <p>Запрошенная страница не существует.</p>
        </body>
        </html>
        """
        self.send_response(404)
        self.send_header('Content-type', 'text/html; charset=utf-8')
        self.end_headers()
        self.wfile.write(html.encode('utf-8'))
    
    def send_html(self, html_content):
        """Универсальный метод отправки HTML"""
        self.send_response(200)
        self.send_header('Content-type', 'text/html; charset=utf-8')
        self.end_headers()
        self.wfile.write(html_content.encode('utf-8'))

def run_server(port=8000):
    server_address = ('', port)
    httpd = HTTPServer(server_address, SimpleHTTPRequestHandler)
    print(f"Сервер запущен на http://localhost:{port}")
    print("Для остановки сервера нажми Ctrl+C")
    
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nСервер остановлен")

if __name__ == '__main__':
    run_server()
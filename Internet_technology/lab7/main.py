import asyncio
import aiohttp
import aiohttp.web
from bs4 import BeautifulSoup
import random
import json
from typing import List, Dict, Any
import logging

# Настройка логирования для отображения процесса работы
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


class AsyncBookScraper:
    """Модуль 1: Асинхронный скрапер книг с сайта books.toscrape.com"""
    
    BASE_URL = "http://books.toscrape.com/catalogue/page-{}.html"
    
    def __init__(self):
        self.books = []
    
    def _parse_book(self, html: str) -> List[Dict[str, Any]]:
        """
        Парсинг HTML страницы с книгами и извлечение информации о каждой книге
        
        Args:
            html: HTML содержимое страницы
            
        Returns:
            Список словарей с информацией о книгах
        """
        soup = BeautifulSoup(html, 'html.parser')
        books_data = []
        
        # Находим все контейнеры с книгами на странице
        book_containers = soup.select('article.product_pod')
        
        for book in book_containers:
            try:
                # Извлекаем название книги
                title = book.h3.a['title']
                
                # Извлекаем цену и преобразуем в float
                price_text = book.select_one('p.price_color').text
                price = float(price_text.replace('£', ''))
                
                # Извлекаем информацию о наличии на складе
                availability = book.select_one('p.instock.availability')
                in_stock = 'In stock' in availability.text.strip()
                
                # Извлекаем рейтинг и преобразуем в число от 1 до 5
                rating_class = book.select_one('p.star-rating')['class'][1]
                rating_map = {'One': 1, 'Two': 2, 'Three': 3, 'Four': 4, 'Five': 5}
                rating = rating_map.get(rating_class, 0)
                
                books_data.append({
                    'title': title,
                    'price': price,
                    'in_stock': in_stock,
                    'rating': rating
                })
                
            except (AttributeError, KeyError, ValueError) as e:
                logger.warning(f"Ошибка при парсинге книги: {e}")
                continue
        
        return books_data
    
    async def fetch_page(self, session: aiohttp.ClientSession, page_num: int) -> List[Dict[str, Any]]:
        """
        Асинхронная загрузка и парсинг одной страницы
        
        Args:
            session: aiohttp сессия
            page_num: номер страницы для загрузки
            
        Returns:
            Список книг со страницы
        """
        url = self.BASE_URL.format(page_num)
        
        try:
            logger.info(f"Начинаю загрузку страницы {page_num}")
            async with session.get(url, timeout=aiohttp.ClientTimeout(total=10)) as response:
                # Проверяем успешность запроса
                if response.status == 200:
                    html = await response.text()
                    books = self._parse_book(html)
                    logger.info(f"Загружено {len(books)} книг со страницы {page_num}")
                    return books
                else:
                    logger.error(f"Ошибка HTTP {response.status} для страницы {page_num}")
                    return []
                    
        except asyncio.TimeoutError:
            logger.error(f"Таймаут при загрузке страницы {page_num}")
            return []
        except aiohttp.ClientError as e:
            logger.error(f"Сетевая ошибка при загрузке страницы {page_num}: {e}")
            return []
        except Exception as e:
            logger.error(f"Неожиданная ошибка при загрузке страницы {page_num}: {e}")
            return []
    
    async def scrape_books(self, num_pages: int = 5) -> List[Dict[str, Any]]:
        """
        Конкурентная загрузка нескольких страниц
        
        Args:
            num_pages: количество страниц для скрапинга
            
        Returns:
            Объединенный список всех книг
        """
        logger.info(f"Начинаю конкурентную загрузку {num_pages} страниц")
        
        # cоздаем сессию aiohttp для повторного использования соединений
        async with aiohttp.ClientSession() as session:
            # cоздаем задачи для конкурентного выполнения
            tasks = [self.fetch_page(session, i) for i in range(1, num_pages + 1)]
            
            # выполняем все задачи параллельно
            results = await asyncio.gather(*tasks, return_exceptions=True)
            
            # обрабатываем результаты
            all_books = []
            for i, result in enumerate(results, 1):
                if isinstance(result, Exception):
                    logger.error(f"Ошибка в задаче для страницы {i}: {result}")
                else:
                    all_books.extend(result)
            
            self.books = all_books
            logger.info(f"Всего загружено {len(all_books)} книг")
            return all_books


class APIClient:
    """Модуль 2: Клиент для работы с внешним API пользователей"""
    
    USERS_API_URL = "https://jsonplaceholder.typicode.com/users"
    
    async def fetch_users(self) -> List[Dict[str, str]]:
        """
        Асинхронная загрузка пользователей из внешнего API
        
        Returns:
            Список пользователей с именами и email
        """
        logger.info("Начинаю загрузку пользователей из API")
        
        try:
            async with aiohttp.ClientSession() as session:
                async with session.get(self.USERS_API_URL, timeout=aiohttp.ClientTimeout(total=10)) as response:
                    
                    if response.status == 200:
                        users_data = await response.json()
                        
                        # извлекаем только нужные поля: имя и email
                        users = [{"name": user["name"], "email": user["email"]} 
                                for user in users_data]
                        
                        logger.info(f"Загружено {len(users)} пользователей")
                        return users
                    else:
                        logger.error(f"Ошибка API: HTTP {response.status}")
                        return []
                        
        except asyncio.TimeoutError:
            logger.error("Таймаут при загрузке пользователей")
            return []
        except aiohttp.ClientError as e:
            logger.error(f"Сетевая ошибка при загрузке пользователей: {e}")
            return []
        except (KeyError, TypeError) as e:
            logger.error(f"Ошибка парсинга JSON ответа: {e}")
            return []
        except Exception as e:
            logger.error(f"Неожиданная ошибка при загрузке пользователей: {e}")
            return []


class DataAggregator:
    """Модуль 3: Агрегатор данных и веб-сервер"""
    
    def __init__(self, scraper: AsyncBookScraper, api_client: APIClient):
        self.scraper = scraper
        self.api_client = api_client
        self.aggregated_data = []
    
    async def aggregate_data(self) -> List[Dict[str, Any]]:
        """
        Объединение данных: назначение случайных пользователей книгам
        
        Returns:
            Список книг с назначенными пользователями
        """
        logger.info("Начинаю агрегацию данных")
        
        # загружаем книги и пользователей конкурентно
        books_task = self.scraper.scrape_books()
        users_task = self.api_client.fetch_users()
        
        # ожидаем завершения обеих задач
        books, users = await asyncio.gather(books_task, users_task)
        
        # если нет пользователей, создаем заглушку
        if not users:
            users = [{"name": "Default User", "email": "default@example.com"}]
        
        # Назначаем каждой книге случайного пользователя
        aggregated_books = []
        for book in books:
            # Выбираем случайного пользователя
            random_user = random.choice(users)
            
            # Создаем объединенную запись
            aggregated_book = {
                **book,
                "potential_customer": random_user
            }
            aggregated_books.append(aggregated_book)
        
        self.aggregated_data = aggregated_books
        logger.info(f"Агрегировано {len(aggregated_books)} записей")
        return aggregated_books
    
    async def analytics_handler(self, request: aiohttp.web.Request) -> aiohttp.web.Response:
        """
        Обработчик GET запроса к /analytics
        
        Args:
            request: HTTP запрос
            
        Returns:
            HTTP ответ с JSON данными
        """
        logger.info("Получен запрос к /analytics")
        
        # Если данные еще не загружены, загружаем их
        if not self.aggregated_data:
            await self.aggregate_data()
        
        # Возвращаем данные в формате JSON
        return aiohttp.web.Response(
            text=json.dumps(self.aggregated_data, indent=2, ensure_ascii=False),
            content_type='application/json'
        )


async def main():
    """Основная функция для запуска приложения"""
    logger.info("=" * 50)
    logger.info("Запуск асинхронного веб-скрапера и API-клиента")
    logger.info("=" * 50)
    
    try:
        # Создаем экземпляры классов
        scraper = AsyncBookScraper()
        api_client = APIClient()
        aggregator = DataAggregator(scraper, api_client)
        
        # Создаем и настраиваем веб-приложение
        app = aiohttp.web.Application()
        
        # Регистрируем маршрут
        app.router.add_get('/analytics', aggregator.analytics_handler)
        
        # Запускаем веб-сервер
        runner = aiohttp.web.AppRunner(app)
        await runner.setup()
        
        # Настраиваем TCP сайт на порту 8080
        site = aiohttp.web.TCPSite(runner, 'localhost', 8080)
        await site.start()
        
        logger.info("Веб-сервер запущен на http://localhost:8080")
        logger.info("Доступные эндпоинты:")
        logger.info("  GET /analytics - получить аналитику по книгам с покупателями")
        logger.info("=" * 50)
        
        # Бесконечно ждем (сервер работает в фоне)
        await asyncio.Event().wait()
        
    except KeyboardInterrupt:
        logger.info("Приложение остановлено пользователем")
    except Exception as e:
        logger.error(f"Критическая ошибка при запуске: {e}")

#чтобы легко запустить 
if __name__ == "__main__":
    # запускаем основную асинхронную функцию
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        logger.info("Приложение завершено")
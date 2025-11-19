from fastapi import FastAPI, Response, Query, Path, HTTPException, Depends
from pydantic import BaseModel, Field
from typing import List, Optional

from models import Book,User
import authh 







tags_metadata = [
    {
        "name": "books",
        "description": "Операции с книгами: получение списка, поиск, добавление, изменение, удаление",
    }
]


app = FastAPI(
    title="API Электронной библиотеки",
    description="Сервис для управления каталогом книг. Позволяет добавлять, искать, обновлять и удалять книги.",
    version="1.0.0",
    openapi_tags=tags_metadata
)

app.include_router(authh.router, prefix="/auth", tags=["auth"])

books = [
    Book(id=1, title="Мастер и Маргарита", author="Михаил Булгаков", publication_year=1967),
    Book(id=2, title="Белый Бим Чёрное ухо", author="Гавриил Троепольский", publication_year=1971)
]

@app.get("/books/", 
         tags=["books"], 
         summary="Получить список всех книг",
         description="Возвращает массив всех книг в библиотеке. Поддерживает фильтрацию по автору.",
         response_model=List[Book],
         )
async def get_books(author: Optional[str] = Query(None, description="Фильтр по автору книги", example="Булгаков")):
    """
    Получить список книг с возможностью фильтрации.
    
    - **Возвращает все книги**, если параметр author не указан
    - **Фильтрует по автору**, если параметр author указан
    - Поддерживает поиск без учета регистра
    """
    if author:
        filtered_books = []
        for book in books:
            if book.author.lower() == author.lower():
                filtered_books.append(book)
        return filtered_books
    return books

@app.get("/books/{book_id}", 
         tags=["books"], 
         summary="Получить книгу по ID",
         description="Возвращает информацию о конкретной книге по её уникальному идентификатору.",
         responses={
             200: {"description": "Книга найдена"},
             404: {"description": "Книга не найдена"}
         },
         response_model=Book)
async def get_book(book_id: int = Path(..., description="ID книги для получения", example=1)):
    """
    Получить детальную информацию о книге по ID.
    
    - **book_id**: Уникальный идентификатор книги (целое число)
    - **Возвращает объект книги**, если книга найдена
    - **Возвращает ошибку 404**, если книга с указанным ID не существует
    """
    for book in books:
        if book.id == book_id:
            return book
    raise HTTPException(status_code=404, detail="Книга не найдена")

@app.post("/books/", 
          tags=["books"], 
          summary="Добавить новую книгу",
          description="Создает новую запись о книге в библиотеке.",
          responses={
              200: {"description": "Книга успешно добавлена"},
              400: {"description": "Книга с таким ID уже существует"}
          },
          status_code=200,
          response_model=Book)
async def post_book(book_data: Book, current_user: User = Depends(authh.get_current_user)):
    """
    Добавить новую книгу в библиотеку.
    
    - **Все поля обязательны** для заполнения
    - **ID должен быть уникальным** - проверяется на дубликаты
    - **Возвращает созданную книгу** при успешном добавлении
    - **Возвращает ошибку 400** при попытке добавить книгу с существующим ID
    """
    for book in books:
        if book.id == book_data.id:
            raise HTTPException(status_code=400, detail="Книга с таким ID уже существует")
    
    new_book = Book(
        id=book_data.id,
        title=book_data.title,
        author=book_data.author,
        publication_year=book_data.publication_year
    )
    
    books.append(new_book)
    return new_book

@app.put("/books/{book_id}", 
         tags=["books"], 
         summary="Обновить информацию о книге",
         description="Обновляет информацию о существующей книге по её ID.",
         responses={
             200: {"description": "Книга успешно обновлена"},
             404: {"description": "Книга не найдена"}
         },
         response_model=Book)
async def update_book(book_id: int = Path(..., description="ID книги для обновления", example=1), 
                book_data: Book = None, current_user: User = Depends(authh.get_current_user)):
    """
    Обновить информацию о книге.
    
    - **book_id**: ID обновляемой книги
    - **Все поля книги** могут быть обновлены
    - **Возвращает обновленную книгу** при успешном обновлении
    - **Возвращает ошибку 404** если книга с указанным ID не найдена
    """
    for i in range(len(books)):
        if books[i].id == book_id:
            updated_book = Book(
                id=book_id,
                title=book_data.title,
                author=book_data.author,
                publication_year=book_data.publication_year
            )
            books[i] = updated_book
            return updated_book
    raise HTTPException(status_code=404, detail="Книга не найдена")

@app.delete("/books/{book_id}", 
            tags=["books"], 
            summary="Удалить книгу",
            description="Удаляет книгу из библиотеки по её ID.",
            responses={
                200: {"description": "Книга успешно удалена"},
                404: {"description": "Книга не найдена"}
            })
async def delete_book(book_id: int = Path(..., description="ID удаляемой книги", example=1), current_user: User = Depends(authh.get_current_user)):
    """
    Удалить книгу из библиотеки.
    
    - **book_id**: ID удаляемой книги
    - **Возвращает сообщение об успехе** при удалении
    - **Возвращает ошибку 404** если книга с указанным ID не найдена
    """
    for i in range(len(books)):
        if books[i].id == book_id:
            deleted_book = books.pop(i)
            return {"message": f"Книга '{deleted_book.title}' успешно удалена"}
    raise HTTPException(status_code=404, detail="Книга не найдена")
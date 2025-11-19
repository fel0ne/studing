from pydantic import BaseModel, Field

class Book(BaseModel):
    id: int = Field(description="Уникальный идентификатор книги", example=1)
    title: str = Field(description="Название книги", example="Мастер и Маргарита")
    author: str = Field(description="Автор книги", example="Михаил Булгаков")
    publication_year: int = Field(description="Год публикации", example=1967)


# Базовая модель пользователя
class User(BaseModel):
    username: str

# Модель для данных, получаемых при регистрации
class UserCreate(User):
    password: str

# Модель для хранения пользователя в "базе данных"
class UserInDB(User):
    hashed_password: str

# Модель для данных токена
class Token(BaseModel):
    access_token: str
    token_type: str

# Модель для данных внутри токена (payload)
class TokenData(BaseModel):
    username: str | None = None
import jwt 
from datetime import datetime, timedelta, timezone
from typing import Dict, Any



from fastapi import APIRouter, Depends, HTTPException, status
from fastapi.security import OAuth2PasswordRequestForm
from typing import List

# Импортируем модели и утилиты
from models import User, UserCreate, UserInDB, Token
from security import get_password_hash, verify_password

from fastapi.security import OAuth2PasswordBearer
from models import TokenData



# Для генерации секретного ключа можно использовать команду в терминале:
# openssl rand -hex 32
SECRET_KEY = "e3b5b053d441cd953a7cc5d9bbd477580b4e17a8a5db426adc393184adf520f2"  # ЗАМЕНИТЕ ЭТО НА СВОЙ КЛЮЧ
ALGORITHM = "HS256"
ACCESS_TOKEN_EXPIRE_MINUTES = 30

# Создаем роутер для эндпоинтов аутентификации
router = APIRouter()

# Наша импровизированная база данных пользователей
fake_users_db: Dict = {}

def get_user(username: str) -> UserInDB | None:
    """
    Находит пользователя по имени пользователя в "базе данных".
    """
    if username in fake_users_db:
        return fake_users_db[username]
    return None

@router.post("/register", response_model=User)
async def register_user(user_in: UserCreate):
    """
    Регистрация нового пользователя.
    """
    if get_user(user_in.username):
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="Username already registered",
        )
    hashed_password = get_password_hash(user_in.password)
    user_db = UserInDB(username=user_in.username, hashed_password=hashed_password)
    fake_users_db[user_in.username] = user_db
    return User(username=user_db.username)

@router.post("/token", response_model=Token)
async def login_for_access_token(form_data: OAuth2PasswordRequestForm = Depends()):
    """
    Аутентификация пользователя и выдача токена.
    """
    user = get_user(form_data.username)
    if not user or not verify_password(form_data.password, user.hashed_password):
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Incorrect username or password",
            headers={"WWW-Authenticate": "Bearer"},
        )
    access_token = create_access_token(
        data={"sub": user.username}
    )
    return {"access_token": access_token, "token_type": "bearer"}

def create_access_token(data: Dict[str, Any]) -> str:
    """
    Создает новый JWT токен доступа.
    """
    to_encode = data.copy()
    expire = datetime.now(timezone.utc) + timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    to_encode.update({"exp": expire})
    encoded_jwt = jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)
    return encoded_jwt


# Эта схема указывает FastAPI, что токен нужно искать в заголовке Authorization
# в формате "Bearer <token>". tokenUrl - это эндпоинт для получения токена.
oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token")

credentials_exception = HTTPException(
    status_code=status.HTTP_401_UNAUTHORIZED,
    detail="Could not validate credentials",
    headers={"WWW-Authenticate": "Bearer"},
)

async def get_current_user(token: str = Depends(oauth2_scheme)) -> User:
    """
    Зависимость для получения текущего пользователя из JWT токена.
    """
    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
        username: str = payload.get("sub")
        if username is None:
            raise credentials_exception
        token_data = TokenData(username=username)
    except jwt.PyJWTError:
        raise credentials_exception
    
    user = get_user(username=token_data.username)
    if user is None:
        raise credentials_exception
    return User(username=user.username)
from passlib.context import CryptContext

# Создаем экземпляр CryptContext, указывая схему хеширования bcrypt
# deprecated="auto" означает, что старые хеши будут автоматически обновляться при необходимости
pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")

def verify_password(plain_password: str, hashed_password: str) -> bool:
    """
    Проверяет, соответствует ли обычный пароль хешированному.
    """
    return pwd_context.verify(plain_password, hashed_password)

def get_password_hash(password: str) -> str:
    """
    Возвращает хеш для заданного пароля.
    """
    return pwd_context.hash(password)
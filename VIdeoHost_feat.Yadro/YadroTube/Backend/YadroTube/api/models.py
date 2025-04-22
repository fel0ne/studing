# Импорт необходимых модулей Django
from django.db import models
from django.contrib.auth.models import User  # Стандартная модель пользователя

# Модель для хранения информации о видео
class Video(models.Model):
    """Модель представляет видеофайл и связанные с ним данные"""
    
    # Заголовок видео: строка до 200 символов
    title = models.CharField(
        max_length=200,
        verbose_name='Название видео'
    )
    
    # Подробное описание видео: текст без ограничения длины
    description = models.TextField(
        verbose_name='Описание видео'
    )
    
    # Поле для загрузки видеофайла
    # Файлы сохраняются в подпапку videos/ медиа-директории
    file = models.FileField(
        upload_to='videos/',
        verbose_name='Видеофайл'
    )
    
    # Связь с автором видео (пользователем)
    # При удалении пользователя удаляются все связанные видео (CASCADE)
    author = models.ForeignKey(
        User,
        on_delete=models.CASCADE,
        verbose_name='Автор'
    )
    
    # Дата и время загрузки видео
    # Автоматически устанавливается при создании записи
    uploaded_at = models.DateTimeField(
        auto_now_add=True,
        verbose_name='Дата загрузки'
    )

    # Строковое представление объекта (для админки и отладки)
    def __str__(self):
        return self.title
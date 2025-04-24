from rest_framework import serializers
from .models import Video
from django.contrib.auth.models import User
from django.contrib.auth.password_validation import validate_password
from django.core.exceptions import ValidationError

class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['id', 'username', 'email', 'date_joined']
        read_only_fields = ['id', 'date_joined']

class VideoSerializer(serializers.ModelSerializer):
    # Поле username автора только для чтения
    author_username = serializers.ReadOnlyField(source='author.username')
    # Поле для получения полного URL файла видео
    file_url = serializers.SerializerMethodField()

    class Meta:
        model = Video
        fields = [
            'id',
            'title',
            'description',
            # 'file', # <-- УДАЛЕНО: Модель имеет поле 'video', а не 'file'
            'video', # <-- ОСТАВЛЕНО: Это имя поля в вашей модели Video
            'file_url', # Поле для полного URL файла видео (SerializerMethodField)
            'author', # Поле автора (ForeignKey)
            'author_username', # Поле username автора (ReadOnlyField)
            'uploaded_at',
            'thumbnail' # Поле миниатюры
        ]
        # Поля, которые не могут быть изменены при создании/обновлении через этот сериализатор
        read_only_fields = ['author', 'uploaded_at', 'thumbnail']
        # Если у вас есть другие read_only поля, добавьте их сюда

    # Метод для получения полного URL файла видео
    def get_file_url(self, obj):
        request = self.context.get('request')
        # Проверяем наличие файла и объекта запроса
        if obj.video and request: # <-- Используем obj.video, т.к. это имя поля в модели
            # Возвращаем полный URL файла видео
            return request.build_absolute_uri(obj.video.url)
        # Если файла нет или нет объекта запроса, возвращаем None
        return None

    # Переопределяем метод create для автоматического назначения автора
    def create(self, validated_data):
        # Устанавливаем текущего пользователя как автора видео
        validated_data['author'] = self.context['request'].user
        # Вызываем стандартный метод create для сохранения объекта
        return super().create(validated_data)

# Сериализатор для регистрации пользователя
class RegistrationSerializer(serializers.ModelSerializer):
    # Поле для пароля (только для записи, обязательное, с валидаторами)
    password = serializers.CharField(
        write_only=True,
        required=True,
        style={'input_type': 'password'},
        validators=[validate_password] # Используем стандартные валидаторы Django для пароля
    )
    # Поле для подтверждения пароля (только для записи, обязательное)
    password2 = serializers.CharField(
        write_only=True,
        style={'input_type': 'password'},
        required=True
    )

    class Meta:
        model = User
        fields = ('username', 'email', 'password', 'password2')
        # Убеждаемся, что email обязателен
        extra_kwargs = {
            'email': {'required': True}
        }

    # Метод для дополнительной валидации (сравнение паролей, проверка email)
    def validate(self, attrs):
        # Проверяем совпадение паролей
        if attrs['password'] != attrs['password2']:
            # Выбрасываем ошибку валидации, если пароли не совпадают
            raise ValidationError({"password": "Пароли не совпадают"})

        # Проверяем, не занят ли email
        if User.objects.filter(email=attrs['email']).exists():
             # Выбрасываем ошибку валидации, если email уже используется
             raise ValidationError({"email": "Этот email уже используется"})

        # Если все проверки пройдены, возвращаем валидированные данные
        return attrs

    # Переопределяем метод create для создания пользователя
    def create(self, validated_data):
        # Удаляем password2, так как оно не является полем модели User
        validated_data.pop('password2')
        # Создаем пользователя с помощью create_user (автоматически хэширует пароль)
        user = User.objects.create_user(**validated_data)
        return user


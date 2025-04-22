from django.urls import path, include
from rest_framework.routers import DefaultRouter
from . import views
from .views import RegistrationAPIView


router = DefaultRouter()
router.register(r'videos', views.VideoViewSet)


urlpatterns = [
    path('auth/register/', RegistrationAPIView.as_view(), name='register'),
    path('', include(router.urls)),
    
]
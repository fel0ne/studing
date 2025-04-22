from rest_framework import viewsets
from .models import Video
from .serializers import VideoSerializer
from rest_framework.permissions import IsAuthenticatedOrReadOnly
from rest_framework import generics, permissions
from rest_framework.response import Response
from .serializers import RegistrationSerializer
from rest_framework import status
class VideoViewSet(viewsets.ModelViewSet):
    queryset = Video.objects.all()
    serializer_class = VideoSerializer
    permission_classes = [IsAuthenticatedOrReadOnly]

    def perform_create(self, serializer):
        serializer.save(author=self.request.user)

class RegistrationAPIView(generics.GenericAPIView):
    serializer_class = RegistrationSerializer
    permission_classes = (permissions.AllowAny,)

    def post(self, request):
        serializer = self.get_serializer(data=request.data)
        serializer.is_valid(raise_exception=True)
        user = serializer.save()
        return Response({
            "user": RegistrationSerializer(user, context=self.get_serializer_context()).data,
            "message": "Пользователь успешно зарегистрирован.",
        }, status=status.HTTP_201_CREATED)
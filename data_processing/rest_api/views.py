from django.shortcuts import render

from rest_framework import viewsets, permissions
from .serializers import *
from rest_framework.response import Response

# Create your views here.
class SensorViewSet(viewsets.ModelViewSet):
    serializer_class = SensorSerializer
    queryset = Sensor.objects.all()
    permission_classes = [permissions.AllowAny]

class SensorDataViewSet(viewsets.ModelViewSet):
    serializer_class = SensorDataSerializer
    queryset = SensorData.objects.all()
    permission_classes = [permissions.AllowAny]
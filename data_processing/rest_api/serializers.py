from rest_framework import serializers
from principal_app.models import *

class SensorSerializer(serializers.ModelSerializer):
    class Meta:
        model = Sensor
        fields = "__all__"
        read_only_fields = ['pub_date', 'upd_date']
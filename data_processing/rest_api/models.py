from django.db import models

# Create your models here.
class Sensor(models.Model):
    sensor_name = models.CharField(max_length=200)
    sensor_value = models.CharField(max_length=10)
    pub_date = models.DateTimeField(auto_now=True)
    upd_date = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return "{}-{}".format(self.sensor_name, self.sensor_value)

class SensorData(models.Model):
    sensor = models.ForeignKey(Sensor, on_delete=models.CASCADE)
    data = models.CharField(max_length=10)
from email.policy import default
from secrets import choice
from django.db import models

# Create your models here.
class Sensor(models.Model):

    SENSOR_UNITS = [
        ('C', 'Celsius'),
        ('F', 'Fahrenheit'),
        ('m', 'Meters'),
        ('km', 'Kilometers')
    ]

    sensor_name = models.CharField(max_length=200)
    sensor_unit = models.CharField(max_length=5, choices=SENSOR_UNITS, default='C')
    pub_date = models.DateTimeField(auto_now_add=True)
    upd_date = models.DateTimeField(auto_now=True)

    def __str__(self):
        return "{} Unit:{}".format(self.sensor_name, self.sensor_unit)

class SensorData(models.Model):
    sensor = models.ForeignKey(Sensor, on_delete=models.CASCADE)
    date_registered = models.DateField(auto_now=True)
    value = models.IntegerField()
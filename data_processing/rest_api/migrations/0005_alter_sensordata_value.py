# Generated by Django 4.1.3 on 2022-11-05 22:45

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('rest_api', '0004_sensordata_time_registered'),
    ]

    operations = [
        migrations.AlterField(
            model_name='sensordata',
            name='value',
            field=models.DecimalField(decimal_places=2, max_digits=3),
        ),
    ]
# Generated by Django 2.1.5 on 2020-04-28 09:46

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('chart', '0002_auto_20200426_1851'),
    ]

    operations = [
        migrations.AddField(
            model_name='chart',
            name='price',
            field=models.IntegerField(null=True),
        ),
    ]

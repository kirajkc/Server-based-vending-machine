from django.db import models
from django.utils import timezone

# Create your models here.
class vend1(models.Model):
    tagid=models.IntegerField(null=True)
    item=models.TextField(max_length=50)
    quantity=models.IntegerField(null=True)
    price=models.IntegerField(null=True)
    def __str__(self):
        return self.item
    class Meta: 
        verbose_name_plural = 'vend1'
        ordering = ('tagid',)


class vend2(models.Model):
    tagid=models.IntegerField(null=True)
    item=models.TextField(max_length=50)
    quantity=models.IntegerField(null=True)
    price=models.IntegerField(null=True)
    def __str__(self):
        return self.item
    class Meta: 
        verbose_name_plural = 'vend2'
        ordering = ('tagid',)

class sold1(models.Model):
    tagid=models.IntegerField(null=True)
    item=models.TextField(max_length=50)
    quantity=models.IntegerField(null=True)
    price=models.IntegerField(null=True)
    saleTime = models.DateTimeField(default=timezone.now)
    def __str__(self):
        return self.item
    class Meta: 
        verbose_name_plural = 'sold1'
        ordering = ('saleTime',)

class sold2(models.Model):
    tagid=models.IntegerField(null=True)
    item=models.TextField(max_length=50)
    quantity=models.IntegerField(null=True)
    price=models.IntegerField(null=True)
    saleTime = models.DateTimeField(default=timezone.now)
    def __str__(self):
        return self.item
    class Meta: 
        verbose_name_plural = 'sold2'
        ordering = ('saleTime',)


class alert(models.Model):

    value=models.IntegerField(null=True)
    def __str__(self):
        return "value"
    class Meta: 
        verbose_name_plural = 'alert'
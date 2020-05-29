from django.db import models

# Create your models here.
class chart(models.Model):
    tagid=models.IntegerField(null=True)
    item=models.TextField(max_length=50)
    quantity=models.IntegerField(null=True)
    price=models.IntegerField(null=True)
    def __str__(self):
        return self.item
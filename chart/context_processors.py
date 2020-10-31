from chart.models import alert

def categories_processor(request):
 categories = alert.objects.all()            
 return {'categories': categories}
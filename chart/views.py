from django.shortcuts import get_object_or_404, redirect, render
from .models import chart
from django.http import JsonResponse
from django.contrib.auth.decorators import login_required
from django.contrib import auth

@login_required(login_url="login/")
def home(request):
    c=chart.objects
    return render(request,'home.html',{'chart':c})

def get_data(request):
    ab=chart.objects.all()
    name = []
    defaultitems = []
    defaultprice=[]
    for items in ab:
        name.append(items.item)
        defaultitems.append(items.quantity)
        defaultprice.append(items.price)
    
    data={
        "labels":name,
        "default": defaultitems,
        "price": defaultprice
    }
    return JsonResponse(data)

def base(request):
    return render(request,'base.html')


def add(request):
    c=chart.objects
    if request.method=="POST":
        if request.POST['item'] and request.POST['quantity']:
            j=chart()
            j.tagid=request.POST['tagid']
            j.item=request.POST['item']
            j.quantity=request.POST['quantity']
            j.price=request.POST['price']
            j.save()
            return redirect('add')
        else:
            return render(request,'add.html',{'error':"no product found"})
    return render(request,'add.html',{'chart':c})

def login(request):
    if request.method == 'POST':
        user = auth.authenticate(username = request.POST['username'],password=request.POST['password1'])
        if user is not None:
            auth.login(request,user)
            return redirect('home')
        else:
            return render(request,'login.html',{'error':"username or password is incorrect"})
    else:
            return render(request,'login.html')
    return render(request,'login.html')

def logout(request):
    if request.method=="POST":
        auth.logout(request)
        return redirect('home')
    return render(request,'home.html')

def update(request,chart_id):
    d=get_object_or_404(chart,pk=chart_id)
    if request.method=="POST":
        if request.POST['item'] and request.POST['quantity']:
            
            d.item=request.POST['item']
            d.quantity=request.POST['quantity']
            d.price=request.POST['price']
            d.save()
            return redirect('home')
        else:
            return render(request,'update.html',{'error':"no product found"})
    return render(request,'update.html',{'update':d})

def erase(request,chart_id):
    c=chart.objects
    d=get_object_or_404(chart,pk=chart_id)
    return render(request,'delete.html',{'chart':c,'required':d})

def Remove(request,chart_id):
    d=get_object_or_404(chart,pk=chart_id)
    d.delete()
    return redirect('home')


# def edit(request):
#     c=chart.objects
#     return render(request,'edit.html',{'chart':c})
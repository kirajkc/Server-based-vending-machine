from django.shortcuts import get_object_or_404, redirect, render
from .models import vend1,vend2,sold1,sold2,alert
from django.http import JsonResponse
from django.contrib.auth.decorators import login_required
from django.contrib import auth

@login_required(login_url="login/")
def home(request):
    a=vend1.objects.all()
    b=vend2.objects.all()
    s1=sold1.objects.all()
    s2=sold2.objects.all()
    c=0
    d=0
    e=0
    f=0
    for i in s1:
        c = c + i.quantity
        d = d + i.price
    for i in s2:
        e = e + i.quantity
        f = f + i.price
    return render(request,'home.html',{'vend1':a,'vend2':b,'c':c,'d':d,'e':e,'f':f,'g':c+e,'h':d+f})

@login_required(login_url="login/")
def get_data(request):
    a=vend1.objects.all()
    b=vend2.objects.all()
    name = []
    defaultitems = []
    defaultprice=[]
    name1 = []
    defaultitems1 = []
    defaultprice1=[]
    line=[]
    line1=[]
    for items in a:
        name.append(items.item)
        defaultitems.append(items.quantity)
        defaultprice.append(items.price)
        line.append('10')
    for items in b:
        name1.append(items.item)
        defaultitems1.append(items.quantity)
        defaultprice1.append(items.price)
        line1.append('10')
    data={
        "labels":name,
        "default": defaultitems,
        "price": defaultprice,
        "labels1":name1,
        "default1": defaultitems1,
        "price1": defaultprice1,
        "line1": line1,
        "line": line
        }
    return JsonResponse(data)

@login_required(login_url="login/")
def base(request):
    c=alert.objects.all()
    return render(request,'base.html',{'categories':c})

@login_required(login_url="login/")
def add(request):
    c=vend1.objects
    if request.method=="POST":
        if request.POST['item'] and request.POST['quantity']:
            j=vend1()
            j.tagid=request.POST['tagid']
            j.item=request.POST['item']
            j.quantity=request.POST['quantity']
            j.price=request.POST['price']
            j.save()
            return redirect('home')
        else:
            return render(request,'add.html',{'error':"no product found"})
    return render(request,'add.html',{'vend1':c})


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

@login_required(login_url="login/")
def update(request,vend_id):
    try:
         d = vend1.objects.get(pk=vend_id)
    except:
        d = vend2.objects.get(pk=vend_id)

    if request.method=="POST":
        if request.POST['item'] and request.POST['quantity']:
            
            d.item=request.POST['item']
            d.tagid=request.POST['tagid']
            d.quantity=request.POST['quantity']
            d.price=request.POST['price']
            d.save()
            return redirect('home')
        else:
            return render(request,'update.html',{'error':"no product found"})
    return render(request,'update.html',{'update':d})

@login_required(login_url="login/")
def erase(request,vend_id):
    try:
         d = vend1.objects.get(pk=vend_id)
         c = vend1.objects
    except:
        d = vend2.objects.get(pk=vend_id)
        c = vend2.objects
    return render(request,'delete.html',{'vend1':c,'required':d})

@login_required(login_url="login/")
def Remove(request,vend_id):
    try:
         d = vend1.objects.get(pk=vend_id)
    except:
        d = vend2.objects.get(pk=vend_id)
    d.delete()
    return redirect('home')

@login_required(login_url="login/")
def sold(request):
    c = sold1.objects.all()
    d= sold2.objects.all()
    a=[]
    b=[]
    f=[]
    itm=[]
    qn=[]  
    p=[]
    id=[]
    y=[]
    for item in c:
        itm.append(item.item)
        qn.append(item.quantity)
        id.append(item.tagid)
        p.append(item.price)
    for i in itm:
        if i not in a:
            a.append(i)
    for i in id:
        if i not in f:
            f.append(i)
    
    for i in f:
        e=0
        z=0
        for j in range(len(itm)):
            if id[j] is  i:
                e = e + qn[j]
                z = z + p[j]
        b.append(e)
        y.append(z)
    l= zip(a, b,y)


    a1=[]
    b1=[]
    f1=[]
    itm1=[]
    qn1=[]  
    p1=[]
    id1=[]
    y1=[]
    for item in d:
        itm1.append(item.item)
        qn1.append(item.quantity)
        id1.append(item.tagid)
        p1.append(item.price)
    for i in itm1:
        if i not in a1:
            a1.append(i)
    for i in id1:
        if i not in f1:
            f1.append(i)
    
    for i in f1:
        e=0
        z=0
        for j in range(len(itm1)):
            if id1[j] is  i:
                e = e + qn1[j]
                z = z + p1[j]
        b1.append(e)
        y1.append(z)
    l1= zip(a1, b1,y1)
 
    return render(request,'sold.html',{'k':l1,'l':l})

@login_required(login_url="login/")
def saleschart1(request):
    c = sold1.objects
    d="VEND1"
    return render(request,'saleschart.html',{'sold':c,"d":d})

@login_required(login_url="login/")
def saleschart2(request):
    c= sold2.objects
    d="VEND2"
    return render(request,'saleschart.html',{'sold':c,'d':d})

@login_required(login_url="login/")
def get_saledata(request):
    c=sold1.objects.all()
    d=sold2.objects.all()
    totalsold=0
    totalsold1=0
    price=[]
    vend=[]

    a=[]
    b=[]
    f=[]
    itm=[]
    qn=[]  
    p=[]
    id=[]
    y=[]

    for item in c:
        itm.append(item.item)
        qn.append(item.quantity)
        id.append(item.tagid)
    for i in itm:
        if i not in a:
            a.append(i)
    for i in id:
        if i not in f:
            f.append(i)
    for i in f:
        e=0
        for j in range(len(itm)):
            if id[j] is  i:
                e = e + qn[j]
        b.append(e)


    a1=[]
    b1=[]
    f1=[]
    itm1=[]
    qn1=[]  
    p1=[]
    id1=[]
    y1=[]

    for item in d:
        itm1.append(item.item)
        qn1.append(item.quantity)
        id1.append(item.tagid)
    for i in itm1:
        if i not in a1:
            a1.append(i)
    for i in id1:
        if i not in f1:
            f1.append(i)
    for i in f1:
        e=0
        for j in range(len(itm1)):
            if id1[j] is  i:
                e = e + qn1[j]
        b1.append(e)
    

    for items in c:
        totalsold=totalsold + items.price
    price.append(totalsold)
    vend.append("vend1")
    for items in d:
        totalsold1=totalsold1 + items.price
    price.append(totalsold1)
    vend.append("vend2")
    data={
        "labels":a,
        "default": b,
        "labels1":a1,
        "default1": b1,
        "totalprice":price,
        "vend":vend
        }
    return JsonResponse(data)


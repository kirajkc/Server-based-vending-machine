"""vend URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from  chart import views 
from chart.views import get_data, get_saledata

urlpatterns = [
    path('admin/', admin.site.urls),
    path('',views.home,name='home'),
    path('add/',views.add,name='add'),
    path('api/chartview',get_data,name="apidata"),
    path('api1/chartview',get_saledata,name="apidata1"),
    path('base/',views.base,name='base'),
    path('login/',views.login,name='login'),
    path('logout/',views.logout,name='logout'),
    path('update/<int:vend_id>',views.update,name="update"),
    path('erase/<int:vend_id>',views.erase,name="delete"),
    path('Remove/<int:vend_id>',views.Remove,name="Remove"),
    path('sold/',views.sold,name='sold'),
    path('saleschart1/',views.saleschart1,name='saleschart1'),
    path('saleschart2/',views.saleschart2,name='saleschart2'),
    
]


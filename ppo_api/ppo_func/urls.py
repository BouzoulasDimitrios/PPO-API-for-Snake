from django.urls import path
from . import views

urlpatterns = [
    path('', views.get_move),
    path('', views.get_reward),
    path('get-number/', views.get_number, name='get_number'),
]




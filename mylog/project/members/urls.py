from django.urls import path
from .views import UserRegistrationForm
urlpatterns = [
    path('register/',UserRegistrationForm.as_view(),name='register'),
]
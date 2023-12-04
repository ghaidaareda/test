from django.urls import path
#from . import views
from .views import HomeView, ArticleView, AddPostView, AboutBlogView, EditPostView
from .views import DeletePostView
urlpatterns = [
    #path("", views.home, name="home"),
    path('', HomeView.as_view(), name="home"),
    path('article/<int:pk>', ArticleView.as_view(), name="article"),
    path('add_post', AddPostView.as_view(), name="add_post"),
    path('about', AboutBlogView.as_view(), name="about"),
    path('article/edit/<int:pk>', EditPostView.as_view(), name="edit_post"),
    path('article/<int:pk>/delete', DeletePostView.as_view(), name="delete_post"),
]
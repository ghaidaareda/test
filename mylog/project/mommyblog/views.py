from django.shortcuts import render
from django.views.generic import ListView, DetailView, CreateView
from .models import Post
from .forms import BlogPostForm
#def home(request):
    #return render(request, 'home.html', {})
class HomeView(ListView):
    model = Post
    template_name ='home.html'
    
class ArticleView(DetailView):
    model = Post
    template_name ='article_details.html'
    
class AddPostView(CreateView):
    model = Post
    form_class = BlogPostForm
    template_name ='add_post.html'
    
class AboutBlogView(ListView):
    model = Post
    template_name = 'about.html'
    

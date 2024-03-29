from django.shortcuts import render
from django.views.generic import ListView, DetailView, CreateView, UpdateView, DeleteView
from .models import Post, Category
from .forms import BlogPostForm
from django.urls import reverse_lazy
#def home(request):
    #return render(request, 'home.html', {})
class HomeView(ListView):
    model = Post
    template_name ='home.html'
    ordering = ['-id']
    
class ArticleView(DetailView):
    model = Post
    template_name ='article_details.html'
    
class AddPostView(CreateView):
    model = Post
    form_class = BlogPostForm
    template_name ='add_post.html'
    
class AddCategoryView(CreateView):
    model = Category
    template_name ='add_category.html'
    fields = '__all__'
    
class AboutBlogView(ListView):
    model = Post
    template_name = 'about.html'
    
class EditPostView(UpdateView):
    model = Post
    template_name ='edit_post.html'
    form_class = BlogPostForm
    
class DeletePostView(DeleteView):
    model = Post
    template_name ='delete_post.html'
    success_url = reverse_lazy('home')
    
    

    
